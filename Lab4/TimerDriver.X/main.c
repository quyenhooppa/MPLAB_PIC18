/*
 * File:   main.c
 * Author: quyenhooppa
 *
 * Created on October 10, 2019, 9:59 AM
 */


#include <xc.h>
#include "task.h"

void main (void) {
    oscillationInitialize ();
    timerInitialize ();
    buttonInitialize ();
    ledInitialize (); 
    LCDInit();
    initTask();
    initStateLed ();
    
    void(*pF)(uint32_t);
    pF = blink;
    register_timer(1000, 500, pF, 7);
    register_timer(200, 1000, pF, 5);
    register_timer(2500, 500, pF, 2);
    register_timer(1500, 0, pF, 1);
    start_timer();
    while (1) {
        dispatch();
    }
}
