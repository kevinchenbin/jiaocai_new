inherited frmMemberVoucher: TfrmMemberVoucher
  Caption = #20250#21592#20805#20540#35760#24405#26597#35810
  ClientHeight = 448
  ClientWidth = 761
  ExplicitWidth = 769
  ExplicitHeight = 482
  PixelsPerInch = 96
  TextHeight = 13
  object 会员充值记录查询: TRzGroupBox [0]
    Left = 0
    Top = 33
    Width = 761
    Height = 136
    Caption = #20250#21592#20805#20540#35760#24405#26597#35810
    TabOrder = 0
    object lblInfor: TRzLabel
      Left = 16
      Top = 25
      Width = 72
      Height = 13
      Caption = #36755#20837#20250#21592#20449#24687
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl1: TLabel
      Left = 314
      Top = 25
      Width = 48
      Height = 13
      Caption = #36215#22987#26102#38388
    end
    object lbl2: TLabel
      Left = 482
      Top = 25
      Width = 48
      Height = 13
      Caption = #32467#26463#26102#38388
    end
    object cbbType: TComboBox
      Left = 216
      Top = 22
      Width = 71
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      Text = #36873#25321#31867#22411
      OnSelect = cbbTypeSelect
      Items.Strings = (
        #20250#21592#21345#21495
        #20250#21592#21495
        #20250#21592#22995#21517)
    end
    object RzEditInfor: TRzEdit
      Left = 90
      Top = 22
      Width = 122
      Height = 21
      FrameColor = 12164479
      FrameVisible = True
      TabOrder = 1
      OnKeyPress = RzEditInforKeyPress
    end
    object dtp1: TDateTimePicker
      Left = 368
      Top = 22
      Width = 81
      Height = 21
      Date = 0.592891886582947300
      Time = 0.592891886582947300
      TabOrder = 2
    end
    object dtp2: TDateTimePicker
      Left = 536
      Top = 22
      Width = 89
      Height = 21
      Date = 40042.593076342590000000
      Time = 40042.593076342590000000
      TabOrder = 3
    end
  end
  object rztlbr1: TRzToolbar [1]
    Left = 0
    Top = 0
    Width = 761
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
    ToolbarControls = (
      RzToolButton1
      RzToolButton5)
    object RzToolButton1: TRzToolButton
      Left = 4
      Top = 2
      Caption = #26597#35810'[Q]'
      OnClick = RzToolButton1Click
    end
    object RzToolButton5: TRzToolButton
      Left = 64
      Top = 2
      Width = 63
      Caption = #36864#20986'[ESC]'
      OnClick = RzToolButton5Click
    end
  end
  object rzdbgrd1: TRzDBGrid [2]
    Left = 0
    Top = 104
    Width = 761
    Height = 344
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = ds1
    DefaultDrawing = True
    ReadOnly = True
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'Tid'
        Title.Caption = #27969#27700#21495
        Width = 39
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Name'
        Title.Caption = #20250#21592#22995#21517
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ID'
        Title.Caption = #20250#21592#21495
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'CardSN'
        Title.Caption = #20250#21592#21345#21495
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'date'
        Title.Caption = #20805#20540#26102#38388
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'VoucherAmount'
        Title.Caption = #26412#27425#20805#20540#37329#39069
        Width = 79
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'BeforeVoucherAmount'
        Title.Caption = #26412#27425#20805#20540#21069#20313#39069
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'AfterVoucherAmount'
        Title.Caption = #20805#20540#21518#20313#39069
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'MIType'
        Title.Caption = #20250#21592#31867#22411
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Discount'
        Title.Caption = #20250#21592#25240#25187
        Width = 67
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'TotalConsumption'
        Title.Caption = #24635#28040#36153#37329#39069
        Visible = True
      end>
  end
  object dsetMemberVoucher: TADODataSet
    Parameters = <>
    Left = 128
    Top = 232
  end
  object ds1: TDataSource
    DataSet = dsetMemberVoucher
    Left = 200
    Top = 232
  end
end
