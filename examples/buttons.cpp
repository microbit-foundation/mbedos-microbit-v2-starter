#include "mbed.h"

#define PRESSED      (0)
#define NOT_PRESSED  (1)

int main(void) {
    DigitalIn buttonA(BUTTONA, PullNone);
    DigitalIn buttonB(BUTTONB, PullNone);

    DigitalOut rows[5] = {
        DigitalOut(ROW_1, 0),
        DigitalOut(ROW_2, 0),
        DigitalOut(ROW_3, 0),
        DigitalOut(ROW_4, 0),
        DigitalOut(ROW_5, 0)
    };
    DigitalOut cols[5] = {
        DigitalOut(COL_1, 0),
        DigitalOut(COL_2, 0),
        DigitalOut(COL_3, 0),
        DigitalOut(COL_4, 0),
        DigitalOut(COL_5, 0)
    };

    while(1) {
        if (buttonA.read() == PRESSED) {
            rows[0] = 1;
            cols[0] = 0;
        } else {
            rows[0] = 0;
            cols[0] = 0;
        }
        if (buttonB.read() == PRESSED) {
            rows[1] = 1;
            cols[1] = 0;
        } else {
            rows[1] = 0;
            cols[1] = 0;
        }
    }
}
