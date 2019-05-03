#include<stdio.h>
#include<math.h>

#define log2N 5
#define len 32

#define Pi 3.141592653589793

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

void Reverse(){                                                                                       //翻转运算
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

void ButterflyAlgorithm(){                                                                             //蝶形运算，有log2N级，每级有len/(2*i)组，每组有2*i个。
    for(unsigned int i=1;i<=len;i<<=1){                                                                //有log2N级
        for(unsigned int j=0;j<(len/(2*i));j++){                                                       //每级有len/(2*i)组
            for(unsigned int k=0;k<i;k++){                                                             //每组有2*i个，每组分为2部分。第一部分为前i个，第二部分为后i个。
                double tmpReal=cos((Pi/i)*k);
                double tmpImg=-1*sin((Pi/i)*k);
                C tmpWn;                                                                               //旋转子。在每组里面，实部为0-Pi的cos，虚部为0-Pi的-1*sin，将0-Pi分为i个点。
                tmpWn.real=tmpReal;
                tmpWn.img=tmpImg;

                C tmpXw=mul(input[j*2*i+k+i],tmpWn);

                C tmpTop=add(input[j*2*i+k],tmpXw);

                C tmpBottom=sub(input[j*2*i+k],tmpXw);

                input[j*2*i+k]=tmpTop;
                input[j*2*i+k+i]=tmpBottom;

            }
        }
    }
}

void fft(){                                                                                            //快速傅里叶变换
    Reverse();
    ButterflyAlgorithm();
    for(unsigned int i=0;i<len;i++){
        output[i].real=(input[i].real*input[i].real+input[i].img*input[i].img);
    }
}

// 在len个点中，如果包含x个正弦周期，就是output[x]为峰值。
int main(){

    double freq=56 *2*Pi/len;

    for(int i=0;i<len;i++){
        input[i].real=cos(i*freq)+0.1;
    }

    fft();


    //横着显示频谱
    double tmpMax=0;
    printf("\n\n");
    for(int i=0;i<len;i++){
        if(tmpMax<output[i].real){
            tmpMax=output[i].real;
        }
    }
    for(int i=tmpMax;i>0;i--){
        for(int j=0;j<len;j++){
            if(output[j].real>i){
                printf("H");
            }else{
                printf(" ");
            }
            if(j==(len/2-1)){
                printf(" | ");
            }
        }
        printf("\n");
    }
    for(int i=0;i<len;i++){
        printf("%d",i%10);
        if(i==(len/2-1)){
            printf(" | ");
        }
    }

    printf("\n\n\t%f",tmpMax);


    //竖着显示频谱
    /*
    for(int i=0;i<len;i++){
        
        for(int lo=0;lo<output[i].real;lo++){
            printf("-");
        }
        if(i==(len/2-1)){
            printf("\n\n----------------------------------------------------------------------\n");
        }
        printf("\n");
    }
    */


    return 0;
}
