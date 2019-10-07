#include "mbed.h"
#include "nrf_delay.h"

#define SPEAKER P0_0
#define AUDIO_PIN P0_2
#define BUTTONA P0_14

PwmOut speaker(SPEAKER);

void audio_sweep() {
    speaker.write(0.5f);      // 0.5 width

    for(int i = 10; i < 2000; i += 5) {
            float f = 1.0f/(float)i;
            speaker.period(f);
            nrf_delay_ms(31); // From MakeCode: music.beat(BeatFraction.Sixteenth)
    }
    
    speaker.write(0.0f);      // 0 width

}

int main() {

    speaker.period(4.0f);      // 4 second period
    speaker.write(0.0f);      // 0 width
    
   // Button A to start
   nrf_gpio_cfg( BUTTONA,
           NRF_GPIO_PIN_DIR_INPUT,
           NRF_GPIO_PIN_INPUT_CONNECT,
           NRF_GPIO_PIN_NOPULL,
           NRF_GPIO_PIN_H0H1,
           NRF_GPIO_PIN_NOSENSE);


    volatile int count = 0;
    while (true) {

        if(nrf_gpio_pin_read(BUTTONA) == 0) {
            audio_sweep();
        }

        nrf_delay_ms(300);

    }
}
