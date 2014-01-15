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
 * The Hello World example is made to get you started and this is the file
 * you want to play with. Do not use other examples to that end, that will
 * be a disappointing experience (or a steep learning curve)
 *
 * Explanation on the website, point your browser at:
 * http://www.femtoos.org/code_start.html
 */

/* This this the only include needed in your code .*/
#include "femtoos_code.h"


static Tuint08 speed = 0;

const Tchar HelloWorldStr[] PROGMEM = "Hello World.";

void appBoot(void)
{ devLedDRR    = 0xFF;
  devLedPORT   = 0xFF;
  devSwitchDRR = 0x00; }



#if (preTaskDefined(Display))

void appLoop_Display(void)
{ speed = 64;
  while (true)
  { Tuint08 uiCharCount;
    Tchar cChar;
    for (uiCharCount = 0; uiCharCount<12; uiCharCount++)
    { cChar = portFlashReadByte(Tchar, HelloWorldStr[uiCharCount]);
      devLedPORT = ~cChar;
      taskDelayFromNow( ((Tuint16)speed)*4 + 64 );
      devLedPORT = 0xFF;
      taskDelayFromNow(64); }
    taskDelayFromNow(2000); } }

#endif



#if (preTaskDefined(Speed))

void appLoop_Speed(void)
{ Tuint08 button  = devSwitchPIN & 01;
  Tuint08 lastbutton  = button;
  while (true)
  { button = devSwitchPIN & 01;
    if (button != lastbutton) { speed += 64; }
    taskDelayFromNow(100); } }

#endif

