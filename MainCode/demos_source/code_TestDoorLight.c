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

/* This file is solely for demonstration purposes. */

#include "femtoos_code.h"

/**
 * This file is the program for controlling a lamp using one capacitive switch.
 * State of the system is displayed using one led. In steady state the led
 * is weakly lit, just enough to find the switch in the dark. Touching the
 * switch once, activates the lamp, for about 2 minutes. The led will start
 * blinking. The following scheme is displayed in repetition:
 *   5 sec on:           Switching now increased the on-timer
 *   1,2,3 or 4 blinks:  Showing the internal mode: (2min, 15min, 60min, 4hour on).
 *   5 sec on:           Switching now  turns lamp of.
 * See also the schematics attached.
 */


/* Connections
 * PA0 out : led beacon (making it easy to find the switch in the dark)
 * PA1 out : led signal (giving information about the internal state)
 * PA2 out : 230V light (via solid state relay)
 * PA3 out : unused
 * PA4 in  : capacitive switch
 * PA5 in  : unused
 * PA6 in  : unused
 * PA7 in  : unused
 */

#define pinLEDbeacon PA0
#define pinLEDsignal PA1
#define pinLAMP      PA2
#define pinSWITCH    PB0

void appBoot(void)
{ DDRA  |= 0x07;
  PORTA &= 0xF7;
  DDRB  &= 0xFE;
  PORTB &= 0xFE; }

/* here you don't need protection since the PORTA operations are sbi/cbi which are atomair operations */
#define setChannel(channel,state)  if (!state) { PORTA |= (1 << (channel)); } else { PORTA &=  ~(1 << (channel)); }

/* uiDelayMode
 * 0: LAMP off
 * 1: LAMP 2 min on
 * 2: LAMP 15 min on
 * 3: LAMP 60 min on
 * 4: LAMP 4.5 hours on (max delay)
 *
 * uiLedMode
 * 0: Led is off, switching at this moment switches off lamp
 * 1: Led is on beacon, switching at this moment increases DelayMode (Lamp is switched on)
 * 2: led if on, switching at this moment increases DelayMode
 * 3: led is in flash state, switching is ignored.
 */

volatile Tuint08 uiLedMode;
volatile Tuint08 uiDelayMode;
volatile Tuint08 uiDelayTimer;


void appTick16(void)
{ if (uiDelayTimer == 0) { uiDelayMode = 0; } else { uiDelayTimer--; }  }


#if (preTaskDefined(ReadSwitch))

void appLoop_ReadSwitch(void)
{ Tuint08 uiSwitchOldState = PINB & (1<<pinSWITCH);;
  Tuint08 uiSwitchNewState;
  while (true)
  { uiSwitchNewState = PINB & (1<<pinSWITCH);
    if (uiSwitchOldState !=  uiSwitchNewState)
    { uiSwitchOldState =  uiSwitchNewState;
      Tuint08 uiLM = uiLedMode;
      if (uiLM==0)
      { uiDelayMode = 0;
        uiDelayTimer = 0; }
      else if (uiLM < 3)
      { if (uiDelayMode++ > 4) uiDelayMode=4;
        switch (uiDelayMode)
        { case 1 : { uiDelayTimer = 2;   } break;
          case 2 : { uiDelayTimer = 15;  } break;
          case 3 : { uiDelayTimer = 60;  } break;
          default: { uiDelayTimer = 255; } break; } } }
    taskDelayFromNow(200); } }

#endif


#if (preTaskDefined(DriveLed))

static void LedOff()
{ if (uiDelayMode > 0)
  { uiLedMode=0;
    setChannel(pinLEDbeacon,false);
    setChannel(pinLEDsignal,false);
    taskDelayFromNow(5000); } }

static void LedFlash()
{ if (uiDelayMode > 0)
  { Tuint08 uiDM = uiDelayMode;
    uiLedMode=3;
    setChannel(pinLEDbeacon,false);
    while (uiDM-- > 0)
    { setChannel(pinLEDsignal,true);
      taskDelayFromNow(200);
      setChannel(pinLEDsignal,false);
      taskDelayFromNow(200); } } }

static void LedOn()
{ if (uiDelayMode > 0)
  { uiLedMode=2;
    setChannel(pinLEDbeacon,false);
    setChannel(pinLEDsignal,true);
    taskDelayFromNow(5000); } }

static void LedBeacon()
{ if (uiDelayMode == 0)
  { uiLedMode=1;
    setChannel(pinLEDbeacon,true);
    setChannel(pinLEDsignal,false);
    taskDelayFromNow(200); } }

void appLoop_DriveLed(void)
{ while (true)
  { LedFlash();
    LedBeacon();
    LedOn();
    LedOff(); } }

#endif


#if (preTaskDefined(DriveLamp))

void appLoop_DriveLamp(void)
{ while (true)
  { setChannel(pinLAMP,uiDelayMode>0)
    taskDelayFromNow(150); } }

#endif

