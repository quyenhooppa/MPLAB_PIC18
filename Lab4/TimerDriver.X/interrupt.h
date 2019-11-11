/* 
 * File:   interrupt.h
 * Author: quyenhooppa
 *
 * Created on October 10, 2019, 9:59 AM
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
#include "task.h"

void __interrupt () deviceInterrupt(void);  


#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPT_H */

