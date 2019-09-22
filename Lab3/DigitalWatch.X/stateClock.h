/* 
 * File:   stateClock.h
 * Author: quyenhooppa
 *
 * Created on September 21, 2019, 9:37 PM
 */

#ifndef STATECLOCK_H
#define	STATECLOCK_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <pic18f8722.h>
#include "interrupt.h"

int sec = 0;
int min = 0;
int hr = 0;

void norClock (void);
void displayClock (void);

#ifdef	__cplusplus
}
#endif

#endif	/* STATECLOCK_H */

