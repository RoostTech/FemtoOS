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
 * The Remember demonstration fills the file system with random
 * numbers and calculates a (xor) hash on before hand. Then three
 * worker tasks are started which read the files with concurrently and
 * calculate hash's for each files. When all workers are done
 * the main task combines the result and checks if it is equal
 * to the value before. If so, a new round is started. Note that
 * this demo wears out the EEPROM rapidly.
 * */


/* This this the only include needed in your code .*/
#include "femtoos_code.h"


/* This is called once at system boot, and before the creating of any of
 * the tasks. Use it to initialize the hardware. */
void appBoot(void)
{ devLedDRR    |= 0xFF;
  devSwitchDRR &= 0x0F;
  devLedPORT |= 0xFF; }


/**
 * This worker process read two files of 8 bytes, xor the values and store the result.
 * The workers are greedy and try to do a much work as possible, thereby hindering
 * each other. This is intentional, to test the blocking of the OS. After each layer
 * has been completed. the worker waits for an event to continue
 *
 * The function contains tracers. This was needed for me to get this demo working
 * (concurrent administration of which files where done and which not was not as
 * easy as i expected). The tracers are removed by the preprocessor if not used.
 *
 * This demo also shows how to make use of variable events. The events are used to
 * signal the workers a new batch is ready for them.
 */

static void WorkerProcess(void) __attribute__((noreturn));

static void WorkerProcess(void)
{ Tuint08 uiCount;
  Tuint08 uiFileOffset;
  Tuint08 uiLayer;
  Tuint08 uiSet;
  Tuint08 uiMemShift;
  Tuint08 uiInputA[8];
  Tuint08 uiInputB[8];
  Tuint08 uiOutput[8];
  while (true)
  { uiLayer = 0;
    uiMemShift = 0;
    do
    { taskWaitForEvent(uiLayer);
      uiSet = 8 >> uiLayer;
      do
      { taskFileOpen(defReadWrite);
        uiFileOffset = taskFileReadByteOnName(LayerInfo,uiLayer);
        genTraceByteInfo(uiLayer);
        genTraceByteInfo(uiFileOffset);
        taskFileWriteByteOnName(LayerInfo,uiLayer,uiFileOffset+1);
        taskFileClose();
        if (uiFileOffset < uiSet)
        { taskFileOpen(defReadOnly);
          taskFileReadBuffer(2+uiMemShift+2*uiFileOffset,0,8,(Taddress) uiInputA);
          taskFileReadBuffer(3+uiMemShift+2*uiFileOffset,0,8,(Taddress) uiInputB);
          taskFileClose();
          for (uiCount=0; uiCount<8; uiCount++) { uiOutput[uiCount] = uiInputA[uiCount] ^ uiInputB[uiCount]; }
          taskFileOpen(defReadWrite);
          taskFileWriteBuffer(2+uiMemShift+2*uiSet+uiFileOffset,0,8,(Taddress) uiOutput);
          taskFileClose(); } }
      while (uiFileOffset < uiSet);
      uiMemShift += 2*uiSet;  }
    while (uiLayer++ < 3); } }



/* We can define the number of workers in the configuration. By this construction
 * we let the main process know which workers are present to do work. All workers
 * make use of the reentrant function  WorkerProcess();
 */

#if (preTaskDefined(Worker0Task))
  void appLoop_Worker0Task(void) { WorkerProcess(); }
  #define WP0 1
#else
  #define WP0 0
#endif


#if (preTaskDefined(Worker1Task))
  void appLoop_Worker1Task(void) { WorkerProcess(); }
  #define WP1 1
#else
  #define WP1 0
#endif


#if (preTaskDefined(Worker2Task))
  void appLoop_Worker2Task(void) { WorkerProcess(); }
  #define WP2 1
#else
  #define WP2 0
#endif

#if (preTaskDefined(SleepTask))
void appLoop_SleepTask(void) {}

#endif


#if (preTaskDefined(SupervisorTask))

void appLoop_SupervisorTask(void)
{ taskFileOpen(defReadWrite);
  taskFileFormat();
  /* define files filled with zero's. */
  taskFileSetSizeOnName(LayerInfo,FileSpace_LayerInfo);
  taskFileSetSizeOnName(Status,FileSpace_Status);
  taskFileClose();
  Tuint08 uiStatus[4];
  taskDelayFromNow(10);
  while (true)
  { genTraceMarker();
    /* prepare the first stage, fill 16 files with 'random' values. */
    taskFileOpen(defReadWrite);
    taskFileReadBufferOnName(Status,defFromFileStart,4,(Taddress) uiStatus);
    Tuint16 uiSeed = ((Tuint16) uiStatus[2] << 8) + (Tuint16) uiStatus[3];
    Tuint16 uiValue = 0;
    Tuint08 uiFileCount;
    for (uiFileCount=0; uiFileCount<16; uiFileCount++)
    { taskFileClear(2+uiFileCount);
      Tuint08 uiByteCount;
      for (uiByteCount=0; uiByteCount<8; uiByteCount++)
      { Tuint08 uiStored = (Tuint08) uiSeed;
        uiValue ^= uiStored;
        devLedPORT = ~uiValue;
        taskFileAppendByte(2+uiFileCount,uiStored);
        uiSeed = (uiSeed * 9497U + 129U) >> 1; } }
    uiStatus[0] = uiStatus[0] + 1;
    uiStatus[1] = uiValue;
    uiStatus[2] = (Tuint08) (uiSeed>>8);
    uiStatus[3] = (Tuint08) (uiSeed & 0xFF);
    taskFileWriteBufferOnName(Status,defFromFileStart,4,(Taddress) uiStatus);
    taskFileClose();
    devLedPORT = ~uiValue;
    taskDelayFromNow(1000);
    devLedPORT = ~0x00;
    /* Set it loose! */
    Tuint08 uiLayer = 0;

    do
    { genTraceMarker();
      Tuint08 uiLayerInfo = 0;
      switch (uiLayer)
      { case 0: { genFireEvent(0); } break;
        case 1: { genFireEvent(1); } break;
        case 2: { genFireEvent(2); } break;
        case 3: { genFireEvent(3); } break;
        case 4: { genFireEvent(4); } break; }
      /* TODO: If we want to add a task for sleeping, the number below is no longer correct. */
      while ((genCountEventBlocks(1 << ((uiLayer+1)%4)) < (WP0+WP1+WP2-1)))
      { taskFileOpen(defReadOnly);
        uiLayerInfo = taskFileReadByteOnName(LayerInfo,uiLayer);
        taskFileClose();
        genTraceByteInfo(uiLayer);
        genTraceByteInfo(uiLayerInfo);
        devLedPORT = ~((uiLayer <<4) | uiLayerInfo);
        /* We must wait here so that the worker threads have some air to breath. */
        taskDelayFromNow(5);
        }

      taskDelayFromNow(100); }
    while(uiLayer++ < 3);
    Tuint08 uiInput[8];
    taskFileOpen(defReadOnly);
    taskFileReadBuffer(2+16+8+4+2,defFromFileStart,8,(Taddress) uiInput);
    taskFileClose();
    Tuint08 uiCount;
    taskFileOpen(defReadWrite);
    for (uiCount=0; uiCount<FileSpace_LayerInfo; uiCount++) { taskFileWriteByteOnName(LayerInfo,uiCount,0); }
    taskFileClose();
    Tuint08 uiCheckValue = 0;
    for (uiCount=0; uiCount<8; uiCount++) { uiCheckValue ^= uiInput[uiCount]; }
    if (uiCheckValue == uiStatus[1])
    { devLedPORT = ~uiCheckValue;
      taskDelayFromNow(5000); }
    else
    { while (true)
      { devLedPORT = uiCheckValue;
        taskDelayFromNow(300);
        devLedPORT = uiStatus[1];
        taskDelayFromNow(300); } } } }

#endif

