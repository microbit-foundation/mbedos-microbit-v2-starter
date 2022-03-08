/*
 * Copyright (c) 2016 Nordic Semiconductor ASA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice, this list
 *      of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form, except as embedded into a Nordic Semiconductor ASA
 *      integrated circuit in a product or a software update for such product, must reproduce
 *      the above copyright notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the distribution.
 *
 *   3. Neither the name of Nordic Semiconductor ASA nor the names of its contributors may be
 *      used to endorse or promote products derived from this software without specific prior
 *      written permission.
 *
 *   4. This software, with or without modification, must only be used with a
 *      Nordic Semiconductor ASA integrated circuit.
 *
 *   5. Any software provided in binary or object form under this license must not be reverse
 *      engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

#define PORT_SHIFT  3

typedef enum {
    p0  = 0,
    p1  = 1,
    p2  = 2,
    p3  = 3,
    p4  = 4,
    p5  = 5,
    p6  = 6,
    p7  = 7,
    p8  = 8,
    p9  = 9,
    p10 = 10,
    p11 = 11,
    p12 = 12,
    p13 = 13,
    p14 = 14,
    p15 = 15,
    p16 = 16,
    p17 = 17,
    p18 = 18,
    p19 = 19,
    p20 = 20,
    p21 = 21,
    p22 = 22,
    p23 = 23,
    p24 = 24,
    p25 = 25,
    p26 = 26,
    p27 = 27,
    p28 = 28,
    p29 = 29,
    p30 = 30,
    p31 = 31,
    p32 = 32,
    p33 = 33,
    p34 = 34,
    p35 = 35,
    p36 = 36,
    p37 = 37,
    p38 = 38,
    p39 = 39,
    p40 = 40,
    p41 = 41,
    p42 = 42,
    p43 = 43,
    p44 = 44,
    p45 = 45,
    p46 = 46,
    p47 = 47,

    P0_0  = p0,
    P0_1  = p1,
    P0_2  = p2,
    P0_3  = p3,
    P0_4  = p4,
    P0_5  = p5,
    P0_6  = p6,
    P0_7  = p7,

    P0_8  = p8,
    P0_9  = p9,
    P0_10 = p10,
    P0_11 = p11,
    P0_12 = p12,
    P0_13 = p13,
    P0_14 = p14,
    P0_15 = p15,

    P0_16 = p16,
    P0_17 = p17,
    P0_18 = p18,
    P0_19 = p19,
    P0_20 = p20,
    P0_21 = p21,
    P0_22 = p22,
    P0_23 = p23,

    P0_24 = p24,
    P0_25 = p25,
    P0_26 = p26,
    P0_27 = p27,
    P0_28 = p28,
    P0_29 = p29,
    P0_30 = p30,
    P0_31 = p31,

    P1_0 = p32,
    P1_1 = p33,
    P1_2 = p34,
    P1_3 = p35,
    P1_4 = p36,
    P1_5 = p37,
    P1_6 = p38,
    P1_7 = p39,

    P1_8 = p40,
    P1_9 = p41,
    P1_10 = p42,
    P1_11 = p43,
    P1_12 = p44,
    P1_13 = p45,
    P1_14 = p46,
    P1_15 = p47,

    // Not connected
    NC = (int)0xFFFFFFFF,

    // Buttons
#if defined(TARGET_NRF52_MICROBIT_V2_IF_833)
    BUTTON1 = P1_9,
    BUTTON_RESET = BUTTON1,
#elif defined(TARGET_NRF52_MICROBIT_V2_IF_820)
    BUTTON1 = P0_6,
    BUTTON_RESET = BUTTON1,
#else
    BUTTON1 = P0_14,
    BUTTON2 = P0_23,
    BUTTONA = BUTTON1,
    BUTTONB = BUTTON2,
#endif

    // Target MCU only pins
#if !defined(MICROBIT_IF)
    // LED matrix
    ROW_1 = P0_21,
    ROW_2 = P0_22,
    ROW_3 = P0_15,
    ROW_4 = P0_24,
    ROW_5 = P0_19,
    COL_1 = P0_28,
    COL_2 = P0_11,
    COL_3 = P0_31,
    COL_4 = P1_5,
    COL_5 = P0_30,

    // RING
    RING0 = P0_2,
    RING1 = P0_3,
    RING2 = P0_4,

    // Free edge connector GPIOs
    GPIO1 = P0_10,  // Edge connector pin 8
    GPIO2 = P0_9,   // Edge connector pin 9
    GPIO3 = P1_2,   // Edge connector pin 16
    GPIO4 = P0_12,  // Edge connector pin 12

    // Audio
    SPEAKER = P0_0,
    MIC = P0_5,
    RUN_MIC = P0_20,
#endif

    // Interface MCU only pins
#if defined(TARGET_NRF52_MICROBIT_V2_IF_833)
    LED1 = P0_15,
    LED2 = P0_17,
#elif defined(TARGET_NRF52_MICROBIT_V2_IF_820)
    LED1 = P0_14,
    LED2 = P0_15,
#endif

    // Other micro:bit specific pins common to Interface and Target
#if defined(TARGET_NRF52_MICROBIT_V2_IF_833)
    COMBINED_SENSOR_INT = P0_9,
#elif defined(TARGET_NRF52_MICROBIT_V2_IF_820)
    COMBINED_SENSOR_INT = P0_16,
#else
    COMBINED_SENSOR_INT = P0_25,
#endif

    // UART
#if defined(TARGET_NRF52_MICROBIT_V2_IF_833)
    // TODO: Add UART TX and RX pins
    RX_PIN_NUMBER  = NC,
    TX_PIN_NUMBER  = NC,
    // mBed interface Pins
    CONSOLE_TX = NC,
    CONSOLE_RX = NC,
    STDIO_UART_TX = NC,
    STDIO_UART_RX = NC,
#elif defined(TARGET_NRF52_MICROBIT_V2_IF_820)
    // TODO: Add UART TX and RX pins
    RX_PIN_NUMBER  = NC,
    TX_PIN_NUMBER  = NC,
    // mBed interface Pins
    CONSOLE_TX = NC,
    CONSOLE_RX = NC,
    STDIO_UART_TX = NC,
    STDIO_UART_RX = NC,
#else
    RX_PIN_NUMBER  = P1_8,
    TX_PIN_NUMBER  = P0_6,
    // mBed interface Pins
    CONSOLE_TX = TX_PIN_NUMBER,
    CONSOLE_RX = RX_PIN_NUMBER,
    STDIO_UART_TX = TX_PIN_NUMBER,
    STDIO_UART_RX = RX_PIN_NUMBER,
#endif

    CTS_PIN_NUMBER = NC,
    RTS_PIN_NUMBER = NC,
    // mBed interface Pins
    STDIO_UART_CTS = CTS_PIN_NUMBER,
    STDIO_UART_RTS = RTS_PIN_NUMBER,

#if defined(MICROBIT_IF)
    SPI_PSELMOSI0 = NC,
    SPI_PSELMISO0 = NC,
    SPI_PSELSS0   = NC,
    SPI_PSELSCK0  = NC,
#else
    SPI_PSELMOSI0 = P0_13,
    SPI_PSELMISO0 = P0_1,
    SPI_PSELSS0   = P1_2,
    SPI_PSELSCK0  = P0_17,
#endif

#if defined(TARGET_NRF52_MICROBIT_V2_IF_833)
    // Internal I2C
    I2C_SDA0 = P0_28,
    I2C_SCL0 = P0_29,
#elif defined(TARGET_NRF52_MICROBIT_V2_IF_820)
    // Internal I2C
    I2C_SDA0 = P0_30,
    I2C_SCL0 = P0_28,
#else
    // Internal I2C
    I2C_SDA0 = P0_16,
    I2C_SCL0 = P0_8,

    // External I2C at the edge connector
    I2C_SDA1 = P1_0,
    I2C_SCL1 = P0_26,
#endif

    /**** QSPI pins ****/
    QSPI1_IO0 = NC,
    QSPI1_IO1 = NC,
    QSPI1_IO2 = NC,
    QSPI1_IO3 = NC,
    QSPI1_SCK = NC,
    QSPI1_CSN = NC,

    /**** QSPI FLASH pins ****/
    QSPI_FLASH1_IO0 = NC,
    QSPI_FLASH1_IO1 = NC,
    QSPI_FLASH1_IO2 = NC,
    QSPI_FLASH1_IO3 = NC,
    QSPI_FLASH1_SCK = NC,
    QSPI_FLASH1_CSN = NC,
} PinName;

typedef enum {
    PullNone = 0,
    PullDown = 1,
    PullUp = 3,
    PullDefault = PullUp
} PinMode;

#ifdef __cplusplus
}
#endif

#endif
