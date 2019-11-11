#include "task.h"

void initStateLed(void) {
    LED0 = 0;
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
    LED5 = 0;
    LED6 = 0;
    LED7 = 0;
}

void blink (uint32_t led) {
    switch (led) {
        case 0: 
            LED0 = (LED0 + 1) % 2;
            break;
        case 1: 
            LED1 = (LED1 + 1) % 2;
            break;
        case 2: 
            LED2 = (LED2 + 1) % 2;
            break;
        case 3: 
            LED3 = (LED3 + 1) % 2;
            break;        
        case 4: 
            LED4 = (LED4 + 1) % 2;
            break;
        case 5: 
            LED5 = (LED5 + 1) % 2;
            break;        
        case 6: 
            LED6 = (LED6 + 1) % 2;
            break;        
        case 7: 
            LED7 = (LED7 + 1) % 2;
            break; 
    }
}

void printLCD (uint32_t num) {
    LCDPutInst(LCD_CURSOR_LINE1);
    int numOfDigit = 1;
    char arr[16];
    num = get_time();
    int temp = num;
    while (num != 0) {
        numOfDigit++;
        arr[16 - numOfDigit] = temp % 10;
        temp = temp / 10;
    }
    for (int i = num; i > 0; i--) {
        LCDPutChar(arr[num -i]);
    }
}

void print10msInterrupt(uint32_t num) {
    LCDPutInst(LCD_CURSOR_LINE2);
    LCDPutChar('T');
    LCDPutChar(':');
    LCDPutChar(' ');
    LCDPutInst(0xC3);
    LCDPutChar(num%10);
    int numOfDigit = 1;
    char arr[16];
    num = get_time();
    int temp = num;
    while (num != 0) {
        numOfDigit++;
        arr[16 - numOfDigit] = temp % 10;
        temp = temp / 10;
    }
    //LCDPutStr(arr);
}
