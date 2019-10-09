#include "mbed.h"
#include "nrf_delay.h"
#include "FXOS8700Q/FXOS8700Q.h"
#include "LSM303AGR/X_NUCLEO_COMMON/DevI2C/DevI2C.h"
#include "LSM303AGR/LSM303AGRMagSensor.h"
#include "LSM303AGR/LSM303AGRAccSensor.h"


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


PwmOut speaker(SPEAKER);

I2C *i2c;
FXOS8700QAccelerometer *accFxos;
FXOS8700QMagnetometer *magFxos;
#ifdef TARGET_NRF52_MICROBIT_v1_43
LSM303AGRAccSensor *accLsm;
LSM303AGRMagSensor *magLsm;
volatile uint8_t whoAmIAccVal = 0;
volatile uint8_t whoAmIMagVal = 0;
#endif

void sensors_init() {
#ifdef TARGET_NRF52_MICROBIT_v1_41
    i2c = new I2C(I2C_SDA0, I2C_SCL0);
#elif TARGET_NRF52_MICROBIT_v1_43
    i2c = new DevI2C(I2C_SDA0, I2C_SCL0);
    accLsm = new LSM303AGRAccSensor((DevI2C *)i2c);
    magLsm = new LSM303AGRMagSensor((DevI2C *)i2c, LSM_MAG_ADDR);

    // During testing of the v1.43.4 boards we found that without this delay
    // the LSM303 accelerometer would fail the Who Am I test below
    nrf_delay_us(1850);

    if ((magLsm->read_id((uint8_t*)&whoAmIMagVal) != 0) || (whoAmIMagVal != 0x40) ||
            (accLsm->read_id((uint8_t*)&whoAmIAccVal) != 0) || (whoAmIAccVal != 0x33)) {
        while (1);
    }
    accLsm->init(NULL);
    accLsm->enable();
    magLsm->init(NULL);
    magLsm->enable();
#endif

    accFxos = new FXOS8700QAccelerometer(*i2c, FXOS_ADDR);
    magFxos = new FXOS8700QMagnetometer(*i2c, FXOS_ADDR);
    if ((accFxos->whoAmI() != 0xC7) || (magFxos->whoAmI() != 0xC7)) {
        while (1);
    }
    accFxos->enable();
    magFxos->enable();
    // Should be set to 400K in the FXOS constructor, but just in case
    i2c->frequency(400000);
}

// Only reads a single Who Am I at a time, but rotates through them
void read_sensor() {
    static int8_t count = 0;
    switch (count) {
        case 0:
            (void) accFxos->whoAmI();
            break;
        case 1:
            (void) magFxos->whoAmI();
            // Fall-through only on v1.41
#ifdef TARGET_NRF52_MICROBIT_v1_43
            break;
        case 2:
            magLsm->read_id((uint8_t*)&whoAmIMagVal);
            break;
        case 3:
            accLsm->read_id((uint8_t*)&whoAmIAccVal);
            // Intentional fall-through
#endif
        default:
            count = -1;
            break;
    }
    count++;
}

void audio_sweep() {
    speaker.write(0.5f);      // 0.5 width

    for(int i = 10; i < 2000; i += 5) {
            float f = 1.0f/(float)i;
            speaker.period(f);
            // This affects the timing significantly, but not sure why
            // At 400K one byte takes 20 microseconds, this should be < 100 us
            read_sensor();
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
