/*
MIT License

Copyright (c) 2019 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef BOARD_HPP
#define BOARD_HPP

#define IOCON_XTAL_IN       IOCON_PIO8
#define IOCON_XTAL_OUT      IOCON_PIO9

#define CLOCK_MAIN_SOURCE   SYSCTL_MAINCLKSRC_PLLOUT

#define CLOCK_XTAL          (12000000u)
#define CLOCK_EXT_IN        (0u)
#define CLOCK_CPU           (30000000u)
#define CLOCK_AHB           (30000000u)
#define CLOCK_MAIN          (60000000u)

#define IOCON_LED_0         IOCON_PIO17
#define PIN_LED_0           (17u)
#define IOCON_LED_1         IOCON_PIO13
#define PIN_LED_1           (13u)
#define IOCON_LED_2         IOCON_PIO12
#define PIN_LED_2           (12u)
#define IOCON_LED_3         IOCON_PIO14
#define PIN_LED_3           (14u)
#define IOCON_BUTTON        IOCON_PIO4
#define PIN_BUTTON          (4u)
#define IOCON_TOGGLE        IOCON_PIO16
#define PIN_TOGGLE          (16u)

#define IOCON_SPI_MOSI      IOCON_PIO13
#define PIN_SPI_MOSI        (13)
#define IOCON_SPI_SCK       IOCON_PIO12
#define PIN_SPI_SCK         (12)

#define IOCON_WS2812_OUT    IOCON_PIO14
#define PIN_WS2812_OUT      (14)



void boardInit(void);

#endif