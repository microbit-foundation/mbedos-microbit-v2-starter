#include "mbed.h"

DigitalOut rows[5] = {
    DigitalOut(ROW_1, 0),
    DigitalOut(ROW_2, 0),
    DigitalOut(ROW_3, 0),
    DigitalOut(ROW_4, 0),
    DigitalOut(ROW_5, 0)
};
DigitalOut cols[5] = {
    DigitalOut(COL_1, 1),
    DigitalOut(COL_2, 1),
    DigitalOut(COL_3, 1),
    DigitalOut(COL_4, 1),
    DigitalOut(COL_5, 1)
};

int main(void) {
    //DigitalOut led(LED1, 0);

    while (true) {
        for (int i = 0; i < 5; i++) {
            rows[i] = 1;
            int prev_i = i - 1;
            if (prev_i < 0) prev_i = 4;
            rows[prev_i] = 0;
            for (int j = 0; j < 5; j++) {
                cols[j] = 0;
                int prev_j = j - 1;
                if (prev_j < 0) prev_j = 4;
                cols[prev_j] = 1;
                wait(0.25);
                //led = !led;
            }
        }
    }
}
