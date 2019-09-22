#include "system.h"

void oscillationInitialize(void) {
    OSCCON = 0b01110111; //oscillation 8MHz 
    //OSCCON = 0b01000111; //oscillation 1MHz 
    OSCTUNE = 0b00001111;
}

void timerInitialize(void) {
    //Timer 0
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.TMR0IF = 0;
    T0CON = 0b11000110;
    //T0CON = 0b10000001;
    //16-bit register, internal oscilation, prescale 1:4
    //timer0ReloadVal = (uint24_t)defineTMR0Register();
    //TMR0H = (timer0ReloadVal << 16);
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
