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
 *  This file is solely for demonstration purposes.
 *
 *  This demo is use to demonstrate the power of mutexes and reentrant
 *  behaviour. Every led gets a state (on/off) from its right neighbour
 *  and tries to pass that on to the left. The last led (to the left)
 *  is coupled to the led on the right, so the form a circle. Every 30
 *  seconds a seed is given to the right most led to get the processes
 *  running.
 */


/* This this the only include needed in your code .*/
#include "femtoos_code.h"

#define taskMutexRelease(Slot)             taskSyncRelease(Slot)


/* This is called once at system boot, and before the creating of any of
 * the tasks. Use it to initialize the hardware. */
void appBoot(void)
{ devLedDRR    = 0xFF;
  devLedPORT   = 0xFF;
  devSwitchDRR = 0x00; }

/* Method to set the value of the led. Here you don't need access protection since the devLedPORT operations
 * are compiled to sbi/cbi instructions which atomic operations! Only if called with constants. */
#define setLed(lednr,state)  if (state) { devLedPORT |= (1 << lednr); } else { devLedPORT &=  ~(1 << lednr); }

#if (defSysOptimized == cfgTrue)
  /* Please note the use of "always_inline" attribute, if you remove this the register use explodes,
   * whereas with this trick the compiler can highly optimize your code (which of course gets longer). */
  static void HandOver(Tuint08 uiLed) __attribute__ ( ( naked, noreturn, always_inline ) );
#else
  static void HandOver(Tuint08 uiLed) __attribute__ ( ( naked, noreturn ) );
#endif


/* The idea of this demo is that the state of a led (one/zero) is passed to its left
 * neighbor. For that to be possible, both leds must be locked so the state of the
 * on led can be read, whereas the other can be written. And, of course, the acces to
 * the display must be guarded as well, so this requires an other mutex. All these
 * tasks run concurrently and the effect is a moving image from right to left.
 *
 * We demonstrate the use of two different kinds of locks, to be chosen in the
 * configuration files. In case of cfgSyncSingleBlock we need to nested locks
 * before we can access both led variables. But with the cfgSyncDoubleBlock
 * setting this is a little easier, because the lock is entered when both
 * resources are available. This is coordinated by the OS.  */

#if (cfgUseSynchronization == cfgSyncSingleBlock)

  #define taskMutexRequest(Slot,TicksToWait) taskSyncRequest(Slot,0,TicksToWait)

  static void HandOver(Tuint08 uiLed)
  { while (true)
    { Tuint08 uiSource = (uiLed & 0x07);
      Tuint08 uiTarget = ((uiLed+1) & 0x07);
      if (taskMutexRequest(uiSource+1,defLockDoNotBlock))
      { if (taskMutexRequest(uiTarget+1,defLockDoNotBlock))
        { taskMutexRequest(9,defLockBlockInfinite);
          Tuint08 uiBit = (devLedPORT >> uiSource) & 0x01;
          setLed(uiTarget,uiBit)
          taskMutexRelease(9);
          taskMutexRelease(uiTarget+1); }
        taskMutexRelease(uiSource+1); }
      taskDelayFromNow(300+(uiLed << 3)); } }

#elif (cfgUseSynchronization == cfgSyncDoubleBlock)

  #define taskMutexRequest(Slot,TicksToWait) taskSyncRequest(Slot,0,0,TicksToWait)

  static void HandOver(Tuint08 uiLed)
  { while (true)
    { Tuint08 uiSource = (uiLed & 0x07);
      Tuint08 uiTarget = ((uiLed+1) & 0x07);
      Tuint08 uiDoubleSlot = (((uiSource+1)<<4) | (uiTarget+1));
      if (taskMutexRequest(uiDoubleSlot,defLockDoNotBlock))
      { taskMutexRequest(9,defLockBlockInfinite);
        Tuint08 uiBit = (devLedPORT >> uiSource) & 0x01;
        setLed(uiTarget,uiBit)
        taskMutexRelease(9);
        taskMutexRelease(uiDoubleSlot); }
      taskDelayFromNow(300+(uiLed << 3)); } }

#else
  #error this is not possible
#endif

/* Reentrant calls to the HandOver lock managers. */

#if (preTaskDefined(LEDtask0))
  void appLoop_LEDtask0(void) { HandOver(0); }
#endif

#if (preTaskDefined(LEDtask1))
  void appLoop_LEDtask1(void) { HandOver(1); }
#endif

#if (preTaskDefined(LEDtask2))
  void appLoop_LEDtask2(void) { HandOver(2); }
#endif

#if (preTaskDefined(LEDtask3))
  void appLoop_LEDtask3(void) { HandOver(3); }
#endif

#if (preTaskDefined(LEDtask4))
  void appLoop_LEDtask4(void) { HandOver(4); }
#endif

#if (preTaskDefined(LEDtask5))
  void appLoop_LEDtask5(void) { HandOver(5); }
#endif

#if (preTaskDefined(LEDtask6))
  void appLoop_LEDtask6(void) { HandOver(6); }
#endif

#if (preTaskDefined(LEDtask7))
  void appLoop_LEDtask7(void) { HandOver(7); }
#endif


/* Possibility to set the display to a start value in order to
 * start the process. Although this task may run in a higher
 * priority, it still has to wait until control over the display
 * is issued. */

#if (preTaskDefined(Reset))

void appLoop_Reset(void)
{ Tuint08 button  = devSwitchPIN & 01;
  Tuint08 lastbutton  = button;
  while (true)
  { button = devSwitchPIN & 01;
    if (button != lastbutton)
    { taskMutexRequest(9,defLockBlockInfinite);
      devLedPORT = 0xFE;
      taskMutexRelease(9);
      }
    taskDelayFromNow(100); } }

#endif


/* This demo has the tendency to get silent after a while. This is because
 * the system knows two fixpoints (all leds on, all leds off). To keep the demo
 * going, every 30 sec a seed is given if needed. */

#if (preTaskDefined(AutoStart))

void appLoop_AutoStart(void)
{ while(true)
  { taskMutexRequest(9,defLockBlockInfinite);
    Tuint08 uiLeds = devLedPORT;
    if ((uiLeds == 0x00) || (uiLeds == 0xFF)) { devLedPORT ^= 0x01; }
    taskMutexRelease(9);
    taskDelayFromNow(30000); } }

#endif
