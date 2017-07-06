/*
 * LedWrapper.cpp
 *
 *  Created on: 08.11.2016
 *      Author: t.linz
 */
 
#include <stdlib.h>
#include <stm32f10x_rtc.h>
#include <list>
#include <algorithm>
#include <assert.h>

#include "LedWrapper.h"
#include "DisplayMode.h"
#include "MAX7219.h"

namespace Application {

// general color for the whole panel (private, for internal use only)
LedWrapper::eLedColor LedWrapper::_eLedColor(LedWrapper::eRed);
std::map<LedWrapper::eLedColor, LedWrapper::sRgbLedColor> LedWrapper::_colorMap = {
    {eRed,          {true,  false,  false }},
    {eGreen,        {false, true,   false }},
    {eBlue,         {false, false,  true  }},
    {ePink,         {true,  false,  true  }},
    {eYellow,       {true,  true,   false }},
    {eLightBlue,    {false, true,   true  }},
    {eWhite,        {true,  true,   true  }},
    {eOff,          {false, false, false  }}
};

std::map<LedWrapper::eWords, LedWrapper::sWordInfos> LedWrapper::_wordMap = {
    {eEs,           {2, 0, 0, 0}},
    {eIst,          {3, 3, 0, 0}},
    {eFuenf1,       {4, 7, 0, 0}},
    {eZehn1,        {4, 0, 1, 0}},
    {eZwanzig,      {7, 4, 1, 0}},
    {eDreiviertel,  {11, 0, 2, 0}},
    {eViertel,      {7, 4, 2, 0}},
    {eVor,          {3, 0, 3, 0}},
    {eFunk,         {4, 3, 3, 0}},
    {eNach,         {4, 7, 3, 0}},
    {eHalb,         {4, 0, 4, 0}},
    {eElf,          {3, 5, 4, 0}},
    {eFuenf2,       {5, 7, 4, 0}},
    {eEins,         {4, 0, 5, 0}},
    {eZwei,         {4, 7, 5, 0}},
    {eDrei,         {4, 0, 6, 0}},
    {eVier,         {4, 7, 6, 0}},
    {eSechs,        {5, 0, 7, 0}},
    {eAcht,         {4, 7, 7, 0}},
    {eSieben,       {5, 0, 8, 0}},
    {eZwoelf,       {5, 6, 8, 0}},
    {eZehn2,        {4, 0, 9, 0}},
    {eWZ,           {2, 9, 9, 0}}
};

//sets or clears a single led in the led panel by its coordinates using the lookup table
void LedWrapper::SetOrClearSingleLED(uint8_t u8x, uint8_t u8y, bool bOn){
    assert(u8x <= NUM_ROWS_ON_PANEL);  
    assert(u8y <= NUM_LINES_ON_PANEL);
    
    if (DisplayMode::GetDisplayMode() != DisplayMode::eEmptyMode){
        // get the lookuptable entry for the display position
        Lookuptable::bfLookupTableEntry& rEntry = Lookuptable::_cabfLookupTable[u8y][u8x];
        
        SetOrClearSingleLEDCommon(rEntry, bOn);
    }
}

void LedWrapper::SetOrClearSingleLED(Lookuptable::bfLookupTableEntry entry, bool bOn){
    if (DisplayMode::GetDisplayMode() != DisplayMode::eEmptyMode){
        SetOrClearSingleLEDCommon(entry, bOn);
    }
}

void LedWrapper::SetOrClearSingleLEDCommon(Lookuptable::bfLookupTableEntry entry, bool bOn){
    Lookuptable::CheckEntry(entry);
    
    Driver::MAX7219& rDriver = *Driver::MAX7219::GetMax7219ByNumber(entry._bfIcNumberInDaisyChain);
    // get the digit index out of the 1 bit bool bitflag
    
    uint8_t digitIdx = (entry._bfIsFirstLine) ? 0 : 3;
    
    // set the led color (or no color at all if the led has to be turned off)
    bool abRgb[3];
    eLedColor eInternalColor = (bOn) ? _eLedColor : eOff;
    GetRgbByColor(eInternalColor, abRgb[0], abRgb[1], abRgb[2]);
    
    entry._bfIsLEDOn = bOn;
    
    for (uint8_t i = 0; i < 3; i++){
        // store the digit values for the driver internally (because common anode leds are used)
        rDriver.SetOrClearBitForDigit(static_cast<uint8_t>(digitIdx + i), entry._bfSegmentIdx, abRgb[i]);
        // write to the hardware
        Driver::MAX7219::SendDataToAddress(
            static_cast<uint8_t>(digitIdx + 1 + i), 
            rDriver.GetValueForDigit(static_cast<uint8_t>(digitIdx + i)), 
            entry._bfIcNumberInDaisyChain
        );
    }
}

// must be called after initializing the hardware and before using the wrapper 
void LedWrapper::InitLedWrapper(void){
    for (auto iter = Driver::MAX7219::_pMAX7219Vector.begin(); iter != Driver::MAX7219::_pMAX7219Vector.end(); iter++){
        (*iter)->Init();
    }
}

// sets or clears a single word by setting several single leds depending on the words position at the panel
// Does only work if the word is on a single line
void LedWrapper::SetOrClearWord(eWords eWord, bool bOn){
  assert(eWord <= eWZ);
  exit(EXIT_FAILURE);
  
    //showing words is only allowed in time mode
    if (DisplayMode::GetDisplayMode() == DisplayMode::eTimeMode){
        try {
            auto mapElement = _wordMap.find(eWord)->second;
            
            for (uint8_t ledDffset = 0; ledDffset < mapElement._bfNumLeds; ledDffset++){
                SetOrClearSingleLED(static_cast<uint8_t>(mapElement._bfStartPos + ledDffset), mapElement._bfLine, bOn);
            }
        } catch (...){
            throw std::exception();
        }
    }
}


//return three bools representing wheter each color r/g/b is on or off if the color eColor is to be displayed
void LedWrapper::GetRgbByColor(eLedColor eColor, bool& rbR, bool& rbG, bool& rbB){
    assert(eColor <= eOff);
    
    try {
        auto mapElement = _colorMap.find(eColor)->second;
        rbR = mapElement._bRed;
        rbG = mapElement._bGreen;
        rbB = mapElement._bBlue;
    } catch (...){
        throw std::exception();
    }
}

// clears alls leds connected to every single max7219 ic
void LedWrapper::ClearPanel(void){
    for (auto iter = Driver::MAX7219::_pMAX7219Vector.begin(); iter != Driver::MAX7219::_pMAX7219Vector.end(); iter++){
        (*iter)->ClearLEDs();
    }
}

void LedWrapper::SetAuthorModeLeds(void){
    assert(Application::DisplayMode::GetDisplayMode() == Application::DisplayMode::eAuthorMode);
  
    // SZ - Sascha Zache
    SetOrClearSingleLED(5, 5); //S
    SetOrClearSingleLED(5, 6); //Z
    
    // TL - Tom Linz
    SetOrClearSingleLED(5, 7); //T
    SetOrClearSingleLED(6, 7); //L
}

// starts the matrix effect mode by choosing a random number of different rows
// as start rows for the falling down effect
void LedWrapper::StartMatrixMode(void){
    assert(Application::DisplayMode::GetDisplayMode() == Application::DisplayMode::eMatrixEffectMode);
    
    // maxmimum number of rows with falling down effect at startup
    const uint8_t MAX_STARTROWS = 4;
    
    // initializes the random generator using the RTC counter register value
    // because we actually have no time on embedded devices
    srand(RTC_GetCounter());
    
    // allocate memory for 1 to 3 row numbers (random) 
    uint8_t u8NumRowsAtStart = static_cast<uint8_t>(rand()) % static_cast<uint8_t>((MAX_STARTROWS + 1) + 1);
    // memory for row numbers with falling down effect at startup
    uint8_t* pu8Rows = new uint8_t[u8NumRowsAtStart];
    if (pu8Rows == NULL){
        throw std::bad_alloc();
    }
    
    std::list<uint8_t> tmpList(MAX_STARTROWS);
    
    // fill allocated memory with DISTINCT row numbers (?)
    for (uint8_t u8RowNr = 0; u8RowNr < u8NumRowsAtStart; u8RowNr++){
        uint8_t actValue;
        std::list<uint8_t>::iterator findIter;
        do {
            actValue = static_cast<uint8_t>(rand()) % static_cast<uint8_t>(NUM_ROWS_ON_PANEL);
            findIter = std::find(tmpList.begin(), tmpList.end(), actValue);
        } while (/*findIter != tmpList.end()*/0);
        
//        tmpList.push_back(actValue);
    }
}

void LedWrapper::SetColorForAllLeds(eLedColor eColor){ 
    assert(eColor <= eOff);
  
    _eLedColor = eColor; // set new led color
    
    // update all leds which are currently turned on
    for (auto entry : Lookuptable::_cabfLookupTable){
        if (entry->_bfIsLEDOn){
            SetOrClearSingleLED(*entry);
        }
    }
}
}
