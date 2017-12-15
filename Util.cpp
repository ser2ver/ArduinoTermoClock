#include "Util.h"

const char *Space2 = "  ";
const char *Space4 = "    ";

void strNum(float num, char *buf, uint8_t len, bool sig, uint8_t pos, bool fill) {
    int x = floor(fabs(num));
    int8_t p = len;
    int8_t b = (sig || (num < 0)) ? 1 : 0;

    buf[p--] = '\0';

    if (pos > 0)
        p -= pos + 1;

    for ( ; p >= b; --p) {
        buf[p] = '0' + (x % 10);
        x /= 10;
        if (!fill && !x) {
            --p;
            break;
        }
    }

    if (num < 0) {
        buf[p--] = '-';
    } else if (sig) {
        buf[p--] = '+';
    }

    for ( ; p >= 0; --p) {
        buf[p] = ' ';
    }

    if (pos > 0) {
        b = len - pos - 1;
        num = fabs(num);
        num -= floor(num);

        buf[b] = '.';
        for (p=1; p < pos; ++p) {
            x = floor(num * 10);
            num = num * 10 - x;
            buf[b+p] = '0' + x;
        }
        x = round(num * 10);
        buf[b+p] = '0' + x;
    }
}
