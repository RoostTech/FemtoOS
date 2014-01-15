/*
 * Femto OS v 0.92 - Copyright (C) 2008-2010 Ruud Vlaming
 *
 * This file is part of the Femto OS distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Please note that, due to the GPLv3 license, for application of this
 * work and/or combined work in embedded systems special obligations apply.
 * If these are not to you liking, please know the Femto OS is dual
 * licensed. A commercial license and support are available.
 * See http://www.femtoos.org/ for details.
 */

/**
 * This file is solely for demonstration purposes.
 *
 * This example is made to demonstrate eight tasks can be run in around
 * 1K of flash and as little as 74 bytes of ram. These are totals, stacks
 * of all tasks and the OS included. Each task drives the flashing of
 * one led, so that the led's all blink independently at different
 * frequencies.
 */

/* This this the only include needed in your code .*/
#include "femtoos_code.h"


/* Below we define the times each task has to pause.
 *
 * If you make use of debugging in the AVR studio, is is handy that you do not
 * have to wait for ever for a new task to become active. I haven't used debugging
 * in ages anymore, but it still may be handy.*/
#if cfgSysDebug == cfgTrue
  #define delay07   9U
  #define delay06   9U
  #define delay05   8U
  #define delay04   7U
  #define delay03   6U
  #define delay02   5U
  #define delay01   4U
  #define delay00   3U
#else
  #define delay07 25000U
  #define delay06 13661U
  #define delay05  7465U
  #define delay04  4079U
  #define delay03  2229U
  #define delay02  1218U
  #define delay01   666U
  #define delay00   364U
#endif


/* This is called once at system boot, and before the creating of any of
 * the tasks. Use it to initialize the hardware. */
void appBoot(void)
{ devLedDRR  |= 0xFF; }


/* Here you don't need protection since the devLedPORT operations are sbi/cbi which are atomic operations,
 * but only if the method is calls with constants. */
#define setLed(lednr,state)  if (state) { devLedPORT |= (1 << lednr); } else { devLedPORT &=  ~(1 << lednr); }
/* Most easy way to toggle a led is of course via the pins, if supported */
#if (devSupPINWrite == cfgTrue)
  #define ledInv(lednr)       do  { devLedPIN |= (1 << lednr); } while(0)
#else
  #define ledInv(lednr)       do  { devLedPORT ^= (1 << lednr); } while(0)
#endif


/* Below all blinker tasks are defined. Note the preprocessor check for presence of the task.
 * The point is, you may want to exclude certain tasks from the system in the configuration
 * file, and this construction makes sure it is excluded from the executable as well. */

#if (preTaskDefined(LEDtask0))

void appLoop_LEDtask0(void)
{
  #if (demoUseShared == cfgTrue)
    ledInv(0);
    taskRestart(defRestartRunning,delay00);
  #else
    while (true)
    { setLed(0,true);
      taskDelayFromNow(delay00);
      setLed(0,false);
      taskDelayFromNow(delay00); }
  #endif
}

#endif


#if (preTaskDefined(LEDtask1))

void appLoop_LEDtask1(void)
{
  #if (demoUseShared == cfgTrue)
    ledInv(1);
    taskRestart(defRestartRunning,delay01);
  #else
    while (true)
    { setLed(1,true);
      taskDelayFromNow(delay01);
      setLed(1,false);
      taskDelayFromNow(delay01); }
  #endif
}

#endif


#if (preTaskDefined(LEDtask2))

void appLoop_LEDtask2(void)
{
  #if (demoUseShared == cfgTrue)
    ledInv(2);
    taskRestart(defRestartRunning,delay02);
  #else
    while (true)
    { setLed(2,true);
      taskDelayFromNow(delay02);
      setLed(2,false);
      taskDelayFromNow(delay02); }
  #endif
}

#endif


#if (preTaskDefined(LEDtask3))

void appLoop_LEDtask3(void)
{
  #if (demoUseShared == cfgTrue)
    ledInv(3);
    taskRestart(defRestartRunning,delay03);
  #else
    while (true)
    { setLed(3,true);
      taskDelayFromNow(delay03);
      setLed(3,false);
      taskDelayFromNow(delay03); }
  #endif
}

#endif


#if (preTaskDefined(LEDtask4))

void appLoop_LEDtask4(void)
{
  #if (demoUseShared == cfgTrue)
    ledInv(4);
    taskRestart(defRestartRunning,delay04);
  #else
    while (true)
    { setLed(4,true);
      taskDelayFromNow(delay04);
      setLed(4,false);
      taskDelayFromNow(delay04); }
  #endif

}

#endif


#if (preTaskDefined(LEDtask5))

void appLoop_LEDtask5(void)
{
  #if (demoUseShared == cfgTrue)
    ledInv(5);
    taskRestart(defRestartRunning,delay05);
  #else
    while (true)
    { setLed(5,true);
      taskDelayFromNow(delay05);
      setLed(5,false);
      taskDelayFromNow(delay05); }
  #endif

}

#endif


#if (preTaskDefined(LEDtask6))

void appLoop_LEDtask6(void)
{
  #if (demoUseShared == cfgTrue)
    ledInv(6);
    taskRestart(defRestartRunning,delay06);
  #else
    while (true)
    { setLed(6,true);
      taskDelayFromNow(delay06);
      setLed(6,false);
      taskDelayFromNow(delay06); }
  #endif

}

#endif


#if (preTaskDefined(LEDtask7))

void appLoop_LEDtask7(void)
{
  #if (demoUseShared == cfgTrue)
    ledInv(7);
    taskRestart(defRestartRunning,delay07);
  #else
    while (true)
    { setLed(7,true);
      taskDelayFromNow(delay07);
      setLed(7,false);
      taskDelayFromNow(delay07); }
  #endif

}

#endif


