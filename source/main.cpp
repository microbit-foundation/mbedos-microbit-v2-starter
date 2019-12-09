#include "mbed.h"
#include "nrf_delay.h"
#include <math.h>

#ifdef TARGET_NRF52_MICROBIT_v1_41
    #define RUN_MIC P0_20
    #define SPEAKER P0_0
    // EC pin 0
    #define AUDIO_PIN P0_2
    #define FXOS_ADDR (0x1E << 1)
#elif TARGET_NRF52_MICROBIT_v1_43
    #define RUN_MIC P0_20
    #define SPEAKER P0_0
    // EC pin 0
    #define AUDIO_PIN P0_2
    #define FXOS_ADDR (0x1F << 1)
    #define LSM_ACC_ADDR (0x19 << 1)
    #define LSM_MAG_ADDR (0x1E << 1)
#else
    #error "The selected target has not been configured in main.cpp."
#endif

Serial pc(USBTX, USBRX); // tx, rx
char buffer[20];
uint8_t buffer_p = 0;

PwmOut speaker(SPEAKER);

float note_to_hz(uint8_t note) {
    // A 440hz
    return 440.0 * pow(2, ((float)(note - 58)/12.0));
}

void play_note(uint8_t note) {
        if(note == 0) {
            speaker.write(0.0);
            return;
        }

        float p = 1.0/note_to_hz(note);
        speaker.write(0.5);
        speaker.period(p);

        return;
}

int main(void) {
    Serial pc(USBTX, USBRX);
    pc.baud(115200);
    pc.printf("hello world!\n");

    // Echo back
    while (true) {
        while (pc.readable()) {
            uint8_t val = pc.getc();
            pc.putc(val);
            play_note(val);
        }
    }
}
