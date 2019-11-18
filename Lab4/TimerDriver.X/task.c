#include "task.h"

void initStateLed(void) {
    LED0 = 0;
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
    LED5 = 0;
    LED6 = 0;
    LED7 = 0;
}

void blink (uint32_t led) {
    switch (led) {
        case 0: 
            LED0 = (LED0 + 1) % 2;
            break;
        case 1: 
            LED1 = (LED1 + 1) % 2;
            break;
        case 2: 
            LED2 = (LED2 + 1) % 2;
            break;
        case 3: 
            LED3 = (LED3 + 1) % 2;
            break;        
        case 4: 
            LED4 = (LED4 + 1) % 2;
            break;
        case 5: 
            LED5 = (LED5 + 1) % 2;
            break;        
        case 6: 
            LED6 = (LED6 + 1) % 2;
            break;        
        case 7: 
            LED7 = (LED7 + 1) % 2;
            break; 
        default:
            break;
    }
}
