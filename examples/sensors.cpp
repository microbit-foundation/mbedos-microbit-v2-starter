#include "mbed.h"

#include "nrf_delay.h"

#include "FXOS8700Q/FXOS8700Q.h"
#include "LSM303AGR/X_NUCLEO_COMMON/DevI2C/DevI2C.h"
#include "LSM303AGR/LSM303AGRMagSensor.h"
#include "LSM303AGR/LSM303AGRAccSensor.h"


// Different boards have different I2C addresses for the sensors
#ifdef TARGET_NRF52_MICROBIT_v1_41
    #define FXOS_ADDR (0x1E << 1)
#elif TARGET_NRF52_MICROBIT_v1_43
    #define FXOS_ADDR (0x1F << 1)
    #define LSM_ACC_ADDR (0x19 << 1)
    #define LSM_MAG_ADDR (0x1E << 1)
#else
    #error "The selected target has not been configured in main.cpp."
#endif


int main(void) {
    // Initialise the serial
    Serial pc(USBTX, USBRX);
    pc.baud(115200);

    // Initialise the FXOS
    DevI2C i2c(I2C_SDA0, I2C_SCL0);
    FXOS8700QAccelerometer accFxos(i2c, FXOS_ADDR);
    FXOS8700QMagnetometer magFxos(i2c, FXOS_ADDR);
    if ((accFxos.whoAmI() != 0xC7) || (magFxos.whoAmI() != 0xC7)) {
        pc.printf("Error reading the FXOS8700 Who Am I register.\n");
        for(;;);
    }
    accFxos.enable();
    magFxos.enable();

#ifdef TARGET_NRF52_MICROBIT_v1_43
    // Initialise the LSM303 only on v1.43
    LSM303AGRAccSensor accLsm(&i2c, LSM_ACC_ADDR);
    LSM303AGRMagSensor magLsm(&i2c, LSM_MAG_ADDR);

    uint8_t whoAmIAccVal = 0;
    uint8_t whoAmIMagVal = 0;
    if ((magLsm.read_id(&whoAmIMagVal) != 0) || (whoAmIMagVal != 0x40)) {
        pc.printf("Error reading the LSM303 Mag Who Am I register.\n");
        for(;;);
    }
    if ((accLsm.read_id(&whoAmIAccVal) != 0) || (whoAmIAccVal != 0x33)) {
        pc.printf("Error reading the LSM303 Acc Who Am I register.\n");
        for(;;);
    }
    accLsm.init(NULL);
    magLsm.init(NULL);
    accLsm.enable();
    magLsm.enable();
#endif

    // Send to the serial the FXOS and LSM accelerometer and magnetometer readings
    motion_data_counts_t accFxosData, magFxosData;
    int32_t accLsmData[3], magLsmData[3];
    while (true) {
        accFxos.getAxis(accFxosData);
        magFxos.getAxis(magFxosData);
        pc.printf("FXOS Acc: [X:%d] [Y:%d] [Z:%d]\n", accFxosData.x, accFxosData.y, accFxosData.z);
        pc.printf("FXOS Mag: [X:%d] [Y:%d] [Z:%d]\n", magFxosData.x, magFxosData.y, magFxosData.z);

#ifdef TARGET_NRF52_MICROBIT_v1_43
        accLsm.get_x_axes(accLsmData);
        magLsm.get_m_axes(magLsmData);
        pc.printf("\nLSM  Acc: [X:%d] [Y:%d] [Z:%d]\n", accLsmData[0], accLsmData[1], accLsmData[2]);
        pc.printf("LSM  Mag: [X:%d] [Y:%d] [Z:%d]\n", magLsmData[0], magLsmData[1], magLsmData[2]);
#endif
        pc.printf("---------\n");
        nrf_delay_ms(500);
    }
}
