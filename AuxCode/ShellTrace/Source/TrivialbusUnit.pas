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

unit TrivialbusUnit;

interface

uses Windows, Classes, StrUtils, SysUtils, Parport, mmsystem;

const NewLine: integer = 10;
// collect maximal 1MB from the device.
const MaxBinArray = 1000000;
  type
  TState = (STATE_IN, STATE_OUT, STATE_TRI);

  ETimeOutException = class(Exception);

  THackedThread = class(TThread);

  Ttrivialbus = class
  private
    FParport: TParport;
    Fvirgin: boolean;
    FcrcValue: byte;
    FprevMaster: boolean;
    FcrcCheckResult: boolean;
    Fmaxtry: integer;
    FStartTime: cardinal;
    FCumBinResponse: string;
    FBlockBus: boolean;
    FBinMessage: array[0..MaxBinArray] of byte;
    FTimeMessage: array[0..MaxBinArray] of integer;
    FCountBytes: integer;
    function getTraceRDY: TBit;
    function getTraceDATA: TBit;
    procedure setTraceACK(const b: TBit);
    function getSCLin: TBit;
    function getACK: TBit;
    function getSDA: TBit;
    procedure setSCLout(const b: TBit);
    procedure setACK(const b: TBit);
    procedure setSDA(const b: TBit);
    procedure dirSDA(const s: TState);
    procedure dirACK(const s: TState);
    procedure propDelay;
    procedure calcCRC(b: byte);
    procedure clearCRC;
    function getCRC: byte;
    function checkCRC(b: byte): boolean;
    procedure initPins;
    procedure CheckTimeOut;
    function  getDO: TBit;
    function  getSIG: TBit;
    procedure setCLK(const b: TBit);
  protected
    procedure writeByte(b: byte);
    function readByte: byte;
    procedure startRead(var Readbuf: string);
    procedure startWrite(const Writebuf: string);
    procedure startCommunication(var Readbuf: string; Writebuf: string; var timeout: boolean);
    //procedure startTrace(var Readbuf: char; var timeout: boolean);
    procedure startTrace(var bufCount: integer; const CommanderObject: TObject);
    procedure TranslateRequest(const Request: string; var BinRequest: string; var succes: boolean);
    procedure TranslateResponse(var BinResponse: string; var Response: string);
    procedure Help(var Response: string);
  public
    property BlockBus: boolean read FBlockBus write FBlockBus;
    constructor create(const LPT: TParport);
    procedure initBus();
    procedure talk(const Request: string; var Response: string; var timeout: boolean);
    procedure trace(var traceMessage: string; const CommanderObject: TObject);

    procedure clearBuffer;
  end;

implementation

uses Constants, CommanderUnit;
// Shell use
// D5 (pin7)  : SCLout  verbind aan (PB2)  ingang aan chip
// D4 (pin6)  : SDAout  verbind aan (PB3)  ingang aan chip
// S5 (pin12) : SCLin   verbind aan (PB0)  uitgang chip
// S4 (pin13) : SDAin   verbind aan (PB1)  uitgang chip

// Trace use
// D7 (pin9)  : CLK0ut  verbind aan (PB2)   ingang aan chip
// S7 (pin11) : SIGin   verbind aan (PB0)   uitgang chip
// S6 (pin10) : DOin    verbind aan (PB1)   uitgang chip

// Trace use Bitbanging
// D7 (pin9)  : ACK0ut  verbind aan (PB2)   ingang aan chip
// S7 (pin11) : DATAin   verbind aan (PB0)   uitgang chip
// S6 (pin10) : RDYin    verbind aan (PB1)   uitgang chip

function Ttrivialbus.getTraceRDY: TBit;
begin
Result:=FParport.StatusBit[6];
end;

function Ttrivialbus.getTraceDATA: TBit;
begin
Result:=FParport.StatusBit[7];
end;

procedure Ttrivialbus.setTraceACK(const b: TBit);
begin
FParport.DataBit[7]:=b;
end;

function Ttrivialbus.getDO: TBit;
begin
Result:=FParport.StatusBit[6];
end;

function Ttrivialbus.getSIG: TBit;
begin
Result:=FParport.StatusBit[7];
end;

procedure Ttrivialbus.setCLK(const b: TBit);
begin
FParport.DataBit[7]:=b;
end;

// These methodes must be ported
function Ttrivialbus.getSCLin: TBit;
begin
Result:=FParport.StatusBit[5];
end;

function Ttrivialbus.getACK: TBit;
begin
Result:=FParport.StatusBit[4];
end;

function Ttrivialbus.getSDA: TBit;
begin
Result:=FParport.StatusBit[4];
end;

procedure Ttrivialbus.setSCLout(const b: TBit);
begin
FParport.DataBit[5]:=b;
end;

procedure Ttrivialbus.setACK(const b: TBit);
begin
FParport.DataBit[4]:=b;
end;

procedure Ttrivialbus.setSDA(const b: TBit);
begin
FParport.DataBit[4]:=b;
end;

procedure Ttrivialbus.dirSDA(const s: TState);
begin
  case s of
  STATE_IN:   FParport.ControlBit[1]:=1;
  STATE_OUT:  FParport.ControlBit[1]:=0;
  STATE_TRI:  FParport.ControlBit[1]:=1;
  end;
end;

procedure Ttrivialbus.dirACK(const s: TState);
begin
  case s of
  STATE_IN:   FParport.ControlBit[0]:=1;
  STATE_OUT:  FParport.ControlBit[0]:=0;
  STATE_TRI:  FParport.ControlBit[0]:=1;
  end;
end;

procedure Ttrivialbus.propDelay;
begin
sleep(1);
end;

procedure Ttrivialbus.calcCRC(b: byte);
begin
end;

procedure Ttrivialbus.clearCRC;
begin
end;

function Ttrivialbus.getCRC: byte;
begin
Result:=$00;
end;

function Ttrivialbus.checkCRC(b: byte): boolean;
begin
Result:=true;
end;

procedure Ttrivialbus.initPins;
begin
setSCLout(0);
setSDA(0);
setACK(0);
setTraceACK(0);
end;

// These methodes are chip independant

procedure Ttrivialbus.writeByte(b: byte);
var bitCnt: byte;
begin
bitCnt:=8;
while (bitCnt<>0) do
  begin
  dec(bitCnt);
  setSDA((b and $80) shr 7);
  while(getACK<>0) do CheckTimeOut;
  setSCLout(1);
  while(getACK=0) do CheckTimeOut;
  b := (b shl 1) and $FF;
  setSCLout(0);
  end;
end;

function Ttrivialbus.readByte: byte;
var bitCnt: byte;
begin
result := 0;
bitCnt := 8;
while (bitCnt<>0) do
  begin
  dec(bitCnt);
  while(getSCLin<>0) do CheckTimeOut;
  if (FBlockBus) and (Random<0.02)
  then setAck(1)
  else setACK(0);
  while(getSCLin=0) do CheckTimeOut;
  result := result shl 1;
  result := result or getSDA;
  setACK(1);
  end;
end;

// Let op, Readbuf is een pascal string, geen c string,
// het is alleen de payload, niets meer. De lengte
// kunnen we eenvoudig vinden.
procedure Ttrivialbus.startRead(var Readbuf: string);
var i: integer;
    payloadLength: byte;
    currentByte: byte;
begin
clearCRC();
setACK(1);
payloadLength := readByte-2;
SetLength(Readbuf,payloadLength);
for i:=1 to payloadLength do
  begin
  currentByte:=readByte;
  ReadBuf[i]:=char(currentByte);
  calcCRC(currentByte);
  end;
FcrcCheckResult:=checkCRC(readByte); // met het resultaat doen we nog niets
while(getSCLin<>0) do CheckTimeOut;
setACK(0);
Fvirgin:=false;
FprevMaster:=true;
end;


procedure Ttrivialbus.startWrite(const Writebuf: string);
var i: integer;
    payloadLength: byte;
begin
clearCRC();
setSCLout(0);
payloadLength := Length(Writebuf);
writeByte(payloadLength+2);
for i:=1 to payloadLength do
  begin
  writeByte(byte(Writebuf[i]));
  calcCRC(byte(Writebuf[i]));
  end;
writeByte(getCRC());
setSDA(0);
while (getACK<>0) do CheckTimeOut;
Fvirgin:=false;
FprevMaster:=false;
end;

procedure Ttrivialbus.CheckTimeOut;
begin
if (GetTickCount()-FStartTime)>5000 then raise ETimeOutException.Create('');
end;


constructor Ttrivialbus.create(const LPT: TParport);
begin
FParport:= LPT;
Fmaxtry:= 255;
end;

procedure Ttrivialbus.initBus;
begin
initPins();
Fvirgin:=true;
FprevMaster:=false;
end;

procedure Ttrivialbus.startCommunication(var Readbuf: string; Writebuf: string; var timeout: boolean);
var cnt: byte;
begin
timeout:=false;
FStartTime := GetTickCount();
try try
  while true do
    begin
    if (Length(writebuf)>0)
    then
      begin
      setSCLout(1);
      while true do
        begin
        if (getACK<>0) then
          begin
          startWrite(writebuf);
          SetLength(writebuf,0);
          break;
          end;
        if ( not(FprevMaster) and (getSCLin<>0) ) then
          begin
          setSCLout(0);
          propDelay();
          cnt:=0;
          while ( not(Fvirgin) or (cnt < Fmaxtry) ) do
            begin
            inc(cnt);
            if (getSCLin<>0) then
              begin
              startRead(readbuf);
              break;
              end;
            CheckTimeOut;
            end;
          break;
          end;
        CheckTimeOut;
        end;
      end
    else
      begin
      if (getSCLin=0) then break;
      if (Length(Readbuf)>0) then  break;
      startRead(readbuf);
      end;
    CheckTimeOut;
    end;
  except
    on ETimeOutException do timeout:=true;
  end;
  finally
  setSCLout(0);
  end;
end;


procedure Ttrivialbus.startTrace(var bufCount: integer; const CommanderObject: TObject);
//const timeMax: integer = 30000;
const periodMax: integer = 5;
var i,j: integer;
    period: integer;
    b: byte;
    repetition: boolean;
    LoopCounter: integer;
    startTime: integer;
    currentTime: integer;
    repLoop: integer;
    bufCountLoop: integer;
    readCount: integer;
    timeOut: boolean;
    markerCount: integer;
    multiByteMes: integer;
    Commander: TCommander;
begin
repLoop:=0;
LoopCounter:=0;
bufCount:=0;
startTime:=timeGetTime();
currentTime:=0;
timeOut:=false;
FCountBytes:=0;
bufCountLoop:=0;
markerCount:=0;
multiByteMes:=0;
repetition:=false;
Commander := CommanderObject as TCommander;

while (bufCount<=(High(FBinMessage)-20)) and (not timeOut) and ((markerCount<Commander.MarkerMaxCount) or (Commander.MarkerMaxCount=0))and (not THackedThread(CommanderObject).Terminated) do
  begin
  readCount:=0;
    repeat
    inc(ReadCount);
    {while(getSIG<>1) and ((currentTime<Commander.Timeout) or( Commander.Timeout=0)) and (not THackedThread(CommanderObject).Terminated)  do currentTime:=integer(timeGetTime())-startTime;
    timeOut:=(getSIG=0);
    if not timeOut then
      begin
      b:=0;
      if (multiByteMes>0) then dec(multiByteMes);
      for i:=0 to 7 do
        begin
        b:=b shl 1;
        setCLK(1);
        b:=b or getDO;
        setCLK(0);
        end;}
//function Ttrivialbus.getRDY: TBit;
//function Ttrivialbus.getDATA: TBit;
//procedure Ttrivialbus.setACK(const b: TBit);
    while(getTraceRDY<>1) and ((currentTime<Commander.Timeout) or( Commander.Timeout=0)) and (not THackedThread(CommanderObject).Terminated)  do currentTime:=integer(timeGetTime())-startTime;
    timeOut:=(getTraceRDY=0);
    if not timeOut then
      begin
      b:=0;
      if (multiByteMes>0) then dec(multiByteMes);
      for i:=0 to 7 do
        begin
        b:=b shl 1;
        j:=(i+1) mod 2;
        while(getTraceRDY<>j) and ((currentTime<Commander.Timeout) or( Commander.Timeout=0)) and (not THackedThread(CommanderObject).Terminated)  do currentTime:=integer(timeGetTime())-startTime;
        timeOut:=(getTraceRDY<>j);
        if (timeOut) then Break;
        b:=b or getTraceDATA;
        setTraceACK(j);
        end;
      inc(FCountBytes);
      if (multiByteMes=0) and ((b = $02) or ((b and $F0) = $30) or ((b and $F0) = $40)) then multiByteMes:=2;
      if (multiByteMes=0) and ((b = $03) or (b = $5F)) then multiByteMes:=3;
      if (multiByteMes=0) and ((b = $58) or (b = $5E) ) then multiByteMes:=100;
      if (multiByteMes=99) then multiByteMes:=b+1;
      if (b=$01) and (multiByteMes=0) then inc(markerCount);
      if (markerCount >= Commander.MarkerMinCount) then
        begin
        FBinMessage[bufCount]:=b;
        FtimeMessage[bufCount]:=currentTime;
        inc(bufCount);
        end;
      end;
    until ((ReadCount>=repLoop) and (bufCount>2*periodMax)) or timeOut;
  if timeOut
  then repetition:=false
  else
    begin
    if (repLoop=0) then period:=0 else period:=repLoop-1;
    // als er aan het begin van het block een multibyte message $F1 staat is de herhalingsdetectie ongeldig.
    // als er aan het begin van het block een multibyte message $3x of $4x staat is de herhalingsdetectie ongeldig.
    if (multiByteMes = 0) then
      repeat
      inc(period);
      repetition:=true;
      i:=0;
      while repetition and (i<period) do
        begin
        repetition := repetition and (FBinMessage[bufCount-i-1] = FBinMessage[bufCount-i-period-1]);
        inc(i);
        end;
      until repetition or (period=periodMax) or (repLoop>0);
    if repetition then
      begin
      if repLoop=0
      then
        begin
        LoopCounter:=2;
        repLoop:=period;
        bufCount:=bufCount-period;
        bufCountLoop:=bufCount;
        end
      else if (repLoop=period) then
        begin
        inc(LoopCounter);
        bufCount:=bufCountLoop;
        end
      else repetition:=false;
      end;
    end;
  if (not repetition) and (repLoop>0) then
    begin
    for i:=bufCount-1 downto bufCountLoop do
      begin
      FBinMessage[i+4]:=FBinMessage[i];
      FtimeMessage[i+4]:=FtimeMessage[i];
      end;
    if (LoopCounter>$FFFF) then LoopCounter:=$FFFF;
    FtimeMessage[bufCountLoop]:=FtimeMessage[bufCount-1];
    FBinMessage[bufCountLoop]:=$0F;
    FBinMessage[bufCountLoop+1]:=repLoop mod 256;
    FBinMessage[bufCountLoop+2]:=LoopCounter div 256;
    FBinMessage[bufCountLoop+3]:=LoopCounter mod 256;
    bufCount:=bufCount+4;
    repLoop:=0;
    end;
  end;
end;

function HexToInt(const hex: string): integer;
begin
if LeftStr(Trim(hex),2)='0x'
then Result := StrToInt('$'+Copy(Trim(hex),3,100))
else Result := StrToInt(Trim(hex));
end;

procedure Ttrivialbus.TranslateRequest(const Request: string; var BinRequest: string; var succes: boolean);
var
  Command: TStringList;

  function minArgs(const args: integer): boolean;
  begin
  result := args<Command.Count;
  end;

var
  i: integer;
  lednumber: integer;
  ledstate: integer;
  ledperon: integer;
  ledperoff: integer;
  valresult: integer;
begin
succes:=true;
BinRequest:='';
valresult := 0;
ledperon:=0;
ledperoff:=0;
Command := TStringList.Create();
Command.Delimiter := ' ';
Command.DelimitedText:=Trim(Request);
for i:=Command.Count-1 downto 0 do  if Command[i]='' then Command.Delete(i);
  try
  if Command[0] = 'id' then BinRequest := char(defRequestFemtoOs)
  else if (Command[0] = 'ticks') then                    BinRequest := char(defRequestTickCount)
  else if (Command[0] = 'uptime') then                   BinRequest := char(defRequestUptime)
  else if (Command[0] = 'reboot') then                   BinRequest := char(defRequestReboot)
  else if (Command[0] = 'list') then                     BinRequest := char(defRequestProcessList)
  else if (Command[0] = 'suspend') and minArgs(1) then   BinRequest := char(defRequestSuspend)+char(StrToInt(Command[1]))
  else if (Command[0] = 'resume') and minArgs(1) then    BinRequest := char(defRequestResume)+char(StrToInt(Command[1]))
  else if (Command[0] = 'kill') then                     BinRequest := char(defRequestTerminate)+char(StrToInt(Command[1]))
  else if (Command[0] = 'priority') and minArgs(2) then  BinRequest := char(defRequestPriority)+char(StrToInt(Command[1]))+char(StrToInt(Command[2]))
  else if (Command[0] = 'recreate') and minArgs(1) then  BinRequest := char(defRequestTaskRecreate)+char(StrToInt(Command[1]))
  else if (Command[0] = 'test') then                     BinRequest := char(defRequestTest) //+'12345678901234567890123456789'
  else if (Command[0] = 'store') and minArgs(2) then     BinRequest := char(defRequestStore)+char(StrToInt(Command[1]))+char(Length(Command[2]))+Command[2]
  else if (Command[0] = 'recall') then                   BinRequest := char(defRequestRecall)+char(StrToInt(Command[1]))
  else if (Command[0] = 'dump') and minArgs(3) then
    begin
    BinRequest := char(defRequestDump);
    if Command[1] = 'ram' then BinRequest := BinRequest+ char(defDumpRAM)
    else if Command[1] = 'eeprom' then BinRequest := BinRequest+ char(defDumpEEPROM)
    else if Command[1] = 'flash' then BinRequest := BinRequest+ char(defDumpFLASH)
    else succes := false;
    if (succes) then BinRequest := BinRequest + char(HexToInt(Command[2]) div 256)+ char(HexToInt(Command[2]) mod 256) + char(HexToInt(Command[3]) mod 256)
    end
  else if (Command[0] = 'ledstate') and minArgs(2) then
    begin
    if Command[1] = 'all' then lednumber:=8 else val(Command[1],lednumber,valresult);
    if Command[2] = 'off' then ledstate := defDemoRequestLedStateOff
    else if Command[2] = 'on' then ledstate := defDemoRequestLedStateOn
    else if Command[2] = 'flash' then ledstate := defDemoRequestLedStateFlash
    else if Command[2] = 'freeze' then ledstate := defDemoRequestLedStateFreeze
    else if Command[2] = 'follow' then ledstate := defDemoRequestLedStateFollow
    else ledstate := defDemoRequestLedStateUndef;
    BinRequest := char(defDemoRequestLedState)+char(lednumber)+char(ledstate);
    end
  else if (Command[0] = 'ledcycle') and minArgs(1) then
    begin
    if Command[1] = 'all' then lednumber:=8 else val(Command[1],lednumber,valresult);
    if valresult=0 then val(Command[2],ledperon,valresult);
    if valresult=0 then val(Command[3],ledperoff,valresult);
    BinRequest := char(defDemoRequestLedCycle)+char(lednumber)+char(ledperon)+char(ledperoff);
    end
  else if (Command[0] = 'ledsave') and minArgs(1) then BinRequest := char(defDemoRequestLedSave)+char(StrToInt(Command[1]))
  else if (Command[0] = 'ledload') and minArgs(1) then BinRequest := char(defDemoRequestLedLoad)+char(StrToInt(Command[1]))
  else succes := false;
  if valresult<>0 then succes:=false;
  finally
  Command.free;
  end;
end;

function fill(n: integer; const s: string; m: integer): string;
const fillstr: string = '          ';
var len: integer;
begin
Result:=s;
len:=Length(Result);
if len<n then Result:=copy(fillstr,1,n-len) + Result;
len:=Length(Result);
if len<m then Result:=Result + copy(fillstr,1,m-len);
end;

function TickTime(val: integer): string;
begin
Result:=fill(5,IntToStr(val),0);
end;

function IntToStr02(const i: integer): string;
begin
Result:=IntToStr(i);
if i<10 then Result:='0'+Result;
end;

function DIG03(const b: double): string;
begin
Result:=FloatToStrF(b,ffFixed,3,3);
end;

function Conv08(const b: char): string;
begin
Result:=fill(3,IntToStr(ord(b)),0);
end;

function Conv16(const b,c: char): string;
begin
Result:=fill(5,IntToStr(256*ord(b)+ord(c)),0);
end;

function ConHex04(const b: char): string;
begin
Result:=IntToHex(ord(b),1);
end;

function ConHex08(const b: char): string;
begin
Result:=IntToHex(ord(b),2);
end;

function ConHex16(const b,c: char): string;
begin
Result:=IntToHex(256*ord(b)+ord(c),4);
end;

function SlotDec(const b: char): string;
begin
Result:=IntToStr(ord(b) div 16)+ ',' +IntToStr(ord(b) mod 16);
end;

function TaskStatus(const c: char): string;
var b: byte;
begin
b := ord(c);
Result:='';
if (b and defBaseTerminatedGetMask) = defBaseTerminatedTask       then
  begin
  Result:=Result+' term ';
  Result:=Result+'  --- ';
  Result:=Result+'  --- ';
  Result:=Result+'  ---';
  end
else if (b and defBaseSuspendedGetMask) = defBaseSuspendedTask     then
  begin
  Result:=Result+' susp ';
  Result:=Result+'  --- ';
  if (b and defBaseDelayStateGetMask) = defBaseDelayStateWake     then Result:=Result+'  run ';
  if (b and defBaseDelayStateGetMask) = defBaseDelayStateDelayed  then Result:=Result+'delay ';
  Result:=Result+'  ---';
  end
else if (b and defBaseSleepingGetMask) = defBaseSleepingTask      then
  begin
  Result:=Result+'sleep ';
  if (b and defBaseBlockStateGetMask) = defBaseBlockStateBlocked  then Result:=Result+' sync ';
  if (b and defBaseBlockStateGetMask) = defBaseBlockStateFree     then Result:=Result+' free ';
  if (b and defBaseDelayStateGetMask) = defBaseDelayStateWake     then Result:=Result+'  run ';
  if (b and defBaseDelayStateGetMask) = defBaseDelayStateDelayed  then Result:=Result+'delay ';
  if (b and defBaseBlockStateGetMask) = defBaseBlockStateBlocked  then
    begin
    if (b and defBaseDressGetMask) = defBaseDressSlot             then Result:=Result+' slot';
    if (b and defBaseDressGetMask) = defBaseDressEvent            then Result:=Result+'event';
    end
  else Result:=Result+'  ---';
  end
else if (b and defBaseStopStateGetMask) = defBaseStopStateGo      then
  begin
  Result:=Result+'   go ';
  if (b and defBaseModeGetMask) = defBaseModeAccess  then
    begin
    if (b and defBaseBlockStateGetMask) = defBaseBlockStateBlocked  then Result:=Result+' file ';
    if (b and defBaseBlockStateGetMask) = defBaseBlockStateFree     then Result:=Result+'share ';
    if (b and defBaseDelayStateGetMask) = defBaseDelayStateWake     then Result:=Result+'  run ';
    if (b and defBaseDelayStateGetMask) = defBaseDelayStateDelayed  then Result:=Result+'delay ';
    if (b and defBaseBlockStateGetMask) = defBaseBlockStateBlocked  then
      begin
      if (b and defBaseDressGetMask) = defBaseDressRead             then Result:=Result+' read';
      if (b and defBaseDressGetMask) = defBaseDressWrite            then Result:=Result+'write';
      end
    else
      begin
      if (b and defBaseDressGetMask) = defBaseDressRead             then Result:=Result+'ready';
      if (b and defBaseDressGetMask) = defBaseDressWrite            then Result:=Result+' done';
      end
    end;
  if (b and defBaseModeGetMask) = defBaseModeSync  then
    begin
    if (b and defBaseBlockStateGetMask) = defBaseBlockStateBlocked  then Result:=Result+' sync ';
    if (b and defBaseBlockStateGetMask) = defBaseBlockStateFree     then Result:=Result+' free ';
    if (b and defBaseDelayStateGetMask) = defBaseDelayStateWake     then Result:=Result+'  run ';
    if (b and defBaseDelayStateGetMask) = defBaseDelayStateDelayed  then Result:=Result+'delay ';
    if (b and defBaseBlockStateGetMask) = defBaseBlockStateBlocked  then
      begin
      if (b and defBaseDressGetMask) = defBaseDressSlot             then Result:=Result+' slot';
      if (b and defBaseDressGetMask) = defBaseDressEvent            then Result:=Result+'event';
      end;
    if (b and defBaseBlockStateGetMask) = defBaseBlockStateFree     then
      begin
      if (b and defBaseDressGetMask) = defBaseDressRunable          then Result:=Result+'ready';
      if (b and defBaseDressGetMask) = defBaseDressDone             then Result:=Result+' done';
      end;
    end;
  end
else
  begin
  Result:=Result+' term ';
  Result:=Result+'  --- ';
  Result:=Result+'  ??? ';
  Result:=Result+'  ---';
  end
end;

function TaskPriority(const c: char): string;
var b: byte;
begin
b := ord(c);
Result:=fill(4,IntToStr((b and defBasePrioGetMask) shr defBasePrioShift),0);
end;

function WatchDog(const c: char): string;
var b: byte;
begin
b := ord(c);
if (b and defDogGetMask) = defDogDead   then Result:=' dead';
if (b and defDogGetMask) = defDogBark   then Result:=' bark';
if (b and defDogGetMask) = defDogWake   then Result:=' wake';
if (b and defDogGetMask) = defDogSleep  then Result:='sleep';
end;

function FileMode(const c: char): string;
var b: byte;
begin
b := ord(c);
if ((b and defFsReadGetMask) = defFsReadClear)  and ((b and defFsWriteGetMask) = defFsWriteClear)  then Result:='    -';
if ((b and defFsReadGetMask) = defFsReadClear)  and ((b and defFsWriteGetMask) = defFsWriteActive) then Result:='write';
if ((b and defFsReadGetMask) = defFsReadActive) and ((b and defFsWriteGetMask) = defFsWriteClear)  then Result:=' read';
if ((b and defFsReadGetMask) = defFsReadActive) and ((b and defFsWriteGetMask) = defFsWriteActive) then Result:='ERROR';
end;


function Slots(const c0,c1,c2,c3: char): string;
var b0,b1,b2,b3: byte;
    SlotString: string;
begin
b0 := ord(c0);
b1 := ord(c1);
b2 := ord(c2);
b3 := ord(c3);
SlotString := '';
if (b0>0) then SlotString := IntToHex((b1 and defSlotRightGetMask) shr defSlotRightShift,1) + SlotString;
if (b0>1) then SlotString := IntToHex((b1 and defSlotLeftGetMask) shr defSlotLeftShift,1) + SlotString;
if (b0>2) then SlotString := IntToHex((b2 and defSlotRightGetMask) shr defSlotRightShift,1) + SlotString;
if (b0>3) then SlotString := IntToHex((b2 and defSlotLeftGetMask) shr defSlotLeftShift,1) + SlotString;
if (b0>4) then SlotString := IntToHex((b3 and defSlotRightGetMask) shr defSlotRightShift,1) + SlotString;
if (b0>5) then SlotString := IntToHex((b3 and defSlotLeftGetMask) shr defSlotLeftShift,1) + SlotString;
while (Length(SlotString)<6) do SlotString := '-' + SlotString;
Result:=SlotString;
end;

function Nest(const c1,c2: char): string;
var b1,b2: byte;
    GlobWidth, TickWidth, SwitchWidth,
    GlobShift, TickShift, SwitchShift,
    GlobNest, TickNest, SwitchNest,
    GlobMask, TickMask, SwitchMask  : integer;
begin
b1:= ord(c1);
b2:= ord(c2);
GlobWidth:=   (b1 and $0F) shr 0;
TickWidth:=   (b1 and $F0) shr 4;
SwitchWidth:= (8-TickWidth-GlobWidth);
GlobShift:=   (0);
TickShift:=   (GlobWidth);
SwitchShift:= (GlobWidth+TickWidth);
GlobMask:=    ((1 shl GlobWidth)-1) shl GlobShift;
TickMask:=    ((1 shl TickWidth)-1) shl TickShift;
SwitchMask:=  ((1 shl SwitchWidth)-1) shl SwitchShift;
GlobNest:=    (b2 and GlobMask) shr GlobShift;
TickNest:=    (b2 and TickMask) shr TickShift;
SwitchNest:=  (b2 and SwitchMask) shr SwitchShift;
Result:= IntToStr(SwitchNest)+' '+IntToStr(TickNest)+' '+IntToStr(GlobNest);
//Result:= ConHex08(c1)+' '+ConHex08(c2);
end;

function RegUse(const c: char): string;
var i: integer;
    b: byte;
begin
b := ord(c);
Result:='';
for i:=7 downto 0 do
  begin
  if (b and (1 shl i))=0 then Result:=Result+'_' else Result:=Result+'x';
  end;
end;

function OsStatus(const c: char): string;
var b: byte;
begin
b := ord(c);
Result:='';
if (b and defNearWakePresentGetMask) = defNearWakeStatePresent  then Result:=Result+' near' else Result:=Result+'  far';
Result:=Result+'   ';
Result:=Result+ fill(2,IntToStr((b and defTaskNumberGetMask) shl defTaskNumberShift),0);
end;

function FsStatus(const c: char): string;
var b: byte;
begin
b := ord(c);
Result:='';
if ((b and defFsReadBlockGetMask) = defFsReadBlockActive) and ((b and defFsWriteBlockGetMask) = defFsWriteBlockActive)  then Result:=Result+' pend ';
if ((b and defFsReadBlockGetMask) = defFsReadBlockActive) and ((b and defFsWriteBlockGetMask) = defFsWriteBlockClear)   then Result:=Result+' read ';
if ((b and defFsReadBlockGetMask) = defFsReadBlockClear) and ((b and defFsWriteBlockGetMask) = defFsWriteBlockActive)   then Result:=Result+'write ';
if ((b and defFsReadBlockGetMask) = defFsReadBlockClear) and ((b and defFsWriteBlockGetMask) = defFsWriteBlockClear)    then Result:=Result+'    - ';
if ((b and defFsBurnBlockGetMask) = defFsBurnBlockActive) then Result:=Result+'block' else Result:=Result+' free';
Result:=Result+'     ';
Result:=Result+ConHex04(c);
end;

procedure Ttrivialbus.TranslateResponse(var BinResponse: string; var Response: string);
var cutLength: integer;
  v,i: integer;
  upTOT: Int64;
  upSECS,upMINS,upHOURS,upDAYS: integer;
  fileLength: integer;
begin
cutLength:=0;
if BinResponse='' then Response := ''
else if BinResponse[1]=char(defResponseOK) then
  begin
  Response := 'sys: ok';
  cutLength := defLengthOK;
  end
else if BinResponse[1]=char(defResponseUnknownCommand) then
  begin
  Response := 'unknown command';
  cutLength := defLengthUnknownCommand;
  end
else if BinResponse[1]=char(defResponseError) then
  begin
  Response := 'sys: error';
  cutLength := defLengthUnknownCommand;
  end
else if BinResponse[1]=char(defResponseInvalidTask) then
  begin
  Response := 'sys: invalid task number';
  cutLength := defLengthInvalidTask;
  end
else if BinResponse[1]=char(defResponseInvalidPriority) then
  begin
  Response := 'sys: invalid priority';
  cutLength := defLengthInvalidPriority;
  end
else if BinResponse[1]=char(defResponseInvalidFileNumber) then
  begin
  Response := 'sys: invalid file number';
  cutLength := defLengthInvalidFileNumber;
  end
else if BinResponse[1]=char(defResponseFemtoOs) then
  begin
  if Length(BinResponse)>=defLengthFemtoOs then
    begin
    Response := 'id: '+copy(BinResponse,2,defLengthFemtoOs-1);
    cutLength := defLengthFemtoOs;
    end;
  end
else if BinResponse[1]=char(defResponseTickCount) then
  begin
  if Length(BinResponse)>=defLengthTickCount then
    begin
    Response := 'System counter: 0x'+ConHex16(BinResponse[2],BinResponse[3]) + ' (ticks)';
    cutLength := defLengthTickCount;
    end;
  end
else if BinResponse[1]=char(defResponseUptime) then
  begin
  if Length(BinResponse)>=defLengthTickCount then
    begin
    upTOT:=0;
    for i:=1 to 5 do upTOT := 256*upTOT + ord(BinResponse[i+1]);
    upDAYS := upTOT div (1000*3600*24); upTOT := upTOT - Int64(upDAYS)*(1000*3600*24);
    upHOURS := upTOT div (1000*3600);   upTOT := upTOT - Int64(upHOURS)*(1000*3600);
    upMINS := upTOT div (1000*60);      upTOT := upTOT - Int64(upMINS)*(1000*60);
    upSECS := upTOT div (1000);         
    Response := 'Uptime: '+IntToStr(upDAYS) + ' days, '+IntToStr02(upHOURS)+':'+IntToStr02(upMINS)+':'+IntToStr02(upSECS)+' hours.';
    cutLength := defLengthUptime;
    end;
  end
else if BinResponse[1]=char(defResponseLogTask) then
  begin
  if Length(BinResponse)>=defLengthLogTask then
    begin
    if (BinResponse[2])=char(0)
    then
      Response := char(NewLine)
        + 'identifier--  status-----------------------------  admin------------------  watermarks----' + char(NewLine)
        + '-nr ----name  state -lock sched dress -wdog -file  prio -time -nest -slots  stack register' + char(NewLine)
    else Response := '';
    Response := Response
      + Conv08(BinResponse[2])+ ' '
      + Copy(BinResponse,6,8)+'  '
      + TaskStatus(BinResponse[3])+' '
      + WatchDog(BinResponse[14])+' '
      + FileMode(BinResponse[14])+'  '
      + TaskPriority(BinResponse[3])+ ' '
      + Conv16(BinResponse[4],BinResponse[5])+' '
      + Nest(BinResponse[15],BinResponse[16])+' '
      + Slots(BinResponse[17],BinResponse[18],BinResponse[19],BinResponse[20])+' '
      + ' '+ Conv16(BinResponse[21],BinResponse[22])+' '
      + RegUse(BinResponse[23]);
    cutLength := defLengthLogTask;
    end;
  end
else if BinResponse[1]=char(defResponseLogOs) then
  begin
  if Length(BinResponse)>=defLengthLogOs then
    begin
    Response :=
        'task------  file system------  time-------------  stack----' + char(NewLine)
      + 'first curr  -mode -burn tsk/#  ---os -idle --isr  -os --isr' + char(NewLine)
      + OsStatus(BinResponse[2])+'  '
      + FsStatus(BinResponse[3])+'  '
      + Conv16(BinResponse[4],BinResponse[5])+' '
      + Conv16(BinResponse[6],BinResponse[7])+' '
      + Conv16(BinResponse[8],BinResponse[9])+'  '
      + Conv08(BinResponse[10])+' '
      + Conv16(BinResponse[11],BinResponse[12]);
    cutLength := defLengthLogOs;
    end;
  end
else if BinResponse[1]=char(defResponseDump) then
  begin
  if Length(BinResponse)>=defLengthDump then
    begin
    Response := ConHex16(BinResponse[2],BinResponse[3])+ ' :';
    for v:=0 to 3 do Response := Response+' '+ConHex08(BinResponse[4+v]);
    Response := Response + ' ';
    for v:=4 to 7 do Response := Response+' '+ConHex08(BinResponse[4+v]);
    Response := Response + ' ';
    for v:=8 to 11 do Response := Response+' '+ConHex08(BinResponse[4+v]);
    Response := Response + ' ';
    for v:=12 to 15 do Response := Response+' '+ConHex08(BinResponse[4+v]);
    Response := Response + ' : ';
    for v:=0 to 15 do
      if (ord(BinResponse[4+v])>32)and (ord(BinResponse[4+v])<127)
      then Response := Response + BinResponse[4+v]
      else Response := Response + '.';
    cutLength := defLengthDump;
    end
  end
else if BinResponse[1]=char(defResponseFile) then
  begin
  if Length(BinResponse)>=defLengthFile then
    begin
    fileLength := ord(BinResponse[2]);
    if (fileLength = 0)
    then Response := 'Empty file.'
    else Response := 'File content: '+ copy(BinResponse,3,fileLength);
    cutLength := defLengthFile + fileLength;
    end
  end
else if BinResponse[1]=char(defDemoResponseLedOK) then
  begin
  Response := 'led: ok';
  cutLength := 1;
  end
else if BinResponse[1]=char(defDemoResponseLedError) then
  begin
  Response := 'led: error';
  cutLength := 1;
  end
else
  begin
  Response := 'Unrecognized response, length: '+IntToStr(Length(BinResponse));
  BinResponse := '';
  end;
if cutLength>0 then BinResponse := copy(BinResponse,cutLength+1,Length(BinResponse));
end;

procedure Ttrivialbus.Help(var Response: string);
begin
Response := 'FemtoOS Shell by R. Vlaming' + char(NewLine)
 + ' ' + char(NewLine)
 + 'general commands:' + char(NewLine)
 + ' help               : generate this text' + char(NewLine)
 + ' id                 : report the FemtoOS system ID' + char(NewLine)
 + ' ticks              : report the system tickcounter in ticks' + char(NewLine)
 + ' uptime             : report the time past since the last reboot' + char(NewLine)
 + ' reboot             : reboot (not reset!) the system' + char(NewLine)
 + ' list               : show OS and task process variables' + char(NewLine)
 + ' suspend [nr]       : stops the given task [nr] from being run' + char(NewLine)
 + ' resume [nr]        : task [nr] is rescheduled for execution again' + char(NewLine)
 + ' kill [nr]          : terminate task [nr]' + char(NewLine)
 + ' recreate [nr]      : complete recreation of task [nr]' + char(NewLine)
 + ' priority [nr] [pr] : give task [nr] new priority [pr] (0..7)' + char(NewLine)
 + ' dump [t] [s] [l]   : dump [l] bytes of the [t] ram/flash/eeprom, starting at [s]; s,l: hex/dec' + char(NewLine)
 + ' store [nr] [cont]  : store ascii content [cont] under filenumber [nr]' + char(NewLine)
 + ' recall [nr]        : recall the content of filenumber [nr]' + char(NewLine)
 + ' test               : may have any effect, including a full crash' + char(NewLine)
 + ' ' + char(NewLine)
 + 'democommands:' + char(NewLine)
 + ' ledstate {[led]|all} {off|on|flash|freeze|follow} : led new state ' + char(NewLine)
 + ' ledcycle {[led]|all} [ontime] [offtime]           : dutycycle, blocks of 32ms.' + char(NewLine)
 + ' ledsave  [nr]      : save the current ledstate and cycles in file [nr] (0..3)' + char(NewLine)
 + ' ledload  [nr]      : load the current ledstate and cycles from file [nr] (0..3)' + char(NewLine)
 + ' ' + char(NewLine)
 + 'examples: ' + char(NewLine)
 + ' kill 0             : immideately terminates task 0.' + char(NewLine)
 + ' priority 4 2       : sets the priority of task 4 to level 2. ' + char(NewLine)
 + ' dump ram 0x200 100 : dump 100 bytes starting from address 0x200.' + char(NewLine)
 + ' ledstate 2 flash   : make ledtask 2 (third led) flash  ' + char(NewLine)
 + ' ledstate 3 follow  : make ledtask 3 follow the interrupts on pin PB6  ' + char(NewLine)
 + ' ledcycle 2 1 10    : make ledtask 2 cycle 32 ms on and 320 ms off. ' + char(NewLine)
 + ' ledstate all off   : switch all leds off. ' + char(NewLine)
 + ' ' + char(NewLine);
end;

procedure Ttrivialbus.talk(const Request: string; var Response: string; var timeout: boolean);
var
  BinRequest: string;
  BinResponse: string;
  succes: boolean;
begin
succes:=true;
BinRequest:='';
BinResponse:='';
Response:='';
if CompareText(Trim(Request),'help')=0
then Help(Response)
else
  begin
  if Length(Request)>0 then TranslateRequest(Request,BinRequest,succes);
  if succes
  then
    begin
    startCommunication(BinResponse,BinRequest,timeout);
    FCumBinResponse := FCumBinResponse + BinResponse;
    TranslateResponse(FCumBinResponse,Response);
    end
  else Response := 'Unrecognized request.';
 end;
end;

procedure Ttrivialbus.trace(var traceMessage: string; const CommanderObject: TObject);
var v,w: integer;
    str: string;
    len: integer;
    tottime: integer;
    val: byte;
    mesCount: integer;
    mesLen: integer;
    repetition: integer;
begin
startTrace(len,CommanderObject);
//setLength(traceMessage,20000);
setLength(str,4);
traceMessage := 'Collected '+ IntToStr(FCountBytes) +' bytes from the device.'+ char(NewLine);
v:=0;
while v<len do
  begin
  val:=FBinMessage[v];
  if (val=$0F) then
    begin
    mesCount:=FBinMessage[v+1];
    repetition:=FBinMessage[v+2]*256+ FBinMessage[v+3]-1;
    // decreasing of upper limit in forloop is intentional!
    // multibyte messages zijn geen onderdeel van de repetitie detectie
    //for i:=1 to mesCount do if (FBinMessage[v-i]=$F1) then dec(mesCount);
    if (mesCount=1) and (repetition=1)        then traceMessage := traceMessage + TickTime(FTimeMessage[v])+': repeated last message once.'+ char(NewLine)
    else if (mesCount=1) and (repetition>1)   then traceMessage := traceMessage + TickTime(FTimeMessage[v])+': repeated last message '+IntToStr(repetition)+' times.'+ char(NewLine)
    else if (mesCount>1) and (repetition=1)   then traceMessage := traceMessage + TickTime(FTimeMessage[v])+': repeated last '+IntToStr(mesCount)+ ' messages once.'+ char(NewLine)
    else traceMessage := traceMessage + TickTime(FTimeMessage[v])+': repeated last '+IntToStr(mesCount)+ ' messages '+IntToStr(repetition)+' times.'+ char(NewLine);
    v:=v+4;
    end
  else if (val=$5F) then
    begin
    traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ eventArray[val]+' '+Conv08(char(FBinMessage[v+1]))+','+Conv08(char(FBinMessage[v+2]))+ char(NewLine) ;
    v:=v+3;
    end
  else if (val=$58) then
    begin
    mesLen:=1+(FBinMessage[v+1] div 3);
    traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ eventArray[val]+ char(NewLine) ;
    traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ '  OS      :    '+Conv08(char(FBinMessage[v+2]))+ char(NewLine) ;
    traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ '  ISR     :  '+Conv16(char(FBinMessage[v+3]),char(FBinMessage[v+4]))+ char(NewLine) ;
    for w:=2 to mesLen-1 do
      begin
      if (w-2)<10
      then traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ '  Task  '+IntToStr(w-2)+' : '+' '+Conv16(char(FBinMessage[v+3*w-1]),char(FBinMessage[v+3*w]))+ '   ' + RegUse(char(FBinMessage[v+3*w+1])) + char(NewLine)
      else traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ '  Task ' +IntToStr(w-2)+' : '+' '+Conv16(char(FBinMessage[v+3*w-1]),char(FBinMessage[v+3*w]))+ '   ' + RegUse(char(FBinMessage[v+3*w+1])) + char(NewLine)
      end;
    v:=v+2+FBinMessage[v+1];
    end
  else if (val=$5E) then
    begin
    mesLen:=(FBinMessage[v+1] div 2);
    tottime:=0;
    for w:=0 to mesLen-1 do tottime := tottime + 256*FBinMessage[v+2*w+2] + FBinMessage[v+2*w+3];
    traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ eventArray[val]+ char(NewLine) ;
    traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ '  OS      :  '+Conv16(char(FBinMessage[v+2]),char(FBinMessage[v+3])) + '   (' + DIG03((256*FBinMessage[v+2]+FBinMessage[v+3])/tottime)+ ')' + char(NewLine) ;
    traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ '  Idle    :  '+Conv16(char(FBinMessage[v+4]),char(FBinMessage[v+5])) + '   (' + DIG03((256*FBinMessage[v+4]+FBinMessage[v+5])/tottime)+ ')' + char(NewLine) ;
    traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ '  ISR     :  '+Conv16(char(FBinMessage[v+6]),char(FBinMessage[v+7])) + '   (' + DIG03((256*FBinMessage[v+6]+FBinMessage[v+7])/tottime)+ ')' + char(NewLine) ;
    for w:=3 to mesLen-1 do
      begin
      if (w-3)<10
      then traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ '  Task  '+IntToStr(w-3)+' : '+' '+Conv16(char(FBinMessage[v+2*w+2]),char(FBinMessage[v+2*w+3]))+ '   (' + DIG03((256*FBinMessage[v+2*w+2]+FBinMessage[v+2*w+3])/tottime)+ ')' + char(NewLine)
      else traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ '  Task ' +IntToStr(w-3)+' : '+' '+Conv16(char(FBinMessage[v+2*w+2]),char(FBinMessage[v+2*w+3]))+ '   (' + DIG03((256*FBinMessage[v+2*w+2]+FBinMessage[v+2*w+3])/tottime)+ ')' + char(NewLine)
      end;
    v:=v+2+FBinMessage[v+1];
    end
  else if (val=$02) then
    begin
    traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ eventArray[val]+' '+ConHex08(char(FBinMessage[v+1]))+ char(NewLine) ;
    v:=v+2;
    end
  else if (val=$03) then
    begin
    traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ eventArray[val]+' '+ConHex08(char(FBinMessage[v+1]))+ConHex08(char(FBinMessage[v+2]))+ char(NewLine) ;
    v:=v+3;
    end
  else if ((val and $F0)=$30) or ((val and $F0)=$40) then
    begin
    traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ eventArray[val]+' '+SlotDec(char(FBinMessage[v+1]))+ char(NewLine) ;
    v:=v+2;
    end
  else
    begin
    traceMessage := traceMessage + TickTime(FTimeMessage[v])+': '+ eventArray[val]+char(NewLine);
    inc(v);
    end;
  end;

end;


procedure Ttrivialbus.clearBuffer;
begin
FCumBinResponse := '';
end;


end.

