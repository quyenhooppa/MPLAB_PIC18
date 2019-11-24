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
#include "interrupt.h"
    
#define STABLE_PERIOD 200

int stTemp = 0;
int sdTemp = 0;
int countTp = 0;
int detect = 0;

int stHumid = 0;
int sdHumid = 0;
int countHd = 0;
int change = 0;
    
void runFan(uint32_t);
uint16_t speedFan3(int);

enum readData {normal, bgLarger, stable, bgSmaller};
enum readData valTemp, valHumid;

#ifdef	__cplusplus
}
#endif

#endif	/* DEVICES_H */

