/*
 * MAX7219.h
 *
 *  Created on: ???
 *      Author: t.linz
 */

#ifndef MAX7219_H
#define MAX7219_H

#include <stdint.h>
#include <vector>

#include "LedWrapper.h"
#include "LookupTable.h"

namespace Driver {
    
    class MAX7219 {
        friend class Application::LedWrapper;
        friend class Application::Lookuptable;
        private:
            enum eRegisterMap {
              eNoOp = 0,
              eDigit0 = 1,
              eDigit1 = 2,
              eDigit2 = 3,
              eDigit3 = 4,
              eDigit4 = 5,
              eDigit5 = 6,
              eDigit6 = 7,
              eDigit7 = 8,

              eDecodeMode = 9,
              eIntensity = 10,
              eScanLimit = 11,
              eShutdown = 12,
              eDisplayTest = 15
            };
            
            enum eSegments {
                eSegDP = 0x80,
                eSegA  = 0x40,
                eSegB  = 0x20,
                eSegC  = 0x10,
                eSegD  = 0x08,
                eSegE  = 0x04,
                eSegF  = 0x02,
                eSegG  = 0x01,
            };
            
            enum ShutdownModes {
              eShutdownMode = 0x0000,
              eNormalOperationMode = 0x0001
            };
            
            MAX7219(uint8_t numberInDaisyChain) : _u8NumberInDaisyChain(numberInDaisyChain){ }
            static void WriteDataToBus(unsigned short data);
            static void SendDataToAddress(uint16_t u16Data, uint8_t u8Address, uint8_t u8Num);
            static MAX7219* GetMax7219ByNumber(uint8_t u8Number);
            
            void SetOrClearBitForDigit(uint8_t u8Digit, uint8_t u8Bit, bool bOn);
            uint8_t GetValueForDigit(uint8_t u8Digit);
            void ClearLEDs(void);
            void Init(void);
            
            static const uint8_t NUM_MAX7219_IN_DAISY_CHAIN = 8;
            static const std::vector<MAX7219*> _pMAX7219Vector;
            
            uint8_t _aValueForDigits[6];
            const uint8_t _u8NumberInDaisyChain;
};
}

#endif
