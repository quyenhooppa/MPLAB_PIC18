#include "system.h"

void oscillationInitialize (void) {
    OSCCON = 0b01000111; //oscillation 1MHz 
    OSCTUNE = 0b00001111;
}

void timerInitialize (void) {
    INTCONbits.GIE = 1;
    //Timer 0
    INTCONbits.TMR0IE = 1;//set timer0
    T0CON = 0b10000001;//16-bit register, internal oscillation, prescaler 1:4 
    //write to timer0 register
    TMR0H = 0xFD;
    TMR0L = 0x8F;
    timer0ReloadVal = TMR0;
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
