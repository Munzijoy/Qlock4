/*
 * LookupTable.h
 *
 *  Created on: 28.10.2016
 *      Author: t.linz
 */

#ifndef LOOKUPTABLE_H_
#define LOOKUPTABLE_H_

#include "MAX7219.h"

struct bfLookupTableEntry {
    uint16_t _bfIcNumberInDaisyChain : 3; //Number of the MAX7219 in the daisy chain (0 is first and 7 ist last)
    uint16_t _bfIsFirstLine : 1; //indicates whether registers DIG0..DIG3 or DIG4...DIG7 have to be used to access the 3 leds
    uint16_t _bfSegmentIdx : 8; //indicates which segment line SegDP to SegG has to be set to HIGH level to flash the led (must be enum value of type Driver::MAX7219::eSegments )
    uint16_t _bfDummy : 4; //always zero, bitflag-padding
};

using namespace Driver; //improves readability of the large array (Driver::MAX7219::eSegDP --> MAX7219::eSegDP)

//11 x 10 leds -> each led has its lookuptable-entry of the type shown above, which contains all information to access the hardware
const bfLookupTableEntry cabfLookupTable[10][11] = {
{{0, true,  MAX7219::eSegDP, 0},    {0, true,  MAX7219::eSegA,  0},    {0, true,  MAX7219::eSegB,  0},    {0, true,  MAX7219::eSegC,  0},    {0, true,  MAX7219::eSegD,  0},    {0, true,  MAX7219::eSegE,  0},    {0, true,  MAX7219::eSegF,  0},    {0, true,  MAX7219::eSegG,  0},    /*---*/    {5, true,  MAX7219::eSegDP, 0},    {5, true,  MAX7219::eSegA,  0},    {5, true,  MAX7219::eSegB,  0}},
{{0, false, MAX7219::eSegDP, 0},    {0, false, MAX7219::eSegA,  0},    {0, false, MAX7219::eSegB,  0},    {0, false, MAX7219::eSegC,  0},    {0, false, MAX7219::eSegD,  0},    {0, false, MAX7219::eSegE,  0},    {0, false, MAX7219::eSegF,  0},    {0, false, MAX7219::eSegG,  0},    /*---*/    {5, true,  MAX7219::eSegC,  0},    {5, true,  MAX7219::eSegD,  0},    {5, true,  MAX7219::eSegE,  0}},
{{1, true,  MAX7219::eSegDP, 0},    {1, true,  MAX7219::eSegA,  0},    {1, true,  MAX7219::eSegB,  0},    {1, true,  MAX7219::eSegC,  0},    {1, true,  MAX7219::eSegD,  0},    {1, true,  MAX7219::eSegE,  0},    {1, true,  MAX7219::eSegF,  0},    {1, true,  MAX7219::eSegG,  0},    /*---*/    {5, true,  MAX7219::eSegF,  0},    {5, true,  MAX7219::eSegG,  0},    {5, false, MAX7219::eSegDP, 0}},
{{1, false, MAX7219::eSegDP, 0},    {1, false, MAX7219::eSegA,  0},    {1, false, MAX7219::eSegB,  0},    {1, false, MAX7219::eSegC,  0},    {1, false, MAX7219::eSegD,  0},    {1, false, MAX7219::eSegE,  0},    {1, false, MAX7219::eSegF,  0},    {1, false, MAX7219::eSegG,  0},    /*---*/    {5, false, MAX7219::eSegA,  0},    {5, false, MAX7219::eSegB,  0},    {5, false, MAX7219::eSegC,  0}},
{{2, true,  MAX7219::eSegDP, 0},    {2, true,  MAX7219::eSegA,  0},    {2, true,  MAX7219::eSegB,  0},    {2, true,  MAX7219::eSegC,  0},    {2, true,  MAX7219::eSegD,  0},    {2, true,  MAX7219::eSegE,  0},    {2, true,  MAX7219::eSegF,  0},    {2, true,  MAX7219::eSegG,  0},    /*---*/    {5, false, MAX7219::eSegD,  0},    {5, false, MAX7219::eSegE,  0},    {5, false, MAX7219::eSegF,  0}},
{{2, false, MAX7219::eSegDP, 0},    {2, false, MAX7219::eSegA,  0},    {2, false, MAX7219::eSegB,  0},    {2, false, MAX7219::eSegC,  0},    {2, false, MAX7219::eSegD,  0},    {2, false, MAX7219::eSegE,  0},    {2, false, MAX7219::eSegF,  0},    {2, false, MAX7219::eSegG,  0},    /*---*/    {5, false, MAX7219::eSegG,  0},    {6, true,  MAX7219::eSegDP, 0},    {6, true,  MAX7219::eSegA,  0}},
{{3, true,  MAX7219::eSegDP, 0},    {3, true,  MAX7219::eSegA,  0},    {3, true,  MAX7219::eSegB,  0},    {3, true,  MAX7219::eSegC,  0},    {3, true,  MAX7219::eSegD,  0},    {3, true,  MAX7219::eSegE,  0},    {3, true,  MAX7219::eSegF,  0},    {3, true,  MAX7219::eSegG,  0},    /*---*/    {6, true,  MAX7219::eSegB,  0},    {6, true,  MAX7219::eSegC,  0},    {6, true,  MAX7219::eSegD,  0}},
{{3, false, MAX7219::eSegDP, 0},    {3, false, MAX7219::eSegA,  0},    {3, false, MAX7219::eSegB,  0},    {3, false, MAX7219::eSegC,  0},    {3, false, MAX7219::eSegD,  0},    {3, false, MAX7219::eSegE,  0},    {3, false, MAX7219::eSegF,  0},    {3, false, MAX7219::eSegG,  0},    /*---*/    {6, true,  MAX7219::eSegE,  0},    {6, true,  MAX7219::eSegF,  0},    {6, true,  MAX7219::eSegG,  0}},
{{4, true,  MAX7219::eSegDP, 0},    {4, true,  MAX7219::eSegA,  0},    {4, true,  MAX7219::eSegB,  0},    {4, true,  MAX7219::eSegC,  0},    {4, true,  MAX7219::eSegD,  0},    {4, true,  MAX7219::eSegE,  0},    {4, true,  MAX7219::eSegF,  0},    {4, true,  MAX7219::eSegG,  0},    /*---*/    {6, false, MAX7219::eSegDP, 0},    {6, false, MAX7219::eSegA,  0},    {6, false, MAX7219::eSegB,  0}},
{{4, false, MAX7219::eSegDP, 0},    {4, false, MAX7219::eSegA,  0},    {4, false, MAX7219::eSegB,  0},    {4, false, MAX7219::eSegC,  0},    {4, false, MAX7219::eSegD,  0},    {4, false, MAX7219::eSegE,  0},    {4, false, MAX7219::eSegF,  0},    {4, false, MAX7219::eSegG,  0},    /*---*/    {6, false, MAX7219::eSegC,  0},    {6, false, MAX7219::eSegD,  0},    {6, false, MAX7219::eSegE,  0}},
};



#endif /* LOOKUPTABLE_H_ */
