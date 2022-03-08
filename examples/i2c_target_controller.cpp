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
/**
 * Programme Description
 * ---------------------
 * 
 * This is an single I2C programme, which is compiled twice, to exemplify
 * I2C communication between an I2C controller and I2C target.
 * 
 * As the micro:bit V2.20 has an nRF52 Interface MCU connected to the internal
 * I2C bus controlled by the Target nRF52 MCU, this project has been configured
 * to be run with a single micro:bit and compiled for two Mbed targets:
 * - `nrf52_microbit_v2`: This will be the I2C Controller programme running
 *   in the Target MCU.
 * - `nrf52_microbit_v2_if_833`: This will be the I2C Target programme running
 *   in the Interface MCU.
 * 
 * 
 * Instructions
 * ------------
 * 
 * As it currently stands, this example can only be run with a micro:bit V2.2.
 * 
 * - First build the I2C Controller programme
 *     $ mbed compile -m nrf52_microbit_v2
 * - Flash the I2C Controller hex file into the MICROBIT drive.
 * - Then build the I2C Target programme:
 *     $ mbed compile -m nrf52_microbit_v2_if_833
 * - Enter MAITENANCE mode by unplugging the USB cable and pressing the reset
 *   button while reattaching the USB cable.
 * - And flash the I2C Target hex file into the MAINTENANCE drive.
 *     - At the end, to restore the MICROBIT drive flash a "Firmware" hex file
 *       to the MAITNENANCE drive as indicated in https://microbit.org/firmware
 * 
 * Now both programmes should be running on the same micro:bit V2.2.
 * 
 * When power is applied to the board these LEDs will flash twice:
 * - The USB orange and the USB red LEDs
 *     - These two LEDs are controlled by the Interface MCU as the I2C Target
 * - The LED matrix LEDs (0,0) and (1,0)
 *     - The LED matrix is controlled by the Target MCU as the I2C Controller
 * 
 * Then the USB orange LED will stay ON, that means the I2C Target is awaiting.
 * And the LED (0,0) in the matrix will be flashing, this means the I2C
 * Controller is awaiting for user input before starting to run.
 * 
 * Press button A to start executing I2C write and read transaction.
 * Now the USB orange LED and LED (0,0) in the matrix should be steady ON.
 * 
 * As the transactions complete successful LED (1,0) in the matrix and the
 * USB red LED will be flashing. This indicates both programmes are running
 * successfully.
 * 
 * If an error is encountered both LEDs for both microcontrollers will start
 * flashing.
 * 
 * 
 * Using two micro:bits instead of a single V2.2 micro:bit
 * -------------------------------------------------------
 * 
 * This programme can be adapted to be used with two micro:bits V2 (including
 * V2.00, which does not have an nRF52 Interface MCU) and to use the external
 * I2C bus accessible via the edge connector instead of the internal bus.
 * 
 * To do this you'll need to build twice for the `nrf52_microbit_v2` target
 * and manually change the `#define BUILD_I2C_CONTROLLER` line to
 * `#define BUILD_I2C_TARGET` for the second build.
 * Every `I2C_SDA0` and `I2C_SCL0` instance must also be changed to `I2C_SDA1`
 * and `I2C_SCL1` to select the external I2C bus.
 * 
 * This has been tested with a micro:bit V2.00 and V2.20 connected via jumper
 * cables (pins 19, 20, and ground) and works.
 * ***************************************************************************/
#include "mbed.h"

/*****************************************************************************/
/* Define roles                                                              */
/*****************************************************************************/
#if defined(MICROBIT_TARGET)
    #define BUILD_I2C_CONTROLLER
#elif defined(MICROBIT_IF)
    #define BUILD_I2C_TARGET
#endif

/*****************************************************************************/
/* I2C data to send between devices                                          */
/*****************************************************************************/
#define I2C_ADDR_8BIT_ (0x2E << 1)
char MSG_CONTROLLER_TO_TARGET[] = "Hello world!";
const uint8_t MSG_C2T_LEN = 13;
char MSG_TARGET_TO_CONTROLLER[] = "Hi back!";
const uint8_t MSG_T2C_LEN = 9;

#if defined(BUILD_I2C_CONTROLLER)
#define test_i2c test_controller
#elif defined(BUILD_I2C_TARGET)
#define test_i2c test_target
#endif

/*****************************************************************************/
/* Serial                                                                    */
/*****************************************************************************/
#ifdef MICROBIT_TARGET
UnbufferedSerial pc(CONSOLE_TX, CONSOLE_RX, 115200);

FileHandle *mbed::mbed_override_console(int fd) {
    return &pc;
}
#endif

/*****************************************************************************/
/* LEDs & Buttons                                                            */
/*****************************************************************************/
#define BUTTON_PRESSED      0
#ifdef MICROBIT_TARGET
    DigitalOut col1(COL_1, 0);
    DigitalOut led1(ROW_1, 0);
    DigitalOut led2(ROW_2, 0);
#else
    DigitalOut led1(LED1, 0);
    DigitalOut led2(LED2, 0);
#endif

/*****************************************************************************/
/* I2C functions                                                             */
/*****************************************************************************/
uint8_t test_controller() {
    printf("I2C Controller test running...\n");

    I2C controller(I2C_SDA0, I2C_SCL0);

    uint8_t error_return = 0;
    int i2c_error = 0;
    while (true) {
        i2c_error = controller.write(
            I2C_ADDR_8BIT_, MSG_CONTROLLER_TO_TARGET, MSG_C2T_LEN, false
        );
        if (i2c_error) {
            printf("Error: I2C write (tx): %d\n", i2c_error);
            error_return |= 1 << 0;
        } else {
            printf("I2C write, TX data: %s\n", MSG_CONTROLLER_TO_TARGET);
        }

        led2 = !led2;
        wait_us(250 * 1000);

        char rx_data[MSG_T2C_LEN] = { 0 };
        i2c_error = controller.read(I2C_ADDR_8BIT_, &rx_data[0], MSG_T2C_LEN, false);
        if (i2c_error) {
            printf("Error: I2C read (rx): %d\n", i2c_error);
            error_return |= 1 << 1;
        } else {
            printf("I2C read, rx data: %s\n", rx_data);
            for (int i = 0; i < MSG_T2C_LEN; i++) {
                if (rx_data[i] != MSG_TARGET_TO_CONTROLLER[i]) {
                    printf("Message unexpected at chacter %d\n", i);
                    error_return |= 1 << 2;
                    break;
                }
            }
        }

        led2 = !led2;
        wait_us(250 * 1000);

        if (error_return) {
            return error_return;
        }
    }
}

uint8_t test_target() {
    printf("I2C Target test running...\n");

    I2CSlave target(I2C_SDA0, I2C_SCL0);
    target.address(I2C_ADDR_8BIT_);

    int error = 0;
    while (true) {
        int status = target.receive();
        switch (status) {
            case I2CSlave::ReadAddressed:
                led2 = !led2;
                error = target.write(MSG_TARGET_TO_CONTROLLER, MSG_T2C_LEN);
                if (error) {
                    printf("Error: I2C read (tx): %d\n", error);
                    return 1;
                }
                printf("I2C read, TX data: %s\n", MSG_TARGET_TO_CONTROLLER);
               break;
            case I2CSlave::WriteGeneral:
            case I2CSlave::WriteAddressed:
                led2 = !led2;
                char rx_buf[MSG_C2T_LEN] = { 0 };
                error = target.read(rx_buf, MSG_C2T_LEN);
                if (error) {
                    printf("Error: I2C write (rx): %d\n", error);
                    return 2;
                }
                printf("I2C write, RX data: %s\n", rx_buf);
                for (int i = 0; i < MSG_C2T_LEN; i++) {
                    if (rx_buf[i] != MSG_CONTROLLER_TO_TARGET[i]) {
                        printf("Error: Message unexpected at chacter %d\n", i);
                        return 3;
                    }
                }
                target.stop();
                break;
        }
    }
    return 0;
}

/*****************************************************************************/
/* main                                                                      */
/*****************************************************************************/
int main(void) {
    uint8_t error_code = 0;
    DigitalIn button(BUTTON1);

    printf("I2C programme starting.\r\n");

    // Blink the two LEDs twice show the programme is running
    for (int i = 0; i < 4; i++) {
        led1 = !led1;
        led2 = !led2;
        wait_us(250 * 1000);
    }

    while (true) {
#ifdef BUILD_I2C_CONTROLLER
        // If this is the I2C controller wait (blinking) until a button press
        if (button != BUTTON_PRESSED)
        {
            led1 = !led1;
            wait_us(500 * 1000);
        }
        else
#endif
        {
            led1 = true;
            error_code = test_i2c();
            break;
        }
    }

    // Reaching this point indicates an error indicated in the flashing LEDs
    printf("Error code %d detected :(\n", error_code);
    while (true) {
        // First toggle the two LEDs alternatively and stop for a second
        for (int i = 0; i < 3; i++) {
            led1 = true;
            led2 = false;
            wait_us(250 * 1000);
            led1 = false;
            led2 = true;
            wait_us(250 * 1000);
        }
        led1 = false;
        led2 = false;
        wait_us(1000 * 1000);
        // Then flash both LEDs as many times as indicated by the error code
        for (int i = 0; i < (error_code * 2); i++) {
            led1 = !led1;
            led2 = !led2;
            wait_us(500 * 1000);
        }
        wait_us(500 * 1000);
    }
}
