inherited frmSupplyInit: TfrmSupplyInit
  Caption = #20379#24212#21830#24448#26469#26399#21021
  ClientHeight = 372
  ClientWidth = 595
  ExplicitWidth = 603
  ExplicitHeight = 406
  PixelsPerInch = 96
  TextHeight = 13
  object lbl4: TRzLabel [0]
    Left = 10
    Top = 66
    Width = 60
    Height = 13
    Caption = #36873#25321#20379#24212#21830
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl1: TRzLabel [1]
    Left = 10
    Top = 98
    Width = 60
    Height = 13
    Caption = #35831#24405#20837#37329#39069
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl3: TRzLabel [2]
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
  object lbl2: TRzLabel [3]
    Left = 134
    Top = 11
    Width = 492
    Height = 13
    Caption = #35831#27880#24847#65306#20070#24215#27424#20379#24212#21830#30340#38065#20026#27491#25968#65307#20379#24212#21830#27424#20070#24215#30340#38065#20026#36127#25968#65307#36134#25143#20313#39069#20026#20379#24212#21830#27424#20070#24215#38065#65281
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl5: TRzLabel [4]
    Left = 23
    Top = 41
    Width = 492
    Height = 13
    Caption = #35831#27880#24847#65306#20070#24215#27424#20379#24212#21830#30340#38065#20026#27491#25968#65307#20379#24212#21830#27424#20070#24215#30340#38065#20026#36127#25968#65307#36134#25143#20313#39069#20026#20379#24212#21830#27424#20070#24215#38065#65281
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl6: TRzLabel [5]
    Left = 183
    Top = 98
    Width = 12
    Height = 13
    Caption = #65509
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object rzdbgrd2: TRzDBGrid [6]
    Left = 0
    Top = 118
    Width = 595
    Height = 254
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = ds1
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
        FieldName = 'Name'
        Title.Caption = #20379#24212#21830#21517#31216
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Contact'
        PickList.Strings = (
          'dfdf')
        Title.Caption = #20379#24212#21830#32852#31995#20154
        Width = 90
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Address'
        Title.Caption = #22320#22336
        Width = 100
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
        Title.Caption = #26399#21021#20070#24215#27424#20379#24212#21830
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'BusinessLessBookstore'
        Title.Caption = #26399#21021#20379#24212#21830#27424#20070#24215
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Balance'
        Title.Caption = #20313#39069
        Width = 57
        Visible = True
      end>
  end
  object cbbType: TComboBox [7]
    Left = 78
    Top = 64
    Width = 179
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    Text = #36873#25321#20379#24212#21830
    OnSelect = cbbTypeSelect
  end
  object RzToolbar1: TRzToolbar [8]
    Left = 0
    Top = 0
    Width = 595
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
      RzToolButton3)
    object RzToolButton3: TRzToolButton
      Left = 4
      Top = 2
      Width = 63
      Caption = #36864#20986'[ESC]'
      OnClick = RzToolButton3Click
    end
  end
  object edt1: TRzDBEdit [9]
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
    TabOrder = 3
  end
  object edtnum1: TEdit [10]
    Left = 76
    Top = 91
    Width = 101
    Height = 21
    TabOrder = 4
    OnKeyPress = edtnum1KeyPress
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
