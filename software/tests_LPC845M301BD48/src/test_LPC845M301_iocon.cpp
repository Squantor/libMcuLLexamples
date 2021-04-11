/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief tests for the LPC845M301 IOCON peripheral
 */
#include <nuclone_LPC845M301BD48_tests.hpp>
#include <MinUnit.h>
#include <LPC845M301_teardown.hpp>
#include <common.hpp>

/**
 * @brief Iocon setup and initialisation
 */
MINUNIT_SETUP(LPC845M301SetupIocon)
{
    minUnitCheck(LPC845M301TeardownCorrect() == true); // check if the MCU is in its reset state
    sysconEnableClocks(SYSCON, CLKCTRL0_GPIO0 | CLKCTRL0_GPIO1 | CLKCTRL0_IOCON, CLKCTRL1_NONE);
    sysconEnableResets(SYSCON, RESETCTRL0_GPIO0 | RESETCTRL0_GPIO1 | RESETCTRL0_IOCON, 0x00);
}

/**
 * @brief tests for the IOCON pullup and down function
 */
MINUNIT_ADD(LPC845M301IoconPull, LPC845M301SetupIocon, LPC845M301Teardown)
{
    gpioSetPortDir(GPIO, PORT_TESTPIN_0_0, 0);
    ioconSetupPin(IOCON, IOCON_TESTPIN_0_0, IOCON_MODE_INACTIVE);
    ioconSetupPin(IOCON, IOCON_TESTPIN_1_0, IOCON_MODE_INACTIVE);
    minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0) == true);
    minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_1_0, PIN_TESTPIN_1_0) == true);
    ioconSetupPin(IOCON, IOCON_TESTPIN_0_1, IOCON_MODE_PULLDOWN);
    ioconSetupPin(IOCON, IOCON_TESTPIN_1_1, IOCON_MODE_PULLDOWN);
    minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0) == false);
    minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_1_0, PIN_TESTPIN_1_0) == false);
    ioconSetupPin(IOCON, IOCON_TESTPIN_0_1, IOCON_MODE_PULLUP);
    ioconSetupPin(IOCON, IOCON_TESTPIN_1_1, IOCON_MODE_PULLUP);
    minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_0_0, PIN_TESTPIN_0_0) == true);
    minUnitCheck(gpioPinRead(GPIO, PORT_TESTPIN_1_0, PIN_TESTPIN_1_0) == true);
}

/**
 * @brief tests for the IOCON repeater function
 */
MINUNIT_ADD(LPC845M301IoconRepeater, LPC845M301SetupIocon, LPC845M301Teardown)
{
    minUnitPass();
}

/**
 * @brief tests for the IOCON repeater function
 */
MINUNIT_ADD(LPC845M301IoconOpenDrain, LPC845M301SetupIocon, LPC845M301Teardown)
{
    minUnitPass();
}

/* Some tests that are still to do:
* Test glitch filtering, depends on timer subsystem
* Analog pin tests, depends on ADC/Comparator
*/