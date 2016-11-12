object frmRetailNote: TfrmRetailNote
  Left = 0
  Top = 0
  Caption = 'frmRetailNote'
  ClientHeight = 276
  ClientWidth = 648
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDesigned
  Visible = True
  OnClose = FormClose
  DesignSize = (
    648
    276)
  PixelsPerInch = 96
  TextHeight = 13
  object RzGroupBox4: TRzGroupBox
    Left = 184
    Top = 14
    Width = 456
    Height = 254
    Anchors = [akLeft, akBottom]
    BorderSides = [sdLeft, sdTop, sdRight]
    Caption = #25171#21360#35774#32622
    TabOrder = 0
    object RzLabel2: TRzLabel
      Left = 6
      Top = 22
      Width = 48
      Height = 13
      Caption = #21333#25454#26631#39064
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLine2: TRzLine
      Left = 6
      Top = 41
      Width = 419
      Height = 20
    end
    object RzLabel1: TRzLabel
      Left = 6
      Top = 62
      Width = 48
      Height = 13
      Caption = #27426'  '#36814'  '#35789
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel3: TRzLabel
      Left = 214
      Top = 61
      Width = 48
      Height = 13
      Caption = #22320'        '#22336
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel4: TRzLabel
      Left = 6
      Top = 89
      Width = 48
      Height = 13
      Caption = #32852#31995#30005#35805
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel5: TRzLabel
      Left = 214
      Top = 89
      Width = 48
      Height = 13
      Caption = #22791'        '#27880
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLine1: TRzLine
      Left = 5
      Top = 113
      Width = 444
      Height = 20
    end
    object RzLabel6: TRzLabel
      Left = 14
      Top = 139
      Width = 92
      Height = 13
      Caption = 'POS'#25171#21360#36830#25509#31471#21475
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel7: TRzLabel
      Left = 17
      Top = 168
      Width = 60
      Height = 13
      Caption = #21333#25454#21015#35774#32622
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl1: TRzLabel
      Left = 14
      Top = 195
      Width = 342
      Height = 13
      Caption = #28201#39336#25552#31034#65306#25152#36873#39033#30446#35831#19981#35201#36229#36807'4'#20010#65292#21542#21017#23558#20250#24433#21709#23567#31080#25171#21360#32654#35266
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object dbedtTitle: TRzDBEdit
      Left = 60
      Top = 19
      Width = 129
      Height = 21
      DataSource = dsNotePrint
      TabOrder = 0
    end
    object dbedtWelcomeMessage: TRzDBEdit
      Left = 60
      Top = 59
      Width = 129
      Height = 21
      DataSource = dsNotePrint
      TabOrder = 1
    end
    object dbedtAddress: TRzDBEdit
      Left = 292
      Top = 58
      Width = 129
      Height = 21
      DataSource = dsNotePrint
      TabOrder = 2
    end
    object dbedtTel: TRzDBEdit
      Left = 60
      Top = 86
      Width = 129
      Height = 21
      DataSource = dsNotePrint
      TabOrder = 3
    end
    object dbedtRemarks: TRzDBEdit
      Left = 292
      Top = 85
      Width = 129
      Height = 21
      DataSource = dsNotePrint
      TabOrder = 4
    end
    object dbcbbPort: TRzDBComboBox
      Left = 116
      Top = 134
      Width = 85
      Height = 21
      DataSource = dsNotePrint
      ItemHeight = 13
      TabOrder = 5
      Items.Strings = (
        'LPT1'
        'COM1'
        'COM2')
      Values.Strings = (
        '1'
        '2'
        '3')
    end
    object CHKPrice: TRzDBCheckBox
      Left = 219
      Top = 166
      Width = 43
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #23450#20215
      TabOrder = 6
    end
    object CHKISBN: TRzDBCheckBox
      Left = 83
      Top = 166
      Width = 42
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = 'ISBN'
      TabOrder = 7
    end
    object CHKBookName: TRzDBCheckBox
      Left = 146
      Top = 166
      Width = 43
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #20070#21517
      TabOrder = 8
    end
    object CHKDiscount: TRzDBCheckBox
      Left = 299
      Top = 166
      Width = 43
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #25240#25187
      TabOrder = 9
    end
    object btn1: TButton
      Left = 14
      Top = 214
      Width = 65
      Height = 24
      Caption = #20445#23384
      TabOrder = 10
      OnClick = btn1Click
    end
    object btn2: TButton
      Left = 166
      Top = 214
      Width = 65
      Height = 24
      Caption = #25171#21360#27979#35797
      TabOrder = 11
      OnClick = btn2Click
    end
  end
  object RzGroupBox1: TRzGroupBox
    Left = -1
    Top = 8
    Width = 175
    Height = 260
    Anchors = [akLeft, akTop, akBottom]
    BorderSides = [sdLeft, sdTop, sdBottom]
    Caption = #36873#25321#24744#38656#35201#35774#32622#30340#24215#21517
    TabOrder = 1
    object LBRetailNote: TListBox
      Left = 6
      Top = 15
      Width = 163
      Height = 218
      ItemHeight = 13
      TabOrder = 0
      OnClick = LBRetailNoteClick
      OnDblClick = LBRetailNoteDblClick
      OnKeyPress = LBRetailNoteKeyPress
    end
  end
  object qryRetailNoteName: TADOQuery
    Parameters = <>
    Left = 89
    Top = 24
  end
  object Ds1: TDataSource
    Left = 81
    Top = 72
  end
  object dsNotePrint: TDataSource
    DataSet = dsetRetailNote
    Left = 120
    Top = 112
  end
  object dsetRetailNote: TADODataSet
    Parameters = <>
    Left = 72
    Top = 128
  end
  object ds2: TDataSource
    DataSet = dsPrint
    Left = 408
    Top = 120
  end
  object dsPrint: TADODataSet
    Parameters = <>
    Left = 440
    Top = 120
  end
  object dsretail: TADODataSet
    Parameters = <>
    Left = 544
    Top = 144
  end
  object ds4: TDataSource
    DataSet = dsretail
    Left = 512
    Top = 144
  end
end
