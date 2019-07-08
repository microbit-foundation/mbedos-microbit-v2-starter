#include "mbed.h"

// LED matrix first row and column
#define COL_1    P0_1
#define ROW_1    P0_21


int main(void) {
    DigitalOut col1(COL_1, 0);
    DigitalOut row1(ROW_1, 1);
    col1 = 0;
    row1 = 1;

    while (true) {
        row1 = !row1;
        wait(0.5);
    }
}
