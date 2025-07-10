



#include<lpc21xx.h>

void delay(int);

int main()
{
    int flag = 0;
    IODIR0 = IODIR0 | (1<<11);      
    IODIR1 = IODIR1 & ~(1<<25);     
    while(1)
    {
        if(IOPIN1 & (1<<25))  
        {
            IOSET0 = 1<<11;
            delay(100);
            IOCLR0 = 1<<11;
            delay(100);         
        }
    }
}

void delay(int ct)
{
    for(int i=0;i<ct;++i)
    {
        for(int j=0;j<6000;j++)
        {}
    }
}





