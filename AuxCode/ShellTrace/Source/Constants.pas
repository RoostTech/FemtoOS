//
// Femto OS v 0.92 - Copyright (C) 2008-2010  Ruud Vlaming
//
// This file is part of the Femto OS distribution.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3 of the License.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Please note that, due to the GPLv3 license, for application of this
// work and/or combined work in embedded systems special obligations apply.
// If these are not to you liking, please know the Femto OS is dual
// licensed. A commercial license and support are available.
// See http://www.femtoos.org/ for details.
//

unit Constants;

interface

const defBaseStopStateGetMask        : integer = $80;
const defBaseModeGetMask             : integer = $40;
const defBaseBlockStateGetMask       : integer = $20;
const defBaseDelayStateGetMask       : integer = $10;
const defBasePrioGetMask             : integer = $0E;
const defBaseDressGetMask            : integer = $01;
const defBaseSuspendedGetMask        : integer = $E0;
const defBaseTerminatedGetMask       : integer = $F0;
const defBaseSleepingGetMask         : integer = $C0;
const defBaseRunningGetMask          : integer = $F0;
const defBaseNoBlocksGetMask         : integer = $E0;
const defBaseSyncBlockedGetMask      : integer = $E0;
const defBaseFileBlockedGetMask      : integer = $E0;
const defBaseSharedGetMask           : integer = $E0;
const defBaseRunOrSharedGetMask      : integer = $A0;

const defBaseStopStateGo             : integer = $80;
const defBaseStopStateHalt           : integer = $00;
const defBaseModeSuspend             : integer = $00;
const defBaseModeSleep               : integer = $40;
const defBaseModeSync                : integer = $40;
const defBaseModeAccess              : integer = $00;
const defBaseBlockStateFree          : integer = $20;
const defBaseBlockStateBlocked       : integer = $00;
const defBaseDelayStateWake          : integer = $10;
const defBaseDelayStateDelayed       : integer = $00;
const defBaseDressRunable            : integer = $01;
const defBaseDressDone               : integer = $00;
const defBaseDressSlot               : integer = $01;
const defBaseDressEvent              : integer = $00;
const defBaseDressRead               : integer = $01;
const defBaseDressWrite              : integer = $00;

const defBaseRunningTask             : integer = $F0;
const defBaseNoBlocksTask            : integer = $E0;
const defBaseSyncBlockedTask         : integer = $C0;
const defBaseFileBlockedTask         : integer = $80;
const defBaseSleepingTask            : integer = $40;
const defBaseSuspendedTask           : integer = $20;
const defBaseTerminatedTask          : integer = $10;
const defBasePrioShift               : Integer = 1;

const defFsReadGetMask               : integer = $80;
const defFsWriteGetMask              : integer = $40;
const defFsReadActive                : integer = $80;
const defFsReadClear                 : integer = $00;
const defFsWriteActive               : integer = $40;
const defFsWriteClear                : integer = $00;

const defFsReadBlockGetMask          : integer = $80;
const defFsWriteBlockGetMask         : integer = $40;
const defFsSleepRequestGetMask       : integer = $20;
const defFsBurnBlockGetMask          : integer = $10;
const defFsWriteNumberGetMask        : integer = $0F;
const defFsReadCountGetMask          : integer = $0F;
const defFsReadBlockActive           : integer = $80;
const defFsReadBlockReleaseRequest   : integer = $80;
const defFsWriteBlockActive          : integer = $40;
const defFsSleepRequestActive        : integer = $20;
const defFsBurnBlockActive           : integer = $10;
const defFsReadBlockClear            : integer = $00;
const defFsWriteBlockClear           : integer = $00;
const defFsSleepRequestClear         : integer = $00;
const defFsBurnBlockClear            : integer = $00;

const defDogGetMask                  : integer = $0C;
const defRetGetMask                  : integer = $03;
const defDogDead                     : integer = $00;
const defDogBark                     : integer = $04;
const defDogWake                     : integer = $08;
const defDogSleep                    : integer = $0C;
const defSlotRightGetMask            : integer = $0F;
const defSlotLeftGetMask             : integer = $F0;
const defSlotRightShift              : integer = 0;
const defSlotLeftShift               : integer = 4;

const defNearWakePresentGetMask      : integer = $20;
const defShareStateGetMask           : integer = $10;
const defNearWakeStatePresent        : integer = $20;
const defNearWakeStateAbsent         : integer = $00;
const defShareStateRunning           : integer = $10;
const defShareStateAbsent            : integer = $00;
const defTaskNumberGetMask           : integer = $0F;
const defTaskNumberShift             : integer = 0;

const defResponseOK                  : Integer = $01;  // datalength: 0
const defResponseUnknownCommand      : Integer = $02;  // datalength: 0
const defResponseError               : Integer = $03;  // datalength: 0
const defResponseInvalidTask         : Integer = $04;  // datalength: 0
const defResponseInvalidPriority     : Integer = $05;  // datalength: 0

const defResponseFemtoOs             : Integer = $10;  // datalength: 12
const defResponseLogTask             : Integer = $11;
const defResponseLogOs               : Integer = $12;
const defResponseTickCount           : Integer = $13;  // datalength: 2
const defResponseDump                : Integer = $14;  // datalength: 2
const defResponseUptime              : Integer = $15;  // datalength: 4
const defResponseFile                : Integer = $16;  // datalength: x
const defResponseInvalidFileNumber   : Integer = $17;  // datalength: 0

const defDumpRAM                     : integer = $01;
const defDumpEEPROM                  : integer = $02;
const defDumpFLASH                   : integer = $03;

const defLengthOK                    : Integer = 1;
const defLengthUnknownCommand        : Integer = 1;
const defLengthError                 : Integer = 1;      // datalength: 0
const defLengthInvalidTask           : Integer = 1;      // datalength: 0
const defLengthInvalidPriority       : Integer = 1;      // datalength: 0
const defLengthInvalidFileNumber     : Integer = 1;      // datalength: 0
const defLengthFemtoOs               : Integer = 13;     // datalength: 12
const defLengthLogTask               : Integer = 23;
const defLengthLogOs                 : Integer = 12;
const defLengthTickCount             : Integer = 3;      // datalength: 2
const defLengthUptime                : Integer = 6;      // datalength: 5
const defLengthDump                  : Integer = 19;     // datalength: 2
const defLengthFile                  : Integer = 2;      // datalength: 2

const defRequestFemtoOs              : Integer = $90;  // datalength: 0
const defRequestProcessList          : Integer = $91;  // datalength: 0
const defRequestTickCount            : Integer = $93;  // datalength: 0
const defRequestReboot               : Integer = $94;  // datalength: 0
const defRequestSuspend              : Integer = $95;  // datalength: 1
const defRequestResume               : Integer = $96;  // datalength: 1
const defRequestTerminate            : Integer = $97;  // datalength: 1
const defRequestPriority             : Integer = $98;  // datalength: 2
const defRequestTaskRecreate         : Integer = $99;  // datalength: 1
const defRequestDump                 : Integer = $9A;  // datalength: 3
const defRequestStore                : Integer = $9B;  // datalength: 3
const defRequestRecall               : Integer = $9C;  // datalength: 3
const defRequestUptime               : Integer = $9D;  // datalength: 0
const defRequestTest                 : Integer = $9E;  // datalength: 1  


const defDemoRequestLedState         : Integer = $20;
const defDemoRequestLedCycle         : Integer = $21;
const defDemoRequestLedSave          : Integer = $22;
const defDemoRequestLedLoad          : Integer = $23;
const defDemoRequestLedStateOff      : Integer = $00;
const defDemoRequestLedStateOn       : Integer = $01;
const defDemoRequestLedStateFlash    : Integer = $02;
const defDemoRequestLedStateFreeze   : Integer = $04;
const defDemoRequestLedStateFollow   : Integer = $05;
const defDemoRequestLedStateUndef    : Integer = $FF;
const defDemoResponseLedOK           : Integer = $A0;
const defDemoResponseLedError        : Integer = $A1;

// 'LOOP_MARKER 0x0F' is used internally in trace program as marker for multibyte messages
const eventArray: array[0..255] of String = (
{ 0x00 }  'Null',
{ 0x01 }  'MARKER',
{ 0x02 }  'UserByteMessage',
{ 0x03 }  'UserWordMessage',
{ 0x04 }  'Undefined 0x04',
{ 0x05 }  'Undefined 0x05',
{ 0x06 }  'Undefined 0x06',
{ 0x07 }  'Undefined 0x07',
{ 0x08 }  'Undefined 0x08',
{ 0x09 }  'Undefined 0x09',
{ 0x0A }  'Undefined 0x0A',
{ 0x0B }  'Undefined 0x0B',
{ 0x0C }  'Undefined 0x0C',
{ 0x0D }  'Undefined 0x0D',
{ 0x0E }  'Undefined 0x0E',
{ 0x0F }  'LOOP_MARKER 0x0F',
{ 0x10 }  'TaskStart 0',
{ 0x11 }  'TaskStart 1',
{ 0x12 }  'TaskStart 2',
{ 0x13 }  'TaskStart 3',
{ 0x14 }  'TaskStart 4',
{ 0x15 }  'TaskStart 5',
{ 0x16 }  'TaskStart 6',
{ 0x17 }  'TaskStart 7',
{ 0x18 }  'TaskStart 8',
{ 0x19 }  'TaskStart 9',
{ 0x1A }  'TaskStart 10',
{ 0x1B }  'TaskStart 11',
{ 0x1C }  'TaskStart 12',
{ 0x1D }  'TaskStart 13',
{ 0x1E }  'TaskStart 14',
{ 0x1F }  'TaskStart 15',
{ 0x20 }  'OsStart',
{ 0x21 }  'IdleStart',
{ 0x22 }  'SleepStart',
{ 0x23 }  'TickInterrupt',
{ 0x24 }  'Watchdog barks',
{ 0x25 }  'LockAquired',
{ 0x26 }  'LockRejected',
{ 0x27 }  'Reset',
{ 0x28 }  'ISR 0',
{ 0x29 }  'ISR 1',
{ 0x2A }  'ISR 2',
{ 0x2B }  'ISR 3',
{ 0x2C }  'ISR 4',
{ 0x2D }  'ISR 5',
{ 0x2E }  'ISR 6',
{ 0x2F }  'ISR 7',
{ 0x30 }  'SlotLock task 0 slots ',
{ 0x31 }  'SlotLock task 1 slots ',
{ 0x32 }  'SlotLock task 2 slots ',
{ 0x33 }  'SlotLock task 3 slots ',
{ 0x34 }  'SlotLock task 4 slots ',
{ 0x35 }  'SlotLock task 5 slots ',
{ 0x36 }  'SlotLock task 6 slots ',
{ 0x37 }  'SlotLock task 7 slots ',
{ 0x38 }  'SlotLock task 8 slots ',
{ 0x39 }  'SlotLock task 9 slots ',
{ 0x3A }  'SlotLock task 10 slots ',
{ 0x3B }  'SlotLock task 11 slots ',
{ 0x3C }  'SlotLock task 12 slots ',
{ 0x3D }  'SlotLock task 13 slots ',
{ 0x3E }  'SlotLock task 14 slots ',
{ 0x3F }  'SlotLock task 15 slots ',
{ 0x40 }  'SlotUnLock task 0 slots  ',
{ 0x41 }  'SlotUnLock task 1 slots  ',
{ 0x42 }  'SlotUnLock task 2 slots  ',
{ 0x43 }  'SlotUnLock task 3 slots  ',
{ 0x44 }  'SlotUnLock task 4 slots  ',
{ 0x45 }  'SlotUnLock task 5 slots  ',
{ 0x46 }  'SlotUnLock task 6 slots  ',
{ 0x47 }  'SlotUnLock task 7 slots  ',
{ 0x48 }  'SlotUnLock task 8 slots  ',
{ 0x49 }  'SlotUnLock task 9 slots  ',
{ 0x4A }  'SlotUnLock task 10 slots  ',
{ 0x4B }  'SlotUnLock task 11 slots  ',
{ 0x4C }  'SlotUnLock task 12 slots  ',
{ 0x4D }  'SlotUnLock task 13 slots  ',
{ 0x4E }  'SlotUnLock task 14 slots  ',
{ 0x4F }  'SlotUnLock task 15 slots  ',
{ 0x50 }  'FireEvent 0',
{ 0x51 }  'FireEvent 1',
{ 0x52 }  'FireEvent 2',
{ 0x53 }  'FireEvent 3',
{ 0x54 }  'FireEvent 4',
{ 0x55 }  'FireEvent 5',
{ 0x56 }  'FireEvent 6',
{ 0x57 }  'FireEvent 7',
{ 0x58 }  'Watermarks (bytes, regmask)',
{ 0x59 }  'Undefined 0x59',
{ 0x5A }  'REGISTERLEAK_5A',
{ 0x5B }  'BurnLock',
{ 0x5C }  'BurnFree',
{ 0x5D }  'CreateContext',
{ 0x5E }  'LoadInfo (subticks, fraction)',
{ 0x5F }  'OsTime (now,ave)',
{ 0x60 }  'TaskInit 0',
{ 0x61 }  'TaskInit 1',
{ 0x62 }  'TaskInit 2',
{ 0x63 }  'TaskInit 3',
{ 0x64 }  'TaskInit 4',
{ 0x65 }  'TaskInit 5',
{ 0x66 }  'TaskInit 6',
{ 0x67 }  'TaskInit 7',
{ 0x68 }  'TaskInit 8',
{ 0x69 }  'TaskInit 9',
{ 0x6A }  'TaskInit 10',
{ 0x6B }  'TaskInit 11',
{ 0x6C }  'TaskInit 12',
{ 0x6D }  'TaskInit 13',
{ 0x6E }  'TaskInit 14',
{ 0x6F }  'TaskInit 15',
{ 0x70 }  'TaskRelease 0',
{ 0x71 }  'TaskRelease 1',
{ 0x72 }  'TaskRelease 2',
{ 0x73 }  'TaskRelease 3',
{ 0x74 }  'TaskRelease 4',
{ 0x75 }  'TaskRelease 5',
{ 0x76 }  'TaskRelease 6',
{ 0x77 }  'TaskRelease 7',
{ 0x78 }  'TaskRelease 8',
{ 0x79 }  'TaskRelease 9',
{ 0x7A }  'TaskRelease 10',
{ 0x7B }  'TaskRelease 11',
{ 0x7C }  'TaskRelease 12',
{ 0x7D }  'TaskRelease 13',
{ 0x7E }  'TaskRelease 14',
{ 0x7F }  'TaskRelease 15',
{ 0x80 }  'APIcallSystem',
{ 0x81 }  'APIcallTaskYield',
{ 0x82 }  'APIcallTaskWaitForEvents',
{ 0x83 }  'APIcallTaskDelayFromNow',
{ 0x84 }  'APIcallTaskDelayFromWake',
{ 0x85 }  'APIcallTaskSuspend',
{ 0x86 }  'APIcallTaskSleep',
{ 0x87 }  'APIcallTaskSleepAll',
{ 0x88 }  'APIcallTaskRecreate',
{ 0x89 }  'APIcallTaskFeedWatchdog',
{ 0x8A }  'APIcallTaskKillWatchdog',
{ 0x8B }  'APIcallTaskRestart',
{ 0x8C }  'APIcallTaskTerminate',
{ 0x8D }  'APIcallTaskEnableGlobalInterrupts',
{ 0x8E }  'APIcallTaskDisableGlobalInterrupts',
{ 0x8F }  'APIcallTaskEnableTickInterrupts',
{ 0x90 }  'APIcallTaskDisableTickInterrupts',
{ 0x91 }  'APIcallTaskEnableSwitchTask',
{ 0x92 }  'APIcallTaskDisableSwitchTask',
{ 0x93 }  'APIcallTaskEnterGlobalCritical',
{ 0x94 }  'APIcallTaskExitGlobalCritical',
{ 0x95 }  'APIcallTaskEnterTickCritical',
{ 0x96 }  'APIcallTaskExitTickCritical',
{ 0x97 }  'APIcallTaskEnterSwitchCritical',
{ 0x98 }  'APIcallTaskExitSwitchCritical',
{ 0x99 }  'APIcallTaskFileOpen',
{ 0x9A }  'APIcallTaskFileClose',
{ 0x9B }  'APIcallTaskFileFormat',
{ 0x9C }  'APIcallTaskFileGetSize',
{ 0x9D }  'APIcallTaskFileSetSize',
{ 0x9E }  'APIcallTaskFileReadByte',
{ 0x9F }  'APIcallTaskFileWriteByte',
{ 0xA0 }  'APIcallTaskFileAppendByte',
{ 0xA1 }  'APIcallTaskFileReadPipe',
{ 0xA2 }  'APIcallTaskFileWritePipe',
{ 0xA3 }  'APIcallTaskFileReadBuffer',
{ 0xA4 }  'APIcallTaskFileWriteBuffer',
{ 0xA5 }  'APIcallREGISTERLEAK_A5',
{ 0xA6 }  'APIcallTaskWaitForTasks',
{ 0xA7 }  'APIcallTaskSyncRequest',
{ 0xA8 }  'APIcallTaskSyncRelease',
{ 0xA9 }  'APIcallTaskMemMalloc',
{ 0xAA }  'APIcallTaskMemFree',
{ 0xAB }  'APIcallTaskMemDefrag',
{ 0xAC }  'APIcallTaskMemPointer',
{ 0xAD }  'APIcallTaskReserved1 (0xAD)',
{ 0xAE }  'APIcallTaskReserved2 (0xAE)',
{ 0xAF }  'APIcallTaskReserved3 (0xAF)',
{ 0xB0 }  'APIcallTaskReserved4 (0xB0)',
{ 0xB1 }  'APIcallTaskReserved5 (0xB1)',
{ 0xB2 }  'APIcallTaskReserved6 (0xB2)',
{ 0xB3 }  'APIcallGenSuspend',
{ 0xB4 }  'APIcallGenResume',
{ 0xB5 }  'APIcallGenSetPriority',
{ 0xB6 }  'APIcallGenGetPriority',
{ 0xB7 }  'APIcallGenGetTickCount',
{ 0xB8 }  'APIcallGenGetLastWakeTime',
{ 0xB9 }  'APIcallGenGetTaskname',
{ 0xBA }  'APIcallGenFireEventSet',
{ 0xBB }  'APIcallGenReboot',
{ 0xBC }  'APIcallGenLogTask',
{ 0xBD }  'APIcallGenLogOs',
{ 0xBE }  'APIcallGenWaitRelease',
{ 0xBF }  'APIcallGenQueuWrite',
{ 0xC0 }  'APIcallGenQueuRead',
{ 0xC1 }  'APIcallGenQueuPeek',
{ 0xC2 }  'APIcallGenQueuReadable',
{ 0xC3 }  'APIcallGenQueuWriteable',
{ 0xC4 }  'APIcallGenQueuFull',
{ 0xC5 }  'APIcallGenQueuEmpty',
{ 0xC6 }  'APIcallGenQueuClear',
{ 0xC7 }  'APIcallGenAddtoTickCount',
{ 0xC8 }  'APIcallGenPassFlashString',
{ 0xC9 }  'APIcallGenCountEventBlocks',
{ 0xCA }  'APIcallGenQueuUnwrite',
{ 0xCB }  'APIcallGenQueuUnread',
{ 0xCC }  'APIcallGenReserved1 (0xCC)',
{ 0xCD }  'APIcallGenReserved2 (0xCD)',
{ 0xCE }  'APIcallGenReserved3 (0xCE)',
{ 0xCF }  'APIcallGenReserved4 (0xCF)',
{ 0xD0 }  'ERRUndefined (0xC0)',
{ 0xD1 }  'ERRInsufficientCapabilities',
{ 0xD2 }  'ERRUndefined (0xD2)',
{ 0xD3 }  'ERRTaskStackWillOverflow',
{ 0xD4 }  'ERRTaskIllegalRegisterUse',
{ 0xD5 }  'ERRTaskTakesTooLong',
{ 0xD6 }  'ERRTaskNestingOverflowed',
{ 0xD7 }  'ERRTaskNestingUnderflowed',
{ 0xD8 }  'ERRTaskNestingPresent',
{ 0xD9 }  'ERRUndefined (0xC9)',
{ 0xDA }  'ERRTaskHoldsNoSlots',
{ 0xDB }  'ERRSlotDoubleUsed',
{ 0xDC }  'ERRQueuOverrun',
{ 0xDD }  'ERRQueuUnderrun',
{ 0xDE }  'ERRTaskPriorityTooHigh',
{ 0xDF }  'ERRTaskDelayTooLong',
{ 0xE0 }  'ERRTaskDelayTooShort',
{ 0xE1 }  'ERRSlotZeroUsed',
{ 0xE2 }  'ERRSlotTypeMismatch',
{ 0xE3 }  'ERRSlotTwins',
{ 0xE4 }  'ERRIllegalDominantState',
{ 0xE5 }  'ERRQueuWriteLimit',
{ 0xE6 }  'ERRQueuReadLimit',
{ 0xE7 }  'ERRSlotDecreaseFail',
{ 0xE8 }  'ERRSlotIncreaseFail',
{ 0xE9 }  'ERRFileOpenMode',
{ 0xEA }  'ERRFileInvalidFileNumber',
{ 0xEB }  'ERRFileOutOfRange',
{ 0xEC }  'ERRFileClosedMode',
{ 0xED }  'ERRFileWrongMode',
{ 0xEE }  'ERRInvalidRestartMode',
{ 0xEF }  'ERRInvalidSuspendMode',
{ 0xF0 }  'FATInternalError',
{ 0xF1 }  'FATOsStackUnderMinimum',
{ 0xF2 }  'FATOsStackOverflowed',
{ 0xF3 }  'FATIllegalEvent',
{ 0xF4 }  'FATTaskStackOverflowed',
{ 0xF5 }  'FATIsrStackOverflowed',
{ 0xF6 }  'FATOsTickRateTooHigh',
{ 0xF7 }  'FATTaskSubtickOverflow',
{ 0xF8 }  'FATTaskIllegalTaskNumber',
{ 0xF9 }  'FATUndefined (0xF9)',
{ 0xFA }  'FATIllegalCallfromISR',
{ 0xFB }  'FATUndefined (0xFB)',
{ 0xFC }  'FATUndefined (0xFC)',
{ 0xFD }  'FATUndefined (0xFD)',
{ 0xFE }  'FATUndefined (0xFE)',
{ 0xFF }  'FATUndefined (0xFF)');


implementation

end.

