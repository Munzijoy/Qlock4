#include "MAX7219.h"
#include "stm32f10x_gpio.h"
#include "Develop.h"
#include "HW_SPI.h"

namespace Driver {
    
    MAX7219 MAX7219::_aMAX7219[NUM_MAX7219_IN_DAISY_CHAIN] = { 
        Driver::MAX7219(0), Driver::MAX7219(1), Driver::MAX7219(2), Driver::MAX7219(3), 
        Driver::MAX7219(4), Driver::MAX7219(5), Driver::MAX7219(6), Driver::MAX7219(7) 
    };
    
void Delay(__IO uint32_t nCount){
  for(; nCount != 0; nCount--);
}

// hardware initialization (sets each ic to default values (includes display test in develop mode)
    void MAX7219::Init(void){
#if DEVELOP
    //jedes IC kurz in den Testmodus versetzen und Testmodus wieder deaktivieren (-> Blinken)
        for (uint8_t num = 0; num < 4; num++){
            SendDataToAddress(eDisplayTest, num % 2, _u8NumberInDaisyChain);
            Delay(0x7FFFF);
        }
#endif
        SendDataToAddress(eDisplayTest, 0, _u8NumberInDaisyChain);
        SendDataToAddress(eShutdown, eNormalOperationMode, _u8NumberInDaisyChain);
        SendDataToAddress(eDecodeMode, 0, _u8NumberInDaisyChain);
        SendDataToAddress(eScanLimit, 5, _u8NumberInDaisyChain);
        SendDataToAddress(eIntensity, 0x0F, _u8NumberInDaisyChain);
        ClearLEDs();
    }
    
    void MAX7219::ClearLEDs(void){
        SendDataToAddress(1, 0, _u8NumberInDaisyChain);
        SendDataToAddress(2, 0, _u8NumberInDaisyChain);
        SendDataToAddress(3, 0, _u8NumberInDaisyChain);
        SendDataToAddress(4, 0, _u8NumberInDaisyChain);
        SendDataToAddress(5, 0, _u8NumberInDaisyChain);
        SendDataToAddress(6, 0, _u8NumberInDaisyChain);
        SendDataToAddress(7, 0, _u8NumberInDaisyChain);
        SendDataToAddress(8, 0, _u8NumberInDaisyChain);
        
        for (uint8_t u8Digit = 0; u8Digit < 5; u8Digit++){
            _aValueForDigits[u8Digit] = 0;
        }
    }

    // writes the content of data to the device register for the num device in the daisy chain
    void MAX7219::SendDataToAddress(uint16_t address, uint8_t data, uint8_t num){
        GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
        Delay(500);
        
        for (uint8_t i = 0; i < 3 - num; i++){
            WriteDataToBus((eNoOp << 8) | 0xFF);
        }
        
        WriteDataToBus((address << 8) | data);
        
        for (uint8_t i = 0; i < num; i++){
            WriteDataToBus((eNoOp << 8) | 0xFF);
        }
        
        GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
        Delay(500);
    }
    
    // returns the driver object corresponding to the daisy chain number
    MAX7219& MAX7219::GetMax7219ByNumber(uint8_t u8Number){ 
        if (u8Number < NUM_MAX7219_IN_DAISY_CHAIN){
            return _aMAX7219[u8Number]; 
        } else { 
            return _aMAX7219[0]; 
        } 
    }
    
    // returns the stored digit values for each digit (must be stored internally because common anode leds are used) 
    uint8_t MAX7219::GetValueForDigit(uint8_t u8Digit){ 
        if (u8Digit < 6){
            return _aValueForDigits[u8Digit]; 
        } else {
            return _aValueForDigits[0]; 
        }
    }
    
    // sets or clears a bit in the internal digit value storage
    void MAX7219::SetOrClearBitForDigit(uint8_t u8Digit, uint8_t u8Bit, bool bOn){
    (bOn) ? SET_BIT(_aValueForDigits[u8Digit], u8Bit) 
          : CLEAR_BIT(_aValueForDigits[u8Digit], u8Bit);
    }
    
    // writes data to the spi bus
    void MAX7219::WriteDataToBus(uint16_t data){
        Hardware::spi1_tx(data);
        Delay(50);
    }
}
