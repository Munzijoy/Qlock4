/*
 * Develop.h
 *
 *  Created on: 08.11.2016
 *      Author: t.linz
 */

#ifndef DEVELOP_H_
#define DEVELOP_H_

#define DEVELOP 1 //indicates a development version

#if DEVELOP
//#warning ================  Development Version of Qlock4. Internal usage only!  ================

#define DISPLAY_TEST_DURATION 8 // 8 means 4 times on and 4 times off
#define DISPLAY_TEST_SPEED 0xFFFFF //the higher the slower
#endif


#endif /* DEVELOP_H_ */
