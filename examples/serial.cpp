#include "mbed.h"

int main(void) {
    Serial pc(USBTX, USBRX);
    pc.baud(115200);
    pc.printf("hello world!\n");

    // Echo back
    while (true) {
        while (pc.readable()) {
            uint32_t val = pc.getc();
            pc.putc(val);
        }
    }
}
