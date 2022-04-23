/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief Teardown function that resets the LPC812 to a state
 * that more or less matches reset state
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <LPC812M101DH20_teardown.hpp>
#include <test_conditions.hpp>
#include <MinUnit.h>

#define IOCON_NORMAL_DEFAULT 0x00000090 /**< Default value for most pins */
#define IOCON_I2CPIN_MASK (~0x00000400) /**< some I2C pins have no default value, so mask them */
#define IOCON_I2CPIN_DEFAULT 0x00000080 /**< I2C pins have some bits extra and lose some bits */
#define IOCON_XTAL_DEFAULT 0x00000080   /**< Crystal oscillator deviate from reset values */

/** @brief resets all the registers to their default states
 */
MINUNIT_TEARDOWN(LPC812M101DH20Teardown) {
  sysconEnableClocks(SYSCON, CLKCTRL_UART0 | CLKCTRL_I2C0);
  sysconDisableResets(SYSCON, RESETCTRL_UART0 | RESETCTRL_I2C0);
  sysconEnableResets(SYSCON, RESETCTRL_UART0 | RESETCTRL_I2C0);
  sysconDisableClocks(SYSCON, CLKCTRL_UART0 | CLKCTRL_I2C0);

  sysconEnableClocks(SYSCON, CLKCTRL_IOCON);
  IOCON->PIO[IOCON_PIO0_17] = IOCON_NORMAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_13] = IOCON_NORMAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_12] = IOCON_NORMAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_5] = IOCON_NORMAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_4] = IOCON_NORMAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_3] = IOCON_NORMAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_2] = IOCON_NORMAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_11] = IOCON_I2CPIN_DEFAULT;
  IOCON->PIO[IOCON_PIO0_10] = IOCON_I2CPIN_DEFAULT;
  IOCON->PIO[IOCON_PIO0_16] = IOCON_NORMAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_15] = IOCON_NORMAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_1] = IOCON_NORMAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_9] = IOCON_XTAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_8] = IOCON_XTAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_7] = IOCON_NORMAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_6] = IOCON_NORMAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_0] = IOCON_NORMAL_DEFAULT;
  IOCON->PIO[IOCON_PIO0_14] = IOCON_NORMAL_DEFAULT;
  sysconDisableClocks(SYSCON, CLKCTRL_IOCON);

  sysconEnableClocks(SYSCON, CLKCTRL_GPIO);
  GPIO->DIR[0] = 0x00000000;
  GPIO->MASK[0] = 0x00000000;
  GPIO->PIN[0] = 0x00000000;
  GPIO->SET[0] = 0x00000000;
  sysconDisableClocks(SYSCON, CLKCTRL_GPIO);

  sysconEnableClocks(SYSCON, CLKCTRL_SWM);
  SWM->PINASSIGN[0] = 0xFFFFFFFF;
  SWM->PINASSIGN[1] = 0xFFFFFFFF;
  SWM->PINASSIGN[2] = 0xFFFFFFFF;
  SWM->PINASSIGN[3] = 0xFFFFFFFF;
  SWM->PINASSIGN[4] = 0xFFFFFFFF;
  SWM->PINASSIGN[5] = 0xFFFFFFFF;
  SWM->PINASSIGN[6] = 0xFFFFFFFF;
  SWM->PINASSIGN[7] = 0xFFFFFFFF;
  SWM->PINASSIGN[8] = 0xFFFFFFFF;
  SWM->PINENABLE0 = 0x1B3;
  sysconDisableClocks(SYSCON, CLKCTRL_SWM);
  minUnitCheck(LPC812M101DH20TeardownCorrect() == true);
}

/** @brief checks if all the registers to their default states
 *  @return if all registers are correctly torndown
 */
bool LPC812M101DH20TeardownCorrect(void) {
  // check i2c reset states
  sysconEnableClocks(SYSCON, CLKCTRL_I2C0);
  TESTANDRETURN(I2C0->CFG == 0x0);
  TESTANDRETURN(I2C0->STAT == 0x801);
  TESTANDRETURN(I2C0->MSTTIME == 0x77);
  sysconDisableClocks(SYSCON, CLKCTRL_I2C0);
  // check IOCON reset state
  sysconEnableClocks(SYSCON, CLKCTRL_IOCON);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_17] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_13] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_12] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_5] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_4] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_3] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_2] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN((IOCON->PIO[IOCON_PIO0_11] & IOCON_I2CPIN_MASK) == IOCON_I2CPIN_DEFAULT);
  TESTANDRETURN((IOCON->PIO[IOCON_PIO0_10] & IOCON_I2CPIN_MASK) == IOCON_I2CPIN_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_16] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_15] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_1] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_9] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_8] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_7] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_6] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_0] == IOCON_NORMAL_DEFAULT);
  TESTANDRETURN(IOCON->PIO[IOCON_PIO0_14] == IOCON_NORMAL_DEFAULT);
  sysconDisableClocks(SYSCON, CLKCTRL_IOCON);
  // check SWM reset state
  sysconEnableClocks(SYSCON, CLKCTRL_SWM);
  TESTANDRETURN(SWM->PINASSIGN[0] == 0xFFFFFFFF);
  TESTANDRETURN(SWM->PINASSIGN[1] == 0xFFFFFFFF);
  TESTANDRETURN(SWM->PINASSIGN[2] == 0xFFFFFFFF);
  TESTANDRETURN(SWM->PINASSIGN[3] == 0xFFFFFFFF);
  TESTANDRETURN(SWM->PINASSIGN[4] == 0xFFFFFFFF);
  TESTANDRETURN(SWM->PINASSIGN[5] == 0xFFFFFFFF);
  TESTANDRETURN(SWM->PINASSIGN[6] == 0xFFFFFFFF);
  TESTANDRETURN(SWM->PINASSIGN[7] == 0xFFFFFFFF);
  TESTANDRETURN(SWM->PINASSIGN[8] == 0xFFFFFFFF);
  TESTANDRETURN(SWM->PINENABLE0 == 0x1B3);
  sysconDisableClocks(SYSCON, CLKCTRL_SWM);
  // verify GPIO reset state
  sysconEnableClocks(SYSCON, CLKCTRL_GPIO);
  TESTANDRETURN(GPIO->DIR[0] == 0x00000000);
  TESTANDRETURN(GPIO->MASK[0] == 0x00000000);
  TESTANDRETURN(GPIO->SET[0] == 0x00000000);
  sysconDisableClocks(SYSCON, CLKCTRL_GPIO);
  // verify UART0 reset state
  sysconEnableClocks(SYSCON, CLKCTRL_UART0);
  TESTANDRETURN(USART0->CFG == 0x00000000);
  TESTANDRETURN(USART0->CTL == 0x00000000);
  TESTANDRETURN((USART0->STAT & 0x0001FD6F) == 0x0000000E);
  TESTANDRETURN(USART0->INTENSET == 0x00000000);
  // this differs from the datasheet
  TESTANDRETURN((USART0->INTSTAT & 0x0001F96D) == 0x00000000);
  TESTANDRETURN(USART0->OSR == 0x0000000F);
  TESTANDRETURN(USART0->ADDR == 0x00000000);
  sysconDisableClocks(SYSCON, CLKCTRL_UART0);
  return true;
}