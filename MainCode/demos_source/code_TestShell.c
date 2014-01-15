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
 *  This file is solely for demonstration purposes.
 *
 *  This example is made to demonstrate what all is possible with a device as
 *  small as the ATtiny861. It runs eight preemptive led blinkers that can be
 *  set to different states and blinker frequencies independently. There is one
 *  task running a 4 wire bus protocol (full handshake, variable speed, interruptible).
 *  The last task is a shell task through which you can talk to the device. Of
 *  course a terminal application is needed which generates the right commands
 *  and which understands the communication protocol. This application (on windows)
 *  is included. Besides controlling the activity of the leds, it also is possible to
 *  suspend and resume the task. Change priority of tasks, restart crashed tasks,
 *  reboot the system etc etc. Type 'help' to see all possibilities.
 *
 *  Extra hardware and external software is needed to run this example.
 *
 *  NOTE: This demo is not yet finished, and must still be virtualized to
 *  work on other hardware, and adapted so it can work with general
 *  terminals.
 */


/* This this the only include needed in your code .*/
#include "femtoos_code.h"

#define defDemoRequestLedState           0x20
#define defDemoRequestLedCycle           0x21
#define defDemoRequestLedSave            0x22
#define defDemoRequestLedLoad            0x23
#define defDemoRequestLedStateOff        0x00
#define defDemoRequestLedStateOn         0x01
#define defDemoRequestLedStateFlash      0x02
#define defDemoRequestLedStateFreeze     0x04
#define defDemoRequestLedStateFollow     0x05
#define defDemoRequestLedStateUndef      0xFF
#define defDemoResponseLedOK             0xA0
#define defDemoResponseLedError          0xA1

static void initBus(void);
static void startCommunication(void);

typedef Tuint08 bit;

/* You get a warning here that crcValue is not used. This is intentional. I have
 * not yet decided if i want to implement that functionality and how. Until that
 * moment has come, i leave the warning as a reminder.
 * Probably i will rewrite the whole implementation of the T4 protocol
 */
static Tbyte crcValue;
static Tbool virgin;
static Tbool prevMaster;
static Tbool crcCheckResult;
static Tuint08 uptime[3];

#define Maxtry 9

#define SETBIT(Reg,Pos,val) if (val) { (Reg|=(1<<Pos)); } else { (Reg&=~(1<<Pos)); }
#define GETBIT(Reg,Pos)     ((Reg>>Pos) & 0x01)

#define SetDebugLed(nr) SETBIT(PORTB,(nr+4),false);
#define ClrDebugLed(nr) SETBIT(PORTB,(nr+4),true);

/*  These methods must be ported */

static bit getSCLin()         __attribute__ ( ( always_inline ) );
static bit getSDA()           __attribute__ ( ( always_inline ) );
static bit getACK()           __attribute__ ( ( always_inline ) );
static void setSCLout(bit b)  __attribute__ ( ( always_inline ) );
static void setSDA(bit b)     __attribute__ ( ( always_inline ) );
static void setACK(bit b)     __attribute__ ( ( always_inline ) );


static bit getSCLin()        { return GETBIT(PINB,PB2); }
static bit getSDA()          { return GETBIT(PINB,PB3); }
static bit getACK()          { return GETBIT(PINB,PB3); }

static void setSCLout(bit b) { SETBIT(PORTB,PB0,b); }
static void setSDA(bit b)    { SETBIT(PORTB,PB1,b); }
static void setACK(bit b)    { SETBIT(PORTB,PB1,b); }


static void propDelay() { asm("nop"); asm("nop"); }

static void calcCRC(Tbyte b)    {}
static void clearCRC()          {}
static Tbyte getCRC()           { return 0; }
static Tbool checkCRC(Tbyte b)  { return true; }

/*
 * SCLout=output   : PB0
 * SDAout=output   : PB1
 * SCLin=input     : PB2
 * SDAin=input     : PB3
 */

static void initPins()
{ /* Switch off the pull up resistors on inputs, write 0 to output SCLout */
  PORTB &= 0xF0;    /* When GCC 4.3.0 is out change to 0b11110000 */
  /* set bit 0,1 to output, bit 2,3 to input, leave first 4 bits alone (PB7-PB4) */
  DDRB = (DDRB & 0xF0) | 0x03; }

/*  These methods are chip independent */

static void writeByte(Tbyte b)
{ Tuint08 bitCnt = 8;
  while (bitCnt--)
  { setSDA(b & 0x80);
    while(getACK());
    setSCLout(1);
    while(!getACK());
    b<<=1;
    setSCLout(0);} }

static Tbyte readByte()
{ Tbyte result = 0;
  Tuint08 bitCnt = 8;
  while (bitCnt--)
  { while(getSCLin());
    setACK(0);
    while(!getSCLin());
    result<<=1;
    result|=getSDA();
    setACK(1); }
  return result; }

static void startRead()
{ clearCRC();
  setACK(1);
  Tbyte payloadLength = readByte()-2;
  if (payloadLength>QueuSize_ReadQueuT4) { payloadLength=QueuSize_ReadQueuT4; }
  taskQueuWriteRequestOnName(ReadQueuT4,payloadLength);
  while (payloadLength--)
  { Tbyte byte = readByte();
    genQueuWriteOnName(ReadQueuT4,byte);
    calcCRC(byte);
    }
  taskQueuReleaseOnName(ReadQueuT4);
  /* This result is not used yet */
  crcCheckResult = checkCRC(readByte());
  while(getSCLin());
  setACK(0);
  virgin = false;
  prevMaster = true; }

static void startWrite()
{ clearCRC();
  setSCLout(0);
  taskQueuReadRequestOnName(WriteQueuT4,1);
  Tbyte payloadLength = genQueuReadableOnName(WriteQueuT4);
  writeByte(payloadLength+2);
  while (payloadLength--)
  { Tbyte byte = genQueuReadOnName(WriteQueuT4);
    writeByte(byte);
    calcCRC(byte);
    }
  taskQueuReleaseOnName(WriteQueuT4);
  writeByte(getCRC());
  setSDA(0);
  while (getACK());
  virgin = false;
  prevMaster = false; }

static void initBus(void)
{ initPins();
  virgin=true;
  prevMaster=false; }

static void startCommunication()
{ while (true)
  { if (!genQueuEmptyOnName(WriteQueuT4))
    { setSCLout(1);
      while (true)
      { if (getACK())
        { startWrite();
          break; }
        if (!prevMaster && getSCLin())
        { setSCLout(0);
          propDelay();
          Tuint08 cnt = 0;
          while (!virgin | (cnt++ < Maxtry))
          { if (getSCLin())
            { startRead();
              break; } }
          break; } } }
    else
    { if (!getSCLin()) break;
      if (!genQueuEmptyOnName(ReadQueuT4)) break;
      startRead(); } } }


static void WriteQueuPipe(Tchar c) { genQueuWriteOnName(WriteQueuT4,c); }
static Tchar ReadQueuPipe()        { return genQueuReadOnName(ReadQueuT4); }

const Tchar FemtoOSid[] PROGMEM = SystemID;

static void SendID()
{ taskQueuWriteRequestOnName(WriteQueuT4,13);
  genQueuWriteOnName(WriteQueuT4,defResponseFemtoOs);
  genPassFlashString((Taddress) FemtoOSid,0,' ', WriteQueuPipe);
  taskQueuReleaseOnName(WriteQueuT4); }

static void SendTickCount()
{ taskQueuWriteRequestOnName(WriteQueuT4,3);
  genQueuWriteOnName(WriteQueuT4,defResponseTickCount);
  genPipeInt16(genGetTickCount(),WriteQueuPipe);
  taskQueuReleaseOnName(WriteQueuT4); }

static void SendUptime()
{ taskQueuWriteRequestOnName(WriteQueuT4,6);
  genQueuWriteOnName(WriteQueuT4,defResponseUptime);
  genQueuWriteOnName(WriteQueuT4,uptime[2]);
  genQueuWriteOnName(WriteQueuT4,uptime[1]);
  genQueuWriteOnName(WriteQueuT4,uptime[0]);
  genPipeInt16(genGetTickCount(),WriteQueuPipe);
  taskQueuReleaseOnName(WriteQueuT4); }

static void SendProcessList()
{ taskQueuWriteRequestOnName(WriteQueuT4,11);
  genLogOs(WriteQueuPipe);
  taskQueuReleaseOnName(WriteQueuT4);
  Tuint08 uiTaskNumber;
  for (uiTaskNumber=0; uiTaskNumber<defNumberOfTasks; uiTaskNumber++)
  { taskQueuWriteRequestOnName(WriteQueuT4,22);
    genLogTask(uiTaskNumber,WriteQueuPipe);
    taskQueuReleaseOnName(WriteQueuT4); } }

static void SendSingleResponse(Tuint08 uiResponse)
{ taskQueuWriteRequestOnName(WriteQueuT4,1);
  genQueuWriteOnName(WriteQueuT4,uiResponse);
  taskQueuReleaseOnName(WriteQueuT4); }

static Tuint08 getSingleValue()
{ taskQueuReadRequestOnName(ReadQueuT4,1);
  Tuint08 Result = genQueuReadOnName(ReadQueuT4);
  taskQueuReleaseOnName(ReadQueuT4);
  return Result; }

static void HandleReboot()
{ SendSingleResponse(defResponseOK);
  taskDelayFromNow(200);
  genReboot(); }

static void HandleRecreate()
{ Tuint08 uiTaskNumber = getSingleValue();
  if (uiTaskNumber<defNumberOfTasks)
  { SendSingleResponse(defResponseOK);
    taskDelayFromNow(200);
    taskRecreate(uiTaskNumber); }
  else
  { SendSingleResponse(defResponseInvalidTask); } }

static void HandleCommand(void (*pCommand)(Tuint08 uiTN))
{ Tuint08 uiTaskNumber = getSingleValue();
  if (uiTaskNumber<defNumberOfTasks)
  { pCommand(uiTaskNumber);
    SendSingleResponse(defResponseOK); }
  else
  { SendSingleResponse(defResponseInvalidTask); } }

static void HandlePriority()
{ Tuint08 uiTaskNumber = getSingleValue();
  Tuint08 uiNewPrio = getSingleValue();
  if (uiTaskNumber>=defNumberOfTasks) { SendSingleResponse(defResponseInvalidTask); }
  else if (uiNewPrio>7) { SendSingleResponse(defResponseInvalidPriority); }
  else
  { genSetPriority(uiTaskNumber,uiNewPrio);
    SendSingleResponse(defResponseOK); } }


static void HandleDump()
{ taskQueuReadRequestOnName(ReadQueuT4,4);
  Tuint08 uiControl = genQueuReadOnName(ReadQueuT4);
  Tuint08 uiHighByte = genQueuReadOnName(ReadQueuT4);
  Tuint08 uiLowByte = genQueuReadOnName(ReadQueuT4);
  Tuint08 uiLength = genQueuReadOnName(ReadQueuT4);
  taskQueuReleaseOnName(ReadQueuT4);
  Taddress pStart = (Taddress) ((((Tuint16) uiHighByte) << 8) | (uiLowByte & 0xF0));
  /* blocks of 16 bytes */
  Tuint08 uiLengthBlocks = ((uiLength-1) >> 4);
  Tuint08 uiCount;
  if (uiControl == defDumpEEPROM) { taskFileOpen(); }
  do
  { taskQueuWriteRequestOnName(WriteQueuT4,19);
    genQueuWriteOnName(WriteQueuT4,defResponseDump);
    genQueuWriteOnName(WriteQueuT4,((Tuint08) (((Tuint16) pStart)>>8)));
    genQueuWriteOnName(WriteQueuT4,((Tuint08) ((Tuint16) (pStart))));
    for (uiCount=0; uiCount<16; uiCount++)
    { Tbyte bVal = 0;
      if (uiControl == defDumpRAM)
      { bVal = *(pStart); }
      else if (uiControl == defDumpEEPROM)
      { bVal = portFSReadByte(pStart); }
      else if (uiControl == defDumpFLASH)
      { bVal = pgm_read_byte(pStart);  }
      genQueuWriteOnName(WriteQueuT4,bVal);
      pStart++; }
    taskQueuReleaseOnName(WriteQueuT4); }
  while (uiLengthBlocks--);
  if (uiControl == defDumpEEPROM) { taskFileClose(); } }


#define BlockLength 16
static void HandleStore()
{ taskQueuReadRequestOnName(ReadQueuT4,2);
  Tuint08 uiFileNumber = genQueuReadOnName(ReadQueuT4);
  Tuint08 uiFileLength = genQueuReadOnName(ReadQueuT4);
  taskQueuReleaseOnName(ReadQueuT4);
  if (uiFileNumber>=defFsNumberOfAllFiles)
  { SendSingleResponse(defResponseInvalidFileNumber);
    /* TODO: must we flush here? */
    }
  else
  { /* blocks of 16 bytes */
    Tuint08 uiOffset = 0;
    Tuint08 uiReadLength;
    taskFileOpen();
    while (uiFileLength>0)
    { if (uiFileLength>BlockLength) { uiReadLength = BlockLength; } else { uiReadLength = uiFileLength; }
      taskQueuReadRequestOnName(ReadQueuT4,uiReadLength);
      taskFileWritePipe(uiFileNumber,uiOffset,uiReadLength,ReadQueuPipe);
      uiOffset += uiReadLength;
      uiFileLength -= uiReadLength;
      taskQueuReleaseOnName(ReadQueuT4); }
    taskFileClose();
    SendSingleResponse(defResponseOK); } }

static void HandleRecall()
{ Tuint08 uiFileNumber = getSingleValue();
  /* blocks of 16 bytes */
  taskFileOpen();
  Tuint08 uiFileLength = taskFileGetSize(uiFileNumber);
  if (uiFileNumber>=defFsNumberOfAllFiles)
  {  SendSingleResponse(defResponseInvalidFileNumber); }
  else
  { taskQueuWriteRequestOnName(WriteQueuT4,2);
    genQueuWriteOnName(WriteQueuT4,defResponseFile);
    genQueuWriteOnName(WriteQueuT4,uiFileLength);
    taskQueuReleaseOnName(WriteQueuT4);
    Tuint08 uiOffset = 0;
    Tuint08 uiWriteLength;
    while (uiFileLength>0)
    { if (uiFileLength>BlockLength) { uiWriteLength = BlockLength; } else { uiWriteLength = uiFileLength; }
      taskQueuWriteRequestOnName(WriteQueuT4,uiWriteLength);
      taskFileReadPipe(uiFileNumber,uiOffset,uiWriteLength,WriteQueuPipe);
      uiOffset += uiWriteLength;
      uiFileLength -= uiWriteLength;
      taskQueuReleaseOnName(WriteQueuT4); } }
  taskFileClose(); }


static void HandleTest()
{ SendSingleResponse(defResponseOK); }


static Tuint08 volatile uiLedState[8];
static Tuint08 volatile uiPeriodOff[8];
static Tuint08 volatile uiPeriodOn[8];

static void ExeLedState()
{ taskQueuReadRequestOnName(ReadQueuT4,2);
  Tuint08 uiNumber = genQueuReadOnName(ReadQueuT4);
  Tuint08 uiState = genQueuReadOnName(ReadQueuT4);
  taskQueuReleaseOnName(ReadQueuT4);
  Tuint08 Result;
  if ((uiNumber>8) || (uiState>defDemoRequestLedStateFollow))
  { Result = defDemoResponseLedError; }
  else
  { taskEnterGlobalCritical();
    if (uiNumber==8)
    { for (uiNumber=0; uiNumber<8; uiNumber++) { uiLedState[uiNumber] = uiState; } }
    else { uiLedState[uiNumber] = uiState; }
    Result = defDemoResponseLedOK; }
    taskExitGlobalCritical();
  SendSingleResponse(Result); }

static void ExeLedCycle()
{ taskQueuReadRequestOnName(ReadQueuT4,3);
  Tuint08 uiNumber = genQueuReadOnName(ReadQueuT4);
  Tuint08 uiOn = genQueuReadOnName(ReadQueuT4);
  Tuint08 uiOff = genQueuReadOnName(ReadQueuT4);
  taskQueuReleaseOnName(ReadQueuT4);
  Tuint08 Result;
  if (uiNumber>8)
  { Result = defDemoResponseLedError; }
  else
  { if (uiNumber==8)
    { for (uiNumber=0; uiNumber<8; uiNumber++)
      { uiPeriodOn[uiNumber] = uiOn;
        uiPeriodOff[uiNumber] = uiOff; } }
    else
    { uiPeriodOn[uiNumber] = uiOn;
      uiPeriodOff[uiNumber] = uiOff; }
    Result = defDemoResponseLedOK; }
  SendSingleResponse(Result); }

static void ExeLedSave()
{ Tuint08 uiFileNumber = getSingleValue();
  taskFileOpen();
  if (uiFileNumber>=defFsNumberOfAllFiles)
  {  SendSingleResponse(defResponseInvalidFileNumber); }
  else
  { taskFileWriteBuffer(uiFileNumber,0,8,(Taddress) uiLedState);
    taskFileWriteBuffer(uiFileNumber,8,8,(Taddress) uiPeriodOff);
    taskFileWriteBuffer(uiFileNumber,16,8,(Taddress) uiPeriodOn);
    SendSingleResponse(defResponseOK); }
  taskFileClose(); }


static void ExeLedLoad()
{ Tuint08 uiFileNumber = getSingleValue();
  taskFileOpen();
  if (uiFileNumber>=defFsNumberOfAllFiles)
  {  SendSingleResponse(defResponseInvalidFileNumber); }
  else
  { taskFileReadBuffer(uiFileNumber,0,8,(Taddress) uiLedState);
    taskFileReadBuffer(uiFileNumber,8,8, (Taddress) uiPeriodOff);
    taskFileReadBuffer(uiFileNumber,16,8,(Taddress)uiPeriodOn);
    SendSingleResponse(defResponseOK); }
  taskFileClose(); }


static void ExecuteShell()
{ Tuint08 uiCommand = getSingleValue();
  if      (uiCommand == defRequestFemtoOs)      SendID();
  else if (uiCommand == defRequestTickCount)    SendTickCount();
  else if (uiCommand == defRequestUptime)       SendUptime();
  else if (uiCommand == defRequestReboot)       HandleReboot();
  else if (uiCommand == defRequestProcessList)  SendProcessList();
  else if (uiCommand == defRequestSuspend)      HandleCommand(genSuspend);
  else if (uiCommand == defRequestResume)       HandleCommand(genResume);
  else if (uiCommand == defRequestTerminate)    HandleCommand(taskTerminate);
  else if (uiCommand == defRequestRecreate)     HandleRecreate();
  else if (uiCommand == defRequestPriority)     HandlePriority();
  else if (uiCommand == defRequestDump)         HandleDump();
  else if (uiCommand == defRequestStore)        HandleStore();
  else if (uiCommand == defRequestRecall)       HandleRecall();
  else if (uiCommand == defRequestTest)         HandleTest();
  else if (uiCommand == defDemoRequestLedState) ExeLedState();
  else if (uiCommand == defDemoRequestLedCycle) ExeLedCycle();
  else if (uiCommand == defDemoRequestLedSave)  ExeLedSave();
  else if (uiCommand == defDemoRequestLedLoad)  ExeLedLoad();
  else SendSingleResponse(defResponseUnknownCommand);
  }

static void clearQueus()
{ taskQueuRequestOnName(WriteQueuT4);
  genQueuClearOnName(WriteQueuT4);
  taskQueuReleaseOnName(WriteQueuT4);
  taskQueuRequestOnName(ReadQueuT4);
  genQueuClearOnName(ReadQueuT4);
  taskQueuReleaseOnName(ReadQueuT4); }

/* This is called once at system boot, and before the creating of any of
 * the tasks. Use it to initialize the hardware. */
void appBoot(void)
{ DDRA  = 0xFF;
  PORTA = 0xFF;
  #if (cfgCheckTrace == cfgFalse)
    DDRB  = 0x30;   /* debug leds 0 and 1 */
    PORTB = 0x30;
  #endif
  GIMSK = 0x20;   /* set PCIE0 bit (enable interrupts on ports 8..11  */
  PCMSK0 = 0x00;  /* only allow for an interrupt on port PB6.            */
  PCMSK1 = 0x40;  /* only allow for an interrupt on port PB6.            */
  Tuint08 i;
  for (i=0; i<8; i++)
  { uiLedState[i]  = defDemoRequestLedStateFlash;
    uiPeriodOff[i] = 8;
    uiPeriodOn[i]  = 8; } }


#if (preTaskDefined(T4Bus))

void appLoop_T4Bus(void)
{ clearQueus();
  initBus();
  while (true)
  {
    #if (cfgUseTaskWatchdog == cfgTrue)
      taskFeedWatchdog();
    #endif
    startCommunication();
    taskDelayFromNow(50);   } }

#endif


#if (preTaskDefined(Shell))

void appLoop_Shell(void)
{ clearQueus();
  while (true)
  { ExecuteShell();
    taskDelayFromNow(50);   } }

#endif

/* 40 bits uptime counter */
void appTick16(void)
{ if (++uptime[0] == 0)
  {  if (++uptime[1] == 0)
     { uptime[2]++; } } }

/* This does only compile to an atomic instruction for fixed lednr! */

#define ledOff(bits)  { PORTA |= (bits); }
#define ledOn(bits)   { PORTA &=  ~(bits); }
#define ledInv(bits)  { PINA = (bits); }
#define getLed(bits)  (PORTA & (bits))


static void wait(Tuint08 uiLed) __attribute__((noreturn));
static void wait(Tuint08 uiLed)
{ Tuint08 uiPerOff = uiPeriodOff[uiLed];
  Tuint08 uiPerOn = uiPeriodOn[uiLed];
  Tuint08 uiState = uiLedState[uiLed];
  Tuint08 uiBits  = (1 << uiLed);
  Tuint16 uiDelay = 100;
  if (uiState == defDemoRequestLedStateFollow)
  { }
  else if (uiState == defDemoRequestLedStateOff)
  { ledOff(uiBits); }
  else if (uiState == defDemoRequestLedStateOn)
  { ledOn(uiBits); }
  else if (uiState == defDemoRequestLedStateFlash)
  { ledInv(uiBits);
    if (getLed(uiBits) == 0x00)
    { uiDelay = (((Tuint16) uiPerOff)<<5); }
    else
    { uiDelay = (((Tuint16) uiPerOn)<<5); } }
  else if (uiState == defDemoRequestLedStateFreeze)
  { while(true); }
  taskRestart(defRestartDefault,uiDelay); }

#if (cfgIntTickTrack == cfgTrue)

void SIG_PIN_CHANGE(void) __attribute__ ( ( signal, naked, used, externally_visible ) );
void SIG_PIN_CHANGE(void) { asm ("reti"); }

#else

void SIG_PIN_CHANGE(void) __attribute__ ( ( signal, naked, used, externally_visible ) );
void SIG_PIN_CHANGE(void)
{ isrEnter();
  Tuint08 uiLed;
  for (uiLed=0; uiLed<8; uiLed++)
  { if ( uiLedState[uiLed]==defDemoRequestLedStateFollow )
    { ledInv(1 << uiLed); } }
  isrExit(); }

#endif

#if (preTaskDefined(LEDtask0))
  void appLoop_LEDtask0(void)  { wait(0); }
#endif

#if (preTaskDefined(LEDtask1))
  void appLoop_LEDtask1(void)  { wait(1); }
  #endif

#if (preTaskDefined(LEDtask2))
  void appLoop_LEDtask2(void)  { wait(2); }
#endif

#if (preTaskDefined(LEDtask3))
  void appLoop_LEDtask3(void)  { wait(3); }
#endif

#if (preTaskDefined(LEDtask4))
  void appLoop_LEDtask4(void)  { wait(4); }
#endif

#if (preTaskDefined(LEDtask5))
  void appLoop_LEDtask5(void)  { wait(5); }
#endif

#if (preTaskDefined(LEDtask6))
  void appLoop_LEDtask6(void)  { wait(6); }
#endif

#if (preTaskDefined(LEDtask7))
  void appLoop_LEDtask7(void)  { wait(7); }
#endif

