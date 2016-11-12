object frmCbprice: TfrmCbprice
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #25104#26412#35745#31639
  ClientHeight = 126
  ClientWidth = 235
  Color = 16180174
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 17
  object rg: TRadioGroup
    Left = 9
    Top = 8
    Width = 218
    Height = 65
    Items.Strings = (
      #25152#26377#24215#32479#19968#25353#24635#24215#20837#24211#35745#31639#25104#26412
      #27599#20010#24215#21333#29420#25353#27599#20010#24215#20837#24211#35745#31639#25104#26412)
    TabOrder = 0
  end
  object RzButton1: TRzButton
    Left = 152
    Top = 86
    Caption = #35745#31639
    TabOrder = 1
    OnClick = RzButton1Click
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 24
    Top = 88
  end
  object fcon: TADOConnection
    Left = 72
    Top = 88
  end
end
