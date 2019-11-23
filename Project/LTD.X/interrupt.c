#include "interrupt.h"

void __interrupt () deviceInterrupt(void) {
    //timer 0 interrupt 1ms
    if (INTCONbits.TMR0IF == 1 && INTCONbits.TMR0IE == 1) {
        INTCONbits.TMR0IF = 0;
        TMR0H = 0xfd;
        TMR0L = 0x5f;
        msCounter++;
        //set timer 0 register
    }
    
    //timer 1 interrupt 10us
    if (PIR1bits.TMR1IF == 1 && PIE1bits.TMR1IE == 1) {
        PIR1bits.TMR1IF = 0;
        dhtCounter++;
        //set timer 1 register
    }
}
