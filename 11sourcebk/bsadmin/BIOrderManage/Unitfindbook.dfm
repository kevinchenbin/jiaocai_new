object frmfindorderbook: Tfrmfindorderbook
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #26597#20070
  ClientHeight = 89
  ClientWidth = 491
  Color = 16180174
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object sbfind: TSpeedButton
    Left = 376
    Top = 56
    Width = 81
    Height = 25
    Caption = #26597#25214
    Flat = True
    OnClick = sbfindClick
  end
  object cbfindname: TComboBox
    Left = 24
    Top = 24
    Width = 97
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 1
    Text = #20070#21517
    Items.Strings = (
      #20070#21517
      'ISBN'
      #33258#32534#30721
      #20986#29256#31038)
  end
  object editname: TEdit
    Left = 127
    Top = 24
    Width = 330
    Height = 21
    TabOrder = 0
    OnKeyPress = editnameKeyPress
  end
  object ADOQuery1: TADOQuery
    Parameters = <>
    Left = 192
    Top = 64
  end
end
