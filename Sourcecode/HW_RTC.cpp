/*
 * HW_RTC.cpp
 *
 *  Created on: 08.11.2016
 *      Author: t.linz
 */

#include "HW_RTC.h"
//#include "stm32f10x_nvic.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_rtc.h"

void RTC_Init(void){
/* CK_RTC clock selection */
RCC_APB1PeriphClockCmd( RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE 
);
PWR_BackupAccessCmd( ENABLE );  /* Allow access to BKP Domain */
BKP_DeInit(); /* Reset Backup Domain */
RCC_LSEConfig( RCC_LSE_ON ); /* Enable the LSE OSC */
while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
{} /* Wait till LSE is ready */
RCC_RTCCLKConfig( RCC_RTCCLKSource_LSE ); /* Select the RTC Clock Source */
RCC_RTCCLKCmd( ENABLE ); /* Enable the RTC Clock */
RTC_WaitForSynchro(); /* Wait for RTC registers synchronization */
/* Wait until last write operation on RTC registers has finished */
RTC_WaitForLastTask();
RTC_ITConfig( RTC_IT_SEC, ENABLE ); /* Enable the RTC Second interrupt 
*/
/* Wait until last write operation on RTC registers has finished */
RTC_WaitForLastTask();
/* Set RTC prescaler: set RTC period to 1sec */
/* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
RTC_SetPrescaler( 32767 );
/* Wait until last write operation on RTC registers has finished */
RTC_WaitForLastTask();
    
NVIC_InitTypeDef NVIC_InitStructure;
// Enable the RTC Interrupt
NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

}
