#include<stdio.h>

int main(){

    float p=0.1;                                        // pid 比例系数
    float i=0.1;                                        // pid 积分系数
    float k=-0.1;                                       // pid 微分系数

    float err=0;                                        // 当前误差
    float errLast=0;                                    // 前一次的误差
    float errSum=0;                                     // 误差的和（积分）

    float purpose=1000;                                 // 目标值

    float actual=0;                                     // 当前的实际值

    float power=0;                                      // 调节功率的值

    for(int loo=0;loo<2048;loo++){                      //pid算法循环
        errLast=err;                                    // 更新errLast
        err=purpose-actual;                             // 获取当前的误差
        errSum+=err;                                    // 误差积分
        power=p*err+i*errSum+k*(err-errLast);           // pid算法 计算功率
        actual+=power*2-222;                             // 当前值和功率的关系，本行代码仅作现实情况的模拟。在实际情况中，actual应该由传感器得到。
    }

    printf("\n目标值 : %f\n",purpose);
    printf("\n最后的actual值 : %f\n\n",actual);

    return 0;
}