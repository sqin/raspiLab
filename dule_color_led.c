#include "dule_color_led.h"
#include <wiringPi.h>
#include <softPwm.h>

#define makerobo_Led_PinRed     0
#define makerobo_Led_PinGreen   1

void makerobo_led_init(){
    softPwmCreate(makerobo_Led_PinRed,0,100);
    softPwmCreate(makerobo_Led_PinGreen,0,100);
}


void makerobo_led_colorSet(uchar r_val,uchar g_val){
    softPwmWrite(makerobo_Led_PinRed,r_val);
    softPwmWrite(makerobo_Led_PinGreen,g_val);
}

void test_led_main()
{
    makerobo_led_init();
    while (1)
    {
        makerobo_led_colorSet(0xff, 0x00);
        delay(500);
        //green led
        makerobo_led_colorSet(0x00, 0xff);
        delay(500);
        makerobo_led_colorSet(0xff, 0x45);
        delay(500);
        makerobo_led_colorSet(0xff, 0xff);
        delay(500);
        makerobo_led_colorSet(0x7c, 0xfc);
        delay(500);
    }
}