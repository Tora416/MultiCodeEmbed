








#include<lpc21xx.h>
void delay(int );
void blink_LED(int );

int main()
{
    IODIR1 = IODIR1 | (0xFF<<17);       
    T0PR = 14;                  
    T0MR0 = 5000000;        
    T0MCR   = (1<<0)|(1<<1);            
    T0TCR   = (1<<0);           
    while(1)
    {
        blink_LED(24);

        while(!(T0IR & (1<<0)))         
        {}
        blink_LED(17);
        T0IR = 1<<0;            

    }
}

void blink_LED(int led)
{
    IOSET1 = 1<<led;
    delay(300);             
    IOCLR1 = 1<<led;
    delay(300);             
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
