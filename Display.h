#ifndef ATC_DISPLAY_H
#define ATC_DISPLAY_H

#define ATC_EDIT_SEC    1
#define ATC_EDIT_MIN    2
#define ATC_EDIT_HOUR   4
#define ATC_EDIT_DAY    8
#define ATC_EDIT_MONTH 16
#define ATC_EDIT_YEAR  32

#define ATC_Space2 "  "
#define ATC_Space4 "    "
#define ATC_Space6 "      "
#define ATC_Space8 "        "

#include "Termo.h"
#include <RTClib.h>

class Display {
protected:
    uint8_t mPinKey1;
    uint8_t mPinKey2;

    bool mOnKey1;
    bool mOnKey2;
    uint16_t mCntKey1;
    uint16_t mCntKey2;

    uint8_t mMode;
    bool mTermoDesc;

    bool mIsEdit;
    uint16_t mPosEdit;
    uint16_t mCntEdit;

    RTC_DS1307 mRtc;
    DateTime mNow;
    Termo mTermo;

    Display(uint8_t aPinKey1, uint8_t aPinKey2, uint8_t aPinTerm, uint8_t aSizeTerm=10) :
            mPinKey1(aPinKey1), mPinKey2(aPinKey2),
            mOnKey1(false), mOnKey2(false), mCntKey1(0), mCntKey2(0),
            mMode(0), mTermoDesc(true),
            mIsEdit(false), mPosEdit(0), mCntEdit(0),
            mRtc(), mNow(), mTermo(aPinTerm, aSizeTerm)
    {}

    virtual void nextMode() {}
    virtual void setMode(uint8_t aMode);

public:
    virtual ~Display() {}

    static Display* make();
    static void strNum(float num, char *buf, uint8_t len, bool sig=false, uint8_t pos=0, bool fill=true);

    virtual void init();
    virtual void fresh();
    virtual void draw();
};

#endif //ATC_DISPLAY_H
