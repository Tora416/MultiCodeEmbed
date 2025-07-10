

#include<lpc21xx.h>

void spi_data(int);

int main()
{
    PINSEL0 |= (1<<8)|(1<<10)|(1<<12);  
    PINSEL0 &= ~((1<<9)|(1<<11)|(1<<13));
    IODIR0 |= (1<<7);       
    
    S0SPCR = (1<<2)|(1<<3)|(1<<4)|(1<<5);       
    S0SPCCR = 8;        
    spi_data(0x0C01);               
    spi_data(0x090F);               
    spi_data(0x0AFF);               
    spi_data(0x0B03);               
    
    spi_data(0x010C);               
    spi_data(0x020B);       
    spi_data(0x030D);       
    spi_data(0x040E);       
}

void spi_data(int data)
{
    IOCLR0  =   (1<<7);         
    S0SPDR = data;              
    while(!(S0SPSR & (1<<7)));
    IOSET0 = (1<<7);            
}

