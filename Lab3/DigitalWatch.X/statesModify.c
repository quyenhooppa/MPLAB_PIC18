#include "statesModify.h"


void modifyHour (void) {
    switch (stModify) {
        case init:
            if (RA5Pressed == 0 && countPressed > 0) {
                hr++;
                stModify = iNor;
            }
            break;
        case iNor:
            if (countPressed == 0 || RA5Pressed == 1) {
                stModify = init;
            }
            if (countAuto > 0) {
                increaseTime = 1;
                stModify = iAuto;
            }
            break;
        case iAuto:
            if (countPressed == 0 || RA5Pressed == 1) {
                stModify = init;
            }
            if (increaseTime == 1) {
                increaseTime = 0;
                hr++;
            } 
            break;
    }
    if (hr >= 24) {
        hr = 0;
    }
}

void modifyMinute (void) {
    switch (stModify) {
        case init:
            if (RA5Pressed == 0 && countPressed > 0) {
                min++;
                stModify = iNor;
            }
            break;
        case iNor:
            if (countPressed == 0 || RA5Pressed == 1) {
                stModify = init;
            }
            if (countAuto > 0) {
                increaseTime = 1;
                stModify = iAuto;
            }
            break;
        case iAuto:
            if (countPressed == 0 || RA5Pressed == 1) {
                stModify = init;
            }
            if (increaseTime == 1) {
                increaseTime = 0;
                min++;
            } 
            break;
    }
    if (min >= 60) {
        min = 0;
    }
}

void modifySecond (void) {
    switch (stModify) {
        case init:
            if (RA5Pressed == 0 && countPressed > 0) {
                sec++;
                stModify = iNor;
            }
            break;
        case iNor:
            if (countPressed == 0 || RA5Pressed == 1) {
                stModify = init;
            }
            if (countAuto > 0) {
                increaseTime = 1;
                stModify = iAuto;
            }
            break;
        case iAuto:
            if (countPressed == 0 || RA5Pressed == 1) {
                stModify = init;
            }
            if (increaseTime == 1) {
                increaseTime = 0;
                sec++;
            } 
            break;
    }
    if (sec >= 60) {
        sec = 0;
    }
}

void displayModHour (void) {
    mCURSOR_LINE1;
    LCDPutStr(" MODIFIES HOUR ");
    mCURSOR_HOUR;
    if (count10ms >= (PERIOD/2)) {
        count10ms = 0;
        if (countAuto <= 0) {
            if (blink == 0) { 
                LCDPutChar(' ');
                LCDPutChar(' ');
            } else {
                LCDPutChar(hr/10+'0');
                LCDPutChar(hr%10+'0');
            }
            blink = (blink + 1) % 2;
        }
    }
    if (countAuto > 0) {
        LCDPutChar(hr/10+'0');
        LCDPutChar(hr%10+'0');
    }
    LCDPutInst(0xC2);
    LCDPutChar(':');
    //mCURSOR_MINUTE;
    LCDPutChar(min/10+'0');
    LCDPutChar(min%10+'0');
    //LCDPutInst(0xC5);
    LCDPutChar(':');
    //mCURSOR_SECOND;
    LCDPutChar(sec/10+'0');
    LCDPutChar(sec%10+'0');
}

void displayModMinute (void) {
    mCURSOR_LINE1;
    LCDPutStr("MODIFIES MINUTE");
    mCURSOR_HOUR;
    LCDPutChar(hr/10+'0');
    LCDPutChar(hr%10+'0');
    //LCDPutInst(0xC2);
    LCDPutChar(':');
    mCURSOR_MINUTE;
    if (count10ms >= (PERIOD/2)) {
        count10ms = 0;
        if (countAuto <= 0) {
            if (blink == 0) { 
                LCDPutChar(' ');
                LCDPutChar(' ');
            } else {
                LCDPutChar(min/10+'0');
                LCDPutChar(min%10+'0');
            }
            blink = (blink + 1) % 2;
        } 
    }
    if (countAuto > 0) {
        LCDPutChar(min/10+'0');
        LCDPutChar(min%10+'0');
    }
    LCDPutInst(0xC5);
    LCDPutChar(':');
    //mCURSOR_SECOND;
    LCDPutChar(sec/10+'0');
    LCDPutChar(sec%10+'0');
}

void displayModSecond (void) {
    mCURSOR_LINE1;
    LCDPutStr("MODIFIES SECOND");
    mCURSOR_HOUR;
    LCDPutChar(hr/10+'0');
    LCDPutChar(hr%10+'0');
    LCDPutInst(0xC2);
    LCDPutChar(':');
    //mCURSOR_MINUTE;
    LCDPutChar(min/10+'0');
    LCDPutChar(min%10+'0');
    LCDPutInst(0xC5);
    LCDPutChar(':');
    mCURSOR_SECOND;
    if (count10ms >= (PERIOD/2)) {
        count10ms = 0;
        if (countAuto <= 0) {
            if (blink == 0) { 
                LCDPutChar(' ');
                LCDPutChar(' ');
            } else {
                LCDPutChar(sec/10+'0');
                LCDPutChar(sec%10+'0');
            }
            blink = (blink + 1) % 2;
        } 
    }
    if (countAuto > 0) {
        LCDPutChar(sec/10+'0');
        LCDPutChar(sec%10+'0');
    }
}
