



#include<lpc21xx.h>

void delay(int);

int main()
{
    int flag = 0;
    IODIR1 |= (0xFF<<17);       
    IODIR1 = IODIR1 & ~(1<<25);     
    while(1)
    {
        if(IOPIN1 & (1<<25))  
        {
            if(flag == 0)               
            {
                IOSET1 = 1<<17;
                delay(500);
                flag = 1;
            }
            else if(flag ==1)       
            {
                IOCLR1 = 1<<17;
                delay(500);
                flag = 0;
            }
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





