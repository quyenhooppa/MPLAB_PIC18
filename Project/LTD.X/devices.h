/* 
 * File:   devices.h
 * Author: quyenhooppa
 *
 * Created on November 18, 2019, 10:20 AM
 */

#ifndef DEVICES_H
#define	DEVICES_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <pic18f8722.h>
#include "dht.h"

void runFan1(void);
void runFan2(void);
void runFan3(void);
void runHeater(void);
void runHeatPump(void);
void runFan(int);

#ifdef	__cplusplus
}
#endif

#endif	/* DEVICES_H */

