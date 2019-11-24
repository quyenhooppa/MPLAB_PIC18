/* 
 * File:   interrupt.h
 * Author: quyenhooppa
 *
 * Created on November 18, 2019, 9:38 AM
 */

#ifndef INTERRUPT_H
#define	INTERRUPT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <pic18f8722.h>
#include <stdint.h>
#include <stdbool.h>
#include "clock.h"
#include "dht.h"
    
#define PERIOD 5000
#define NUM 25

int msCounter = 0; 
int counter = 0;
int period = 0;
int read = 0;
int arrTemp[NUM] =  {31, 30, 32, 31, 33,
                     29, 31, 29, 28, 29, 
                     28, 29, 31, 28, 31,
                     32, 31, 33, 29, 31,
                     30, 28, 29, 31, 29};

int arrHumid[NUM] =  {51, 50, 52, 55, 60,
                     61, 65, 66, 70, 74, 
                     75, 78, 69, 68, 58,
                     59, 58, 84, 88, 86,
                     85, 90, 91, 92, 94};
int num = 0;

void __interrupt () deviceInterrupt(void);  
void readTemp(void);
void readHumid(void);

enum {heater, heatpump}state;
enum {on, off}fan3St;

#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPT_H */

