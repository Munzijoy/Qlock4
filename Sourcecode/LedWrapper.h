/*
 * LedWrapper.h
 *
 *  Created on: 08.11.2016
 *      Author: t.linz
 */

#ifndef LEDWRAPPER_H_
#define LEDWRAPPER_H_

#include <stdint.h>

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

    // sets the color for all leds of the panel from the outside
    static void SetColorForAllLeds(eLedColor eColor){ _eLedColor = eColor; }
    static void InitLedWrapper(void);
    static void SetOrClearWord(eWords eWord, bool bOn = true);
private:
    static eLedColor _eLedColor;
    //could maybe be made public if more complex stuff than words are to be shown
    static void SetOrClearSingleLED(uint8_t u8x, uint8_t u8y, bool bOn = true);   
    static void GetRgbByColor(eLedColor eColor, bool& rbR, bool& rbG, bool& rbB);
    static void SetAuthorModeLeds(void);
    static void StartMatrixMode(void);
    static void ClearPanel(void);

    static const uint8_t NUM_LINES_ON_PANEL = 10;
    static const uint8_t NUM_ROWS_ON_PANEL = 11;
};
}

#endif /* LEDWRAPPER_H_ */
