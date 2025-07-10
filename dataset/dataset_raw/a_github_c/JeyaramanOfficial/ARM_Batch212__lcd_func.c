
#include "lcd_header.h"

void lcd_config(void)
{
    IODIR0 |= DATA_PINS|RS|RW|EN;       
                        
                        
    lcd_cmd(0x38);  
    lcd_cmd(0x0E);  
    lcd_cmd(0x01);  
    lcd_cmd(0x80);  
}

void lcd_cmd(char cmd)
{
    IOCLR0 = DATA_PINS;     
    IOSET0 = cmd<<15;  
    IOCLR0 = RW;                
    IOCLR0 = RS;        
    IOSET0 = EN;
    delay(100);
    IOCLR0 = EN;
}

void lcd_data(char data)
{
    IOCLR0 = DATA_PINS;     
    IOSET0 = data<<15;  
    IOCLR0 = RW;                
    IOSET0 = RS;            
    IOSET0 = EN;
    delay(100);
    IOCLR0 = EN;
}

void delay(int ct)
{
    int i,j;
    for(i=0;i<ct;++i)
    {
        for(j=0;j<6000;++j)             
        {}
    }
}


void lcd_str(char str[])
{
    int i;
    for(i=0;str[i]!='\0';++i)
        {
            lcd_data(str[i]);
        }
}

void lcd_str1(char str[])
{
    int i,count=0;
    for(i=0;str[i]!='\0';++i)
        {
            lcd_data(str[i]);
            if(count == 16)
            {
                lcd_cmd(0xC0);
            }
            count++;
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






