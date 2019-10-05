/*
 * File:   main.c
 * Author: quyenhooppa
 *
 * Created on September 21, 2019, 8:56 AM
 */

#include <xc.h>
#include <pic18f8722.h>
#include "interrupt.h"
#include "stateClock.h"
#include "statesModify.h"
#include "stateStpWatch.h"

void main(void) {
    oscillationInitialize();
    timerInitialize();
    buttonInitialize();
    LCDInit();
    state = norClk;
    stModify = init;
    int changeModePressed = 0;
    if (RA5Pressed == 0) {
        changeModePressed = 0;
    }
    while (1)
    {
        switch (state) {
            case norClk:
                miliSecSTW = 0;
                secSTW = 0;
                minSTW = 0;
                norClock();
                displayClock();
                if (changeModePressed == 0) {
                    changeModePressed = 1;
                    state = modHr;
                    blink = 0;
                    count10ms = 0;
                }
                break;
            case modHr:
                modifyHour();
                displayModHour();
                if (changeModePressed == 0) {
                    changeModePressed = 1;
                    state = modMin;
                    blink = 0;
                    count10ms = 0;
                }
                break;
            case modMin:
                modifyMinute();
                displayModMinute();
                if (changeModePressed == 0) {
                    changeModePressed = 1;
                    state = modSec;
                    blink = 0;
                    count10ms = 0;
                }
                break;
            case modSec:
                modifySecond();
                displayModSecond();
                if (changeModePressed == 0) {
                    changeModePressed = 1;
                    state = stpWatch;
                    runSTW = 0;
                    count10ms = 0;
                }
                break; 
            case stpWatch:
                norClock();
                stopWatch();
                displayStpWatch();
                if (changeModePressed == 0) {
                    changeModePressed = 1;
                    state = norClk;
                    runSTW = 0;
                }
                break;
        }
    }
    return;
}
