#include<lpc21xx.h>

void delay(int);
int main()
{
    PINSEL0 |= (1<<17);
    PINSEL0 &= ~(1<<16);  
    

    
    PWMPR = 14;
    PWMMR0 = 10000;
    PWMLER = 1<<0;
    PWMMCR = (1<<1);   
    PWMPCR = (1<<4)|(1<<12);  
    PWMTCR = (1<<0)|(1<<3);  
    
        while(1)
        {
            PWMMR3 = 1000;   
            PWMMR4 = 3500;
            PWMLER = (1<<3)|(1<<4);
            delay(500);
            
            PWMMR3 = 1000;  
            PWMMR4 = 6000;
            PWMLER = (1<<3)|(1<<4);
            delay(500);
            
            PWMMR3 = 1000;  
            PWMMR4 = 8500;
            PWMLER = (1<<3)|(1<<4);
            delay(500);
        
    }
}

void delay(int ct)
{
    for(int i=0;i<ct;i++)
    {
        for(int j=0;j<6000;j++)
        {
        }
    }
}
