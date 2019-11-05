#include <pic18f8722.h>

#include "system.h"

void oscillationInitialize (void) {
    OSCCON = 0b01110111; //oscillation 8MHz 
    OSCTUNE = 0b00001111;
}

void timerInitialize (void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    //Timer 0
    INTCONbits.TMR0IE = 1;//set timer0
    INTCONbits.TMR0IF = 0;
    T0CON = 0b00000100; 
    
    //Timer 1
    PIE1bits.TMR1IE = 1;
    PIR1bits.TMR1IF = 0;
    T1CON = 0b00001110;
}

void buttonInitialize (void) {
    TRISAbits.TRISA5 = 1;
    TRISBbits.TRISB0 = 1;
    ADCON1 = 0b00001111;
}

void ledInitialize(void) {
    TRISD = 0x00;
    LATD = 0x00;
}