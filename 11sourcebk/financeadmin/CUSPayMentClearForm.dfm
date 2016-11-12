inherited frmCUSPayMentClear: TfrmCUSPayMentClear
  Caption = #25910#27454#32467#31639
  ExplicitWidth = 859
  ExplicitHeight = 661
  PixelsPerInch = 96
  TextHeight = 13
  object RzToolButton8: TRzToolButton [0]
    Left = 514
    Top = 3
    Caption = #21453#23457#26680
  end
  object RzLine2: TRzLine [1]
    Left = 0
    Top = 165
    Width = 814
    Height = 20
  end
  object RzLine1: TRzLine [2]
    Left = 8
    Top = 75
    Width = 561
    Height = 20
  end
  object lbl9: TRzLabel [3]
    Left = 422
    Top = 56
    Width = 48
    Height = 13
    Caption = #26412#21333#20184#27454
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl8: TRzLabel [4]
    Left = 275
    Top = 112
    Width = 36
    Height = 13
    Caption = #19994#21153#21592
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl7: TRzLabel [5]
    Left = 8
    Top = 114
    Width = 48
    Height = 13
    Caption = #32467#31639#31867#22411
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl5: TRzLabel [6]
    Left = 250
    Top = 56
    Width = 48
    Height = 13
    Caption = #25910#27454#21333#21495
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl3: TRzLabel [7]
    Left = 422
    Top = 112
    Width = 48
    Height = 13
    Caption = #32467#31639#26085#26399
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl2: TRzLabel [8]
    Left = 144
    Top = 112
    Width = 48
    Height = 13
    Caption = #32467#31639#26041#24335
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl14: TRzLabel [9]
    Left = 8
    Top = 196
    Width = 48
    Height = 13
    Caption = #32467#31639#37329#39069
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl11: TRzLabel [10]
    Left = 8
    Top = 146
    Width = 48
    Height = 13
    Caption = #26412#21333#22791#27880
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl10: TRzLabel [11]
    Left = 422
    Top = 146
    Width = 48
    Height = 13
    Caption = #21333#25454#29366#24577
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl1: TRzLabel [12]
    Left = 8
    Top = 56
    Width = 48
    Height = 13
    Caption = #23458'        '#25143
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object rztlbr2: TRzToolbar [13]
    Left = 0
    Top = 0
    Width = 851
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
      RzToolButton3
      RzToolButton2
      RzToolButton4
      RzToolButton5
      RzToolButton6
      RzToolButton7
      RzToolButton13)
    object RzToolButton3: TRzToolButton
      Left = 1
      Top = 3
      Caption = #26597#21333'[Q]'
      OnClick = RzToolButton3Click
    end
    object RzToolButton13: TRzToolButton
      Left = 443
      Top = 3
      Width = 63
      Caption = #36864#20986'[ESC]'
      OnClick = RzToolButton13Click
    end
    object RzToolButton2: TRzToolButton
      Left = 61
      Top = 3
      Width = 87
      Caption = #28155#21152#32467#27454#21333'[A]'
      OnClick = RzToolButton2Click
    end
    object RzToolButton4: TRzToolButton
      Left = 148
      Top = 3
      Width = 87
      Caption = #21024#38500#32467#27454#21333'[D]'
      OnClick = RzToolButton4Click
    end
    object RzToolButton5: TRzToolButton
      Left = 235
      Top = 3
      Width = 80
      Caption = #26410#26680#21333#25454'[F1]'
      OnClick = RzToolButton5Click
    end
    object RzToolButton6: TRzToolButton
      Left = 315
      Top = 3
      Caption = #23457#26680'[F2]'
      OnClick = RzToolButton6Click
    end
    object RzToolButton7: TRzToolButton
      Left = 375
      Top = 3
      Width = 68
      Caption = #21453#23457#26680'[F3]'
      OnClick = RzToolButton7Click
    end
  end
  object rzgrpbx3: TRzGroupBox [14]
    Left = 262
    Top = 221
    Width = 570
    Height = 267
    Anchors = [akLeft, akTop, akBottom]
    BorderSides = [sdLeft, sdTop, sdBottom]
    Caption = #36873#25321#20320#35201#32467#31639#30340#36827#36135#21333
    TabOrder = 1
    VisualStyle = vsGradient
    object rzdbgrd1: TRzDBGrid
      Left = 1
      Top = 22
      Width = 568
      Height = 244
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
      OnDblClick = rzdbgrd1DblClick
      FrameColor = 12164479
      FrameVisible = True
      Columns = <
        item
          Expanded = False
          FieldName = 'WsaleNtCode'
          Title.Caption = #36827#36135#21333#21495
          Width = 83
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HdTime'
          Title.Caption = #36827#36135#26085#26399
          Width = 74
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'TotalFixedPrice'
          Title.Caption = #36827#36135#30721#27915
          Width = 67
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'TotalDiscountedPrice'
          Title.Caption = #36827#36135#23454#27915
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AddCosts'
          Title.Caption = #38468#21152#36153#29992
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Checked'
          Title.Caption = #24050#32467
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'NoChecked'
          Title.Caption = #26410#32467
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'State'
          Title.Caption = #29366#24577
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Remarks'
          Title.Caption = #21333#25454#22791#27880
          Width = 54
          Visible = True
        end>
    end
  end
  object rzgrpbx2: TRzGroupBox [15]
    Left = 8
    Top = 219
    Width = 193
    Height = 269
    Anchors = [akLeft, akTop, akBottom]
    BorderSides = [sdLeft, sdTop, sdBottom]
    Caption = #26412#21333#32467#31639#20449#24687
    TabOrder = 2
    VisualStyle = vsGradient
    DesignSize = (
      193
      269)
    object lst: TStringGrid
      Left = 7
      Top = 24
      Width = 178
      Height = 233
      Anchors = [akLeft, akTop, akRight, akBottom]
      ColCount = 2
      DefaultColWidth = 86
      DefaultRowHeight = 18
      FixedCols = 0
      RowCount = 1
      FixedRows = 0
      TabOrder = 0
      OnDblClick = lstDblClick
      OnSelectCell = lstSelectCell
    end
  end
  object rzgrpbx1: TRzGroupBox [16]
    Left = 591
    Top = 42
    Width = 223
    Height = 129
    Caption = #20379#24212#21830#24080#27454#20449#24687
    TabOrder = 3
    VisualStyle = vsGradient
    object lbl4: TRzLabel
      Left = 16
      Top = 37
      Width = 48
      Height = 13
      Caption = #36134#25143#32467#20313
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl6: TRzLabel
      Left = 16
      Top = 61
      Width = 48
      Height = 13
      Caption = #26399#21021#27424#27454
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl13: TRzLabel
      Left = 16
      Top = 87
      Width = 48
      Height = 13
      Caption = #24635'  '#24212'  '#20184
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object edtName1: TRzDBEdit
      Left = 81
      Top = 29
      Width = 112
      Height = 21
      DataSource = ds1
      DataField = 'Balance'
      ReadOnly = True
      Color = clInfoBk
      FrameColor = 12164479
      FrameVisible = True
      TabOrder = 0
    end
    object edtName2: TRzDBEdit
      Left = 81
      Top = 56
      Width = 112
      Height = 21
      DataSource = ds1
      DataField = 'BusinessLessBookstore'
      ReadOnly = True
      Color = clInfoBk
      FrameColor = 12164479
      FrameVisible = True
      TabOrder = 1
    end
    object edt1: TEdit
      Left = 81
      Top = 85
      Width = 112
      Height = 21
      ReadOnly = True
      TabOrder = 2
    end
  end
  object RzButton3: TRzButton [17]
    Left = 207
    Top = 359
    Width = 49
    Height = 26
    Caption = #12299#12299#12299
    TabOrder = 4
    OnClick = RzButton3Click
  end
  object RzButton2: TRzButton [18]
    Left = 264
    Top = 190
    Width = 92
    Caption = #33258#21160#32467#31639
    TabOrder = 5
    OnClick = RzButton2Click
  end
  object RzButton1: TRzButton [19]
    Left = 207
    Top = 304
    Width = 49
    Caption = #12298#12298#12298
    TabOrder = 6
    OnClick = RzButton1Click
  end
  object edtNum: TEdit [20]
    Left = 303
    Top = 52
    Width = 107
    Height = 21
    ReadOnly = True
    TabOrder = 7
  end
  object edtMoney: TEdit [21]
    Left = 61
    Top = 192
    Width = 124
    Height = 21
    MaxLength = 7
    TabOrder = 8
    OnKeyPress = edtMoneyKeyPress
  end
  object edt6: TEdit [22]
    Left = 317
    Top = 109
    Width = 93
    Height = 21
    TabOrder = 9
    OnKeyPress = edt6KeyPress
  end
  object edt5: TEdit [23]
    Left = 474
    Top = 109
    Width = 94
    Height = 21
    ReadOnly = True
    TabOrder = 10
  end
  object edt4: TEdit [24]
    Left = 474
    Top = 143
    Width = 94
    Height = 21
    ReadOnly = True
    TabOrder = 11
  end
  object edt3: TEdit [25]
    Left = 61
    Top = 143
    Width = 350
    Height = 21
    TabOrder = 12
    OnKeyPress = edt3KeyPress
  end
  object edt2: TEdit [26]
    Left = 474
    Top = 52
    Width = 91
    Height = 21
    ReadOnly = True
    TabOrder = 13
  end
  object cbbType: TComboBox [27]
    Left = 60
    Top = 52
    Width = 179
    Height = 21
    ItemHeight = 13
    TabOrder = 14
    Text = #36873#25321#23458#25143
    OnSelect = cbbTypeSelect
  end
  object cbb2: TComboBox [28]
    Left = 195
    Top = 109
    Width = 70
    Height = 21
    ItemHeight = 13
    TabOrder = 15
    Text = #36873#25321#31867#22411
    OnSelect = cbb2Select
    Items.Strings = (
      #29616#37329
      #36716#36134
      #30005#27719
      #25176#25910)
  end
  object cbb1: TComboBox [29]
    Left = 60
    Top = 109
    Width = 76
    Height = 21
    ItemHeight = 13
    TabOrder = 16
    Text = #36873#25321#31867#22411
    OnSelect = cbb1Select
    Items.Strings = (
      #36864#27454#20184#27454
      #20313#39069#32467#27454
      #39044#20184#27454)
  end
  object rzgrpbx6: TRzGroupBox [30]
    Left = 359
    Top = 375
    Width = 593
    Height = 267
    Anchors = [akLeft, akTop, akBottom]
    BorderSides = [sdLeft, sdTop, sdBottom]
    Caption = #26597#35810#30340#21333#25454#20449#24687
    GroupStyle = gsTopLine
    TabOrder = 17
    Visible = False
    VisualStyle = vsGradient
    object lbl12: TRzLabel
      Left = 10
      Top = 28
      Width = 72
      Height = 13
      Caption = #36755#20837#25910#27454#21333#21495
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object rzdbgrd2: TRzDBGrid
      Left = 0
      Top = 51
      Width = 593
      Height = 216
      Align = alBottom
      Anchors = [akLeft, akTop, akRight, akBottom]
      DataSource = ds6
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
          FieldName = 'CustmerName'
          Title.Caption = #23458#25143
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'MoneyCode'
          Title.Caption = #25910#27454#21333#21495
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'State'
          Title.Caption = #21333#25454#29366#24577
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Payment'
          Title.Caption = #26412#21333#20184#27454
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'date'
          Title.Caption = #32467#27454#26085#26399
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ClearingType'
          Title.Caption = #32467#31639#31867#22411
          Width = 61
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Clearingstyle'
          Title.Caption = #32467#31639#26041#24335
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Salesman'
          Title.Caption = #19994#21153#21592
          Width = 54
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Remarks'
          Title.Caption = #21333#25454#22791#27880
          Width = 54
          Visible = True
        end>
    end
    object RzButton8: TRzButton
      Left = 233
      Top = 19
      Width = 68
      Caption = #21453#23457#26680
      TabOrder = 1
      OnClick = RzButton8Click
    end
    object RzButton10: TRzButton
      Left = 321
      Top = 19
      Width = 67
      Caption = #36864#20986
      TabOrder = 2
      OnClick = RzButton10Click
    end
    object edtquery: TEdit
      Left = 87
      Top = 23
      Width = 107
      Height = 21
      MaxLength = 7
      ReadOnly = True
      TabOrder = 3
      OnKeyPress = edtqueryKeyPress
    end
  end
  object rzgrpbx7: TRzGroupBox [31]
    Left = 235
    Top = 191
    Width = 572
    Height = 267
    Anchors = [akLeft, akTop, akBottom]
    BorderSides = [sdLeft, sdTop, sdBottom]
    Caption = #36873#25321#20320#35201#23457#26680#30340#21333#25454
    GradientColorStyle = gcsMSOffice
    TabOrder = 18
    Visible = False
    VisualStyle = vsGradient
    object rzdbgrd4: TRzDBGrid
      Left = 1
      Top = 55
      Width = 570
      Height = 211
      Align = alBottom
      Anchors = [akLeft, akTop, akRight, akBottom]
      DataSource = ds4
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
          FieldName = 'CustmerName'
          Title.Caption = #23458#25143
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'MoneyCode'
          Title.Caption = #25910#27454#21333#21495
          Width = 83
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Payment'
          Title.Caption = #26412#21333#20184#27454
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'date'
          Title.Caption = #32467#27454#26085#26399
          Width = 74
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ClearingType'
          Title.Caption = #32467#31639#31867#22411
          Width = 67
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Clearingstyle'
          Title.Caption = #32467#31639#26041#24335
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Salesman'
          Title.Caption = #19994#21153#21592
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Remarks'
          Title.Caption = #21333#25454#22791#27880
          Width = 54
          Visible = True
        end>
    end
    object RzButton11: TRzButton
      Left = 13
      Top = 24
      Width = 68
      Caption = #23457#26680
      TabOrder = 1
      OnClick = RzButton11Click
    end
    object RzButton12: TRzButton
      Left = 106
      Top = 23
      Width = 66
      Caption = #20840#37096#23457#26680
      TabOrder = 2
      OnClick = RzButton12Click
    end
    object RzButton13: TRzButton
      Left = 198
      Top = 23
      Width = 67
      Caption = #36864#20986
      TabOrder = 3
      OnClick = RzButton13Click
    end
  end
  object cmdcheck: TADOCommand
    Parameters = <>
    Left = 304
    Top = 96
  end
  object qrySupply: TADOQuery
    Parameters = <>
    Left = 121
    Top = 127
  end
  object ds: TDataSource
    DataSet = qrySupply
    Left = 152
    Top = 56
  end
  object ds2: TDataSource
    DataSet = dsPurchase
    Left = 560
    Top = 184
  end
  object dsPurchase: TADODataSet
    Parameters = <>
    Left = 512
    Top = 184
  end
  object dstruncheck: TADODataSet
    Parameters = <>
    Left = 512
    Top = 280
  end
  object ds7: TDataSource
    DataSet = dstruncheck
    Left = 552
    Top = 280
  end
  object cmdtruncheck: TADOCommand
    Parameters = <>
    Left = 488
    Top = 360
  end
  object cmdState: TADOCommand
    Parameters = <>
    Left = 328
    Top = 304
  end
  object ds6: TDataSource
    DataSet = dsQuery
    Left = 272
    Top = 304
  end
  object dsQuery: TADODataSet
    Parameters = <>
    Left = 232
    Top = 304
  end
  object dscheck: TADODataSet
    Parameters = <>
    Left = 216
    Top = 272
  end
  object ds5: TDataSource
    DataSet = dscheck
    Left = 248
    Top = 240
  end
  object cmdNewDocuments: TADOCommand
    Parameters = <>
    Left = 232
    Top = 64
  end
  object ds4: TDataSource
    DataSet = dsNewDoc
    Left = 504
    Top = 96
  end
  object dsNewDoc: TADODataSet
    Parameters = <>
    Left = 432
    Top = 96
  end
  object ds3: TDataSource
    DataSet = qryTotal
    Left = 712
    Top = 144
  end
  object qryTotal: TADOQuery
    Parameters = <>
    Left = 665
    Top = 135
  end
  object ds1: TDataSource
    DataSet = dsSupplyInit
    Left = 744
    Top = 32
  end
  object dsSupplyInit: TADODataSet
    Parameters = <>
    Left = 704
    Top = 32
  end
  object cmddel: TADOCommand
    Parameters = <>
    Left = 128
    Top = 40
  end
  object dsdel: TADODataSet
    Parameters = <>
    Left = 200
    Top = 24
  end
  object ds9: TDataSource
    DataSet = dsdel
    Left = 248
    Top = 32
  end
end
