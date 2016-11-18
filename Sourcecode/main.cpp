#include "LedWrapper.h"
#include "HW_RCC.h"
#include "HW_SPI.h"
#include "HW_RTC.h"
#include "Develop.h"

void Delay(__IO uint32_t nCount){
  for(; nCount != 0; nCount--);
}

// entry point of the application
int main(void){
    Hardware::RCC_Configuration();
    Hardware::spi1_init();
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
    
    RTC_Init();
    
    LedWrapper::InitLedWrapper();
    LedWrapper::SetColorForAllLeds(LedWrapper::eYellow);
    
    LedWrapper::SetOrClearWord(LedWrapper::eDrei, true);
    LedWrapper::SetOrClearWord(LedWrapper::eSechs, true);
    
    for(;;);
}
