#include "DisplayGraph.h"

#ifdef ATC_DISPLAY_GRAPH

void DisplayGraph::nextMode() {
    if (++mMode > ATC_MODE_GRAPH2)
        mMode = 0;
    setMode(mMode);
}

void DisplayGraph::setMode(uint8_t aMode) {
    Display::setMode(aMode);
    switch (mMode) {
        case ATC_MODE_GRAPH1:
            mTermo.setSize(10);
            break;
        case ATC_MODE_GRAPH2:
        default:
            mTermo.setSize(12);
            break;
    }
}

void DisplayGraph::drawMode1() {
    float i;
    mGraph->drawCircle(31, 31, 31);
    mGraph->drawPixel(31, 31);
    for (i=0.0; i < 2 * PI; i += PI / 6) {
        mGraph->drawLine(31 + sin(i) * 31, 31 + cos(i) * 31, 31 + sin(i) * 28, 31 + cos(i) * 28);
    }

    if (!mIsEdit || !(mPosEdit & ATC_EDIT_HOUR) || !(mCntEdit & 1)) {
        i = (mNow.hour() + mNow.minute() / 60.0) / 6.0 * PI;
        mGraph->drawLine(31, 31, 31 + sin(i) * 15, 31 - cos(i) * 15);
    }
    if (!mIsEdit || !(mPosEdit & ATC_EDIT_MIN) || !(mCntEdit & 1)) {
        i = mNow.minute() / 30.0 * PI;
        mGraph->drawLine(31, 31, 31 + sin(i) * 20, 31 - cos(i) * 20);
    }
    if (!mIsEdit || !(mPosEdit & ATC_EDIT_SEC) || !(mCntEdit & 1)) {
        i = mNow.second() / 30.0 * PI;
        mGraph->drawLine(31, 31, 31 + sin(i) * 25, 31 - cos(i) * 25);
    }

    mGraph->setFont(u8g_font_8x13B);
    if (mIsEdit && (mPosEdit & ATC_EDIT_DAY) && (mCntEdit & 1)) {
        strcpy(mBuf+0, ATC_Space2);
    } else {
        strNum(mNow.day(), mBuf + 0, 2);
    }
    mBuf[2] = '.';
    if (mIsEdit && (mPosEdit & ATC_EDIT_MONTH) && (mCntEdit & 1)) {
        strcpy(mBuf+3, ATC_Space2);
    } else {
        strNum(mNow.month(), mBuf + 3, 2);
    }
    mBuf[5] = '.';
    if (mIsEdit && (mPosEdit & ATC_EDIT_YEAR) && (mCntEdit & 1)) {
        strcpy(mBuf+6, ATC_Space2);
    } else {
        strNum(mNow.year() - 2000, mBuf + 6, 2);
    }
    mGraph->drawStr( 64, 62, mBuf);

    mGraph->setFont(u8g_font_10x20);

    if (mTermo.getNumDev() > 0) {
        strNum(mTermo.getTermC(0), mBuf, 6, true, 2, false);
        mGraph->drawStr(65, (mTermoDesc ? 38 : 14), mBuf);
    }
    if (mTermo.getNumDev() > 1) {
        strNum(mTermo.getTermC(1), mBuf, 6, true, 2, false);
        mGraph->drawStr(65, (mTermoDesc ? 14 : 38), mBuf);
    }
}

void DisplayGraph::drawMode2() {
    mGraph->setFont(u8g_font_10x20);
    if (mIsEdit && (mPosEdit & ATC_EDIT_HOUR) && (mCntEdit & 1)) {
        strcpy(mBuf+0, ATC_Space2);
    } else {
        strNum(mNow.hour(), mBuf + 0, 2);
    }
    mBuf[2] = ':';
    if (mIsEdit && (mPosEdit & ATC_EDIT_MIN) && (mCntEdit & 1)) {
        strcpy(mBuf+3, ATC_Space2);
    } else {
        strNum(mNow.minute(), mBuf + 3, 2);
    }
    mBuf[5] = ':';
    if (mIsEdit && (mPosEdit & ATC_EDIT_SEC) && (mCntEdit & 1)) {
        strcpy(mBuf+6, ATC_Space2);
    } else {
        strNum(mNow.second(), mBuf + 6, 2);
    }
    mGraph->drawStr(24, 14, mBuf);

    strNum(mNow.day(), mBuf+0, 2);
    if (mIsEdit && (mPosEdit & ATC_EDIT_DAY) && (mCntEdit & 1)) {
        strcpy(mBuf+0, ATC_Space2);
    } else {
        strNum(mNow.day(), mBuf + 0, 2);
    }
    mBuf[2] = '.';
    if (mIsEdit && (mPosEdit & ATC_EDIT_MONTH) && (mCntEdit & 1)) {
        strcpy(mBuf+3, ATC_Space2);
    } else {
        strNum(mNow.month(), mBuf + 3, 2);
    }
    mBuf[5] = '.';
    if (mIsEdit && (mPosEdit & ATC_EDIT_YEAR) && (mCntEdit & 1)) {
        strcpy(mBuf+6, ATC_Space4);
    } else {
        strNum(mNow.year(), mBuf + 6, 4);
    }
    mGraph->drawStr(14, 38, mBuf);

    mGraph->setFont(u8g_font_8x13B);
    if (mTermo.getNumDev() > 0) {
        strNum(mTermo.getTermC(0), mBuf, 7, true, 3, false);
        mGraph->drawStr( (mTermoDesc ? 68 : 4), 62, mBuf);
    }
    if (mTermo.getNumDev() > 1) {
        strNum(mTermo.getTermC(1), mBuf, 7, true, 3, false);
        mGraph->drawStr((mTermoDesc ? 4 : 68), 62, mBuf);
    }
}

DisplayGraph::DisplayGraph(uint8_t aPinKey1, uint8_t aPinKey2, uint8_t aPinTerm, uint8_t aSizeTerm) :
    Display(aPinKey1, aPinKey2, aPinTerm, aSizeTerm),
    mGraph(new U8GLIB_SSD1306_128X64(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0)), mBuf()
{}

void DisplayGraph::init() {
    Display::init();

    for (uint8_t i=0; i < 12; ++i)
        mBuf[i] = '\0';

    // Display init
    mGraph->setRot180();
}

void DisplayGraph::draw() {
    mGraph->firstPage();
    do {
        if (mMode == ATC_MODE_GRAPH2) {
            drawMode2();
        } else {
            drawMode1();
        }
    } while( mGraph->nextPage() );
}

#endif
