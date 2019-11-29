/* 
 * File:   dht.h
 * Author: quyenhooppa
 *
 * Created on November 18, 2019, 9:49 AM
 */

#ifndef DHT_H
#define	DHT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <pic18f8722.h>
#include "clock.h"
#define _XTAL_FREQ 10000000 
    
#define TIME_OUT 1000
    
#define ERROR -10    
    
int MAX_TEMP = 40;
int MAX_HUMID = 60;

int realTemp;
int realHumid;
char dhtData[5];


char getByteData(void);
int readDHT (void);
void readTempAndHumid(void);
void printTempHumid (void);


#ifdef	__cplusplus
}
#endif

#endif	/* DHT_H */

