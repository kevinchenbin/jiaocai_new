inherited frmRetailNote: TfrmRetailNote
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #38646#21806#25171#21360
  ClientHeight = 459
  ClientWidth = 461
  Color = clInactiveCaptionText
  Position = poMainFormCenter
  ExplicitWidth = 477
  ExplicitHeight = 497
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel [0]
    Left = 0
    Top = 0
    Width = 461
    Height = 459
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    DesignSize = (
      461
      459)
    object labstorage: TLabel
      Left = 9
      Top = 16
      Width = 52
      Height = 13
      Caption = #24403#21069#24215#65306
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object RzGroupBox4: TRzGroupBox
      Left = 9
      Top = 35
      Width = 448
      Height = 409
      Anchors = [akLeft, akBottom]
      BorderColor = clInactiveCaptionText
      BorderSides = [sdLeft, sdTop, sdRight]
      Caption = #25171#21360#35774#32622
      Color = 16180174
      TabOrder = 0
      object RzLabel1: TRzLabel
        Left = 11
        Top = 30
        Width = 48
        Height = 13
        Caption = #27426'  '#36814'  '#35789
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLabel3: TRzLabel
        Left = 11
        Top = 61
        Width = 48
        Height = 13
        Caption = #22320'        '#22336
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLabel4: TRzLabel
        Left = 11
        Top = 92
        Width = 48
        Height = 13
        Caption = #32852#31995#30005#35805
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLabel5: TRzLabel
        Left = 11
        Top = 126
        Width = 48
        Height = 13
        Caption = #22791'        '#27880
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLine1: TRzLine
        Left = -2
        Top = 145
        Width = 444
        Height = 20
      end
      object RzLabel6: TRzLabel
        Left = 12
        Top = 260
        Width = 92
        Height = 13
        Caption = 'POS'#25171#21360#36830#25509#31471#21475
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLabel7: TRzLabel
        Left = 12
        Top = 289
        Width = 60
        Height = 13
        Caption = #21333#25454#21015#35774#32622
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl1: TRzLabel
        Left = 15
        Top = 320
        Width = 342
        Height = 13
        Caption = #28201#39336#25552#31034#65306#25152#36873#39033#30446#35831#19981#35201#36229#36807'4'#20010#65292#21542#21017#23558#20250#24433#21709#23567#31080#25171#21360#32654#35266
        Color = 16180174
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object dbedtWelcomeMessage: TRzDBEdit
        Left = 72
        Top = 27
        Width = 353
        Height = 21
        DataSource = dsNotePrint
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 0
      end
      object dbedtAddress: TRzDBEdit
        Left = 72
        Top = 58
        Width = 353
        Height = 21
        DataSource = dsNotePrint
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 1
      end
      object dbedtTel: TRzDBEdit
        Left = 72
        Top = 89
        Width = 353
        Height = 21
        DataSource = dsNotePrint
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 2
      end
      object dbedtRemarks: TRzDBEdit
        Left = 72
        Top = 123
        Width = 353
        Height = 21
        DataSource = dsNotePrint
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 3
      end
      object CHKPrice: TRzDBCheckBox
        Left = 180
        Top = 289
        Width = 43
        Height = 15
        DataSource = dsNotePrint
        ValueChecked = '1'
        ValueUnchecked = '0'
        Caption = #23450#20215
        TabOrder = 4
      end
      object CHKBookName: TRzDBCheckBox
        Left = 117
        Top = 289
        Width = 43
        Height = 15
        DataSource = dsNotePrint
        ValueChecked = '1'
        ValueUnchecked = '0'
        Caption = #20070#21517
        TabOrder = 5
      end
      object CHKDiscount: TRzDBCheckBox
        Left = 316
        Top = 288
        Width = 43
        Height = 15
        DataSource = dsNotePrint
        ValueChecked = '1'
        ValueUnchecked = '0'
        Caption = #25240#25187
        TabOrder = 6
      end
      object btn1: TButton
        Left = 18
        Top = 346
        Width = 65
        Height = 24
        Caption = #20445#23384'[S]'
        TabOrder = 7
        OnClick = btn1Click
      end
      object btn2: TButton
        Left = 117
        Top = 346
        Width = 65
        Height = 24
        Caption = #25171#21360#27979#35797'[Z]'
        TabOrder = 8
        OnClick = btn2Cick
      end
      object btn3: TRzButton
        Left = 352
        Top = 376
        Caption = #36864#20986'[ESC]'
        TabOrder = 9
        OnClick = btn3Click
      end
      object CHKtotalamount: TRzDBCheckBox
        Left = 244
        Top = 288
        Width = 43
        Height = 15
        DataSource = dsNotePrint
        ValueChecked = '1'
        ValueUnchecked = '0'
        Caption = #25968#37327
        TabOrder = 10
      end
      object CHKjine: TRzDBCheckBox
        Left = 388
        Top = 288
        Width = 43
        Height = 15
        DataSource = dsNotePrint
        ValueChecked = '1'
        ValueUnchecked = '0'
        Caption = #37329#39069
        TabOrder = 11
      end
      object CHKCardrec: TRzDBCheckBox
        Left = 11
        Top = 171
        Width = 127
        Height = 15
        DataSource = dsNotePrint
        ValueChecked = '1'
        ValueUnchecked = '0'
        Caption = #25171#21360#20648#20540#21345#28040#36153#37329#39069
        TabOrder = 12
      end
      object CHKtotalhang: TRzDBCheckBox
        Left = 256
        Top = 171
        Width = 79
        Height = 15
        DataSource = dsNotePrint
        ValueChecked = '1'
        ValueUnchecked = '0'
        Caption = #25171#21360#27719#24635#34892
        TabOrder = 13
      end
      object Button1: TButton
        Left = 206
        Top = 346
        Width = 99
        Height = 24
        Caption = #38065#31665#24182#21475'1'#27979#35797
        TabOrder = 14
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 334
        Top = 346
        Width = 93
        Height = 24
        Caption = #38065#31665#24182#21475'2'#27979#35797
        TabOrder = 15
        OnClick = Button2Click
      end
      object dbcbbPort: TComboBox
        Left = 117
        Top = 257
        Width = 96
        Height = 21
        ItemHeight = 13
        TabOrder = 16
        Text = 'LPT1'
        Items.Strings = (
          'LPT1'
          'LPT2'
          'LPT3'
          'USB'
          'COM1'
          'COM2')
      end
      object chprintmayang: TRzDBCheckBox
        Left = 11
        Top = 225
        Width = 91
        Height = 15
        DataSource = dsNotePrint
        ValueChecked = '1'
        ValueUnchecked = '0'
        Caption = #25171#21360#21407#20215#21512#35745
        TabOrder = 17
      end
      object chprintdiscount: TRzDBCheckBox
        Left = 256
        Top = 225
        Width = 91
        Height = 15
        DataSource = dsNotePrint
        ValueChecked = '1'
        ValueUnchecked = '0'
        Caption = #25171#21360#25240#25187#37329#39069
        TabOrder = 18
      end
      object chkpostcard: TRzDBCheckBox
        Left = 11
        Top = 198
        Width = 127
        Height = 15
        DataSource = dsNotePrint
        ValueChecked = '1'
        ValueUnchecked = '0'
        Caption = #25171#21360#38134#34892#21345#28040#36153#37329#39069
        TabOrder = 19
      end
      object chkyouhuiquan: TRzDBCheckBox
        Left = 256
        Top = 198
        Width = 127
        Height = 15
        DataSource = dsNotePrint
        ValueChecked = '1'
        ValueUnchecked = '0'
        Caption = #25171#21360#20248#24800#21048#28040#36153#37329#39069
        TabOrder = 20
      end
      object rgtype: TRadioGroup
        Left = 256
        Top = 246
        Width = 175
        Height = 36
        Columns = 2
        ItemIndex = 0
        Items.Strings = (
          #23567#31080
          #26222#36890#31080#25454)
        TabOrder = 21
      end
    end
  end
  object qryRetailNoteName: TADOQuery
    Parameters = <>
    Left = 441
    Top = 96
  end
  object Ds1: TDataSource
    Left = 361
    Top = 65528
  end
  object dsNotePrint: TDataSource
    DataSet = dsetRetailNote
    Left = 408
    Top = 65528
  end
  object dsetRetailNote: TADODataSet
    Parameters = <>
    Left = 488
    Top = 8
  end
  object ds2: TDataSource
    DataSet = dsPrint
    Left = 616
    Top = 64
  end
  object dsPrint: TADODataSet
    Parameters = <>
    Left = 552
    Top = 72
  end
  object dsretail: TADODataSet
    Parameters = <>
    Left = 552
    Top = 16
  end
  object ds4: TDataSource
    DataSet = dsretail
    Left = 616
    Top = 16
  end
  object con: TADOConnection
    Left = 232
    Top = 24
  end
end
