/* 
 * File:   clock.h
 * Author: quyenhooppa
 *
 * Created on September 21, 2019, 6:05 PM
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
#include "button.h"
#include "stateStpWatch.h" 
    
int count10ms = 0;    
int flag = 0;

void __interrupt () deviceInterrupt(void);  

enum State{norClk, modHr, modMin, modSec, stpWatch} state;

#ifdef	__cplusplus
}
#endif

#endif	/* CLOCK_H */

