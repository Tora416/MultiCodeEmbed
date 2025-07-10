




#include "../lcd_header.h"
void i2c_init(void);
void i2c_Start(void);
void i2c_tx_data(char );
void i2c_stop(void);

int main()
{   
    lcd_config();
    i2c_init();
    i2c_Start();
    i2c_tx_data(0xA0);          
    i2c_tx_data(0x01);          
    i2c_tx_data('C');   
    i2c_tx_data('R');   
    i2c_tx_data('A');   
    i2c_tx_data('N');
    i2c_tx_data('E');   
    i2c_tx_data('S');       
    i2c_stop();

    lcd_str("Data sent");
}

void i2c_init(void)
{
    PINSEL0 |= (1<<4)|(1<<6);
    PINSEL0 &= ~((1<<5)|(1<<7));        
    I2CONSET = 1<<6;                                
    I2SCLH = 75;                                        
    I2SCLL = 75;
}

void i2c_Start(void)
{
    I2CONCLR = (1<<3);      
    I2CONSET = (1<<5);          
    while(!(I2CONSET &(1<<3)));
    I2CONCLR = (1<<5);          
    I2CONCLR = (1<<3);          
}

void i2c_tx_data(char idata)
{
    I2DAT = idata;
    while(!(I2CONSET &(1<<3)));
    I2CONCLR = (1<<3);          
}

void i2c_stop(void)
{
    I2CONSET = (1<<4);
}
