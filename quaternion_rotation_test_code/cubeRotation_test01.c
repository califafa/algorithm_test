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

/******************************************************************************
  * 函数名称：Q_rsqrt
  * 函数描述：快速计算 1 / Sqrt(x) 
  * 输    入：float number:要计算的数据
  * 输    出：void
  * 返    回：1 / Sqrt(x) 
  * 备    注：null
  *    
  *
******************************************************************************/
float Q_rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;
 
    x2 = number * 0.5F;
    y  = number;
    i  = *(long*) &y;                      
    i  = 0x5f3759df - ( i >> 1 );               
    y  = *(float*) &i;
    y  = y * (threehalfs - (x2 * y * y ));   // 1st iteration （第一次牛顿迭代）
    return y;
}

float* toOne(float*u){
    float quaSum=u[1]*u[1]+u[2]*u[2]+u[3]*u[3];
    float rsqrt=Q_rsqrt(quaSum);
    u[1]=u[1]*rsqrt;
    u[2]=u[2]*rsqrt;
    u[3]=u[3]*rsqrt;
    
    return u;
}


int route[12][2]={{0,1},{0,2},{1,3},{2,3},{1,5},{3,7},{2,6},{0,4},{5,7},{4,5},{4,6},{6,7}}; //正方体的12条边对应的顶点


float** cube_generate(float width){
    float originCube[8][3]={{-1,-1,-1},{-1,-1,1},{-1,1,-1},{-1,1,1},{1,-1,-1},{1,-1,1},{1,1,-1},{1,1,1}};
    //route [0,1],[0,2],[1,3],[2,3],[1,5],[3,7],[2,6],[0,4],[5,7],[4,5],[4,6],[6,7]
    //float route[12][2]={{0,1},{0,2},{1,3},{2,3},{1,5},{3,7},{2,6},{0,4},{5,7},{4,5},{4,6},{6,7}};
    float**cube=(float**)malloc(sizeof(float*)*8);
    for(int i=0;i<8;i++){
        cube[i]=(float*)malloc(sizeof(float)*3);
    }
    for(int i=0;i<8;i++){
        for(int j=0;j<3;j++){
            cube[i][j]=originCube[i][j]*width;
        }
    }

    return cube;

}


float** cube_Rotation(float**cube,float*u){
    for(int i=0;i<8;i++){
        float* ncube=one_Rotation(cube[i],u);
        for(int j=0;j<3;j++){
            cube[i][j]=ncube[j];
        }
    }

    return cube;
}


void print_line(float**cube){
    for(int i=0;i<12;i++){
        float tmp[3]={0,0,0};//{cube[route[i][0]][0],cube[route[i][0]][1],cube[route[i][0]][2]};
        float addtmp[3]={cube[route[i][0]][0],cube[route[i][0]][1],cube[route[i][0]][2]};
        tmp[0]=cube[route[i][1]][0]-cube[route[i][0]][0];
        tmp[1]=cube[route[i][1]][1]-cube[route[i][0]][1];
        tmp[2]=cube[route[i][1]][2]-cube[route[i][0]][2];
        for(int j=0;j<100;j++){
            addtmp[0]+=tmp[0]/100;
            addtmp[1]+=tmp[1]/100;
            addtmp[2]+=tmp[2]/100;

            printf("[%f,%f,%f],",addtmp[0],addtmp[1],addtmp[2]);
        }


        printf("\n\n\n\n\n\n\n\n\n");
    }
}

float eyes_location[3]={10,0,0};    //眼睛在距离原点10的x轴上
float retina_dis=1;                 //视网膜距离眼睛1

float** onRetina(float**cube){
    float**cubeOnRetina=(float**)malloc(sizeof(float*)*8);
    for(int i=0;i<8;i++){
        cubeOnRetina[i]=(float*)malloc(sizeof(float)*3);
    }
    
    for(int i=0;i<8;i++){
        float tmp[3]={eyes_location[0]-cube[i][0],eyes_location[1]-cube[i][1],eyes_location[2]-cube[i][2]};
        float addtmp[3]={eyes_location[0],eyes_location[1],eyes_location[2]};
        while(1){
            addtmp[0]+=0.01*tmp[0];
            addtmp[1]+=0.01*tmp[1];
            addtmp[2]+=0.01*tmp[2];
            if(addtmp[0]>(eyes_location[0]+retina_dis)){
                cubeOnRetina[i][0]=addtmp[0];
                cubeOnRetina[i][1]=addtmp[1];
                cubeOnRetina[i][2]=addtmp[2];
            //printf("[%f,%f,%f],",addtmp[0],addtmp[1],addtmp[2]);
                break;
            }
        }

        //printf("\n\n\n\n");
    }
    return cubeOnRetina;
}

int main(){


    float U[4]={3.1415926/2,1,1,2};
    float*u=toOne(U);
    float**cube=cube_generate(2);

    for(int i=0;i<8;i++){
        printf("%d      %f  %f  %f \n ",i,cube[i][0],cube[i][1],cube[i][2]);
    }

    cube=cube_Rotation(cube,u);
    cube=onRetina(cube);
    printf("\n\n");

    for(int i=0;i<8;i++){
        printf("%d      %f  %f  %f \n ",i,cube[i][0],cube[i][1],cube[i][2]);
    }

    print_line(cube);
    return 0;
}