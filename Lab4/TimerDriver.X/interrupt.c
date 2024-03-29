#include "interrupt.h"

void __interrupt () deviceInterrupt(void) {
    //Timer 0 interrupt 
    if (INTCONbits.TMR0IF == 1 && INTCONbits.TMR0IE == 1) {
        INTCONbits.TMR0IF = 0;//clear overflow flag
        //write to timer0 register
        TMR0H = 0xfd;
        TMR0L = 0x0f;
}
    
    //Timer 1 interrupt
    if (PIR1bits.TMR1IF == 1 && PIE1bits.TMR1IE == 1) {
        PIR1bits.TMR1IF = 0;//clear overflow flag
        counterTime++;
        //write to timer1 register
        TMR1H = 0xff;
        TMR1L = 0xdc;
        timer_ISR();
    }
}