object Form1: TForm1
  Left = 142
  Top = 142
  Width = 889
  Height = 571
  Caption = 'Femto OS v 0.92 - Communication Programm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel4: TPanel
    Left = 0
    Top = 0
    Width = 680
    Height = 544
    Align = alClient
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 0
    object Panel5: TPanel
      Left = 2
      Top = 514
      Width = 676
      Height = 28
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 0
      DesignSize = (
        676
        28)
      object InputEdit: TEdit
        Left = 4
        Top = 4
        Width = 668
        Height = 23
        Anchors = [akLeft, akTop, akRight]
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Fixedsys'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnKeyDown = InputEditKeyDown
      end
    end
    object Panel6: TPanel
      Left = 2
      Top = 2
      Width = 676
      Height = 512
      Align = alClient
      BevelOuter = bvNone
      BorderWidth = 4
      TabOrder = 1
      object OutputEdit: TRichEdit
        Left = 4
        Top = 4
        Width = 668
        Height = 504
        Align = alClient
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Fixedsys'
        Font.Style = []
        HideScrollBars = False
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
  end
  object Panel8: TPanel
    Left = 680
    Top = 0
    Width = 201
    Height = 544
    Align = alRight
    BevelOuter = bvNone
    BorderWidth = 2
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 97
      Height = 97
      Caption = 'Base Port'
      TabOrder = 0
      object Port278: TRadioButton
        Left = 16
        Top = 16
        Width = 73
        Height = 17
        Caption = '0x0278'
        TabOrder = 0
        OnClick = Port278Click
      end
      object Port378: TRadioButton
        Left = 16
        Top = 40
        Width = 73
        Height = 17
        Caption = '0x0378'
        Checked = True
        TabOrder = 1
        TabStop = True
        OnClick = Port378Click
      end
      object Port3BC: TRadioButton
        Left = 16
        Top = 64
        Width = 73
        Height = 17
        Caption = '0x03BC'
        TabOrder = 2
        OnClick = Port3BCClick
      end
    end
    object GroupBox2: TGroupBox
      Left = 104
      Top = 0
      Width = 97
      Height = 97
      Caption = 'Port'
      TabOrder = 1
      object DataBtn: TRadioButton
        Left = 16
        Top = 16
        Width = 73
        Height = 17
        Caption = 'Data'
        Checked = True
        TabOrder = 0
        TabStop = True
      end
      object StatusBtn: TRadioButton
        Left = 16
        Top = 40
        Width = 73
        Height = 17
        Caption = 'Status'
        TabOrder = 1
      end
      object ControlBtn: TRadioButton
        Left = 16
        Top = 64
        Width = 73
        Height = 17
        Caption = 'Control'
        TabOrder = 2
      end
    end
    object Panel1: TPanel
      Left = 0
      Top = 104
      Width = 201
      Height = 73
      BevelInner = bvRaised
      BevelOuter = bvLowered
      TabOrder = 2
      object Led4: TShape
        Left = 80
        Top = 8
        Width = 17
        Height = 17
        Brush.Color = clGray
        Shape = stCircle
        OnContextPopup = Led4ContextPopup
      end
      object Led3: TShape
        Left = 104
        Top = 8
        Width = 17
        Height = 17
        Brush.Color = clGray
        Shape = stCircle
        OnContextPopup = Led3ContextPopup
      end
      object Led0: TShape
        Left = 176
        Top = 8
        Width = 17
        Height = 17
        Brush.Color = clGray
        Shape = stCircle
        OnContextPopup = Led0ContextPopup
      end
      object Led2: TShape
        Left = 128
        Top = 8
        Width = 17
        Height = 17
        Brush.Color = clGray
        Shape = stCircle
        OnContextPopup = Led2ContextPopup
      end
      object Led1: TShape
        Left = 152
        Top = 8
        Width = 17
        Height = 17
        Brush.Color = clGray
        Shape = stCircle
        OnContextPopup = Led1ContextPopup
      end
      object Led7: TShape
        Left = 8
        Top = 8
        Width = 17
        Height = 17
        Brush.Color = clGray
        Shape = stCircle
        OnContextPopup = Led7ContextPopup
      end
      object Led6: TShape
        Left = 32
        Top = 8
        Width = 17
        Height = 17
        Brush.Color = clGray
        Shape = stCircle
        OnContextPopup = Led6ContextPopup
      end
      object Led5: TShape
        Left = 56
        Top = 8
        Width = 17
        Height = 17
        Brush.Color = clGray
        Shape = stCircle
        OnContextPopup = Led5ContextPopup
      end
      object WriteBtn: TButton
        Left = 16
        Top = 40
        Width = 73
        Height = 25
        Caption = 'Write Byte'
        TabOrder = 0
        OnClick = WriteBtnClick
      end
      object ReadBtn: TButton
        Left = 112
        Top = 40
        Width = 75
        Height = 25
        Caption = 'Read Byte'
        TabOrder = 1
        OnClick = ReadBtnClick
      end
    end
    object Panel3: TPanel
      Left = 0
      Top = 184
      Width = 201
      Height = 89
      BevelInner = bvRaised
      BevelOuter = bvLowered
      TabOrder = 3
      object Label1: TLabel
        Left = 16
        Top = 48
        Width = 27
        Height = 13
        Caption = 'Bit nr:'
      end
      object Bit0: TButton
        Left = 112
        Top = 8
        Width = 75
        Height = 25
        Caption = 'Clear Bit'
        TabOrder = 0
        OnClick = Bit0Click
      end
      object Bit1: TButton
        Left = 16
        Top = 8
        Width = 75
        Height = 25
        Caption = 'Set Bit'
        TabOrder = 1
        OnClick = Bit1Click
      end
      object SpinEdit: TEdit
        Left = 56
        Top = 48
        Width = 33
        Height = 21
        TabOrder = 2
        Text = '0'
      end
      object SpinBtn: TSpinButton
        Left = 112
        Top = 48
        Width = 20
        Height = 25
        DownGlyph.Data = {
          0E010000424D0E01000000000000360000002800000009000000060000000100
          200000000000D800000000000000000000000000000000000000008080000080
          8000008080000080800000808000008080000080800000808000008080000080
          8000008080000080800000808000000000000080800000808000008080000080
          8000008080000080800000808000000000000000000000000000008080000080
          8000008080000080800000808000000000000000000000000000000000000000
          0000008080000080800000808000000000000000000000000000000000000000
          0000000000000000000000808000008080000080800000808000008080000080
          800000808000008080000080800000808000}
        TabOrder = 3
        UpGlyph.Data = {
          0E010000424D0E01000000000000360000002800000009000000060000000100
          200000000000D800000000000000000000000000000000000000008080000080
          8000008080000080800000808000008080000080800000808000008080000080
          8000000000000000000000000000000000000000000000000000000000000080
          8000008080000080800000000000000000000000000000000000000000000080
          8000008080000080800000808000008080000000000000000000000000000080
          8000008080000080800000808000008080000080800000808000000000000080
          8000008080000080800000808000008080000080800000808000008080000080
          800000808000008080000080800000808000}
        OnDownClick = SpinBtnDownClick
        OnUpClick = SpinBtnUpClick
      end
    end
    object Panel2: TPanel
      Left = 0
      Top = 280
      Width = 201
      Height = 41
      BevelInner = bvRaised
      BevelOuter = bvLowered
      TabOrder = 4
      object DriverLed: TShape
        Left = 144
        Top = 8
        Width = 25
        Height = 25
        Brush.Color = clGray
        Shape = stCircle
        OnContextPopup = Led0ContextPopup
      end
      object CheckBtn: TButton
        Left = 8
        Top = 8
        Width = 105
        Height = 25
        Caption = 'Check Driver'
        TabOrder = 0
        OnClick = CheckBtnClick
      end
    end
    object Panel7: TPanel
      Left = 0
      Top = 325
      Width = 201
      Height = 33
      BevelInner = bvRaised
      BevelOuter = bvLowered
      TabOrder = 5
      object StartButton: TButton
        Left = 6
        Top = 4
        Width = 91
        Height = 25
        Caption = 'Start bus'
        TabOrder = 0
        OnClick = StartButtonClick
      end
      object StopBtn: TButton
        Left = 102
        Top = 4
        Width = 91
        Height = 25
        Caption = 'Stop bus'
        TabOrder = 1
        OnClick = StopBtnClick
      end
    end
    object Panel9: TPanel
      Left = 0
      Top = 362
      Width = 201
      Height = 33
      BevelInner = bvRaised
      BevelOuter = bvLowered
      TabOrder = 6
      object BlockBusBox: TCheckBox
        Left = 8
        Top = 8
        Width = 97
        Height = 17
        Caption = 'BlockBusBox'
        TabOrder = 0
        OnClick = BlockBusBoxClick
      end
    end
    object AppTypePanel: TPanel
      Left = 0
      Top = 400
      Width = 201
      Height = 57
      BevelInner = bvRaised
      BevelOuter = bvLowered
      TabOrder = 7
      object ShellRadio: TRadioButton
        Left = 8
        Top = 8
        Width = 57
        Height = 17
        Caption = 'Shell'
        Checked = True
        TabOrder = 0
        TabStop = True
      end
      object TraceRadio: TRadioButton
        Left = 8
        Top = 32
        Width = 57
        Height = 17
        Caption = 'Trace'
        TabOrder = 1
      end
    end
    object Panel10: TPanel
      Left = 0
      Top = 464
      Width = 201
      Height = 81
      BevelInner = bvRaised
      BevelOuter = bvLowered
      TabOrder = 8
      object Label2: TLabel
        Left = 8
        Top = 10
        Width = 81
        Height = 13
        Caption = 'Start after marker'
      end
      object Label3: TLabel
        Left = 8
        Top = 58
        Width = 77
        Height = 13
        Caption = 'Stop after timout'
      end
      object Label4: TLabel
        Left = 8
        Top = 34
        Width = 81
        Height = 13
        Caption = 'Stop after marker'
      end
      object MinCountEdit: TEdit
        Left = 104
        Top = 8
        Width = 57
        Height = 21
        TabOrder = 0
        Text = '0'
      end
      object TimeoutEdit: TEdit
        Left = 104
        Top = 56
        Width = 57
        Height = 21
        TabOrder = 1
        Text = '0'
      end
      object MaxCountEdit: TEdit
        Left = 104
        Top = 32
        Width = 57
        Height = 21
        TabOrder = 2
        Text = '0'
      end
    end
  end
end
