#include<stdio.h>
#include<math.h>

#define log2N 6

#define len 64

#define Pi 3.1415926

typedef struct{
    double real;
    double img;
}C;

C input[len];

C output[len];


C add(C a, C b){
    C c;
    c.real=a.real+b.real;
    c.img=a.img+b.img;
    return c;
}

C sub(C a,C b){
    C c;
    c.real=a.real-b.real;
    c.img=a.img-b.img;
    return c;
}

C mul(C a,C b){
    C c;
    c.real=a.real*b.real-a.img*b.img;
    c.img=a.real*b.img+a.img*b.real;
    return c;
}

void Reverse(){
    for(unsigned int i=0;i<len;i++){
        unsigned int I=i;
        unsigned int R=0;
        for(unsigned char bit=0;bit<log2N;bit++){
            R<<=1;
            R|=(I&1);
            I>>=1;
        }
        if(R>i){
            C tmp=input[R];
            input[R]=input[i];
            input[i]=tmp;
        }
    }
}

void ButterflyAlgorithm(){
    for(unsigned int i=1;i<=len;i<<=1){
        for(unsigned int j=0;j<(len/(2*i));j++){
            for(unsigned int k=0;k<i;k++){
                double tmpCos=cos((Pi/i)*k);
                double tmpSin=-1*sin((Pi/i)*k);
                C tmpWn;
                tmpWn.real=tmpCos;
                tmpWn.img=tmpSin;

                C tmpXw=mul(input[j*2*i+k+i],tmpWn);

                C tmpTop=add(input[j*2*i+k],tmpXw);

                C tmpBottom=sub(input[j*2*i+k],tmpXw);

                input[j*2*i+k]=tmpTop;
                input[j*2*i+k+i]=tmpBottom;

            }
        }
    }
}

void fft(){
    Reverse();
    ButterflyAlgorithm();
    for(unsigned int i=0;i<len;i++){
        output[i].real=sqrt(input[i].real*input[i].real+input[i].img*input[i].img);
    }
}


int main(){

    double freq=2;

    for(int i=0;i<len;i++){
        input[i].real=sin(i*freq);
    }

    fft();

    for(int i=0;i<len;i++){
        
        for(int lo=0;lo<output[i].real;lo++){
            printf("x");
        }
        printf("\n");
    }

    return 0;
}