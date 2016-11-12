object frmlock: Tfrmlock
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #38145#23450
  ClientHeight = 266
  ClientWidth = 399
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object SpeedButton1: TSpeedButton
    Left = 310
    Top = 223
    Width = 81
    Height = 26
    Caption = #21462#28040
    OnClick = SpeedButton1Click
  end
  object SpeedButton2: TSpeedButton
    Left = 209
    Top = 223
    Width = 81
    Height = 26
    Caption = #20445#23384
    OnClick = SpeedButton2Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 377
    Height = 65
    Caption = #20379#24212#21830
    TabOrder = 0
    object sadd: TCheckBox
      Left = 32
      Top = 29
      Width = 105
      Height = 17
      Caption = #28155#21152#38145#23450
      TabOrder = 0
    end
    object smodify: TCheckBox
      Left = 137
      Top = 29
      Width = 97
      Height = 17
      Caption = #20462#25913#38145#23450
      TabOrder = 1
    end
    object sdel: TCheckBox
      Left = 248
      Top = 29
      Width = 97
      Height = 17
      Caption = #21024#38500#38145#23450
      TabOrder = 2
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 71
    Width = 377
    Height = 74
    Caption = #23458#25143
    TabOrder = 1
    object cadd: TCheckBox
      Left = 32
      Top = 27
      Width = 97
      Height = 17
      Caption = #28155#21152#38145#23450
      TabOrder = 0
    end
    object cmodify: TCheckBox
      Left = 137
      Top = 32
      Width = 97
      Height = 17
      Caption = #20462#25913#38145#23450
      TabOrder = 1
    end
    object cdel: TCheckBox
      Left = 248
      Top = 32
      Width = 97
      Height = 17
      Caption = #21024#38500#38145#23450
      TabOrder = 2
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 141
    Width = 377
    Height = 76
    Caption = #20070#30446
    TabOrder = 2
    object badd: TCheckBox
      Left = 32
      Top = 33
      Width = 97
      Height = 17
      Caption = #28155#21152#38145#23450
      TabOrder = 0
    end
    object bmodify: TCheckBox
      Left = 135
      Top = 31
      Width = 97
      Height = 17
      Caption = #20462#25913#38145#23450
      TabOrder = 1
    end
    object bdel: TCheckBox
      Left = 248
      Top = 31
      Width = 97
      Height = 17
      Caption = #21024#38500#38145#23450
      TabOrder = 2
    end
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 96
    Top = 232
  end
end
