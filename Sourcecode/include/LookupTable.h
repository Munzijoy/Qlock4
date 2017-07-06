/*
 * LookupTable.h
 *
 *  Created on: 28.10.2016
 *      Author: t.linz
 */

#ifndef LOOKUPTABLE_H_
#define LOOKUPTABLE_H_

#include <stdint.h>
#include <assert.h>

#include "Panel.h"

namespace Application {

class Lookuptable {
	friend class LedWrapper;
    private:
    
    struct bfLookupTableEntry {
        uint16_t _bfIcNumberInDaisyChain : 3; //Number of the MAX7219 in the daisy chain (0 is first and 7 ist last)
        uint16_t _bfIsFirstLine : 1; //indicates whether registers DIG0..DIG3 or DIG4...DIG7 have to be used to access the 3 leds
        uint16_t _bfIsLEDOn : 1;
        uint16_t _bfSegmentIdx : 8; //indicates which segment line SegDP to SegG has to be set to HIGH level to flash the led (must be enum value of type Driver::MAX7219::eSegments )
        uint16_t _bfDummy : 4; //always zero, bitflag-padding
    };
    
    static void CheckEntry(bfLookupTableEntry& rEntry);

    //11 x 10 leds -> each led has its lookuptable-entry of the type shown above, which contains all information to access the hardware
    static bfLookupTableEntry _cabfLookupTable[NUM_LINES_ON_PANEL][NUM_ROWS_ON_PANEL]; 
};

}


#endif /* LOOKUPTABLE_H_ */
