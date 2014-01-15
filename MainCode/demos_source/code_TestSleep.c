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
 *  Most atmel devices can be brought to a low power sleep. This application
 *  demonstrates that the Femto OS is capable of utilizing this feature,
 *  and at the same time keeps the tick counter into sync. The OS periodically
 *  checks if the smallest delay time off all running tasks is large enough to
 *  start sleeping. If so, the device is put to low power sleep. After wake up the
 *  tick counter is restored and operations are continued.
 */

/* This this the only include needed in your code .*/
#include "femtoos_code.h"


/* Delays of the blinkers, they are choosen in such a way that the leds blink shortly
 * and than pause for a longer time. The two leds blink with a slightly different frequency
 * so, as time goes by, the are getting more and more out of phase. In the beginning both
 * leds can be handled in the same wake period, later on the system must be woken for
 * both tasks seperately. */
#define delay05 31000U
#define delay04 30500U
#define delay03 30000U
#define delay02  1500U
#define delay01  1000U
#define delay00   250U
#define delayFLASH 50U

/* If only two leds burn continuously you have not connected the button
 * to the correct interrupt pin. See the pin-configuration for your device
 * and connect the switch to INT0 */

#if (defSysGCCstartup != cfgReplace) && (devINT != cfgUndefined)
  #define IntPortSetup()   do { devSwitchDRR = 0x00; devEIR = preBitSet1(0x00,devINT); } while(false)
  void devSigExternalInt(void) __attribute__ ( ( signal, naked, used, externally_visible ) );
  void devSigExternalInt(void) { asm("reti"); }
#else
/* Games with interrupts are not possible when we use cfgReplace, since there is no interrupt
 * vector table. So pushing the button will not cause a wake-up in the demo. Furthermore,
 * if the device has no watchdog interrupt, the system cannot wake up at all in this case.*/
  #define IntPortSetup()
#endif


/* This is called once at system boot, and before the creating of any of
 * the tasks. Use it to initialize the hardware. */
void appBoot(void)
{ devLedDRR    = 0xFF;
  devLedPORT   = 0xFF;
  IntPortSetup(); }


/* During sleep, the device wakes up very shortly every second (configurable), to see if
 * he must wake up already. This is the hook if you want to do something yourself in that
 * period. We very shortly blink a led, it is just visible in the dark. */
void appTickSleep(void)
{ devLedPORT &= ~0x40;
  portNop();
  portNop();
  portNop();
  devLedPORT |= 0x40; }


/* This is the hook to do something when you enter sleep. In this case we switch
 * off the leftmost led. */
void appEnterSleep(void) { devLedPORT |= 0x80; }


/* This is the hook to do something when you exit sleep. In this case we switch
 * on the leftmost led, so we can see when the device is awake. */
void appExitSleep(void)  { devLedPORT &= ~0x80; }


/* Method to set the value of the led. Here you don't need access protection since the devLedPORT operations
 * are compiled to sbi/cbi instructions which atomic operations! Only if called with constants. */
#define setLed(lednr,state)  if (state) { devLedPORT &=  ~(1 << lednr); } else { devLedPORT |= (1 << lednr); }


/* Method to flash a particular led once. */
void flashLED(Tuint08 ledNR)
{ setLed(ledNR,1);
  taskDelayFromNow(delayFLASH);
  setLed(ledNR,0); }


/* These are the flashers. If we have cfgUseLowPowerOnDelay activated the Femto OS decides
 * when the delay is long enough to put the device to sleep. It will wake up just before the
 * first task is due. If not (when no dedicated watchdog interrupt is present) we must
 * manually put the task to sleep. When all tasks sleep, the device is put into low power mode. */

#if (preTaskDefined(LEDtask0))

void appLoop_LEDtask0(void)
{ while (true)
  { flashLED(0);
    taskDelayFromNow(delay02);
    flashLED(0);
    #if (cfgUseLowPowerOnDelay == cfgTrue)
      taskDelayFromNow(delay05);
    #else
      taskSleep();
    #endif
  } }

#endif

#if (preTaskDefined(LEDtask1))

void appLoop_LEDtask1(void)
{ while (true)
  { flashLED(1);
    taskDelayFromNow(delay01);
    flashLED(1);
    #if (cfgUseLowPowerOnDelay == cfgTrue)
      taskDelayFromNow(delay04);
    #else
      taskSleep();
    #endif
  } }

#endif


/* This tasks just blinks every time the device gets woken. */

#if (preTaskDefined(LEDtask2))

void appLoop_LEDtask2(void)
{ while (true)
  { Tuint08 count = 8;
    while (count--)
    { flashLED(2);
      taskDelayFromNow(delay00); }
    taskSleep(); } }

#endif

