#ifndef ATC_TERMO_H
#define ATC_TERMO_H

#include "Settings.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class Termo {
private:
    uint8_t mPin;
    uint8_t mSize;
    uint8_t mNumDev;

    OneWire mWire;
    DallasTemperature mSensors;
    DeviceAddress *mDevices;

public:
    explicit Termo(uint8_t aPin, uint8_t aSize=10) :
            mPin(aPin), mSize(aSize), mNumDev(0),
            mWire(aPin), mSensors(&mWire), mDevices(NULL)
    {}
    virtual ~Termo() {}

    void init();

    void reload() {
        mSensors.requestTemperatures();
    }

    uint8_t getSize() const { return mSize; }
    void setSize(uint8_t aSize);

    uint8_t getNumDev() const { return mNumDev; }
    float getTermC(uint8_t aDevNum=0) {
        return mSensors.getTempC(mDevices[aDevNum]);
    }
};

#endif //ATC_TERMO_H
