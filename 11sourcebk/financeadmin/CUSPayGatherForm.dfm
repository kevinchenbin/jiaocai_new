inherited frmCUSPayGather: TfrmCUSPayGather
  Caption = 'frmCUSPayGather'
  ClientHeight = 402
  ClientWidth = 720
  ExplicitWidth = 728
  ExplicitHeight = 436
  PixelsPerInch = 96
  TextHeight = 13
  object lbl2: TRzLabel [0]
    Left = 337
    Top = 55
    Width = 48
    Height = 13
    Caption = #32456#27490#26102#38388
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl1: TRzLabel [1]
    Left = 186
    Top = 55
    Width = 48
    Height = 13
    Caption = #36215#22987#26102#38388
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl4: TRzLabel [2]
    Left = 8
    Top = 55
    Width = 48
    Height = 13
    Caption = #36873#25321#23458#25143
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl5: TRzLabel [3]
    Left = 475
    Top = 55
    Width = 24
    Height = 13
    Caption = #36827#20986
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object rzdbgrd2: TRzDBGrid [4]
    Left = 0
    Top = 96
    Width = 720
    Height = 306
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
    FrameColor = 12164479
    FrameVisible = True
    Columns = <
      item
        Expanded = False
        FieldName = 'Name1'
        Title.Caption = #23458#25143#21517#31216
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'TotalFixedPrice'
        PickList.Strings = (
          'dfdf')
        Title.Caption = #24635#30721#27915
        Width = 71
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'TotalDiscountedPrice'
        Title.Caption = #24635#23454#26679
        Width = 93
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Amount'
        Title.Caption = #24635#25968#37327
        Width = 77
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'AddCosts'
        Title.Caption = #24635#38468#21152#36153#29992
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Checked'
        Title.Caption = #24050#32467
        Width = 84
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'NoChecked'
        Title.Caption = #26410#32467
        Width = 57
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Balance'
        Title.Caption = #36134#25143#20313#39069
        Visible = True
      end>
  end
  object dtp2: TDateTimePicker [5]
    Left = 389
    Top = 52
    Width = 80
    Height = 21
    Date = 40018.450151180560000000
    Time = 40018.450151180560000000
    TabOrder = 1
    OnChange = RzToolButton3Click
  end
  object dtp1: TDateTimePicker [6]
    Left = 239
    Top = 52
    Width = 85
    Height = 21
    Date = 40018.450151180560000000
    Time = 40018.450151180560000000
    TabOrder = 2
    OnChange = RzToolButton3Click
  end
  object cbbType: TComboBox [7]
    Left = 74
    Top = 52
    Width = 95
    Height = 21
    ItemHeight = 13
    TabOrder = 3
    Text = #20840#37096#23458#25143
    OnSelect = RzToolButton3Click
  end
  object RzToolbar1: TRzToolbar [8]
    Left = 0
    Top = 0
    Width = 720
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
    TabOrder = 4
    VisualStyle = vsGradient
    ToolbarControls = (
      RzToolButton3
      RzToolButton1)
    object RzToolButton3: TRzToolButton
      Left = 4
      Top = 2
      Caption = #26597#35810'[Q]'
      OnClick = RzToolButton3Click
    end
    object RzToolButton1: TRzToolButton
      Left = 64
      Top = 2
      Width = 63
      Caption = #36864#20986'[ESC]'
      OnClick = RzToolButton1Click
    end
  end
  object cbb2: TComboBox [9]
    Left = 513
    Top = 52
    Width = 49
    Height = 21
    ItemHeight = 13
    TabOrder = 5
    Text = #20840#37096
    Items.Strings = (
      #36827#36135
      #36864#36135)
  end
  object chk1: TCheckBox [10]
    Left = 568
    Top = 54
    Width = 150
    Height = 17
    Caption = #26159#21542#21253#21547#20174#26410#32467#27454#20379#24212#21830
    TabOrder = 6
  end
  object qrySupply: TADOQuery
    Parameters = <>
    Left = 97
    Top = 135
  end
  object ds: TDataSource
    DataSet = qrySupply
    Left = 144
    Top = 136
  end
  object dsQuery: TADODataSet
    Parameters = <>
    Left = 256
    Top = 160
  end
  object ds2: TDataSource
    DataSet = dsQuery
    Left = 288
    Top = 176
  end
end
