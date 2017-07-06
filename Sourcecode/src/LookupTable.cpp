/*
 * LookupTable.cpp
 *
 *  Created on: 10.11.2016
 *      Author: t.linz
 */

#include <assert.h>

#include "LookupTable.h"
#include "MAX7219.h"
#include "Panel.h"

namespace Application {

Lookuptable::bfLookupTableEntry Lookuptable::_cabfLookupTable[NUM_LINES_ON_PANEL][NUM_ROWS_ON_PANEL] = {
    {{0, true,  false,  Driver::MAX7219::eSegDP, 0},    {0, true, false,  Driver::MAX7219::eSegA,  0},    {0, true, false,  Driver::MAX7219::eSegB,  0},    {0, true, false,  Driver::MAX7219::eSegC,  0},    {0, true, false,  Driver::MAX7219::eSegD,  0},    {0, true, false,  Driver::MAX7219::eSegE,  0},    {0, true, false,  Driver::MAX7219::eSegF,  0},    {0, true, false,  Driver::MAX7219::eSegG,  0},    /*---*/    {5, true,  false,  Driver::MAX7219::eSegDP, 0},    {5, true, false,  Driver::MAX7219::eSegA,  0},    {5, true, false,  Driver::MAX7219::eSegB,  0}},
    {{0, false, false, Driver::MAX7219::eSegDP, 0},    {0, false, false, Driver::MAX7219::eSegA,  0},    {0, false, false, Driver::MAX7219::eSegB,  0},    {0, false, false, Driver::MAX7219::eSegC,  0},    {0, false, false, Driver::MAX7219::eSegD,  0},    {0, false, false, Driver::MAX7219::eSegE,  0},    {0, false, false, Driver::MAX7219::eSegF,  0},    {0, false, false, Driver::MAX7219::eSegG,  0},    /*---*/    {5, true, false,  Driver::MAX7219::eSegC,  0},    {5, true, false,  Driver::MAX7219::eSegD,  0},    {5, true, false,  Driver::MAX7219::eSegE,  0}},
    {{1, true,  false,  Driver::MAX7219::eSegDP, 0},    {1, true, false,  Driver::MAX7219::eSegA,  0},    {1, true, false,  Driver::MAX7219::eSegB,  0},    {1, true, false,  Driver::MAX7219::eSegC,  0},    {1, true, false,  Driver::MAX7219::eSegD,  0},    {1, true, false,  Driver::MAX7219::eSegE,  0},    {1, true, false,  Driver::MAX7219::eSegF,  0},    {1, true, false,  Driver::MAX7219::eSegG,  0},    /*---*/    {5, true,  false,  Driver::MAX7219::eSegF,  0},    {5, true, false,  Driver::MAX7219::eSegG,  0},    {5, false,  false, Driver::MAX7219::eSegDP, 0}},
    {{1, false, false, Driver::MAX7219::eSegDP, 0},    {1, false, false, Driver::MAX7219::eSegA,  0},    {1, false, false, Driver::MAX7219::eSegB,  0},    {1, false, false, Driver::MAX7219::eSegC,  0},    {1, false, false, Driver::MAX7219::eSegD,  0},    {1, false, false, Driver::MAX7219::eSegE,  0},    {1, false, false, Driver::MAX7219::eSegF,  0},    {1, false, false, Driver::MAX7219::eSegG,  0},    /*---*/    {5, false,  false, Driver::MAX7219::eSegA,  0},    {5, false, false, Driver::MAX7219::eSegB,  0},    {5, false, false, Driver::MAX7219::eSegC,  0}},
    {{2, true,  false,  Driver::MAX7219::eSegDP, 0},    {2, true, false,  Driver::MAX7219::eSegA,  0},    {2, true, false,  Driver::MAX7219::eSegB,  0},    {2, true, false,  Driver::MAX7219::eSegC,  0},    {2, true, false,  Driver::MAX7219::eSegD,  0},    {2, true, false,  Driver::MAX7219::eSegE,  0},    {2, true, false,  Driver::MAX7219::eSegF,  0},    {2, true, false,  Driver::MAX7219::eSegG,  0},    /*---*/    {5, false, false, Driver::MAX7219::eSegD,  0},    {5, false, false, Driver::MAX7219::eSegE,  0},    {5, false, false, Driver::MAX7219::eSegF,  0}},
    {{2, false, false, Driver::MAX7219::eSegDP, 0},    {2, false, false, Driver::MAX7219::eSegA,  0},    {2, false, false, Driver::MAX7219::eSegB,  0},    {2, false, false, Driver::MAX7219::eSegC,  0},    {2, false, false, Driver::MAX7219::eSegD,  0},    {2, false, false, Driver::MAX7219::eSegE,  0},    {2, false, false, Driver::MAX7219::eSegF,  0},    {2, false, false, Driver::MAX7219::eSegG,  0},    /*---*/    {5, false,  false, Driver::MAX7219::eSegG,  0},    {6, true,  false,  Driver::MAX7219::eSegDP, 0},    {6, true, false,  Driver::MAX7219::eSegA,  0}},
    {{3, true,  false,  Driver::MAX7219::eSegDP, 0},    {3, true, false,  Driver::MAX7219::eSegA,  0},    {3, true, false,  Driver::MAX7219::eSegB,  0},    {3, true, false,  Driver::MAX7219::eSegC,  0},    {3, true, false,  Driver::MAX7219::eSegD,  0},    {3, true, false,  Driver::MAX7219::eSegE,  0},    {3, true, false,  Driver::MAX7219::eSegF,  0},    {3, true, false,  Driver::MAX7219::eSegG,  0},    /*---*/    {6, true,  false,  Driver::MAX7219::eSegB,  0},    {6, true, false,  Driver::MAX7219::eSegC,  0},    {6, true, false,  Driver::MAX7219::eSegD,  0}},
    {{3, false, false, Driver::MAX7219::eSegDP, 0},    {3, false, false, Driver::MAX7219::eSegA,  0},    {3, false, false, Driver::MAX7219::eSegB,  0},    {3, false, false, Driver::MAX7219::eSegC,  0},    {3, false, false, Driver::MAX7219::eSegD,  0},    {3, false, false, Driver::MAX7219::eSegE,  0},    {3, false, false, Driver::MAX7219::eSegF,  0},    {3, false, false, Driver::MAX7219::eSegG,  0},    /*---*/    {6, true, false,  Driver::MAX7219::eSegE,  0},    {6, true, false,  Driver::MAX7219::eSegF,  0},    {6, true, false,  Driver::MAX7219::eSegG,  0}},
    {{4, true,  false,  Driver::MAX7219::eSegDP, 0},    {4, true, false,  Driver::MAX7219::eSegA,  0},    {4, true, false,  Driver::MAX7219::eSegB,  0},    {4, true, false,  Driver::MAX7219::eSegC,  0},    {4, true, false,  Driver::MAX7219::eSegD,  0},    {4, true, false,  Driver::MAX7219::eSegE,  0},    {4, true, false,  Driver::MAX7219::eSegF,  0},    {4, true, false,  Driver::MAX7219::eSegG,  0},    /*---*/    {6, false, false, Driver::MAX7219::eSegDP, 0},    {6, false, false, Driver::MAX7219::eSegA,  0},    {6, false, false, Driver::MAX7219::eSegB,  0}},
    {{4, false, false, Driver::MAX7219::eSegDP, 0},    {4, false, false, Driver::MAX7219::eSegA,  0},    {4, false, false, Driver::MAX7219::eSegB,  0},    {4, false, false, Driver::MAX7219::eSegC,  0},    {4, false, false, Driver::MAX7219::eSegD,  0},    {4, false, false, Driver::MAX7219::eSegE,  0},    {4, false, false, Driver::MAX7219::eSegF,  0},    {4, false, false, Driver::MAX7219::eSegG,  0},    /*---*/    {6, false,  false, Driver::MAX7219::eSegC,  0},    {6, false, false, Driver::MAX7219::eSegD,  0},    {6, false, false, Driver::MAX7219::eSegE,  0}},
    };

void Lookuptable::CheckEntry(Lookuptable::bfLookupTableEntry& rEntry){
  assert(rEntry._bfIcNumberInDaisyChain < Driver::MAX7219::NUM_MAX7219_IN_DAISY_CHAIN);
  
  assert(rEntry._bfDummy == 0);
  
  assert((rEntry._bfSegmentIdx == Driver::MAX7219::eSegDP) ||
        (rEntry._bfSegmentIdx == Driver::MAX7219::eSegA) ||
        (rEntry._bfSegmentIdx == Driver::MAX7219::eSegB) ||
        (rEntry._bfSegmentIdx == Driver::MAX7219::eSegC) ||
        (rEntry._bfSegmentIdx == Driver::MAX7219::eSegD) ||
        (rEntry._bfSegmentIdx == Driver::MAX7219::eSegE) ||
        (rEntry._bfSegmentIdx == Driver::MAX7219::eSegF) ||
        (rEntry._bfSegmentIdx == Driver::MAX7219::eSegG));
}

}
