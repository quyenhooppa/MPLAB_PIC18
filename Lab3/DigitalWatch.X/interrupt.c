#include "interrupt.h"

void __interrupt () deviceInterrupt(void) {
    if (INTCONbits.TMR0IF == 1 && INTCONbits.TMR0IE == 1) {
        INTCONbits.TMR0IF = 0;//clear overflow flag
        //write to timer0 register
        TMR0H = 0xfd;
        TMR0L = 0x5f;
        count10ms++;
        if (runSTW == 1) {
            miliSecSTW++;
            if (miliSecSTW >= 100) {
                miliSecSTW = 0;
                flag = 1;
            }
        }
        button();
    }
}
