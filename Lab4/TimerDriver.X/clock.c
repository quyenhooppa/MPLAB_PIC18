#include "clock.h"

void start_timer (void) {
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
    if (listOfTask.size > MAX_TASK) {
        return 0;
    }
    struct task* temp;
    temp->pTask = callback;
    temp->delay = delay;
    temp->period = period;
    temp->run = 0;
    temp->led = (int)(arg);
    temp->next = NULL;
    if (listOfTask.size == 0) { //current have no task
        listOfTask.head = temp;
        listOfTask.tail = temp;
    }
    else {
       (listOfTask.tail)->next = temp;
       listOfTask.tail = temp; 
    }
    listOfTask.size++;
    return listOfTask.size;
}

int remove_timer (uint32_t id) {
    if (id > MAX_TASK || id == 0 || id > listOfTask.size) {
        return 0;
    }
    listOfTask.size--;
    struct task* temp;
    if (id == 1) { //first task in the list
        temp = listOfTask.head;
        listOfTask.head = temp->next;
        temp->next = NULL;
    }
    else {
        int pos = 1;
        //find the task before the removed 
        while (pos < id - 1) {
            temp = temp->next;
            pos++;
        }
        struct task* del = temp->next;//removed task
        temp->next = del->next;
        del->next = NULL;
        if (temp->next == NULL) { //last task in the list
            listOfTask.tail = temp;
        }
    }
    return 1;
}

void stop_timer (void) {
    T0CONbits.TMR0ON = 0;
    T1CONbits.TMR1ON = 0;
    //remove all the task 
    int empty = 0;
    empty = remove_timer(1);
    while (empty != 0) {
        remove_timer(1);
    }
}

int timer_ISR (void) {
    if (listOfExe.head == NULL) {
        return 0;
    }
    struct task* temp = listOfExe.head;
    if (temp->delay == 0) {
        temp->run += 1;
        if (temp->period != 0) {
            temp->delay = temp->period;
        }
    } else {
        temp->delay -= 1;
    }
    return 1;
}

void addTaskExe (struct task* tsk) {
    if (listOfExe.size == 0) {
        listOfExe.head = tsk;
    } else if (listOfExe.size == 1) {
        struct task* temp = listOfExe.head;
        if (tsk->delay >= temp->delay) {
            temp->next = tsk;
            tsk->delay -= temp->delay;
        } else {
            tsk->next = temp;
            listOfExe.head = tsk;
            temp->delay -= tsk->delay;
        }
    } else {
        struct task* tempPrev = listOfExe.head;
        struct task* temp = tempPrev->next;
        if (tsk->delay < tempPrev->delay) {
            tsk->next = tempPrev;
            listOfExe.head = tsk;
            tempPrev->delay -= tsk->delay;
        } else {
            int add = 0;
            int pos = 0;
            while (add != 1 && temp != NULL) {
                pos++;
                if (tsk->delay == temp->delay) {
                    add = 1;
                    tsk->next = (temp->next)->next;
                    temp->next = tsk;  
                    tsk->delay = 0;
                } else if (tsk->delay < temp->delay) {
                    add = 1;
                    tsk->next = temp;
                    tempPrev->next = tsk;
                }
                else {
                    add = 1;
                    tsk->delay -= temp->delay;
                    tempPrev = temp;
                    temp = temp->next;
                }
            }
            if (add == 0) {
                temp->next = tsk;
            } else {
                while (temp != NULL) {
                    temp->delay -= tsk->delay;
                    temp->next = temp;
                }
            }   
        }
    }
    listOfExe.size++;
}

void deleteTask (struct task* tsk) {
    struct task* temp = listOfTask.head;
    int pos = 0;
    while (temp != NULL) {
        pos++;
        if (temp == tsk) {
            remove_timer(pos);
            temp = NULL;
        } else {
            temp = temp->next;
        }
    }
    temp = listOfExe.head;
    pos = 0;
    while (temp != NULL) {
        pos++;
        if (temp == data) {
            break;
        }
    }
    if (temp != NULL) {
        
    }
}

void dispatch (void) {
    if (listOfExe.head != NULL) {
        struct task* temp = listOfExe.head;
        if (temp->run > 0) {
            (*(temp->pTask))(temp->led);
            temp->run = 0;
            if (temp->period == 0) {
                deleteTask(temp);
            } else {
                addTaskExe(temp);
            }
            LCDPutInst(LCD_CURSOR_LINE2);
            printLCD(counterTime);
        }
    }
}

void printLCD (unsigned long int num) {
    int numOfDigit = 1;
    char arr[16] = {'\0'};
    int temp = num;
    while (num != 0) {
        numOfDigit++;
        arr[16 - numOfDigit] = temp % 10;
        temp = temp / 10;
    }
    for (int i = num; i>0; i--) {
        LCDPutChar(arr[num -i]);
    }
}