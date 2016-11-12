object frmsettyperss: Tfrmsettyperss
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #32479#19968#20449#24687
  ClientHeight = 166
  ClientWidth = 473
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 473
    Height = 166
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    ExplicitLeft = -8
    ExplicitWidth = 504
    ExplicitHeight = 322
    object chprice: TCheckBox
      Left = 16
      Top = 57
      Width = 49
      Height = 17
      Caption = #23450#20215
      TabOrder = 0
    end
    object chpress: TCheckBox
      Left = 225
      Top = 57
      Width = 57
      Height = 17
      Caption = #20986#29256#31038
      TabOrder = 1
    end
    object edprice: TEdit
      Left = 72
      Top = 55
      Width = 121
      Height = 21
      TabOrder = 2
      OnChange = edpriceChange
      OnKeyDown = edpriceKeyDown
    end
    object edpress: TEdit
      Left = 281
      Top = 55
      Width = 49
      Height = 21
      TabOrder = 3
      OnKeyPress = edpressKeyPress
    end
    object cbpress: TComboBox
      Left = 330
      Top = 55
      Width = 127
      Height = 21
      ItemHeight = 13
      TabOrder = 4
      OnChange = cbpressChange
    end
    object RzButton1: TRzButton
      Left = 301
      Top = 127
      Caption = #30830#23450
      TabOrder = 5
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 382
      Top = 127
      Caption = #21462#28040
      TabOrder = 6
      OnClick = RzButton2Click
    end
    object chisbn: TCheckBox
      Left = 16
      Top = 24
      Width = 49
      Height = 17
      Caption = 'ISBN'
      TabOrder = 7
    end
    object edisbn: TEdit
      Left = 72
      Top = 22
      Width = 121
      Height = 21
      MaxLength = 13
      TabOrder = 8
      OnChange = edisbnChange
      OnKeyDown = edpriceKeyDown
    end
    object chname: TCheckBox
      Left = 225
      Top = 24
      Width = 49
      Height = 17
      Caption = #20070#21517
      TabOrder = 9
    end
    object edname: TEdit
      Left = 281
      Top = 22
      Width = 176
      Height = 21
      TabOrder = 10
      OnChange = ednameChange
      OnKeyDown = edpriceKeyDown
    end
    object chauthor: TCheckBox
      Left = 16
      Top = 91
      Width = 49
      Height = 17
      Caption = #20316#32773
      TabOrder = 11
    end
    object edauthor: TEdit
      Left = 72
      Top = 89
      Width = 121
      Height = 21
      TabOrder = 12
      OnChange = edauthorChange
      OnKeyDown = edpriceKeyDown
    end
    object chpresscount: TCheckBox
      Left = 225
      Top = 91
      Width = 49
      Height = 17
      Caption = #29256#27425
      TabOrder = 13
    end
    object edpresscount: TEdit
      Left = 281
      Top = 89
      Width = 176
      Height = 21
      TabOrder = 14
      OnChange = edpresscountChange
      OnKeyDown = edpriceKeyDown
    end
  end
  object con: TADOConnection
    Left = 112
    Top = 128
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 56
    Top = 120
  end
end
