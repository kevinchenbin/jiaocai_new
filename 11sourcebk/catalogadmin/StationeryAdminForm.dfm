inherited frmStationeryAdmin: TfrmStationeryAdmin
  Caption = #25991#20855#31649#29702
  ClientHeight = 461
  ClientWidth = 631
  Font.Charset = ANSI_CHARSET
  ExplicitWidth = 639
  ExplicitHeight = 495
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TRzLabel [0]
    Left = 10
    Top = 35
    Width = 24
    Height = 13
    Caption = #26465#30721
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl2: TRzLabel [1]
    Left = 12
    Top = 55
    Width = 24
    Height = 13
    Caption = #21697#21517
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl3: TRzLabel [2]
    Left = 8
    Top = 92
    Width = 24
    Height = 13
    Caption = #23450#20215
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl4: TRzLabel [3]
    Left = 12
    Top = 159
    Width = 36
    Height = 13
    Caption = #38646#21806#20215
    Visible = False
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl5: TRzLabel [4]
    Left = 12
    Top = 189
    Width = 36
    Height = 13
    Caption = #20250#21592#20215
    Visible = False
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl6: TRzLabel [5]
    Left = 367
    Top = 35
    Width = 28
    Height = 13
    Caption = #21482'/'#30418
    Visible = False
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl7: TRzLabel [6]
    Left = 367
    Top = 92
    Width = 28
    Height = 13
    Caption = #21482'/'#31665
    Visible = False
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl8: TRzLabel [7]
    Left = 232
    Top = 112
    Width = 48
    Height = 13
    Caption = #20876'/'#21253'('#20214')'
    Visible = False
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl9: TRzLabel [8]
    Left = 181
    Top = 160
    Width = 48
    Height = 13
    Caption = #24211#23384#19978#38480
    Visible = False
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl10: TRzLabel [9]
    Left = 181
    Top = 195
    Width = 48
    Height = 13
    Caption = #24211#23384#19979#38480
    Visible = False
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl11: TRzLabel [10]
    Left = 8
    Top = 120
    Width = 24
    Height = 13
    Caption = #31867#21035
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object rztlbr1: TRzToolbar [11]
    Left = 0
    Top = 0
    Width = 631
    Height = 29
    BorderInner = fsNone
    BorderOuter = fsGroove
    BorderSides = [sdTop]
    BorderWidth = 0
    TabOrder = 0
    ToolbarControls = (
      btnExit1
      btnExit2
      btnExit3)
    object btnExit1: TRzToolButton
      Left = 4
      Top = 2
      Width = 68
      ShowCaption = True
      UseToolbarShowCaption = False
      Caption = #28155#21152'[F6]'
      OnClick = btnExit1Click
    end
    object btnExit2: TRzToolButton
      Left = 72
      Top = 2
      Width = 75
      ShowCaption = True
      UseToolbarShowCaption = False
      Caption = #21024#38500'[Del]'
      OnClick = btnExit2Click
    end
    object btnExit3: TRzToolButton
      Left = 147
      Top = 2
      Width = 75
      ShowCaption = True
      UseToolbarShowCaption = False
      Caption = #36864#20986'[Esc]'
      OnClick = btnExit3Click
    end
  end
  object chckbxInput: TRzCheckBox [12]
    Left = 220
    Top = 35
    Width = 67
    Height = 15
    Caption = #36830#32493#36755#20837
    State = cbUnchecked
    TabOrder = 1
  end
  object dbedtBarcode: TRzDBEdit [13]
    Left = 64
    Top = 33
    Width = 121
    Height = 21
    DataSource = dsrcStationery
    DataField = 'Barcode'
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 2
    OnKeyPress = dbedtBarcodeKeyPress
  end
  object dbedtName: TRzDBEdit [14]
    Left = 64
    Top = 61
    Width = 121
    Height = 21
    DataSource = dsrcStationery
    DataField = 'Name_1'
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 3
    OnKeyPress = dbedtNameKeyPress
  end
  object dbedtPrice: TRzDBEdit [15]
    Left = 64
    Top = 89
    Width = 121
    Height = 21
    DataSource = dsrcStationery
    DataField = 'Price'
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 4
    OnKeyPress = dbedtPriceKeyPress
  end
  object dbedt4: TRzDBEdit [16]
    Left = 54
    Top = 152
    Width = 121
    Height = 21
    DataSource = dsrcStationery
    DataField = 'RetailPrice'
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 5
    Visible = False
    OnKeyPress = dbedt4KeyPress
  end
  object dbedt5: TRzDBEdit [17]
    Left = 54
    Top = 184
    Width = 121
    Height = 21
    DataField = 'MemberPrice'
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 6
    Visible = False
    OnKeyPress = dbedt5KeyPress
  end
  object edt1: TRzSpinEdit [18]
    Left = 314
    Top = 35
    Width = 47
    Height = 21
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 7
    Visible = False
  end
  object edt2: TRzSpinEdit [19]
    Left = 314
    Top = 89
    Width = 47
    Height = 21
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 8
    Visible = False
  end
  object edt3: TRzSpinEdit [20]
    Left = 314
    Top = 117
    Width = 47
    Height = 21
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 9
    Visible = False
  end
  object edt4: TRzSpinEdit [21]
    Left = 248
    Top = 157
    Width = 47
    Height = 21
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 10
    Visible = False
  end
  object edt5: TRzSpinEdit [22]
    Left = 248
    Top = 187
    Width = 47
    Height = 21
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 11
    Visible = False
  end
  object rzdbgrdPress1: TRzDBGrid [23]
    Left = 54
    Top = 159
    Width = 433
    Height = 310
    DataSource = dsrcStationery
    DefaultDrawing = True
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    TabOrder = 12
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'Barcode'
        Title.Caption = #26465#30721
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'UserDefCode'
        Title.Caption = #33258#32534#30721
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Name_1'
        Title.Caption = #21697#21517
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Price'
        Title.Caption = #23450#20215
        Visible = True
      end>
  end
  object cbb2: TRzDBLookupComboBox [24]
    Left = 64
    Top = 117
    Width = 65
    Height = 21
    DataField = 'ID'
    DataSource = dsrcStationery
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    KeyField = 'ID'
    ListField = 'Name'
    ListSource = dsrc1
    TabOrder = 13
    OnKeyPress = cbb2KeyPress
  end
  object dbedtUserDefCode: TRzDBEdit [25]
    Left = 207
    Top = 78
    Width = 67
    Height = 21
    DataSource = dsrcStationery
    DataField = 'UserDefCode'
    TabOrder = 14
  end
  object dsetStationery: TADODataSet
    CursorType = ctStatic
    CommandText = 
      'select BS_BookType.ID,BS_BookType.ParentID,BS_BookType.Code,BS_B' +
      'ookType.Name,BS_Stationery.PressType,BS_Stationery.Author,BS_Sta' +
      'tionery.ISBN,BS_Stationery.UserDefCode,BS_Stationery. ID,BS_Stat' +
      'ionery.Barcode,BS_Stationery.Name ,BS_Stationery.Price ,BS_Stati' +
      'onery.RetailPrice,BS_Stationery.MemberPrice,BS_Stationery.Type f' +
      'rom BS_Stationery,BS_BookType where BS_BookType.Name = BS_Statio' +
      'nery.Type'
    Parameters = <>
    Left = 136
    Top = 152
  end
  object dsrcStationery: TDataSource
    DataSet = dsetStationery
    Left = 208
    Top = 160
  end
  object tbl1: TADOTable
    CursorType = ctStatic
    Filter = 'ParentID=1'
    Filtered = True
    TableName = 'BS_BookType'
    Left = 226
    Top = 102
  end
  object dsrc1: TDataSource
    DataSet = tbl1
    Left = 250
    Top = 126
  end
end
