



#include<lpc21xx.h>
#define RS (1<<10)
#define RW (1<<12)
#define EN (1<<13)
#define DATA_PINS (0xFF<<15)

void lcd_config(void);
void lcd_cmd(char);
void lcd_data(char);
void lcd_str(char []);
void lcd_str1(char []);
void delay(int);

int main()
{



        int num = 8,res,quotient,remainder;     
        res = 66 + 33;
        lcd_config();   
        quotient = res/10;
        remainder = res%10;
        lcd_data(quotient + 0x30);
        lcd_data(remainder + 0x30);
    







}

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








