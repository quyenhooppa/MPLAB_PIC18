#include "clock.h"

int defineTMR0Register(void) {
    return 256 - (CLOCK * 2000) / (int)128; 
}

void __interrupt () deviceInterrupt(void) {
    //TMR0L = 100;
    if (INTCONbits.TMR0IF == 1 && INTCONbits.TMR0IE == 1) {
        INTCONbits.TMR0IF = 0;
        TMR0L = timer0Register;
        //LATD++;
        button();
    }
}