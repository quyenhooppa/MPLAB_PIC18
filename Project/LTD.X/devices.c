#include "devices.h"

void runFan(int fan) {
    switch(fan) {
        case 1: 
            LED1 = (LED1 + 1) % 2;
            break;
        case 2: 
            LED2 = (LED2 + 1) % 2;
            break;
        case 3: 
            LED3 = (LED3 + 1) % 2;
            break;
        default:
            break;
    }
}

