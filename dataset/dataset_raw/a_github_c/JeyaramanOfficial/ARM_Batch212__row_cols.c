



        
#include "../lcd_header.h"
#define ROWS (0x0F<<21)
#define COLS (0x0F<<17)

void rows(void);
void cols(void);


int main()
{

    lcd_config();
    while(1)
    {
        rows();
        delay(1000);
        lcd_cmd(0x01);
        
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
        case 0x0E:  lcd_str("r1"); cols();  delay(200); break;
        case 0x0D:  lcd_str("r2"); cols();  delay(200); break;
        case 0x0B:  lcd_str("r3"); cols();  delay(200); break;
        case 0x07:  lcd_str("r4"); cols();  delay(200); break;
    }
}

void cols(void)
{
    int val;
    IODIR1 = IODIR1 & ~COLS;        
    IODIR1 = IODIR1 | ROWS;         
    
    val = IOPIN1 & COLS;        
    val = val >> 17;
    switch(val)
    {
        case 0x0E:  lcd_str("C1");  delay(200); break;
        case 0x0D:  lcd_str("C2");  delay(200); break;
        case 0x0B:  lcd_str("C3");  delay(200); break;
        case 0x07:  lcd_str("C4");  delay(200); break;
    }
}
