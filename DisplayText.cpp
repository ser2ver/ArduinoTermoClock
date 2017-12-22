#include "DisplayText.h"

#ifdef ATC_DISPLAY_TEXT

void DisplayText::nextMode() {
    if (++mMode > ATC_MODE_TEXT2)
        mMode = 0;
    setMode(mMode);
    mLcd.clear();
}

void DisplayText::setMode(uint8_t aMode) {
    Display::setMode(aMode);
    switch (mMode) {
        case ATC_MODE_TEXT1:
            mTermo.setSize(10);
            break;
        case ATC_MODE_TEXT2:
        default:
            mTermo.setSize(12);
            break;
    }
}

void DisplayText::init() {
    Display::init();

    for (uint8_t i=0; i < 12; ++i)
        mBuf[i] = '\0';

    // Display init
    mLcd.init();
    mLcd.backlight();
}

void DisplayText::draw() {
    // Draw Date
    mLcd.setCursor(0, 1);
    if (mIsEdit && (mPosEdit & ATC_EDIT_DAY) && (mCntEdit & 1)) {
        mLcd.print(ATC_Space2);
    } else {
        strNum(mNow.day(), mBuf, 2);
        mLcd.print(mBuf);
    }

    mLcd.setCursor(2, 1);
    mLcd.print(".");

    mLcd.setCursor(3, 1);
    if (mIsEdit && (mPosEdit & ATC_EDIT_MONTH) && (mCntEdit & 1)) {
        mLcd.print(ATC_Space2);
    } else {
        strNum(mNow.month(), mBuf, 2);
        mLcd.print(mBuf);
    }

    mLcd.setCursor(5, 1);
    mLcd.print(".");

    mLcd.setCursor(6, 1);
    if (mIsEdit && (mPosEdit & ATC_EDIT_YEAR) && (mCntEdit & 1)) {
        mLcd.print((mMode == ATC_MODE_TEXT1) ? ATC_Space4 : ATC_Space2);
    } else {
        if (mMode == ATC_MODE_TEXT1)
            strNum(mNow.year(), mBuf, 4);
        else
            strNum(mNow.year() - 2000, mBuf, 2);
        mLcd.print(mBuf);
    }

    // Draw Time
    uint8_t pos = (mMode == ATC_MODE_TEXT1) ? 1 : 0;

    mLcd.setCursor(pos + 0, 0);
    if (mIsEdit && (mPosEdit & ATC_EDIT_HOUR) && (mCntEdit & 1)) {
        mLcd.print(ATC_Space2);
    } else {
        strNum(mNow.hour(), mBuf, 2);
        mLcd.print(mBuf);
    }

    mLcd.setCursor(pos + 2, 0);
    mLcd.print(":");

    mLcd.setCursor(pos + 3, 0);
    if (mIsEdit && (mPosEdit & ATC_EDIT_MIN) && (mCntEdit & 1)) {
        mLcd.print(ATC_Space2);
    } else {
        strNum(mNow.minute(), mBuf, 2);
        mLcd.print(mBuf);
    }

    mLcd.setCursor(pos + 5, 0);
    mLcd.print(":");

    mLcd.setCursor(pos + 6, 0);
    if (mIsEdit && (mPosEdit & ATC_EDIT_SEC) && (mCntEdit & 1)) {
        mLcd.print(ATC_Space2);
    } else {
        strNum(mNow.second(), mBuf, 2);
        mLcd.print(mBuf);
    }

    // Draw Temperature
    uint8_t size;
    uint8_t acc;
    if (mMode == ATC_MODE_TEXT1) {
        pos  = 10;
        size = 6;
        acc  = 1;
    } else {
        pos  = 8;
        size = 8;
        acc  = 3;
    }
    mLcd.setCursor(pos, (mTermoDesc ? 1 : 0));
    if (mTermo.getNumDev() > 0) {
        strNum(mTermo.getTermC(0), mBuf, size, true, acc, false);
        mLcd.print(mBuf);
    } else {
        mLcd.print((mMode == ATC_MODE_TEXT1) ? ATC_Space6 : ATC_Space8);
    }

    mLcd.setCursor(pos, (mTermoDesc ? 0 : 1));
    if (mTermo.getNumDev() > 1) {
        strNum(mTermo.getTermC(1), mBuf, size, true, acc, false);
        mLcd.print(mBuf);
    } else {
        mLcd.print((mMode == ATC_MODE_TEXT1) ? ATC_Space6 : ATC_Space8);
    }
}

#endif
