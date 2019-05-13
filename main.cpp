#include "mbed.h"

int main() {
    volatile int count = 0;
    while (true) {
        count++;
    }
}
