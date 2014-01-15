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
 * This example is made to demonstrate how small the Femto OS can be.
 * It just runs two tasks. One task reads the status of the switches
 * and copies the result to a variable. The other reads the variable
 * and displays it on the leds. It takes around 600 bytes of flash
 * and 29 bytes of ram.
 */


/* This this the only include needed in your code .*/
#include "femtoos_code.h"

/* use one (volatile!) byte to communicate from one task
 * to the other. Exercise: what happens when the keyword
 * volatile is left out?*/
volatile Tuint08 state;

/* Infinite task displaying the state */
void appLoop_LEDtask(void)
{ devLedDRR = 0xFF;
  while (true)
  { devLedPORT = state; } }

/* Infinite task reading the state */
void appLoop_SWITCHtask(void)
{ /* This register is already zero per default, so we can save two bytes: devSwitchDRR = 0x00; */
  while (true)
  { state = devSwitchPIN;  } }


