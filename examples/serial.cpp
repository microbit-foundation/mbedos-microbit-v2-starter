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

UnbufferedSerial pc_serial(USBTX, USBRX, 115200);

// Wire up printf to serial
FileHandle *mbed::mbed_override_console(int fd) {
    return &pc_serial;
}

void rx_irq_echo() {
    char single_byte;
    if (pc_serial.read(&single_byte, 1)) {
        pc_serial.write(&single_byte, 1);
    }
}

int main(void) {
    printf("printf test! (MbedOS %d.%d.%d)\n",
           MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    // Send a string directly (size calculation removes the null terminator)
    char hello[] = "hello world!\n";
    size_t hello_size = (sizeof(hello) / sizeof(hello[0])) - 1;
    pc_serial.write(hello, hello_size);

    // Configure RX IRQ to a function to echos back the data
    pc_serial.attach(&rx_irq_echo, SerialBase::RxIrq);
}
