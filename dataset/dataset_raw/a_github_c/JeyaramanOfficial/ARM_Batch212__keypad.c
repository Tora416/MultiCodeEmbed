





        
#include "../lcd_header.h"
#define ROWS (0x0F<<21)
#define COLS (0x0F<<17)

void rows(void);
void col_1(void);
void col_2(void);
void col_3(void);
void col_4(void);

int main()
{

    lcd_config();
    while(1)
    {
        rows();


        
    }
}

void rows(void)
{
    int val;

    IODIR1 = IODIR1 & ~ROWS;        
    IODIR1 = IODIR1 | COLS;         
    val = IOPIN1 & ROWS;        
    val = val >> 21;
    switch(val)
    {
        case 0x0E:   col_1();   delay(200); break;
        case 0x0D:   col_2();   delay(200); break;
        case 0x0B:   col_3();   delay(200); break;
        case 0x07:   col_4();   delay(200); break;
    }
}

void col_1(void)                    
{
    int val;
    IODIR1 = IODIR1 & ~COLS;        
    IODIR1 = IODIR1 | ROWS;         
    
    val = IOPIN1 & COLS;        
    val = val >> 17;
    switch(val)
    {
        case 0x0E:  lcd_data('7');  delay(200); break;
        case 0x0D:  lcd_data('8');  delay(200); break;
        case 0x0B:  lcd_data('9');  delay(200); break;
        case 0x07:  lcd_data('/');  delay(200); break;
    }
}

void col_2(void)                    
{
    int val;
    IODIR1 = IODIR1 & ~COLS;        
    IODIR1 = IODIR1 | ROWS;         
    
    val = IOPIN1 & COLS;        
    val = val >> 17;
    switch(val)
    {
        case 0x0E:  lcd_data('4');  delay(200); break;
        case 0x0D:  lcd_data('5');  delay(200); break;
        case 0x0B:  lcd_data('6');  delay(200); break;
        case 0x07:  lcd_data('x');  delay(200); break;
    }
}

void col_3(void)            
{
    int val;
    IODIR1 = IODIR1 & ~COLS;        
    IODIR1 = IODIR1 | ROWS;         
    
    val = IOPIN1 & COLS;        
    val = val >> 17;
    switch(val)
    {
        case 0x0E:  lcd_data('1');  delay(200); break;
        case 0x0D:  lcd_data('2');  delay(200); break;
        case 0x0B:  lcd_data('3');  delay(200); break;
        case 0x07:  lcd_data('-');  delay(200); break;
    }
}

void col_4(void)    
{
    int val;
    IODIR1 = IODIR1 & ~COLS;        
    IODIR1 = IODIR1 | ROWS;         
    
    val = IOPIN1 & COLS;        
    val = val >> 17;
    switch(val)
    {
        case 0x0E:  lcd_data('.');  delay(200); break;
        case 0x0D:  lcd_data('0');  delay(200); break;
        case 0x0B:  lcd_data('=');  delay(200); break;
        case 0x07:  lcd_data('+');  delay(200); break;
    }
}



