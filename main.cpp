#include "nrf52.h"
#include "nrf_soc.h"
#include "nrf_delay.h"
#include "nrf52_bitfields.h"
#include "hal/nrf_gpio.h"
#include "hal/nrf_gpiote.h"
#include "PinNames.h"
#include "FXOS8700Q/FXOS8700Q.h"

#define RUN_MIC P0_20
#define SPEAKER_1 P0_0

#define I2C_SCL P0_8
#define I2C_SDA P0_16

#define BUTTONA P0_14
#define BUTTONB P0_15

#define COL1 P0_1
#define COL2 P0_11

#define FXOS_ADDR (0x1E << 1)

const int addr = 0x1E << 1; // Uses 8-bit addresses

char fxos_cmd[2];

void system_off(){
    
    nrf_gpio_pin_clear(COL2);

    nrf_gpio_cfg_sense_input(BUTTONB, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    sd_power_system_off();
    NRF_POWER->SYSTEMOFF = 1;
    while(1);

}

int main(void)
{
    volatile int count = 0;
    
    // FXOS
    I2C i2c(I2C_SDA, I2C_SCL);
    FXOS8700QAccelerometer acc(i2c, FXOS_ADDR);
    FXOS8700QMagnetometer mag(i2c, FXOS_ADDR);

    // Check comms work
    if(acc.whoAmI() != 0xC7)
            while(1);

    acc.disable();
    mag.disable();
    
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

    // Disable MIC
    nrf_gpio_cfg(RUN_MIC,
                NRF_GPIO_PIN_DIR_OUTPUT,
                NRF_GPIO_PIN_INPUT_DISCONNECT,
                NRF_GPIO_PIN_NOPULL,
                NRF_GPIO_PIN_H0H1,
                NRF_GPIO_PIN_NOSENSE);        

    nrf_gpio_pin_clear(RUN_MIC);

    // Disable Speaker
    nrf_gpio_cfg( SPEAKER_1,
            NRF_GPIO_PIN_DIR_OUTPUT,
            NRF_GPIO_PIN_INPUT_DISCONNECT,
            NRF_GPIO_PIN_NOPULL,
            NRF_GPIO_PIN_H0H1,
            NRF_GPIO_PIN_NOSENSE);
    
    nrf_gpio_pin_clear(SPEAKER_1);
    
    // Button A to sleep
    nrf_gpio_cfg( BUTTONA,
            NRF_GPIO_PIN_DIR_INPUT,
            NRF_GPIO_PIN_INPUT_CONNECT,
            NRF_GPIO_PIN_NOPULL,
            NRF_GPIO_PIN_H0H1,
            NRF_GPIO_PIN_NOSENSE);
    
    while(1) {
        count++;
        nrf_delay_ms(500);
        nrf_gpio_pin_toggle(COL1);

        if(nrf_gpio_pin_read(BUTTONA) == 0)
                system_off();
        
    }

}
