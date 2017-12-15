#include "DisplayText.h"

const uint8_t keyPin1  = 2; // Specify pin for button 1
const uint8_t keyPin2  = 3; // Specify pin for button 2

const uint8_t tempPin  = 4; // Specify pin for Temperature sensor
const uint8_t tempSize = 11;// Specify accuracy for Temperature sensor

Display *display;

void setup() {
    Serial.begin(9600);

    display = new DisplayText(keyPin1, keyPin2, tempPin, tempSize);

    display->init();

    display->fresh();
    display->console();
}

void loop() {
    display->fresh();
//    display->console();
    display->draw();

    delay(50);
}
