#include <pic18f8722.h>

#include "clock.h"

int defineTMR0Register(void) {
    return 256 * 256 - (CLOCK * 250) / (int)4; 
}

void __interrupt () deviceInterrupt(void) {
    //TMR0L = 100;
    if (INTCONbits.TMR0IF == 1 && INTCONbits.TMR0IE == 1) {
        INTCONbits.TMR0IF = 0;
        TMR0L = defineTMR0Register();
        button();
    }
}