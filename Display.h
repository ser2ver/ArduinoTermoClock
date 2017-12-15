#ifndef ATC_DISPLAY_H
#define ATC_DISPLAY_H

#define TC_EDIT_SEC     1
#define TC_EDIT_MIN     2
#define TC_EDIT_HOUR    4
#define TC_EDIT_DAY     8
#define TC_EDIT_MONTH  16
#define TC_EDIT_YEAR   32

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

    bool mYear4;
    bool mTermoDesc;

    bool mIsEdit;
    uint16_t mPosEdit;
    uint16_t mCntEdit;

    RTC_DS1307 mRtc;
    DateTime mNow;
    Termo mTermo;

public:
    Display(uint8_t aPinKey1, uint8_t aPinKey2, uint8_t aPinTerm, uint8_t aSizeTerm=10) :
            mPinKey1(aPinKey1), mPinKey2(aPinKey2),
            mOnKey1(false), mOnKey2(false), mCntKey1(0), mCntKey2(0),
            mYear4(true), mTermoDesc(true),
            mIsEdit(false), mPosEdit(0), mCntEdit(0),
            mRtc(), mNow(), mTermo(aPinTerm, aSizeTerm)
    {}
    virtual ~Display() = default;

    virtual void init();
    virtual void fresh();

    virtual void console();
    virtual void draw() {}
    virtual void clear() {}
};

#endif //ATC_DISPLAY_H
