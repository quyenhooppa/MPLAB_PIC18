/* 
 * File:   clock.h
 * Author: quyenhooppa
 *
 * Created on September 21, 2019, 8:45 AM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <pic18f8722.h>
#include "button.h"

int timer0Register = 0;

void __interrupt () deviceInterrupt(void);
int defineTMR0Register(void);

#ifdef	__cplusplus
}
#endif

#endif	/* CLOCK_H */

