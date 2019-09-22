/*
 * File:   main.c
 * Author: quyenhooppa
 *
 * Created on September 15, 2019, 4:45 PM
 */
#include <xc.h>
#include <pic18f8722.h>
#include "system.h"
#include "button.h"
#include "clock.h"

void main(void) {
    enum State{init, iNormal, iFast, iSlow, dNormal, dFast, dSlow} state;
    oscillationInitialize();
    timerInitialize();
    buttonInitialize();
    ledInitialize();
    state = init;
    while (1) {
        switch (state) {
            case init:
                countFast = 0;
                countSlow = 0;
                if (iCount > 0) {
                    LATD++;
                    state = iNormal;
                }
                else if (iCount == 0 && dCount > 0) {
                    LATD--;
                    state = dNormal;
                }
                break;
            case iNormal:
                if (iCount == 0) {
                    state = init;
                }
                if (countSlow > 0) {
                    changeSlow = 1;
                    state = iSlow;
                } 
                break;
            case iSlow:
                if (iCount == 0) {
                    state = init;
                }
                if (changeSlow == 1) {
                    LATD++;
                    changeSlow = 0;
                }
                if (countFast > 0) {
                    changeFast = 1;
                    state = iFast;
                }
                break;
            case iFast:
                if (iCount == 0) {
                    state = init;
                }
                if (changeFast == 1) {
                    LATD++;
                    changeFast = 0;
                }
                break;
            case dNormal:
                if (dCount == 0 || iCount > 0) {
                    state = init;
                }
                if (countSlow > 0) {
                    changeSlow = 1;
                    state = dSlow;
                } 
                break;
            case dSlow:
                if (dCount == 0 || iCount > 0) {
                    state = init;
                }
                if (changeSlow == 1) {
                    LATD--;
                    changeSlow = 0;
                }
                if (countFast > 0) {
                    changeFast = 1;
                    state = dFast;
                }
                break;
            case dFast:
                if (dCount == 0 || iCount > 0) {
                    state = init;
                }
                if (changeFast == 1) {
                    LATD--;
                    changeFast = 0;
                }
                break;  
        }
    }
    return;
}
