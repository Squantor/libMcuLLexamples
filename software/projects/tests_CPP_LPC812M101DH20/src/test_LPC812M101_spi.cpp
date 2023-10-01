/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file tests for the LPC812M101 SPI peripheral polling mode
 */
#include <nuclone_LPC812M101DH20_tests.hpp>
#include <MinUnit.h>
#include <LPC812M101_teardown.hpp>
#include <common.hpp>
#include <array>

static constexpr libMcuLL::hwAddressType spi0Address = libMcuLL::hw::SPI0_cpp;
libMcuLL::hw::spi::peripheral *const dutRegisters{reinterpret_cast<libMcuLL::hw::spi::peripheral *>(spi0Address)};

/**
 * @brief Spi setup and initialisation
 */
MINUNIT_SETUP(LPC812M101CppSetupSpi) {
  minUnitCheck(LPC812M101TeardownCorrect() == true);
  sysconPeripheral.enablePeripheralClocks(libMcuLL::sw::syscon::CLOCK_SPI0 | libMcuLL::sw::syscon::CLOCK_SWM |
                                          libMcuLL::sw::syscon::CLOCK_IOCON);
  sysconPeripheral.resetPeripherals(libMcuLL::sw::syscon::RESET_SPI0);
}

MINUNIT_ADD(LPC812M101CppSpiInits, LPC812M101CppSetupSpi, LPC812M101Teardown) {
  uint32_t actualClock;
  actualClock = spiPeripheral.initMaster(100000);
  minUnitCheck(actualClock == 100000);
  minUnitCheck((dutRegisters->CFG & libMcuLL::sw::spi::CFG::MASK) == 0x00000005);
  minUnitCheck(dutRegisters->DIV == 299);
  dutRegisters->CFG = 0x00000000;
  actualClock = spiPeripheral.initMaster(65399, libMcuLL::sw::spi::CPHA1_CPOL1_LSB, libMcuLL::sw::spi::SPOL_HIGH);
  minUnitCheck(actualClock == 65502);
  minUnitCheck((dutRegisters->CFG & libMcuLL::sw::spi::CFG::MASK) == 0x0000013D);
  minUnitCheck(dutRegisters->DIV == 457);
}

MINUNIT_ADD(LPC812M101CppSpiRxTx, LPC812M101CppSetupSpi, LPC812M101Teardown) {
  swmPeriperhal.setup(test2Pin, spiMainSckFunction);
  swmPeriperhal.setup(test1Pin, spiMainMosiFunction);
  swmPeriperhal.setup(test0Pin, spiMainMisoFunction);
  spiPeripheral.initMaster(1000000);
  minUnitCheck((dutRegisters->STAT & libMcuLL::sw::spi::STAT::MASK) == 0x00000102);
  minUnitCheck(dutRegisters->DIV == 29);

  std::array<uint16_t, 5> testDataSend{0x1234, 0x4567, 0x89AB, 0xCDEF, 0x5A5A};
  std::array<uint16_t, 5> testDataReceive;
  testDataReceive.fill(0x0000u);
  // test "simple"(below 17 bits) transaction
  spiPeripheral.readWrite(libMcuLL::sw::spi::chipEnables::SSEL_NONE, testDataSend, testDataReceive, 8, true);
  minUnitCheck((testDataSend[0] & 0xFF) == testDataReceive[0]);
  // test "multi"(above 17 bits) transaction to test multi transfers
  testDataReceive.fill(0x0000u);
  spiPeripheral.readWrite(libMcuLL::sw::spi::chipEnables::SSEL_NONE, testDataSend, testDataReceive, 24, true);
  minUnitCheck(testDataSend[0] == testDataReceive[0]);
  minUnitCheck((testDataSend[1] & 0xFF) == testDataReceive[1]);
  // test receive
  // disable MOSI
  swmPeriperhal.clear(test1Pin, spiMainMosiFunction);
  gpioPeripheral.output(test1Pin);
  gpioPeripheral.high(test1Pin);
  // enable pullup, read all ones
  spiPeripheral.read(libMcuLL::sw::spi::chipEnables::SSEL_NONE, testDataReceive, 12, true);
  minUnitCheck(0xFFFu == testDataReceive[0]);
  // enable pulldown, read all zeroes
  gpioPeripheral.low(test1Pin);
  testDataReceive[0] = 0xFFFF;
  spiPeripheral.read(libMcuLL::sw::spi::chipEnables::SSEL_NONE, testDataReceive, 12, true);
  minUnitCheck(0x0u == testDataReceive[0]);
}