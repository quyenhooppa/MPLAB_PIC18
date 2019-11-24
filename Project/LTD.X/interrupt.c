#include "interrupt.h"

void __interrupt () deviceInterrupt(void) {
    //timer 0 interrupt 
    if (INTCONbits.TMR0IF == 1 && INTCONbits.TMR0IE == 1) {
        INTCONbits.TMR0IF = 0;//clear overflow flag
        //write to timer0 register
        TMR0H = 0xfd;
        TMR0L = 0x0f;
        //count++;
        readTemp();
        readHumid();
    }
    
    //timer 1 interrupt 
    if (PIR1bits.TMR1IF == 1 && PIE1bits.TMR1IE == 1) {
        PIR1bits.TMR1IF = 0;//clear overflow flag
        //write to timer1 register
        TMR1H = 0xff;
        TMR1L = 0xdc;
        msCounter++;
        if (msCounter == 1000) {
            read = 1;
            //LATD++;
//            num = (num + 1) % NUM;
//            realTemp = arrTemp[num];
//            realHumid = arrHumid[num];
//            //realTemp = 29;
            msCounter = 0;
            counter = (counter + 1) % (PERIOD / 1000);
            period = (counter == (PERIOD/1000 - 1)) ? 1 : 0;
        }
        timer_ISR();
    }
}
