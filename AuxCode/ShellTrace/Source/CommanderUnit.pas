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

unit CommanderUnit;

interface

uses SysUtils, Classes, TrivialbusUnit, ColoredListUnit;

type
  TCommander =
  class(TThread)
  private
    FT4: Ttrivialbus;
    FList: TColoredList;
    FProtect: TMultiReadExclusiveWriteSynchronizer;
    FReadStr: string;
    FWriteStr: string;
    FShell: boolean;
    FTrace: boolean;
    FMarkerMinCount: integer;
    FMarkerMaxCount: integer;
    FTimeout: integer;
  protected
    procedure BusTimeOut;
    procedure ReceiveCommand;
  public
    property Trace: boolean read FTrace write FTrace;
    property Shell: boolean read FShell write FShell;
    property MarkerMinCount: integer read FMarkerMinCount write FMarkerMinCount;
    property MarkerMaxCount: integer read FMarkerMaxCount write FMarkerMaxCount;
    property Timeout: integer read FTimeout write FTimeout;
    constructor Create(const T4: Ttrivialbus; const CommandList: TColoredList);
    procedure Execute; override;
    procedure SendCommand(const s: string);
    procedure BlockBus(val: boolean);
  end;

implementation

constructor TCommander.Create(const T4: Ttrivialbus; const CommandList: TColoredList);
begin
inherited Create(true);
Priority:=tpLower;
FProtect:=TMultiReadExclusiveWriteSynchronizer.Create;
FT4:=T4;
FList:=CommandList;
FT4.initBus;
end;


procedure TCommander.sendCommand(const s: string);
begin
FProtect.BeginWrite;
  try
  FWriteStr:=Copy(s,0,Length(s));
  finally
  FProtect.EndWrite;
  end;
FList.writeBlack(s);
end;

procedure TCommander.ReceiveCommand;
var LocalStr: string;
begin
LocalStr:=Copy(FReadStr,0,Length(FReadStr));
FList.writeRed(LocalStr);
end;

procedure TCommander.BusTimeOut;
begin
FList.writeGreen('Bus timout.');
end;

procedure TCommander.Execute;
var timeout: boolean;
begin
timeout := false;
while (not Terminated) do
  begin
  FProtect.BeginWrite;
    try
    if FShell then FT4.talk(FWriteStr,FReadStr,timeout)
    else if FTrace then FT4.trace(FReadStr,self);
    SetLength(FWriteStr,0);
    finally
    FProtect.EndWrite;
    end;
  if timeout then
    begin
    Synchronize(BusTimeOut);
    timeout := false;
    end;
  if (length(FReadStr)>0) then
    begin
    Synchronize(ReceiveCommand);
    SetLength(FReadStr,0);
    end;
  if FTrace then Terminate;
  end;
FT4.clearBuffer;
end;

procedure TCommander.BlockBus(val: boolean);
begin
FT4.BlockBus:=val;
end;

end.
