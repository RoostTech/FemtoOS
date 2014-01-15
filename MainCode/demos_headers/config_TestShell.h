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

#ifndef CONFIG_SHELL_H_
#define CONFIG_SHELL_H_

/* Comments are in the config default file */

/* ========================================================================= */
/* SYSTEM CONFIGURATION ==================================================== */
/* ========================================================================= */

#define  cfgSysOptimized                         cfgFalse
#define  cfgSysDebug                             cfgFalse
#define  cfgSysInline                            cfgFalse
#define  cfgSysFramePointerCounterMeasures       cfgTrue
#define  cfgSysReduceProEpilogue                 cfgBikini
#define  cfgSysRegisterCheckByte                 0xA5
#define  cfgSysStackGrowthUp                     cfgFalse
#define  cfgSysZeroPageStack                     cfgFalse
#define  cfgSysClearUnusedR1                     cfgTrue
#define  cfgSysSqueezeState                      defSysOptimized
#define  cfgSysReuseOsStack                      cfgFalse
#define  cfgSysClockDivider                      1
#define  cfgSysSubTicksPerFullTick               32
#define  cfgSysSubTickDivider                    256
#define  cfgSysGCCstartup                        cfgOverride
#define  cfgSysFsStorageSpace                    512


/* ========================================================================= */
/* INTERRUPT HANDLING ====================================================== */
/* ========================================================================= */

#define  cfgIntGlobalOnly                        cfgTrue
#define  cfgIntUserDefined                       cfgTrue
#define  cfgIntSwitchUsesOSstack                 cfgTrue
#define  cfgIntOsProtected                       cfgTrue
#define  cfgIntTickTrack                         cfgFalse
#define  cfgIntManualTicks                       cfgFalse


/* ========================================================================= */
/* QUALITY ASSURANCE ======================================================= */
/* ========================================================================= */

#define  cfgCheckSystem                          cfgFalse
#define  cfgCheckReset                           cfgTrue
#define  cfgCheckTrace                           cfgFalse
#define  cfgCheckAlwaysFatal                     cfgFalse
#define  cfgCheckWatermarks                      cfgTrue
#define  cfgCheckOsStack                         cfgTrue
#define  cfgCheckTaskStack                       cfgTrue
#define  cfgCheckIsrStack                        cfgFalse
#define  cfgCheckRegisters                       cfgTrue
#define  cfgCheckTiming                          cfgFalse
#define  cfgCheckQueuFilling                     cfgTrue
#define  cfgCheckMethodUse                       cfgFalse
#define  cfgCheckApplication                     cfgFalse


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
#define  cfgUseTaskWatchdog                      cfgTrue
#define  cfgUseCorrectWakeupTimes                cfgFalse
#define  cfgUseTimeout                           cfgFalse
#define  cfgUseTasknames                         cfgTrue
#define  cfgUseLowPowerSleep                     cfgFalse
#define  cfgUseLowPowerOnDelay                   cfgFalse
#define  cfgUseLowPowerDelayRelease              cfgFalse
#define  cfgUseLoadMonitor                       cfgTrue
#define  cfgUseFileSystem                        cfgTrue
#define  cfgUseFileSystemConcurrentRead          cfgFalse
#define  cfgUseFileSystemEconomyMode             cfgFalse
#define  cfgUseFileSystemMaintainFAT             cfgTrue
#define  cfgUseEvents                            cfgFalse
#define  cfgUseEventsOnVariables                 cfgFalse


/* ========================================================================= */
/* CODE PARAMETERS ========================================================= */
/* ========================================================================= */

#define  cfgNumWatchdogDiv                       3
#define  cfgNumMonitorDiv                        3
#define  cfgNumSleepPeriod                       0
#define  cfgNumSleepThreshold                    0
#define  cfgNumGlobWidth                         2
#define  cfgNumSwitchWidth                       0
#define  cfgNumTickWidth                         0


/* ========================================================================= */
/* EXTERNAL CALLS ========================================================== */
/* ========================================================================= */

#define  callAppTick00                           cfgFalse
#define  callAppTick08                           cfgFalse
#define  callAppTick16                           cfgTrue
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
#define  includeGenSuspend                       cfgTrue
#define  includeTaskSuspend                      cfgTrue
#define  includeGenResume                        cfgTrue
#define  includeTaskSleep                        cfgFalse
#define  includeTaskSleepAll                     cfgFalse
#define  includeGenSetPriority                   cfgTrue
#define  includeGenGetPriority                   cfgFalse
#define  includeGenGetTickCount                  cfgTrue
#define  includeGenAddtoTickCount                cfgFalse
#define  includeGenGetLastWakeTime               cfgFalse
#define  includeTaskFeedWatchdog                 cfgTrue
#define  includeTaskKillWatchdog                 cfgFalse
#define  includeGenGetTaskname                   cfgFalse
#define  includeTaskTerminate                    cfgTrue
#define  includeGenReboot                        cfgTrue
#define  includeTaskRecreate                     cfgTrue
#define  includeTaskRestart                      cfgTrue
#define  includeGenLogTask                       cfgTrue
#define  includeGenLogOs                         cfgTrue
#define  includeGenTrace                         cfgFalse
#define  includeGenPipeInt16                     cfgTrue
#define  includeGenPassFlashString               cfgTrue

/* Event functions --------------------------------------------------------- */
#define  includeTaskWaitForEvents                cfgFalse
#define  includeIsrFireEvent                     cfgFalse
#define  includeGenFireEvent                     cfgFalse
#define  includeGenFireEventSet                  cfgFalse
#define  includeGenCountEventBlocks              cfgFalse

/* Synchronization functions ----------------------------------------------- */
#define  includeTaskWaitForTasks                 cfgFalse
#define  includeGenWaitRelease                   cfgFalse
#define  includeTaskMutex                        cfgFalse
#define  includeTaskQueu                         cfgTrue

/* Queu functions --------------------------------------------------------- */
#define  includeGenQueuWrite                     cfgTrue
#define  includeGenQueuRead                      cfgTrue
#define  includeGenQueuUnwrite                   cfgFalse
#define  includeGenQueuUnread                    cfgFalse
#define  includeGenQueuClear                     cfgTrue
#define  includeGenQueuPeek                      cfgFalse
#define  includeGenQueuReadable                  cfgTrue
#define  includeGenQueuWriteable                 cfgFalse
#define  includeGenQueuFull                      cfgFalse
#define  includeGenQueuEmpty                     cfgTrue

/* File System functions --------------------------------------------------- */
#define  includeTaskFileAccess                   cfgTrue
#define  includeTaskFileFormat                   cfgFalse
#define  includeTaskFileGetSize                  cfgTrue
#define  includeTaskFileSetSize                  cfgFalse
#define  includeTaskFileReadByte                 cfgFalse
#define  includeTaskFileWriteByte                cfgFalse
#define  includeTaskFileAppendByte               cfgFalse
#define  includeTaskFileReadPipe                 cfgTrue
#define  includeTaskFileWritePipe                cfgTrue
#define  includeTaskFileReadBuffer               cfgTrue
#define  includeTaskFileWriteBuffer              cfgTrue

/* Protection functions ---------------------------------------------------- */
#define  includeTaskProtectGlobalInterrupts      cfgFalse
#define  includeTaskProtectSwitchTasks           cfgFalse
#define  includeTaskProtectTickInterrupts        cfgFalse
#define  includeTaskProtectGlobalCritical        cfgTrue
#define  includeTaskProtectSwitchCritical        cfgFalse
#define  includeTaskProtectTickCritical          cfgFalse

/* ISR header/footer functions --------------------------------------------- */
#define  includeIsrEnter                         cfgTrue
#define  includeIsrExit                          cfgTrue
#define  includeIsrBegin                         cfgFalse
#define  includeIsrEndReturn                     cfgFalse
#define  includeIsrEndYield                      cfgFalse
#define  includeIsrStartLoad                     cfgFalse
#define  includeIsrStopLoad                      cfgFalse

/* Quality assurance functions --------------------------------------------- */
#define  includeTaskStackCheck                   cfgTrue
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
#define  CN_08                                   T4Bus
#define  CN_09                                   Shell


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
#define  TaskInclude_T4Bus                       cfgStartRunning
#define  TaskInclude_Shell                       cfgStartRunning


/* ========================================================================= */
/* TASK CAPABILITIES ======================================================= */
/* ========================================================================= */

#define  Capabilities_LEDtask0                   cfgCapDelay | cfgCapCritical
#define  Capabilities_LEDtask1                   cfgCapDelay | cfgCapCritical
#define  Capabilities_LEDtask2                   cfgCapDelay | cfgCapCritical
#define  Capabilities_LEDtask3                   cfgCapDelay | cfgCapCritical
#define  Capabilities_LEDtask4                   cfgCapDelay | cfgCapCritical
#define  Capabilities_LEDtask5                   cfgCapDelay | cfgCapCritical
#define  Capabilities_LEDtask6                   cfgCapDelay | cfgCapCritical
#define  Capabilities_LEDtask7                   cfgCapDelay | cfgCapCritical
#define  Capabilities_T4Bus                      cfgCapDelay | cfgCapWatchdog | cfgCapSynchronization
#define  Capabilities_Shell                      cfgCapDelay | cfgCapSynchronization | cfgCapFileSystem


/* ========================================================================= */
/* STACK SIZES ============================================================= */
/* ========================================================================= */

#define  StackSafety                             0
#define  StackSizeOS                             32
#define  StackSizeISR                            0
#define  StackSizeShared                         21
#define  StackSize_LEDtask0                      21
#define  StackSize_LEDtask1                      cfgShared
#define  StackSize_LEDtask2                      cfgShared
#define  StackSize_LEDtask3                      cfgShared
#define  StackSize_LEDtask4                      cfgShared
#define  StackSize_LEDtask5                      cfgShared
#define  StackSize_LEDtask6                      cfgShared
#define  StackSize_LEDtask7                      cfgShared
#define  StackSize_T4Bus                         32
#define  StackSize_Shell                         70


/* ========================================================================= */
/* TIMES SLICES ============================================================ */
/* ========================================================================= */

#define  TimeSliceIdleTime                       cfgSysSubTicksPerFullTick
#define  TimeSliceOverride                       cfgSysSubTicksPerFullTick


/* ========================================================================= */
/* RUNTIME TASK NAMES ====================================================== */
/* ========================================================================= */

#define  TaskName_LEDtask0                       "LED 0"
#define  TaskName_LEDtask1                       "LED 1"
#define  TaskName_LEDtask2                       "LED 2"
#define  TaskName_LEDtask3                       "LED 3"
#define  TaskName_LEDtask4                       "LED 4"
#define  TaskName_LEDtask5                       "LED 5"
#define  TaskName_LEDtask6                       "LED 6"
#define  TaskName_LEDtask7                       "LED 7"
#define  TaskName_T4Bus                          "T4 Bus"
#define  TaskName_Shell                          "Shell"


/* ========================================================================= */
/* TASK PRIORITIES ========================================================= */
/* ========================================================================= */

#define  Priority_LEDtask0                       4
#define  Priority_LEDtask1                       2
#define  Priority_LEDtask2                       2
#define  Priority_LEDtask3                       2
#define  Priority_LEDtask4                       2
#define  Priority_LEDtask5                       2
#define  Priority_LEDtask6                       2
#define  Priority_LEDtask7                       2
#define  Priority_T4Bus                          3
#define  Priority_Shell                          3


/* ========================================================================= */
/* REGISTER USE ============================================================ */
/* ========================================================================= */

#define  RegisterUse_LEDtask0                    r16_upto_r31
#define  RegisterUse_LEDtask1                    r16_upto_r31
#define  RegisterUse_LEDtask2                    r16_upto_r31
#define  RegisterUse_LEDtask3                    r16_upto_r31
#define  RegisterUse_LEDtask4                    r16_upto_r31
#define  RegisterUse_LEDtask5                    r16_upto_r31
#define  RegisterUse_LEDtask6                    r16_upto_r31
#define  RegisterUse_LEDtask7                    r16_upto_r31
#define  RegisterUse_T4Bus                       r16_upto_r31
#define  RegisterUse_Shell                       registersAll


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
#define  RegisterCheck_T4Bus                     registersAll & (~r12r13r14r15)
#define  RegisterCheck_Shell                     registersAll


/* ========================================================================= */
/* INTERRUPT SETTING ======================================================= */
/* ========================================================================= */

#define  InterruptStartOverride                  cfgGlobSet | cfgTickSet
#define  InterruptStart_LEDtask0                 cfgGlobSet | cfgTickSet
#define  InterruptStart_LEDtask1                 cfgGlobSet | cfgTickClear
#define  InterruptStart_LEDtask2                 cfgGlobSet | cfgTickClear
#define  InterruptStart_LEDtask3                 cfgGlobSet | cfgTickClear
#define  InterruptStart_LEDtask4                 cfgGlobSet | cfgTickClear
#define  InterruptStart_LEDtask5                 cfgGlobSet | cfgTickClear
#define  InterruptStart_LEDtask6                 cfgGlobSet | cfgTickClear
#define  InterruptStart_LEDtask7                 cfgGlobSet | cfgTickClear
#define  InterruptStart_T4Bus                    cfgGlobSet | cfgTickSet
#define  InterruptStart_Shell                    cfgGlobSet | cfgTickSet


/* ========================================================================= */
/* EVENT NAMES ============================================================= */
/* ========================================================================= */


/* ========================================================================= */
/* SLOT NAMES ============================================================== */
/* ========================================================================= */

#define  SN_01                                   WriteQueuT4
#define  SN_02                                   ReadQueuT4


/* ========================================================================= */
/* SLOT SIZES ============================================================== */
/* ========================================================================= */

#define  SlotSize_LEDtask0                       0
#define  SlotSize_LEDtask1                       0
#define  SlotSize_LEDtask2                       0
#define  SlotSize_LEDtask3                       0
#define  SlotSize_LEDtask4                       0
#define  SlotSize_LEDtask5                       0
#define  SlotSize_LEDtask6                       0
#define  SlotSize_LEDtask7                       0
#define  SlotSize_T4Bus                          1
#define  SlotSize_Shell                          1


/* ========================================================================= */
/* SLOT USAGE ============================================================== */
/* ========================================================================= */

#define  SlotUse_WriteQueuT4                     cfgUseAsQueu
#define  SlotUse_ReadQueuT4                      cfgUseAsQueu


/* ========================================================================= */
/* QUEU SIZES ============================================================== */
/* ========================================================================= */

#define  QueuSize_WriteQueuT4                    24
#define  QueuSize_ReadQueuT4                     20


/* ========================================================================= */
/* FILE NAMES ============================================================== */
/* ========================================================================= */

#define  FN_00                                   state0
#define  FN_01                                   state1
#define  FN_02                                   state2
#define  FN_03                                   state3


/* ========================================================================= */
/* FILE SIZES ============================================================== */
/* ========================================================================= */

#define  FileSpaceStandard                       16
#define  FileSpace_state0                        24
#define  FileSpace_state1                        24
#define  FileSpace_state2                        24
#define  FileSpace_state3                        24

#endif /*CONFIG_SHELL_H_*/
