inherited frmBookstackMng: TfrmBookstackMng
  Caption = #24211#20301#31649#29702
  ClientHeight = 401
  ClientWidth = 609
  ExplicitWidth = 617
  ExplicitHeight = 435
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TRzLabel [0]
    Left = 32
    Top = 100
    Width = 48
    Height = 13
    Caption = #24211#20301#21517#31216
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl2: TRzLabel [1]
    Left = 316
    Top = 100
    Width = 48
    Height = 13
    Caption = #24211#20301#32534#30721
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl3: TRzLabel [2]
    Left = 32
    Top = 55
    Width = 48
    Height = 13
    Caption = #24215'        '#21495
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object edtStgName: TRzDBEdit [3]
    Left = 102
    Top = 97
    Width = 187
    Height = 21
    DataSource = ds1
    DataField = 'Name1'
    ReadOnly = True
    Color = clInfoBk
    FrameColor = 12164479
    FrameVisible = True
    TabOrder = 0
    OnKeyPress = edtStgNameKeyPress
  end
  object edtNum: TRzDBEdit [4]
    Left = 370
    Top = 97
    Width = 123
    Height = 21
    DataSource = ds1
    DataField = 'StgID'
    ReadOnly = True
    Color = clInfoBk
    FrameColor = 12164479
    FrameVisible = True
    TabOrder = 1
    OnKeyPress = edtNumKeyPress
  end
  object rztlbr1: TRzToolbar [5]
    Left = 0
    Top = 0
    Width = 609
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
    TabOrder = 2
    VisualStyle = vsGradient
    ToolbarControls = (
      RzToolButton2
      RzToolButton4
      RzToolButton1
      RzToolButton5
      RzToolButton3)
    object RzToolButton2: TRzToolButton
      Left = 4
      Top = 2
      Caption = #28155#21152'[A]'
      OnClick = RzToolButton2Click
    end
    object RzToolButton4: TRzToolButton
      Left = 64
      Top = 2
      Caption = #21024#38500'[D]'
      OnClick = RzToolButton4Click
    end
    object RzToolButton5: TRzToolButton
      Left = 184
      Top = 2
      Caption = #20445#23384'[S]'
      OnClick = RzToolButton5Click
    end
    object RzToolButton1: TRzToolButton
      Left = 124
      Top = 2
      Caption = #20462#25913'[F1]'
      OnClick = RzToolButton1Click
    end
    object RzToolButton3: TRzToolButton
      Left = 244
      Top = 2
      Width = 63
      Caption = #36864#20986'[ESC]'
      OnClick = RzToolButton3Click
    end
  end
  object rzdbgrdGridCust: TRzDBGrid [6]
    Left = 0
    Top = 136
    Width = 609
    Height = 265
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = ds1
    DefaultDrawing = True
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    ReadOnly = True
    TabOrder = 3
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
        FieldName = 'StgID'
        Title.Caption = #24211#20301#32534#30721
        Width = 72
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Name1'
        Title.Caption = #24211#20301#21517#31216
        Width = 199
        Visible = True
      end>
  end
  object edtID: TRzDBEdit [7]
    Left = 102
    Top = 52
    Width = 38
    Height = 21
    DataSource = ds2
    DataField = 'id'
    ReadOnly = True
    Color = clInfoBk
    FrameColor = 12164479
    FrameVisible = True
    TabOrder = 4
  end
  object edtName: TRzDBEdit [8]
    Left = 146
    Top = 52
    Width = 149
    Height = 21
    DataSource = ds2
    DataField = 'Name'
    ReadOnly = True
    Color = clInfoBk
    FrameColor = 12164479
    FrameVisible = True
    TabOrder = 5
  end
  object dsetBookStackMng: TADODataSet
    CacheSize = 2
    LockType = ltBatchOptimistic
    Parameters = <>
    Left = 424
    Top = 48
  end
  object ds1: TDataSource
    DataSet = dsetBookStackMng
    Left = 480
    Top = 48
  end
  object ds2: TDataSource
    DataSet = dsStore
    Left = 344
    Top = 40
  end
  object dsStore: TADODataSet
    Parameters = <>
    Left = 312
    Top = 40
  end
end
