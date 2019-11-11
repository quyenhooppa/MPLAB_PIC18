/* 
 * File:   clock.h
 * Author: quyenhooppa
 *
 * Created on October 10, 2019, 9:59 AM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <pic18f8722.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "system.h"

#define MAX_TASK 10
    
typedef unsigned long int timestamp_t;
typedef void(*timer_callback_t)(uint32_t);

struct task{
    void(*pTask)(uint32_t);
    uint32_t delay;
    uint32_t period;
    int run;
    uint32_t arg;
    long int next;
};

struct task lsOfTask[MAX_TASK];

unsigned long int counterTime = 0;
unsigned long int ticks = 0;
uint32_t head = 0;//head begins at 1 

void start_timer (void);
timestamp_t get_time (void);
void initTask(void);
void register_timer (uint32_t, uint32_t, timer_callback_t, uint32_t);
void remove_timer (uint32_t);
void stop_timer (void);
void timer_ISR (void);
void addTaskExe (uint32_t);
void dispatch (void);

#ifdef	__cplusplus
}
#endif

#endif	/* CLOCK_H */

