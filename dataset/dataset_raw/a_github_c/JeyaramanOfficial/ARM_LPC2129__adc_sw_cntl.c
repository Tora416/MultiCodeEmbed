#include "lcd_header.h"


int main()
{
    int res,done = 1;
    


    PINSEL1 |= 1<<24;
    PINSEL1 &= ~(1<<25); 
    lcd_config();

    ADCR = (1<<1)|(4<<8)|(1<<21)|(1<<24);  
    while(1)
    {
        
        
        while(!(ADDR & (done<<31)));
        res = ADDR & (0x3FF<<6);   
        res = res>>6;                               
        res = res/3.3;  
        lcd_num(res);
        delay(1000);

        
    }
}

void adc_pot(void)
{
    int res,done = 1;
    ADCR = (1<<0)|(4<<8)|(1<<21)|(1<<24); 
    while(!(ADDR & (done<<31)));
    res = ADDR & (0x3FF<<6);   
    res = res>>6;       
}

void adc_temp(void)
{
    int res,done = 1;
    ADCR = (1<<1)|(4<<8)|(1<<21)|(1<<24); 
    while(!(ADDR & (done<<31)));
    res = ADDR & (0x3FF<<6);   
    res = res>>6;       
}