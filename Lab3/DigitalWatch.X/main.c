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
    ledInitialize();
    LCDInit();
    state = norClk;
    stModify = init;
    while (1)
    {
        switch (state) {
            case norClk:
                miliSecSTW = 0;
                secSTW = 0;
                minSTW = 0;
                norClock();
                displayClock();
                if (changeModePressed == 1) {
                    changeModePressed = 0;
                    state = modHr;
                    blink = 0;
                    count10ms = 0;
                }
                break;
            case modHr:
                modifyHour();
                //displayModify
                displayModHour();
                if (changeModePressed == 1) {
                    changeModePressed = 0;
                    state = modMin;
                    blink = 0;
                    count10ms = 0;
                }
                break;
            case modMin:
                modifyMinute();
                //displayModify();
                displayModMinute();
                if (changeModePressed == 1) {
                    changeModePressed = 0;
                    state = modSec;
                    blink = 0;
                    count10ms = 0;
                }
                break;
            case modSec:
                modifySecond();
                //displayModify();
                displayModSecond();
                if (changeModePressed == 1) {
                    changeModePressed = 0;
                    state = stpWatch;
                    run = 0;
                    count10ms = 0;
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
    }
    return;
}
