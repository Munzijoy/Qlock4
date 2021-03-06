/*
 * DisplayMode.cpp
 *
 *  Created on: 10.11.2016
 *      Author: t.linz
 */
 
#include "DisplayMode.h"
#include "LedWrapper.h"

namespace Application {

DisplayMode::eDisplayMode DisplayMode::_eDisplayMode(DisplayMode::eEmptyMode);

//Sets the display to author mode
void DisplayMode::SetAuthorMode(void){
    _eDisplayMode = eAuthorMode;
    Application::LedWrapper::ClearPanel();  
    Application::LedWrapper::SetAuthorModeLeds();
}


// Clears the whole panel and sets display mode to eEmpty
void DisplayMode::SetEmptyMode(){
    _eDisplayMode = eEmptyMode;
    Application::LedWrapper::ClearPanel();
}

// sets the panel into the standard mode where the time is displayed
void DisplayMode::SetTimeMode(void){
    _eDisplayMode = eTimeMode;
    Application::LedWrapper::ClearPanel();
}

void DisplayMode::SetMatrixEffectMode(void){
    _eDisplayMode = eMatrixEffectMode;
    Application::LedWrapper::ClearPanel();
    Application::LedWrapper::StartMatrixMode();
}
}
