object frmretaillock: Tfrmretaillock
  Left = 0
  Top = 0
  BorderIcons = [biHelp]
  Caption = #31561#24453
  ClientHeight = 89
  ClientWidth = 278
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
  object Label1: TLabel
    Left = 16
    Top = 24
    Width = 96
    Height = 13
    Caption = #35831#36755#20837#35299#38145#23494#30721#65306
  end
  object edpassword: TEdit
    Left = 110
    Top = 21
    Width = 147
    Height = 21
    TabOrder = 0
    OnKeyPress = edpasswordKeyPress
  end
  object btok: TButton
    Left = 126
    Top = 56
    Width = 75
    Height = 25
    Caption = #30830#23450
    TabOrder = 1
    OnClick = btokClick
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 248
    Top = 64
  end
end
