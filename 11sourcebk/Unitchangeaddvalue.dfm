object frmchangeaddvalue: Tfrmchangeaddvalue
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #20805#20540#20462#25913
  ClientHeight = 163
  ClientWidth = 414
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 414
    Height = 163
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 16
      Width = 48
      Height = 13
      Caption = #20250#21592#22995#21517
    end
    object Label2: TLabel
      Left = 232
      Top = 16
      Width = 48
      Height = 13
      Caption = #20250#21592#21345#21495
    end
    object Label3: TLabel
      Left = 220
      Top = 51
      Width = 60
      Height = 13
      Caption = #21407#20805#20540#37329#39069
    end
    object Label4: TLabel
      Left = 20
      Top = 89
      Width = 60
      Height = 13
      Caption = #29616#20805#20540#37329#39069
    end
    object Label5: TLabel
      Left = 32
      Top = 51
      Width = 48
      Height = 13
      Caption = #20313'        '#39069
    end
    object edname: TEdit
      Left = 86
      Top = 13
      Width = 115
      Height = 21
      Enabled = False
      TabOrder = 0
    end
    object edcard: TEdit
      Left = 286
      Top = 13
      Width = 115
      Height = 21
      Enabled = False
      TabOrder = 1
    end
    object edyuan: TEdit
      Left = 286
      Top = 48
      Width = 115
      Height = 21
      Enabled = False
      TabOrder = 2
    end
    object ednow: TEdit
      Left = 86
      Top = 86
      Width = 315
      Height = 21
      MaxLength = 10
      TabOrder = 3
    end
    object edyue: TEdit
      Left = 86
      Top = 48
      Width = 115
      Height = 21
      Enabled = False
      TabOrder = 4
    end
    object RzButton1: TRzButton
      Left = 232
      Top = 128
      Caption = #30830#23450
      TabOrder = 5
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 326
      Top = 128
      Caption = #21462#28040
      TabOrder = 6
      OnClick = RzButton2Click
    end
  end
end
