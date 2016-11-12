inherited frmCUSDocQuery: TfrmCUSDocQuery
  Caption = #25910#27454#21333#26597#35810
  ClientHeight = 535
  ClientWidth = 682
  ExplicitWidth = 690
  ExplicitHeight = 569
  PixelsPerInch = 96
  TextHeight = 13
  object lbl4: TRzLabel [0]
    Left = 7
    Top = 42
    Width = 48
    Height = 13
    Caption = #36873#25321#23458#25143
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl1: TRzLabel [1]
    Left = 200
    Top = 42
    Width = 48
    Height = 13
    Caption = #36215#22987#26102#38388
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl3: TRzLabel [2]
    Left = 387
    Top = 42
    Width = 48
    Height = 13
    Caption = #32456#27490#26102#38388
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl2: TRzLabel [3]
    Left = 387
    Top = 87
    Width = 48
    Height = 13
    Caption = #23457#26680#24773#20917
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl6: TRzLabel [4]
    Left = 200
    Top = 87
    Width = 48
    Height = 13
    Caption = #32467#27454#31867#21035
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl5: TRzLabel [5]
    Left = 7
    Top = 87
    Width = 57
    Height = 13
    Caption = #32467' '#27454' '#26041' '#24335
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object RzToolbar1: TRzToolbar [6]
    Left = 0
    Top = 0
    Width = 682
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
  object cbbType: TComboBox [7]
    Left = 83
    Top = 39
    Width = 95
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    Text = #20840#37096#23458#25143
    OnSelect = RzToolButton3Click
  end
  object dtp1: TDateTimePicker [8]
    Left = 265
    Top = 39
    Width = 85
    Height = 21
    Date = 40018.450151180560000000
    Time = 40018.450151180560000000
    TabOrder = 2
    OnChange = RzToolButton3Click
  end
  object dtp2: TDateTimePicker [9]
    Left = 451
    Top = 39
    Width = 80
    Height = 21
    Date = 40018.450151180560000000
    Time = 40018.450151180560000000
    TabOrder = 3
    OnChange = RzToolButton3Click
  end
  object cbb2: TComboBox [10]
    Left = 451
    Top = 84
    Width = 80
    Height = 21
    ItemHeight = 13
    TabOrder = 4
    Text = #20840#37096
    OnSelect = RzToolButton3Click
    Items.Strings = (
      #26410#23457#26680
      #23457#26680)
  end
  object cbb3: TComboBox [11]
    Left = 265
    Top = 84
    Width = 80
    Height = 21
    ItemHeight = 13
    TabOrder = 5
    Text = #20840#37096
    OnSelect = RzToolButton3Click
    Items.Strings = (
      #30005#27719
      #25176#25910
      #29616#37329
      #36716#36134)
  end
  object cbb1: TComboBox [12]
    Left = 83
    Top = 84
    Width = 80
    Height = 21
    ItemHeight = 13
    TabOrder = 6
    Text = #20840#37096
    OnSelect = RzToolButton3Click
    Items.Strings = (
      #36864#27454#20184#27454
      #20313#39069#20184#27454
      #39044#20184#27454)
  end
  object rzgrpbx1: TRzGroupBox [13]
    Left = 0
    Top = 120
    Width = 681
    Height = 146
    Caption = #23458#25143#32467#27454#21333#20449#24687
    TabOrder = 7
    object rzdbgrd1: TRzDBGrid
      Left = 1
      Top = 23
      Width = 679
      Height = 122
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
      OnDblClick = rzdbgrd1DblClick
      FrameColor = 12164479
      FrameVisible = True
      Columns = <
        item
          Expanded = False
          FieldName = 'MoneyCode'
          Title.Caption = ' '#25910#27454#21333#21495
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'date'
          PickList.Strings = (
            'dfdf')
          Title.Caption = #26085#26399
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ClearingType'
          Title.Caption = #32467#27454#31867#21035
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Clearingstyle'
          Title.Caption = #32467#27454#26041#24335
          Width = 77
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Payment'
          Title.Caption = #32467#27454#37329#39069
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'State'
          Title.Caption = #23457#26680#29366#24577
          Width = 57
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
          Title.Caption = #22791#27880
          Visible = True
        end>
    end
  end
  object rzgrpbx4: TRzGroupBox [14]
    Left = -1
    Top = 266
    Width = 682
    Height = 263
    Caption = #23458#25143#24080#27454#20449#24687
    TabOrder = 8
    object rzdbgrd3: TRzDBGrid
      Left = 1
      Top = 24
      Width = 680
      Height = 238
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
          FieldName = 'StgNtCode'
          Title.Caption = #25209#38144#21333#21495
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'TotalFixedPrice'
          PickList.Strings = (
            'dfdf')
          Title.Caption = #30721#27915
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'TotalDiscountedPrice'
          Title.Caption = #23454#26679
          Width = 77
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Amount'
          Title.Caption = #25968#37327
          Width = 77
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AddCosts'
          Title.Caption = #38468#21152#36153#29992
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
          FieldName = 'HdTime'
          Title.Caption = #26085#26399
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Remarks'
          Title.Caption = #22791#27880
          Width = 98
          Visible = True
        end>
    end
  end
  object qrySupply: TADOQuery
    Parameters = <>
    Left = 121
    Top = 39
  end
  object ds: TDataSource
    DataSet = qrySupply
    Left = 152
    Top = 40
  end
  object dsSNoteHD: TADODataSet
    Parameters = <>
    Left = 200
    Top = 312
  end
  object ds2: TDataSource
    DataSet = dsSNoteHD
    Left = 256
    Top = 328
  end
  object dsDoc: TADODataSet
    Parameters = <>
    Left = 160
    Top = 160
  end
  object ds1: TDataSource
    DataSet = dsDoc
    Left = 224
    Top = 152
  end
end
