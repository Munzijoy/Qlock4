/*
 * HW_RTC.cpp
 *
 *  Created on: 08.11.2016
 *      Author: t.linz
 */
#include "stm32f10x_rtc.h"
#include "HW_RTC.h"
#include "DeviceTime.h"

// ISRs needs to be written in a C section, not C++, thatswhy this is a C file,
// so no seperate sections are needed. Place all required ISRs here (names can
// be found in the asm startup file (*.s)

// Real Time Clock Interrupt handler, catching the secound interrupt only
void RTC_IRQHandler(void){
        // only catch the second interrupt
    if (RTC_GetITStatus(RTC_IT_SEC) != RESET){
        
        // refer to en.CD00207941.pdf
        uint32_t u32RtcCounter = RTC_GetCounter();
        gTimeStruct.tm_hour =  u32RtcCounter / 3600;
        gTimeStruct.tm_min = (u32RtcCounter % 3600) / 60;
        gTimeStruct.tm_sec = (u32RtcCounter % 3600) % 60;
        
        // Clear the RTC Second interrupt
        RTC_ClearITPendingBit(RTC_IT_SEC);
        // Wait until last write operation on RTC registers has finished
        RTC_WaitForLastTask();
    }
}
