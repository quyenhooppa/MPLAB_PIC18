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
#include "task.h"
#include "BBSPI_LCD.h"

#define MAX_TASK 10
    
typedef unsigned long int timestamp_t;
typedef void(*timer_callback_t)(int);

struct task{
    void(*pTask)(int);
    uint32_t delay;
    uint32_t period;
    int run;
    int led;
    struct task* next;
};

struct {
    struct task* head; 
    struct task* tail;
    uint32_t size;
}listOfTask;

struct {
    struct task* head; 
    uint32_t size;
}listOfExe;

unsigned long int counterTime = 0;
unsigned long int ticks = 0;

void start_timer (void);
timestamp_t get_time (void);
uint32_t register_timer (uint32_t delay, uint32_t period, timer_callback_t callback, void* arg);
int remove_timer (uint32_t id);
void stop_timer (void);
int timer_ISR (void);
void addTaskExe (struct task* tsk);
void deleteTask (struct task* tsk);
void dispatch (void);
void printLCD(unsigned long int num);

#ifdef	__cplusplus
}
#endif

#endif	/* CLOCK_H */

