/*
 * File:   main.c
 * Author: quyenhooppa
 *
 * Created on November 18, 2019, 9:09 AM
 */


#include <xc.h>
#include <pic18f8722.h>
//#include "devices.h"
//include "interrupt.h"
#include "devices.h"
//#include "clock.h"

void main(void) {
    oscillationInitialize();
    timerInitialize();
    inputInitialize();
    LCDInit();
    ledInitialize();
    initTask();
    
    valTemp = normal;
    valHumid = normal;
    state = heater;
    fan3St = off;
    void(*pF)(uint32_t);
    pF = runFan;
    //register_timer(0, 500, pF, 5);
    register_timer(0, 500, pF, 2);
    LED7 = 1;
    start_timer();
    uint16_t speed, newSpeed;
    int oldTemp, oldHumid;
    int temp;
    char counter = 0;
    while (1) {
        dispatch();
        int temp = realTemp / 10;
        mCURSOR_LINE1;
        LCDPutChar(temp/10 + '0');
        LCDPutChar(temp%10 + '0');
        LCDPutChar(realTemp%10 + '0');
        LCDPutChar(' ');
        temp = realHumid / 10;
        LCDPutChar(temp/10 + '0');
        LCDPutChar(temp%10 + '0');
        LCDPutChar(realHumid%10 + '0');
        if (read == 1) {
            oldTemp = realTemp;
            oldHumid = realHumid;
            //LATD = realTemp;
            readTempAndHumid();
            read = 0;
            if (error == 1) {
                error = 0;
                realTemp = oldTemp;
                realHumid = oldHumid;
                //LCDPutChar(' ');
                //LCDPutStr("No");
            } else {
                //LCDPutChar(' ');
                //LCDPutStr("OK");
            }
        }
        int changeS0 = detect || period;
        int changeS1 = !detect && period;
        switch (state) {
            case heater:
                if (changeS0 == 1) {
                    state = heatpump;
                    uint32_t remove = findTask(2);
                    period = 0;
                    remove_timer(remove);
                    LED2 = 0;
                    LED7 = 0;
                    LED8 = 1;
                    register_timer(0, 500, pF, 1);
                }
                break;
            case heatpump:
                if (changeS1 == 1) {
                    state = heater;
                    period = 0;
                    uint32_t remove = findTask(1);
                    remove_timer(remove);
                    LED1 = 0;
                    LED7 = 1;
                    LED8 = 0;
                    register_timer(0, 500, pF, 2);
                }
                break;
        } 
        switch(fan3St) {
            case off:
                if (change == 1) {
                    fan3St = on;
                    speed = speedFan3(realHumid);
                    register_timer(0, speed, pF, 3);
                } 
                break;
            case on:
                if (change == 0) {
                    fan3St = off;
                    uint32_t remove = findTask(3);
                    remove_timer(remove);
                    LED3 = 0;
                } else if (realHumid > MAX_HUMID) {
                    newSpeed = speedFan3(realHumid);
                    if (newSpeed != speed) {
                        uint32_t remove = findTask(3);
                        remove_timer(remove);
                        register_timer(0, newSpeed, pF, 3);
                    }
                    speed = newSpeed;
                } else {
                    speed = speedFan3(realHumid);
                }
                break;
        }
    }
    return;
}
