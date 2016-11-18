/*
 * LedWrapper.cpp
 *
 *  Created on: 08.11.2016
 *      Author: t.linz
 */
 
#include "LedWrapper.h"
#include "LookupTable.h"
#include "DisplayMode.h"
#include "MAX7219.h"
#include <stdlib.h>
#include <stm32f10x_rtc.h>
#include <list>
#include <algorithm>

namespace Application {

// general color for the whole panel (private, for internal use only)
LedWrapper::eLedColor LedWrapper::_eLedColor(LedWrapper::eRed);

//sets or clears a single led in the led panel by its coordinates using the lookup table
void LedWrapper::SetOrClearSingleLED(uint8_t u8x, uint8_t u8y, bool bOn){
    if (DisplayMode::GetDisplayMode() != DisplayMode::eEmptyMode){
        // get the lookuptable entry and the corresponding ic driver
        const Lookuptable::bfLookupTableEntry& rEntry = Lookuptable::_cabfLookupTable[u8y][u8x];
        Driver::MAX7219& rDriver = Driver::MAX7219::GetMax7219ByNumber(rEntry._bfIcNumberInDaisyChain);
        // get the digit index out of the 1 bit bool bitflag
        uint8_t digitIdx = (rEntry._bfIsFirstLine) ? 0 : 3;
        
        // set the led color (or no color at all if the led has to be turned off)
        bool abRgb[3];
        eLedColor eInternalColor = (bOn) ? _eLedColor : eOff;
        GetRgbByColor(eInternalColor, abRgb[0], abRgb[1], abRgb[2]);
        
        for (uint8_t i = 0; i < 3; i++){
            // store the digit values for the driver internally (because common anode leds are used)
            rDriver.SetOrClearBitForDigit(digitIdx + i, rEntry._bfSegmentIdx, abRgb[i]);
            // write to the hardware
            Driver::MAX7219::SendDataToAddress(digitIdx + 1 + i, rDriver.GetValueForDigit(digitIdx + i), rEntry._bfIcNumberInDaisyChain);
        }
    }
}

// must be called after initializing the hardware and before using the wrapper 
void LedWrapper::InitLedWrapper(void){
    for (uint8_t num = 0; num < Driver::MAX7219::NUM_MAX7219_IN_DAISY_CHAIN; num++){
        Driver::MAX7219::GetMax7219ByNumber(num).Init();
    }
}

// sets or clears a single word by setting several single leds depending on the words position at the panel
// Does only work if the word is on a single line
void LedWrapper::SetOrClearWord(eWords eWord, bool bOn){
    //only allowed in time mode
    if (DisplayMode::GetDisplayMode() == DisplayMode::eTimeMode){
        uint8_t u8Start, u8Line, u8NumLeds = 0;
        
        switch (eWord){
            case eEs:
                u8NumLeds = 2;
                u8Start = 0;
                u8Line = 0;
                break;
            case eIst:
                u8NumLeds = 3;
                u8Start = 3;
                u8Line = 0;
                break;
            case (eFuenf1):
                u8NumLeds = 4;
                u8Start = 7;
                u8Line = 0;
                break;
            case (eZehn1):
                u8NumLeds = 4;
                u8Start = 0;
                u8Line = 1;
                break;
            case (eZwanzig):
                u8NumLeds = 7;
                u8Start = 4;
                u8Line = 1;
                break;
            case (eDreiviertel):
                u8NumLeds = 11;
                u8Start = 0;
                u8Line = 2;
                break;
            case (eViertel):
                u8NumLeds = 7;
                u8Start = 4;
                u8Line = 2;
                break;
            case (eVor):
                u8NumLeds = 3;
                u8Start = 0;
                u8Line = 3;
                break;
            case (eFunk):
                u8NumLeds = 4;
                u8Start = 3;
                u8Line = 3;
                break;
            case (eNach):
                u8NumLeds = 4;
                u8Start = 7;
                u8Line = 3;
                break;
            case (eHalb):
                u8NumLeds = 4;
                u8Start = 0;
                u8Line = 4;
                break;
            case (eElf):
                u8NumLeds = 3;
                u8Start = 5;
                u8Line = 4;
                break;
            case (eFuenf2):
                u8NumLeds = 5;
                u8Start = 7;
                u8Line = 4;
                break;
            case eEins:
                u8NumLeds = 4;
                u8Start = 0;
                u8Line = 5;
                break;
            case (eZwei):
                u8NumLeds = 4;
                u8Start = 7;
                u8Line = 5;
                break;
            case (eDrei):
                u8NumLeds = 4;
                u8Start = 0;
                u8Line = 6;
                break;
            case (eVier):
                u8NumLeds = 4;
                u8Start = 7;
                u8Line = 6;
                break;
            case (eSechs):
                u8NumLeds = 5;
                u8Start = 0;
                u8Line = 7;
                break;
            case (eAcht):
                u8NumLeds = 4;
                u8Start = 7;
                u8Line = 7;
                break;
            case (eSieben):
                u8NumLeds = 5;
                u8Start = 0;
                u8Line = 8;
                break;
            case (eZwoelf):
                u8NumLeds = 5;
                u8Start = 6;
                u8Line = 8;
                break;
            case (eZehn2):
                u8NumLeds = 4;
                u8Start = 0;
                u8Line = 9;
                break;
            case (eWZ):
                u8NumLeds = 2;
                u8Start = 9;
                u8Line = 9;
                break;
            default:
                break;
        }
        
        for (uint8_t ledDffset = 0; ledDffset < u8NumLeds; ledDffset++){
            SetOrClearSingleLED(u8Start + ledDffset, u8Line, bOn);
        }
    }
}


//return three bools representing wheter each color r/g/b is on or off if the color eColor is to be displayed
void LedWrapper::GetRgbByColor(eLedColor eColor, bool& rbR, bool& rbG, bool& rbB){
    switch (eColor){
        case eRed:
            rbR = true;
            rbG = false;
            rbB = false;
            break;
        case eGreen:
            rbR = false;
            rbG = true;
            rbB = false;
            break;
        case eBlue:
            rbR = false;
            rbG = false;
            rbB = true;
            break;
        case ePink:
            rbR = true;
            rbG = false;
            rbB = true;
            break;
        case eYellow:
            rbR = true;
            rbG = true;
            rbB = false;
            break;
        case eLightBlue:
            rbR = false;
            rbG = true;
            rbB = true;
            break;
        case eWhite:
            rbR = true;
            rbG = true;
            rbB = true;
            break;
        case eOff:
        default:
            rbR = false;
            rbG = false;
            rbB = false;
    }
}

// clears alls leds connected to every single max7219 ic
void LedWrapper::ClearPanel(void){
    for (uint8_t ic = 0; ic < Driver::MAX7219::NUM_MAX7219_IN_DAISY_CHAIN; ic++){
        Driver::MAX7219::GetMax7219ByNumber(ic).ClearLEDs();
    }
}

void LedWrapper::SetAuthorModeLeds(void){
    if (DisplayMode::GetDisplayMode() != DisplayMode::eAuthorMode){
        // SZ - Sascha Zache
        SetOrClearSingleLED(5, 5); //S
        SetOrClearSingleLED(5, 6); //Z
        
        // TL - Tom Linz
        SetOrClearSingleLED(5, 7); //T
        SetOrClearSingleLED(6, 7); //L
    }
}

// starts the matrix effect mode by choosing a random number of different rows
// as start rows for the falling down effect
void LedWrapper::StartMatrixMode(void){
    // maxmimum number of rows with falling down effect at startup
    const uint8_t MAX_STARTROWS = 4;
    
    ClearPanel();
    
    // initializes the random generator using the RTC counter register value
    // because we actually have no time on embedded devices
    srand(RTC_GetCounter());
    
    // allocate memory for 1 to 3 row numbers (random) 
    uint8_t u8NumRowsAtStart = rand() % (MAX_STARTROWS + 1) + 1;
    // memory for row numbers with falling down effect at startup
    uint8_t* pu8Rows = new uint8_t[u8NumRowsAtStart];
    if (pu8Rows == NULL){
        exit(EXIT_FAILURE);
    }
    
    std::list<uint8_t> tmpList;
    
    // fill allocated memory with DISTINCT row numbers (?)
    for (uint8_t u8RowNr = 0; u8RowNr < u8NumRowsAtStart; u8RowNr++){
        uint8_t actValue;
        std::list<uint8_t>::iterator findIter;
        do {
            actValue = rand() % LedWrapper::NUM_ROWS_ON_PANEL;
            findIter = std::find(tmpList.begin(), tmpList.end(), actValue);
        } while (findIter != tmpList.end());
        
        tmpList.push_back(actValue);
    }
}
}
