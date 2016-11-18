/*
 * HW_RTC.cpp
 *
 *  Created on: 08.11.2016
 *      Author: t.linz
 */
#include "stm32f10x_rtc.h"

void RTC_IRQHandler(void){
    if (RTC_GetITStatus(RTC_IT_SEC) != RESET){
        static volatile uint8_t i = 0;
        i++;
        if (i == 60){
            i = 0;
        }
        // Clear the RTC Second interrupt
        RTC_ClearITPendingBit(RTC_IT_SEC);
        // Wait until last write operation on RTC registers has finished
        RTC_WaitForLastTask();
    } 
}
