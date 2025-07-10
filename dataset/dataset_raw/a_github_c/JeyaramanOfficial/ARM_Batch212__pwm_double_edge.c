



                                            
#include<LPC21xx.h>
void delay_ms(int);
int main()
{

    PINSEL0 |= (1<<17);
    PINSEL0 &= ~(1<<16);                
    PWMPR = 14;
    PWMMR0 = 10000;                         
    PWMLER = (1<<0);
    PWMMCR = (1<<1);                        
    PWMPCR |= (1<<12)|(1<<4);                   
    PWMTCR = (1<<0) | (1<<3);       
    while(1)
    {
            PWMMR3 = 3000;          
            PWMMR4 = 5500;          
            PWMLER = (1<<3)|(1<<4);
            delay_ms(1000);
            PWMMR3 = 3000;          
            PWMMR4 = 7000;          
            PWMLER = (1<<3)|(1<<4);
            delay_ms(1000);
    }   
}

void delay_ms(int ct)
{
    int i,j;
    for(i=0;i<ct;++i)
    {
        for(j=0;j<6000;++j)
        {}
    }
}
