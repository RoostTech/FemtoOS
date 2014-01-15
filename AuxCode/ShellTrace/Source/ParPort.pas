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

unit ParPort;

interface

uses Sysutils;

type
  TBit = 0 .. 1;
  TParPort = class
  private
    FDataAddress: word;
    FStatusAddress: word;
    FControlAddress: word;
    function WordBoolToBit(b: WordBool): TBit;
  protected
    procedure WriteDataByte(const val: byte);
    procedure WriteDataBit(const bit: byte; const val: TBit);
    procedure WriteStatusByte(const val: byte);
    procedure WriteStatusBit(const bit: byte; const val: TBit);
    procedure WriteControlByte(const val: byte);
    procedure WriteControlBit(const bit: byte; const val: TBit);
    function ReadDataByte: byte;
    function ReadDataBit(const bit: byte): TBit;
    function ReadStatusByte: byte;
    function ReadStatusBit(const bit: byte): TBit;
    function ReadControlByte: byte;
    function ReadControlBit(const bit: byte): TBit;
  public
    constructor create(BaseAddress: word);
    function CheckDriver: boolean;
    property DataByte: byte read ReadDataByte write WriteDataByte;
    property StatusByte: byte read ReadStatusByte write WriteStatusByte;
    property ControlByte: byte read ReadControlByte write WriteControlByte;
    property DataBit[const nr: byte]: TBit read ReadDataBit write WriteDataBit;
    property StatusBit[const nr: byte]: TBit read ReadStatusBit write WriteStatusBit;
    property ControlBit[const nr: byte]: TBit read ReadControlBit write WriteControlBit;
    procedure ClearAllPorts;
  end;

implementation

    procedure PortOut(Port : Word; Data : Byte); stdcall; external 'io.dll';
    //procedure PortWordOut(Port : Word; Data : Word); stdcall; external 'io.dll';
    //procedure PortDWordOut(Port : Word; Data : DWord); stdcall; external 'io.dll';
    function PortIn(Port : Word) : Byte; stdcall; external 'io.dll';
    //function PortWordIn(Port : Word) : Word; stdcall; external 'io.dll';
    //function PortDWordIn(Port : Word) : DWord; stdcall; external 'io.dll';
    procedure SetPortBit(Port : Word; Bit : Byte); stdcall; external 'io.dll';
    procedure ClrPortBit(Port : Word; Bit : Byte); stdcall; external 'io.dll';
    //procedure NotPortBit(Port : Word; Bit : Byte); stdcall; external 'io.dll';
    function GetPortBit(Port : Word; Bit : Byte) : WordBool; stdcall; external 'io.dll';
    //function RightPortShift(Port : Word; Val : WordBool) : WordBool; stdcall; external 'io.dll';
    //function LeftPortShift(Port : Word; Val : WordBool) : WordBool; stdcall; external 'io.dll';
    function IsDriverInstalled : Boolean; stdcall; external 'io.dll';

constructor TParPort.create(BaseAddress: word);
begin
FDataAddress:=BaseAddress;
FStatusAddress:=BaseAddress+1;
FControlAddress:=BaseAddress+2;
end;

function TParPort.WordBoolToBit(b: WordBool): TBit;
begin
if b then Result:=1 else Result:=0;
end;


function TParPort.CheckDriver: boolean;
begin
Result:=IsDriverInstalled;
end;

procedure TParPort.WriteDataByte(const val: byte);
begin
PortOut(FDataAddress,val);
end;

procedure TParPort.WriteDataBit(const bit: byte; const val: TBit);
begin
if (bit<8) then
  begin
  if (val=1) then SetPortBit(FDataAddress,byte(bit)) else ClrPortBit(FDataAddress,bit);
  end;
end;

procedure TParPort.WriteStatusByte(const val: byte);
begin
PortOut(FStatusAddress,val xor $80);
end;

procedure TParPort.WriteStatusBit(const bit: byte; const val: TBit);
begin
  case bit of
  0..6: if (val=1) then SetPortBit(FStatusAddress,byte(bit)) else ClrPortBit(FStatusAddress,bit);
  7:    if (val=0) then SetPortBit(FStatusAddress,byte(bit)) else ClrPortBit(FStatusAddress,bit);
  else raise Exception.Create('Bit value must be between 0..7, but was: '+IntToStr(bit));
  end;
end;

procedure TParPort.WriteControlByte(const val: byte);
begin
PortOut(FControlAddress,val xor $0B);
end;

procedure TParPort.WriteControlBit(const bit: byte; const val: TBit);
begin
  case bit of
  2,4..7: if (val=1) then SetPortBit(FControlAddress,byte(bit)) else ClrPortBit(FControlAddress,bit);
  0,1,3:  if (val=0) then SetPortBit(FControlAddress,byte(bit)) else ClrPortBit(FControlAddress,bit);
  else raise Exception.Create('Bit value must be between 0..7, but was: '+IntToStr(bit));
  end;
end;

function TParPort.ReadDataByte: byte;
begin
Result:=PortIn(FDataAddress);
end;

function TParPort.ReadDataBit(const bit: byte): TBit;
begin
Result:=WordBoolToBit(GetPortBit(FDataAddress,bit));
end;

function TParPort.ReadStatusByte: byte;
begin
Result:=PortIn(FStatusAddress) xor $80;
end;

function TParPort.ReadStatusBit(const bit: byte): TBit;
var t: WordBool;
begin
t:=(GetPortBit(FStatusAddress,bit));
  case bit of
  0..6: Result:=TBit(WordBoolToBit(t));
  7:    Result:=1-TBit(WordBoolToBit(t));
  else raise Exception.Create('Bit value must be between 0..7, but was: '+IntToStr(bit));
  end;
end;

function TParPort.ReadControlByte: byte;
begin
Result:=PortIn(FControlAddress) xor $0B;
end;

function TParPort.ReadControlBit(const bit: byte): TBit;
begin
  case bit of
  2,4..7: Result:=WordBoolToBit(GetPortBit(FControlAddress,bit));
  0,1,3:  Result:=1-WordBoolToBit(GetPortBit(FControlAddress,bit));
  else raise Exception.Create('Bit value must be between 0..7, but was: '+IntToStr(bit));
  end;
end;

procedure TParPort.ClearAllPorts;
begin
WriteDataByte($00);
WriteStatusByte($00);
WriteControlByte($00);
end;




end.
