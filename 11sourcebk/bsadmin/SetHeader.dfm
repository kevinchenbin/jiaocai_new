object frmSetHeader: TfrmSetHeader
  Left = 0
  Top = 0
  Caption = #35774#32622#25171#21360#21333#22836
  ClientHeight = 97
  ClientWidth = 460
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
  object Label1: TLabel
    Left = 40
    Top = 16
    Width = 72
    Height = 13
    Caption = #36755#20837#21333#22836#21517#31216
  end
  object edheadername: TEdit
    Left = 128
    Top = 13
    Width = 297
    Height = 21
    TabOrder = 0
  end
  object Btok: TButton
    Left = 152
    Top = 56
    Width = 75
    Height = 25
    Caption = #30830#23450
    TabOrder = 1
    OnClick = BtokClick
  end
  object btconcel: TButton
    Left = 264
    Top = 56
    Width = 75
    Height = 25
    Caption = #21462#28040
    TabOrder = 2
    OnClick = btconcelClick
  end
end
