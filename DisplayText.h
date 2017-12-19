#ifndef ATC_DISPLAYTEXT_H
#define ATC_DISPLAYTEXT_H

#include "Display.h"

#ifdef ATC_DISPLAY_TEXT

#define ATC_MODE_TEXT1 0
#define ATC_MODE_TEXT2 1

#include <LiquidCrystal_I2C.h>

class DisplayText : public Display {
protected:
    LiquidCrystal_I2C mLcd;
    char mBuf[12];

    virtual void nextMode();

public:
    DisplayText(uint8_t aPinKey1, uint8_t aPinKey2, uint8_t aPinTerm, uint8_t aSizeTerm=10) :
            Display(aPinKey1, aPinKey2, aPinTerm, aSizeTerm),
            mLcd(0x27, 16, 2), mBuf() {}
    virtual ~DisplayText() {}

    virtual void init();
    virtual void fresh();

    virtual void draw();
};

#endif

#endif //ATC_DISPLAYTEXT_H
