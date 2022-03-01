/*
 * Copyright 2022 Micro:bit Educational Foundation and contributors
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

// I2C address of the on-board accelerometer & Who Am I values for LSM303AGR
#define ACC_I2C_ADDR    (0x19 << 1)
#define ACC_WHOAMI_REG  (0x0F)
#define ACC_WHOAMI_VAL  (0x33)

// Set up I2C with the internal I2C bus pins
I2C i2c(I2C_SDA0, I2C_SCL0);

// Set up serial and printf
UnbufferedSerial pc_serial(USBTX, USBRX, 115200);
FileHandle *mbed::mbed_override_console(int fd) {
    return &pc_serial;
}

// Simple function to read a single register from an I2C device
uint8_t i2c_read_register(uint8_t target_address, uint8_t reg_address) {
    uint8_t error = i2c.write(target_address, (char *)&reg_address, 1, true);
    if (error) {
        printf("Error performing an I2C write.");
        return 0;
    }
    uint8_t data = 0;
    error = i2c.read(target_address, (char *)&data, 1);
    if (error) {
        printf("Error performing an I2C read.");
    }
    return data;
}


int main(void) {
    uint8_t acc_who_am_i_value = i2c_read_register(ACC_I2C_ADDR, ACC_WHOAMI_REG);

    printf("I2C accelerometer Who Am I value: %d\n", acc_who_am_i_value);
    printf((acc_who_am_i_value == ACC_WHOAMI_VAL) ? "Success!\n" : "Invalid value :(\n");

    while (1);
}
