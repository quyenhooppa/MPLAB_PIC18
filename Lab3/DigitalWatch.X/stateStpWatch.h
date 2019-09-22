/* 
 * File:   stateStpWatch.h
 * Author: quyenhooppa
 *
 * Created on September 21, 2019, 11:33 PM
 */

#ifndef STATESTPWATCH_H
#define	STATESTPWATCH_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "interrupt.h"

int run = 0;
int minSTW = 0;
int secSTW = 0;
int miliSecSTW = 0;
    
void stopWatch (void);
void displayStpWatch (void);

#ifdef	__cplusplus
}
#endif

#endif	/* STATESTPWATCH_H */

