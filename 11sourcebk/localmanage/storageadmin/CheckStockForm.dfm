inherited frmCheckStock: TfrmCheckStock
  Caption = #24211#23384#30424#28857
  ClientHeight = 470
  ClientWidth = 766
  Position = poDefault
  ExplicitWidth = 774
  ExplicitHeight = 504
  PixelsPerInch = 96
  TextHeight = 13
  object lbl2: TRzLabel [0]
    Left = 8
    Top = 112
    Width = 72
    Height = 13
    Caption = #35831#36755#20837#30424#28857#25968
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl4: TRzLabel [1]
    Left = 8
    Top = 80
    Width = 66
    Height = 13
    Caption = #26816'  '#32034'  '#36755'  '#20837
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl1: TRzLabel [2]
    Left = 8
    Top = 53
    Width = 66
    Height = 13
    Caption = #36873'  '#25321'  '#24211'  '#20301
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl: TRzLabel [3]
    Left = 356
    Top = 80
    Width = 48
    Height = 13
    Caption = #24403#21069#24211#23384
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl3: TRzLabel [4]
    Left = 216
    Top = 54
    Width = 36
    Height = 13
    Caption = #24403#21069#24215
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl5: TRzLabel [5]
    Left = 356
    Top = 53
    Width = 45
    Height = 13
    Caption = #21333'       '#21495
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object cbbNum: TComboBox [6]
    Left = 101
    Top = 50
    Width = 89
    Height = 21
    ItemHeight = 13
    TabOrder = 0
    Text = #36873#25321#24211#20301
    OnSelect = cbbNumSelect
  end
  object rztlbr1: TRzToolbar [7]
    Left = 0
    Top = 0
    Width = 766
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
    TabOrder = 1
    VisualStyle = vsGradient
    ExplicitWidth = 826
    ToolbarControls = (
      RzToolButton1
      RzToolButton5
      RzToolButton6
      RzToolButton3
      RzToolButton4)
    object RzToolButton5: TRzToolButton
      Left = 79
      Top = 2
      Width = 74
      Caption = #30830#35748#30424#28857'[S]'
      OnClick = RzToolButton5Click
    end
    object RzToolButton1: TRzToolButton
      Left = 4
      Top = 2
      Width = 75
      Caption = #24320#22987#30424#28857'[A]'
      OnClick = RzToolButton1Click
    end
    object RzToolButton3: TRzToolButton
      Left = 228
      Top = 2
      Width = 76
      Caption = #30424#28857#26597#35810'[Q]'
      OnClick = RzToolButton3Click
    end
    object RzToolButton6: TRzToolButton
      Left = 153
      Top = 2
      Width = 75
      Caption = #20316#24223#30424#28857'[D]'
      OnClick = RzToolButton6Click
    end
    object RzToolButton4: TRzToolButton
      Left = 304
      Top = 2
      Width = 63
      Caption = #36864#20986'[ESC]'
      OnClick = RzToolButton4Click
    end
  end
  object RzEdit1: TRzEdit [8]
    Left = 216
    Top = 77
    Width = 122
    Height = 21
    FrameColor = 12164479
    FrameVisible = True
    TabOrder = 2
    OnKeyPress = RzEdit1KeyPress
  end
  object cbbType: TComboBox [9]
    Left = 101
    Top = 77
    Width = 99
    Height = 21
    ItemHeight = 13
    TabOrder = 3
    Text = #26465#30721
    OnSelect = cbbTypeSelect
    Items.Strings = (
      #26465#30721
      #20070#21517
      #20316#32773
      'ISBN')
  end
  object edtnum1: TRzNumericEdit [10]
    Left = 101
    Top = 109
    Width = 99
    Height = 21
    Color = clInfoBk
    ReadOnly = True
    TabOrder = 4
    OnKeyPress = edtnum1KeyPress
    DisplayFormat = ',0;(,0)'
  end
  object rzgrpbx1: TRzGroupBox [11]
    Left = 0
    Top = 136
    Width = 753
    Height = 257
    Caption = #30424#28857#20449#24687
    TabOrder = 5
    object rzdbgrd1: TRzDBGrid
      Left = 1
      Top = 24
      Width = 751
      Height = 232
      Align = alBottom
      Anchors = [akLeft, akTop, akRight, akBottom]
      DataSource = ds3
      DefaultDrawing = True
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
      ReadOnly = True
      TabOrder = 0
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
          FieldName = 'Barcode'
          Title.Caption = #26465#30721
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'BookName'
          Title.Caption = #20070#21517
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ISBN'
          Width = 67
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Author'
          Title.Caption = #20316#32773
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Pressname'
          Title.Caption = #20986#29256#31038
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ShouldAmount'
          Title.Caption = #24211#23384
          Width = 54
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ActualAmount'
          Title.Caption = #30424#28857#25968
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Loss_Or_Leave'
          Title.Caption = #30424#20111'/'#30424#30408
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Balance'
          Title.Caption = #24046#39069
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'date'
          Title.Caption = #26102#38388
          Visible = True
        end>
    end
  end
  object edtNum: TRzDBEdit [12]
    Left = 410
    Top = 77
    Width = 146
    Height = 21
    DataSource = ds2
    DataField = 'Amount'
    ReadOnly = True
    Color = clInfoBk
    FrameColor = 12164479
    FrameVisible = True
    TabOrder = 6
  end
  object rzgrpbx2: TRzGroupBox [13]
    Left = 158
    Top = 179
    Width = 489
    Height = 166
    Caption = #22810#20070#26597#35810#20449#24687
    TabOrder = 7
    Visible = False
    object rzdbgrd2: TRzDBGrid
      Left = 1
      Top = 23
      Width = 487
      Height = 142
      Align = alBottom
      Anchors = [akLeft, akTop, akRight, akBottom]
      DataSource = ds2
      DefaultDrawing = True
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnDblClick = rzdbgrd2DblClick
      FrameColor = 12164479
      FrameVisible = True
      Columns = <
        item
          Expanded = False
          FieldName = 'Barcode'
          Title.Caption = #26465#30721
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Name'
          Title.Caption = #20070#21517
          Width = 54
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'CUSName'
          Title.Caption = #20379#24212#21830
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ISBN'
          Width = 67
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Author'
          Title.Caption = #20316#32773
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PressCount'
          Title.Caption = #29256#27425
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'FullName'
          Title.Caption = #20986#29256#31038
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Amount'
          Title.Caption = #24211#23384
          Visible = True
        end>
    end
  end
  object edtName: TRzDBEdit [14]
    Left = 266
    Top = 50
    Width = 72
    Height = 21
    DataSource = ds4
    DataField = 'Name'
    ReadOnly = True
    Color = clInfoBk
    FrameColor = 12164479
    FrameVisible = True
    TabOrder = 8
  end
  object RzEdit2: TRzEdit [15]
    Left = 101
    Top = 50
    Width = 99
    Height = 21
    Color = clInfoBk
    FrameColor = 12164479
    FrameVisible = True
    ReadOnly = True
    TabOrder = 9
    Visible = False
  end
  object edtName1: TRzDBEdit [16]
    Left = 407
    Top = 50
    Width = 149
    Height = 21
    ReadOnly = True
    Color = clInfoBk
    FrameColor = 12164479
    FrameVisible = True
    TabOrder = 10
    OnClick = edtName1Click
  end
  object rzgrpbx3: TRzGroupBox [17]
    Left = 0
    Top = 136
    Width = 751
    Height = 330
    Caption = #30424#28857#26597#35810#20449#24687
    TabOrder = 11
    Visible = False
    object lbl6: TLabel
      Left = 8
      Top = 24
      Width = 48
      Height = 13
      Caption = #36215#22987#26102#38388
    end
    object lbl7: TLabel
      Left = 206
      Top = 24
      Width = 48
      Height = 13
      Caption = #32467#26463#26102#38388
    end
    object rzdbgrd3: TRzDBGrid
      Left = 1
      Top = 48
      Width = 749
      Height = 281
      Align = alBottom
      Anchors = [akLeft, akTop, akRight, akBottom]
      DataSource = ds7
      DefaultDrawing = True
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
      ReadOnly = True
      TabOrder = 0
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
          FieldName = 'NoteCode'
          Title.Caption = #30424#28857#21333#21495
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Barcode'
          Title.Caption = #26465#30721
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'BookName'
          Title.Caption = #20070#21517
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ISBN'
          Width = 67
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Author'
          Title.Caption = #20316#32773
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Pressname'
          Title.Caption = #20986#29256#31038
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ShouldAmount'
          Title.Caption = #24211#23384
          Width = 54
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ActualAmount'
          Title.Caption = #30424#28857#25968
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Loss_Or_Leave'
          Title.Caption = #30424#20111'/'#30424#30408
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Balance'
          Title.Caption = #24046#39069
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'date'
          Title.Caption = #26102#38388
          Visible = True
        end>
    end
    object dtp1: TDateTimePicker
      Left = 101
      Top = 21
      Width = 99
      Height = 21
      Date = 40043.409419479170000000
      Time = 40043.409419479170000000
      TabOrder = 1
      OnChange = dtp1Change
    end
    object dtp2: TDateTimePicker
      Left = 268
      Top = 21
      Width = 99
      Height = 21
      Date = 40043.409419479170000000
      Time = 40043.409419479170000000
      TabOrder = 2
      OnChange = dtp2Change
    end
  end
  inherited qryUserAuthority: TADOQuery
    Left = 600
  end
  object qryName: TADOQuery
    Parameters = <>
    Left = 17
    Top = 223
  end
  object ds1: TDataSource
    DataSet = dsCheckStock
    Left = 208
    Top = 231
  end
  object ds2: TDataSource
    DataSet = dsCheckStock
    Left = 320
    Top = 240
  end
  object dsCheckStock: TADODataSet
    Parameters = <>
    Left = 272
    Top = 216
  end
  object ds3: TDataSource
    DataSet = dscheck
    Left = 168
    Top = 208
  end
  object dscheck: TADODataSet
    DataSource = ds1
    Parameters = <>
    Left = 104
    Top = 248
  end
  object cmdCreate: TADOCommand
    Parameters = <>
    Left = 352
    Top = 272
  end
  object cmd1: TADOCommand
    Parameters = <>
    Left = 496
    Top = 256
  end
  object dsStore: TADODataSet
    Parameters = <>
    Left = 416
    Top = 304
  end
  object ds4: TDataSource
    DataSet = dsStore
    Left = 464
    Top = 240
  end
  object qryCode: TADOQuery
    Parameters = <>
    Left = 545
    Top = 239
  end
  object ds5: TDataSource
    DataSet = qryCode
    Left = 608
    Top = 295
  end
  object dsqryinventory: TADODataSet
    Parameters = <>
    Left = 56
    Top = 240
  end
  object ds7: TDataSource
    DataSet = dsqryinventory
    Left = 152
    Top = 256
  end
  object dsinventory: TADODataSet
    CursorType = ctStatic
    CommandType = cmdTable
    Parameters = <>
    Left = 240
    Top = 256
  end
  object ds8: TDataSource
    DataSet = dsinventory
    Left = 392
    Top = 240
  end
end
