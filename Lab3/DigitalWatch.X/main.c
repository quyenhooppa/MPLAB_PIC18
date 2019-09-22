/*
 * File:   main.c
 * Author: quyenhooppa
 *
 * Created on September 21, 2019, 8:56 AM
 */

#include <xc.h>
#include <pic18f8722.h>
#include "stateClock.h"
#include "statesModify.h"
#include "stateStpWatch.h"

void main(void) {
    oscillationInitialize();
    timerInitialize();
    buttonInitialize();
    state = norClk;
    stModify = init;
    switch (state) {
        case norClk:
            norClock();
            displayClock();
            if (changeModePressed == 1) {
                changeModePressed = 0;
                state = modHr;
            }
            break;
        case modHr:
            modifyHour();
            displayModify();
            if (changeModePressed == 1) {
                changeModePressed = 0;
                state = modMin;
            }
            break;
        case modMin:
            modifyMinute();
            displayModify();
            if (changeModePressed == 1) {
                changeModePressed = 0;
                state = modSec;
            }
            break;
        case modSec:
            modifySecond();
            displayModify();
            if (changeModePressed == 1) {
                changeModePressed = 0;
                state = stpWatch;
            }
            break; 
        case stpWatch:
            norClock();
            stopWatch();
            displayStpWatch();
            if (changeModePressed == 1) {
                changeModePressed = 0;
                state = norClk;
            }
            break;
    }
    return;
}
