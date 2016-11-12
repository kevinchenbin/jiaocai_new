inherited frmPayGather: TfrmPayGather
  Caption = 'frmPayGather'
  ClientHeight = 313
  ClientWidth = 803
  OnClose = FormClose
  ExplicitWidth = 811
  ExplicitHeight = 347
  PixelsPerInch = 96
  TextHeight = 13
  object lbl4: TRzLabel
    Left = 8
    Top = 55
    Width = 60
    Height = 13
    Caption = #36873#25321#20379#24212#21830
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl1: TRzLabel
    Left = 186
    Top = 55
    Width = 48
    Height = 13
    Caption = #36215#22987#26102#38388
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl2: TRzLabel
    Left = 337
    Top = 55
    Width = 48
    Height = 13
    Caption = #32456#27490#26102#38388
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl3: TRzLabel
    Left = 478
    Top = 55
    Width = 36
    Height = 13
    Caption = #25152#23646#24215
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl5: TRzLabel
    Left = 590
    Top = 55
    Width = 24
    Height = 13
    Caption = #36827#20986
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 803
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
      RzToolButton3
      RzToolButton2
      RzToolButton1)
    object RzToolButton3: TRzToolButton
      Left = 4
      Top = 2
      Caption = #26597#35810
      OnClick = RzToolButton3Click
    end
    object RzToolButton1: TRzToolButton
      Left = 124
      Top = 2
      Caption = #36864#20986
      OnClick = RzToolButton1Click
    end
    object RzToolButton2: TRzToolButton
      Left = 64
      Top = 2
      Caption = #25171#21360
    end
  end
  object cbbType: TComboBox
    Left = 74
    Top = 52
    Width = 95
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    Text = #20840#37096#20379#24212#21830
  end
  object rzdbgrd2: TRzDBGrid
    Left = 0
    Top = 96
    Width = 803
    Height = 217
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = ds2
    DefaultDrawing = True
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    ReadOnly = True
    TabOrder = 2
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
        FieldName = 'TotalFixedPrice'
        PickList.Strings = (
          'dfdf')
        Title.Caption = #24635#30721#27915
        Width = 90
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'TotalDiscountedPrice'
        Title.Caption = #24635#23454#26679
        Width = 100
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
  object dtp1: TDateTimePicker
    Left = 239
    Top = 52
    Width = 85
    Height = 21
    Date = 40018.450151180560000000
    Time = 40018.450151180560000000
    TabOrder = 3
  end
  object dtp2: TDateTimePicker
    Left = 389
    Top = 52
    Width = 80
    Height = 21
    Date = 40018.450151180560000000
    Time = 40018.450151180560000000
    TabOrder = 4
  end
  object cbb1: TComboBox
    Left = 520
    Top = 52
    Width = 63
    Height = 21
    ItemHeight = 13
    TabOrder = 5
    Text = #20840#37096
  end
  object cbb2: TComboBox
    Left = 617
    Top = 52
    Width = 49
    Height = 21
    ItemHeight = 13
    TabOrder = 6
    Text = #20840#37096
    Items.Strings = (
      #36827#36135
      #36864#36135)
  end
  object chk1: TCheckBox
    Left = 675
    Top = 54
    Width = 150
    Height = 17
    Caption = #26159#21542#21253#21547#20174#26410#32467#27454#20379#24212#21830
    TabOrder = 7
  end
  object ds2: TDataSource
    DataSet = dsQuery
    Left = 288
    Top = 176
  end
  object dsQuery: TADODataSet
    Parameters = <>
    Left = 256
    Top = 160
  end
  object ds: TDataSource
    DataSet = qrySupply
    Left = 144
    Top = 120
  end
  object qrySupply: TADOQuery
    Parameters = <>
    Left = 105
    Top = 111
  end
end
