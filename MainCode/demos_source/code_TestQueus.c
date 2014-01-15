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
 * Here we show the simple use of a queue. One 12 byte queue is defined
 * which is written to from one task, 8 bytes at a time, and is read
 * from in an other task, 6 bytes at a time. If a task does not gets
 * access to the queue because it is blocked, it tries for about one
 * second (using the time-out facility on locks) and then complains
 * for about one second by blinking a led. It subsequently tries again.
 * Notice the dynamics of the process, which is:
 *   write - read - write - read - write - read - read and then it
 * repeats itself. It is possible to reset (empty) the queue by pushing
 * the button.
 */


/* This this the only include needed in your code .*/
#include "femtoos_code.h"

/* For this application i choose for a decent, that is concurrency protected, way
 * to flip a ledbit. Inverting a bit cannot be compiled to an atomic instruction by gcc. */
static void invLed(Tuint08 lednr)
{ taskEnterSwitchCritical();
  devLedPORT ^= (1 << lednr);
  taskExitSwitchCritical(); }

/* Writing a number to the display need such a protection too. By using a mask we can write
 * a number to a specific part of the display, leaving the rest as is. */
static void setNumber(Tuint08 mask,Tuint08 number)
{ taskEnterSwitchCritical();
  devLedPORT = ~((~devLedPORT & (mask)) | (number));
  taskExitSwitchCritical(); }

/* After the appBoot (which is not used in this example) the OS calls for each
 * task to be started the function appInit_[taskname]. Here, you can set task
 * specific hardware initialization. You can be sure that all initializers of
 * all tasks are called before any task is started. */
void appInit_WriteTask(void)
{ devLedDRR  |= 0x0F;
  devLedPORT |= 0x0F; }


/* The write task writes number into the queue in series of 8, as long as
 * space allows for. The numbers written are displayed. When the queue
 * cannot be obtained, a wait led starts flashing until a new attempt is
 * done. */
void appLoop_WriteTask(void)
{ Tuint08 count = 0;
  while (true)
  { if (taskQueuWriteRequestOnName(ThePipe,8,800))
    { for (count=0; count<8; count++)
      { genQueuWriteOnName(ThePipe,count);
        setNumber(0xF0,count);
        taskDelayFromNow(600); }
      taskQueuReleaseOnName(ThePipe); }
    else
    { for (count=0; count<10; count++)
      { invLed(3);
        taskDelayFromNow(80); } } } }


/* After the appBoot (which is not used in this example) the OS calls for each
 * task to be started the function appInit_[taskname]. Here, you can set task
 * specific hardware initialization. You can be sure that all initializers of
 * all tasks are called before any task is started. */
void appInit_ReadTask(void)
{ devLedDRR  |= 0xF0;
  devLedPORT |= 0xF0; }


/* The read task reads numbers from the queue in series of 6, as long as
 * numbers are available. The numbers read are displayed. When the queue
 * cannot be obtained, a wait led starts flashing until a new attempt is
 * done. */
void appLoop_ReadTask(void)
{ Tuint08 count = 0;
  Tuint08 Result;
  while (true)
  { if (taskQueuReadRequestOnName(ThePipe,6,800))
    { for (count=0; count<6; count++)
      { Result = genQueuReadOnName(ThePipe);
        setNumber(0x0F,Result<<4);
        taskDelayFromNow(600); }
      taskQueuReleaseOnName(ThePipe); }
    else
    { for (count=0; count<10; count++)
      { invLed(7);
        taskDelayFromNow(80); } } } }


#if (preTaskDefined(ResetTask))

/* Special initialization for the reset task, we need the switches to be input. */
void appInit_ResetTask(void)
{ devSwitchDRR = 0x00; }

/* If you want you can reset the queue by pushing the button.
 * This task starts waiting until a lock on the queue is
 * obtained. When this is the case, the queue is reset. */
void appLoop_ResetTask(void)
{ Tuint08 button  = devSwitchPIN & 01;
  Tuint08 lastbutton  = button;
  while (true)
  { button = devSwitchPIN & 01;
    if (button != lastbutton)
    { setNumber(0x88,0x88);
      taskQueuReadRequestOnName(ThePipe,0,defDelayTimeMax);
      Tuint08 uiLedState = devLedPORT;
      devLedPORT = 0x00;
      genQueuClearOnName(ThePipe);
      taskDelayFromNow(80);
      devLedPORT = uiLedState;
      taskQueuReleaseOnName(ThePipe); }
    taskDelayFromNow(100); } }

#endif

