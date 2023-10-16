/*
 * File:   timer_handling.c
 * Author: M67252
 *
 * Created on August 29, 2023, 2:36 PM
 */


#include <xc.h>
#include"timer_handling.h"

volatile uint16_t u16Time = 0;
bool bMyTimout = false;

void timerCB(void) {
   asm("NOP"); 
    if (u16Time) {
        u16Time--;
        if (u16Time == 0)bMyTimout = true;
    }
}

bool isTimeout(void) {
    if (bMyTimout) {
        bMyTimout = false;
        return true;
    }
    return false;
}

void setTimout(uint16_t mSec) {
    u16Time = mSec;
}
