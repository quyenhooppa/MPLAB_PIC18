#include "button.h"

int readIButton(void) {
    firstReadRA5 = secondReadRA5;
    secondReadRA5 = PORTAbits.RA5;
    if (firstReadRA5 == secondReadRA5) {
        if (firstReadRA5 == 0) {
            return 1;
        }
        else {
            return 2;
        }
    }
   return 0; 
}

int readDButton (void) {
    firstReadRB0 = secondReadRB0;
    secondReadRB0 = PORTBbits.RB0;
    if (firstReadRB0 == secondReadRB0) {
        if (firstReadRB0 == 0) {
            return 1;
        }
        else {
            return 2;
        }
    }
    return 0;
}

void button (void) {
    int iButton = readIButton();
    int dButton = readDButton();
    if (iButton == 1) {
        iCount++;
        if (iCount > SHORTER / CLOCK) {
            countSlow++;
            if (countSlow > SLOWER / CLOCK) {
                changeSlow = 1;
                countSlow = 0;
            }
        }
        if (iCount > LONGER / CLOCK) {
            countFast++;
            if (countFast > FASTER / CLOCK) {
                changeFast = 1;
                countFast = 0;
            }
        }
    }
    else if (dButton == 1) {
        dCount++;
        if (dCount > SHORTER / CLOCK) {
            countSlow++;
            if (countSlow > SLOWER / CLOCK) {
                changeSlow = 1;
                countSlow = 0;
            }
        }
        if (dCount > LONGER / CLOCK) {
            countFast++;
            if (countFast > FASTER / CLOCK) {
                changeFast = 1;
                countFast = 0;
            }
        }
    }
    else if (iButton == 2 || dButton == 2) {
        iCount = 0;
        dCount = 0;
        countFast = 0;
        changeFast = 0;
        countSlow = 0;
        changeSlow = 0;
    }
}