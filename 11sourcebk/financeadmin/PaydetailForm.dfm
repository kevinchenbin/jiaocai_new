inherited frmPaydetail: TfrmPaydetail
  Caption = 'frmPaydetail'
  ClientHeight = 583
  ClientWidth = 907
  ExplicitWidth = 915
  ExplicitHeight = 617
  PixelsPerInch = 96
  TextHeight = 13
  object lbl2: TRzLabel [0]
    Left = 200
    Top = 42
    Width = 48
    Height = 13
    Caption = #32467#27454#24773#20917
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl3: TRzLabel [1]
    Left = 200
    Top = 85
    Width = 48
    Height = 13
    Caption = #32456#27490#26102#38388
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl1: TRzLabel [2]
    Left = 19
    Top = 86
    Width = 48
    Height = 13
    Caption = #36215#22987#26102#38388
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object lbl4: TRzLabel [3]
    Left = 7
    Top = 42
    Width = 60
    Height = 13
    Caption = #36873#25321#20379#24212#21830
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  object RzToolbar1: TRzToolbar [4]
    Left = 0
    Top = 0
    Width = 907
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
  object cbb2: TComboBox [5]
    Left = 296
    Top = 39
    Width = 54
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    Text = #20840#37096
    OnSelect = RzToolButton3Click
    Items.Strings = (
      #26410#32467
      #24050#32467
      #23457#26680#20013)
  end
  object dtp2: TDateTimePicker [6]
    Left = 270
    Top = 82
    Width = 80
    Height = 21
    Date = 40018.450151180560000000
    Time = 40018.450151180560000000
    TabOrder = 2
    OnChange = RzToolButton3Click
  end
  object dtp1: TDateTimePicker [7]
    Left = 83
    Top = 82
    Width = 85
    Height = 21
    Date = 40018.450151180560000000
    Time = 40018.450151180560000000
    TabOrder = 3
    OnChange = RzToolButton3Click
  end
  object cbbType: TComboBox [8]
    Left = 83
    Top = 39
    Width = 95
    Height = 21
    ItemHeight = 13
    TabOrder = 4
    Text = #20840#37096#20379#24212#21830
    OnSelect = RzToolButton3Click
  end
  object rzgrpbx1: TRzGroupBox [9]
    Left = 431
    Top = 31
    Width = 401
    Height = 93
    Caption = #35813#20379#36135#21830#27719#24635#20449#24687
    TabOrder = 5
    object lbl5: TRzLabel
      Left = 11
      Top = 24
      Width = 42
      Height = 13
      Caption = #23454'      '#27915
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl6: TRzLabel
      Left = 11
      Top = 55
      Width = 48
      Height = 13
      Caption = #38468#21152#36153#29992
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl7: TRzLabel
      Left = 138
      Top = 24
      Width = 24
      Height = 13
      Caption = #24050#32467
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl8: TRzLabel
      Left = 246
      Top = 23
      Width = 24
      Height = 13
      Caption = #20313#39069
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl9: TRzLabel
      Left = 195
      Top = 54
      Width = 48
      Height = 13
      Caption = #21512#35745#24212#20184
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object edt1: TEdit
      Left = 59
      Top = 18
      Width = 72
      Height = 21
      ReadOnly = True
      TabOrder = 0
    end
    object edt2: TEdit
      Left = 165
      Top = 18
      Width = 70
      Height = 21
      ReadOnly = True
      TabOrder = 1
    end
    object edt3: TEdit
      Left = 272
      Top = 51
      Width = 73
      Height = 21
      ReadOnly = True
      TabOrder = 2
    end
    object edt4: TEdit
      Left = 60
      Top = 51
      Width = 72
      Height = 21
      ReadOnly = True
      TabOrder = 3
    end
    object edt5: TEdit
      Left = 276
      Top = 18
      Width = 70
      Height = 21
      ReadOnly = True
      TabOrder = 4
    end
  end
  object rzgrpbx2: TRzGroupBox [10]
    Left = 0
    Top = 130
    Width = 833
    Height = 191
    Caption = #20379#24212#21830#24080#27454#20449#24687
    TabOrder = 6
    object rzdbgrd2: TRzDBGrid
      Left = 1
      Top = 24
      Width = 831
      Height = 166
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
          FieldName = 'StgNtCode'
          Title.Caption = #20837#24211#21333#21495
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'TotalFixedPrice'
          PickList.Strings = (
            'dfdf')
          Title.Caption = #30721#27915
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'TotalDiscountedPrice'
          Title.Caption = #23454#26679
          Width = 100
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
          Visible = True
        end>
    end
    object rzgrpbx4: TRzGroupBox
      Left = 0
      Top = 0
      Width = 833
      Height = 191
      Caption = #20379#24212#21830#24080#27454#20449#24687
      TabOrder = 1
      object rzdbgrd3: TRzDBGrid
        Left = 1
        Top = 24
        Width = 831
        Height = 166
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
        OnDblClick = rzdbgrd3DblClick
        FrameColor = 12164479
        FrameVisible = True
        Columns = <
          item
            Expanded = False
            FieldName = 'StgNtCode'
            Title.Caption = #20837#24211#21333#21495
            Width = 77
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'TotalFixedPrice'
            PickList.Strings = (
              'dfdf')
            Title.Caption = #30721#27915
            Width = 90
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'TotalDiscountedPrice'
            Title.Caption = #23454#26679
            Width = 100
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
            Visible = True
          end>
      end
    end
  end
  object rzgrpbx3: TRzGroupBox [11]
    Left = 1
    Top = 325
    Width = 833
    Height = 260
    Caption = #20837#24211#21333#35814#32454#20449#24687
    TabOrder = 7
    object rzdbgrd1: TRzDBGrid
      Left = 1
      Top = 21
      Width = 831
      Height = 238
      Align = alBottom
      Anchors = [akLeft, akTop, akRight, akBottom]
      DataSource = ds3
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
          FieldName = 'ISBN'
          Width = 94
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Name'
          PickList.Strings = (
            'dfdf')
          Title.Caption = #20070#21517
          Width = 94
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Price'
          Title.Caption = #23450#20215
          Width = 76
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PressCount'
          Title.Caption = #29256#21035
          Width = 83
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Amount'
          Title.Caption = #25968#37327
          Width = 74
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'FixedPrice'
          Title.Caption = #30721#27915
          Width = 82
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Discount'
          Title.Caption = #25240#25187
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'DiscountedPrice'
          Title.Caption = #23454#27915
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HdTime'
          Title.Caption = #26085#26399
          Visible = True
        end>
    end
  end
  object ds: TDataSource
    DataSet = qrySupply
    Left = 152
    Top = 40
  end
  object qrySupply: TADOQuery
    Parameters = <>
    Left = 121
    Top = 39
  end
  object dsDoc: TADODataSet
    Parameters = <>
    Left = 152
    Top = 192
  end
  object ds1: TDataSource
    DataSet = dsDoc
    Left = 224
    Top = 192
  end
  object ds2: TDataSource
    DataSet = dsbalance
    Left = 784
    Top = 40
  end
  object dsbalance: TADODataSet
    Parameters = <>
    Left = 744
    Top = 40
  end
  object ds3: TDataSource
    DataSet = dsdetail
    Left = 192
    Top = 392
  end
  object dsdetail: TADODataSet
    Parameters = <>
    Left = 120
    Top = 392
  end
end
