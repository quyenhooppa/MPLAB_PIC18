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
#include "interrupt.h"
#include "BBSPI_LCD.h"
    
#define MAX_TEMP 40
#define MAX_HUMID 80
    
unsigned temp = 0;
unsigned humid = 0;
int receive = 0;
int stReadA0 = 0;
int sdReadA0 = 0;
int stReadA1 = 0;
int sdReadA1 = 0;
int stReadA2 = 0;
int sdReadA2 = 0;

void startSignal (void);
void checkSignal (void);
char readA0 (void);
void readA1 (void);
void readA2 (void);
void readTemp (void);
void readHumid (void);


#ifdef	__cplusplus
}
#endif

#endif	/* DHT_H */

