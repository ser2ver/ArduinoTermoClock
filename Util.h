#ifndef ATC_UTIL_H
#define ATC_UTIL_H

#include <Arduino.h>

extern const char *Space2;
extern const char *Space4;

void strNum(float num, char *buf, uint8_t len, bool sig=false, uint8_t pos=0, bool fill=true);

#endif //ATC_UTIL_H
