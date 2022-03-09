/*
 * Copyright 2020-2022 Micro:bit Educational Foundation and contributors
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

#define ROW_COUNT   5
#define COL_COUNT   5

#if defined(MICROBIT_TARGET)
    // Main micro:bit target has access to the LED matrix and on-board features
    DigitalOut rows[ROW_COUNT] = {
        DigitalOut(ROW_1, 0),
        DigitalOut(ROW_2, 0),
        DigitalOut(ROW_3, 0),
        DigitalOut(ROW_4, 0),
        DigitalOut(ROW_5, 0)
    };
    DigitalOut cols[COL_COUNT] = {
        DigitalOut(COL_1, 1),
        DigitalOut(COL_2, 1),
        DigitalOut(COL_3, 1),
        DigitalOut(COL_4, 1),
        DigitalOut(COL_5, 1)
    };
    bool led1 = false;
    bool led2 = false;
#else
    // The nRF52833 DK and micro:bit V2.2 IF MCU have access to direct LEDs
    bool rows[ROW_COUNT];
    bool cols[COL_COUNT];
    DigitalOut led1(LED1, 0);
    DigitalOut led2(LED2, 1);
#endif

int main(void) {
    // Infinite loop to blink the matrix LEDs if built for the target MCU or
    // to toggle the orange and red USB LEDs if built for the interface MCU
    while (true) {
        for (int i = 0, prev_i = ROW_COUNT - 1; i < ROW_COUNT; ++i, prev_i = i - 1) {
            rows[i] = true;
            rows[prev_i] = false;
            for (int j = 0, prev_j = COL_COUNT - 1; j < COL_COUNT; ++j, prev_j = j - 1) {
                cols[j] = false;
                cols[prev_j] = true;

                led1 = !led1;
                led2 = !led2;

                ThisThread::sleep_for(250);
                //wait_us(250000);
            }
        }
    }
}
