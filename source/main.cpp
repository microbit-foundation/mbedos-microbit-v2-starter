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

DigitalOut rows[5] = {
    DigitalOut(ROW_1, 0),
    DigitalOut(ROW_2, 0),
    DigitalOut(ROW_3, 0),
    DigitalOut(ROW_4, 0),
    DigitalOut(ROW_5, 0)
};
DigitalOut cols[5] = {
    DigitalOut(COL_1, 1),
    DigitalOut(COL_2, 1),
    DigitalOut(COL_3, 1),
    DigitalOut(COL_4, 1),
    DigitalOut(COL_5, 1)
};

#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif

int main(void) {
    while (true) {
        for (int i = 0; i < 5; i++) {
            rows[i] = 1;
            int prev_i = i - 1;
            if (prev_i < 0) prev_i = 4;
            rows[prev_i] = 0;
            for (int j = 0; j < 5; j++) {
                cols[j] = 0;
                int prev_j = j - 1;
                if (prev_j < 0) prev_j = 4;
                cols[prev_j] = 1;

                ThisThread::sleep_for(250);
                //wait_us(250000);

                led = !led;
            }
        }
    }
}
