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
#include "USBSerial.h"
#include "USBCDC.h"

// WARNING! This example currently only works with the nRF52833 DK board!

/**
 * USBSerial or USBCDC can both be used (not simultaneously) and they have
 * the same constructor.
 */
// USBSerial usb_serial(
USBCDC usb_serial (
    false,   // connect_blocking
    0x0d28,  // vendor_id (test value from DAPLink)
    0x0204,  // product_id (test value from DAPLink)
    0x0001   // product_release
);

int main(void) {
    char msgUSB[] = "Hello from nRF52 USB CDC!\r\n";
    DigitalOut led_orange(LED1, 0);
    DigitalOut led_red(LED2, 0);

    // Blink both LEDs to show the programme is running
    ThisThread::sleep_for(250);
    led_orange = 1;
    led_red = 1;
    ThisThread::sleep_for(250);
    led_orange = 0;
    led_red = 0;

    // Block here and blink the red LED until the CDC port is connected
    usb_serial.connect();
    while (!usb_serial.ready()) {
        ThisThread::sleep_for(250);
        led_red = !led_red;
    }
    led_red = 1;

    // Send a message via USB CDC and blink the orange LED
    while (true) {
        ThisThread::sleep_for(1000);
        led_orange = !led_orange;
        usb_serial.send((uint8_t *)msgUSB, strlen(msgUSB));
        //usb_serial.printf(msgUSB); // printf only available with USBSerial constructor
    }
}
