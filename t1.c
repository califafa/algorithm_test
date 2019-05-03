#include<stdio.h>

int main(){

	int a=-0x1f;
	
	char b=a;

//	a|=0x80000000;

	b=-126;
	b>>=1;

	printf("%d",(int)b);

	return 0;
}
