/* 
 * File:   button.h
 * Author: quyenhooppa
 *
 * Created on September 21, 2019, 8:41 AM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <pic18f8722.h>
#include "clock.h" 
    
#define SHORTER 1000 
#define LONGER 3000
#define SLOWER 500 
#define FASTER 100 

int iCount = 0;
int dCount = 0;
int countSlow = 0;
int countFast = 0;
int changeSlow = 0;
int changeFast = 0;
char firstReadRA5 = 1;
char secondReadRA5 = 1;
char firstReadRB0 = 1;
char secondReadRB0 = 1;

int readIButton(void);
int readDButton (void);
void button (void);

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_H */

