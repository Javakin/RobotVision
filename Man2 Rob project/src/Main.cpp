#include <iostream>
#include <rw/rw.hpp>
#include <rwlibs/pathplanners/rrt/RRTPlanner.hpp>
#include <rwlibs/pathplanners/rrt/RRTQToQPlanner.hpp>
#include <rwlibs/proximitystrategies/ProximityStrategyFactory.hpp>
#include <fstream>

using namespace std;
using namespace rw::common;
using namespace rw::math;
using namespace rw::kinematics;
using namespace rw::loaders;
using namespace rw::models;
using namespace rw::pathplanning;
using namespace rw::proximity;
using namespace rw::trajectory;
using namespace rwlibs::pathplanners;
using namespace rwlibs::proximitystrategies;

#define MAXTIME 60.


WorkCell::Ptr wc;
Device::Ptr device;
rw::kinematics::Frame* gripper;
rw::kinematics::Frame* bottle;

bool checkCollisions(Device::Ptr device, const State &state, const CollisionDetector &detector, const Q &q) {
    State testState;
    CollisionDetector::QueryResult data;
    bool colFrom;

    testState = state;
    device->setQ(q,testState);
    colFrom = detector.inCollision(testState,&data);
    if (colFrom) {
        cerr << "Configuration in collision: " << q << endl;
        cerr << "Colliding frames: " << endl;
        FramePairSet fps = data.collidingFrames;
        for (FramePairSet::iterator it = fps.begin(); it != fps.end(); it++) {
            cerr << (*it).first->getName() << " " << (*it).second->getName() << endl;
        }
        return false;
    }
    return true;
}

double pathLength(QPath path,State state){
    if(path.size() == 0) return 0;
    Q pos1,pos2;
    Transform3D<double> tra1,tra2;
    Vector3D<double> vec;
    pos2 = path[0];
    double Length = 0;
    for(unsigned int i = 1; i<path.size(); i++){
        pos1 = path[i];
	
        device->setQ(pos1,state);
        tra1 = device->baseTframe(bottle,state);
	
        device->setQ(pos2,state);
        tra2 = device->baseTframe(bottle,state);

	vec = tra2.P()-tra1.P();
	Length+= vec.norm2();
	pos2 = pos1;
    }
    return Length;

}
double configLength(QPath path){
    if(path.size() == 0) return 0;
    Q pos1,pos2;
    pos2 = path[0];
    double Length = 0;
    for(unsigned int i = 1; i<path.size(); i++){
        pos1 = path[i];
	pos2 -=pos1;
	Length+= pos2.norm2();
	pos2 = pos1;
    }
    return Length;

}

void exportLUA(QPath path){
    // write the data toan executable Lua file
    ofstream myfile;
     myfile.open ("../LUA_code.txt");
    if (myfile.is_open()){
        // initial code for the LUA file
        myfile << "wc = rws.getRobWorkStudio():getWorkCell()" << endl;
        myfile << "state = wc:getDefaultState()" << endl;
        myfile << "device = wc:findDevice(\"KukaKr16\")" << endl;
        myfile << "gripper = wc:findFrame(\"Tool\");" << endl;
        myfile << "bottle = wc:findFrame(\"Bottle\");" << endl;
        myfile << "table = wc:findFrame(\"Table\");" << endl;

        myfile << "function setQ(q)" << endl;
        myfile << "qq = rw.Q(#q,q[1],q[2],q[3],q[4],q[5],q[6])" << endl;
        myfile << "device:setQ(qq,state)" << endl;
        myfile << "rws.getRobWorkStudio():setState(state)" << endl;
        myfile << "rw.sleep(0.01)" << endl;
        myfile << "end" << endl;

        myfile << "function attach(obj, tool)" << endl;
        myfile << "rw.gripFrame(obj, tool, state)" << endl;
        myfile << "rws.getRobWorkStudio():setState(state)" << endl;
        myfile << "rw.sleep(0.1)" << endl;
        myfile << "end" << endl;


        myfile << "setQ({-3.142, -0.827, -3.002, -3.143, 0.099, -1.573})" << endl;
        myfile << "attach(bottle,gripper)" << endl;



         // insert RRT-path
         for (unsigned  int n = 1; n < path.size(); n++){
              myfile << "setQ({";
              myfile << path[n][0];
              for(unsigned int i = 1; i<6; i++){
                 myfile << ", " << path[n][i];
              }
              myfile << "})" << endl;
          }

          myfile <<"attach(bottle,table)" << endl;


          myfile.close();
      }

}

int main(int argc, char** argv) {
    const string wcFile = "../../Kr16WallWorkCell/Scene.wc.xml";
    const string deviceName = "KukaKr16";
    cout << "Trying to use workcell " << wcFile << " and device " << deviceName << endl;

    // initialize see
    rw::math::Math::seed();
    Timer t;
    QPath path;
    wc = WorkCellLoader::Factory::load(wcFile);
    device = wc->findDevice(deviceName);

    // check that the device has been correctly added
    if (device == NULL) {
        cerr << "Device: " << deviceName << " not found!" << endl;
        return 0;
    }

    State state = wc->getDefaultState();
    Q from(6, -3.142, -0.827, -3.002, -3.143, 0.099, -1.573); // exercise path
    Q to(6, 1.571, 0.006, 0.03, 0.153, 0.762, 4.49);

    device->setQ(from,state);
    gripper = wc->findFrame("Tool");
    bottle = wc->findFrame("Bottle");
    rw::kinematics::Kinematics::gripFrame(bottle, gripper, state);

    CollisionDetector detector(wc, ProximityStrategyFactory::makeDefaultCollisionStrategy());
    PlannerConstraint constraint = PlannerConstraint::make(&detector,device,state);

    /** Most easy way: uses default parameters based on given device
        sampler: QSampler::makeUniform(device)
        metric: PlannerUtil::normalizingInfinityMetric(device->getBounds())
    extend: 0.05 */

   

    /** More complex way: allows more detailed definition of parameters and methods */
    QSampler::Ptr sampler = QSampler::makeConstrained(QSampler::makeUniform(device),constraint.getQConstraintPtr());
    QMetric::Ptr metric = MetricFactory::makeEuclidean<Q>();

    //###################################################################################################
    //for generating lua script
    
    double extend = 0.1;
     QToQPlanner::Ptr planner = RRTPlanner::makeQToQPlanner(constraint, sampler, metric, extend, RRTPlanner::RRTBalancedBidirectional);
    

    if (!checkCollisions(device, state, detector, from))
        return 0;
    if (!checkCollisions(device, state, detector, to))
        return 0;

	cout << "Planning from " << from << " to " << to << endl;

    t.resetAndResume();
    planner->query(from,to,path,MAXTIME);
    t.pause();
    
    cout << "Path of length " << path.size() << " found in " << t.getTime() << " seconds." << endl;
    if (t.getTime() >= MAXTIME) {
        cout << "Notice: max time of " << MAXTIME << " seconds reached." << endl;
	}
    
    cout << pathLength(path,state)<< endl;;
    exportLUA(path);
    
    
    //###################################################################################################
    // For generating test statistics
    /*
    int loops = 40;
    QPath reset;
    ofstream myfile;
    double Length[loops];
    double ConLength[loops];
    
    myfile.open ("../Test_statistics2.txt");
    if (!myfile.is_open()){
      cout << "file not found" << endl;
      return 1;
    }

    for (double extend = 0.5 ; extend < 10; extend += 0.5){
      cout << "extend: " << extend << flush;
      QToQPlanner::Ptr planner = RRTPlanner::makeQToQPlanner(constraint, sampler, metric, extend, RRTPlanner::RRTBalancedBidirectional);
      myfile << endl << extend << ",";
      for(int i = 0; i<loops; i++){
	path = reset;
	t.resetAndResume();
	planner->query(from,to,path,MAXTIME);
	t.pause();
	Length[i] = pathLength(path,state);
	ConLength[i] = configLength(path);
	myfile << t.getTime() <<", ";
	cout << ";" << i<< flush; 
      }
      for(int i = 0; i<loops;i++){
	myfile << Length[i] << ", ";
      }
      for(int i = 0; i<loops;i++){
	myfile << ConLength[i] << ", ";
      }
      cout << endl;
     }
    */
    //###################################################################################################

    cout << "Program done." << endl;
    return 0;
}


