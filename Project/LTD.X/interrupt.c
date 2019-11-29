#include "interrupt.h"

void __interrupt () deviceInterrupt(void) {
    //timer 1 interrupt 
    if (PIR1bits.TMR1IF == 1 && PIE1bits.TMR1IE == 1) {
        PIR1bits.TMR1IF = 0;//clear overflow flag
        //write to timer1 register
        TMR1H = 0xff;
        TMR1L = 0xdc;
        msCounter++;
        count10ms--;
        if (count10ms <= 0) {
            button();
            count10ms = 10;
            readTemp();
            readHumid();
        }
        if (msCounter >= 1000) {
            msCounter = 0;
            counter = (counter + 1) % (PERIOD / 1000);
            period = (counter == (PERIOD/1000 - 1)) ? 1 : 0;
            if (read == 1) {
                readTempAndHumid();
            }
        }
        timer_ISR();
    }
}
