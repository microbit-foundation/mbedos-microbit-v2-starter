#include "mbed.h"
#include "nrf_delay.h"

#define OFF 0
#define C6  1
#define Cs6 2
#define D6  3
#define Ds6 4
#define E6  5
#define F6  6
#define Fs6 7
#define G6  8
#define Gs6 9
#define A6  10
#define As6 11
#define B6  12
#define C7  13
#define Cs7 14
#define D7  15
#define Ds7 16
#define E7  17
#define F7  18
#define Fs7 19
#define G7  20
#define Gs7 21
#define A7  22
#define As7 23
#define B7  24
#define C8  25

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
    switch(note) {
        case OFF:
            return 0.0;
        case C6:
            return 1046.50;
        case Cs6:
            return 1108.73;
        case D6:
            return 1174.66;
        case Ds6:
            return 1244.51;
        case E6:
            return 1318.51;
        case F6:
            return 1396.91;
        case Fs6:
            return 1479.98;
        case G6:
            return 1567.98;
        case Gs6:
            return 1661.22;
        case A6:
            return 1760.00;
        case As6:
            return 1864.66;
        case B6:
            return 1975.53;
        case C7:
            return 2093.00;
        case Cs7:
            return 2217.46;
        case D7:
            return 2349.32;
        case Ds7:
            return 2489.02;
        case E7:
            return 2637.02;
        case F7:
            return 2793.83;
        case Fs7:
            return 2959.96;
        case G7:
            return 3135.96;
        case Gs7:
            return 3322.44;
        case A7:
            return 3520.00;
        case As7:
            return 3729.31;
        case B7:
            return 3951.07;
        case C8:
            return 4186.01;
        default:
            return 0.0;
    }
}

void play_note(uint8_t note) {
        if(note_to_hz(note) == 0) {
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
