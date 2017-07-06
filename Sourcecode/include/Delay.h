/*
 * Delay.h
 *
 *  Created on: 24.11.2016
 *      Author: t.linz
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <stdint.h>

namespace Tools {

class Timing {
public:
  static volatile int32_t gvs32SysTickCnt;
private:
  
  static void WaitTicks(int32_t s32Ticks);
};

}

#endif /* DELAY_H_ */
