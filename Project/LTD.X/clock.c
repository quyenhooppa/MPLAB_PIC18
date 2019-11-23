#include "clock.h"

void start_timer (void) {
    T0CONbits.TMR0ON = 1;
    //write to timer0 register
    TMR0H = 0xfd;
    TMR0L = 0x0f;
    
    T1CONbits.TMR1ON = 1;
    //write to timer1 register
    TMR1H = 0xff;
    TMR1L = 0xdc;
}

void initTask(void) {
    for (int i = 0; i < MAX_TASK; i++) {
        lsOfTask[i].pTask = 0x0000;
        lsOfTask[i].delay = 0;
        lsOfTask[i].period = 0;
        lsOfTask[i].run = -1;  
        lsOfTask[i].next = -1;
    }
}

void register_timer (uint32_t delay, uint32_t period, timer_callback_t callback, uint32_t arg) {
    int pos = -1;
    for (int i = 0; i < MAX_TASK; i++) {
        if (lsOfTask[i].run == -1) {
            pos = i;
            break;
        }
    }
    if (pos != -1) {
        lsOfTask[pos].pTask = callback;
        lsOfTask[pos].delay = delay;
        lsOfTask[pos].period = period;
        lsOfTask[pos].run = 0;
        lsOfTask[pos].arg = arg;
        lsOfTask[pos].next = -1;
        addTaskExe(pos + 1);
    }
}

void remove_timer (uint32_t id) {
    if (id <= MAX_TASK && id != 0 && head > 0) {
        if (lsOfTask[id - 1].run !=  -1) {
            if  (id == head) {
                head = lsOfTask[head - 1].next + 1;
                lsOfTask[id - 1].pTask = 0x0000;
                lsOfTask[id - 1].delay = 0;
                lsOfTask[id - 1].period = 0;
                lsOfTask[id - 1].run = -1;
                lsOfTask[id - 1].next = -1;  
            } else {
                uint32_t pre = head - 1;
                uint32_t cur = lsOfTask[pre].next;
                while (cur != id - 1) {
                    pre  = cur;
                    cur = lsOfTask[pre].next;
                }
                lsOfTask[pre].next = lsOfTask[cur].next;
                    cur = lsOfTask[cur].next;
                lsOfTask[cur].delay += lsOfTask[id - 1].delay;
                lsOfTask[id - 1].pTask = 0x0000;
                lsOfTask[id - 1].delay = 0;
                lsOfTask[id - 1].period = 0;
                lsOfTask[id - 1].run = -1;
                lsOfTask[id - 1].next = -1;  
            }
        }
    }
}

void stop_timer (void) {
    T0CONbits.TMR0ON = 0;
    T1CONbits.TMR1ON = 0;
    //remove all the task 
    for (int i = 0; i < MAX_TASK; i++) {
        remove_timer(i + 1);
    }
}

void timer_ISR (void) {
    if (head > 0) {
        if (lsOfTask[head - 1].delay == 0) {
            lsOfTask[head - 1].run = 1;
            if (lsOfTask[head - 1].period != 0) {
                lsOfTask[head - 1].delay = lsOfTask[head - 1].period;
            }
        } else {
            lsOfTask[head - 1].delay -= 1;
        }
    }
}

void addTaskExe (uint32_t id) {//id equals index in arr - 1 
    if (head == 0) {
        head = id;
    } else if (lsOfTask[head - 1].next == -1) {
        if (lsOfTask[head - 1].delay > lsOfTask[id - 1].delay) {
            lsOfTask[head - 1].delay -= lsOfTask[id - 1].delay;
            lsOfTask[id - 1].next = head - 1;
            head = id;
        } else {
            lsOfTask[id - 1].delay -= lsOfTask[head - 1].delay;
            lsOfTask[head - 1].next = id - 1;
        }
    } else {
        uint32_t pre = head - 1;
        uint32_t cur = lsOfTask[pre].next;
        if (lsOfTask[id - 1].delay < lsOfTask[pre].delay) {
            lsOfTask[pre].delay -= lsOfTask[id - 1].delay;
            lsOfTask[id - 1].next = pre;
            head = id;
        } else {
            int add = 0;
            while (cur != -1) {
                if (lsOfTask[id - 1].delay == lsOfTask[cur].delay) {
                    add = 1;
                    lsOfTask[id - 1].delay -= lsOfTask[cur].delay;
                    lsOfTask[id - 1].next = lsOfTask[cur].next;
                    lsOfTask[cur].next = id - 1;
                    break;
                } else if (lsOfTask[id - 1].delay < lsOfTask[cur].delay) {
                    add = 1;
                    lsOfTask[pre].next = id - 1;
                    lsOfTask[id - 1].next = cur;
                    lsOfTask[cur].delay -= lsOfTask[id - 1].delay;
                    break;
                } else {
                    lsOfTask[id - 1].delay -= lsOfTask[cur].delay;
                    pre = cur;
                    cur = lsOfTask[pre].next;
                }
            }
            if (add == 0) {
                lsOfTask[pre].next = id - 1;
                lsOfTask[id - 1].next = -1;
            }
        }
    }
}

void dispatch (void) {
    if (head != 0) { 
        uint32_t id = head;
        if (lsOfTask[id - 1].run > 0) {
            void(*pF)(uint32_t);
            pF = lsOfTask[id - 1].pTask;
            uint32_t arg = lsOfTask[id - 1].arg;
            (*pF)(arg);
            if (lsOfTask[id - 1].period == 0) {
                //head = lsOfTask[id - 1].next;
                remove_timer(id);
            } else {
                head = lsOfTask[id - 1].next + 1;
                lsOfTask[id - 1].next = -1;
                addTaskExe(id);
            }
            lsOfTask[id - 1].run = 0;
        }
    }
}

