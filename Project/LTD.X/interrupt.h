/* 
 * File:   interrupt.h
 * Author: quyenhooppa
 *
 * Created on November 18, 2019, 9:38 AM
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
#include "dht.h"
#include "button.h"
    
#define PERIOD 5000

int msCounter = 0; 
int count10ms = 10;
int count500ms = 0;
int counter = 0;
int period = 0;
int read = 0;

void __interrupt () deviceInterrupt(void);  
void readTemp(void);
void readHumid(void);

enum {heater, heatpump}heatSt;
enum {on, off}fan3St;
enum {idle, chooseTemp, chooseHumid}state;

#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPT_H */

