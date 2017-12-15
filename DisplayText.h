#ifndef ATC_DISPLAYTEXT_H
#define ATC_DISPLAYTEXT_H

#include "Display.h"

#include <LiquidCrystal_I2C.h>

class DisplayText : public Display {
private:
    LiquidCrystal_I2C mLcd;
    char mBuf[12];

public:
    DisplayText(uint8_t aPinKey1, uint8_t aPinKey2, uint8_t aPinTerm, uint8_t aSizeTerm=10) :
            Display(aPinKey1, aPinKey2, aPinTerm, aSizeTerm),
            mLcd(0x27, 16, 2)
    {}
    virtual ~DisplayText() = default;

    virtual void init();
    virtual void fresh();

    virtual void draw();
    virtual void clear() {
        mLcd.clear();
    }
};

#endif //ATC_DISPLAYTEXT_H
