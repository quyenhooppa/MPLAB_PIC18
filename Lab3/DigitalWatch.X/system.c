#include "system.h"

void oscillationInitialize(void) {
    OSCCON = 0b01000111; //oscillation 1MHz 
    OSCTUNE = 0b00001111;
}

void timerInitialize(void) {
    //Timer 0
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;
    T0CON = 0b10000001;//16-bit register, internal oscillation, prescaler 1:4 
    //TMR0L = defineTMR0Register();
}

void buttonInitialize(void) {
    TRISAbits.TRISA5 = 1;
    TRISBbits.TRISB0 = 1;
    ADCON1 = 0b00001111;
}

