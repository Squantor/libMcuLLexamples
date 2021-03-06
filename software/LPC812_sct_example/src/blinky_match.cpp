/*
MIT License

Copyright (c) 2020 Bart Bilos

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
/*
    blink pin at 1 Hz
*/
#include <board.hpp>
#include <mcu_ll.h>
#include <sct_cookbook.hpp>

void exampleSetup(void)
{
    // setup SCT out0 to pin 17
    ClockEnablePeriphClock(SYSCTL_CLOCK_SWM);
    ClockEnablePeriphClock(SYSCTL_CLOCK_IOCON);
    IoconPinSetMode(IOCON, IOCON_LED_0, PIN_MODE_INACTIVE);
    SwmMovablePinAssign(SWM_CTOUT_0_O, PIN_LED_0);
    ClockDisablePeriphClock(SYSCTL_CLOCK_IOCON);
    ClockDisablePeriphClock(SYSCTL_CLOCK_SWM);

    SctInit(LPC_SCT);    
    SctConfig(LPC_SCT, SCT_CONFIG_32BIT_COUNTER);
    SctMatchReloadU(LPC_SCT, SCT_MATCH_0, ClockGetSystemClockRate());
    // Set SCT to pingpong between state 0 and 1 and clear and set the output
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_0_VAL, SCT_STATE_0_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_0_VAL, 
        SCT_EV_CTRL_MATCHSEL(SCT_MATCH_0) | 
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH) |
        SCT_EV_CTRL_STATELD_LOAD | 
        SCT_EV_CTRL_STATEV(SCT_STATE_1_VAL));
    SctSetEventStateMask(LPC_SCT, SCT_EVENT_1_VAL, SCT_STATE_1_BIT);
    SctSetEventControl(LPC_SCT, SCT_EVENT_1_VAL, 
        SCT_EV_CTRL_MATCHSEL(SCT_MATCH_0) | 
        SCT_EV_CTRL_COMBMODE(SCT_COMBMODE_MATCH) |
        SCT_EV_CTRL_STATELD_LOAD | 
        SCT_EV_CTRL_STATEV(SCT_STATE_0_VAL));
    // event 0 clears sets output 0, event 1 clears it
    SctOutputSet(LPC_SCT, SCT_OUTPUT_0_VALUE, SCT_EVENT_0_BIT);
    SctOutputClear(LPC_SCT, SCT_OUTPUT_0_VALUE, SCT_EVENT_1_BIT);
    // event 0 and 1 limit the counter
    SctLimitL(LPC_SCT, SCT_EVENT_0_BIT | SCT_EVENT_1_BIT);
    // start the timer
    SctClearControl(LPC_SCT, SCT_CTRL_HALT_L);
}

void exampleLoop(void)
{
    __NOP();
}