#include "stateClock.h"

void norClock (void) {
    //while(state == norClk || state == stpWatch) {
        if (count10ms >= 100) {
            count10ms = 0;
            sec++;
            if (sec >= 60) {
                sec = 0;
                min++;
            }
            if (min >= 60) {
                min = 0;
                hr++;
            }
            if (hr >= 24) {
                hr = 0;
            } 
        }
    //}
}

void displayClock (void) {
    //while (state == norClk) {
        mCURSOR_LINE1;
        LCDPutStr("  NORMAL CLOCK  ");
        mCURSOR_LINE2;
        LCDPutChar(hr/10+'0');
        LCDPutChar(hr%10+'0');
        LCDPutChar(':');
        LCDPutChar(min/10+'0');
        LCDPutChar(min%10+'0');
        LCDPutChar(':');
        LCDPutChar(sec/10+'0');
        LCDPutChar(sec%10+'0');
    //}
}