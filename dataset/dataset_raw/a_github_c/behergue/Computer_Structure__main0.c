#include <stdio.h>
#include "44b.h"
#include "button.h"
#include "leds.h"
#include "utils.h"
#include "D8Led.h"
#include "intcontroller.h"
#include "timer.h"
#include "gpio.h"
#include "keyboard.h"

struct RLstat {
    int moving;
    int speed;
    int direction;
    int position;
};

static struct RLstat RL = {
    .moving = 0,
    .speed = 5,
    .direction = 0,
    .position = 0,
};

void timer_ISR(void) __attribute__ ((interrupt ("IRQ")));
void button_ISR(void) __attribute__ ((interrupt ("IRQ")));


void timer_ISR(void)
{
    
    if (RL.direction == 1) 
    {
        if (RL.position + 1 < 6)
        {
            RL.position += 1;
        }
        else
        {
            RL.position = 0;
        }
    }
    else
    {
        if (RL.position - 1 >= 0)
        {
            RL.position -= 1;
        }
        else
        {
            RL.position = 5;
        }
    }

    D8Led_segment(RL.position);
}

void button_ISR(void)
{
    unsigned int whicheint = rEXTINTPND;
    unsigned int buttons = (whicheint >> 2) & 0x3;

    
    

    if (buttons & ~BUT1) {
        
        
        
        

        led1_off();
        led2_off();

        if(RL.direction == 0)
        {
            RL.direction = 1;
        }
        else
        {
            RL.direction = 0;
        }
    }

    if (buttons & ~BUT2) {
        
        
        
        
        
        

        led1_switch();

        led2_switch();


        if (RL.moving == 0)
        {
            RL.moving= 1;
        }
        else
        {
            RL.moving= 0;
        }
    }

    
    Delay(2000);
    
    rEXTINTPND &= ~(0x03 << 2);
            
            
            
}













































int setup(void)
{
    ic_enable(INT_GLOBAL);

    leds_init();
    D8Led_init();
    D8Led_segment(RL.position);

    

    
    
    
    

    portG_conf(6, EINT);
    portG_conf(7, EINT);
    portG_conf(1, EINT);

    portG_conf_pup(6, ENABLE);
    portG_conf_pup(7, ENABLE);
    portG_conf_pup(1, ENABLE);
    

    
    tmr_set_prescaler(TIMER0, 255);
    tmr_set_divider(8, TIMER0);
    tmr_set_count(TIMER0, 62500, 1);

    if (RL.moving)
        tmr_start(TIMER0);
    

    
    pISR_TIMER0   = timer_ISR; 
    pISR_EINT4567 = button_ISR; 
    

    
    ic_conf_irq(ENABLE, VEC);
    ic_conf_fiq(DISABLE);
    ic_conf_line(INT_TIMER0, IRQ);
    ic_conf_line(INT_EINT4567, IRQ);
    ic_conf_line(INT_EINT1, IRQ);
    ic_enable(INT_TIMER0);
    ic_enable(INT_EINT4567);
    ic_enable(INT_EINT1);

    ic_init();
    
    
    
    
    
    
    
    
    
    ic_conf_irq(ENABLE, VEC);
    ic_conf_fiq(DISABLE);
    ic_conf_line(INT_TIMER0, IRQ);
    ic_conf_line(INT_EINT4567, IRQ);
    ic_conf_line(INT_EINT1, IRQ);
    ic_enable(INT_TIMER0);
    ic_enable(INT_EINT4567);
    ic_enable(INT_EINT1);
    

    Delay(0);
    return 0;
}

int loop(void)
{
    return 0;
}


int main(void)
{
    setup();

    while (1) {
        loop();
    }
}
