#include "Display.h"

const uint8_t TC_daysInMonth [] PROGMEM = { 31,28,31,30,31,30,31,31,30,31,30,31 };

void Display::init() {
    // Buttons init
    pinMode(mPinKey1, INPUT);
    pinMode(mPinKey2, INPUT);

    // Real Time Clock init
    if (!mRtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1) delay(1000);
    }

    if (!mRtc.isrunning()) {
        Serial.println("RTC is NOT running!");
    }

    mNow = mRtc.now();
    if (mNow.year() <= 2015) {
        // following line sets the RTC to the date & time this sketch was compiled
        mRtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }

    // Temperature sensors init
    mTermo.init();
}

void Display::fresh() {
    bool newOnKey1 = digitalRead(mPinKey1);
    bool newOnKey2 = digitalRead(mPinKey2);

    if (!newOnKey1 && mOnKey1)
        mCntKey1 = 0;
    else if (newOnKey1)
        ++mCntKey1;
    mOnKey1 = newOnKey1;

    if (!newOnKey2 && mOnKey2)
        mCntKey2 = 0;
    else if (newOnKey2)
        ++mCntKey2;
    mOnKey2 = newOnKey2;

    if (mOnKey1 || mOnKey2) {
        Serial.print("Keys: ");
        Serial.print(mCntKey1);
        Serial.print("/");
        Serial.println(mCntKey2);
    }

    mTermo.reload();
    mNow = mRtc.now();

    if (!mIsEdit && (((mCntKey1 == 2) && (mCntKey2 >= 2) && (mCntKey2 < 4)) ||
                     ((mCntKey1 >= 2) && (mCntKey2 == 2)))) {
        mTermoDesc = !mTermoDesc;
    } else if (!mIsEdit && (mCntKey1 == 0) && (mCntKey2 == 2)) {
        mYear4 = !mYear4;
        clear();
    } else if (!mIsEdit && (mCntKey1 == 4) && (mCntKey2 == 0)) {
        mIsEdit = true;
        mPosEdit = 1;
        mCntEdit = 1;
    } else if (mIsEdit) {
        ++mCntEdit;
        if ((mCntKey1 == 1) && (mCntKey2 == 0)) {
            mPosEdit <<= 1;
            if (mPosEdit > TC_EDIT_YEAR) {
                mPosEdit = 0;
                mIsEdit = false;
            }
            mCntEdit = 1;
        } else if ((mCntKey1 == 4) && (mCntKey2 == 0)) {
            mIsEdit = false;
        } else if ((mCntKey1 == 0) && (mCntKey2 > 0)) {
            uint16_t x;
            mNow = mRtc.now();

            switch (mPosEdit) {
                case TC_EDIT_SEC:
                    if (mNow.second() < 30) {
                        mRtc.adjust(DateTime(mNow.year(), mNow.month(), mNow.day(), mNow.hour(), mNow.minute(), 0));
                    } else {
                        if ((x = mNow.minute() + 1) >= 60)
                            x = 0;
                        mRtc.adjust(DateTime(mNow.year(), mNow.month(), mNow.day(), mNow.hour(), x, 0));
                    }
                    break;

                case TC_EDIT_MIN:
                    if ((x = mNow.minute() + 1) >= 60)
                        x = 0;
                    mRtc.adjust(DateTime(mNow.year(), mNow.month(), mNow.day(), mNow.hour(), x, mNow.second()));
                    break;

                case TC_EDIT_HOUR:
                    if ((x = mNow.hour() + 1) >= 24)
                        x = 0;
                    mRtc.adjust(DateTime(mNow.year(), mNow.month(), mNow.day(), x, mNow.minute(), mNow.second()));
                    break;

                case TC_EDIT_DAY:
                    if ((x = mNow.day() + 1) > (pgm_read_byte(TC_daysInMonth + mNow.month() - 1) + (((mNow.month() == 2) && (mNow.year() % 4 == 0)) ? 1 : 0)))
                        x = 1;
                    mRtc.adjust(DateTime(mNow.year(), mNow.month(), x, mNow.hour(), mNow.minute(), mNow.second()));
                    break;

                case TC_EDIT_MONTH:
                    if ((x = mNow.month() + 1) > 12)
                        x = 1;
                    mRtc.adjust(DateTime(mNow.year(), x, mNow.day(), mNow.hour(), mNow.minute(), mNow.second()));
                    break;

                case TC_EDIT_YEAR:
                    if ((x = mNow.year() + 1) > 2030)
                        x = 2016;
                    mRtc.adjust(DateTime(x, mNow.month(), mNow.day(), mNow.hour(), mNow.minute(), mNow.second()));
                    break;

                default:
                    break;
            }

            mCntEdit = 0;
            mNow = mRtc.now();
        } else if (mCntEdit > 100) {
            mIsEdit = false;
        }
    }
}

void Display::console() {
    Serial.print(mNow.year(), DEC);
    Serial.print('/');
    Serial.print(mNow.month(), DEC);
    Serial.print('/');
    Serial.print(mNow.day(), DEC);
    Serial.print(" ");
    Serial.print(mNow.hour(), DEC);
    Serial.print(':');
    Serial.print(mNow.minute(), DEC);
    Serial.print(':');
    Serial.print(mNow.second(), DEC);
    Serial.println();

    if (mOnKey1 || mOnKey2) {
        Serial.print("Keys: ");
        Serial.print(mCntKey1);
        Serial.print("/");
        Serial.println(mCntKey2);
    }

    for (uint8_t i=0; i < mTermo.getNumDev(); ++i) {
        Serial.print("Temperature ");
        Serial.print(i, DEC);
        Serial.print(": ");
        Serial.println(mTermo.getTermC(i));
    }
}
