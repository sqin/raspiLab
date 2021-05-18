#include <stdio.h>
#include "dule_color_led.h"
#include "ultrasonic_ranging.h"
#include "lcd1602.h"
#include "temperature.h"

// #define LCD_TEST 1
#define TEMP_TEST 1

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

#ifdef TEMP_TEST
    lcd_show_temp_init();
while(1){
    float temp = getTemp();
    // test_temperature_main();
    lcd_show_temp(temp);
}
#endif

    return 0;
}
