inherited frmStorageNote: TfrmStorageNote
  Caption = #20837#24211#21333#26684#24335
  ClientHeight = 279
  ClientWidth = 564
  Position = poDefault
  ExplicitWidth = 572
  ExplicitHeight = 313
  DesignSize = (
    564
    279)
  PixelsPerInch = 96
  TextHeight = 13
  object RzGroupBox1: TRzGroupBox [0]
    Left = 0
    Top = 3
    Width = 194
    Height = 266
    Anchors = [akLeft, akTop, akBottom]
    BorderSides = [sdLeft, sdTop, sdBottom]
    Caption = #36873#25321#24744#38656#35201#35774#32622#30340#24215#21517
    TabOrder = 0
    object ListBox1: TListBox
      Left = 3
      Top = 26
      Width = 183
      Height = 225
      ItemHeight = 13
      TabOrder = 0
      OnClick = ListBox1Click
      OnDblClick = ListBox1DblClick
      OnKeyPress = ListBox1KeyPress
    end
  end
  object rzgrpbx1: TRzGroupBox [1]
    Left = 200
    Top = 8
    Width = 337
    Height = 270
    Anchors = [akLeft, akBottom]
    BorderSides = [sdLeft, sdTop, sdBottom]
    Caption = #25171#21360#35774#32622
    TabOrder = 1
    object lbl1: TRzLabel
      Left = 15
      Top = 22
      Width = 48
      Height = 13
      Caption = #21333#25454#26631#39064
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object edtStorageNoteTitle: TRzDBEdit
      Left = 81
      Top = 19
      Width = 216
      Height = 21
      DataSource = dsNotePrint
      DataField = 'StorageNoteTitle'
      TabOrder = 0
    end
    object RzDBCheckBox1: TRzDBCheckBox
      Left = 14
      Top = 46
      Width = 43
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #24207#21495
      TabOrder = 1
    end
    object CHKBarcode: TRzDBCheckBox
      Left = 229
      Top = 46
      Width = 43
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #26465#30721
      TabOrder = 2
    end
    object CHKPrice: TRzDBCheckBox
      Left = 229
      Top = 88
      Width = 43
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #23450#20215
      TabOrder = 3
    end
    object CHKBookName: TRzDBCheckBox
      Left = 14
      Top = 88
      Width = 43
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #20070#21517
      TabOrder = 4
    end
    object CHKISBN: TRzDBCheckBox
      Left = 14
      Top = 67
      Width = 42
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = 'ISBN'
      TabOrder = 5
    end
    object CHKCatalog: TRzDBCheckBox
      Left = 229
      Top = 67
      Width = 55
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #33258#32534#21495
      TabOrder = 6
    end
    object CHKPress: TRzDBCheckBox
      Left = 14
      Top = 151
      Width = 55
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #20986#29256#31038
      TabOrder = 7
    end
    object CHKFixedPrice: TRzDBCheckBox
      Left = 229
      Top = 151
      Width = 43
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #30721#27915
      TabOrder = 8
    end
    object CHKCategory: TRzDBCheckBox
      Left = 229
      Top = 130
      Width = 43
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #31867#21035
      TabOrder = 9
    end
    object CHKPublicDate: TRzDBCheckBox
      Left = 14
      Top = 130
      Width = 67
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #20986#29256#26085#26399
      TabOrder = 10
    end
    object CHKRevision: TRzDBCheckBox
      Left = 229
      Top = 109
      Width = 43
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #29256#27425
      TabOrder = 11
    end
    object CHKAuthor: TRzDBCheckBox
      Left = 14
      Top = 109
      Width = 43
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #20316#32773
      TabOrder = 12
    end
    object CHKDiscountedPrice: TRzDBCheckBox
      Left = 14
      Top = 172
      Width = 43
      Height = 15
      DataSource = dsNotePrint
      ValueChecked = '1'
      ValueUnchecked = '0'
      Caption = #23454#27915
      TabOrder = 13
    end
    object btn1: TButton
      Left = 15
      Top = 208
      Width = 75
      Height = 25
      Caption = #20445#23384'[S]'
      TabOrder = 14
      OnClick = btn1Click
    end
    object btn2: TRzButton
      Left = 136
      Top = 207
      Caption = #36864#20986'[ESC]'
      TabOrder = 15
      OnClick = btn2Click
    end
  end
  object qryStorageName: TADOQuery
    Parameters = <>
    Left = 57
    Top = 24
  end
  object DataSource1: TDataSource
    DataSet = qryStorageName
    Left = 57
    Top = 64
  end
  object dsetStorageNote: TADODataSet
    DataSource = DataSource1
    Parameters = <>
    Left = 168
    Top = 24
  end
  object dsNotePrint: TDataSource
    DataSet = dsetStorageNote
    Left = 160
    Top = 80
  end
end
