#include "stateStpWatch.h"

void stopWatch (void) {
    if (countPressed > 0) {
        if (runSTW == 0) {
            miliSecSTW = 0;
            secSTW = 0;
            minSTW = 0;
        }
        runSTW = (runSTW + 1) % 2;
        timerFlag = 0;
    }
    if (runSTW == 1) {
        //if (timerFlag == 1) {
            //miliSecSTW++;
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
            //timerFlag = 0;
        //}
    }
}

void displayStpWatch (void) {
    mCURSOR_LINE1;
    LCDPutStr("   STOP WATCH   ");
    mCURSOR_HOUR;
    LCDPutChar(minSTW/10+'0');
    LCDPutChar(minSTW%10+'0');
    LCDPutInst(0xC2);
    LCDPutChar(':');
    mCURSOR_MINUTE;
    LCDPutChar(secSTW/10+'0');
    LCDPutChar(secSTW%10+'0');
    LCDPutInst(0xC5);
    LCDPutChar(':');
    mCURSOR_SECOND;
    LCDPutChar(miliSecSTW/10+'0');
    LCDPutChar(miliSecSTW%10+'0');
}