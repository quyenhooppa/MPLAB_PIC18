#include "interrupt.h"

void __interrupt () deviceInterrupt(void) {
    if (INTCONbits.TMR0IF == 1 && INTCONbits.TMR0IE == 1) {
        INTCONbits.TMR0IF = 0;//clear overflow flag
        //write to timer0 register
        TMR0H = (timer0ReloadVal << 16);
        TMR0L = (uint8_t)timer0ReloadVal;
        count10ms++;
        timerFlag = 1;
        button();
    }
}
