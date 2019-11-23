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
#include "system.h"

int msCounter = 0;    
int fan1Counter = 0;
int fan2Counter = 0;
int fan3Counter = 0;
int dhtCounter = 0;

void __interrupt () deviceInterrupt(void);  

#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPT_H */

