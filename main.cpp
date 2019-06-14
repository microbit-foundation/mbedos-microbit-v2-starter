#include "nrf_delay.h"
#include "hal/nrf_gpio.h"
#include "PinNames.h"

#define COL1 P0_1
#define COL2 P0_11

int main(void)
{
    volatile int count = 0;

    // Config LED COL1
    nrf_gpio_cfg(COL1,
                NRF_GPIO_PIN_DIR_OUTPUT,
                NRF_GPIO_PIN_INPUT_DISCONNECT,
                NRF_GPIO_PIN_NOPULL,
                NRF_GPIO_PIN_H0H1,
                NRF_GPIO_PIN_NOSENSE);

    nrf_gpio_pin_set(COL1);

    // Config LED COL2
    nrf_gpio_cfg(COL2,
                NRF_GPIO_PIN_DIR_OUTPUT,
                NRF_GPIO_PIN_INPUT_DISCONNECT,
                NRF_GPIO_PIN_NOPULL,
                NRF_GPIO_PIN_H0H1,
                NRF_GPIO_PIN_NOSENSE);

    nrf_gpio_pin_set(COL2);

    while(1) {
        count++;
        nrf_delay_ms(500);
        nrf_gpio_pin_toggle(COL1);
    }

}
