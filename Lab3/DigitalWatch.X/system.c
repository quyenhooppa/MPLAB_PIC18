#include "system.h"

void oscillationInitialize (void) {
    OSCCON = 0b01110111; //oscillation 8MHz 
    OSCTUNE = 0b00001111;
}

void timerInitialize (void) {
    INTCONbits.GIE = 1;
    //Timer 0
    INTCONbits.TMR0IE = 1;//set timer0
    INTCONbits.TMR0IF = 0;
    T0CON = 0b10000100; 
    //write to timer0 register
    TMR0H = 0xfd;
    TMR0L = 0x7f;
}

void buttonInitialize (void) {
    TRISAbits.TRISA5 = 1;
    TRISBbits.TRISB0 = 1;
    ADCON1 = 0b00001111;
}
