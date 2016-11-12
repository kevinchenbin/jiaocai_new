object frmQuery: TfrmQuery
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #26597#21333
  ClientHeight = 186
  ClientWidth = 341
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
    Width = 341
    Height = 186
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object Label1: TLabel
      Left = 27
      Top = 22
      Width = 36
      Height = 13
      Caption = #24215#21495#65306
    end
    object Label2: TLabel
      Left = 189
      Top = 60
      Width = 12
      Height = 13
      Caption = #21040
    end
    object spok: TSpeedButton
      Left = 136
      Top = 137
      Width = 73
      Height = 25
      Caption = #30830#23450
      OnClick = spokClick
    end
    object spcancel: TSpeedButton
      Left = 230
      Top = 137
      Width = 73
      Height = 25
      Caption = #21462#28040
      OnClick = spcancelClick
    end
    object Label3: TLabel
      Left = 188
      Top = 96
      Width = 12
      Height = 13
      Caption = #21040
    end
    object cbstore: TComboBox
      Left = 120
      Top = 18
      Width = 183
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      OnChange = cbstoreChange
    end
    object rb1: TRadioButton
      Left = 28
      Top = 60
      Width = 59
      Height = 17
      Caption = #25353#21333#21495
      Checked = True
      TabOrder = 2
      TabStop = True
    end
    object rb2: TRadioButton
      Left = 28
      Top = 95
      Width = 57
      Height = 17
      Caption = #25353#26085#26399
      TabOrder = 3
    end
    object sefrom: TRzSpinEdit
      Left = 86
      Top = 57
      Width = 97
      Height = 21
      AllowKeyEdit = True
      Max = 100000000.000000000000000000
      Min = 1.000000000000000000
      Value = 1.000000000000000000
      TabOrder = 1
      OnKeyPress = sefromKeyPress
    end
    object seto: TRzSpinEdit
      Left = 206
      Top = 57
      Width = 97
      Height = 21
      AllowKeyEdit = True
      Max = 100000000.000000000000000000
      Min = 1.000000000000000000
      Value = 1.000000000000000000
      TabOrder = 4
      OnExit = sefromExit
    end
    object dtfrom: TDateTimePicker
      Left = 86
      Top = 91
      Width = 97
      Height = 21
      Date = 40240.725682800930000000
      Time = 40240.725682800930000000
      TabOrder = 5
      OnExit = dtfromExit
    end
    object dtto: TDateTimePicker
      Left = 206
      Top = 91
      Width = 97
      Height = 21
      Date = 40240.738719375000000000
      Time = 40240.738719375000000000
      TabOrder = 6
      OnExit = dtfromExit
    end
    object editstorehao: TEdit
      Left = 86
      Top = 18
      Width = 33
      Height = 21
      TabOrder = 7
    end
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 304
    Top = 96
  end
end
