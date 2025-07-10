#include "lcd_header.h"

void lcd_config(void)
{
    IODIR0 = IODIR0 | RS | RW | EN | DATA; 
    
    lcd_cmd(0x38);  
    lcd_cmd(0x0E);  
    lcd_cmd(0x01);  
    lcd_cmd(0x80);  
}

void lcd_cmd(char c)
{
    
    
    
    IOCLR0 = DATA;    
    IOSET0 = c<<15;
    IOCLR0 = RW;    
    IOCLR0 = RS;    
    IOSET0 = EN;
    delay(100);
    IOCLR0 = EN;    
}

void lcd_data(char d)
{
    IOCLR0 = DATA;
    IOSET0 = d <<15;
    IOCLR0 = RW;
    IOSET0 = RS;
    IOSET0 = EN;
    delay(100);
    IOCLR0 = EN;
}

void lcd_str(char str[])
{
    for(int i=0;str[i]!='\0';i++)
    {
        lcd_data(str[i]);
    }





}

void lcd_num(int num)
{
    if(num)
    {
        lcd_num(num/10);
        lcd_data(num%10 + 0x30);
    }
}

void delay(int ct)
{
    for(int i =0 ;i<ct; i++)
    {
        for(int j=0;j<6000;++j)
        {
        }
    }
}
