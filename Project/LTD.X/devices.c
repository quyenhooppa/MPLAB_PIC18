#include "devices.h"

void runFan(uint32_t fan) {
    switch(fan) {
        case 1: 
            LED5 = (LED5 + 1) % 2;
            break;
        case 2: 
            LED3 = (LED3 + 1) % 2;
            break;
        case 3: 
            LED4 = (LED4 + 1) % 2;
            break;
        default:
            break;
    }
}

void readTemp(void) {
        switch (valTemp) {
            case normal:
                detect = 0;
                if (realTemp > MAX_TEMP) {
                    valTemp = bgLarger;
                    countTp = 0;
                }
                break;
            case bgLarger:
                countTp++;
                if (realTemp < MAX_TEMP) {
                    valTemp = normal;
                    countTp = 0;
                } else if (countTp > STABLE_PERIOD) {
                    valTemp = stable;
                    countTp = 0;
                    detect = 1;
                }
                break;
            case stable:
                if (realTemp < MAX_TEMP) {
                    valTemp = bgSmaller;
                    countTp = 0;
                }
                break;
            case bgSmaller:
                countTp++;
                if (realTemp >= MAX_TEMP) {
                    valTemp = stable;
                } else if (countTp > STABLE_PERIOD) {
                    valTemp = normal;
                    detect = 0;
                    countTp = 0; 
                }
                break;
        }
//    }
}

void readHumid(void) {
        switch (valHumid) {
            case normal:
                change = 0;
                if (realHumid > MAX_HUMID) {
                    valHumid = bgLarger;
                    countHd = 0;
                }
                break;
            case bgLarger:
                countHd++;
                if (realHumid < MAX_HUMID) {
                    valHumid = normal;
                    countHd = 0;
                } else if (countHd > STABLE_PERIOD) {
                    valHumid = stable;
                    countHd = 0;
                    change = 1;
                }
                break;
            case stable:
                if (realHumid < MAX_HUMID) {
                    valHumid = bgSmaller;
                    countHd = 0;
                }
                break;
            case bgSmaller:
                countHd++;
                if (realHumid >= MAX_HUMID) {
                    valHumid = stable;
                } else if (countHd > STABLE_PERIOD) {
                    valHumid = normal;
                    change = 0;
                    countHd = 0; 
                }
                break;
        }
//    }
}

uint16_t speedFan3(int val) {
    uint16_t result = 0;
    if (val < 50) {
        result = MAX_FAN_PERIOD / (0.5);
    }
    else if (val < 60) {
        result = MAX_FAN_PERIOD / (0.6);
    }
    else if (val < 70) {
        result = MAX_FAN_PERIOD / (0.7);
    } else if (val < 80) {
        result = MAX_FAN_PERIOD / (0.8);
    } else if (val < 90) {
        result = MAX_FAN_PERIOD / (0.9);
    } else {
        result = MAX_FAN_PERIOD;
    }
    return result;
}

void modifyMaxHumid (void) {
    switch (stModify) {
        case init:
            if (RA5Pressed == 0 && countPressed > 0) {
                modHumidVal++;
                stModify = iNor;
            }
            break;
        case iNor:
            if (countPressed == 0 || RA5Pressed == 1) {
                stModify = init;
            }
            if (countAuto > 0) {
                increaseTime = 1;
                stModify = iAuto;
            }
            break;
        case iAuto:
            if (countPressed == 0 || RA5Pressed == 1) {
                stModify = init;
            }
            if (increaseTime == 1) {
                increaseTime = 0;
                modHumidVal += 10;
            } 
            break;
    }
    if (modHumidVal >= 100) {
        modHumidVal = 0;
    }
}

void modifyMaxTemp (void) {
    switch (stModify) {
        case init:
            if (RA5Pressed == 0 && countPressed > 0) {
                modTempVal++;
                stModify = iNor;
            }
            break;
        case iNor:
            if (countPressed == 0 || RA5Pressed == 1) {
                stModify = init;
            }
            if (countAuto > 0) {
                increaseTime = 1;
                stModify = iAuto;
            }
            break;
        case iAuto:
            if (countPressed == 0 || RA5Pressed == 1) {
                stModify = init;
            }
            if (increaseTime == 1) {
                increaseTime = 0;
                modTempVal += 10;
            } 
            break;
    }
    if (modTempVal >= 100) {
        modTempVal = 0;
    }
}

void display (void) {
    mCURSOR_LINE1;
    LCDPutStr("MODIFY TEMP: ");
    mCURSOR_TEMP;
    LCDPutChar(modTempVal/10+'0');
    LCDPutChar(modTempVal%10+'0');
    if (state == chooseTemp) {
        LCDPutChar('<');
    }
    mCURSOR_LINE2;
    LCDPutStr("MODIFY HUMID: ");
    mCURSOR_HUMID;
    LCDPutChar(modHumidVal/10+'0');
    LCDPutChar(modHumidVal%10+'0');
    if (state == chooseHumid) {
        LCDPutChar('<');
    }
}

void stateDevices (void) {
    void(*pF)(uint32_t);
    pF = runFan;
    uint16_t speed, newSpeed;
    printTempHumid();
    int changeS0 = detect || period;
    int changeS1 = !detect && period;
        switch (heatSt) {
        case heater:
            if (changeS0 == 1) {
                heatSt = heatpump;
                uint32_t remove = findTask(2);
                period = 0;
                remove_timer(remove);
                LED3 = 0;
                LED7 = 0;
                LED8 = 1;
                register_timer(0, 500, pF, 3);
            }
                break;
        case heatpump:
                if (changeS1 == 1) {
                    heatSt = heater;
                    period = 0;
                    uint32_t remove = findTask(3);
                    remove_timer(remove);
                    LED4 = 0;
                    LED7 = 1;
                    LED8 = 0;
                    register_timer(0, 500, pF, 2);
                }
                break;
        } 
        switch(fan3St) {
            case off:
                //LED5 = 0;
                if (change == 1) {
                    fan3St = on;
                    speed = speedFan3(realHumid);
                    register_timer(0, speed, pF, 1);
                } 
                break;
            case on:
                if (change == 0) {
                    fan3St = off;
                    uint32_t remove = findTask(1);
                    remove_timer(remove);
                    LED5 = 0;
                } else if (realHumid > MAX_HUMID) {
                    newSpeed = speedFan3(realHumid);
                    if (newSpeed != speed) {
                        uint32_t remove = findTask(1);
                        remove_timer(remove);
                        register_timer(0, newSpeed, pF, 1);
                    }
                    speed = newSpeed;
                } else {
                    speed = speedFan3(realHumid);
                }
                break;
        }
}