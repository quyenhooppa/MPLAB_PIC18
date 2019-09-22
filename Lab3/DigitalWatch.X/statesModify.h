/* 
 * File:   statesModify.h
 * Author: quyenhooppa
 *
 * Created on September 21, 2019, 10:03 PM
 */

#ifndef STATESMODIFY_H
#define	STATESMODIFY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stateClock.h"

int blink = 0;
    
void modifyHour (void);
void modifyMinute (void);
void modifySecond (void);
void displayModify (void);

enum st{init, iNor, iAuto} stModify;

#ifdef	__cplusplus
}
#endif

#endif	/* STATESMODIFY_H */

