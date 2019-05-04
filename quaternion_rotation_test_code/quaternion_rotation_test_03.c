#include<stdio.h>
#include<math.h>
#include<stdlib.h>

float*generate_quaternion(float*u){
    float*q=(float*)malloc(sizeof(float)*4);
    q[0]=cos(0.5*u[0]);
    q[1]=sin(0.5*u[0])*u[1];
    q[2]=sin(0.5*u[0])*u[2];
    q[3]=sin(0.5*u[0])*u[3];

    return q;
}

float** generate_matrix_3x3(float*q){
    float **m=(float**)malloc(sizeof(float*)*3);
    for(int i=0;i<3;i++){
        m[i]=(float*)malloc(sizeof(float)*3);
    }

    //L(q)R(q*)

    m[0][0]=1-2*q[2]*q[2]-2*q[3]*q[3];
    m[0][1]=2*q[1]*q[2]-2*q[0]*q[3];
    m[0][2]=2*q[0]*q[2]+2*q[1]*q[3];

    m[1][0]=2*q[1]*q[2]+2*q[0]*q[3];
    m[1][1]=1-2*q[1]*q[1]-2*q[3]*q[3];
    m[1][2]=2*q[2]*q[3]-2*q[0]*q[1];

    m[2][0]=2*q[1]*q[3]-2*q[0]*q[2];
    m[2][1]=2*q[0]*q[1]+2*q[2]*q[3];
    m[2][2]=1-2*q[1]*q[1]-2*q[2]*q[2];

    return m;
}

float* mutiply_3x1(float** j,float* v){             //矩阵 乘法
    float *nv=(float*)malloc(sizeof(float)*3);
    for(int i=0;i<3;i++){
        nv[i]=0;
        for(int k=0;k<3;k++){
            nv[i]+=v[k]*j[i][k];
        }
    }

    return nv;
}

float* one_Rotation(float*v,float*u){
    float*q=generate_quaternion(u);
    float**m=generate_matrix_3x3(q);
    float*nv=mutiply_3x1(m,v);

    free(q);
    free(m);

    return nv;
}


int main(){
    float v[3]={2,2,0};     // v[0]=x, v[1]=y, v[2]=z
    float u[4]={3.1415926/2,0,0,1};     //u[0]=angle, u[1]=x, u[2]=y, u[3]=z

    float* result=one_Rotation(v,u);

    printf("%f   %f   %f",result[0],result[1],result[2]);

    return 0;
}