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
 * The Femto OS contains a facility that checks on the status of all tasks,
 * which is called the watchdog. This is not to be confused with the watchdog
 * of the device, to which it has no relation, it is a pure OS feature. If
 * a task is not running anymore the watchdog calls your special code inside
 * a 'bark' routine after which the task is restarted. This is particularly
 * useful for code that may get stuck on a lot of places, and you don't want
 * to implement timeouts everywhere. Here we have eight led blinkers running in
 * different priorities. The rightmost led gets stuck after a while (endless loop).
 * As soon as the watchdog kicks in the priority of the task is lowered by one,
 * and the task is restarted. This continues until the priority is zero and the
 * task is suspended. By using the switch the task can be restarted in the old
 * priority. Furthermore the two slowest leds, who have identical blinking frequencies,
 * get out of sync because they run in different priorities. They may be
 * re-synced by pushing a button.
 */


/* This this the only include needed in your code .*/
#include "femtoos_code.h"

/* Define the delays for the different blinker tasks. These regular values makes it
 * extra clear when tasks are getting hindered. */
#define delay07  1600U
#define delay06   800U
#define delay05   400U
#define delay04   200U
#define delay03  1600U
#define delay02   800U
#define delay01   400U
#define delay00   200U

static Tbool bSync = false;

/* This is called once at system boot, and before the creating of any of
 * the tasks. Use it to initialize the hardware. */
void appBoot(void)
{ devLedDRR  |= 0xFF;
  devSwitchDRR  &= 0xFC;
  devLedPORT |= 0xFF; }

/* Method to set the value of the led. Here you don't need access protection since the devLedPORT operations
 * are compiled to sbi/cbi instructions which atomic operations! Only if called with constants. */
#define setLed(lednr,state)  if (state) { devLedPORT |= (1 << lednr); } else { devLedPORT &=  ~(1 << lednr); }


/* This is the offending task. After it has been blinking for a while (32 x 200 ms)
 * it hits the infinite loop. The watchdog is not fed anymore. */

#if (preTaskDefined(LEDtask0))

void appLoop_LEDtask0(void)
{ Tuint08 led  = 0;
  Tuint08 count = 32;
  while (count--)
  { taskFeedWatchdog();
    led = 1 - led;
    setLed(0,led);
    taskDelayFromNow(delay00); }
   while (1); }


/* After a while, when the watchdog is not being fed, it starts barking, by calling
 * the routine below. Note, within this routine, you are in OS space, so do not
 * call ant taskXXX() methodes. It is save however to call genXXXX() methodes.
 * We do so here to lower the priority, or, when that is already at its minimum,
 * to suspend the task.
 *
 * Note that if an appInit_LEDtask0 would be present (but it is not in this case)
 * it will not be called by the OS at barking. If needed, you can do so yourself
 * from this place.
 */

void appBark_LEDtask0(void)
{ devLedPORT |= 0x01;
  Tuint08 lastPrio = genGetPriorityOnName(LEDtask0);
  if(lastPrio>0)
  { --lastPrio;
    genSetPriorityOnName(LEDtask0,lastPrio); }
  else
  { genSuspendOnName(LEDtask0); } }

#endif


/* Regular blinking leds do not have watchdog protection in this demo. */

#if (preTaskDefined(LEDtask1))

void appLoop_LEDtask1(void)
{ Tuint08 led  = false;
  while (true)
  { led = !led;
    setLed(1,led);
    taskDelayFromNow(delay01);
    led = !led;
    setLed(1,led);
    taskDelayFromNow(delay01); } }

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
    taskDelayFromNow(delay02);  } }

#endif


/* LEDtask3 can be synchronized with LEDtask7 by pushing a button. You see that
 * as soon as the bSync variable gets true, this task starts waiting for an
 * other task on a specific point. We did not synchronize the access on bSync
 * since the concurrent modification does not lead to errors in this case. */

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
    { taskWaitForOtherTaskOnName(TrefPunt);
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
    taskDelayFromNow(delay04); } }

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
    taskDelayFromNow(delay05); } }

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
    taskDelayFromNow(delay06);  } }

#endif


/* LEDtask7 can be synchronized with LEDtask3 by pushing a button. You see that
 * as soon as the bSync variable gets true, this task starts waiting for an
 * other task on a specific point. We did not synchronize the access on bSync
 * since the concurrent modification does not lead to errors in this case. */

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
    { taskWaitForOtherTaskOnName(TrefPunt);
      bSync = false; }
    } }

#endif


/* This is the task which waits for the synchronizer button to be pushed. If
 * so, the bSync will be set and  LEDtask7, LEDtask3 will be waiting for each
 * other. */

#if (preTaskDefined(Synchronize))

void appLoop_Synchronize(void)
{ Tuint08 button  = devSwitchPIN & 01;
  Tuint08 lastbutton  = button;
  while (true)
  { button = devSwitchPIN & 01;
    if (button != lastbutton) { bSync = true;  }
    taskDelayFromNow(100); } }

#endif


/* By pushing the other button, we can revive the task, LEDtask0, that was
 * suspended by the watchdog. The priority is restored and the task is
 * resumed. Because the infinite loop is still present, the watchdog bark
 * cycle will repeat itself. */

#if (preTaskDefined(Release))

void appLoop_Release(void)
{ Tuint08 button  = devSwitchPIN & 02;
  Tuint08 lastbutton  = button;
  while (true)
  { button = devSwitchPIN & 02;
    if (button != lastbutton)
    { genSetPriorityOnName(LEDtask0,3);
      genResumeOnName(LEDtask0); }
    taskDelayFromNow(100); } }

#endif

