#include<stdio.h>
#include<wiringPi.h>
#include<string.h>


int makerobo_LCDAddr = 0x27; //LCD 1602液晶IIC地址
int makerobo_BLEN = 1; //写入标志位
int makerobo_fd;

//IIC LCD1602 液晶模块写入字
void makerobo_write_word(int data){
    int temp = data;
    if( makerobo_BLEN ==1 )
        temp |= 0x08;
    else
        temp &= 0xF7;
    wiringPiI2CWrite(makerobo_fd,temp); //设置液晶模块地址
}

// LCD1602 发送命令
void makerobo_send_command(int comm){
    int lcd_buf;
    //首先发送bit 7-4位
    lcd_buf = comm & 0xF0;
    lcd_buf |= 0x04;
    makerobo_write_word(lcd_buf);
    delay(2);
    lcd_buf &= 0xFB;
    makerobo_write_word(lcd_buf);
    //其次发送bit 3-0位
    lcd_buf = (comm & 0x0F) << 4;
    lcd_buf |= 0x04;
    makerobo_write_word(lcd_buf);
    delay(2);
    lcd_buf &= 0xFB;
    makerobo_write_word(lcd_buf);
}

//发送数据
void makerobo_send_data(int data){
    int lcd_buf;
    lcd_buf = data & 0xF0;
    lcd_buf |= 0x05;
    makerobo_write_word(lcd_buf);
    delay(2);
    lcd_buf &= 0xFB;
    makerobo_write_word(lcd_buf);

    lcd_buf = (data & 0x0F) << 4;
    lcd_buf |= 0x05;
    makerobo_write_word(lcd_buf);
    delay(2);
    lcd_buf &= 0xFB;
    makerobo_write_word(lcd_buf);
}

void makerobo_init(){
    makerobo_send_command(0x33);
    delay(5);
    makerobo_send_command(0x32);
    delay(5);
    makerobo_send_command(0x28);
    delay(5);
    makerobo_send_command(0x0C);
    delay(5);
    makerobo_send_command(0x01);
    wiringPiI2CWrite(makerobo_fd,0x08);
}

void makerobo_clear(){
    makerobo_send_command(0x01);
}

void makerobo_write(int lcd_x,int lcd_y,char data[]){
    int lcd_addr,lcd_i;
    int lcd_tmp;
    if( lcd_x < 0) lcd_x = 0;
    if( lcd_x > 15) lcd_x = 15;
    if( lcd_y < 0 ) lcd_y = 0;
    if( lcd_y > 1 ) lcd_y = 1;

    //移动光标
    lcd_addr = 0x80 + 0x40 * lcd_y + lcd_x;
    makerobo_send_command(lcd_addr);
    lcd_tmp = strlen(data);

    for( lcd_i=0; lcd_i < lcd_tmp;lcd_i++){
        makerobo_send_data(data[lcd_i]);
    }
}

void test_lcd_main(){
    makerobo_fd = wiringPiI2CSetup(makerobo_LCDAddr);

    makerobo_init();
    while (1)
    {
        makerobo_write(0,0,"HELLO linlin");
        makerobo_write(0,1,"HELLO huahua");
        delay(2000);
        makerobo_clear();

    }
    return 0;
}

void lcd_show_temp_init(){
    makerobo_fd = wiringPiI2CSetup(makerobo_LCDAddr);
    makerobo_init();
}

void lcd_show_temp(float temp){
    char str_temp[16];
    sprintf(str_temp,"%.3f",temp);
    makerobo_write(0, 0, str_temp);
    delay(500);
}
