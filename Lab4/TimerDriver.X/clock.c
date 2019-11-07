#include "clock.h"

void start_timer (void) {
    initTask();
    T0CONbits.TMR0ON = 1;
    //write to timer0 register
    TMR0H = 0xfd;
    TMR0L = 0x7f;
    
    T1CONbits.TMR1ON = 1;
    //write to timer1 register
    TMR1H = 0xff;
    TMR1L = 0xdf;
}

timestamp_t get_time (void) {
    return counterTime;
}

uint32_t register_timer (uint32_t delay, uint32_t period, timer_callback_t callback, void* arg) {
    int pos = -1;
    for (int i = 0; i < MAX_TASK; i++) {
        if (lsOfTask[i].pTask != NULL && lsOfTask[i].run != -1) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        return 0;
    }
    lsOfTask[pos].pTask = callback;
    lsOfTask[pos].delay = delay;
    lsOfTask[pos].period = period;
    lsOfTask[pos].run = 0;
    lsOfTask[pos].arg = (uint32_t)arg;
    lsOfTask[pos].next = -1;
    return pos + 1;
}

int remove_timer (uint32_t id) {
    if (id > MAX_TASK || id == 0) {
        return 0;
    }
    if (lsOfTask[id - 1].pTask == NULL && lsOfTask[id - 1].run ==  -1) {
        return 0;
    }
    uint32_t cur = lsOfTask[id - 1].next;
    while (cur != -1) {
        lsOfTask[cur].delay += lsOfTask[id - 1].delay;
        cur = lsOfTask[cur].next;
    }
    lsOfTask[id - 1].pTask = NULL;
    lsOfTask[id - 1].delay = 0;
    lsOfTask[id - 1].period = 0;
    lsOfTask[id - 1].run = -1;
    lsOfTask[id - 1].next = -1;   
    return 1;
}

void stop_timer (void) {
    T0CONbits.TMR0ON = 0;
    T1CONbits.TMR1ON = 0;
    //remove all the task 
    for (int i = 0; i < MAX_TASK; i++) {
        remove_timer(i + 1);
    }
}

int timer_ISR (void) {
    if (head == 0) {
        return 0;
    }
    struct task temp = lsOfTask[head - 1];
    if (temp.delay == 0) {
        temp.run = 1;
        if (temp.period != 0) {
            temp.delay = temp.period;
        }
    } else {
        temp.delay -= 1;
    }
    return 1;
}

void initTask(void) {
    for (int i = 0; i< MAX_TASK; i++) {
        lsOfTask[i].pTask = NULL;
        lsOfTask[i].delay = 0;
        lsOfTask[i].period = 0;
        lsOfTask[i].run = -1;  
        lsOfTask[i].next = -1;
    }
}

void addTaskExe (struct task tsk, uint32_t id) {//id equals index in arr - 1 
    if (head == 0) {
        head = id;
    } else if (lsOfTask[head - 1].next == -1) {
        if (lsOfTask[head - 1].delay > tsk.delay) {
            lsOfTask[head - 1].delay -= tsk.delay;
            tsk.next = head - 1;
            head = id;
        } else {
            tsk.delay -= lsOfTask[head - 1].delay;
            lsOfTask[head - 1].next = id - 1;
        }
    } else {
        uint32_t pre = head - 1;
        uint32_t cur = lsOfTask[pre].next;
        if (tsk.delay < lsOfTask[pre].delay) {
            lsOfTask[pre].delay -= tsk.delay;
            tsk.next = head - 1;
            head = id - 1;
        } else {
            int add = 0;
            while (cur != -1) {
                if (tsk.delay == lsOfTask[cur].delay) {
                    add = 1;
                    tsk.delay -= lsOfTask[cur].delay;
                    tsk.next = lsOfTask[cur].next;
                    lsOfTask[cur].next = id - 1;
                    break;
                } else if (tsk.delay < lsOfTask[cur].delay) {
                    add = 1;
                    lsOfTask[pre].next = id - 1;
                    tsk.next = cur;
                    lsOfTask[cur].delay -= tsk.delay;
                    break;
                } else {
                    tsk.delay -= lsOfTask[cur].delay;
                    pre = cur;
                    cur = lsOfTask[pre].next;
                }
            }
            if (add == 0) {
                lsOfTask[pre].next = id - 1;
                tsk.next = -1;
            } else {
                cur = lsOfTask[cur].next;
                if (cur == id - 1) {
                    cur = lsOfTask[cur].next;
                }
                while (cur != -1) {
                    lsOfTask[cur].delay -= tsk.delay;
                    cur = lsOfTask[cur].next;
                }
            }
        }
    }
}

void dispatch (void) {
    if (head != 0) {
        struct task temp = lsOfTask[head - 1]; 
        if (temp.run > 0) {
            (*(temp.pTask))(temp.arg);
            temp.run = 0;
            if (temp.period == 0) {
                remove_timer(head);
            } else {
                uint32_t id = head;
                head = temp.next;
                temp.next = -1;
                addTaskExe(temp, id);
            }
        }
    }
}