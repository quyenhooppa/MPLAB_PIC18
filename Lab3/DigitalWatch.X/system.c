#include "system.h"

void oscillationInitialize (void) {
    //OSCCON = 0b01000111; //oscillation 1MHz 
    OSCCON = 0b01110111; //oscillation 8MHz 
    OSCTUNE = 0b00001111;
}

void timerInitialize (void) {
    INTCONbits.GIE = 1;
    //Timer 0
    INTCONbits.TMR0IE = 1;//set timer0
    INTCONbits.TMR0IF = 0;
    T0CON = 0b10000100; 
    //T0CON = 0b11000110;
    //write to timer0 register
    TMR0H = 0xfd;
    TMR0L = 0x8f;
    //TMR0L = 100;
    //timer0ReloadVal = TMR0;
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
