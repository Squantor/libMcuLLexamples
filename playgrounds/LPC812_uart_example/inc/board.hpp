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

#include <mcu_ll.h>

#define IOCON_XTAL_IN   IOCON_PIO8
#define IOCON_XTAL_OUT  IOCON_PIO9

#define IOCON_UART_TX   IOCON_PIO13
#define PIN_UART_TX     (13u)
#define IOCON_UART_RX   IOCON_PIO17
#define PIN_UART_RX     (17u)

#define UART_DEBUG      LPC_USART0

#define XTAL_FREQ   (12000000u)
#define CPU_FREQ    (30000000u)
#define AHB_FREQ    (30000000u)
#define MAIN_FREQ   (60000000u)

void boardInit(void);

#endif