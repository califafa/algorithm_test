#include<stdio.h>

struct _pid{
	float SetSpeed;
	float ActualSpeed;
	float err;
	float err_last;
	float Kp, Ki, Kd;
	float voltage;
	float integral;
}pid;

float PID_realize(float speed){
	pid.SetSpeed=speed;
	pid.err=pid.SetSpeed-pid.ActualSpeed;
	pid.integral+=pid.err;
	pid.voltage=pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);	//此处的意思是指代 动力
	pid.err_last=pid.err;
	pid.ActualSpeed=(pid.voltage)/3-100;                                      //速度和动力的关系（本行代码为模拟用途，实际情况比这个复杂，并且在实际使用中用不到），实际情况可以不用考虑。
	return pid.ActualSpeed;
}

void PID_init(){
	printf("pid_value_init begin\n");
	pid.SetSpeed=0;
	pid.ActualSpeed=0;
	pid.err=0;
	pid.err_last=0;
	pid.voltage=0;
	pid.integral=0;
	pid.Kp=0.2;
	pid.Ki=0.3;
	pid.Kd=-0.2;
	printf("pid_init completed\n");
}

int main(){
	int count=0;
	printf("Begin\n");
	PID_init();
	while(count<128){
		float speed=PID_realize(1000);
//		pid.ActualSpeed-=100;
		printf("value is %f\n",speed);

		count++;
	}
	return 0;
}

