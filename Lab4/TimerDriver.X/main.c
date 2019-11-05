/*
 * File:   main.c
 * Author: quyenhooppa
 *
 * Created on October 10, 2019, 9:59 AM
 */


#include <xc.h>
#include "clock.h"

void main (void) {
    oscillationInitialize ();
    timerInitialize ();
    buttonInitialize ();
    ledInitialize (); 
    initStateLed ();
    listOfTask.size = 0;
    listOfExe.size = 0;
    
    void(*pF)(int);
    pF = blink;
    int count = 0;
    register_timer(500, 1000, pF, &count);
    count++;
    register_timer(200, 1500, pF, &count);
    count++;
    register_timer(10, 500, pF, &count);
    count++;
    register_timer(10, 1500, pF, &count);
    count++;
    register_timer(300, 0, pF, &count);
    count++;
    register_timer(200, 1500, pF, &count);
    start_timer();
    while (1) {
        dispatch();
    }
}
