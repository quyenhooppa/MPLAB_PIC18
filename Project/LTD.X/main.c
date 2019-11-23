/*
 * File:   main.c
 * Author: quyenhooppa
 *
 * Created on November 18, 2019, 9:09 AM
 */


#include <xc.h>
#include <pic18f8722.h>
#include "devices.h"
#include "dht.h"

void main(void) {
    oscillationInitialize();
    timerInitialize();
    inputInitialize();
    LCDInit();
    ledInitialize();
    int check = 0; 
//    startSignal();
//    checkSignal();
//    while (1) {
//        if (msCounter == 150) {
    if (check == 0) {
            startSignal();
            checkSignal();
            check = 1;
    }
            //LATD = 5;
//            if (receive == 1) {
//                //LATD++;
                unsigned char iHumid = readA0();
//                unsigned char dHumid = readA0();
//                unsigned char iTemp = readA0();
//                unsigned char dTemp = readA0();
//                unsigned sum = readA0();
//                if (sum == ((iHumid + dHumid + iTemp + dTemp) & 0xff)) {
//                    temp = dTemp;
//                    humid = dHumid;
//                    LATD = temp;
////                    LCDPutInst(0x80);
////                    LCDPutChar(temp/10);
////                    LCDPutChar(temp%10);
//                } else {
//                    LATD = 1;
////                    LCDPutInst(0x80);
////                    LCDPutChar('S');
//            }
//      
//            } else {
//                LATD = 2;
//                LCDPutInst(0x80);
//                LCDPutChar('F');
//            }
//            msCounter = 0;
//        }
//    }
    return;
}
