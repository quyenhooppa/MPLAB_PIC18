#include "dht.h"

void startSignal (void) {
    TRISAbits.TRISA5 = 0; //set RA0 as output 
    PORTAbits.RA5 = 0; //send signal to RA0
    TRISAbits.TRISA1 = 0; //set RA1 as output 
    PORTAbits.RA1 = 0; //send signal to RA1
    TRISAbits.TRISA2 = 0; //set RA2 as output 
    PORTAbits.RA2 = 0; //send signal to RA2
    __delay_ms(18);
    
    PORTAbits.RA5 = 1;
    PORTAbits.RA1 = 1;
    PORTAbits.RA2 = 1;
    __delay_us(40);
    
    TRISAbits.TRISA5 = 1; //set RA0 as input   
    TRISAbits.TRISA1 = 1; //set RA1 as input
    TRISAbits.TRISA2 = 1; //set RA2 as input
}

void checkSignal (void) {
    receive = 0;
    while (PORTAbits.RA5 == 0) {LATD = 3;};
    if (PORTAbits.RA5 == 0) {
        __delay_us(80);   
    }
    else {
        receive = 1;
        //LATD++;
        __delay_us(40);
    }
}

char readA0 (void) {
    char result;
    //LATD++;
    for (char i = 0; i < 8; i++) {
        while (PORTAbits.RA5 == 0){LATD = 8;};//wait for going to 1
        __delay_us(35);
        //LATD++;
        if (PORTAbits.RA5 == 0) {
            //LATD++;
            result&= ~(1 << (7 - i)); //Clear bit (7-b)
        } else {
            //LATD++;
            result|= (1 << (7 - i)); //Set bit (7-b)
            while (PORTAbits.RA5 == 1);//{LATD = 8;};//wait for going to 0
        }
    }
    return result;
}