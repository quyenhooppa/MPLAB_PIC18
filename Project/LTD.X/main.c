/*
 * File:   main.c
 * Author: quyenhooppa
 *
 * Created on November 18, 2019, 9:09 AM
 */


#include <xc.h>
#include <pic18f8722.h>
#include "devices.h"
#include "interrupt.h"
//#include "dht.h"
//#include "clock.h"

void main(void) {
    oscillationInitialize();
    timerInitialize();
    pinInitialize();
    LCDInit();
    ledInitialize();
    initTask();
    
    valTemp = normal;
    valHumid = normal;
    heatSt = heater;
    fan3St = off;
    void(*pF)(uint32_t);
    pF = runFan;
    //register_timer(0, 10, pF, 5);
    state = chooseTemp;
    int changeMod = 0;
    start_timer();
    
    while (1) {
//        readTempAndHumid();
//        __delay_ms(1000);
        dispatch();
        if (RA5Pressed == 0) {
            changeMod = 0;
        }
        switch (state) {
            case idle:
                stateDevices();
                read = 1;
                if (RA5Pressed == 1) {
                    if (changeMod == 0) {
                        state = chooseTemp;
                        modTempVal = MAX_TEMP;
                        modHumidVal = MAX_HUMID;
                        changeMod = 1;
                        mLCD_CLEAR;
                        read = 0;
                    }
                }
                break;
            case chooseTemp:
                modifyMaxTemp();
                display();
                if (RA5Pressed == 1) {
                    if (changeMod == 0) {
                        state = chooseHumid;
                        changeMod = 1;
                        MAX_TEMP = modTempVal;
                        mLCD_CLEAR;
                    }
                }
                break;
            case chooseHumid:
                modifyMaxHumid();
                display();
                if (RA5Pressed == 1) {
                    if (changeMod == 0) {
                        state = idle;
                        changeMod = 1;
                        MAX_HUMID = modHumidVal;
                        mLCD_CLEAR;
                        read = 1;
                    }
                }
                break;
        }
         
    }
    return;
}
