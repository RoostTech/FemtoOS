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

#ifndef CONFIG_TESTRENDEZVOUS_H_
#define CONFIG_TESTRENDEZVOUS_H_

/* Comments are in the config default file */

/* ========================================================================= */
/* SYSTEM CONFIGURATION ==================================================== */
/* ========================================================================= */

#define  cfgSysOptimized                         cfgFalse
#define  cfgSysDebug                             cfgFalse
#define  cfgSysInline                            cfgFalse
#define  cfgSysFramePointerCounterMeasures       cfgFalse
#define  cfgSysReduceProEpilogue                 cfgBikini
#define  cfgSysRegisterCheckByte                 0xA5
#define  cfgSysStackGrowthUp                     cfgFalse
#define  cfgSysZeroPageStack                     cfgFalse
#define  cfgSysClearUnusedR1                     cfgTrue
#define  cfgSysSqueezeState                      defSysOptimized
#define  cfgSysReuseOsStack                      cfgTrue
#define  cfgSysClockDivider                      1
#define  cfgSysSubTicksPerFullTick               32
#define  cfgSysSubTickDivider                    256
#define  cfgSysGCCstartup                        cfgOverride
#define  cfgSysFsStorageSpace                    0


/* ========================================================================= */
/* INTERRUPT HANDLING ====================================================== */
/* ========================================================================= */

#define  cfgIntGlobalOnly                        cfgTrue
#define  cfgIntUserDefined                       cfgFalse
#define  cfgIntSwitchUsesOSstack                 cfgFalse
#define  cfgIntOsProtected                       cfgFalse
#define  cfgIntTickTrack                         cfgFalse
#define  cfgIntManualTicks                       cfgFalse


/* ========================================================================= */
/* QUALITY ASSURANCE ======================================================= */
/* ========================================================================= */

#if (defSysOptimized == cfgTrue)

#define  cfgCheckSystem                          cfgFalse
#define  cfgCheckReset                           cfgFalse
#define  cfgCheckTrace                           cfgFalse
#define  cfgCheckAlwaysFatal                     cfgFalse
#define  cfgCheckWatermarks                      cfgFalse
#define  cfgCheckOsStack                         cfgFalse
#define  cfgCheckTaskStack                       cfgFalse
#define  cfgCheckIsrStack                        cfgFalse
#define  cfgCheckRegisters                       cfgFalse
#define  cfgCheckTiming                          cfgFalse
#define  cfgCheckQueuFilling                     cfgFalse
#define  cfgCheckMethodUse                       cfgFalse
#define  cfgCheckApplication                     cfgFalse

#else

#define  cfgCheckSystem                          cfgTrue
#define  cfgCheckReset                           cfgTrue
#define  cfgCheckTrace                           cfgFalse
#define  cfgCheckAlwaysFatal                     cfgFalse
#define  cfgCheckWatermarks                      cfgFalse
#define  cfgCheckOsStack                         cfgTrue
#define  cfgCheckTaskStack                       cfgTrue
#define  cfgCheckIsrStack                        cfgFalse
#define  cfgCheckRegisters                       cfgTrue
#define  cfgCheckTiming                          cfgTrue
#define  cfgCheckQueuFilling                     cfgFalse
#define  cfgCheckMethodUse                       cfgTrue
#define  cfgCheckApplication                     cfgFalse

#endif


/* ========================================================================= */
/* COMMON CAPABILITIES ===================================================== */
/* ========================================================================= */

#define  cfgUseEquidistantTicks                  cfgTrue
#define  cfgUseDelay                             cfgTrue
#define  cfgUseSuspendOnDelay                    cfgFalse
#define  cfgUseSynchronization                   cfgSyncSingleSlot
#define  cfgUseHierarchicalRoundRobin            cfgFalse
#define  cfgUseNestedCriticals                   cfgFalse
#define  cfgUsePrioritizedRelease                cfgFalse
#define  cfgUsePriorityLifting                   cfgFalse
#define  cfgUseTaskWatchdog                      cfgFalse
#define  cfgUseCorrectWakeupTimes                cfgFalse
#define  cfgUseTimeout                           cfgFalse
#define  cfgUseTasknames                         cfgFalse
#define  cfgUseLowPowerSleep                     cfgFalse
#define  cfgUseLowPowerOnDelay                   cfgFalse
#define  cfgUseLowPowerDelayRelease              cfgFalse
#define  cfgUseLoadMonitor                       cfgFalse
#define  cfgUseFileSystem                        cfgFalse
#define  cfgUseFileSystemConcurrentRead          cfgFalse
#define  cfgUseFileSystemEconomyMode             cfgFalse
#define  cfgUseFileSystemMaintainFAT             cfgFalse
#define  cfgUseEvents                            cfgFalse
#define  cfgUseEventsOnVariables                 cfgFalse


/* ========================================================================= */
/* CODE PARAMETERS ========================================================= */
/* ========================================================================= */

#define  cfgNumWatchdogDiv                       0
#define  cfgNumMonitorDiv                        0
#define  cfgNumSleepPeriod                       0
#define  cfgNumSleepThreshold                    0
#define  cfgNumGlobWidth                         0
#define  cfgNumSwitchWidth                       0
#define  cfgNumTickWidth                         0


/* ========================================================================= */
/* EXTERNAL CALLS ========================================================== */
/* ========================================================================= */

#define  callAppTick00                           cfgFalse
#define  callAppTick08                           cfgFalse
#define  callAppTick16                           cfgFalse
#define  callAppTickSleep                        cfgFalse
#define  callAppEnterIdle                        cfgFalse
#define  callAppEnterSleep                       cfgFalse
#define  callAppExitSleep                        cfgFalse
#define  callAppBoot                             cfgTrue
#define  callAppInit                             cfgFalse
#define  callAppBark                             cfgFalse


/* ========================================================================= */
/* API INCLUSIONS ========================================================== */
/* ========================================================================= */

/* Standard functions ------------------------------------------------------ */
#define  includeTaskYield                        cfgFalse
#define  includeTaskDelayFromNow                 cfgTrue
#define  includeTaskDelayFromWake                cfgFalse
#define  includeGenSuspend                       cfgFalse
#define  includeTaskSuspend                      cfgFalse
#define  includeGenResume                        cfgFalse
#define  includeTaskSleep                        cfgFalse
#define  includeTaskSleepAll                     cfgFalse
#define  includeGenSetPriority                   cfgFalse
#define  includeGenGetPriority                   cfgFalse
#define  includeGenGetTickCount                  cfgFalse
#define  includeGenAddtoTickCount                cfgFalse
#define  includeGenGetLastWakeTime               cfgFalse
#define  includeTaskFeedWatchdog                 cfgFalse
#define  includeTaskKillWatchdog                 cfgFalse
#define  includeGenGetTaskname                   cfgFalse
#define  includeTaskTerminate                    cfgFalse
#define  includeGenReboot                        cfgFalse
#define  includeTaskRecreate                     cfgFalse
#define  includeTaskRestart                      cfgFalse
#define  includeGenLogTask                       cfgFalse
#define  includeGenLogOs                         cfgFalse
#define  includeGenTrace                         cfgFalse
#define  includeGenPipeInt16                     cfgFalse
#define  includeGenPassFlashString               cfgFalse

/* Event functions --------------------------------------------------------- */
#define  includeTaskWaitForEvents                cfgFalse
#define  includeIsrFireEvent                     cfgFalse
#define  includeGenFireEvent                     cfgFalse
#define  includeGenFireEventSet                  cfgFalse
#define  includeGenCountEventBlocks              cfgFalse

/* Synchronization functions ----------------------------------------------- */
#define  includeTaskWaitForTasks                 cfgTrue
#define  includeGenWaitRelease                   cfgFalse
#define  includeTaskMutex                        cfgFalse
#define  includeTaskQueu                         cfgFalse

/* Queu functions --------------------------------------------------------- */
#define  includeGenQueuWrite                     cfgFalse
#define  includeGenQueuRead                      cfgFalse
#define  includeGenQueuUnwrite                   cfgFalse
#define  includeGenQueuUnread                    cfgFalse
#define  includeGenQueuClear                     cfgFalse
#define  includeGenQueuPeek                      cfgFalse
#define  includeGenQueuReadable                  cfgFalse
#define  includeGenQueuWriteable                 cfgFalse
#define  includeGenQueuFull                      cfgFalse
#define  includeGenQueuEmpty                     cfgFalse

/* File System functions --------------------------------------------------- */
#define  includeTaskFileAccess                   cfgFalse
#define  includeTaskFileFormat                   cfgFalse
#define  includeTaskFileGetSize                  cfgFalse
#define  includeTaskFileSetSize                  cfgFalse
#define  includeTaskFileReadByte                 cfgFalse
#define  includeTaskFileWriteByte                cfgFalse
#define  includeTaskFileAppendByte               cfgFalse
#define  includeTaskFileReadPipe                 cfgFalse
#define  includeTaskFileWritePipe                cfgFalse
#define  includeTaskFileReadBuffer               cfgFalse
#define  includeTaskFileWriteBuffer              cfgFalse

/* Protection functions ---------------------------------------------------- */
#define  includeTaskProtectGlobalInterrupts      cfgFalse
#define  includeTaskProtectSwitchTasks           cfgFalse
#define  includeTaskProtectTickInterrupts        cfgFalse
#define  includeTaskProtectGlobalCritical        cfgFalse
#define  includeTaskProtectSwitchCritical        cfgFalse
#define  includeTaskProtectTickCritical          cfgFalse

/* ISR header/footer functions --------------------------------------------- */
#define  includeIsrEnter                         cfgFalse
#define  includeIsrExit                          cfgFalse
#define  includeIsrBegin                         cfgFalse
#define  includeIsrEndReturn                     cfgFalse
#define  includeIsrEndYield                      cfgFalse
#define  includeIsrStartLoad                     cfgFalse
#define  includeIsrStopLoad                      cfgFalse

/* Quality assurance functions --------------------------------------------- */
#define  includeTaskStackCheck                   cfgFalse
#define  includeIsrStackCheck                    cfgFalse


/* ========================================================================= */
/* TASK NAMES ============================================================== */
/* ========================================================================= */

#define  CN_00                                   LEDtask0
#define  CN_01                                   LEDtask1
#define  CN_02                                   LEDtask2
#define  CN_03                                   LEDtask3
#define  CN_04                                   LEDtask4
#define  CN_05                                   LEDtask5
#define  CN_06                                   LEDtask6
#define  CN_07                                   LEDtask7
#define  CN_08                                   Synchronize


/* ========================================================================= */
/* INCLUDE TASKS =========================================================== */
/* ========================================================================= */

#define  TaskInclude_LEDtask0                    cfgStartRunning
#define  TaskInclude_LEDtask1                    cfgStartRunning
#define  TaskInclude_LEDtask2                    cfgStartRunning
#define  TaskInclude_LEDtask3                    cfgStartRunning
#define  TaskInclude_LEDtask4                    cfgStartRunning
#define  TaskInclude_LEDtask5                    cfgStartRunning
#define  TaskInclude_LEDtask6                    cfgStartRunning
#define  TaskInclude_LEDtask7                    cfgStartRunning
#define  TaskInclude_Synchronize                 cfgStartRunning


/* ========================================================================= */
/* TASK CAPABILITIES ======================================================= */
/* ========================================================================= */

#define  Capabilities_LEDtask0                   cfgCapDelay | cfgCapSynchronization
#define  Capabilities_LEDtask1                   cfgCapDelay | cfgCapSynchronization
#define  Capabilities_LEDtask2                   cfgCapDelay | cfgCapSynchronization
#define  Capabilities_LEDtask3                   cfgCapDelay | cfgCapSynchronization
#define  Capabilities_LEDtask4                   cfgCapDelay | cfgCapSynchronization
#define  Capabilities_LEDtask5                   cfgCapDelay | cfgCapSynchronization
#define  Capabilities_LEDtask6                   cfgCapDelay | cfgCapSynchronization
#define  Capabilities_LEDtask7                   cfgCapDelay | cfgCapSynchronization
#define  Capabilities_Synchronize                cfgCapDelay


/* ========================================================================= */
/* STACK SIZES ============================================================= */
/* ========================================================================= */

#if (defSysOptimized == cfgTrue)

#define  StackSafety                             0
#define  StackSizeOS                             12
#define  StackSizeISR                            0
#define  StackSizeShared                         0
#define  StackSize_LEDtask0                      17
#define  StackSize_LEDtask1                      17
#define  StackSize_LEDtask2                      17
#define  StackSize_LEDtask3                      17
#define  StackSize_LEDtask4                      17
#define  StackSize_LEDtask5                      17
#define  StackSize_LEDtask6                      17
#define  StackSize_LEDtask7                      17
#define  StackSize_Synchronize                   13

#else

#define  StackSafety                             0
#define  StackSizeOS                             20
#define  StackSizeISR                            0
#define  StackSizeShared                         0
#define  StackSize_LEDtask0                      24
#define  StackSize_LEDtask1                      24
#define  StackSize_LEDtask2                      24
#define  StackSize_LEDtask3                      24
#define  StackSize_LEDtask4                      24
#define  StackSize_LEDtask5                      24
#define  StackSize_LEDtask6                      24
#define  StackSize_LEDtask7                      24
#define  StackSize_Synchronize                   24

#endif


/* ========================================================================= */
/* TIMES SLICES ============================================================ */
/* ========================================================================= */

#define  TimeSliceIdleTime                       cfgSysSubTicksPerFullTick
#define  TimeSlice_LEDtask0                      cfgSysSubTicksPerFullTick
#define  TimeSlice_LEDtask1                      cfgSysSubTicksPerFullTick
#define  TimeSlice_LEDtask2                      cfgSysSubTicksPerFullTick
#define  TimeSlice_LEDtask3                      cfgSysSubTicksPerFullTick
#define  TimeSlice_LEDtask4                      cfgSysSubTicksPerFullTick
#define  TimeSlice_LEDtask5                      cfgSysSubTicksPerFullTick
#define  TimeSlice_LEDtask6                      cfgSysSubTicksPerFullTick
#define  TimeSlice_LEDtask7                      cfgSysSubTicksPerFullTick
#define  TimeSlice_Synchronize                   cfgSysSubTicksPerFullTick


/* ========================================================================= */
/* RUNTIME TASK NAMES ====================================================== */
/* ========================================================================= */


/* ========================================================================= */
/* TASK PRIORITIES ========================================================= */
/* ========================================================================= */

#define  Priority_LEDtask0                       0
#define  Priority_LEDtask1                       0
#define  Priority_LEDtask2                       0
#define  Priority_LEDtask3                       0
#define  Priority_LEDtask4                       0
#define  Priority_LEDtask5                       0
#define  Priority_LEDtask6                       0
#define  Priority_LEDtask7                       0
#define  Priority_Synchronize                    1


/* ========================================================================= */
/* REGISTER USE ============================================================ */
/* ========================================================================= */

#if (defSysOptimized == cfgTrue)

#define  RegisterUse_LEDtask0                    r16_upto_r23 | r24r25r26r27
#define  RegisterUse_LEDtask1                    r16_upto_r23 | r24r25r26r27
#define  RegisterUse_LEDtask2                    r16_upto_r23 | r24r25r26r27
#define  RegisterUse_LEDtask3                    r16_upto_r23 | r24r25r26r27
#define  RegisterUse_LEDtask4                    r16_upto_r23 | r24r25r26r27
#define  RegisterUse_LEDtask5                    r16_upto_r23 | r24r25r26r27
#define  RegisterUse_LEDtask6                    r16_upto_r23 | r24r25r26r27
#define  RegisterUse_LEDtask7                    r16_upto_r23 | r24r25r26r27
#define  RegisterUse_Synchronize                 r16r17r18r19 | r24r25r26r27

#else

#define  RegisterUse_LEDtask0                    r16_upto_r31
#define  RegisterUse_LEDtask1                    r16_upto_r31
#define  RegisterUse_LEDtask2                    r16_upto_r31
#define  RegisterUse_LEDtask3                    r16_upto_r31
#define  RegisterUse_LEDtask4                    r16_upto_r31
#define  RegisterUse_LEDtask5                    r16_upto_r31
#define  RegisterUse_LEDtask6                    r16_upto_r31
#define  RegisterUse_LEDtask7                    r16_upto_r31
#define  RegisterUse_Synchronize                 r16_upto_r31

#endif


/* ========================================================================= */
/* REGISTER CHECK ========================================================== */
/* ========================================================================= */

#define  RegisterCheck_LEDtask0                  registersAll
#define  RegisterCheck_LEDtask1                  registersAll
#define  RegisterCheck_LEDtask2                  registersAll
#define  RegisterCheck_LEDtask3                  registersAll
#define  RegisterCheck_LEDtask4                  registersAll
#define  RegisterCheck_LEDtask5                  registersAll
#define  RegisterCheck_LEDtask6                  registersAll
#define  RegisterCheck_LEDtask7                  registersAll
#define  RegisterCheck_Synchronize               registersAll


/* ========================================================================= */
/* INTERRUPT SETTING ======================================================= */
/* ========================================================================= */

#define  InterruptStartOverride                  cfgGlobSet | cfgTickSet


/* ========================================================================= */
/* EVENT NAMES ============================================================= */
/* ========================================================================= */


/* ========================================================================= */
/* SLOT NAMES ============================================================== */
/* ========================================================================= */

#define  SN_01                                   TrefPunt


/* ========================================================================= */
/* SLOT SIZES ============================================================== */
/* ========================================================================= */

#define  SlotSize_LEDtask0                       1
#define  SlotSize_LEDtask1                       1
#define  SlotSize_LEDtask2                       1
#define  SlotSize_LEDtask3                       1
#define  SlotSize_LEDtask4                       1
#define  SlotSize_LEDtask5                       1
#define  SlotSize_LEDtask6                       1
#define  SlotSize_LEDtask7                       1
#define  SlotSize_Synchronize                    1


/* ========================================================================= */
/* SLOT USAGE ============================================================== */
/* ========================================================================= */

#define  SlotUse_TrefPunt                        cfgUseAsWait


/* ========================================================================= */
/* QUEU SIZES ============================================================== */
/* ========================================================================= */


/* ========================================================================= */
/* FILE NAMES ============================================================== */
/* ========================================================================= */


/* ========================================================================= */
/* FILE SIZES ============================================================== */
/* ========================================================================= */

#define  FileSpaceStandard                       0



#endif /*CONFIG_TESTRENDEZVOUS_H_*/
