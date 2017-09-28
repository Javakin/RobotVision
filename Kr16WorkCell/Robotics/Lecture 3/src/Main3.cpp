#include <iostream>
#include <rw/math.hpp> // Pi, Deg2Rad
#include <rw/math/Q.hpp>
#include <rw/math/Transform3D.hpp>
#include <rw/math/RPY.hpp>
#include <rw/math/Vector3D.hpp>
#include <rw/math/EAA.hpp>
#include <math.h>

using namespace std;
using namespace rw::math;

void dot3x3(float Matrix1[3][3], float Matrix2[3][3], float return_Matrix[3][3]){
    for(int x = 0; x < 3; x++){
       for(int y = 0; y < 3; y++){
           return_Matrix[x][y] = 0;
           for(int i = 0; i < 3; i++){
               return_Matrix[x][y] += Matrix1[i][y]*Matrix2[x][i];
           }
       }
    }
}
void dot3x1(float Matrix1[3][3], float Matrix2[3], float return_Matrix[3]){
    for(int y = 0; y < 3; y++){
       return_Matrix[y] = 0;
       for(int i = 0; i < 3; i++){
           return_Matrix[y] += Matrix1[i][y]*Matrix2[i];
       }
    }
}

void Print3x3Matrix(float Matrix[3][3]){
    cout << "Printing Matrix" << endl;
    for(int x = 0; x < 3; x++){
       for(int y = 0; y < 3; y++){
           cout << Matrix[x][y] << "\t";
       }
       cout << endl;
    }
}

void Rotate(float Vector[3],char axis,float angel_deg){
    float C = cos(angel_deg/360*(2*M_PI));
    cout << angel_deg/360*(2*M_PI) << ", " << C << endl;
    float S = sin(angel_deg/360*(2*M_PI));
    
    if(axis == 'y'|| axis == 'Y'){
        float RotMat[3][3] = {
            {C,0,S},
            {0,1,0},
            {-S,0,C}
        };
        float* Res = new float[3];
        dot3x1(RotMat,Vector,Res);
        delete(Vector);
        Vector = Res;
        
    }else if(axis == 'x'|| axis == 'X'){
        float RotMat[3][3] = {
            {1,0,0},
            {0,C,-S},
            {0,S,C}
        };
        float* Res = new float[3];
        dot3x1(RotMat,Vector,Res);
        delete(Vector);
        Vector = Res;
        
    }else if(axis == 'z'|| axis == 'Z'){
        float RotMat[3][3] = {
            {C,-S,0},
            {S,C,0},
            {0,0,1} 
        };
        float* Res = new float[3];
        dot3x1(RotMat,Vector,Res);
        delete(Vector);
        Vector = Res;
        
    }else{
        cout << "you have failed" << endl;
    }
}


int main(int argc, char** argv) {
    float Mat1[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    float Mat2[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
    float* Vec1 = new float[3];
    Vec1[1] = 3;
    Vec1[0] = 3;
    Vec1[2] = 3;
    Print3x3Matrix(Mat1);
    Rotate(Vec1,'y',180);
    cout << "Vec out" <<endl;
    for(int x = 0; x<3; x++){
        cout << Vec1[x] << endl;
    }

	return 0;
}
