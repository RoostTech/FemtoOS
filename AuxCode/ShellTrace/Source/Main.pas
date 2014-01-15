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

unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, TrivialbusUnit, ParPort, CommanderUnit, ColoredListUnit,
  ExtCtrls, Spin, ComCtrls;

type
  TForm1 = class(TForm)
    Panel4: TPanel;
    Panel5: TPanel;
    InputEdit: TEdit;
    Panel6: TPanel;
    OutputEdit: TRichEdit;
    Panel8: TPanel;
    GroupBox1: TGroupBox;
    Port278: TRadioButton;
    Port378: TRadioButton;
    Port3BC: TRadioButton;
    GroupBox2: TGroupBox;
    DataBtn: TRadioButton;
    StatusBtn: TRadioButton;
    ControlBtn: TRadioButton;
    Panel1: TPanel;
    Led4: TShape;
    Led3: TShape;
    Led0: TShape;
    Led2: TShape;
    Led1: TShape;
    Led7: TShape;
    Led6: TShape;
    Led5: TShape;
    WriteBtn: TButton;
    ReadBtn: TButton;
    Panel3: TPanel;
    Label1: TLabel;
    Bit0: TButton;
    Bit1: TButton;
    SpinEdit: TEdit;
    SpinBtn: TSpinButton;
    Panel2: TPanel;
    DriverLed: TShape;
    CheckBtn: TButton;
    Panel7: TPanel;
    StartButton: TButton;
    StopBtn: TButton;
    Panel9: TPanel;
    BlockBusBox: TCheckBox;
    AppTypePanel: TPanel;
    ShellRadio: TRadioButton;
    TraceRadio: TRadioButton;
    Panel10: TPanel;
    Label2: TLabel;
    MinCountEdit: TEdit;
    Label3: TLabel;
    TimeoutEdit: TEdit;
    Label4: TLabel;
    MaxCountEdit: TEdit;
    procedure CheckBtnClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure Led7ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
    procedure Led6ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
    procedure Led5ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
    procedure Led4ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
    procedure Led3ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
    procedure Led2ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
    procedure Led1ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
    procedure Led0ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
    procedure WriteBtnClick(Sender: TObject);
    procedure Port278Click(Sender: TObject);
    procedure Port378Click(Sender: TObject);
    procedure Port3BCClick(Sender: TObject);
    procedure ReadBtnClick(Sender: TObject);
    procedure Bit0Click(Sender: TObject);
    procedure Bit1Click(Sender: TObject);
    procedure SpinBtnDownClick(Sender: TObject);
    procedure SpinBtnUpClick(Sender: TObject);
    procedure StartButtonClick(Sender: TObject);
    procedure StopBtnClick(Sender: TObject);
    procedure InputEditKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure BlockBusBoxClick(Sender: TObject);
  private
    FT4: Ttrivialbus;
    FParport: TParPort;
    FColoredList: TColoredList;
    FCommander: TCommander;
    FLed: array[0..7] of boolean;
    FCurrentCommand: integer;
    FHistory: TStringList;
    function BoolToByte(const b: boolean): byte;
  protected
    procedure setLed(const nr: integer; const val: boolean);
    function getLed(const nr: integer): boolean;
    procedure setTransfer(const val: byte);
    function getTransfer: byte;
  public
   property Led[const nr: integer]: boolean read getLed write setLed;
   property Transfer: byte read getTransfer write setTransfer;
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

function TForm1.BoolToByte(const b: boolean): byte;
begin
if b then Result:=1 else Result:=0;
end;

procedure TForm1.setLed(const nr: integer; const val: boolean);
var col: TColor;
begin
FLed[nr]:=val;
if val then col:=clRed else col:=clGray;
  case nr of
  0: Led0.Brush.Color:=col;
  1: Led1.Brush.Color:=col;
  2: Led2.Brush.Color:=col;
  3: Led3.Brush.Color:=col;
  4: Led4.Brush.Color:=col;
  5: Led5.Brush.Color:=col;
  6: Led6.Brush.Color:=col;
  7: Led7.Brush.Color:=col;
  end;
end;

function TForm1.getLed(const nr: integer): boolean;
begin
Result:=FLed[nr];
end;

procedure TForm1.CheckBtnClick(Sender: TObject);
begin
if FParPort.CheckDriver then DriverLed.Brush.Color:=clGreen else DriverLed.Brush.Color:=clRed;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
FParport:=TParPort.create(888);
Port378Click(Sender);
FT4:=Ttrivialbus.Create(FParport);
FColoredList:=TColoredList.Create(OutputEdit);
FHistory:=TStringList.Create;
FHistory.Add('');
end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
FParPort.free;
FHistory.free;
end;

procedure TForm1.Led7ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
begin
Led[7]:=not Led[7];
end;

procedure TForm1.Led6ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
begin
Led[6]:=not Led[6];
end;

procedure TForm1.Led5ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
begin
Led[5]:=not Led[5];
end;

procedure TForm1.Led4ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
begin
Led[4]:=not Led[4];
end;

procedure TForm1.Led3ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
begin
Led[3]:=not Led[3];
end;

procedure TForm1.Led2ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
begin
Led[2]:=not Led[2];
end;

procedure TForm1.Led1ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
begin
Led[1]:=not Led[1];
end;

procedure TForm1.Led0ContextPopup(Sender: TObject; MousePos: TPoint; var Handled: Boolean);
begin
Led[0]:=not Led[0];
end;

procedure TForm1.setTransfer(const val: byte);
var i: integer;
begin
for i:=0 to 7 do Led[i] := ((val shr i) and $01) = 1;
end;

function TForm1.getTransfer: byte;
var i: integer;
begin
Result:=0;
for i:=0 to 7 do Result:=Result or (BoolToByte(Led[i]) shl i)
end;

procedure TForm1.Port278Click(Sender: TObject);
begin
FParport.create(632);
end;

procedure TForm1.Port378Click(Sender: TObject);
begin
FParport.create(888);
end;

procedure TForm1.Port3BCClick(Sender: TObject);
begin
FParport.create(956);
end;

procedure TForm1.ReadBtnClick(Sender: TObject);
begin
if DataBtn.Checked    then setTransfer(FParport.DataByte);
if StatusBtn.Checked  then setTransfer(FParport.StatusByte);
if ControlBtn.Checked then setTransfer(FParport.ControlByte);
end;

procedure TForm1.WriteBtnClick(Sender: TObject);
begin
FParport.DataByte:=getTransfer;
if DataBtn.Checked    then FParport.DataByte:=getTransfer;
if StatusBtn.Checked  then FParport.StatusByte:=getTransfer;
if ControlBtn.Checked then FParport.ControlByte:=getTransfer;
end;

procedure TForm1.Bit0Click(Sender: TObject);
var bit: shortint;
begin
bit:=StrToInt(SpinEdit.Text);
if DataBtn.Checked    then FParport.DataBit[bit]:=0;
if StatusBtn.Checked  then FParport.StatusBit[bit]:=0;
if ControlBtn.Checked then FParport.ControlBit[bit]:=0;
end;

procedure TForm1.Bit1Click(Sender: TObject);
var bit: shortint;
begin
bit:=StrToInt(SpinEdit.Text);
if DataBtn.Checked    then FParport.DataBit[bit]:=1;
if StatusBtn.Checked  then FParport.StatusBit[bit]:=1;
if ControlBtn.Checked then FParport.ControlBit[bit]:=1;
end;

procedure TForm1.SpinBtnDownClick(Sender: TObject);
begin
SpinEdit.Text:=IntToStr(StrToInt(SpinEdit.Text)-1);
end;

procedure TForm1.SpinBtnUpClick(Sender: TObject);
begin
SpinEdit.Text:=IntToStr(StrToInt(SpinEdit.Text)+1);
end;

procedure TForm1.StartButtonClick(Sender: TObject);
begin
FCommander:=TCommander.Create(FT4,FColoredList);
FColoredList.writeGreen('Bus started');
AppTypePanel.Enabled:=false;
FCommander.Shell:=ShellRadio.Checked;
FCommander.Trace:=TraceRadio.Checked;
FCommander.MarkerMinCount:=StrToIntDef(MinCountEdit.Text,0);
FCommander.MarkerMaxCount:=StrToIntDef(MaxCountEdit.Text,0);
FCommander.Timeout:=StrToIntDef(TimeoutEdit.Text,0);
FCommander.Resume;
end;

procedure TForm1.StopBtnClick(Sender: TObject);
begin
FColoredList.writeGreen('Bus terminating ...');
FCommander.Terminate;
FCommander.WaitFor;
AppTypePanel.Enabled:=true;
FColoredList.writeGreen('... done.');
end;

procedure TForm1.InputEditKeyDown(Sender: TObject; var Key: Word;  Shift: TShiftState);
var LocStr: string;
begin
LocStr:=' ';
if Key=VK_RETURN then
  begin
  if (FHistory.Count<2) or (FHistory[FHistory.Count-2]<>InputEdit.Text) then
    begin
    FHistory[FHistory.Count-1]:=InputEdit.Text;
    FHistory.Add('');
    end;
  //FHistory[FHistory.Count-1]:=InputEdit.Text;
  FCommander.SendCommand(InputEdit.Text);
  InputEdit.Text:='';
  //FHistory.Add('');
  FCurrentCommand:=FHistory.Count-1;
  end
else if Key=VK_UP then
  begin
  if (FCurrentCommand=FHistory.Count-1) then FHistory[FHistory.Count-1]:=InputEdit.Text;
  if  (FCurrentCommand>0) then dec(FCurrentCommand);
  InputEdit.Text := FHistory[FCurrentCommand];
  end
else if Key=VK_DOWN then
  begin
  if  (FCurrentCommand<FHistory.Count-1) then
    begin
    inc(FCurrentCommand);
    InputEdit.Text := FHistory[FCurrentCommand];
    end;
  end
end;

procedure TForm1.BlockBusBoxClick(Sender: TObject);
begin
FCommander.BlockBus(BlockBusBox.Checked);
end;

end.
