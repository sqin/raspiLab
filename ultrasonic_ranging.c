#include <sys/time.h>
#include <wiringPi.h>

#define NULL 0
#define makerobo_Trig 0
#define makerobo_Echo 1

//超声波模块初始化工作
void makerobo_ultraInit(){
    pinMode(makerobo_Trig,OUTPUT);
    pinMode(makerobo_Echo,INPUT);
}

float ur_disMeasure(){
    struct timeval ur_tv1;
    struct timeval ur_tv2;
    long ur_time1,ur_time2;
    float ur_dis;
    digitalWrite(makerobo_Trig,LOW);
    delayMicroseconds(2); //2us
    digitalWrite(makerobo_Trig,HIGH);
    delayMicroseconds(10); //10us
    digitalWrite(makerobo_Trig,LOW);
    
    while(! (digitalRead(makerobo_Echo) == 1));
    gettimeofday(&ur_tv1,NULL);
    while(! (digitalRead(makerobo_Echo) == 0));
    gettimeofday(&ur_tv2,NULL);
    ur_time1 = ur_tv1.tv_sec*1000000 + ur_tv1.tv_usec;
    ur_time2 = ur_tv2.tv_sec*1000000 + ur_tv2.tv_usec;

    ur_dis = (float)(ur_time2 - ur_time1)/1000000 * 34000 /2;
    return ur_dis;
}

void test_ranging_main(){
    float ur_dis;
    makerobo_ultraInit();
    while (1)
    {
        ur_dis = ur_disMeasure();
        printf("%0.2f cm\n\n",ur_dis);
        delay(300);
    }
}
