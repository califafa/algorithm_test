#include<stdio.h>
#include<stdlib.h>
#include<math.h>


float* generate_quaternion(float* u){
    float* q=(float*)malloc(sizeof(float)*4);
    q[0]=cos(0.5*u[0]);
    q[1]=sin(0.5*u[0])*u[1];
    q[2]=sin(0.5*u[0])*u[2];
    q[3]=sin(0.5*u[0])*u[3];

    return q;
}

//左乘q 等价矩阵 4x4
float** generate_matrix_qL(float* q){
    float **m=(float**)malloc(sizeof(float*)*4);
    for(int i=0;i<4;i++){
        m[i]=(float*)malloc(sizeof(float)*4);
    }
    m[0][0]=q[0];
    m[0][1]=(-1)*q[1];
    m[0][2]=(-1)*q[2];
    m[0][3]=(-1)*q[3];
    m[1][0]=q[1];
    m[1][1]=q[0];
    m[1][2]=(-1)*q[3];
    m[1][3]=q[2];
    m[2][0]=q[2];
    m[2][1]=q[3];
    m[2][2]=q[0];
    m[2][3]=(-1)*q[1];
    m[3][0]=q[3];
    m[3][1]=(-1)*q[2];
    m[3][2]=q[1];
    m[3][3]=q[0];

    return m;
}

//右乘q 等价矩阵 4x4
float** generate_matrix_qR(float* q){
    float **m=(float**)malloc(sizeof(float*)*4);
    for(int i=0;i<4;i++){
        m[i]=(float*)malloc(sizeof(float)*4);
    }
    m[0][0]=q[0];
    m[0][1]=(-1)*q[1];
    m[0][2]=(-1)*q[2];
    m[0][3]=(-1)*q[3];
    m[1][0]=q[1];
    m[1][1]=q[0];
    m[1][2]=q[3];
    m[1][3]=(-1)*q[2];
    m[2][0]=q[2];
    m[2][1]=(-1)*q[3];
    m[2][2]=q[0];
    m[2][3]=q[1];
    m[3][0]=q[3];
    m[3][1]=q[2];
    m[3][2]=(-1)*q[1];
    m[3][3]=q[0];

    return m;
}

//q* == q^(-1) 
float** generate_matrix_qsL(float* q){
    float **m=(float**)malloc(sizeof(float*)*4);
    for(int i=0;i<4;i++){
        m[i]=(float*)malloc(sizeof(float)*4);
    }

    m[0][0]=q[0];
    m[0][1]=(-1)*q[1];
    m[0][2]=(-1)*q[2];
    m[0][3]=(-1)*q[3];
    m[1][0]=q[1];
    m[1][1]=q[0];
    m[1][2]=(-1)*q[3];
    m[1][3]=q[2];
    m[2][0]=q[2];
    m[2][1]=q[3];
    m[2][2]=q[0];
    m[2][3]=(-1)*q[1];
    m[3][0]=q[3];
    m[3][1]=(-1)*q[2];
    m[3][2]=q[1];
    m[3][3]=q[0];

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i!=j){
                m[i][j]=(-1)*m[i][j];
            }
        }
    }

    return m;
}

float** generate_matrix_qsR(float* q){
    float **m=(float**)malloc(sizeof(float*)*4);
    for(int i=0;i<4;i++){
        m[i]=(float*)malloc(sizeof(float)*4);
    }

    m[0][0]=q[0];
    m[0][1]=(-1)*q[1];
    m[0][2]=(-1)*q[2];
    m[0][3]=(-1)*q[3];
    m[1][0]=q[1];
    m[1][1]=q[0];
    m[1][2]=q[3];
    m[1][3]=(-1)*q[2];
    m[2][0]=q[2];
    m[2][1]=(-1)*q[3];
    m[2][2]=q[0];
    m[2][3]=q[1];
    m[3][0]=q[3];
    m[3][1]=q[2];
    m[3][2]=(-1)*q[1];
    m[3][3]=q[0];

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i!=j){
                m[i][j]=(-1)*m[i][j];
            }
        }
    }

    return m;
}


float** multiply_4x4(float**a,float**b){
    float **m=(float**)malloc(sizeof(float*)*4);
    for(int i=0;i<4;i++){
        m[i]=(float*)malloc(sizeof(float)*4);
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            m[i][j]=0;
            for(int k=0;k<4;k++){
                m[i][j]+=a[i][k]*b[k][j];
            }
        }
    }

    return m;
}

float* multiply_4x1(float**a,float*b){
    float *m=(float*)malloc(sizeof(float)*4);
    for(int i=0;i<4;i++){
        m[i]=0;
        for(int k=0;k<4;k++){
            m[i]+=b[k]*a[i][k];
        }
    }
    return m;
}

float* multiply_1x4(float*a,float**b){
    float *m=(float*)malloc(sizeof(float)*4);
    for(int i=0;i<4;i++){
        m[i]=0;
        for(int k=0;k<4;k++){
            m[i]+=a[k]*b[k][i];
        }
    }

    return m;
}

//返回参数的共轭矩阵（即逆矩阵）
float** qS(float** q){
    float **m=(float**)malloc(sizeof(float*)*4);
    for(int i=0;i<4;i++){
        m[i]=(float*)malloc(sizeof(float)*4);
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i!=j){
                m[i][j]=(-1)*q[i][j];
            }else{
                m[i][j]=q[i][j];
            }
        }
    }

    return m;
}

float* one_Rotation(float*d,float*u){
    float* q=generate_quaternion(u);
    float** qL=generate_matrix_qL(q);
    float** qR=generate_matrix_qR(q);
    float** qsL=generate_matrix_qsL(q);
    float** qsR=generate_matrix_qsR(q);
    float* r=multiply_4x1(multiply_4x4(qL,qsR),d);
    free(q);
    free(qL);
    free(qR);
    free(qsL);
    free(qsR);

    return r;
}

float* two_Rotation(float*d,float*u1,float*u2){

    float*t=one_Rotation(d,u1);
    float*r=one_Rotation(t,u2);
    free(t);

    return r;
}



/*

q=q[0]+q[1]i+q[2]j+q[3]k

u[0]    angle
u[1]    u_x
u[2]    u_y
u[3]    u_z

*/



int main(){

    float dian[4]={0,2,0,0};
    float u[4]={3.1415926/4,0,0,1};
    float u2[4]={3.1415926/4,0,1,0};

    float*r=two_Rotation(dian,u,u2);
    printf("%f   %f   %f   %f",r[0],r[1],r[2],r[3]);


    return 0;

}