#include "system.h"

void oscillationInitialize(void) {
    OSCCON = 0b01110111; //oscillation 8MHz 
    OSCTUNE = 0b00001111;
}

void timerInitialize(void) {
    //Timer 0
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;
    T0CON = 0b11000110;
    TMR0L = defineTMR0Register();
}

void buttonInitialize(void) {
    TRISAbits.TRISA5 = 1;
    TRISBbits.TRISB0 = 1;
    ADCON1 = 0b00001111;
}

void ledInitialize(void) {
    TRISD = 0x00;
    LATD = 0x00;
}
