#include "Termo.h"

void Termo::init() {
    // Temperature sensors init
    mSensors.begin();

    // report parasite power requirements
    Serial.print("Parasite power is: ");
    if (mSensors.isParasitePowerMode())
        Serial.println("ON");
    else
        Serial.println("OFF");

    // locate devices on the bus
    mNumDev = mSensors.getDeviceCount();
    mDevices = new DeviceAddress[mNumDev];

    for (int i=0; i < mNumDev; ++i) {
        // set the addresses we found on the bus
        if (!mSensors.getAddress(mDevices[i], i)) {
            Serial.print("Unable to find address for Device ");
            Serial.println(i, DEC);
            continue;
        }

        Serial.print("Device ");
        Serial.print(i, DEC);
        Serial.print(" Address: ");
        for (uint8_t j = 0; j < 8; j++) {
            // zero pad the address if necessary
            if (mDevices[i][j] < 16) {
                Serial.print("0");
            }
            Serial.print(mDevices[i][j], HEX);
        }
        Serial.println();

        // set the resolution to 10 bit per device
        mSensors.setResolution(mDevices[i], mSize);

        Serial.print("Device ");
        Serial.print(i, DEC);
        Serial.print(" Resolution: ");
        Serial.print(mSensors.getResolution(mDevices[i]), DEC);
        Serial.println();
    }
}
