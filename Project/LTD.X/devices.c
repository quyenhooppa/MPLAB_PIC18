#include "devices.h"

void runFan(uint32_t fan) {
    switch(fan) {
        case 1: 
            LED1 = (LED1 + 1) % 2;
            break;
        case 2: 
            LED2 = (LED2 + 1) % 2;
            break;
        case 3: 
            LED3 = (LED3 + 1) % 2;
            break;
        case 5:
            LED5 = (LED5 + 1) % 2;
            break;
        default:
            break;
    }
}

void readTemp(void) {
    stTemp = sdTemp;
    sdTemp = realTemp;
    if (stTemp == sdTemp) {
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
    }
}

void readHumid(void) {
    stHumid = sdHumid;
    sdHumid = realHumid;
    if (stHumid == sdHumid) {
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
    }
}

uint16_t speedFan3(int val) {
    uint16_t result = 0;
    if (val < 60) {
        result = 0;
    }
    else if (val < 70) {
        result = 500;
    } else if (val < 80) {
        result = 200;
    } else if (val < 90) {
        result = 100;
    } else {
        result = 50;
    }
    return result;
}
