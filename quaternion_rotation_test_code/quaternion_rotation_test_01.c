#include<stdio.h>
#include<math.h>
#include<stdlib.h>

typedef struct{ //quaternion
    float a;
    float b;
    float c;
    float d;
}Q;

Q generate_quaternion(float angle,Q axis){  //generate quaternion
    Q q;
    q.a=cos(0.5*angle);
    q.b=sin(0.5*angle)*axis.b;
    q.c=sin(0.5*angle)*axis.c;
    q.d=sin(0.5*angle)*axis.d;

    return q;
}

float** generate_3x3(Q q){                  //generate 3x3 矩阵  bsed on quaternion
    float **j=(float**)malloc(sizeof(float*)*3);
    for(int i=0;i<3;i++){
        j[i]=(float*)malloc(sizeof(float)*3);
    }

    //L(q)R(q*)

    j[0][0]=1-2*(q.c)*(q.c)-2*(q.d)*(q.d);
    j[0][1]=2*(q.b)*(q.c)-2*(q.a)*(q.d);
    j[0][2]=2*(q.a)*(q.c)+2*(q.b)*(q.d);

    j[1][0]=2*q.b*q.c+2*q.a*q.d;
    j[1][1]=1-2*q.b*q.b-2*q.d*q.d;
    j[1][2]=2*q.c*q.d-2*q.a*q.b;

    j[2][0]=2*q.b*q.d-2*q.a*q.c;
    j[2][1]=2*q.a*q.b+2*q.c*q.d;
    j[2][2]=1-2*q.b*q.b-2*q.c*q.c;

    return j;
}

float* mutiply(float** j,float* v){             //矩阵 乘法
    float *nv=(float*)malloc(sizeof(float)*3);
    for(int i=0;i<3;i++){
        nv[i]=0;
        for(int k=0;k<3;k++){
            nv[i]+=v[k]*j[i][k];
        }
    }

    return nv;
}


int main(){
    float angle=3.1415926/4;  //要旋转的角度
    
    Q axis;                 //绕哪个轴旋转  （轴必过原点）（模长为1）
    axis.a=0;//无用项
    axis.b=0;
    axis.c=1;
    axis.d=0;

    float v[3]={3,0,0};     //要被旋转的点




    Q q=generate_quaternion(angle,axis);
    float** juz=generate_3x3(q);

    float* result=mutiply(juz,v);

    printf("%f   %f   %f",result[0],result[1],result[2]);


    return 0;
}