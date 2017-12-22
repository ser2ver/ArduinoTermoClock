#include "Display.h"

Display *display;

void setup() {
    // If Arduino 5V output is broken, use A0 and A1 for 5V power
//    pinMode(A0, OUTPUT);
//    pinMode(A1, OUTPUT);
//    digitalWrite(A0, HIGH);
//    digitalWrite(A1, HIGH);

    Serial.begin(9600);
    display = Display::make();
    display->init();
}

void loop() {
    display->fresh();
    display->draw();
    delay(50);
}
