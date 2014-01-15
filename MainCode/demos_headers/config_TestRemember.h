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

#ifndef CONFIG_TESTFLASHNLEDS_H_
#define CONFIG_TESTFLASHNLEDS_H_

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
#define  cfgSysFsStorageSpace                    512


/* ========================================================================= */
/* INTERRUPT HANDLING ====================================================== */
/* ========================================================================= */

#define  cfgIntGlobalOnly                        cfgTrue
#define  cfgIntUserDefined                       cfgFalse
#define  cfgIntSwitchUsesOSstack                 cfgFalse
#define  cfgIntOsProtected                       cfgTrue
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
#define  cfgUseSynchronization                   cfgSyncNon
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
#define  cfgUseFileSystem                        cfgTrue
#define  cfgUseFileSystemConcurrentRead          cfgTrue
#define  cfgUseFileSystemEconomyMode             cfgFalse
#define  cfgUseFileSystemMaintainFAT             cfgTrue
#define  cfgUseEvents                            cfgTrue
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
#define  includeGenSuspend                       cfgTrue
#define  includeTaskSuspend                      cfgFalse
#define  includeGenResume                        cfgTrue
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
#define  includeGenTrace                         cfgTrue
#define  includeGenPipeInt16                     cfgFalse
#define  includeGenPassFlashString               cfgFalse

/* Event functions --------------------------------------------------------- */
#define  includeTaskWaitForEvents                cfgTrue
#define  includeIsrFireEvent                     cfgFalse
#define  includeGenFireEvent                     cfgTrue
#define  includeGenFireEventSet                  cfgFalse
#define  includeGenCountEventBlocks              cfgTrue

/* Synchronization functions ----------------------------------------------- */
#define  includeTaskWaitForTasks                 cfgFalse
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
#define  includeTaskFileAccess                   cfgTrue
#define  includeTaskFileFormat                   cfgTrue
#define  includeTaskFileGetSize                  cfgFalse
#define  includeTaskFileSetSize                  cfgTrue
#define  includeTaskFileReadByte                 cfgTrue
#define  includeTaskFileWriteByte                cfgTrue
#define  includeTaskFileAppendByte               cfgTrue
#define  includeTaskFileReadPipe                 cfgFalse
#define  includeTaskFileWritePipe                cfgFalse
#define  includeTaskFileReadBuffer               cfgTrue
#define  includeTaskFileWriteBuffer              cfgTrue

/* Protection functions ---------------------------------------------------- */
#define  includeTaskProtectGlobalInterrupts      cfgFalse
#define  includeTaskProtectSwitchTasks           cfgFalse
#define  includeTaskProtectTickInterrupts        cfgFalse
#define  includeTaskProtectGlobalCritical        cfgFalse
#define  includeTaskProtectSwitchCritical        cfgTrue
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

#define  CN_00                                   Worker0Task
#define  CN_01                                   Worker1Task
#define  CN_02                                   Worker2Task
#define  CN_03                                   SupervisorTask
#define  CN_04                                   SleepTask


/* ========================================================================= */
/* INCLUDE TASKS =========================================================== */
/* ========================================================================= */

#define  TaskInclude_Worker0Task                 cfgStartRunning
#define  TaskInclude_Worker1Task                 cfgStartRunning
#define  TaskInclude_Worker2Task                 cfgStartRunning
#define  TaskInclude_SupervisorTask              cfgStartRunning
#define  TaskInclude_SleepTask                   cfgExclude


/* ========================================================================= */
/* TASK CAPABILITIES ======================================================= */
/* ========================================================================= */

#define  Capabilities_Worker0Task                cfgCapFileSystem | cfgCapEvent
#define  Capabilities_Worker1Task                cfgCapFileSystem | cfgCapEvent
#define  Capabilities_Worker2Task                cfgCapFileSystem | cfgCapEvent
#define  Capabilities_SupervisorTask             cfgCapFileSystem | cfgCapDelay | cfgCapEvent
#define  Capabilities_SleepTask                  cfgCapDelay


/* ========================================================================= */
/* STACK SIZES ============================================================= */
/* ========================================================================= */

#if (defSysOptimized == cfgTrue)

#define  StackSafety                             0
#define  StackSizeOS                             20
#define  StackSizeISR                            0
#define  StackSizeShared                         0
#define  StackSize_Worker0Task                   80
#define  StackSize_Worker1Task                   80
#define  StackSize_Worker2Task                   80
#define  StackSize_SupervisorTask                80
#define  StackSize_SleepTask                     80

#else

#define  StackSafety                             0
#define  StackSizeOS                             20
#define  StackSizeISR                            0
#define  StackSizeShared                         0
#define  StackSize_Worker0Task                   110
#define  StackSize_Worker1Task                   110
#define  StackSize_Worker2Task                   110
#define  StackSize_SupervisorTask                110
#define  StackSize_SleepTask                     110

#endif


/* ========================================================================= */
/* TIMES SLICES ============================================================ */
/* ========================================================================= */

#define  TimeSliceIdleTime                       cfgSysSubTicksPerFullTick


/* ========================================================================= */
/* RUNTIME TASK NAMES ====================================================== */
/* ========================================================================= */


/* ========================================================================= */
/* TASK PRIORITIES ========================================================= */
/* ========================================================================= */

#define  Priority_Worker0Task                    0
#define  Priority_Worker1Task                    0
#define  Priority_Worker2Task                    0
#define  Priority_SupervisorTask                 1
#define  Priority_SleepTask                      1


/* ========================================================================= */
/* REGISTER USE ============================================================ */
/* ========================================================================= */

#define  RegisterUse_Worker0Task                 registersAll
#define  RegisterUse_Worker1Task                 registersAll
#define  RegisterUse_Worker2Task                 registersAll
#define  RegisterUse_SupervisorTask              registersAll
#define  RegisterUse_SleepTask                   registersAll


/* ========================================================================= */
/* REGISTER CHECK ========================================================== */
/* ========================================================================= */

#define  RegisterCheck_Worker0Task               registersAll
#define  RegisterCheck_Worker1Task               registersAll
#define  RegisterCheck_Worker2Task               registersAll
#define  RegisterCheck_SupervisorTask            registersAll
#define  RegisterCheck_SleepTask                 registersAll


/* ========================================================================= */
/* INTERRUPT SETTING ======================================================= */
/* ========================================================================= */

#define  InterruptStartOverride                  cfgGlobSet | cfgTickSet


/* ========================================================================= */
/* EVENT NAMES ============================================================= */
/* ========================================================================= */

#define  EN_00                                   ProceedTo1
#define  EN_01                                   ProceedTo2
#define  EN_02                                   ProceedTo3
#define  EN_03                                   ProceedTo4
#define  EN_04                                   ProceedTo5


/* ========================================================================= */
/* SLOT NAMES ============================================================== */
/* ========================================================================= */


/* ========================================================================= */
/* SLOT SIZES ============================================================== */
/* ========================================================================= */


/* ========================================================================= */
/* SLOT USAGE ============================================================== */
/* ========================================================================= */


/* ========================================================================= */
/* QUEU SIZES ============================================================== */
/* ========================================================================= */


/* ========================================================================= */
/* FILE NAMES ============================================================== */
/* ========================================================================= */

#define  FN_00                                   LayerInfo
#define  FN_01                                   Status

/* ========================================================================= */
/* FILE SIZES ============================================================== */
/* ========================================================================= */

#define  FileSpaceStandard                       8
#define  FileSpace_LayerInfo                     6
#define  FileSpace_Status                        4

#endif /*CONFIG_TESTFLASHNLEDS_H_*/
