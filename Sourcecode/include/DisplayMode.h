/*
 * DisplayMode.h
 *
 *  Created on: 10.11.2016
 *      Author: t.linz
 */

#ifndef DISPLAYMODE_H_
#define DISPLAYMODE_H_

namespace Application {

class DisplayMode {
public:
    enum eDisplayMode {
        eAuthorMode,
        eTimeMode,
        eMatrixEffectMode,
        eEmptyMode,
    };
    
    static void SetAuthorMode(void);
    static void SetEmptyMode(void);
    static void SetTimeMode(void);
    static void SetMatrixEffectMode(void);
    static eDisplayMode GetDisplayMode(void){ return _eDisplayMode; };
    static bool IsInTimeMode(void){ return _eDisplayMode == eTimeMode; };
    
private:
    static eDisplayMode _eDisplayMode;
};
}


#endif /* DISPLAYMODE_H_ */
