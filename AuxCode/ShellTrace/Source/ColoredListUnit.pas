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

unit ColoredListUnit;

interface

uses ComCtrls, Graphics;

type
  TColoredList =
  class
  private
    FRichEdit: TRichEdit;
  public
    constructor Create(const RichEdit: TRichEdit);
    procedure writeRed(const s: string);
    procedure writeBlack(const s: string);
    procedure writeGreen(const s: string);
    procedure writeLn;
  end;

implementation

constructor TColoredList.Create(const RichEdit: TRichEdit);
begin
FRichEdit:=RichEdit;
end;

procedure TColoredList.writeRed(const s: string);
begin
FRichEdit.SelAttributes.Color:=clRed;
FRichEdit.Lines.Add(s);
end;

procedure TColoredList.writeBlack(const s: string);
begin
FRichEdit.SelAttributes.Color:=clBlack;
FRichEdit.Lines.Add('>'+s);
end;

procedure TColoredList.writeGreen(const s: string);
begin
FRichEdit.SelAttributes.Color:=clGreen;
FRichEdit.Lines.Add(s);
end;

procedure TColoredList.writeLn;
begin
FRichEdit.Lines.Add('');
end;


end.
