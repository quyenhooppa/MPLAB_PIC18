#include "stateStpWatch.h"

void stopWatch (void) {
    if (btnPressed == 0) {
        btnPressed = 1;
        if (runSTW == 0) {
            miliSecSTW = 0;
            secSTW = 0;
            minSTW = 0;
        }
        runSTW = (runSTW + 1) % 2;
    }
    if (RA5Pressed == 0) {
        btnPressed = 0;
    }
    if (runSTW == 1) {
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