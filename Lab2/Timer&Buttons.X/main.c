/*
 * File:   main.c
 * Author: quyenhooppa
 *
 * Created on September 15, 2019, 4:45 PM
 */

//Configuration 
#ifdef _18F8722
#pragma config  OSC = HSPLL
#pragma config 	FCMEN = OFF
#pragma config 	IESO = OFF
#pragma config 	PWRT = OFF
#pragma config 	BOREN = OFF
#pragma config 	WDT = OFF
#pragma config 	MCLRE = ON
#pragma config 	LVP = OFF
#pragma config 	XINST = OFF
#endif

#include <xc.h>
#include <pic18f8722.h>

#define CLOCK 10 //clock oscillate (ms)
#define SHORTER 1000 
#define LONGER 3000
#define SLOWER 500 
#define FASTER 100 

int iCount = 0;
int dCount = 0;
int countSlow = 0;
int countFast = 0;
int changeSlow = 0;
int changeFast = 0;
char firstReadRA5 = 1;
char secondReadRA5 = 1;
char firstReadRB0 = 1;
char secondReadRB0 = 1;

void oscillationInitialize(void) {
    OSCCON = 0b01110111; //oscillation 8MHz 
    OSCTUNE = 0b00001111;
}

int defineTMR0Register(void) {
    return 256 - (CLOCK * 2000) / (int)128; 
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

int readIButton(void) {
    firstReadRA5 = secondReadRA5;
    secondReadRA5 = PORTAbits.RA5;
    if (firstReadRA5 == secondReadRA5) {
        if (firstReadRA5 == 0) {
            return 1;
        }
        else {
            return 2;
        }
    }
   return 0; 
}

int readDButton (void) {
    firstReadRB0 = secondReadRB0;
    secondReadRB0 = PORTBbits.RB0;
    if (firstReadRB0 == secondReadRB0) {
        if (firstReadRB0 == 0) {
            return 1;
        }
        else {
            return 2;
        }
    }
    return 0;
}

void button (void) {
    int iButton = readIButton();
    int dButton = readDButton();
    if (iButton == 1) {
        iCount++;
        if (iCount > SHORTER / CLOCK) {
            countSlow++;
            if (countSlow > SLOWER / CLOCK) {
                changeSlow = 1;
                countSlow = 0;
            }
        }
        if (iCount > LONGER / CLOCK) {
            countFast++;
            if (countFast > FASTER / CLOCK) {
                changeFast = 1;
                countFast = 0;
            }
        }
    }
    else if (dButton == 1) {
        dCount++;
        if (dCount > SHORTER / CLOCK) {
            countSlow++;
            if (countSlow > SLOWER / CLOCK) {
                changeSlow = 1;
                countSlow = 0;
            }
        }
        if (dCount > LONGER / CLOCK) {
            countFast++;
            if (countFast > FASTER / CLOCK) {
                changeFast = 1;
                countFast = 0;
            }
        }
    }
    else if (iButton == 2 || dButton == 2) {
        iCount = 0;
        dCount = 0;
        countFast = 0;
        changeFast = 0;
        countSlow = 0;
        changeSlow = 0;
    }
}

void __interrupt () deviceInterrupt(void) {
    //TMR0L = 100;
    if (INTCONbits.TMR0IF == 1) {
        INTCONbits.TMR0IF = 0;
        TMR0L = defineTMR0Register();
        button();
    }
}

void main(void) {
    enum State{init, iNormal, iFast, iSlow, dNormal, dFast, dSlow} state;
    oscillationInitialize();
    timerInitialize();
    buttonInitialize();
    ledInitialize();
    state = init;
    while (1) {
        switch (state) {
            case init:
                countFast = 0;
                countSlow = 0;
                if (iCount > 0) {
                    LATD++;
                    state = iNormal;
                }
                else if (iCount == 0 && dCount > 0) {
                    LATD--;
                    state = dNormal;
                }
                break;
            case iNormal:
                if (iCount == 0) {
                    state = init;
                }
                if (countSlow > 0) {
                    changeSlow = 1;
                    state = iSlow;
                } 
                break;
            case iSlow:
                if (iCount == 0) {
                    state = init;
                }
                if (changeSlow == 1) {
                    LATD++;
                    changeSlow = 0;
                }
                if (countFast > 0) {
                    changeFast = 1;
                    state = iFast;
                }
                break;
            case iFast:
                if (iCount == 0) {
                    state = init;
                }
                if (changeFast == 1) {
                    LATD++;
                    changeFast = 0;
                }
                break;
            case dNormal:
                if (dCount == 0 || iCount > 0) {
                    state = init;
                }
                if (countSlow > 0) {
                    changeSlow = 1;
                    state = dSlow;
                } 
                break;
            case dSlow:
                if (dCount == 0 || iCount > 0) {
                    state = init;
                }
                if (changeSlow == 1) {
                    LATD--;
                    changeSlow = 0;
                }
                if (countFast > 0) {
                    changeFast = 1;
                    state = dFast;
                }
                break;
            case dFast:
                if (dCount == 0 || iCount > 0) {
                    state = init;
                }
                if (changeFast == 1) {
                    LATD--;
                    changeFast = 0;
                }
                break;  
        }
    }
    return;
}
