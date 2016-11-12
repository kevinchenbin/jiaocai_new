inherited frmCUSInit: TfrmCUSInit
  Caption = #23458#25143#24448#26469#26399#21021
  ClientHeight = 435
  ExplicitWidth = 859
  ExplicitHeight = 469
  PixelsPerInch = 96
  TextHeight = 13
  object lbl3: TRzLabel [0]
    Left = 328
    Top = 66
    Width = 60
    Height = 13
    Caption = #36134#25143#20313#39069#65509
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl5: TRzLabel [1]
    Left = 23
    Top = 41
    Width = 468
    Height = 13
    Caption = #35831#27880#24847#65306#20070#24215#27424#23458#25143#30340#38065#20026#36127#25968#65307#23458#25143#27424#20070#24215#30340#38065#20026#27491#25968#65307#36134#25143#20313#39069#20026#20070#24215#27424#23458#25143#30340#38065#65281
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl4: TRzLabel [2]
    Left = 10
    Top = 69
    Width = 57
    Height = 13
    Caption = #36873' '#25321' '#23458' '#25143
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl6: TRzLabel [3]
    Left = 183
    Top = 98
    Width = 12
    Height = 13
    Caption = #65509
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl1: TRzLabel [4]
    Left = 10
    Top = 99
    Width = 60
    Height = 13
    Caption = #35831#24405#20837#37329#39069
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object RzToolbar1: TRzToolbar [5]
    Left = 0
    Top = 0
    Width = 851
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
      RzToolButton3)
    object RzToolButton3: TRzToolButton
      Left = 4
      Top = 2
      Width = 63
      Caption = #36864#20986'[ESC]'
      OnClick = RzToolButton3Click
    end
  end
  object edtBalance: TRzDBEdit [6]
    Left = 394
    Top = 61
    Width = 133
    Height = 21
    DataSource = ds1
    DataField = 'Balance'
    ReadOnly = True
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
  end
  object cbbType: TComboBox [7]
    Left = 76
    Top = 61
    Width = 179
    Height = 21
    ItemHeight = 0
    TabOrder = 2
    Text = #36873#25321#23458#25143
    OnSelect = cbbTypeSelect
  end
  object edtnum1: TEdit [8]
    Left = 76
    Top = 94
    Width = 101
    Height = 21
    MaxLength = 7
    TabOrder = 3
    OnKeyPress = edtnum1KeyPress
  end
  object rzdbgrd2: TRzDBGrid [9]
    Left = 0
    Top = 152
    Width = 851
    Height = 283
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = ds1
    DefaultDrawing = True
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    ReadOnly = True
    TabOrder = 4
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
        FieldName = 'Name'
        Title.Caption = #23458#25143#21517#31216
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Contact'
        PickList.Strings = (
          'dfdf')
        Title.Caption = #32852#31995#20154
        Width = 74
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Telephone'
        Title.Caption = #30005#35805
        Width = 77
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'BookstoreLessBusiness'
        Title.Caption = #26399#21021#20070#24215#27424#23458#25143
        Width = 93
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'BusinessLessBookstore'
        Title.Caption = #26399#21021#23458#25143#27424#20070#24215
        Width = 122
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Balance'
        Title.Caption = #20313#39069
        Width = 57
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Address'
        Title.Caption = #22320#22336
        Width = 100
        Visible = True
      end>
  end
  object dsSupplyInit: TADODataSet
    Parameters = <>
    Left = 192
  end
  object ds1: TDataSource
    DataSet = dsSupplyInit
    Left = 224
  end
  object qrySupply: TADOQuery
    Parameters = <>
    Left = 305
    Top = 65535
  end
  object ds2: TDataSource
    DataSet = qrySupply
    Left = 352
  end
  object cmdaddMoney: TADOCommand
    Parameters = <>
    Left = 304
    Top = 88
  end
end
