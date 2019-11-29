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
    T0CON = 0b0000100; 
    
    //Timer 1
    PIE1bits.TMR1IE = 1;
    PIR1bits.TMR1IF = 0;
    T1CON = 0b00001110;
}


void pinInitialize (void) {
    TRISAbits.TRISA5 = 1;
    TRISBbits.TRISB0 = 1;
    //DHT_DIRECTION = 0;
    ADCON1 = 0b00001111;
}

void ledInitialize(void) {
    TRISD = 0x00;
    LATD = 0x00;
}
