/*
 * HW_RCC.h
 *
 *  Created on: 27.10.2016
 *      Author: t.linz
 */

#ifndef HW_RCC_H_
#define HW_RCC_H_

#include "stm32f10x_rcc.h"

namespace Hardware {

class HW_RCC {
    public:
        static void Init(void);
};

}

#endif /* HW_RCC_H_ */
