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

#define PRESSED      (0)
#define NOT_PRESSED  (1)

int main(void) {
    DigitalIn buttonA(BUTTONA, PullNone);
    DigitalIn buttonB(BUTTONB, PullNone);

    DigitalOut rows[5] = {
        DigitalOut(ROW_1, 0),
        DigitalOut(ROW_2, 0),
        DigitalOut(ROW_3, 0),
        DigitalOut(ROW_4, 0),
        DigitalOut(ROW_5, 0)
    };
    DigitalOut cols[5] = {
        DigitalOut(COL_1, 0),
        DigitalOut(COL_2, 0),
        DigitalOut(COL_3, 0),
        DigitalOut(COL_4, 0),
        DigitalOut(COL_5, 0)
    };

    while(1) {
        if (buttonA.read() == PRESSED) {
            rows[0] = 1;
            cols[0] = 0;
        } else {
            rows[0] = 0;
            cols[0] = 0;
        }
        if (buttonB.read() == PRESSED) {
            rows[1] = 1;
            cols[1] = 0;
        } else {
            rows[1] = 0;
            cols[1] = 0;
        }
    }
}
