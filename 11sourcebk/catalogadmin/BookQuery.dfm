object frmBookQuery: TfrmBookQuery
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #20070#30446#26597#35810
  ClientHeight = 148
  ClientWidth = 427
  Color = 16180174
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 417
    Height = 105
    Caption = #26597#35810#26465#20214
    TabOrder = 0
    object edisbn: TEdit
      Left = 60
      Top = 20
      Width = 133
      Height = 21
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 0
      OnChange = edisbnChange
    end
    object chpress: TCheckBox
      Left = 6
      Top = 77
      Width = 57
      Height = 17
      Caption = #20986#29256#31038
      TabOrder = 1
    end
    object cbpress: TComboBox
      Left = 106
      Top = 75
      Width = 87
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      OnChange = cbpressChange
    end
    object edpress: TEdit
      Left = 60
      Top = 75
      Width = 46
      Height = 21
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 3
      OnKeyPress = edpressKeyPress
    end
    object chtype: TCheckBox
      Left = 213
      Top = 77
      Width = 45
      Height = 17
      Caption = #31867#21035
      TabOrder = 4
    end
    object cbtype: TComboBox
      Left = 311
      Top = 75
      Width = 92
      Height = 21
      ItemHeight = 13
      TabOrder = 5
      OnChange = cbtypeChange
      OnKeyPress = cbtypeKeyPress
    end
    object edtype: TEdit
      Left = 264
      Top = 75
      Width = 46
      Height = 21
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 6
      OnKeyPress = edtypeKeyPress
    end
    object chisbn: TCheckBox
      Left = 6
      Top = 22
      Width = 43
      Height = 17
      Caption = #20070#21495
      TabOrder = 7
    end
    object edname: TEdit
      Left = 261
      Top = 20
      Width = 142
      Height = 21
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 8
      OnChange = ednameChange
    end
    object chname: TCheckBox
      Left = 213
      Top = 22
      Width = 45
      Height = 17
      Caption = #20070#21517
      TabOrder = 9
    end
    object edprice: TEdit
      Left = 60
      Top = 47
      Width = 133
      Height = 21
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 10
      OnChange = edpriceChange
      OnKeyPress = edpriceKeyPress
    end
    object chprice: TCheckBox
      Left = 6
      Top = 49
      Width = 43
      Height = 17
      Caption = #23450#20215
      TabOrder = 11
    end
    object edauthor: TEdit
      Left = 261
      Top = 47
      Width = 142
      Height = 21
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 12
      OnChange = edauthorChange
    end
    object chauthor: TCheckBox
      Left = 213
      Top = 49
      Width = 43
      Height = 17
      Caption = #20316#32773
      TabOrder = 13
    end
  end
  object btOK: TRzButton
    Left = 251
    Top = 119
    Caption = #30830#35748
    ParentColor = True
    TabOrder = 1
    OnClick = btOKClick
  end
  object btConcel: TRzButton
    Left = 344
    Top = 119
    Caption = #21462#28040
    ParentColor = True
    TabOrder = 2
    OnClick = RzButton1Click
  end
  object fcon: TADOConnection
    Left = 344
    Top = 65520
  end
end
