/*
 * Copyright 2020 Micro:bit Educational Foundation and contributors
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "mbed.h"

#include "nrf_delay.h"

#include "FXOS8700Q/FXOS8700Q.h"
#include "LSM303AGR/X_NUCLEO_COMMON/DevI2C/DevI2C.h"
#include "LSM303AGR/LSM303AGRMagSensor.h"
#include "LSM303AGR/LSM303AGRAccSensor.h"


// Different boards have different I2C addresses for the sensors
#if defined(TARGET_NRF52_MICROBIT_v2)
    #define LSM_ACC_ADDR (0x19 << 1)
    #define LSM_MAG_ADDR (0x1E << 1)
    #define LSM_PRESENT 1
#elif defined(TARGET_NRF52_MICROBIT_v1_43)
    #define FXOS_ADDR (0x1F << 1)
    #define FXOS_PRESENT 1
    #define LSM_ACC_ADDR (0x19 << 1)
    #define LSM_MAG_ADDR (0x1E << 1)
    #define LSM_PRESENT 1
#elif defined(TARGET_NRF52_MICROBIT_v1_41)
    #define FXOS_ADDR (0x1E << 1)
    #define FXOS_PRESENT 1
#else
    #error "The selected target has not been configured in main.cpp."
#endif


int main(void) {
    // Initialise the serial
    Serial pc(USBTX, USBRX);
    pc.baud(115200);
    pc.printf("Starting programme.\n");

    DevI2C i2c(I2C_SDA0, I2C_SCL0);
    // This is an open drain combined interrupt line, not used in this example
    // but need the pull up to work
    DigitalIn sensor_int(COMBINED_SENSOR_INT);
    sensor_int.mode(PullUp);

#ifdef FXOS_PRESENT
    // Initialise the FXOS
    FXOS8700QAccelerometer accFxos(i2c, FXOS_ADDR);
    FXOS8700QMagnetometer magFxos(i2c, FXOS_ADDR);
    if ((accFxos.whoAmI() != 0xC7) || (magFxos.whoAmI() != 0xC7)) {
        pc.printf("Error reading the FXOS8700 Who Am I register.\n");
        for(;;);
    }
    accFxos.enable();
    magFxos.enable();
#endif
#ifdef LSM_PRESENT
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
#ifdef FXOS_PRESENT
        accFxos.getAxis(accFxosData);
        magFxos.getAxis(magFxosData);
        pc.printf("FXOS Acc: [X:%d] [Y:%d] [Z:%d]\n", accFxosData.x, accFxosData.y, accFxosData.z);
        pc.printf("FXOS Mag: [X:%d] [Y:%d] [Z:%d]\n", magFxosData.x, magFxosData.y, magFxosData.z);
#endif
#ifdef LSM_PRESENT
        accLsm.get_x_axes(accLsmData);
        magLsm.get_m_axes(magLsmData);
        pc.printf("\nLSM  Acc: [X:%d] [Y:%d] [Z:%d]\n", accLsmData[0], accLsmData[1], accLsmData[2]);
        pc.printf("LSM  Mag: [X:%d] [Y:%d] [Z:%d]\n", magLsmData[0], magLsmData[1], magLsmData[2]);
#endif
        pc.printf("---------\n");
        nrf_delay_ms(500);
    }
}
