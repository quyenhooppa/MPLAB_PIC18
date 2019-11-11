/* 
 * File:   task.h
 * Author: quyenhooppa
 *
 * Created on November 2, 2019, 9:07 PM
 */

#ifndef TASK_H
#define	TASK_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <pic18f8722.h>
#include "BBSPI_LCD.h"
#include "clock.h"

#define LED0 LATD0
#define LED1 LATD1
#define LED2 LATD2
#define LED3 LATD3
#define LED4 LATD4
#define LED5 LATD5
#define LED6 LATD6
#define LED7 LATD7
  
void initStateLed (void);
void blink (uint32_t);
void printLCD(uint32_t);
void print10msInterrupt(uint32_t);


#ifdef	__cplusplus
}
#endif

#endif	/* TASK_H */

