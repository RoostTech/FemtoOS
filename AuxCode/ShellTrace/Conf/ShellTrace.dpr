//
// Femto OS v 0.80 - Copyright (C) 2008  Ruud Vlaming
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

program ShellTrace;

uses
  Forms,
  Main in '..\Source\Main.pas' {Form1},
  ParPort in '..\Source\ParPort.pas',
  TrivialbusUnit in '..\Source\TrivialbusUnit.pas',
  CommanderUnit in '..\Source\CommanderUnit.pas',
  ColoredListUnit in '..\Source\ColoredListUnit.pas',
  Constants in '..\Source\Constants.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.Title := 'ShellTrace';
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
