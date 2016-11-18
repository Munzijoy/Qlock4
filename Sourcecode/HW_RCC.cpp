/*
 * HW_RCC.cpp
 *
 *  Created on: 27.10.2016
 *      Author: t.linz
 */

#include "HW_RCC.h"

namespace Hardware {

void RCC_Configuration(void){

        /* RCC system reset(for debug purpose) */
        RCC_DeInit();

        /* Enable HSE */
        RCC_HSEConfig(RCC_HSE_ON);

        /* Wait till HSE is ready */
        ErrorStatus HSEStartUpStatus = RCC_WaitForHSEStartUp();

        if(HSEStartUpStatus == SUCCESS)
        {
            /* HCLK = SYSCLK */
            RCC_HCLKConfig(RCC_SYSCLK_Div1); 

            /* PCLK2 = HCLK */
            RCC_PCLK2Config(RCC_HCLK_Div1); 

            /* PCLK1 = HCLK/2 */
            RCC_PCLK1Config(RCC_HCLK_Div2);

            /* Flash 2 wait state: required at operation of 72MHz */
            FLASH_SetLatency(FLASH_Latency_2);
            /* Enable Prefetch Buffer */
            FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

            /* PLLCLK = 8MHz * 9 = 72 MHz */
            RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

            /* Enable PLL */ 
            RCC_PLLCmd(ENABLE);

            /* Wait till PLL is ready */
            while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
            {
            }
            /* Select PLL as system clock source */
            RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

            /* Wait till PLL is used as system clock source */
            while(RCC_GetSYSCLKSource() != 0x08)
            {
            }
        }
        
        // Enable peripheral Clocks
        /* Enable GPIO clock */
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
        /* Enable SPI clock  */
        RCC_APB1PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  
        
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_SPI1, ENABLE);
       
}

}
