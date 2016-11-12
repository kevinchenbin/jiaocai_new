inherited frmAdjustStock: TfrmAdjustStock
  Caption = #24211#20301#35843#25972
  ClientHeight = 440
  ClientWidth = 744
  ExplicitWidth = 752
  ExplicitHeight = 474
  PixelsPerInch = 96
  TextHeight = 13
  object lbl3: TRzLabel [0]
    Left = 336
    Top = 38
    Width = 48
    Height = 13
    Caption = #24215'        '#21495
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl4: TRzLabel [1]
    Left = 20
    Top = 37
    Width = 48
    Height = 13
    Caption = #26597#35810#36755#20837
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object Label1: TLabel [2]
    Left = 592
    Top = 32
    Width = 77
    Height = 13
    Caption = 'AAAAAAAAAAA'
  end
  object RzToolbar1: TRzToolbar [3]
    Left = 0
    Top = 0
    Width = 744
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
      RzToolButton10)
    object RzToolButton10: TRzToolButton
      Left = 4
      Top = 2
      Width = 63
      Caption = #36864#20986'[ESC]'
      OnClick = RzToolButton10Click
    end
  end
  object edtNum: TRzDBEdit [4]
    Left = 390
    Top = 35
    Width = 43
    Height = 21
    DataSource = ds2
    DataField = 'ID'
    ReadOnly = True
    Color = clInfoBk
    FrameColor = 12164479
    FrameVisible = True
    TabOrder = 1
  end
  object edtName: TRzDBEdit [5]
    Left = 439
    Top = 35
    Width = 98
    Height = 21
    DataSource = ds2
    DataField = 'Name'
    ReadOnly = True
    Color = clInfoBk
    FrameColor = 12164479
    FrameVisible = True
    TabOrder = 2
  end
  object RzEditInfor: TRzEdit [6]
    Left = 72
    Top = 34
    Width = 122
    Height = 21
    FrameColor = 12164479
    FrameVisible = True
    TabOrder = 3
    OnKeyPress = RzEditInforKeyPress
  end
  object cbbType: TComboBox [7]
    Left = 205
    Top = 34
    Width = 76
    Height = 21
    ItemHeight = 13
    TabOrder = 4
    Text = #36873#25321#31867#22411
    OnSelect = cbbTypeSelect
    Items.Strings = (
      #21333#21697
      #31867#21035
      #20986#29256#31038
      #24211#20301#32534#30721)
  end
  object rzdbgrdGridCust: TRzDBGrid [8]
    Left = 0
    Top = 176
    Width = 744
    Height = 264
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = ds4
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
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'BookName'
        Title.Caption = #20070#21517
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'BsINforName'
        Title.Caption = #24211#20301#21517#31216
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'StgID'
        Title.Caption = #24211#20301#32534#30721
        Width = 68
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'BookTypeName'
        Title.Caption = #31867#21035
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Amount'
        Title.Caption = #25968#37327
        Width = 102
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
        FieldName = 'FullName'
        Title.Caption = #20986#29256#31038
        Width = 50
        Visible = True
      end>
  end
  object rzgrpbx1: TRzGroupBox [9]
    Left = 0
    Top = 62
    Width = 409
    Height = 108
    Caption = #21333#21697#35843#25972
    TabOrder = 6
    object lbl5: TRzLabel
      Left = 4
      Top = 71
      Width = 48
      Height = 13
      Caption = #35843'  '#25972'  '#21040
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl6: TRzLabel
      Left = 228
      Top = 71
      Width = 12
      Height = 13
      Caption = #26412
      Visible = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl2: TRzLabel
      Left = 234
      Top = 34
      Width = 48
      Height = 13
      Caption = #24211#20301#32534#30721
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl1: TRzLabel
      Left = 4
      Top = 34
      Width = 48
      Height = 13
      Caption = #24211#20301#21517#31216
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object edtContact: TRzDBEdit
      Left = 52
      Top = 31
      Width = 176
      Height = 21
      DataSource = ds4
      DataField = 'BsINforName'
      ReadOnly = True
      Color = clInfoBk
      FrameColor = 12164479
      FrameVisible = True
      TabOrder = 0
    end
    object edtSingle: TRzNumericEdit
      Left = 145
      Top = 68
      Width = 79
      Height = 21
      TabOrder = 1
      Visible = False
      OnKeyPress = edtSingleKeyPress
      DisplayFormat = ',0;(,0)'
    end
    object cbbNum: TComboBox
      Left = 55
      Top = 68
      Width = 89
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      Text = #36873#25321#24211#20301
      OnSelect = cbbNumSelect
    end
    object edtContact1: TRzDBEdit
      Left = 288
      Top = 31
      Width = 113
      Height = 21
      DataSource = ds4
      DataField = 'StgID'
      ReadOnly = True
      Color = clInfoBk
      FrameColor = 12164479
      FrameVisible = True
      TabOrder = 3
    end
  end
  object rzgrpbx2: TRzGroupBox [10]
    Left = 415
    Top = 62
    Width = 322
    Height = 108
    Caption = #25209#37327#35843#25972
    TabOrder = 7
    object lbl8: TRzLabel
      Left = 36
      Top = 44
      Width = 96
      Height = 13
      Caption = #35843#25972#24403#21069#25152#26377#20070#21040
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl10: TRzLabel
      Left = 235
      Top = 44
      Width = 24
      Height = 13
      Caption = #24211#20301
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object cbbNum1: TComboBox
      Left = 140
      Top = 40
      Width = 89
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      Text = #36873#25321#24211#20301
      OnSelect = cbbNum1Select
    end
  end
  object dsStoreName: TADODataSet
    Parameters = <>
    Left = 424
    Top = 32
  end
  object ds2: TDataSource
    DataSet = dsStoreName
    Left = 488
    Top = 32
  end
  object qryName: TADOQuery
    Parameters = <>
    Left = 185
    Top = 136
  end
  object ds1: TDataSource
    DataSet = dsStoreName
    Left = 240
    Top = 152
  end
  object dsAdjustStock: TADODataSet
    Parameters = <>
    Left = 128
    Top = 56
  end
  object ds4: TDataSource
    DataSet = dsAdjustStock
    Left = 208
    Top = 56
  end
  object dsetwhole: TADODataSet
    Parameters = <>
    Left = 672
    Top = 56
  end
  object ds5: TDataSource
    DataSet = dsetwhole
    Left = 672
    Top = 112
  end
  object cmdwhole: TADOCommand
    Parameters = <>
    Left = 552
    Top = 112
  end
  object cmdSingle: TADOCommand
    Parameters = <>
    Left = 304
    Top = 136
  end
  object ds3: TDataSource
    DataSet = dsetID
    Left = 376
    Top = 120
  end
  object dsetID: TADODataSet
    Parameters = <>
    Left = 344
    Top = 120
  end
end
