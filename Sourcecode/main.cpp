/*
 * main.cpp
 *
 *  Created on: 04.10.2016
 *      Author: t.linz
 */

#include "LedWrapper.h"
#include "HW_RCC.h"
#include "HW_SPI.h"
#include "HW_RTC.h"
#include "DisplayMode.h"
#include <stdlib.h>

void ExitHandler(void){
    for(;;);
}

// entry point of the application
int main(void){
    Hardware::HW_RCC::Init();
    Hardware::HW_SPI::Init();
    Hardware::HW_RTC::Init();
    
    atexit(ExitHandler);
    
    Application::LedWrapper::InitLedWrapper();
    Application::LedWrapper::SetColorForAllLeds(Application::LedWrapper::eYellow);
    
    Application::DisplayMode::SetAuthorMode();
    Application::DisplayMode::SetEmptyMode();
    
    Application::DisplayMode::SetMatrixEffectMode();
    Application::DisplayMode::SetEmptyMode();
    
    Application::DisplayMode::SetTimeMode();
    
    Application::LedWrapper::SetOrClearWord(Application::LedWrapper::eDrei);
    Application::LedWrapper::SetOrClearWord(Application::LedWrapper::eSechs);
    
    for(;;);
}
