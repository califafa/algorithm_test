#include<stdio.h>
#include<math.h>

typedef struct{
	float x_init;
	float y_init;
	float step;
	unsigned int times;
}RK_DATA;


//微分方程，目标(模拟的)方程的导数,对此方程积分，得到目标值。实际工程中，此值的获取需要通过传感器获得（不然可以直接获得积分的表达式了）。
float derivatives_func(float x,float y){
	return 3*x*x+4;//假设
}

//目标方程
float real_func(float x, float y){
	return x*x*x+4*x;//假设
}

//积分范围：(x_init:x_init+step*times)
float RF4(RK_DATA RK4){

	for(unsigned int i=0;i<RK4.times;i++){
		float k1=derivatives_func(RK4.x_init,RK4.y_init);
		float k2=derivatives_func(RK4.x_init+RK4.step/2,RK4.y_init+RK4.step*k1/2);
		float k3=derivatives_func(RK4.x_init+RK4.step/2,RK4.y_init+RK4.step*k2/2);
		float k4=derivatives_func(RK4.x_init+RK4.step,RK4.y_init+RK4.step*k3);
		float y_end=RK4.y_init+RK4.step*(k1+2*k2+2*k3+k4)/6;
		float x_end=RK4.x_init+RK4.step;
		RK4.x_init=x_end;
		RK4.y_init=y_end;
	}
	return RK4.y_init;
}


float Runge_Kuatta(RK_DATA RK4, float x_init, float y_init, float step, float times){
	RK4.x_init=x_init;
	RK4.y_init=y_init;
	RK4.step=step;
	RK4.times=times;
	return RF4(RK4);
}


//test code
int main(){

	RK_DATA rk4;

	float x_init=3;
	float y_init=10;
	float step=1;
	float times=99;

	float a=Runge_Kuatta(rk4,x_init,y_init,step,times);
	float b=real_func(x_init+step*times,y_init)-real_func(x_init,y_init)+y_init;

	printf("Runge_Kuatta: %f  ,  real_Value: %f",a,b);

}
