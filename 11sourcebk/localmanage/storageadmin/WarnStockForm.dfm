inherited frmWarnStock: TfrmWarnStock
  Caption = #24211#23384#39044#35686
  ClientHeight = 373
  ClientWidth = 673
  ExplicitWidth = 681
  ExplicitHeight = 407
  PixelsPerInch = 96
  TextHeight = 13
  object lbl4: TRzLabel [0]
    Left = 8
    Top = 48
    Width = 48
    Height = 13
    Caption = #26816#32034#36755#20837
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl1: TRzLabel [1]
    Left = 282
    Top = 50
    Width = 48
    Height = 13
    Caption = #39044#35686#19978#38480
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl2: TRzLabel [2]
    Left = 418
    Top = 48
    Width = 48
    Height = 13
    Caption = #39044#35686#19979#38480
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl3: TRzLabel [3]
    Left = 8
    Top = 76
    Width = 72
    Height = 13
    Caption = #35831#36873#25321#20379#24212#21830
    Visible = False
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object rztlbr1: TRzToolbar [4]
    Left = 0
    Top = 0
    Width = 673
    Height = 29
    ButtonWidth = 60
    ShowButtonCaptions = True
    TextOptions = ttoCustom
    BorderInner = fsNone
    BorderOuter = fsGroove
    BorderSides = [sdTop]
    BorderWidth = 0
    Caption = #21024#38500
    GradientColorStyle = gcsMSOffice
    TabOrder = 0
    VisualStyle = vsGradient
    ToolbarControls = (
      RzToolButton5
      RzToolButton1
      RzToolButton3)
    object RzToolButton5: TRzToolButton
      Left = 4
      Top = 2
      Width = 75
      Caption = #39044#35686#35774#32622'[A]'
      OnClick = RzToolButton5Click
    end
    object RzToolButton3: TRzToolButton
      Left = 155
      Top = 2
      Width = 63
      Caption = #36864#20986'[ESC]'
      OnClick = RzToolButton3Click
    end
    object RzToolButton1: TRzToolButton
      Left = 79
      Top = 2
      Width = 76
      Caption = #39044#35686#26597#35810'[Q]'
      OnClick = RzToolButton1Click
    end
  end
  object cbbType: TComboBox [5]
    Left = 59
    Top = 45
    Width = 76
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    Text = #36873#25321#31867#22411
    OnSelect = cbbTypeSelect
    Items.Strings = (
      #26465#30721
      #31867#21035
      #20070#21517
      'ISBN')
  end
  object RzEdtInfor: TRzEdit [6]
    Left = 142
    Top = 45
    Width = 122
    Height = 21
    FrameColor = 12164479
    FrameVisible = True
    TabOrder = 2
    OnKeyPress = RzEdtInforKeyPress
  end
  object edtnum1: TRzNumericEdit [7]
    Left = 333
    Top = 45
    Width = 79
    Height = 21
    Color = clInfoBk
    MaxLength = 8
    ReadOnly = True
    TabOrder = 3
    OnKeyPress = edtnum1KeyPress
    DisplayFormat = ',0;(,0)'
  end
  object RzNumericEdit1: TRzNumericEdit [8]
    Left = 472
    Top = 45
    Width = 79
    Height = 21
    Color = clInfoBk
    ReadOnly = True
    TabOrder = 4
    OnKeyPress = RzNumericEdit1KeyPress
    DisplayFormat = ',0;(,0)'
  end
  object rzdbgrd2: TRzDBGrid [9]
    Left = 0
    Top = 102
    Width = 673
    Height = 271
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = ds1
    DefaultDrawing = True
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    ReadOnly = True
    TabOrder = 5
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    FrameColor = 12164479
    FrameVisible = True
    Columns = <
      item
        Expanded = False
        FieldName = 'ISBN'
        Width = 67
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'BookName'
        PickList.Strings = (
          'dfdf')
        Title.Caption = #20070#21517
        Width = 54
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Price'
        Title.Caption = #23450#20215
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Amount'
        Title.Caption = #24211#23384
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'MaxStock'
        Title.Caption = #39044#35686#19978#38480
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'MinStock'
        Title.Caption = #39044#35686#19979#38480
        Visible = True
      end>
  end
  object cbb1: TComboBox [10]
    Left = 141
    Top = 45
    Width = 76
    Height = 21
    ItemHeight = 0
    TabOrder = 6
    Text = #36873#25321#31867#21035
    Visible = False
    OnSelect = cbb1Select
  end
  object cbbSupply: TComboBox [11]
    Left = 94
    Top = 73
    Width = 91
    Height = 21
    ItemHeight = 0
    TabOrder = 7
    Text = #36873#25321#20379#24212#21830
    Visible = False
    OnSelect = cbbSupplySelect
  end
  object chk1: TCheckBox [12]
    Left = 191
    Top = 76
    Width = 74
    Height = 16
    Caption = #39640#20110#19978#38480
    Checked = True
    State = cbChecked
    TabOrder = 8
    Visible = False
    OnClick = chk1Click
  end
  object chk2: TCheckBox [13]
    Left = 270
    Top = 76
    Width = 73
    Height = 16
    Caption = #20302#20110#19979#38480
    Checked = True
    State = cbChecked
    TabOrder = 9
    Visible = False
    OnClick = chk2Click
  end
  object btn1: TButton [14]
    Left = 610
    Top = 43
    Width = 56
    Height = 26
    Caption = #35774#32622
    TabOrder = 10
    OnClick = btn1Click
  end
  object btn2: TButton [15]
    Left = 349
    Top = 70
    Width = 56
    Height = 26
    Caption = #26597#35810
    TabOrder = 11
    Visible = False
    OnClick = btn2Click
  end
  object rb1: TCheckBox [16]
    Left = 557
    Top = 47
    Width = 47
    Height = 17
    Caption = #25152#26377
    TabOrder = 12
  end
  object ds1: TDataSource
    DataSet = dsWarnStock
    Left = 272
    Top = 160
  end
  object dsWarnStock: TADODataSet
    CursorType = ctStatic
    CommandText = 
      'select STK_BookInfo.id,ISBN,BS_BookCatalog.Name as BookName,Pric' +
      'e,Amount,MaxStock,MinStock,Barcode,BS_BookType.Name as TypeName,' +
      'CUST_CustomerInfo.Name as SupplyName from STK_BookInfo  left joi' +
      'n STK_BookstackInfo on BkstackID=STK_BookstackInfo.id left join ' +
      'BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_Pre' +
      'ssInfo on PressID=BS_PressInfo.id left join BS_BookType on BS_Bo' +
      'okType.id=smallBookTypeID left join CUST_CustomerInfo on CUST_Cu' +
      'stomerInfo.id=SupplierID where CUST_CustomerInfo.Type=1'
    Parameters = <>
    Left = 360
    Top = 192
  end
  object ds2: TDataSource
    Left = 144
    Top = 119
  end
  object qryName: TADOQuery
    Parameters = <>
    Left = 97
    Top = 119
  end
  object qrySupply: TADOQuery
    Parameters = <>
    Left = 193
    Top = 127
  end
  object ds3: TDataSource
    Left = 232
    Top = 111
  end
  object cmdSetWarn: TADOCommand
    Parameters = <>
    Left = 440
    Top = 88
  end
end
