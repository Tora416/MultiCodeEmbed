


#include "../lcd_header.h"

void i2c_config(void);
void i2c_start(void);
void i2c_data(char );
void i2c_stop(void);


int main()
{
    lcd_config();
    i2c_config();
    
    i2c_start();
    i2c_data(0xA0);     
    i2c_data(0x00);     
    i2c_data('A');
    i2c_data('B');
    i2c_data('C');
    i2c_stop();
    
}

void i2c_config(void)
{
    PINSEL0 |= (1<<4)|(1<<6);           
    PINSEL0 &= ~((1<<5)|(1<<7));
    
    I2CONSET    = 1<<6;     
    I2SCLH = 75;                
    I2SCLL = 75;
}

void i2c_start(void)
{
    I2CONCLR = 1<<3;
    I2CONSET = 1<<5;        
    while(!(I2CONSET & (1<<3)));    
    I2CONCLR = 1<<3;        
    I2CONCLR = 1<<5;        
}

void i2c_data(char data)
{
    I2DAT = data;
    while(!(I2CONSET & (1<<3)));    
    I2CONCLR = 1<<3;
}

void i2c_stop(void)
{
    I2CONSET = 1<<4;    
}



