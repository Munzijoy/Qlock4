/*
 * Develop.h
 *
 *  Created on: 08.11.2016
 *      Author: t.linz
 */

#ifndef DEVELOP_H_
#define DEVELOP_H_

#define DEVELOP 0 //indicates a development version

#if DEVELOP
    //#warning ================  Development Version of Qlock4. Internal usage only!  ================
    #define DISPLAY_TEST_DURATION 8 // 8 means 4 times on and 4 times off
    #define DISPLAY_TEST_SPEED 0xFFFFFFF //the higher the slower
    #define NO_DEBUGGER 1 // only map file debugging
#else
    #define NDEBUG // kein assert()-Output
#endif


#endif /* DEVELOP_H_ */
