/*
 * LookupTable.cpp
 *
 *  Created on: 10.11.2016
 *      Author: t.linz
 */

#include "LookupTable.h"
#include "MAX7219.h"

namespace Application {

const Lookuptable::bfLookupTableEntry Lookuptable::_cabfLookupTable[10][11] = {
    {{0, true,  Driver::MAX7219::eSegDP, 0},    {0, true,  Driver::MAX7219::eSegA,  0},    {0, true,  Driver::MAX7219::eSegB,  0},    {0, true,  Driver::MAX7219::eSegC,  0},    {0, true,  Driver::MAX7219::eSegD,  0},    {0, true,  Driver::MAX7219::eSegE,  0},    {0, true,  Driver::MAX7219::eSegF,  0},    {0, true,  Driver::MAX7219::eSegG,  0},    /*---*/    {5, true,  Driver::MAX7219::eSegDP, 0},    {5, true,  Driver::MAX7219::eSegA,  0},    {5, true,  Driver::MAX7219::eSegB,  0}},
    {{0, false, Driver::MAX7219::eSegDP, 0},    {0, false, Driver::MAX7219::eSegA,  0},    {0, false, Driver::MAX7219::eSegB,  0},    {0, false, Driver::MAX7219::eSegC,  0},    {0, false, Driver::MAX7219::eSegD,  0},    {0, false, Driver::MAX7219::eSegE,  0},    {0, false, Driver::MAX7219::eSegF,  0},    {0, false, Driver::MAX7219::eSegG,  0},    /*---*/    {5, true,  Driver::MAX7219::eSegC,  0},    {5, true,  Driver::MAX7219::eSegD,  0},    {5, true,  Driver::MAX7219::eSegE,  0}},
    {{1, true,  Driver::MAX7219::eSegDP, 0},    {1, true,  Driver::MAX7219::eSegA,  0},    {1, true,  Driver::MAX7219::eSegB,  0},    {1, true,  Driver::MAX7219::eSegC,  0},    {1, true,  Driver::MAX7219::eSegD,  0},    {1, true,  Driver::MAX7219::eSegE,  0},    {1, true,  Driver::MAX7219::eSegF,  0},    {1, true,  Driver::MAX7219::eSegG,  0},    /*---*/    {5, true,  Driver::MAX7219::eSegF,  0},    {5, true,  Driver::MAX7219::eSegG,  0},    {5, false, Driver::MAX7219::eSegDP, 0}},
    {{1, false, Driver::MAX7219::eSegDP, 0},    {1, false, Driver::MAX7219::eSegA,  0},    {1, false, Driver::MAX7219::eSegB,  0},    {1, false, Driver::MAX7219::eSegC,  0},    {1, false, Driver::MAX7219::eSegD,  0},    {1, false, Driver::MAX7219::eSegE,  0},    {1, false, Driver::MAX7219::eSegF,  0},    {1, false, Driver::MAX7219::eSegG,  0},    /*---*/    {5, false, Driver::MAX7219::eSegA,  0},    {5, false, Driver::MAX7219::eSegB,  0},    {5, false, Driver::MAX7219::eSegC,  0}},
    {{2, true,  Driver::MAX7219::eSegDP, 0},    {2, true,  Driver::MAX7219::eSegA,  0},    {2, true,  Driver::MAX7219::eSegB,  0},    {2, true,  Driver::MAX7219::eSegC,  0},    {2, true,  Driver::MAX7219::eSegD,  0},    {2, true,  Driver::MAX7219::eSegE,  0},    {2, true,  Driver::MAX7219::eSegF,  0},    {2, true,  Driver::MAX7219::eSegG,  0},    /*---*/    {5, false, Driver::MAX7219::eSegD,  0},    {5, false, Driver::MAX7219::eSegE,  0},    {5, false, Driver::MAX7219::eSegF,  0}},
    {{2, false, Driver::MAX7219::eSegDP, 0},    {2, false, Driver::MAX7219::eSegA,  0},    {2, false, Driver::MAX7219::eSegB,  0},    {2, false, Driver::MAX7219::eSegC,  0},    {2, false, Driver::MAX7219::eSegD,  0},    {2, false, Driver::MAX7219::eSegE,  0},    {2, false, Driver::MAX7219::eSegF,  0},    {2, false, Driver::MAX7219::eSegG,  0},    /*---*/    {5, false, Driver::MAX7219::eSegG,  0},    {6, true,  Driver::MAX7219::eSegDP, 0},    {6, true,  Driver::MAX7219::eSegA,  0}},
    {{3, true,  Driver::MAX7219::eSegDP, 0},    {3, true,  Driver::MAX7219::eSegA,  0},    {3, true,  Driver::MAX7219::eSegB,  0},    {3, true,  Driver::MAX7219::eSegC,  0},    {3, true,  Driver::MAX7219::eSegD,  0},    {3, true,  Driver::MAX7219::eSegE,  0},    {3, true,  Driver::MAX7219::eSegF,  0},    {3, true,  Driver::MAX7219::eSegG,  0},    /*---*/    {6, true,  Driver::MAX7219::eSegB,  0},    {6, true,  Driver::MAX7219::eSegC,  0},    {6, true,  Driver::MAX7219::eSegD,  0}},
    {{3, false, Driver::MAX7219::eSegDP, 0},    {3, false, Driver::MAX7219::eSegA,  0},    {3, false, Driver::MAX7219::eSegB,  0},    {3, false, Driver::MAX7219::eSegC,  0},    {3, false, Driver::MAX7219::eSegD,  0},    {3, false, Driver::MAX7219::eSegE,  0},    {3, false, Driver::MAX7219::eSegF,  0},    {3, false, Driver::MAX7219::eSegG,  0},    /*---*/    {6, true,  Driver::MAX7219::eSegE,  0},    {6, true,  Driver::MAX7219::eSegF,  0},    {6, true,  Driver::MAX7219::eSegG,  0}},
    {{4, true,  Driver::MAX7219::eSegDP, 0},    {4, true,  Driver::MAX7219::eSegA,  0},    {4, true,  Driver::MAX7219::eSegB,  0},    {4, true,  Driver::MAX7219::eSegC,  0},    {4, true,  Driver::MAX7219::eSegD,  0},    {4, true,  Driver::MAX7219::eSegE,  0},    {4, true,  Driver::MAX7219::eSegF,  0},    {4, true,  Driver::MAX7219::eSegG,  0},    /*---*/    {6, false, Driver::MAX7219::eSegDP, 0},    {6, false, Driver::MAX7219::eSegA,  0},    {6, false, Driver::MAX7219::eSegB,  0}},
    {{4, false, Driver::MAX7219::eSegDP, 0},    {4, false, Driver::MAX7219::eSegA,  0},    {4, false, Driver::MAX7219::eSegB,  0},    {4, false, Driver::MAX7219::eSegC,  0},    {4, false, Driver::MAX7219::eSegD,  0},    {4, false, Driver::MAX7219::eSegE,  0},    {4, false, Driver::MAX7219::eSegF,  0},    {4, false, Driver::MAX7219::eSegG,  0},    /*---*/    {6, false, Driver::MAX7219::eSegC,  0},    {6, false, Driver::MAX7219::eSegD,  0},    {6, false, Driver::MAX7219::eSegE,  0}},
    };

}
