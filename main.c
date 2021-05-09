#include <stdio.h>
#include "dule_color_led.h"
#include "ultrasonic_ranging.h"


#define LCD_TEST 1

int main(){
    if(wiringPiSetup() == -1){
        printf("setup wiringPi failed");
        return 1;
    }
#ifdef LED_TEST
    test_led_main();
#endif

#ifdef RANGING_TEST
    test_ranging_main();
#endif

#ifdef LCD_TEST
    test_lcd_main();
#endif
    return 0;
}
