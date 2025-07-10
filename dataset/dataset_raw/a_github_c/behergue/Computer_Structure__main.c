#include <stdio.h>
#include "44b.h"
#include "button.h"
#include "leds.h"
#include "utils.h"
#include "D8Led.h"
#include "gpio.h"

struct RLstat {
    int moving;
    int speed;
    int iter;
    int direction;
    int position;
};

static struct RLstat RL = {
    .moving = 0,
    .speed = 5,
    .iter = 0,
    .direction = 0,
    .position = 0,
};

int setup(void)
{
    leds_init();
    D8Led_init();
    D8Led_segment(RL.position);

    

    
    
    
    
    

    Delay(0);
    return 0;
}

int loop(void)
{
    unsigned int buttons = read_button();

    if (buttons & BUT1) {
        
        
        
        
    }

    if (buttons & BUT2) {
        
        
        
        
        
        
    }

    if (RL.moving) {
        RL.iter--;
        if (RL.iter == 0) {
            
            
            
            
            
            
            
        }
    }

    Delay(2000); 
    return 0;
}


int main(void)
{
    setup();

    while (1) {
        loop();
    }
}
