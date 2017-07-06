/*
 * LedWrapper.h
 *
 *  Created on: 08.11.2016
 *      Author: t.linz
 */

#ifndef LEDWRAPPER_H_
#define LEDWRAPPER_H_

#include <stdint.h>
#include <map>

#include "LookupTable.h"

namespace Application {

// static class to simplify access to the LEDs without accessing the MAX7219 driver hardware directly
class LedWrapper {
    friend class DisplayMode;
    friend class Lookuptable;
public:
    // all possible led colors for rgb leds (without PWM)
    enum eLedColor {
        eRed,
        eGreen,
        eBlue,
        ePink,
        eYellow,
        eLightBlue,
        eWhite,
        eOff
    };
    
    // all possible words on the panel
    enum eWords{
        eEs,
        eIst,
        eFuenf1,
        eZehn1,
        eZwanzig,
        eDreiviertel,
        eViertel,
        eVor,
        eFunk,
        eNach,
        eHalb,
        eElf,
        eFuenf2,
        eEins,
        eZwei,
        eDrei,
        eVier,
        eSechs,
        eAcht,
        eSieben,
        eZwoelf,
        eZehn2,
        eWZ
    };
    
    struct sWordInfos {
      uint16_t _bfNumLeds   : 4;
      uint16_t _bfStartPos  : 4;
      uint16_t _bfLine      : 4;
      uint16_t _bfDummy     : 4;
    };

    // sets the color for all leds of the panel from the outside
    static void SetColorForAllLeds(eLedColor eColor);
    static void InitLedWrapper(void);
    static void SetOrClearWord(eWords eWord, bool bOn = true);
private:
    static eLedColor _eLedColor;
    //could maybe be made public if more complex stuff than words are to be shown
    static void SetOrClearSingleLED(uint8_t u8x, uint8_t u8y, bool bOn = true);
    static void SetOrClearSingleLED(Lookuptable::bfLookupTableEntry entry, bool bOn = true);
    static void SetOrClearSingleLEDCommon(Lookuptable::bfLookupTableEntry entry, bool bOn = true);
    static void GetRgbByColor(eLedColor eColor, bool& rbR, bool& rbG, bool& rbB);
    static void SetAuthorModeLeds(void);
    static void StartMatrixMode(void);
    static void ClearPanel(void);
    
    struct sRgbLedColor {
      bool _bRed; 
      bool _bGreen;
      bool _bBlue;
    };
    
    static std::map<eLedColor, sRgbLedColor> _colorMap;
    static std::map<eWords, sWordInfos> _wordMap;
};
}

#endif /* LEDWRAPPER_H_ */
