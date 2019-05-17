#include<stdio.h>

float readValue(){
    return 2;
}


//kalmanFilter

float x_last=0;
float p_last=0.02;
float Q=0.018;
float R=0.542;
float kg;
float x_mid;
float x_now;
float p_mid;
float p_now;
float z_measure;

void kalmanInit(){
    z_measure=readValue();
    x_last=z_measure;
    x_mid=x_last;
}

float kalmanRealize(){
    x_mid=x_last;
    p_mid=p_last+Q;
    kg=p_mid/(p_mid+R);
    z_measure=(float)readValue();
    x_now=x_mid+kg*(z_measure-x_mid);
    p_now=(1-kg)*p_mid;

    p_last=p_now;
    x_last=x_now;

    return x_now;
}


int main(){

    float value=2;// value from sensor
    kalmanInit();
    for(int i=0;i<99;i++){
        value=kalmanRealize();
        printf("%f   ",value);
    }
}