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
 * This example is made to demonstrate how small the Femto OS can be. It runs
 * only the idle task, which is not really a task since it runs totally
 * in OS space. However, there is the possibility to add some code to
 * this 'task' through the idle hook. Here we made a 16 bit counter out
 * of the I/O lines.
 */

/* This this the only include needed in your code .*/
#include "femtoos_code.h"


/* This is the hook activated just before the OS goes idle. */
void appEnterIdle(void)
{ /* Using a register saves 2 bytes ;-) */
  Tuint08 newPortB = devSwitchPORT--;
  /* Start counting on all i/o lines */
  if (newPortB == 0x00) { devLedPORT--; } }


/* This is called once at system boot, and before the creating of any of
 * the tasks. Use it to initialize the hardware. */
void appBoot(void)
{ /* Make sure all lines are output */
  devLedDRR = 0xFF;
  devSwitchDRR = 0xFF;  }
