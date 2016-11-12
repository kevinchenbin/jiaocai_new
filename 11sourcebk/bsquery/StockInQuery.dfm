inherited frmStockInQuery: TfrmStockInQuery
  Caption = #24211#23384#26597#35810
  ClientHeight = 668
  ClientWidth = 1021
  Color = 16180174
  WindowState = wsMaximized
  OnKeyDown = FormKeyDown
  ExplicitWidth = 1037
  ExplicitHeight = 706
  PixelsPerInch = 96
  TextHeight = 13
  object rztlbr1: TRzToolbar [0]
    Left = 0
    Top = 0
    Width = 1021
    Height = 29
    AutoStyle = False
    Images = ImageList1
    ButtonWidth = 60
    ShowButtonCaptions = True
    TextOptions = ttoSelectiveTextOnRight
    BorderInner = fsNone
    BorderOuter = fsNone
    BorderSides = [sdTop]
    BorderWidth = 0
    Color = clSkyBlue
    GradientColorStyle = gcsMSOffice
    TabOrder = 0
    VisualStyle = vsClassic
    ToolbarControls = (
      btnExit1
      btnExit2
      btnExit3
      BtnOK
      BtnAlignBottom
      btnExit4)
    object btnExit1: TRzToolButton
      Left = 4
      Top = -4
      Width = 60
      Height = 36
      ImageIndex = 0
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      Caption = #26597#35810#13'(&F)'
      OnClick = btnExit1Click
    end
    object btnExit2: TRzToolButton
      Left = 64
      Top = -4
      Width = 60
      Height = 36
      ImageIndex = 2
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      Caption = #23548#20986'[F6]'
      OnClick = btnExit2Click
    end
    object btnExit3: TRzToolButton
      Left = 124
      Top = -4
      Width = 60
      Height = 36
      ImageIndex = 4
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      Caption = #39044#35272#25171#21360
      Visible = False
    end
    object btnExit4: TRzToolButton
      Left = 304
      Top = -4
      Width = 60
      Height = 36
      ImageIndex = 6
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      Caption = #36864#20986#13'(&Q)'
      OnClick = btnExit4Click
    end
    object BtnAlignBottom: TRzToolButton
      Left = 244
      Top = -4
      Width = 60
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 9
      ImageIndex = 8
      UseToolbarButtonSize = False
      Caption = #26368#23567#21270#13'(&N)'
      OnClick = BtnAlignBottomClick
    end
    object BtnOK: TRzToolButton
      Left = 184
      Top = -4
      Width = 60
      Height = 36
      Hint = 'OK'
      ImageIndex = 12
      UseToolbarButtonSize = False
      Caption = #24211#23384#13#32467#36716
      Visible = False
      OnClick = BtnOKClick
    end
  end
  object rzgrpbx4: TRzGroupBox [1]
    Left = 0
    Top = 29
    Width = 1021
    Height = 110
    Align = alTop
    ParentColor = True
    TabOrder = 1
    object lbl1: TLabel
      Left = 543
      Top = 50
      Width = 16
      Height = 13
      Caption = '>='
    end
    object lbl2: TLabel
      Left = 616
      Top = 49
      Width = 16
      Height = 13
      Caption = '<='
    end
    object chckbxBookName: TRzCheckBox
      Left = 9
      Top = 21
      Width = 67
      Height = 15
      Caption = #20070'        '#21517
      State = cbUnchecked
      TabOrder = 0
    end
    object chckbxISBN: TRzCheckBox
      Left = 9
      Top = 49
      Width = 67
      Height = 15
      Caption = #20070'        '#21495
      State = cbUnchecked
      TabOrder = 1
    end
    object chckbxSupplier: TRzCheckBox
      Left = 9
      Top = 74
      Width = 67
      Height = 15
      Caption = #20379'  '#24212'  '#21830
      State = cbUnchecked
      TabOrder = 2
    end
    object chckbxUserDefNum: TRzCheckBox
      Left = 463
      Top = 74
      Width = 55
      Height = 15
      Caption = #33258#32534#21495
      State = cbUnchecked
      TabOrder = 3
    end
    object chckbxPrice: TRzCheckBox
      Left = 252
      Top = 22
      Width = 61
      Height = 15
      Caption = #23450'      '#20215
      State = cbUnchecked
      TabOrder = 4
    end
    object chckbxAuthor: TRzCheckBox
      Left = 252
      Top = 48
      Width = 61
      Height = 15
      Caption = #20316'      '#32773
      State = cbUnchecked
      TabOrder = 5
    end
    object chckbxAmount: TRzCheckBox
      Left = 463
      Top = 48
      Width = 55
      Height = 15
      Caption = #25968'    '#37327
      State = cbUnchecked
      TabOrder = 6
    end
    object chckbxPressCount: TRzCheckBox
      Left = 463
      Top = 20
      Width = 55
      Height = 15
      Caption = #20986#29256#31038
      State = cbUnchecked
      TabOrder = 7
    end
    object chckbxType: TRzCheckBox
      Left = 251
      Top = 76
      Width = 61
      Height = 15
      Caption = #31867'      '#21035
      State = cbUnchecked
      TabOrder = 8
    end
    object chckbxShopNum: TRzCheckBox
      Left = 714
      Top = 22
      Width = 61
      Height = 15
      Caption = #24215'      '#21495
      State = cbUnchecked
      TabOrder = 9
    end
    object edtBookName: TRzEdit
      Left = 82
      Top = 19
      Width = 151
      Height = 21
      TabOrder = 10
      OnChange = edtBookNameChange
    end
    object edtISBN: TRzEdit
      Left = 82
      Top = 45
      Width = 151
      Height = 21
      MaxLength = 13
      TabOrder = 11
      OnChange = edtISBNChange
      OnKeyPress = edtISBNKeyPress
    end
    object edtSupplier1: TRzEdit
      Left = 82
      Top = 71
      Width = 42
      Height = 21
      TabOrder = 12
      OnKeyPress = edtSupplier1KeyPress
    end
    object edtUserDefNum: TRzEdit
      Left = 533
      Top = 72
      Width = 161
      Height = 21
      TabOrder = 13
      OnChange = edtUserDefNumChange
    end
    object edtPrice: TRzEdit
      Left = 317
      Top = 18
      Width = 121
      Height = 21
      TabOrder = 14
      OnChange = edtPriceChange
    end
    object edtAuthor: TRzEdit
      Left = 317
      Top = 45
      Width = 121
      Height = 21
      TabOrder = 15
      OnChange = edtAuthorChange
    end
    object edtAmountHigh: TRzEdit
      Left = 649
      Top = 45
      Width = 45
      Height = 21
      TabOrder = 16
      OnChange = edtAmountHighChange
      OnKeyPress = edtAmountHighKeyPress
    end
    object edtPressCount1: TRzEdit
      Left = 533
      Top = 18
      Width = 51
      Height = 21
      TabOrder = 17
      OnKeyPress = edtPressCount1KeyPress
    end
    object edtType1: TRzEdit
      Left = 319
      Top = 73
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 18
    end
    object edtSupplier: TRzDBLookupComboBox
      Left = 124
      Top = 71
      Width = 109
      Height = 21
      DropDownWidth = 150
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = ds2supplier
      TabOrder = 19
      OnClick = edtSupplierClick
      AutoDropDown = True
    end
    object edtstore: TRzDBLookupComboBox
      Left = 781
      Top = 18
      Width = 108
      Height = 21
      KeyField = 'ID'
      ListField = 'name'
      ListSource = dsstore
      TabOrder = 20
      OnClick = edtstoreClick
    end
    object rzlocal: TRzCheckBox
      Left = 714
      Top = 49
      Width = 61
      Height = 15
      Caption = #24211'      '#20301
      State = cbUnchecked
      TabOrder = 21
    end
    object edtlocal: TRzDBLookupComboBox
      Left = 781
      Top = 45
      Width = 108
      Height = 21
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dslocal
      TabOrder = 22
      OnClick = edtlocalClick
    end
    object edtPressCount: TRzDBLookupComboBox
      Left = 585
      Top = 18
      Width = 109
      Height = 21
      DropDownRows = 20
      KeyField = 'ID'
      ListField = 'AbbreviatedName'
      ListSource = dsrcPress
      TabOrder = 23
      OnClick = edtPressCountClick
    end
    object edtType: TRzDBLookupComboBox
      Left = 317
      Top = 72
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcCatalogType
      TabOrder = 24
      OnClick = edtTypeClick
      AutoDropDown = True
    end
    object chmutisupplier: TCheckBox
      Left = 808
      Top = 76
      Width = 82
      Height = 17
      Caption = #22810#36135#28304#26597#35810
      TabOrder = 25
    end
    object chlocal: TCheckBox
      Left = 714
      Top = 76
      Width = 92
      Height = 17
      Caption = #35746#21333#38145#23450#20070#30446
      TabOrder = 26
    end
    object chharm: TCheckBox
      Left = 895
      Top = 20
      Width = 50
      Height = 17
      Caption = #25439#20070
      TabOrder = 27
    end
    object chdam: TCheckBox
      Left = 957
      Top = 20
      Width = 50
      Height = 17
      Caption = #32570#20070
      TabOrder = 28
    end
    object chother: TCheckBox
      Left = 895
      Top = 76
      Width = 118
      Height = 17
      Caption = #21253#25324#20854#20182#21487#26597#35810#24215
      TabOrder = 29
    end
  end
  object DBGridEh1: TDBGridEh [2]
    Left = 0
    Top = 139
    Width = 1021
    Height = 529
    Align = alClient
    AllowedOperations = []
    AllowedSelections = [gstRecordBookmarks, gstAll]
    Ctl3D = True
    DataSource = ds1
    FixedColor = 16180174
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    FooterColor = 16180174
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clNavy
    FooterFont.Height = -11
    FooterFont.Name = 'Tahoma'
    FooterFont.Style = [fsBold]
    FooterRowCount = 1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentCtl3D = False
    ParentFont = False
    PopupMenu = PopupMenu1
    RowHeight = 2
    RowLines = 1
    SumList.Active = True
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnCellClick = DBGridEh1CellClick
    OnDblClick = DBGridEh1DblClick
    OnTitleClick = DBGridEh1TitleClick
    Columns = <
      item
        EditButtons = <>
        FieldName = 'xuhao'
        Footer.Value = #21512#35745
        Footer.ValueType = fvtStaticText
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #24207#21495
        Width = 36
      end
      item
        EditButtons = <>
        FieldName = 'ID'
        Footers = <>
        Visible = False
        Width = 29
      end
      item
        EditButtons = <>
        FieldName = 'suppliername'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20379#24212#21830
        Width = 89
      end
      item
        EditButtons = <>
        FieldName = 'ISBN'
        Footers = <>
        Title.Alignment = taCenter
        Width = 71
      end
      item
        EditButtons = <>
        FieldName = 'bookname'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20070#21517
        Width = 124
      end
      item
        EditButtons = <>
        FieldName = 'AbbreviatedName'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20986#29256#31038
        Width = 55
      end
      item
        EditButtons = <>
        FieldName = 'pressdate'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20986#29256#26085#26399
      end
      item
        EditButtons = <>
        FieldName = 'presscount'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #29256#27425
        Width = 48
      end
      item
        EditButtons = <>
        FieldName = 'typename'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #31867#21517
        Width = 48
      end
      item
        EditButtons = <>
        FieldName = 'userdefcode'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #33258#32534#30721
        Width = 50
      end
      item
        EditButtons = <>
        FieldName = 'BookWords'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20876'/'#21253
        Width = 43
      end
      item
        EditButtons = <>
        FieldName = 'author'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20316#32773
        Width = 46
      end
      item
        EditButtons = <>
        FieldName = 'price'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #23450#20215
        Width = 47
      end
      item
        EditButtons = <>
        FieldName = 'Cbprice'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #25104#26412#21333#20215
        Width = 53
      end
      item
        EditButtons = <>
        FieldName = 'tuihuocb'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #36864#36135#25104#26412
        Width = 53
      end
      item
        EditButtons = <>
        FieldName = 'amount'
        Footer.FieldName = 'amount'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #24211#23384#25968#37327
        Width = 63
      end
      item
        EditButtons = <>
        FieldName = 'mayang'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clFuchsia
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Footer.FieldName = 'mayang'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #24211#23384#30721#27915
        Width = 78
      end
      item
        EditButtons = <>
        FieldName = 'shiyang'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clFuchsia
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Footer.FieldName = 'shiyang'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #24211#23384#23454#27915
        Width = 78
      end
      item
        EditButtons = <>
        FieldName = 'bkharmnum'
        Footer.FieldName = 'bkharmnum'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #25439#37327
        Width = 52
      end
      item
        EditButtons = <>
        FieldName = 'bkdamnum'
        Footer.FieldName = 'bkdamnum'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #32570#37327
        Width = 52
      end
      item
        EditButtons = <>
        FieldName = 'storagename'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #24215#21517
        Width = 92
      end
      item
        EditButtons = <>
        FieldName = 'stackname'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #24211#20301
        Width = 81
      end>
  end
  object edtAmountLow: TEdit [3]
    Left = 565
    Top = 74
    Width = 47
    Height = 21
    TabOrder = 3
    OnChange = edtAmountLowChange
  end
  object chzero: TCheckBox [4]
    Left = 895
    Top = 78
    Width = 112
    Height = 17
    Caption = #24211#23384#20026'0'#19981#26174#31034
    TabOrder = 4
  end
  object DBGridEh2: TDBGridEh [5]
    Left = 0
    Top = 139
    Width = 1021
    Height = 529
    Align = alClient
    AllowedOperations = []
    AllowedSelections = [gstRecordBookmarks, gstAll]
    Ctl3D = True
    DataSource = ds1
    FixedColor = 16180174
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    FooterColor = 16180174
    FooterFont.Charset = DEFAULT_CHARSET
    FooterFont.Color = clNavy
    FooterFont.Height = -11
    FooterFont.Name = 'Tahoma'
    FooterFont.Style = [fsBold]
    FooterRowCount = 1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentCtl3D = False
    ParentFont = False
    PopupMenu = PopupMenu1
    RowHeight = 2
    RowLines = 1
    SumList.Active = True
    TabOrder = 5
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnCellClick = DBGridEh1CellClick
    OnDblClick = DBGridEh1DblClick
    OnTitleClick = DBGridEh1TitleClick
    Columns = <
      item
        EditButtons = <>
        FieldName = 'xuhao'
        Footer.Value = #21512#35745
        Footer.ValueType = fvtStaticText
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #24207#21495
        Width = 36
      end
      item
        EditButtons = <>
        FieldName = 'ID'
        Footers = <>
        Visible = False
        Width = 29
      end
      item
        EditButtons = <>
        FieldName = 'ISBN'
        Footers = <>
        Title.Alignment = taCenter
        Width = 71
      end
      item
        EditButtons = <>
        FieldName = 'bookname'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20070#21517
        Width = 124
      end
      item
        EditButtons = <>
        FieldName = 'AbbreviatedName'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20986#29256#31038
        Width = 55
      end
      item
        EditButtons = <>
        FieldName = 'pressdate'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20986#29256#26085#26399
      end
      item
        EditButtons = <>
        FieldName = 'presscount'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #29256#27425
        Width = 48
      end
      item
        EditButtons = <>
        FieldName = 'typename'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #31867#21517
        Width = 48
      end
      item
        EditButtons = <>
        FieldName = 'userdefcode'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #33258#32534#30721
        Width = 50
      end
      item
        EditButtons = <>
        FieldName = 'BookWords'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20876'/'#21253
        Width = 43
      end
      item
        EditButtons = <>
        FieldName = 'author'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #20316#32773
        Width = 46
      end
      item
        EditButtons = <>
        FieldName = 'price'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #23450#20215
        Width = 47
      end
      item
        EditButtons = <>
        FieldName = 'Cbprice'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #25104#26412#21333#20215
        Width = 53
      end
      item
        EditButtons = <>
        FieldName = 'tuihuocb'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #36864#36135#25104#26412
        Width = 53
      end
      item
        EditButtons = <>
        FieldName = 'amount'
        Footer.FieldName = 'amount'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #24211#23384#25968#37327
        Width = 63
      end
      item
        EditButtons = <>
        FieldName = 'mayang'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clFuchsia
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Footer.FieldName = 'mayang'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #24211#23384#30721#27915
        Width = 78
      end
      item
        EditButtons = <>
        FieldName = 'shiyang'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clFuchsia
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Footer.FieldName = 'shiyang'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #24211#23384#23454#27915
        Width = 78
      end
      item
        EditButtons = <>
        FieldName = 'bkharmnum'
        Footer.FieldName = 'bkharmnum'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #25439#37327
        Width = 52
      end
      item
        EditButtons = <>
        FieldName = 'bkdamnum'
        Footer.FieldName = 'bkdamnum'
        Footer.ValueType = fvtSum
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #32570#37327
        Width = 52
      end
      item
        EditButtons = <>
        FieldName = 'stackname'
        Footers = <>
        Title.Alignment = taCenter
        Title.Caption = #24211#20301
        Width = 81
      end>
  end
  inherited qryUserAuthority: TADOQuery
    Left = 824
    Top = 312
  end
  object qry1: TADOQuery
    CursorType = ctStatic
    Parameters = <>
    Left = 568
    Top = 256
  end
  object ds1: TDataSource
    DataSet = qry1
    Left = 448
    Top = 264
  end
  object tbl2supplier: TADOTable
    CursorType = ctStatic
    TableName = 'STK_BookInfo'
    Left = 720
    Top = 264
  end
  object tbl1supplier: TADOTable
    CursorType = ctStatic
    Filter = 'type = 1'
    Filtered = True
    TableName = 'CUST_CustomerInfo'
    Left = 216
    Top = 216
  end
  object ds2supplier: TDataSource
    DataSet = aq1supplier
    Left = 632
    Top = 272
  end
  object ds3supplier: TDataSource
    DataSet = tbl2supplier
    Left = 576
    Top = 320
  end
  object dsetCatlog: TADODataSet
    CursorType = ctStatic
    CommandText = 
      'select ID, PressID,ISBN, Name, Price, Barcode, UserDefCode, Date' +
      ', Author, PressCount, Unavailable, bigBookTypeID, smallBookTypeI' +
      'D, TotalAmount, PresentNum, AbbreviatedName, BookTypeName,FullNa' +
      'me from UV_PressAndBookCatalogQuery'
    Parameters = <>
    Left = 400
    Top = 288
  end
  object tblPress: TADOTable
    CursorType = ctStatic
    TableName = 'BS_PressInfo'
    Left = 280
    Top = 368
  end
  object tblCatalogType: TADOTable
    CursorType = ctStatic
    Filter = 'ParentID=1'
    Filtered = True
    TableName = 'BS_BookType'
    Left = 728
    Top = 344
  end
  object dsrcPress: TDataSource
    DataSet = aqpress
    Left = 320
    Top = 344
  end
  object dsCatlog: TDataSource
    DataSet = dsetCatlog
    Left = 496
    Top = 296
  end
  object dsrcCatalogType: TDataSource
    DataSet = tblCatalogType
    Left = 232
    Top = 272
  end
  object aquery: TADOQuery
    Parameters = <>
    Left = 696
    Top = 400
  end
  object tblStore: TADOTable
    TableName = 'SYS_StorageInfo'
    Left = 392
    Top = 400
  end
  object dsstore: TDataSource
    DataSet = tblStore
    Left = 456
    Top = 400
  end
  object tbllocal: TADOTable
    TableName = 'STK_BookstackInfo'
    Left = 336
    Top = 272
  end
  object dslocal: TDataSource
    DataSet = tbllocal
    Left = 656
    Top = 344
  end
  object ImageList1: TImageList
    Left = 848
    Top = 192
    Bitmap = {
      494C01010D000F00780010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000004000000001002000000000000040
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000CC00000066000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000CC
      0000009900000099000000660000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000CC00000099
      0000009900000099000000990000006600000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000CC0000009900000099
      0000009900000099000000990000009900000066000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000CC0000009900000099
      00000066000000CC000000990000009900000099000000660000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000CC0000009900000066
      0000000000000000000000CC0000009900000099000000990000006600000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000CC0000006600000000
      000000000000000000000000000000CC00000099000000990000009900000066
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000CC000000990000009900000099
      0000006600000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000CC0000009900000099
      0000009900000066000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000CC00000099
      0000009900000066000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000CC
      0000009900000066000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000CC00000066000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000993300009933000099330000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999009999990099999900000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000000000000000000099330000CC660000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000099999900CCCCCC00CCCCCC00999999000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000000000000000000099330000CC660000CC660000CC6600009933
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000099999900CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000099330000993300009933
      000099330000993300009933000099330000CC660000CC660000CC660000CC66
      0000993300000000000000000000000000000000000099999900999999009999
      990099999900999999009999990099999900CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC660000CC660000CC660000CC660000CC66
      0000CC6600009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC660000CC660000CC660000CC660000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC660000CC660000CC660000CC660000CC66
      0000CC6600009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000099330000993300009933
      000099330000993300009933000099330000CC660000CC660000CC660000CC66
      0000993300000000000000000000000000000000000099999900999999009999
      990099999900999999009999990099999900CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000099330000CC660000CC660000CC6600009933
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000099999900CCCCCC00CCCCCC00CCCCCC009999
      99000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000000000000000
      000000000000000000000000000099330000CC660000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000099999900CCCCCC00CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000993300009933000099330000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999009999990099999900000000000000
      00000000000000000000000000000000000000000000CC99660000000000CC99
      660000000000CC99660000000000CC99660000000000CC99660000000000CC99
      660000000000CC996600000000000000000000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000CCCCCC0000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC99990099330000CC9999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0099999900CCCCCC000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9999009933000099330000993300000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900CCCCCC00999999009999990099999900000000000000000000000000E2EF
      F100E5E5E500CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F10000000000CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF008080
      8000993300009933000099330000CC9999000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      8000999999009999990099999900CCCCCC0000000000E2EFF100E5E5E500B2B2
      B200CC9999009966660099666600B2B2B200CCCCCC00E5E5E500E2EFF1000000
      00000000000000000000000000000000000000000000E2EFF10000000000B2B2
      B200999999009999990099999900B2B2B200CCCCCC0000000000E2EFF1000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E5008080800080808000808080009933
      00009933000099330000CC99990000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC008080800080808000808080009999
      99009999990099999900CCCCCC0000000000E5E5E500CC99990099666600CC99
      9900CC999900FFFFFF00996666009999990099999900B2B2B200E5E5E5000000
      0000000000000000000000000000000000000000000099999900999999009999
      990099999900FFFFFF00999999009999990099999900B2B2B200000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00E5E5E50099996600FFFFCC00FFFFCC00FFFFFF00CCCC
      990099330000CC99990000000000000000000000000099999900000000000000
      00000000000000000000CCCCCC0099999900E5E5E500E5E5E500FFFFFF00E5E5
      E50099999900CCCCCC00000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600336699003366990033669900E2EFF1000000
      0000000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900999999009999990099999900E2EFF1000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E50099999900F2EABF00FFFFCC00FFFFCC00FFFFCC00FFFF
      FF0066666600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC0099999900E5E5E500E5E5E500E5E5E500E5E5E500FFFF
      FF006666660000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCCC000099CC00FFFFFF00FFCC
      CC000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000C0C0C00099999900FFFFFF00CCCC
      CC000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0099999900F2EABF00FFFFFF00F2EABF00FFFFCC00FFFF
      CC00666666000000000000000000000000000000000099999900000000000000
      0000000000000000000099999900E5E5E500FFFFFF00E5E5E500E5E5E500E5E5
      E5006666660000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCFF003399CC00FFCCCC00CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000CCCCCC0099999900CCCCCC009999
      99000000000000000000000000000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E50099999900F2EABF00FFFFFF00FFFFFF00F2EABF00FFFF
      CC0066666600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC0099999900E5E5E500FFFFFF00FFFFFF00E5E5E500E5E5
      E5006666660000000000000000000000000099666600FFCC9900CC999900CC99
      6600FFCCCC00FFFFFF009966660099CCCC0099CCFF00B2B2B200FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000999999009999
      9900CCCCCC00FFFFFF0099999900CCCCCC00CCCCCC00B2B2B200999999009999
      99000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0099999900F2EABF00F2EABF00F2EABF009999
      6600808080000000000000000000000000000000000099999900000000000000
      000000000000000000000000000099999900E5E5E500E5E5E500E5E5E5009999
      99008080800000000000000000000000000099666600FFCC990099666600FFFF
      FF00FFCCCC00FFFFFF009966660099CCCC00C0C0C000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C00066666600FFFF
      FF00CCCCCC00FFFFFF0099999900CCCCCC00C0C0C00099999900999999009999
      99009999990099999900999999000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500999999009999990099999900E5E5
      E500CC996600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999009999990099999900E5E5
      E5009999990000000000000000000000000099666600FFCC9900CC9999009966
      6600FFCCCC00FFFFFF009966660000000000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000999999006666
      6600CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      99009999990099999900999999000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CC9966000000000000000000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009999990000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660000000000CC999900CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      99009999990099999900999999000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500FFFFFF00CC996600CC996600CC99
      6600CC996600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC000000000099999900999999009999
      99009999990000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00E2EFF100CC999900FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E2EFF10099999900999999009999
      99000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600E5E5E500CC99
      6600000000000000000000000000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000099999900E5E5E5009999
      99000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660099CCCC000000000099CCCC00FFCC9900CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E500CCCCCC00C0C0C0009999
      99000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600CC9966000000
      0000000000000000000000000000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000099999900999999000000
      00000000000000000000000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00000000003399CC0000000000FFCC
      9900000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E5009999990000000000C0C0
      C0000000000000000000000000000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600000000000000
      0000000000000000000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900000000000000
      00000000000000000000000000000000000000000000C0C0C000CC996600CC99
      9900CCCC9900FFFFFF00996666000099CC000099CC000099CC00000000000000
      00000000000000000000000000000000000000000000C0C0C000999999009999
      9900C0C0C000FFFFFF0099999900999999009999990099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00CC9999009966660099666600000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00999999009999990099999900000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC0066999900666699009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC00B2B2B200999999009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000066CCFF003399CC006666
      990099999900E5E5E50000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00B2B2B2009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      99000000000000000000000000000000000000000000CCCCFF0066CCFF003399
      CC006666990099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E5E5E500CCCCCC00B2B2
      B2009999990099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300000000000000000000000000000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999000000000000000000000000000000000000000000CCCCFF0066CC
      FF003399CC006666990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E5E5E500CCCC
      CC00B2B2B2009999990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      990000000000000000000000000000000000000000000000000000000000CCCC
      FF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC999900CC999900CC99
      9900CCCC9900E5E5E5000000000000000000000000000000000000000000E5E5
      E500CCCCCC00B2B2B20099999900CCCCCC00E5E5E50099999900999999009999
      9900B2B2B200E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EABF00FFFFCC00F2EA
      BF00F2EABF00CC999900ECC6D900000000000000000000000000000000000000
      0000E5E5E500CCCCCC00B2B2B20099999900B2B2B200CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000E5E5E500CC999900FFCC9900FFFFCC00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E50099999900E5E5E500CC996600CC996600CC996600CC99
      6600CC996600CC996600CC99660000000000000000003399CC00006699000066
      9900006699000066990000669900006699009999990099999900999999009999
      9900999999009999990099999900000000000000000099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFCC00F2EABF00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00F2EABF00CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E500CCCCCC00B2B2B200CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CCCC9900FFCC9900F2EABF00F2EABF00FFFFCC00FFFFCC00FFFF
      CC00FFFFFF00FFFFFF00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00E5E5E500E5E5E500CCCCCC0099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CC999900F2EABF00F2EABF00F2EABF00F2EABF00FFFFCC00FFFF
      CC00FFFFCC00FFFFCC00FFFFCC00CC9999000000000000000000000000000000
      00000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC0099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CCCC9900F2EABF00FFFFCC00F2EABF00F2EABF00F2EABF00FFFF
      CC00FFFFCC00FFFFCC00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC0099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EABF00F2EABF00F2EA
      BF00F2EABF00FFFFCC00CCCC9900CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00B2B2B200B2B2B200CC996600FFFFFF00FFFFFF00CC99
      6600CC996600CC996600CC99660000000000000000003399CC0099FFFF0099FF
      FF003399CC003399CC003399CC003399CC009999990000000000000000009999
      9900999999009999990099999900000000000000000099999900CCCCCC00CCCC
      CC00999999009999990099999900999999000000000000000000000000000000
      000000000000E5E5E500CC999900ECC6D900FFFFFF00FFFFCC00F2EABF00F2EA
      BF00F2EABF00FFCC9900CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00E5E5E50099999900E5E5E500CC996600FFFFFF00FFFFFF00CC99
      6600E5E5E500CC9966000000000000000000000000003399CC0099FFFF0099FF
      FF003399CC00CCFFFF0000669900000000009999990000000000000000009999
      9900E5E5E5009999990000000000000000000000000099999900CCCCCC00CCCC
      CC0099999900CCCCCC0099999900000000000000000000000000000000000000
      00000000000000000000FFCCCC00CC999900FFCCCC00F2EABF00F2EABF00F2EA
      BF00CCCC9900CC999900FFCCCC00000000000000000000000000000000000000
      00000000000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCC
      CC00B2B2B20099999900E5E5E50000000000CC996600FFFFFF00FFFFFF00CC99
      6600CC996600000000000000000000000000000000003399CC0099FFFF0099FF
      FF003399CC000066990000000000000000009999990000000000000000009999
      9900999999000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500CCCC9900CC999900CC999900CC99
      9900CC999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500B2B2B20099999900999999009999
      990099999900E5E5E5000000000000000000CC996600CC996600CC996600CC99
      660000000000000000000000000000000000000000003399CC003399CC003399
      CC003399CC000000000000000000000000009999990099999900999999009999
      9900000000000000000000000000000000000000000099999900999999009999
      990099999900000000000000000000000000424D3E000000000000003E000000
      2800000040000000400000000100010000000000000200000000000000000000
      000000000000000000000000FFFFFF00FFFF000000000000FFFF000000000000
      F3FF000000000000E1FF000000000000C0FF000000000000807F000000000000
      803F0000000000008C1F0000000000009E0F000000000000FF07000000000000
      FF83000000000000FFC3000000000000FFE3000000000000FFF3000000000000
      FFFF000000000000FFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      80038003FFFFFFFF80038003FE3FFE3F80038003FE1FFE1F80038003FE0FFE0F
      8003800380078007FFFFFFFF80038003BFFBBFFB80018001FFFFFFFF80038003
      BFFBBFFB80078007FFFFFFFFFE0FFE0FBFFBBFFBFE1FFE1FFFFFFFFFFE3FFE3F
      AAABAAABFFFFFFFFFFFFFFFFFFFFFFFFFFF8FFF8FDFFFDFF80008000E0FFE8FF
      8000BFE0801FA05F8001A001001F803F8003BC03001F001F8007A007000F000F
      8007BC07000F000F8007A007000F000F8007BE07000100018007A00701010001
      8007BFF7010100018007A087000F000F800FBF8F008F000F801FBF9F00AF002F
      803F803F803F803FFFFFFFFFE1FFE1FF8FFF8FFFFFFFFFFF07FF07FFFFDFFFDF
      83FF83FFFFCFFFCF81FF81FFE007E007C0FFC0FFFFCFFFCFE003E003FFDFFFDF
      F001F001FFFFFFFFF800F80001800180F800F80001807D80F800F80001807D80
      F800F80001807D80F800F80001807D80F800F80001806180F800F80003816381
      FC01FC0107836783FE03FE030F870F8700000000000000000000000000000000
      000000000000}
  end
  object aq1supplier: TADOQuery
    Parameters = <>
    SQL.Strings = (
      'select ID,Name from CUST_CustomerInfo where type = 1')
    Left = 64
    Top = 296
  end
  object aqpress: TADOQuery
    Parameters = <>
    SQL.Strings = (
      'select ID,PresentNum,AbbreviatedName from BS_PressInfo')
    Left = 152
    Top = 376
  end
  object savedlg: TSaveDialog
    Left = 736
    Top = 208
  end
  object adospcopy: TADOStoredProc
    Parameters = <>
    Left = 368
    Top = 168
  end
  object PopupMenu1: TPopupMenu
    Left = 496
    Top = 184
    object N2: TMenuItem
      Caption = #20840#36873
      OnClick = N2Click
    end
    object N1: TMenuItem
      Caption = #22797#21046
      OnClick = N1Click
    end
    object N3: TMenuItem
      Caption = #21382#21490#26126#32454
      OnClick = N3Click
    end
    object N4: TMenuItem
      Caption = '---------'
    end
    object N5: TMenuItem
      Caption = #21024#38500#24211#23384#35760#24405
      OnClick = N5Click
    end
  end
end