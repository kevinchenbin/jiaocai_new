object frmkuchenjizhuan: Tfrmkuchenjizhuan
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #24211#23384#32467#36716
  ClientHeight = 192
  ClientWidth = 369
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object SpeedButton1: TSpeedButton
    Left = 200
    Top = 143
    Width = 145
    Height = 41
    Caption = #24320#22987#32467#36716
    OnClick = SpeedButton1Click
  end
  object Label1: TLabel
    Left = 24
    Top = 20
    Width = 24
    Height = 13
    Caption = #22791#27880
  end
  object membk: TMemo
    Left = 54
    Top = 20
    Width = 291
    Height = 120
    TabOrder = 0
  end
  object cn: TADOConnection
    LoginPrompt = False
    Left = 112
    Top = 152
  end
  object aq: TADOQuery
    Connection = cn
    Parameters = <>
    Left = 72
    Top = 152
  end
end
