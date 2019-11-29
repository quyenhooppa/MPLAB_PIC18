/* 
 * File:   system.h
 * Author: quyenhooppa
 *
 * Created on November 18, 2019, 9:38 AM
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <pic18f8722.h>
    
#ifdef _18F8722
#pragma config  OSC = HSPLL
#pragma config 	FCMEN = OFF
#pragma config 	IESO = OFF
#pragma config 	PWRT = OFF
#pragma config 	BOREN = OFF
#pragma config 	WDT = OFF
#pragma config 	MCLRE = ON
#pragma config 	LVP = OFF
#pragma config 	XINST = OFF
#endif

#define LED2 LATD1
#define LED3 LATD2
#define LED4 LATD3
#define LED5 LATD4
#define LED6 LATD5
#define LED7 LATD6
#define LED8 LATD7
    
#define DHT_DIRECTION TRISDbits.TRISD0
#define DHT_IN PORTDbits.RD0
#define DHT_OUT LATDbits.LATD0

void oscillationInitialize (void);
void timerInitialize (void);
void pinInitialize (void);
void ledInitialize (void); 


#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

