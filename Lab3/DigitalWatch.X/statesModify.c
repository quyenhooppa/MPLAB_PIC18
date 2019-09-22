#include "statesModify.h"


void modifyHour (void) {
    switch (stModify) {
        case init:
            if (changeModePressed == 0 && countPressed > 0) {
                hr++;
                stModify = iNor;
            }
            break;
        case iNor:
            if (countPressed == 0 || changeModePressed == 1) {
                stModify = init;
            }
            if (countAuto > 0) {
                increaseTime = 1;
                stModify = iAuto;
            }
            break;
        case iAuto:
            if (countPressed == 0 || changeModePressed == 1) {
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
            if (changeModePressed == 0 && countPressed > 0) {
                min++;
                stModify = iNor;
            }
            break;
        case iNor:
            if (countPressed == 0 || changeModePressed == 1) {
                stModify = init;
            }
            if (countAuto > 0) {
                increaseTime = 1;
                stModify = iAuto;
            }
            break;
        case iAuto:
            if (countPressed == 0 || changeModePressed == 1) {
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
            if (changeModePressed == 0 && countPressed > 0) {
                sec++;
                stModify = iNor;
            }
            break;
        case iNor:
            if (countPressed == 0 || changeModePressed == 1) {
                stModify = init;
            }
            if (countAuto > 0) {
                increaseTime = 1;
                stModify = iAuto;
            }
            break;
        case iAuto:
            if (countPressed == 0 || changeModePressed == 1) {
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
    mCURSOR_LINE2;
    if (count10ms >= (PERIOD/4)) {
        count10ms = 0;
            if (blink == 0) { 
                LCDPutChar(' ');
                LCDPutChar(' ');
            } else {
                LCDPutChar(hr/10+'0');
                LCDPutChar(hr%10+'0');
            }
            blink = (blink + 1) % 2;
    }
    LCDPutChar(':');
    LCDPutChar(min/10+'0');
    LCDPutChar(min%10+'0');
    LCDPutChar(':');
    LCDPutChar(sec/10+'0');
    LCDPutChar(sec%10+'0');
}

void displayModMinute (void) {
    mCURSOR_LINE1;
    LCDPutStr("MODIFIES MINUTE");
    mCURSOR_LINE2;
    LCDPutChar(hr/10+'0');
    LCDPutChar(hr%10+'0');
    LCDPutChar(':');
    if (count10ms >= (PERIOD/4)) {
        count10ms = 0;
            if (blink == 0) { 
                LCDPutChar(' ');
                LCDPutChar(' ');
            } else {
                LCDPutChar(min/10+'0');
                LCDPutChar(min%10+'0');
            }
            blink = (blink + 1) % 2;
    }
    LCDPutChar(':');
    LCDPutChar(sec/10+'0');
    LCDPutChar(sec%10+'0');
}

void displayModSecond (void) {
    mCURSOR_LINE1;
    LCDPutStr("MODIFIES MINUTE");
    mCURSOR_LINE2;
    LCDPutChar(hr/10+'0');
    LCDPutChar(hr%10+'0');
    LCDPutChar(':');
    LCDPutChar(min/10+'0');
    LCDPutChar(min%10+'0');
    LCDPutChar(':');
    if (count10ms >= (PERIOD/4)) {
        count10ms = 0;
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

/*void displayModify (void) {
    switch (state) {
        case norClk:
            break;
        case modHr:
            mCURSOR_LINE1;
            LCDPutStr(" MODIFIES HOUR ");
            mCURSOR_LINE2;
            if ((count10ms % 10) == 0) {
                if (blink == 0) { 
                    LCDPutChar(' ');
                    LCDPutChar(' ');
                }
                else {
                    LCDPutChar(hr/10+'0');
                    LCDPutChar(hr%10+'0');
                }
                blink = (blink + 1) % 2;
            }
            LCDPutChar(':');
            LCDPutChar(min/10+'0');
            LCDPutChar(min%10+'0');
            LCDPutChar(':');
            LCDPutChar(sec/10+'0');
            LCDPutChar(sec%10+'0');
            break;
        case modMin:
            mCURSOR_LINE1;
            LCDPutStr("MODIFIES MINUTE");
            mCURSOR_LINE2;
            LCDPutChar(hr/10+'0');
            LCDPutChar(hr%10+'0');
            LCDPutChar(':');
            if ((count10ms % 10) == 0) {
                if (blink == 0) { 
                    LCDPutChar(' ');
                    LCDPutChar(' ');
                }
                else {
                    LCDPutChar(min/10+'0');
                    LCDPutChar(min%10+'0');
                }
                blink = (blink + 1) % 2;
            }
            LCDPutChar(':');
            LCDPutChar(sec/10+'0');
            LCDPutChar(sec%10+'0');
            break;
        case modSec:
            mCURSOR_LINE1;
            LCDPutStr("MODIFIES SECOND");
            mCURSOR_LINE2;
            LCDPutChar(hr/10+'0');
            LCDPutChar(hr%10+'0');
            LCDPutChar(':');
            LCDPutChar(min/10+'0');
            LCDPutChar(min%10+'0');
            LCDPutChar(':');
            if ((count10ms % 10) == 0) {
                if (blink == 0) { 
                    LCDPutChar(' ');
                    LCDPutChar(' ');
                }
                else {
                    LCDPutChar(sec/10+'0');
                    LCDPutChar(sec%10+'0');
                }
                blink = (blink + 1) % 2;
            }            
            break;
        case stpWatch:
            break;
    }
}*/
