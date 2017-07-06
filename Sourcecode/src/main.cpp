//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "LedWrapper.h"
#include "HW_RCC.h"
#include "HW_SPI.h"
#include "HW_RTC.h"
#include "DisplayMode.h"
#include <stdlib.h>

// ----------------------------------------------------------------------------
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

void SysSysSystemErrorHandler(void){
    for(;;);
}

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[]){
    Hardware::HW_RCC::Init();
//    Hardware::HW_RTC::Init();
    Hardware::HW_SPI::Init();
    
    RCC_ClocksTypeDef Clocks;
    RCC_GetClocksFreq(&Clocks);
    SysTick_Config(Clocks.HCLK_Frequency / 1000 - 1 );  // 1000 Hz ( T=1ms)
    
    atexit(SysSysSystemErrorHandler);
    
    Application::LedWrapper::InitLedWrapper();
    Application::LedWrapper::SetColorForAllLeds(Application::LedWrapper::eYellow);
    
    Application::DisplayMode::SetAuthorMode();
    Application::DisplayMode::SetEmptyMode();
    
//    Application::DisplayMode::SetMatrixEffectMode();
//    Application::DisplayMode::SetEmptyMode();
    
    Application::DisplayMode::SetTimeMode();
    
    Application::LedWrapper::SetOrClearWord(Application::LedWrapper::eDrei);
    Application::LedWrapper::SetOrClearWord(Application::LedWrapper::eSechs);
    
    while(1){}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
