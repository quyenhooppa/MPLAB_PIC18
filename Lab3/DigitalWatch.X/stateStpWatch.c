#include "stateStpWatch.h"

void stopWatch (void) {
    if (countPressed > 0) {
        if (run == 0) {
            miliSecSTW = 0;
            secSTW = 0;
            minSTW = 0;
        }
        run = (run + 1) % 2;
    }
    if (run == 1) {
        if (timerFlag == 1) {
            miliSecSTW++;
            if (miliSecSTW >= 100) {
                miliSecSTW = 0;
                secSTW++;
            }
            if (secSTW >= 60) {
                secSTW = 0;
                minSTW++;
            }
            if (minSTW >= 60) {
                minSTW = 0;
            }
            timerFlag = 0;
        }
    }
}

void displayStpWatch (void) {
    mCURSOR_LINE1;
    LCDPutStr("   STOP WATCH   ");
    mCURSOR_LINE2;
    LCDPutChar(minSTW/10+'0');
    LCDPutChar(minSTW%10+'0');
    LCDPutChar(':');
    LCDPutChar(secSTW/10+'0');
    LCDPutChar(secSTW%10+'0');
    LCDPutChar(':');
    LCDPutChar(miliSecSTW/10+'0');
    LCDPutChar(miliSecSTW%10+'0');
}