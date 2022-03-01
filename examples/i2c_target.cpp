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
#include "nrf_delay.h"

#if !DEVICE_I2CSLAVE
  #error [NOT_SUPPORTED] I2C Target mode is not supported
#endif

#define BUTTON_PRESSED  0


/*****************************************************************************/
/* Serial                                                                   */
/*****************************************************************************/
UnbufferedSerial pc(CONSOLE_TX, CONSOLE_RX, 115200);

FileHandle *mbed::mbed_override_console(int fd) {
    return &pc;
}

/*****************************************************************************/
/* I2C data to send between devices                                          */
/*****************************************************************************/
#define TARGET_ADDR_8BIT (0xA0 << 1)
const char MSG[] = "Slave!";
const uint8_t MSG_LEN = 7;

/*****************************************************************************/
/* LED functions                                                             */
/*****************************************************************************/
void conf_op_pin(PinName pin) {
    nrf_gpio_cfg(pin,
        NRF_GPIO_PIN_DIR_OUTPUT,
        NRF_GPIO_PIN_INPUT_DISCONNECT,
        NRF_GPIO_PIN_NOPULL,
        NRF_GPIO_PIN_H0H1,
        NRF_GPIO_PIN_NOSENSE);
}

void set_led_1(bool set) {
    set ? nrf_gpio_pin_clear(COL_1) : nrf_gpio_pin_set(COL_1);
}

void set_led_2(bool set) {
    set ? nrf_gpio_pin_clear(COL_2) : nrf_gpio_pin_set(COL_2);
}

void leds_init() {
    conf_op_pin(COL_1);
    nrf_gpio_pin_clear(COL_1);
    conf_op_pin(COL_2);
    nrf_gpio_pin_clear(COL_2);
    conf_op_pin(ROW_1);
    nrf_gpio_pin_set(ROW_1);
    set_led_1(false);
    set_led_2(false);
}

void error_loop() {
    while(1) {
        set_led_1(true);
        set_led_2(false);
        nrf_delay_ms(250);
        set_led_1(false);
        set_led_2(true);
        nrf_delay_ms(250);
    }
}

/*****************************************************************************/
/* I2C functions                                                             */
/*****************************************************************************/
void test_master() {
    I2C controller(I2C_SDA1, I2C_SCL1);

    uint8_t rxData[MSG_LEN] = { 0 };
    int result = 0;

    while (true) {
        const uint8_t I2C_MSG_SLEEP = 0xAB;
        uint8_t txData[1] = { I2C_MSG_SLEEP };
        result = controller.write(TARGET_ADDR_8BIT, (char *)&txData, 1, false);
        if (result != 0) {
            printf("Write error: %d\n", result);
            return;
        }

        result = controller.read(TARGET_ADDR_8BIT, (char *)&rxData, MSG_LEN);
        if (result != 0) {
            printf("Read error: %d\n", result);
            return;
        }
        for (uint8_t i = 0; i < MSG_LEN; i++) {
            if (rxData[i] != MSG[i]) {
                printf("Message unexpected at chacter %d\n", i);
                printf("Read buffer: %s\n", rxData);
                return;
            }
            rxData[i] = 0;    // Reset it for next iteration
        }
        nrf_delay_ms(250);
    }
}


void test_slave() {
    I2CSlave target(I2C_SDA1, I2C_SCL1);
    target.address(TARGET_ADDR_8BIT);

    char buf[10];
    while (true) {
        int i = target.receive();
        switch (i) {
            case I2CSlave::ReadAddressed:
                target.write(MSG, MSG_LEN);
                printf("Received a read command");
               break;
            case I2CSlave::WriteGeneral:
                target.read(buf, 10);
                printf("Read General: %s\n", buf);
                break;
            case I2CSlave::WriteAddressed:
                target.read(buf, 10);
                printf("Read Address: %s\n", buf);
                break;
        }
        for(int i = 0; i < 10; i++) buf[i] = 0;    // Clear buffer
    }
}

/*****************************************************************************/
/* main                                                                      */
/*****************************************************************************/
int main(void) {
    printf("I2C programme starting.\r\n");

    DigitalIn buttonA(BUTTONA);
    DigitalIn buttonB(BUTTONB);

    leds_init();

    while (true) {
        if (buttonA == BUTTON_PRESSED) {
            printf("MAIN device\r\n");
            set_led_1(true);
            test_master();
            break;
        }
        if (buttonB == BUTTON_PRESSED) {
            printf("SECONDARY device\r\n");
            set_led_2(true);
            test_slave();
            break;
        }
    }

    // test functions only return on failure
    error_loop();
}
