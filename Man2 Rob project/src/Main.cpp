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

int main(int argc, char** argv) {
    const string wcFile = "../Kr16WallWorkCell/Scene.wc.xml";
    const string deviceName = "KukaKr16";
    cout << "Trying to use workcell " << wcFile << " and device " << deviceName << endl;



    WorkCell::Ptr wc = WorkCellLoader::Factory::load(wcFile);
    Device::Ptr device = wc->findDevice(deviceName);

    // check that the device has been correctly added
    if (device == NULL) {
        cerr << "Device: " << deviceName << " not found!" << endl;
        return 0;
    }
    const State state = wc->getDefaultState();

    CollisionDetector detector(wc, ProximityStrategyFactory::makeDefaultCollisionStrategy());
    PlannerConstraint constraint = PlannerConstraint::make(&detector,device,state);

    /** Most easy way: uses default parameters based on given device
        sampler: QSampler::makeUniform(device)
        metric: PlannerUtil::normalizingInfinityMetric(device->getBounds())
        extend: 0.05 */
    //QToQPlanner::Ptr planner = RRTPlanner::makeQToQPlanner(constraint, device, RRTPlanner::RRTConnect);

    /** More complex way: allows more detailed definition of parameters and methods */
    QSampler::Ptr sampler = QSampler::makeConstrained(QSampler::makeUniform(device),constraint.getQConstraintPtr());
    QMetric::Ptr metric = MetricFactory::makeEuclidean<Q>();
    double extend = 0.1;
    QToQPlanner::Ptr planner = RRTPlanner::makeQToQPlanner(constraint, sampler, metric, extend, RRTPlanner::RRTConnect);

    //Q from(6,-0.2,-0.6,1.5,0.0,0.6,1.2);
    //Q to(6,1.7,0.6,-0.8,0.3,0.7,-0.5); // Very difficult for planner
    //Q to(6,1.4,-1.3,1.5,0.3,1.3,1.6);

    Q from(6, -3.142, -0.827, -3.002, -3.143, 0.099, -1.573); // exercise path
    Q to(6, 1.571, 0.006, 0.03, 0.153, 0.762, 4.49);


    if (!checkCollisions(device, state, detector, from))
        return 0;
    if (!checkCollisions(device, state, detector, to))
        return 0;

    cout << "Planning from " << from << " to " << to << endl;
    QPath path;
    Timer t;
    t.resetAndResume();
    planner->query(from,to,path,MAXTIME);
    t.pause();
    cout << "Path of length " << path.size() << " found in " << t.getTime() << " seconds." << endl;
    if (t.getTime() >= MAXTIME) {
        cout << "Notice: max time of " << MAXTIME << " seconds reached." << endl;
    }

    // print the path in the cout terminal
    /*for (unsigned  int n = 0; n < path.size(); n++){
        std::cout << "setQ({";
        cout << path[n][0];
        for(unsigned int i = 1; i<6; i++){
           cout << ", " << path[n][i];
        }
        std::cout << "})" << endl;
    }*/



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
        myfile << "rw.sleep(0.1)" << endl;
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
      else
          return 1;


    cout << "Program done." << endl;
    return 0;
}
