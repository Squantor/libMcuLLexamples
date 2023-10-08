# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20230101

# current makefile base dir relative to Makefile
PROJ_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# project settings
NAME := LPC812M101DH20_CPP_tests
BOARD := nuclone_LPC812M101DH20_tests
$(NAME)_TARGET := MCU
$(NAME)_MCU := LPC812M101DH20
$(NAME)_DEFINES += -DMINUNIT_MAX_TESTS=100 -DMINUNIT_REPORT_DISABLE # saves load of flash space
$(NAME)_LIBS := libMcuLL squantorLibC squantorLibEmbedded squantorMinUnit
$(NAME)_FILES := $(PROJ_DIR)/src/main.cpp \
$(PROJ_DIR)/src/$(BOARD).cpp \
$(PROJ_DIR)/src/LPC812M101_teardown.cpp \
$(PROJ_DIR)/src/test_LPC812M101_spi.cpp \
$(PROJ_DIR)/src/test_LPC812M101_syscon.cpp \
$(PROJ_DIR)/src/test_LPC812M101_gpio.cpp \
$(PROJ_DIR)/src/test_LPC812M101_uart.cpp \
$(PROJ_DIR)/src/test_LPC812M101_iocon.cpp \
$(PROJ_DIR)/src/test_LPC812M101_i2c.cpp

$(NAME)_INCLUDES := -I$(PROJ_DIR)/inc -Icommon/inc

# --- nothing user definable below ---
PROJECTS += $(NAME)
$(NAME)_PROJECT_ROOT := $(PROJ_DIR)
$(NAME)_BOARD := $(BOARD)
