#include "interrupt.h"

void __interrupt () deviceInterrupt(void) {
    if (INTCONbits.TMR0IF == 1 && INTCONbits.TMR0IE == 1) {
        INTCONbits.TMR0IF = 0;//clear overflow flag
        //write to timer0 register
        TMR0H = 0xfd;
        TMR0L = 0xaf;
        //TMR0L = 100;
        count10ms++;
        //LATD++;
        timerFlag = 1;
        if (runSTW == 1) {
            miliSecSTW++;
        }
        button();
    }
}
