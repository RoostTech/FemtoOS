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
 * In this example eight leds are blinking at slightly different frequencies.
 * The effect is that they will get out off phase after about a minute or so.
 * All blinkers are independent preempted tasks. There is one switch which
 * activates a semaphore so that all tasks block at a particular point until
 * all of them have arrived there. If this happens the semaphore is released
 * (by arrival of the last task) and the game starts all over again.
 */


/* This this the only include needed in your code .*/
#include "femtoos_code.h"

#define delay07   349U
#define delay06   342U
#define delay05   335U
#define delay04   328U
#define delay03   321U
#define delay02   314U
#define delay01   307U
#define delay00   300U

static Tbool bSync = false;

/* This is called once at system boot, and before the creating of any of
 * the tasks. Use it to initialize the hardware. */
void appBoot(void)
{ devLedDRR    = 0xFF;
  devLedPORT   = 0xFF;
  devSwitchDRR = 0x00; }

/* Method to set the value of the led. Here you don't need access protection since the devLedPORT operations
 * are compiled to sbi/cbi instructions which atomic operations! Only if called with constants. */
#define setLed(lednr,state)  if (state) { devLedPORT |= (1 << lednr); } else { devLedPORT &=  ~(1 << lednr); }


/* All indentical tasks just blinking and when the bSync variable is activated, they wait
 * for each other. Note you must explicitly tell the wait method the number of tasks
 * that must be waited for. */

#if (preTaskDefined(LEDtask0))

void appLoop_LEDtask0(void)
{ Tuint08 led  = false;
  while (true)
  { led = !led;
    setLed(0,led);
    taskDelayFromNow(delay00);
    led = !led;
    setLed(0,led);
    taskDelayFromNow(delay00);
    if (bSync)
    { taskWaitForTasksOnName(TrefPunt,defNumberOfTasks-1);
      bSync = false; } } }


#endif

#if (preTaskDefined(LEDtask1))

void appLoop_LEDtask1(void)
{ Tuint08 led  = false;
  while (true)
  { led = !led;
    setLed(1,led);
    taskDelayFromNow(delay01);
    led = !led;
    setLed(1,led);
    taskDelayFromNow(delay01);
    if (bSync)
    { taskWaitForTasksOnName(TrefPunt,defNumberOfTasks-1);
      bSync = false; } } }

#endif

#if (preTaskDefined(LEDtask2))

void appLoop_LEDtask2(void)
{ Tuint08 led  = false;
  while (true)
  { led = !led;
    setLed(2,led);
    taskDelayFromNow(delay02);
    led = !led;
    setLed(2,led);
    taskDelayFromNow(delay02);
    if (bSync)
    { taskWaitForTasksOnName(TrefPunt,defNumberOfTasks-1);
      bSync = false; } } }

#endif

#if (preTaskDefined(LEDtask3))

void appLoop_LEDtask3(void)
{ Tuint08 led  = false;
  while (true)
  { led = !led;
    setLed(3,led);
    taskDelayFromNow(delay03);
    led = !led;
    setLed(3,led);
    taskDelayFromNow(delay03);
    if (bSync)
    { taskWaitForTasksOnName(TrefPunt,defNumberOfTasks-1);
      bSync = false; } } }

#endif

#if (preTaskDefined(LEDtask4))

void appLoop_LEDtask4(void)
{ Tuint08 led  = false;
  while (true)
  { led = !led;
    setLed(4,led);
    taskDelayFromNow(delay04);
    led = !led;
    setLed(4,led);
    taskDelayFromNow(delay04);
    if (bSync)
    { taskWaitForTasksOnName(TrefPunt,defNumberOfTasks-1);
      bSync = false; } } }

#endif

#if (preTaskDefined(LEDtask5))

void appLoop_LEDtask5(void)
{ Tuint08 led  = false;
  while (true)
  { led = !led;
    setLed(5,led);
    taskDelayFromNow(delay05);
    led = !led;
    setLed(5,led);
    taskDelayFromNow(delay05);
    if (bSync)
    { taskWaitForTasksOnName(TrefPunt,defNumberOfTasks-1);
      bSync = false; } } }

#endif

#if (preTaskDefined(LEDtask6))

void appLoop_LEDtask6(void)
{ Tuint08 led  = false;
  while (true)
  { led = !led;
    setLed(6,led);
    taskDelayFromNow(delay06);
    led = !led;
    setLed(6,led);
    taskDelayFromNow(delay06);
    if (bSync)
    { taskWaitForTasksOnName(TrefPunt,defNumberOfTasks-1);
      bSync = false; } } }

#endif

#if (preTaskDefined(LEDtask7))

void appLoop_LEDtask7(void)
{ Tuint08 led  = false;
  while (true)
  { led = !led;
    setLed(7,led);
    taskDelayFromNow(delay07);
    led = !led;
    setLed(7,led);
    taskDelayFromNow(delay07);
    if (bSync)
    { taskWaitForTasksOnName(TrefPunt,defNumberOfTasks-1);
      bSync = false; } } }

#endif


/* This is the task which waits for the synchronizer button to be pushed. If
 * so, the bSync will be set and all tasks will start waiting. */

#if (preTaskDefined(Synchronize))

void appLoop_Synchronize(void)
{ Tuint08 button  = devSwitchPIN & 01;
  Tuint08 lastbutton  = button;
  while (true)
  { button = devSwitchPIN & 01;
    if (button != lastbutton) { bSync = true; }
    taskDelayFromNow(100); } }

#endif

