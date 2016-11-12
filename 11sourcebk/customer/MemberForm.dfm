inherited frmMember: TfrmMember
  Caption = #20250#21592#35774#32622
  ClientHeight = 591
  ClientWidth = 849
  ExplicitWidth = 865
  ExplicitHeight = 627
  PixelsPerInch = 96
  TextHeight = 13
  object rztlbr1: TRzToolbar [0]
    Left = 0
    Top = 0
    Width = 849
    Height = 29
    AutoResize = False
    AutoStyle = False
    Margin = 1
    TopMargin = 1
    RowHeight = 29
    ButtonWidth = 60
    ShowButtonCaptions = True
    ShowDivider = False
    TextOptions = ttoCustom
    WrapControls = False
    BorderInner = fsNone
    BorderOuter = fsStatus
    BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
    BorderWidth = 0
    Caption = #21024#38500
    GradientColorStyle = gcsMSOffice
    TabOrder = 0
    VisualStyle = vsGradient
    ToolbarControls = (
      RzSpacer1
      RzToolButton3
      RzToolButton4
      RzToolButton5
      RzToolButton9
      RzToolButton10
      RzToolButton1
      RzToolButton2
      RzToolButton8
      RzToolButton7
      RzToolButton6)
    object RzSpacer1: TRzSpacer
      Left = 1
      Top = 3
    end
    object RzToolButton3: TRzToolButton
      Left = 9
      Top = 3
      Width = 76
      Caption = #26597#35810#20250#21592'[Q]'
      OnClick = RzToolButton3Click
    end
    object RzToolButton4: TRzToolButton
      Left = 85
      Top = 3
      Width = 74
      Caption = #28155#21152#20250#21592'[S]'
      OnClick = RzToolButton4Click
    end
    object RzToolButton5: TRzToolButton
      Left = 159
      Top = 3
      Width = 75
      Caption = #21024#38500#20250#21592'[D]'
      OnClick = RzToolButton5Click
    end
    object RzToolButton1: TRzToolButton
      Left = 368
      Top = 3
      Width = 74
      Caption = #22686#21152#32423#21035'[Z]'
      OnClick = RzToolButton1Click
    end
    object RzToolButton2: TRzToolButton
      Left = 442
      Top = 3
      Width = 74
      Caption = #21024#38500#32423#21035'[X]'
      OnClick = RzToolButton2Click
    end
    object RzToolButton7: TRzToolButton
      Left = 591
      Top = 3
      Caption = #20805#20540'[T]'
      OnClick = RzToolButton7Click
    end
    object RzToolButton6: TRzToolButton
      Left = 651
      Top = 3
      Width = 63
      Caption = #36864#20986'[ESC]'
      OnClick = RzToolButton6Click
    end
    object RzToolButton8: TRzToolButton
      Left = 516
      Top = 3
      Width = 75
      Caption = #20462#25913#32423#21035'[C]'
      OnClick = RzToolButton8Click
    end
    object RzToolButton9: TRzToolButton
      Left = 234
      Top = 3
      Width = 74
      Caption = #20462#25913#20250#21592'[E]'
      OnClick = RzToolButton9Click
    end
    object RzToolButton10: TRzToolButton
      Left = 308
      Top = 3
    end
  end
  object RzGroupBox1: TRzGroupBox [1]
    Left = 632
    Top = 35
    Width = 216
    Height = 182
    Caption = #20250#21592#32423#21035#20449#24687
    TabOrder = 1
    DesignSize = (
      216
      182)
    object RzLabel2: TRzLabel
      Left = 15
      Top = 28
      Width = 48
      Height = 13
      Caption = #20250#21592#32423#21035
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel1: TRzLabel
      Left = 15
      Top = 55
      Width = 48
      Height = 13
      Caption = #25240'        '#25187
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object dbedtName: TRzDBEdit
      Left = 69
      Top = 25
      Width = 131
      Height = 21
      DataSource = ds2
      DataField = 'Type'
      Anchors = [akLeft, akTop, akRight]
      FrameColor = 12164479
      FrameVisible = True
      TabOrder = 0
      OnKeyPress = dbedtNameKeyPress
    end
    object dbedtName1: TRzDBEdit
      Left = 69
      Top = 52
      Width = 131
      Height = 21
      DataSource = ds2
      DataField = 'Discount'
      Anchors = [akLeft, akTop, akRight]
      FrameColor = 12164479
      FrameVisible = True
      TabOrder = 1
      OnKeyPress = dbedtName1KeyPress
    end
    object RzDBGrid1: TRzDBGrid
      Left = 1
      Top = 79
      Width = 214
      Height = 102
      Align = alBottom
      Anchors = [akLeft, akTop, akRight, akBottom]
      DataSource = ds2
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
          FieldName = 'Type'
          Title.Caption = #20250#21592#32423#21035
          Width = 93
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Discount'
          Title.Caption = #25240#25187
          Width = 104
          Visible = True
        end>
    end
  end
  object RzGroupBox2: TRzGroupBox [2]
    Left = 0
    Top = 35
    Width = 626
    Height = 183
    Caption = #20250#21592#20449#24687
    TabOrder = 2
    object RzLabel4: TRzLabel
      Left = 15
      Top = 21
      Width = 48
      Height = 13
      Caption = #26597#35810#36755#20837
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel3: TRzLabel
      Left = 15
      Top = 64
      Width = 48
      Height = 13
      Caption = #20250#21592#22995#21517
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel6: TRzLabel
      Left = 15
      Top = 155
      Width = 48
      Height = 13
      Caption = #20250#21592#22320#22336
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel7: TRzLabel
      Left = 412
      Top = 95
      Width = 48
      Height = 13
      Caption = #37038#25919#32534#30721
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel8: TRzLabel
      Left = 15
      Top = 95
      Width = 48
      Height = 13
      Caption = #30005'        '#35805
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel9: TRzLabel
      Left = 210
      Top = 95
      Width = 48
      Height = 13
      Caption = #25163'        '#26426
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel10: TRzLabel
      Left = 412
      Top = 64
      Width = 48
      Height = 13
      Caption = #24615'        '#21035
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel11: TRzLabel
      Left = 15
      Top = 125
      Width = 48
      Height = 13
      Caption = #29983'        '#26085
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel12: TRzLabel
      Left = 412
      Top = 155
      Width = 48
      Height = 13
      Caption = #24635'  '#28040'  '#36153
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel13: TRzLabel
      Left = 210
      Top = 64
      Width = 48
      Height = 13
      Caption = #20250#21592#21345#21495
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel5: TRzLabel
      Left = 412
      Top = 125
      Width = 48
      Height = 13
      Caption = #21345#20869#32467#20313
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel14: TRzLabel
      Left = 210
      Top = 125
      Width = 48
      Height = 13
      Caption = #20250#21592#31867#22411
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLabel15: TRzLabel
      Left = 302
      Top = 155
      Width = 36
      Height = 13
      Caption = #25240#25187#29575
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lblTop: TRzLabel
      Left = 306
      Top = 21
      Width = 99
      Height = 13
      Caption = #35831#36755#20837#20805#20540#37329#39069' '#65509
      Visible = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl1: TRzLabel
      Left = 499
      Top = 21
      Width = 12
      Height = 13
      Caption = #20803
      Visible = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lblcancel: TRzLabel
      Left = 517
      Top = 19
      Width = 68
      Height = 16
      Caption = #21462#28040#20805#20540
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'System'
      Font.Style = [fsBold]
      ParentFont = False
      Visible = False
      OnClick = lblcancelClick
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzEditInfor: TRzEdit
      Left = 69
      Top = 18
      Width = 122
      Height = 21
      FrameColor = 12164479
      FrameVisible = True
      MaxLength = 13
      TabOrder = 0
      OnKeyPress = RzEditInforKeyPress
    end
    object MemberType: TRzDBComboBox
      Left = 268
      Top = 119
      Width = 122
      Height = 21
      DataField = 'MemberType'
      DataSource = ds1
      ReadOnly = True
      Color = clInfoBk
      ItemHeight = 13
      TabOrder = 1
      OnKeyPress = MemberTypeKeyPress
      Items.Strings = (
        #26222#36890#20250#21592
        #39640#32423#20250#21592)
      Values.Strings = (
        '1'
        '2')
    end
    object edtName: TRzDBEdit
      Left = 69
      Top = 59
      Width = 122
      Height = 21
      DataSource = ds1
      DataField = 'Name'
      ReadOnly = True
      Color = clInfoBk
      FrameColor = 12164479
      FrameVisible = True
      TabOrder = 2
      OnKeyPress = edtNameKeyPress
    end
    object Sex: TRzDBComboBox
      Left = 466
      Top = 59
      Width = 45
      Height = 21
      DataField = 'Sex'
      DataSource = ds1
      ReadOnly = True
      Color = clInfoBk
      ItemHeight = 13
      TabOrder = 3
      OnKeyPress = SexKeyPress
      Items.Strings = (
        #30007
        #22899)
      Values.Strings = (
        '1'
        '0')
    end
    object edtName2: TRzDBEdit
      Left = 69
      Top = 92
      Width = 122
      Height = 21
      DataSource = ds1
      DataField = 'Tel'
      ReadOnly = True
      Color = clInfoBk
      FrameColor = 12164479
      FrameVisible = True
      MaxLength = 13
      TabOrder = 4
      OnKeyPress = edtName2KeyPress
    end
    object RzDBEdit3: TRzDBEdit
      Left = 268
      Top = 92
      Width = 122
      Height = 21
      DataSource = ds1
      DataField = 'Mobile'
      ReadOnly = True
      Color = clInfoBk
      FrameColor = 12164479
      FrameVisible = True
      MaxLength = 11
      TabOrder = 5
      OnKeyPress = RzDBEdit3KeyPress
    end
    object RzDBEdit4: TRzDBEdit
      Left = 268
      Top = 59
      Width = 122
      Height = 21
      DataSource = ds1
      DataField = 'CardSN'
      ReadOnly = True
      Color = clInfoBk
      FrameColor = 12164479
      FrameVisible = True
      MaxLength = 13
      TabOrder = 6
      OnKeyPress = RzDBEdit4KeyPress
    end
    object RzDBEdit5: TRzDBEdit
      Left = 466
      Top = 122
      Width = 122
      Height = 21
      DataSource = ds1
      DataField = 'Balance'
      ReadOnly = True
      Color = clInfoBk
      FrameColor = 12164479
      FrameVisible = True
      TabOrder = 7
      OnKeyPress = RzDBEdit5KeyPress
    end
    object RzDBEdit8: TRzDBEdit
      Left = 69
      Top = 151
      Width = 220
      Height = 21
      DataSource = ds1
      DataField = 'Address'
      ReadOnly = True
      Color = clInfoBk
      FrameColor = 12164479
      FrameVisible = True
      TabOrder = 8
      OnKeyPress = RzDBEdit8KeyPress
    end
    object RzDBEdit9: TRzDBEdit
      Left = 344
      Top = 151
      Width = 46
      Height = 21
      DataSource = ds1
      DataField = 'Discount'
      ReadOnly = True
      Color = clInfoBk
      FrameColor = 12164479
      FrameVisible = True
      TabOrder = 9
    end
    object RzDBEdit12: TRzDBEdit
      Left = 466
      Top = 151
      Width = 122
      Height = 21
      DataSource = ds1
      DataField = 'TotalConsumption'
      ReadOnly = True
      Color = clInfoBk
      FrameColor = 12164479
      FrameVisible = True
      TabOrder = 10
    end
    object cbbType: TComboBox
      Left = 197
      Top = 18
      Width = 76
      Height = 21
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 11
      Text = #20250#21592#21345#21495
      OnSelect = cbbTypeSelect
      Items.Strings = (
        #20250#21592#21345#21495
        #20250#21592#21495
        #20250#21592#22995#21517)
    end
    object edtTop: TRzNumericEdit
      Left = 411
      Top = 18
      Width = 79
      Height = 21
      MaxLength = 6
      TabOrder = 12
      Visible = False
      OnKeyPress = edtTopKeyPress
      Max = 1000000.000000000000000000
      DisplayFormat = ',0;(,0)'
    end
    object edtName3: TRzDBDateTimePicker
      Left = 69
      Top = 122
      Width = 122
      Height = 21
      Date = 0.496297557867365000
      Time = 0.496297557867365000
      ShowCheckbox = True
      TabOrder = 13
      OnChange = edtName3Change
      DataField = 'Birthday'
      DataSource = ds1
      ReadOnly = True
    end
  end
  object RzDBGrid: TRzDBGrid [3]
    Left = 0
    Top = 222
    Width = 849
    Height = 369
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
    DataSource = ds1
    DefaultDrawing = True
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ReadOnly = True
    TabOrder = 3
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'Id'
        Title.Caption = #20250#21592#32534#21495
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Name'
        Title.Caption = #20250#21592#21517#31216
        Width = 75
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'CardSN'
        Title.Caption = #20250#21592#21345#21495
        Width = 75
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Tel'
        Title.Caption = #30005#35805
        Width = 75
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Mobile'
        Title.Caption = #25163#26426
        Width = 75
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Birthday'
        Title.Caption = #29983#26085
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'TotalConsumption'
        Title.Caption = #24635#28040#36153
        Width = 40
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Balance'
        Title.Caption = #21345#20869#32467#20313
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Type'
        Title.Alignment = taRightJustify
        Title.Caption = #20250#21592#31867#22411
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Discount'
        Title.Caption = #20250#21592#25240#25187#29575
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'PostalCode'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Terminal'
        Font.Style = []
        Title.Caption = #37038#25919#32534#30721
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Address'
        Title.Caption = #20250#21592#22320#22336
        Visible = True
      end>
  end
  object edtName1: TRzDBEdit [4]
    Left = 467
    Top = 125
    Width = 122
    Height = 21
    DataSource = ds1
    DataField = 'PostalCode'
    ReadOnly = True
    Color = clInfoBk
    FrameColor = 12164479
    FrameVisible = True
    MaxLength = 6
    TabOrder = 4
    OnKeyPress = edtName1KeyPress
  end
  object ds1: TDataSource
    DataSet = dsetMemberSettings
    Left = 24
    Top = 112
  end
  object dsetMemberLevel: TADODataSet
    Parameters = <>
    Left = 672
    Top = 40
  end
  object ds2: TDataSource
    DataSet = dsetMemberLevel
    Left = 728
    Top = 40
  end
  object qryMemberSettings: TADOQuery
    Parameters = <>
    Left = 593
    Top = 144
  end
  object ds3: TDataSource
    DataSet = qryMemberSettings
    Left = 601
    Top = 112
  end
  object dsetMemberSettings: TADODataSet
    OnMoveComplete = dsetMemberSettingsMoveComplete
    Parameters = <>
    Left = 40
    Top = 64
  end
  object cmdDelMember: TADOCommand
    Parameters = <>
    Left = 392
    Top = 128
  end
  object cmdTop: TADOCommand
    Parameters = <>
    Left = 392
    Top = 80
  end
  object cmdTopRecord: TADOCommand
    Parameters = <>
    Left = 520
    Top = 64
  end
end
