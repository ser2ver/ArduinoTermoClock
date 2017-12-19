#include "Display.h"

Display *display;

void setup() {
    Serial.begin(9600);
    display = Display::make();
    display->init();
}

void loop() {
    display->fresh();
    display->draw();
    delay(50);
}
