#include "stateStpWatch.h"

void stopWatch (void) {
    if (countPressed >= 2) {
        if (runSTW == 0) {
            miliSecSTW = 0;
            secSTW = 0;
            minSTW = 0;
        }
        runSTW = (runSTW + 1) % 2;
    }
    if (runSTW == 1) {
        //if (timerFlag == 1) {
            //miliSecSTW++;
            if (flag == 1) {
                flag = 0;
                secSTW++;
            }
            if (secSTW >= 60) {
                secSTW = 0;
                minSTW++;
            }
            if (minSTW >= 60) {
                minSTW = 0;
            }
        //}
    }
}

void displayStpWatch (void) {
    LCD_CLEAR;
    mCURSOR_LINE1;
    LCDPutStr("   STOP WATCH   ");
    mCURSOR_HOUR;
    LCDPutChar(minSTW/10+'0');
    LCDPutChar(minSTW%10+'0');
    LCDPutChar(':');
    mCURSOR_MINUTE;
    LCDPutChar(secSTW/10+'0');
    LCDPutChar(secSTW%10+'0');
    LCDPutChar(':');
    mCURSOR_SECOND;
    LCDPutChar(miliSecSTW/10+'0');
    LCDPutChar(miliSecSTW%10+'0');
}