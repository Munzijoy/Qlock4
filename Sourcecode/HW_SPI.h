/*
 * HW_SPI.h
 *
 *  Created on: 27.10.2016
 *      Author: t.linz
 */

#ifndef HW_SPI_H_
#define HW_SPI_H_

#include "stm32f10x_spi.h"

namespace Hardware {
    void spi1_init(void);
    int spi1_tx(uint16_t u16Tx);
}



#endif /* HW_SPI_H_ */
