#ifndef MAX7219_H
#define MAX7219_H

#include <stdint.h>

namespace Driver {
    
    class MAX7219 {
        public:
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
            void Init(void);
            void ClearLEDs(void);
            uint8_t GetValueForDigit(uint8_t u8Digit);
            void SetOrClearBitForDigit(uint8_t u8Digit, uint8_t u8Bit, bool bOn);
            
            static MAX7219& GetMax7219ByNumber(uint8_t u8Number);
            static void SendDataToAddress(unsigned short data, uint8_t address, uint8_t num);
            
            static const uint8_t NUM_MAX7219_IN_DAISY_CHAIN = 8;
        private:
            
            uint8_t _aValueForDigits[6];
            const uint8_t _u8NumberInDaisyChain;
        
            static void WriteDataToBus(unsigned short data);
            
            static MAX7219 _aMAX7219[NUM_MAX7219_IN_DAISY_CHAIN];
};
}

#endif
