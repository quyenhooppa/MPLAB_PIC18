#include "dht.h"

char getByteData (void) {
    char result;
    char i, j;
    unsigned int timeOut;
    for (j = 0; j < 8; j++) {
        while (DHT_IN == 0) { 
            if (timeOut == 0) { 
                return 0;
            }
            timeOut--;
        }//wait for going to 1
        __delay_us(30);
        if (DHT_IN == 0) {
            //LATD++;
            i &= ~(1 << (7 - j)); //Clear bit (7-b)
            //result = (result << 1);
        } else {
            //LATD++;
            i |= (1 << (7 - j)); //Set bit (7-b)
            //result = (result << 1) | 0x01;
            timeOut = TIME_OUT;
            while (DHT_IN == 1) {
                if (timeOut == 0) { 
                return 0;
                }
                timeOut--;
            }//wait for going to 0
        }
    }
    //LATD = 10;
    //return result;
    return i;
}

int readDHT (void) {
    unsigned int timeOut = TIME_OUT;
    DHT_DIRECTION = 0;
    DHT_OUT = 0;
    __delay_ms(20);
    
    DHT_OUT = 1;
    __delay_us(20);
    DHT_DIRECTION = 1;
    
    while(DHT_IN & 1) {
        if(timeOut == 0) {
            return 0;
        }
        timeOut--;
    }
    
    
    timeOut = TIME_OUT;
    while(!DHT_IN & 1) {
        if(timeOut == 0) {
            return 0;
        }
        timeOut--;
    }
    
    timeOut = TIME_OUT;
    while(DHT_IN & 1) {
        if(timeOut == 0) {
            return 0;
        }
        timeOut--;
    }
    
//    LCDPutInst(0x87);
//    LCDPutStr("OK");
    dhtData[0] = getByteData();
    dhtData[1] = getByteData();
    dhtData[2] = getByteData();
    dhtData[3] = getByteData();
    dhtData[4] = getByteData();
    
    if((char)(dhtData[0] + dhtData[1] + dhtData[2] + dhtData[3]) & 0xFF != dhtData[4] )
        return 0;
    return 1;  
}

void readTempAndHumid (void) {
    //LCDPutInst(0x88);
    //LCDPutStr("OK");
    int check = readDHT();
    if (check == 0) {
        realTemp = ERROR;
        realHumid = ERROR;
        error = 1;
    } else {
        realTemp = (int)dhtData[2];
        realHumid = (int)dhtData[0];
    }
}

//void readA0(void) {
//    switch(dhtA0State) {
//        case IDLE:
//            if (dhtCounterA0 >= 800000) {
//                dhtA0State = SEND0;
//                dhtCounterA0 = 0;
//                pinA0 = 0;
//                A0 = 0;
//            }
//            break;
//        case SEND0:
//            if (dhtCounterA0 > 18010) {
//                dhtA0State = SEND1;
//                A0 = 1;
//                dhtCounterA0 = 0;
//            }
//            break;
//        case SEND1:
//            if (dhtCounterA0 > 40) {
//                dhtA0State = SEND1;
//                pinA0 = 1;
//                dhtCounterA0 = 0;
//            }
//            break;
//        case REPLY0:
//            if (dhtCounterA0 < 80) {
//                if (A0 == 1) {
//                    dhtA0State = IDLE;
//                    errorA0 = 1;
//                    dhtCounterA0 = 0;
//                    pinA0 = 0;
//                }
//            }
//            else {
//                if (A0 == 1) {
//                    dhtA0State = REPLY1;
//                }
//                else {
//                    dhtA0State = IDLE;
//                    errorA0 = 1;
//                    pinA0 = 0;
//                }
//                dhtCounterA0 = 0;
//            }
//            break;
//        case REPLY1:
//            if (dhtCounterA0 < 80) {
//                if (A0 == 0) {
//                    dhtA0State = IDLE;
//                    errorA0 = 1;
//                    dhtCounterA0 = 0;
//                    pinA0 = 0;
//                }
//            }
//            else {
//                if (A0 == 0) {
//                    dhtA0State = TRANSMIT;
//                }
//                else {
//                    dhtA0State = IDLE;
//                    errorA0 = 1;
//                    pinA0 = 0;
//                }
//                dhtCounterA0 = 0;
//            }
//            break;
//        case TRANSMIT:
//            if (dhtCounterA0 < 50) {
//                if (A0 == 1) {
//                    dhtA0State = IDLE;
//                    errorA0 = 1;
//                    dhtCounterA0 = 0;
//                    pinA0 = 0;
//                }
//            }
//            else {
//                if (A0 == 1) {
//                    dhtA0State = RECEIVE1;
//                }
//                else {
//                    dhtA0State = IDLE;
//                    errorA0 = 1;
//                    pinA0 = 0;
//                }
//                dhtCounterA0 = 0;
//            }
//            break;
//        case RECEIVE1:
//            if (A0 == 0) {
//                if (indxA0 >= 5) {
//                    dhtA0State = TERMINATE;
//                }
//                else {
//                    if (dhtCounterA0 > 70) {
//                        dhtA0State = IDLE;
//                        errorA0 = 1;
//                        pinA0 = 0;
//                    } else if (dhtCounterA0 < 40) {
//                        dhtA0State = TRANSMIT;
//                        dataA0[indxA0] = (dataA0[indxA0] << 1);
//                        numOfBitA0++;
//                        if (numOfBitA0 >= 8) {
//                            indxA0++;
//                            numOfBitA0 = 0;
//                        }
//                    } else {
//                        dhtA0State = TRANSMIT;
//                        dataA0[indxA0] = (dataA0[indxA0] << 1) | 0x01;
//                        numOfBitA0++;
//                        if (numOfBitA0 >= 8) {
//                            indxA0++;
//                            numOfBitA0 = 0;
//                        } 
//                    }
//                dhtCounterA0 = 0;
//                }
//            }
//            break;
//        case TERMINATE:
//            if (((dataA0[0]+dataA0[1]+dataA0[2]+dataA0[3])&0xff) == dataA0[4]) {
//                tempA0 = dataA0[2];
//                humidA0 = dataA0[0];  
//                pinA0 = 0;
//                done = 0;
//            } else {
//                errorA0 = 1;
//            }
//            dhtA0State = IDLE;
//            break;
//    }
//}