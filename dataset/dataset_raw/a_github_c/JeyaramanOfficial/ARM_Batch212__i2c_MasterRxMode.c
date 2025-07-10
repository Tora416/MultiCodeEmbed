




#include "../lcd_header.h"
void i2c_init(void);
void i2c_Start(void);
void i2c_tx_data(char );
char i2c_rx_data(void);
void i2c_stop(void);

int main()
{   
    char i2c_rdata;
    lcd_config();
    i2c_init();
    
    i2c_Start();
    i2c_tx_data(0xA0);          
    i2c_tx_data(0x01);          
    
    I2CONSET = (1<<2);          
    
    i2c_Start();                        
    i2c_tx_data(0xA1);          
    
    i2c_rdata = i2c_rx_data();
    lcd_data(i2c_rdata);        
    i2c_rdata = i2c_rx_data();
    lcd_data(i2c_rdata);        
    i2c_rdata = i2c_rx_data();
    lcd_data(i2c_rdata);        
    i2c_rdata = i2c_rx_data();
    lcd_data(i2c_rdata);        
    i2c_rdata = i2c_rx_data();
    lcd_data(i2c_rdata);        
    i2c_rdata = i2c_rx_data();
    lcd_data(i2c_rdata);        
    
    i2c_stop();

    lcd_cmd(0xC0);
    lcd_str("Data from EEPROM");
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

char i2c_rx_data(void)
{
    char recv_data;
    while(!(I2CONSET &(1<<3)));
    I2CONCLR = (1<<3);
    recv_data = I2DAT;
    return recv_data;
}

void i2c_stop(void)
{
    I2CONSET = (1<<4);
}
