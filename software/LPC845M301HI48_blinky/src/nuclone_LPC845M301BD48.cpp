/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <nuclone_LPC845M301BD48.hpp>

void boardInit(void)
{
    sysconlEnableClocks(SYSCON, CLKCTRL0_IOCON | CLKCTRL0_GPIO0 | CLKCTRL0_SWM, CLKCTRL1_NONE);
    ioconSetupPin(IOCON, IOCON_LED, IOCON_MODE(IOCON_MODE_INACTIVE));
    // disable all unneedded clocks
    sysconlDisableClocks(SYSCON, CLKCTRL0_SWM, CLKCTRL1_NONE);
    // setup systick
    SysTick_Config(CLOCK_AHB / TICKS_PER_S);
}
