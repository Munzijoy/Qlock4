/*
 * Delay.cpp
 *
 *  Created on: 24.11.2016
 *      Author: t.linz
 */

#include "Delay.h"

namespace Tools {

volatile int32_t Timing::gvs32SysTickCnt(0);

void Timing::WaitTicks(int32_t s32Ticks){
    int32_t s32SysTickCntHold;
    s32SysTickCntHold = gvs32SysTickCnt;  
    while((gvs32SysTickCnt - s32SysTickCntHold ) <= s32Ticks );
}

}


