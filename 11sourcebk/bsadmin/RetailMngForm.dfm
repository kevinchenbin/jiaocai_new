inherited frmRetailMng: TfrmRetailMng
  BorderStyle = bsSingle
  Caption = 'POS'#38646#21806
  ClientHeight = 662
  ClientWidth = 1026
  Position = poMainFormCenter
  WindowState = wsMaximized
  OnKeyDown = FormKeyDown
  ExplicitLeft = -138
  ExplicitWidth = 1032
  ExplicitHeight = 690
  PixelsPerInch = 96
  TextHeight = 13
  object rztlbr1: TRzToolbar [0]
    Left = 0
    Top = 0
    Width = 1026
    Height = 33
    AutoResize = False
    AutoStyle = False
    Images = ImageList1
    Margin = 1
    TopMargin = 1
    RowHeight = 29
    ButtonWidth = 60
    ShowButtonCaptions = True
    ShowDivider = False
    TextOptions = ttoCustom
    WrapControls = False
    BorderInner = fsNone
    BorderOuter = fsNone
    BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
    BorderWidth = 0
    Caption = #21024#38500
    Color = clSkyBlue
    Ctl3D = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    GradientColorStyle = gcsMSOffice
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 0
    VisualStyle = vsClassic
    ToolbarControls = (
      tlbtn8
      BtnNew
      tlbtn1
      tlbtn2
      tlbtn3
      BtnUpOneLevel
      tlbtn4
      BtnAttachFiles
      tlbtnMixed
      tlbtnRecMoney
      BtnPrint
      BtnFinish
      BtnReminder
      BtnAlignClient
      BtnView
      BtnAlignBottom
      tlbtn7)
    object tlbtn8: TRzToolButton
      Tag = 1
      Left = 1
      Top = -3
      Width = 60
      Height = 36
      ImageIndex = 6
      UseToolbarButtonSize = False
      Caption = #26597#21333'[F1]'
      OnClick = tlbtn8Click
    end
    object tlbtn1: TRzToolButton
      Tag = 3
      Left = 121
      Top = -3
      Width = 60
      Height = 36
      ImageIndex = 2
      UseToolbarButtonSize = False
      Caption = #21024#21333'[F9]'
      Visible = False
      OnClick = tlbtn8Click
    end
    object tlbtn2: TRzToolButton
      Tag = 5
      Left = 181
      Top = -3
      Width = 60
      Height = 36
      ImageIndex = 8
      UseToolbarButtonSize = False
      Caption = #21024#34892'[F5]'
      OnClick = tlbtn8Click
    end
    object tlbtn3: TRzToolButton
      Tag = 6
      Left = 241
      Top = -3
      Width = 60
      Height = 36
      ImageIndex = 10
      UseToolbarButtonSize = False
      Caption = #32479#19968'[F6]'
      OnClick = tlbtn8Click
    end
    object tlbtn4: TRzToolButton
      Tag = 7
      Left = 361
      Top = -3
      Width = 60
      Height = 36
      UseToolbarButtonSize = False
      Caption = #20250#21592#21345#13'[F4]'
      Visible = False
      OnClick = tlbtn4Click
    end
    object tlbtnRecMoney: TRzToolButton
      Left = 550
      Top = -3
      Width = 60
      Height = 36
      UseToolbarButtonSize = False
      Caption = #30452#25509#25910#27454'[F12]'
      OnClick = tlbtnRecMoneyClick
    end
    object tlbtnMixed: TRzToolButton
      Left = 491
      Top = -3
      Width = 59
      Height = 36
      UseToolbarButtonSize = False
      Caption = #28151#21512#25910#27454'[F8]'
      Visible = False
      OnClick = tlbtnMixedClick
    end
    object tlbtn7: TRzToolButton
      Left = 939
      Top = -3
      Width = 60
      Height = 36
      ImageIndex = 12
      UseToolbarButtonSize = False
      Caption = #36864#20986#13'(&Q)'
      OnClick = tlbtn7Click
    end
    object BtnNew: TRzToolButton
      Tag = 2
      Left = 61
      Top = -3
      Width = 60
      Height = 36
      Hint = 'New'
      DisabledIndex = 15
      ImageIndex = 14
      UseToolbarButtonSize = False
      Caption = #22686#21333'[F2]'
      OnClick = tlbtn8Click
    end
    object BtnFinish: TRzToolButton
      Left = 670
      Top = -3
      Width = 60
      Height = 36
      Hint = 'Finish'
      DisabledIndex = 17
      ImageIndex = 16
      UseToolbarButtonSize = False
      Caption = #34917#20070#19978#26550
      OnClick = BtnFinishClick
    end
    object BtnReminder: TRzToolButton
      Left = 730
      Top = -3
      Width = 70
      Height = 36
      Hint = 'Reminder'
      DisabledIndex = 19
      ImageIndex = 18
      UseToolbarButtonSize = False
      Caption = #25209#38144#29616#22330#25910#27454'[F11]'
      OnClick = BtnReminderClick
    end
    object BtnAlignClient: TRzToolButton
      Left = 800
      Top = -3
      Width = 19
      Height = 36
      Hint = 'Align Client'
      DisabledIndex = 21
      ImageIndex = 20
      UseToolbarButtonSize = False
      Caption = #38145#23631
      Visible = False
      OnClick = BtnAlignClientClick
    end
    object BtnView: TRzToolButton
      Left = 819
      Top = -3
      Width = 60
      Height = 36
      Hint = 'View'
      DisabledIndex = 23
      ImageIndex = 22
      UseToolbarButtonSize = False
      Caption = #26597#20070#13'(&F)'
      OnClick = BtnViewClick
    end
    object BtnAttachFiles: TRzToolButton
      Left = 421
      Top = -3
      Width = 70
      Height = 36
      Hint = 'Attach Files'
      DisabledIndex = 25
      ImageIndex = 24
      UseToolbarButtonSize = False
      Caption = #20250#21592#20449#24687#38142#25509'[F7]'
      Visible = False
      OnClick = BtnAttachFilesClick
    end
    object BtnAlignBottom: TRzToolButton
      Left = 879
      Top = -3
      Width = 60
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 27
      ImageIndex = 26
      UseToolbarButtonSize = False
      Caption = #26368#23567#21270#13'(&N)'
      OnClick = BtnAlignBottomClick
    end
    object BtnUpOneLevel: TRzToolButton
      Left = 301
      Top = -3
      Width = 60
      Height = 36
      Hint = 'Up One Level'
      DisabledIndex = 31
      ImageIndex = 30
      UseToolbarButtonSize = False
      Caption = #38065#31665#13'[F3]'
      OnClick = BtnUpOneLevelClick
    end
    object BtnPrint: TRzToolButton
      Left = 610
      Top = -3
      Width = 60
      Height = 36
      Hint = 'Print'
      DisabledIndex = 33
      ImageIndex = 32
      UseToolbarButtonSize = False
      Caption = #25171#21360#13'[F10]'
      OnClick = BtnPrintClick
    end
  end
  object Panel1: TPanel [1]
    Left = 0
    Top = 33
    Width = 1026
    Height = 629
    Align = alClient
    BevelInner = bvLowered
    Caption = 'Panel1'
    Color = 16180174
    Ctl3D = False
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 1
    object grpbxNtHeader: TGroupBox
      Left = 5
      Top = 6
      Width = 998
      Height = 86
      Caption = #38646#21806#21333
      Ctl3D = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
      object lbl2: TRzLabel
        Left = 5
        Top = 26
        Width = 48
        Height = 13
        Caption = #20250#21592#21517#31216
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl4: TRzLabel
        Left = 255
        Top = 25
        Width = 24
        Height = 13
        Caption = #21333#21495
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object Label3: TLabel
        Left = 536
        Top = 25
        Width = 30
        Height = 13
        Caption = #22791'  '#27880
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object RzButton1: TSpeedButton
        Left = 213
        Top = 22
        Width = 23
        Height = 19
        Caption = #26032
        Flat = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        OnClick = RzButton1Click
      end
      object Label1: TLabel
        Left = 548
        Top = 60
        Width = 14
        Height = 14
        Caption = '%'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lbl5: TRzLabel
        Left = 653
        Top = 153
        Width = 48
        Height = 13
        Caption = #24403#21069#24211#23384
        Visible = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl8: TRzLabel
        Left = 310
        Top = 60
        Width = 44
        Height = 14
        Caption = #25968#37327'[&S]'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl9: TRzLabel
        Left = 441
        Top = 60
        Width = 45
        Height = 14
        Caption = #25240#25187'[&D]'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lblCatalog: TRzLabel
        Left = 27
        Top = 60
        Width = 26
        Height = 14
        Alignment = taRightJustify
        Caption = #20070#21495
        DragCursor = crHandPoint
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold, fsUnderline]
        ParentFont = False
        PopupMenu = pm
        OnMouseDown = lblCatalogMouseDown
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLabel1: TRzLabel
        Left = 798
        Top = 155
        Width = 24
        Height = 13
        Caption = #24211#20301
        Visible = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLabel5: TRzLabel
        Left = 591
        Top = 60
        Width = 26
        Height = 14
        Caption = #21806#20215
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object dbedtRetailNtCode: TRzDBEdit
        Left = 285
        Top = 22
        Width = 110
        Height = 21
        DataSource = dsrcNtHeader
        DataField = 'RetailNtCode'
        ReadOnly = True
        Ctl3D = True
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentCtl3D = False
        ParentFont = False
        ReadOnlyColor = clWindow
        TabOrder = 1
      end
      object dblkpcbbMemberID: TRzDBLookupComboBox
        Left = 56
        Top = 22
        Width = 154
        Height = 21
        Color = clHighlightText
        Ctl3D = True
        DataField = 'MemberID'
        DataSource = dsrcNtHeader
        DropDownRows = 0
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        KeyField = 'ID'
        ListField = 'Name'
        ListSource = dsrcMember
        ParentCtl3D = False
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
        OnExit = dblkpcbbMemberIDExit
        OnKeyPress = dblkpcbbMemberIDKeyPress
        DisabledColor = clWhite
        FocusColor = clInfoBk
        ReadOnlyColor = clHighlightText
      end
      object cbbkstackID: TComboBox
        Left = 828
        Top = 151
        Width = 120
        Height = 21
        Ctl3D = False
        Enabled = False
        ImeName = #29579#30721#20116#31508#22411#36755#20837#27861'86'#29256
        ItemHeight = 13
        ParentCtl3D = False
        TabOrder = 3
        Visible = False
        OnExit = cbbkstackIDExit
      end
      object chckbxSwitch: TRzCheckBox
        Left = 815
        Top = 134
        Width = 115
        Height = 28
        Caption = #22238#36710#26102#20999#25442#22270#20070#26597#35810#27169#24335
        Checked = True
        State = cbChecked
        TabOrder = 4
        Visible = False
      end
      object dbnbedtAmount: TRzDBNumericEdit
        Left = 356
        Top = 58
        Width = 60
        Height = 21
        DataSource = dsrcNote
        DataField = 'Amount'
        Alignment = taLeftJustify
        Ctl3D = True
        DisabledColor = clWhite
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 5
        OnExit = dbnbedtAmountExit
        OnKeyPress = dbnbedtAmountKeyPress
        Max = 20000.000000000000000000
        DisplayFormat = '###,##0;-###,##0'
      end
      object dbnbedtDiscount: TRzDBNumericEdit
        Left = 486
        Top = 58
        Width = 60
        Height = 21
        DataSource = dsrcNote
        DataField = 'Discount'
        Alignment = taLeftJustify
        Ctl3D = True
        DisabledColor = clWhite
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 6
        OnExit = dbnbedtDiscountExit
        OnKeyPress = dbnbedtDiscountKeyPress
        BlankValue = 100.000000000000000000
        CheckRange = True
        IntegersOnly = False
        Max = 100.000000000000000000
        DisplayFormat = '##0.00'
      end
      object dbnbedtTotalAmount: TRzDBNumericEdit
        Left = 707
        Top = 151
        Width = 72
        Height = 19
        DataSource = dsrcNote
        DataField = 'TotalAmount'
        ReadOnly = True
        Alignment = taLeftJustify
        Ctl3D = False
        DisabledColor = clWhite
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        FrameColor = clCream
        FrameHotColor = clCream
        ImeName = #29579#30721#20116#31508#22411#36755#20837#27861'86'#29256
        ParentCtl3D = False
        ParentFont = False
        ReadOnlyColor = clWhite
        TabOrder = 7
        Visible = False
        DisplayFormat = '###,##0;-###,##0'
      end
      object edtCatalog: TRzEdit
        Left = 55
        Top = 58
        Width = 153
        Height = 21
        Ctl3D = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        MaxLength = 13
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 0
        OnKeyPress = edtCatalogKeyPress
      end
      object RzButton2: TRzButton
        Left = 890
        Top = 20
        Width = 53
        Caption = #36864#25442'(&E)'
        Color = 16180174
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 8
        OnClick = RzButton2Click
      end
      object RzButton3: TRzButton
        Left = 890
        Top = 51
        Width = 53
        Caption = #25442#25187'(&G)'
        Color = 16180174
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 9
        OnClick = RzButton3Click
      end
      object GroupBox5: TGroupBox
        Left = 6
        Top = 46
        Width = 823
        Height = 7
        TabOrder = 10
      end
      object RzButton4: TRzButton
        Left = 835
        Top = 20
        Width = 55
        Caption = #25346#21333'(&A)'
        Color = 16180174
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 11
        OnClick = RzButton4Click
      end
      object RzButton5: TRzButton
        Left = 836
        Top = 51
        Width = 54
        Caption = #25552#21333'(&W)'
        Color = 16180174
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 12
        OnClick = RzButton5Click
      end
      object membk: TMemo
        Left = 572
        Top = 21
        Width = 257
        Height = 22
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 13
        OnExit = membkExit
      end
      object edprice: TEdit
        Left = 617
        Top = 58
        Width = 60
        Height = 21
        BiDiMode = bdRightToLeft
        Ctl3D = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentBiDiMode = False
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 14
        OnKeyPress = edpriceKeyPress
      end
      object RzButton6: TRzButton
        Left = 942
        Top = 51
        Width = 53
        Caption = #25442#20215'(&B)'
        Color = 16180174
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 15
        OnClick = RzButton6Click
      end
      object chqikan: TCheckBox
        Left = 214
        Top = 60
        Width = 62
        Height = 17
        Caption = #26399#21002'(&X)'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 16
        OnClick = chqikanClick
      end
      object edqikan: TEdit
        Left = 178
        Top = 58
        Width = 32
        Height = 21
        Ctl3D = True
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        NumbersOnly = True
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 17
        Visible = False
        OnKeyPress = edqikanKeyPress
      end
      object RzButton7: TRzButton
        Left = 942
        Top = 20
        Width = 53
        Caption = #26041#26696'(&R)'
        Color = 16180174
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 18
        OnClick = RzButton7Click
      end
      object chdingwei: TCheckBox
        Left = 736
        Top = 59
        Width = 59
        Height = 17
        Caption = #23450#20301'(&C)'
        Color = 16180174
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentColor = False
        ParentFont = False
        TabOrder = 19
      end
    end
    object GroupBox1: TGroupBox
      Left = 5
      Top = 552
      Width = 319
      Height = 72
      Caption = #19978#31508#21333#25454
      Ctl3D = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 1
      object lbl10: TRzLabel
        Left = 17
        Top = 48
        Width = 30
        Height = 13
        Caption = #20876'  '#25968
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl15: TRzLabel
        Left = 173
        Top = 22
        Width = 30
        Height = 13
        Caption = #25214'  '#38646
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl16: TRzLabel
        Left = 173
        Top = 48
        Width = 30
        Height = 13
        Caption = #25910'  '#29616
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl6: TRzLabel
        Left = 17
        Top = 22
        Width = 30
        Height = 13
        Caption = #37329'  '#39069
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object numedtCheck: TRzNumericEdit
        Left = 209
        Top = 19
        Width = 99
        Height = 21
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        FocusColor = clCream
        ImeName = #29579#30721#20116#31508#22411#36755#20837#27861'86'#29256
        ParentFont = False
        ReadOnly = True
        ReadOnlyColor = clCream
        TabOrder = 0
        IntegersOnly = False
        DisplayFormat = #65509'###,##0.0;-'#65509'###,##0.0'
      end
      object numedtDiscountedMoney: TRzNumericEdit
        Left = 56
        Top = 19
        Width = 99
        Height = 21
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        FocusColor = clCream
        ImeName = #29579#30721#20116#31508#22411#36755#20837#27861'86'#29256
        ParentFont = False
        ReadOnly = True
        ReadOnlyColor = clCream
        TabOrder = 1
        DisplayFormat = #65509'###,##0.0;-'#65509'###,##0.0'
      end
      object numedtRec: TRzNumericEdit
        Left = 209
        Top = 45
        Width = 99
        Height = 21
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        FocusColor = clCream
        ImeName = #29579#30721#20116#31508#22411#36755#20837#27861'86'#29256
        ParentFont = False
        ReadOnly = True
        ReadOnlyColor = clCream
        TabOrder = 2
        DisplayFormat = #65509'###,##0.0;-'#65509'###,##0.0'
      end
      object numedtTotalAmount: TRzNumericEdit
        Left = 56
        Top = 45
        Width = 99
        Height = 21
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        FocusColor = clCream
        ImeName = #29579#30721#20116#31508#22411#36755#20837#27861'86'#29256
        ParentFont = False
        ReadOnly = True
        ReadOnlyColor = clCream
        TabOrder = 3
        DisplayFormat = '###,##0;-###,##0'
      end
    end
    object dbgrdNote: TRzDBGrid
      Left = 5
      Top = 95
      Width = 998
      Height = 369
      Ctl3D = True
      DataSource = dsrcNote
      DefaultDrawing = True
      FixedColor = 16180174
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
      ParentCtl3D = False
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
      TitleFont.Charset = ANSI_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -13
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnCellClick = dbgrdNoteCellClick
      DisabledColor = cl3DLight
      FixedLineColor = clDefault
      LineColor = clBtnShadow
      AltRowShadingFixed = False
      Columns = <
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'xuhao'
          Title.Alignment = taCenter
          Title.Caption = #24207#21495
          Width = 40
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ISBN'
          Title.Alignment = taCenter
          Width = 108
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'CatalogName'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 286
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Price'
          Title.Alignment = taCenter
          Title.Caption = #23450#20215
          Width = 68
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Amount'
          Title.Alignment = taCenter
          Title.Caption = #25968#37327
          Width = 58
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Discount'
          Title.Alignment = taCenter
          Title.Caption = #25240#25187
          Width = 65
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'FixedPrice'
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Width = 78
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'DiscountedPrice'
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Width = 73
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AbbreviatedName'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'TotalAmount'
          Title.Alignment = taCenter
          Title.Caption = #24211#23384
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'BkstackName'
          Title.Alignment = taCenter
          Title.Caption = #24211#20301
          Width = 74
          Visible = True
        end>
    end
    object pnl1: TPanel
      Left = 5
      Top = 462
      Width = 998
      Height = 76
      BevelInner = bvLowered
      Color = 16180174
      Ctl3D = True
      ParentBackground = False
      ParentCtl3D = False
      TabOrder = 3
      object lbl1: TRzLabel
        Left = 3
        Top = 10
        Width = 92
        Height = 48
        Caption = #24212#25910
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -45
        Font.Name = #21326#25991#32454#40657
        Font.Style = [fsBold]
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl7: TRzLabel
        Left = 335
        Top = 10
        Width = 92
        Height = 48
        Caption = #25214#36174
        Font.Charset = GB2312_CHARSET
        Font.Color = clBlack
        Font.Height = -45
        Font.Name = #21326#25991#32454#40657
        Font.Style = [fsBold]
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl3: TRzLabel
        Left = 664
        Top = 10
        Width = 92
        Height = 48
        Caption = #25910#27454
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -45
        Font.Name = #21326#25991#32454#40657
        Font.Style = [fsBold]
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object numedtOdd: TRzNumericEdit
        Left = 426
        Top = 6
        Width = 235
        Height = 60
        Color = clCream
        Ctl3D = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -43
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentCtl3D = False
        ParentFont = False
        ReadOnly = True
        ReadOnlyColor = clCream
        TabOrder = 0
        IntegersOnly = False
        DisplayFormat = '###,##0.00;-###,##0.00'
      end
      object numedtPaidinMoney: TRzNumericEdit
        Left = 758
        Top = 6
        Width = 235
        Height = 60
        Color = clCream
        Ctl3D = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -43
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentCtl3D = False
        ParentFont = False
        ReadOnlyColor = clCream
        TabOrder = 1
        OnChange = numedtPaidinMoneyChange
        OnKeyPress = numedtPaidinMoneyKeyPress
        IntegersOnly = False
        Max = 10000.000000000000000000
        DisplayFormat = '###,##0.00;-###,##0.00'
      end
      object dbnbedtReceivableMoney: TRzNumericEdit
        Left = 94
        Top = 8
        Width = 235
        Height = 60
        Color = clCream
        Ctl3D = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -43
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentCtl3D = False
        ParentFont = False
        ReadOnly = True
        ReadOnlyColor = clCream
        TabOrder = 2
        IntegersOnly = False
        DisplayFormat = '###,##0.00;-###,##0.00'
      end
    end
    object GroupBox3: TGroupBox
      Left = 693
      Top = 552
      Width = 310
      Height = 72
      Caption = #29992#25143#20449#24687
      Ctl3D = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 4
      object Label4: TLabel
        Left = 24
        Top = 22
        Width = 36
        Height = 13
        Caption = #38646#21806#21592
      end
      object Label5: TLabel
        Left = 24
        Top = 48
        Width = 36
        Height = 13
        Caption = #24403#21069#24215
      end
      object lblOpName: TRzLabel
        Left = 71
        Top = 22
        Width = 3
        Height = 13
        Color = 16180174
        Enabled = False
        ParentColor = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object edopername: TEdit
        Left = 71
        Top = 19
        Width = 226
        Height = 21
        Enabled = False
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 0
      end
      object edstoragename: TEdit
        Left = 71
        Top = 45
        Width = 226
        Height = 21
        Ctl3D = True
        Enabled = False
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ParentCtl3D = False
        TabOrder = 1
      end
    end
    object GroupBox4: TGroupBox
      Left = 332
      Top = 552
      Width = 352
      Height = 72
      Caption = #24403#21069#21333#25454
      Ctl3D = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 5
      object lbl14: TRzLabel
        Left = 195
        Top = 22
        Width = 36
        Height = 13
        Caption = #24635#23454#27915
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl13: TRzLabel
        Left = 21
        Top = 48
        Width = 36
        Height = 13
        Caption = #24635#30721#27915
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl12: TRzLabel
        Left = 21
        Top = 22
        Width = 36
        Height = 13
        Caption = #24635#25968#37327
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object Label2: TLabel
        Left = 195
        Top = 48
        Width = 36
        Height = 13
        Caption = #24635#24212#25910
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object dbnbedt4: TRzDBNumericEdit
        Left = 242
        Top = 19
        Width = 95
        Height = 21
        DataSource = dsrcNtHeader
        DataField = 'TotalDiscountedPrice'
        Alignment = taLeftJustify
        Ctl3D = True
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 0
        DisplayFormat = #65509'###,##0.00;-'#65509'###,##0.00'
      end
      object dbnbedt3: TRzDBNumericEdit
        Left = 66
        Top = 45
        Width = 95
        Height = 21
        DataSource = dsrcNtHeader
        DataField = 'TotalFixedPrice'
        Alignment = taLeftJustify
        Ctl3D = True
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 1
        DisplayFormat = #65509'###,##0.00;-'#65509'###,##0.00'
      end
      object dbnbedt2: TRzDBNumericEdit
        Left = 66
        Top = 19
        Width = 95
        Height = 21
        DataSource = dsrcNtHeader
        DataField = 'TotalAmount'
        Alignment = taLeftJustify
        Ctl3D = True
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ImeName = #29579#30721#20116#31508#22411#36755#20837#27861'86'#29256
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 2
        DisplayFormat = '###,##0;-###,##0'
      end
      object dbnbedt5: TRzDBNumericEdit
        Left = 242
        Top = 45
        Width = 95
        Height = 21
        DataSource = dsrcNtHeader
        DataField = 'TotalDiscountedPrice'
        Alignment = taLeftJustify
        Ctl3D = True
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 3
        DisplayFormat = '###,##0.00;-###,##0.00'
      end
    end
  end
  object GroupBox2: TGroupBox [2]
    Left = 237
    Top = 175
    Width = 480
    Height = 220
    Caption = #25346#21333#21015#34920
    Color = 16180174
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentColor = False
    ParentFont = False
    TabOrder = 2
    Visible = False
    object DBGrid1: TDBGrid
      Left = 8
      Top = 17
      Width = 461
      Height = 189
      DataSource = ds
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = [fsBold]
      OnDblClick = DBGrid1DblClick
      Columns = <
        item
          Expanded = False
          FieldName = 'RetailNtCode'
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -11
          Title.Font.Name = 'Tahoma'
          Title.Font.Style = [fsBold]
          Width = 121
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Name'
          Title.Alignment = taCenter
          Title.Caption = #20250#21592#21517#31216
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -11
          Title.Font.Name = 'Tahoma'
          Title.Font.Style = [fsBold]
          Width = 93
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HdTime'
          Title.Alignment = taCenter
          Title.Caption = #26102#38388
          Title.Font.Charset = DEFAULT_CHARSET
          Title.Font.Color = clNavy
          Title.Font.Height = -11
          Title.Font.Name = 'Tahoma'
          Title.Font.Style = [fsBold]
          Width = 180
          Visible = True
        end>
    end
  end
  object GroupBox6: TGroupBox [3]
    Left = 541
    Top = 125
    Width = 457
    Height = 51
    Color = 16180174
    ParentBackground = False
    ParentColor = False
    TabOrder = 3
    Visible = False
    object labdiscountstyle: TLabel
      Left = 370
      Top = 21
      Width = 77
      Height = 13
      BiDiMode = bdRightToLeft
      Caption = 'labdiscountstyle'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBiDiMode = False
      ParentFont = False
    end
  end
  object dbhd: TDBNavigator [4]
    Left = 398
    Top = 60
    Width = 112
    Height = 22
    DataSource = dshd
    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast]
    Flat = True
    TabOrder = 4
    OnClick = dbhdClick
  end
  inherited qryUserAuthority: TADOQuery
    Left = 104
    Top = 392
  end
  object spQryNtHeader: TADOStoredProc
    ProcedureName = 'USP_BS_Qry_NtHeader;1'
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@ID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Prepared = True
    Left = 168
    Top = 352
  end
  object cmdUpdateNtHeader: TADOCommand
    CommandText = 'USP_BS_Update_NtHeader;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@ID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@HdTime'
        Attributes = [paNullable]
        DataType = ftDateTime
        Value = Null
      end
      item
        Name = '@StgID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@CustomerID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Remarks'
        Attributes = [paNullable]
        DataType = ftWideString
        Size = 500
        Value = Null
      end
      item
        Name = '@StaffID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@AddCosts'
        Attributes = [paNullable]
        DataType = ftFloat
        Precision = 15
        Value = Null
      end
      item
        Name = '@SupplySN'
        Attributes = [paNullable]
        DataType = ftString
        Size = 50
        Value = Null
      end
      item
        Name = '@CardMoney'
        Attributes = [paNullable]
        DataType = ftBCD
        Precision = 19
        Value = Null
      end
      item
        Name = '@Cash'
        Attributes = [paNullable]
        DataType = ftBCD
        Precision = 19
        Value = Null
      end
      item
        Name = '@State'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@date'
        DataType = ftDateTime
        Value = Null
      end
      item
        Name = '@Postcard'
        DataType = ftFloat
        Precision = 10
        Value = Null
      end
      item
        Name = '@Youhuiquan'
        DataType = ftFloat
        Precision = 10
        Value = Null
      end>
    Left = 336
    Top = 216
  end
  object spQryNtHeader1: TADOStoredProc
    ProcedureName = 'USP_BS_Qry_NtHeader1;1'
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@NtCode'
        Attributes = [paNullable]
        DataType = ftString
        Size = 15
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Prepared = True
    Left = 160
    Top = 320
  end
  object cmdDelNtHeader: TADOCommand
    CommandText = 'USP_BS_Del_NtHeader;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@ID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 360
    Top = 336
  end
  object dsetNtHeader: TADODataSet
    CursorType = ctOpenForwardOnly
    Parameters = <>
    Left = 256
    Top = 280
  end
  object dsrcNtHeader: TDataSource
    DataSet = dsetNtHeader
    OnDataChange = dsrcNtHeaderDataChange
    Left = 232
    Top = 192
  end
  object dsrcNote: TDataSource
    DataSet = dsetNote
    OnDataChange = dsrcNoteDataChange
    Left = 288
    Top = 352
  end
  object dsetNote: TADODataSet
    AfterScroll = dsetNoteAfterScroll
    Parameters = <>
    Left = 328
    Top = 288
  end
  object cmdAddNote: TADOCommand
    CommandText = 'USP_BS_Add_Note;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@NtHeaderID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@BkcatalogID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@SupplierID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@NoteMode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@bkstackID'
        DataType = ftInteger
        Value = Null
      end>
    Left = 472
    Top = 288
  end
  object cmdUpdateNote: TADOCommand
    CommandText = 'USP_BS_Update_Note;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@ID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Amount'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Discount'
        Attributes = [paNullable]
        DataType = ftFloat
        Precision = 15
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 432
    Top = 352
  end
  object cmdDelNote: TADOCommand
    CommandText = 'USP_BS_Del_Note;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@ID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 216
    Top = 408
  end
  object cmdBatchUpdateNote: TADOCommand
    CommandText = 'USP_BS_BatchUpdate_Note;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@IDS'
        Attributes = [paNullable]
        DataType = ftString
        Size = 2147483647
        Value = Null
      end
      item
        Name = '@Amount'
        Attributes = [paNullable]
        DataType = ftString
        Precision = 10
        Size = -1
        Value = Null
      end
      item
        Name = '@Discount'
        Attributes = [paNullable]
        DataType = ftString
        Precision = 15
        Size = -1
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 504
    Top = 400
  end
  object cmdBatchDelNote: TADOCommand
    CommandText = 'USP_BS_BatchDel_Note;1'
    CommandType = cmdStoredProc
    Prepared = True
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@IDS'
        Attributes = [paNullable]
        DataType = ftString
        Size = 2147483647
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 424
    Top = 328
  end
  object pm1: TPopupMenu
    Left = 72
    Top = 408
    object mniBsNote: TMenuItem
      Tag = 1
      Caption = #38646#21806#21333
      Checked = True
      GroupIndex = 1
      RadioItem = True
      OnClick = mniBsNoteSendbackClick
    end
    object mniBsNoteSendback: TMenuItem
      Tag = 2
      Caption = #38646#21806#36864#36135#21333
      GroupIndex = 1
      RadioItem = True
      OnClick = mniBsNoteSendbackClick
    end
  end
  object dsetMember: TADODataSet
    CommandText = 'select ID, Name from CUST_MemberInfo order by ID'
    Parameters = <>
    Left = 48
    Top = 264
  end
  object dsrcMember: TDataSource
    DataSet = dsetMember
    Left = 120
    Top = 264
  end
  object cmdAddNtHeader: TADOCommand
    CommandText = 'USP_BS_Add_NtHeader;1'
    CommandType = cmdStoredProc
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@OperatorID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@StgID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@CustomerID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 448
    Top = 352
  end
  object dsetBkstack: TADODataSet
    CursorType = ctStatic
    CommandText = 'select ID, Name from STK_BookstackInfo'
    Parameters = <>
    Left = 296
    Top = 416
  end
  object dsrcBkstack: TDataSource
    DataSet = dsetBkstack
    Left = 184
    Top = 240
  end
  object cmdResetNtHeader: TADOCommand
    CommandText = 'USP_BS_Reset_NtHeader;1'
    CommandType = cmdStoredProc
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@ID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end>
    Left = 456
    Top = 368
  end
  object pmPrint: TPopupMenu
    Left = 352
    Top = 424
    object mniPrintNtHeader: TMenuItem
      Tag = 1
      AutoCheck = True
      Caption = #25910#27454#26102#25171#21360#23567#31080
      Checked = True
      OnClick = mniPrintNtHeaderClick
    end
  end
  object ImageList1: TImageList
    Left = 336
    Top = 384
    Bitmap = {
      494C0101220023004C0010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000009000000001002000000000000090
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300000000000000000000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFCC9900FFCC
      9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900CC99
      6600CC99660099330000000000000000000000000000B2B2B200CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00B2B2
      B200B2B2B2009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CC996600CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      660099330000CC9966009933000000000000B2B2B200B2B2B200B2B2B200B2B2
      B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2
      B20099999900B2B2B20099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CC996600FFFFFF00FFCC9900FFCC
      9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC
      9900CC996600993300009933000000000000B2B2B20000000000CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00B2B2B2009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CC996600FFFFFF00FFCC9900FFCC
      9900FFCC9900FFCC990000CC000000990000FFCC99000000FF000000CC00FFCC
      9900CC996600CC9966009933000000000000B2B2B20000000000CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00B2B2B20099999900CCCCCC00B2B2B20099999900CCCC
      CC00B2B2B200B2B2B20099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CC996600CC996600CC99660099330000B2B2B20000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B2B2B200B2B2B200B2B2B200999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CC996600FFFFFF00FFCC9900FFCC
      9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC9900FFCC
      9900CC996600CC996600CC99660099330000B2B2B20000000000CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00B2B2B200B2B2B200B2B2B200999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600FFCC
      9900FFCC9900CC996600CC9966009933000000000000B2B2B200B2B2B200B2B2
      B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200CCCC
      CC00CCCCCC00B2B2B200B2B2B200999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC99
      6600FFCC9900FFCC9900CC996600993300000000000000000000B2B2B2000000
      000000000000000000000000000000000000000000000000000000000000B2B2
      B200CCCCCC00CCCCCC00B2B2B200999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500FFFFFF00CC99
      6600CC996600CC9966009933000000000000000000000000000000000000B2B2
      B20000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0000000000B2B2
      B200B2B2B200B2B2B20099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CC996600000000000000000000000000000000000000000000000000B2B2
      B200000000000000000000000000000000000000000000000000000000000000
      0000B2B2B2000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CC996600FFFFFF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500FFFF
      FF00CC9966000000000000000000000000000000000000000000000000000000
      0000B2B2B20000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC000000
      0000B2B2B2000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CC996600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000000000000000
      0000B2B2B2000000000000000000000000000000000000000000000000000000
      000000000000B2B2B20000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC99660000000000000000000000000000000000000000000000
      000000000000B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2B200B2B2
      B200B2B2B200B2B2B20000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000003399CC000066
      9900006699000066990000669900006699000066990000669900006699000066
      9900006699000066990000000000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000003399CC0066CCFF003399
      CC0099FFFF0066CCFF0066CCFF0066CCFF0066CCFF0066CCFF0066CCFF0066CC
      FF003399CC0099FFFF0000669900000000000000000099999900CCCCCC009999
      9900E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC0099999900E5E5E5009999990000000000000000003399CC00006699000066
      9900006699000066990000669900006699000066990000669900006699000066
      9900006699000000000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      990099999900000000000000000000000000000000003399CC0066CCFF003399
      CC0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FF
      FF0066CCFF0099FFFF0000669900000000000000000099999900CCCCCC009999
      9900E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500CCCCCC00E5E5E50099999900000000003399CC0066CCFF003399CC0099FF
      FF0066CCFF0066CCFF0066CCFF0066CCFF0066CCFF0066CCFF0066CCFF003399
      CC0099FFFF0000669900000000000000000099999900CCCCCC0099999900E5E5
      E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      9900E5E5E500999999000000000000000000000000003399CC0066CCFF003399
      CC0099FFFF0099FFFF00006600003399660099FFFF0099FFFF0099FFFF0099FF
      FF0066CCFF0099FFFF0000669900000000000000000099999900CCCCCC009999
      9900E5E5E500E5E5E50099999900CCCCCC00E5E5E500E5E5E500E5E5E500E5E5
      E500CCCCCC00E5E5E50099999900000000003399CC0066CCFF003399CC0099FF
      FF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0066CC
      FF0099FFFF0000669900000000000000000099999900CCCCCC0099999900E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500CCCC
      CC00E5E5E500999999000000000000000000000000003399CC0066CCFF003399
      CC0099FFFF0099FFFF0033999900339933003399330099FFFF0099FFFF0099FF
      FF0066CCFF0099FFFF0000669900000000000000000099999900CCCCCC009999
      9900E5E5E500E5E5E500CCCCCC009999990099999900E5E5E500E5E5E500E5E5
      E500CCCCCC00E5E5E50099999900000000003399CC0066CCFF003399CC0099FF
      FF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0066CC
      FF0099FFFF0000669900000000000000000099999900CCCCCC0099999900E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500CCCC
      CC00E5E5E500999999000000000000000000000000003399CC0066CCFF003399
      CC0099FFFF0099FFFF0099FFCC003399330033CC66003399660099FFFF0099FF
      FF0066CCFF0099FFFF0000669900000000000000000099999900CCCCCC009999
      9900E5E5E500E5E5E500E5E5E50099999900E5E5E500CCCCCC00E5E5E500E5E5
      E500CCCCCC00E5E5E50099999900000000003399CC0066CCFF003399CC0099FF
      FF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0066CC
      FF0099FFFF0000669900000000000000000099999900CCCCCC0099999900E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500CCCC
      CC00E5E5E500999999000000000000000000000000003399CC0066CCFF003399
      CC0099FFFF0099FFFF0099FFFF000099330066FF99003399330099FFCC0099FF
      FF0066CCFF0099FFFF0000669900000000000000000099999900CCCCCC009999
      9900E5E5E500E5E5E500E5E5E50099999900E5E5E50099999900E5E5E500E5E5
      E500CCCCCC00E5E5E50099999900000000003399CC0066CCFF003399CC0099FF
      FF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099CC
      FF006699FF006699FF00CCCCFF000000000099999900CCCCCC0099999900E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500CCCCCC00CCCCCC000000000000000000000000003399CC0099FFFF0099FF
      FF003399CC003399CC003399CC000066330033CC660033CC6600339966003399
      CC003399CC003399CC003399CC00000000000000000099999900E5E5E500E5E5
      E50099999900999999009999990099999900E5E5E500E5E5E500CCCCCC009999
      9900999999009999990099999900000000003399CC0066CCFF003399CC0099FF
      FF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0099CCFF000033
      FF003399FF003366FF000033FF009999FF0099999900CCCCCC0099999900E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E5009999
      9900CCCCCC00CCCCCC0099999900CCCCCC00000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF000080000033CC660033CC66003399330099FF
      FF00006699000000000000000000000000000000000099999900E5E5E500E5E5
      E500E5E5E500E5E5E500E5E5E50099999900E5E5E500E5E5E50099999900E5E5
      E500999999000000000000000000000000003399CC0099FFFF0099FFFF003399
      CC003399CC003399CC003399CC003399CC003399CC003399CC0099CCFF003399
      FF0033CCFF0033CCFF003399FF0099CCFF0099999900E5E5E500E5E5E5009999
      9900999999009999990099999900999999009999990099999900E5E5E500CCCC
      CC009999990099999900CCCCCC000000000000000000000000003399CC0099FF
      FF0099FFFF0099FFFF0099FFFF000080000033CC660033CC6600339933003399
      CC0000000000000000000000000000000000000000000000000099999900E5E5
      E500E5E5E500E5E5E500E5E5E50099999900E5E5E500E5E5E500999999009999
      9900000000000000000000000000000000003399CC0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF0099FFFF0099FFFF0066CCFF003366FF000066
      FF00CCFFFF0099FFFF003366FF003366FF0099999900E5E5E500E5E5E500E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00E5E5E500E5E5E500CCCCCC00CCCCCC000000000000000000000000003399
      CC003399CC003399CC003399CC000099330033CC660033CC6600339933000000
      0000000000000000000000000000000000000000000000000000000000009999
      990099999900999999009999990099999900E5E5E500E5E5E500999999000000
      000000000000000000000000000000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF003399CC003399CC003399CC003399CC003399CC000033
      FF000033FF003399FF000033FF00CCCCFF000000000099999900E5E5E500E5E5
      E500E5E5E500E5E5E50099999900999999009999990099999900999999009999
      990099999900CCCCCC0099999900000000000000000000000000000000000000
      00000066000000800000008000003399330033CC660033CC6600336633000080
      0000008000000000000000000000000000000000000000000000000000000000
      000099999900999999009999990099999900E5E5E500E5E5E500999999009999
      99009999990000000000000000000000000000000000000000003399CC003399
      CC003399CC003399CC00000000000000000000000000000000000033FF0099CC
      FF000033FF006699FF009999FF0099CCFF000000000000000000999999009999
      9900999999009999990000000000000000000000000000000000999999000000
      000099999900CCCCCC00CCCCCC00000000000000000000000000000000000000
      0000669966000080000033CC330033CC330033CC660033CC6600339933000066
      0000669966000000000000000000000000000000000000000000000000000000
      0000CCCCCC0099999900E5E5E500E5E5E500E5E5E500E5E5E500999999009999
      9900CCCCCC000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099CCFF0099CCFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000336633000099330033CC330033CC33000099330033663300C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990099999900E5E5E500E5E5E5009999990099999900C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099CC990000800000009900000080000066999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000E5E5E500999999009999990099999900CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000006699660033993300CCCCCC0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000CCCCCC0099999900CCCCCC0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600993300009933000099330000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC00999999009999990099999900CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CC9966009933000000000000000000000000000099330000CC9966000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CCCCCC009999990000000000000000000000000099999900CCCCCC000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000993300000000000000000000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      00009933000000000000CC99660099330000CC99660000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009999990000000000CCCCCC0099999900CCCCCC0000000000999999000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000993300000000000099330000000000009933000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999000000000099999900000000009999990000000000999999000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000993300000000000099330000000000009933000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999000000000099999900000000009999990000000000999999000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000993300000000000099330000000000009933000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999000000000099999900000000009999990000000000999999000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      0000993300000000000099330000000000009933000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999000000000099999900000000009999990000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000993300000000000099330000000000009933000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999000000000099999900000000009999990000000000999999000000
      00000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000000000000000
      0000993300000000000099330000000000009933000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999000000000099999900000000009999990000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000993300000000000099330000000000009933000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999000000000099999900000000009999990000000000999999000000
      00000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000000000000000
      0000993300000000000099330000000000009933000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999000000000099999900000000009999990000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099330000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900000000000000000000000000999999000000
      00000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000000000000000
      0000000000000000000099330000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099330000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900000000000000000000000000999999000000
      00000000000000000000000000000000000000000000CC99660000000000CC99
      660000000000CC99660000000000CC99660000000000CC99660000000000CC99
      660000000000CC996600000000000000000000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000CCCCCC0000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000000000000000000000000000000000000000
      0000000000000000000000000000993300009933000099330000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999009999990099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC0066999900666699009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC00B2B2B200999999009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000066CCFF003399CC006666
      990099999900E5E5E50000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00B2B2B2009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000000000000CCCCFF0066CCFF003399
      CC006666990099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E5E5E500CCCCCC00B2B2
      B2009999990099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000CCCCFF0066CC
      FF003399CC006666990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E5E5E500CCCC
      CC00B2B2B2009999990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00999999000000000000000000000000000000000000000000CCCC
      FF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC999900CC999900CC99
      9900CCCC9900E5E5E5000000000000000000000000000000000000000000E5E5
      E500CCCCCC00B2B2B20099999900CCCCCC00E5E5E50099999900999999009999
      9900B2B2B200E5E5E50000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EABF00FFFFCC00F2EA
      BF00F2EABF00CC999900ECC6D900000000000000000000000000000000000000
      0000E5E5E500CCCCCC00B2B2B20099999900B2B2B200CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900E5E5E500000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000E5E5E500CC999900FFCC9900FFFFCC00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E50099999900E5E5E5000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFCC00F2EABF00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00F2EABF00CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E500CCCCCC00B2B2B2000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000CCCC9900FFCC9900F2EABF00F2EABF00FFFFCC00FFFFCC00FFFF
      CC00FFFFFF00FFFFFF00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00E5E5E500E5E5E500CCCCCC00999999000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000CC999900F2EABF00F2EABF00F2EABF00F2EABF00FFFFCC00FFFF
      CC00FFFFCC00FFFFCC00FFFFCC00CC9999000000000000000000000000000000
      00000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000CCCC9900F2EABF00FFFFCC00F2EABF00F2EABF00F2EABF00FFFF
      CC00FFFFCC00FFFFCC00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EABF00F2EABF00F2EA
      BF00F2EABF00FFFFCC00CCCC9900CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00B2B2B200B2B2B2000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000E5E5E500CC999900ECC6D900FFFFFF00FFFFCC00F2EABF00F2EA
      BF00F2EABF00FFCC9900CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00E5E5E50099999900E5E5E5000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      00000000000000000000FFCCCC00CC999900FFCCCC00F2EABF00F2EABF00F2EA
      BF00CCCC9900CC999900FFCCCC00000000000000000000000000000000000000
      00000000000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCC
      CC00B2B2B20099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500CCCC9900CC999900CC999900CC99
      9900CC999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500B2B2B20099999900999999009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000080808000808080000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008080800000000000000000008080800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008080800080808000808080008080800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000080808000FFFFFF0000000000000000008080800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000080808000FFFFFF0080808000808080008080800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      8000FFFFFF00FFFFFF0080808000FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000066CCFF003399CC003399CC0066CCFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000B2B2B2009999990099999900B2B2B200000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF000000000000000000FFFFFF008080800080808000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000FFFFFF008080800080808000FFFFFF008080800080808000000000000000
      00000000000000000000000000000000000000000000000000003399CC003399
      CC003399CC003399CC003399CC0066CCFF0066CCFF003399CC003399CC003399
      CC003399CC003399CC0000000000000000000000000000000000999999009999
      9900999999009999990099999900B2B2B200B2B2B20099999900999999009999
      9900999999009999990000000000000000000000000080808000000000000000
      0000000000000000000000000000808080000000000000000000000000000000
      0000000000000000000000000000666699000000000080808000808080008080
      8000808080008080800080808000808080008080800080808000000000000000
      00000000000000000000000000009999990000000000000000003399CC0099FF
      FF00FFFFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0066CCFF0066CC
      FF0066CCFF003399CC000000000000000000000000000000000099999900CCCC
      CC00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00B2B2B200B2B2
      B200B2B2B20099999900000000000000000080808000FFFFFF00FFFFFF000000
      0000FFFFFF000000000000000000C0C0C0000000000000000000000000000000
      00000000000000000000666699003399CC0080808000FFFFFF00FFFFFF008080
      8000FFFFFF008080800080808000C0C0C0008080800080808000808080000000
      0000000000000000000099999900CCCCCC000000000000000000000000003399
      CC0099FFFF00FFFFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0066CC
      FF003399CC000000000000000000000000000000000000000000000000009999
      9900CCCCCC00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00B2B2
      B2009999990000000000000000000000000080808000FFFFFF00000000000000
      0000FFFFFF0080808000C0C0C000FFFFFF008080800000000000FFFFFF008080
      800000000000666699003399CC0066CCFF0080808000FFFFFF00808080008080
      8000FFFFFF0080808000C0C0C000FFFFFF008080800080808000FFFFFF008080
      80000000000099999900CCCCCC00FFFFFF000000000000000000000000000000
      00003399CC0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF003399
      CC00000000000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000008080800000000000000000000000
      0000808080000000000000000000FFFFFF0000000000FFFFFF00FFFFFF00FFFF
      FF00666699003399CC0066CCFF00000000008080800080808000808080008080
      8000808080008080800080808000FFFFFF0080808000FFFFFF00FFFFFF00FFFF
      FF0099999900CCCCCC00FFFFFF00000000000000000000000000000000000000
      00003399CC0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF003399
      CC00000000000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000008080
      8000000000000000000000000000000000000000000000000000FFFFFF006666
      99003399CC0066CCFF0000000000000000000000000080808000808080008080
      8000808080008080800080808000808080008080800080808000FFFFFF009999
      9900CCCCCC00FFFFFF0000000000000000000000000000000000000000000000
      00003399CC0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF003399
      CC00000000000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000000000000C0C0C000C0C0
      C0000000000000000000FFFFFF00000000000000000000000000666699003399
      CC0066CCFF000000000000000000000000000000000080808000C0C0C000C0C0
      C0008080800080808000FFFFFF0080808000808080008080800099999900CCCC
      CC00FFFFFF000000000000000000000000000000000000000000000000000000
      00003399CC00FFFFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF003399
      CC00000000000000000000000000000000000000000000000000000000000000
      000099999900FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000080808000C0C0C000FFFF
      FF0000000000FFFFFF00FFFFFF00FFFFFF0000000000666699003399CC0066CC
      FF00000000000000000000000000000000000000000080808000C0C0C000FFFF
      FF0080808000FFFFFF00FFFFFF00FFFFFF008080800099999900CCCCCC00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      000066CCFF0066CCFF00FFFFFF0000FFFF0000FFFF0000FFFF0066CCFF0066CC
      FF00000000000000000000000000000000000000000000000000000000000000
      0000B2B2B200B2B2B200FFFFFF00CCCCCC00CCCCCC00CCCCCC00B2B2B200B2B2
      B200000000000000000000000000000000000000000000000000808080008080
      80000000000000000000FFFFFF00FFFFFF00666699003399CC0066CCFF000000
      0000000000000000000000000000000000000000000000000000808080008080
      80008080800080808000FFFFFF00FFFFFF0099999900CCCCCC00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000003399CC0099FFFF00FFFFFF0000FFFF0000FFFF003399CC000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00FFFFFF00CCCCCC00CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000666699003399CC0066CCFF00000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      800080808000808080008080800099999900CCCCCC00FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000003399CC003399CC003399CC003399CC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900999999009999990099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000666699003399CC0066CCFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000808080008080800099999900CCCCCC00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000666699003399CC0066CCFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F100E5E5E500CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F10000000000CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC99660000000000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900000000000000000000000000E2EFF100E5E5E500B2B2
      B200CC9999009966660099666600B2B2B200CCCCCC00E5E5E500E2EFF1000000
      00000000000000000000000000000000000000000000E2EFF10000000000B2B2
      B200999999009999990099999900B2B2B200CCCCCC0000000000E2EFF1000000
      0000000000000000000000000000000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000999999000000000000000000E5E5E500CC99990099666600CC99
      9900CC999900FFFFFF00996666009999990099999900B2B2B200E5E5E5000000
      0000000000000000000000000000000000000000000099999900999999009999
      990099999900FFFFFF00999999009999990099999900B2B2B200000000000000
      0000000000000000000000000000000000000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC000000000099999900000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600336699003366990033669900E2EFF1000000
      0000000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900999999009999990099999900E2EFF1000000
      0000000000000000000000000000000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCCC000099CC00FFFFFF00FFCC
      CC000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000C0C0C00099999900FFFFFF00CCCC
      CC00000000000000000000000000000000000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC000000000099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCFF003399CC00FFCCCC00CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000CCCCCC0099999900CCCCCC009999
      9900000000000000000000000000000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900000000000000000099666600FFCC9900CC999900CC99
      6600FFCCCC00FFFFFF009966660099CCCC0099CCFF00B2B2B200FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000999999009999
      9900CCCCCC00FFFFFF0099999900CCCCCC00CCCCCC00B2B2B200999999009999
      9900000000000000000000000000000000000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC000000000099999900000000000000000099666600FFCC990099666600FFFF
      FF00FFCCCC00FFFFFF009966660099CCCC00C0C0C000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C00066666600FFFF
      FF00CCCCCC00FFFFFF0099999900CCCCCC00C0C0C00099999900999999009999
      9900999999009999990099999900000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900000000000000000099666600FFCC9900CC9999009966
      6600FFCCCC00FFFFFF009966660000000000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000999999006666
      6600CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5
      E500FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC000000000099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660000000000CC999900CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CC99660000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00E2EFF100CC999900FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E2EFF10099999900999999009999
      9900000000000000000000000000000000000000000000000000CC996600FFFF
      FF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500FFFFFF00CC996600CC99
      6600CC996600CC99660000000000000000000000000000000000999999000000
      0000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0000000000999999009999
      99009999990099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660099CCCC000000000099CCCC00FFCC9900CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E500CCCCCC00C0C0C0009999
      9900000000000000000000000000000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600E5E5
      E500CC9966000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000999999000000
      00009999990000000000000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00000000003399CC0000000000FFCC
      9900000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E5009999990000000000C0C0
      C000000000000000000000000000000000000000000000000000CC996600FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600CC99
      6600000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000999999009999
      99000000000000000000000000000000000000000000C0C0C000CC996600CC99
      9900CCCC9900FFFFFF00996666000099CC000099CC000099CC00000000000000
      00000000000000000000000000000000000000000000C0C0C000999999009999
      9900C0C0C000FFFFFF0099999900999999009999990099999900000000000000
      0000000000000000000000000000000000000000000000000000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC9966000000
      0000000000000000000000000000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00CC9999009966660099666600000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00999999009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC996600CC996600CC9966000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000099999900000000000000FF00000099000000
      99000000990000000000000000000000000000000000000000000000FF000000
      99000000990000009900000000000000000000000000B2B2B200808080008080
      8000808080000000000000000000000000000000000000000000B2B2B2008080
      800080808000808080000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      99000000000000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00000000000000000099999900000000000000FF000000CC000000
      CC000000CC00000099000000000000000000000000000000FF000000CC000000
      CC000000CC0000009900000000000000000000000000B2B2B200999999009999
      99009999990080808000000000000000000000000000B2B2B200999999009999
      990099999900808080000000000000000000000099000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966009999990000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000009999990000000000000000000000FF000000
      CC000000CC000000CC0000009900000000000000FF000000CC000000CC000000
      CC00000099000000000000000000000000000000000000000000B2B2B2009999
      990099999900999999008080800000000000B2B2B20099999900999999009999
      9900808080000000000000000000000000000000CC000000990000000000CC99
      6600FFFFFF009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC996600B2B2B20099999900000000009999
      9900000000009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000999999000000000000000000000000000000
      FF000000CC000000CC000000CC00000099000000CC000000CC000000CC000000
      990000000000000000000000000000000000000000000000000000000000B2B2
      B200999999009999990099999900808080009999990099999900999999008080
      8000000000000000000000000000000000000000FF000000CC0000009900CC99
      6600FFFFFF0099330000CC996600CC996600CC996600CC996600CC996600CC99
      6600CC99660099330000FFFFFF00CC996600CCCCCC00B2B2B200999999009999
      99000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000999999000000000000000000000000000000
      00000000FF000000CC000000CC000000CC000000CC000000CC00000099000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B2B2B2009999990099999900999999009999990099999900808080000000
      0000000000000000000000000000000000000000FF000000CC0000000000CC99
      6600FFFFFF009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC996600CCCCCC00B2B2B200000000009999
      9900000000009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000999999000000000000000000000000000000
      0000000000000000FF000000CC000000CC000000CC0000009900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000B2B2B20099999900999999009999990080808000000000000000
      0000000000000000000000000000000000000000FF000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC996600CCCCCC0000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000000000
      00000000FF000000CC000000CC000000CC000000CC000000CC00000099000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B2B2B2009999990099999900999999009999990099999900808080000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      99000000000000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC000000000000000000999999000000000000000000000000000000
      FF000000CC000000CC000000CC00000099000000CC000000CC000000CC000000
      990000000000000000000000000000000000000000000000000000000000B2B2
      B200999999009999990099999900808080009999990099999900999999008080
      800000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000009999990000000000000000000000FF000000
      CC000000CC000000CC0000009900000000000000FF000000CC000000CC000000
      CC00000099000000000000000000000000000000000000000000B2B2B2009999
      990099999900999999008080800000000000B2B2B20099999900999999009999
      990080808000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      99000000000000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00000000000000000099999900000000000000FF000000CC000000
      CC000000CC00000099000000000000000000000000000000FF000000CC000000
      CC000000CC0000009900000000000000000000000000B2B2B200999999009999
      99009999990080808000000000000000000000000000B2B2B200999999009999
      990099999900808080000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000099999900000000000000FF000000FF000000
      FF000000FF0000000000000000000000000000000000000000000000FF000000
      FF000000FF000000FF00000000000000000000000000B2B2B200B2B2B200B2B2
      B200B2B2B2000000000000000000000000000000000000000000B2B2B200B2B2
      B200B2B2B200B2B2B2000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      99000000000000000000CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC000000000000000000999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC996600CC996600CC9966000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      000000000000000000003399CC00006699000066990000669900006699000066
      9900006699000066990000669900000000000000000000000000000000000000
      0000000000000000000099999900999999009999990099999900999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC99990099330000CC9999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0099999900CCCCCC000000000000000000000000000000
      000000000000000000003399CC0099FFFF0099FFFF0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF0000669900000000000000000000000000000000000000
      0000000000000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00999999000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9999009933000099330000993300000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900CCCCCC009999990099999900999999000000000000000000000000000000
      000000000000000000003399CC0099FFFF0099FFFF0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF0000669900000000000000000000000000000000000000
      0000000000000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00999999000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF008080
      8000993300009933000099330000CC9999000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      8000999999009999990099999900CCCCCC000000000000000000000000000000
      000000000000000000003399CC0099FFFF0099FFFF0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF0000669900000000000000000000000000000000000000
      0000000000000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00999999000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E5008080800080808000808080009933
      00009933000099330000CC99990000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC008080800080808000808080009999
      99009999990099999900CCCCCC00000000000000000000000000000000000000
      000000000000000000003399CC0099FFFF0099FFFF0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF0000669900000000000000000000000000000000000000
      0000000000000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00999999000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00E5E5E50099996600FFFFCC00FFFFCC00FFFFFF00CCCC
      990099330000CC99990000000000000000000000000099999900000000000000
      00000000000000000000CCCCCC0099999900E5E5E500E5E5E500FFFFFF00E5E5
      E50099999900CCCCCC00000000000000000000000000CC996600CC996600CC99
      6600CC996600CC9966003399CC0099FFFF0099FFFF0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF0000669900000000000000000099999900999999009999
      9900999999009999990099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00999999000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E50099999900F2EABF00FFFFCC00FFFFCC00FFFFCC00FFFF
      FF0066666600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC0099999900E5E5E500E5E5E500E5E5E500E5E5E500FFFF
      FF006666660000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF003399CC0099FFFF0099FFFF0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF0000669900000000000000000099999900000000000000
      0000000000000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00999999000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0099999900F2EABF00FFFFFF00F2EABF00FFFFCC00FFFF
      CC00666666000000000000000000000000000000000099999900000000000000
      0000000000000000000099999900E5E5E500FFFFFF00E5E5E500E5E5E500E5E5
      E5006666660000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF003399CC0099FFFF0099FFFF0099FFFF0099FFFF003399
      CC003399CC003399CC003399CC00000000000000000099999900000000000000
      0000000000000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      99009999990099999900999999000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E50099999900F2EABF00FFFFFF00FFFFFF00F2EABF00FFFF
      CC0066666600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC0099999900E5E5E500FFFFFF00FFFFFF00E5E5E500E5E5
      E5006666660000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF003399CC0099FFFF0099FFFF0099FFFF0099FFFF003399
      CC00CCFFFF000066990000000000000000000000000099999900000000000000
      0000000000000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      9900CCCCCC0099999900000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0099999900F2EABF00F2EABF00F2EABF009999
      6600808080000000000000000000000000000000000099999900000000000000
      000000000000000000000000000099999900E5E5E500E5E5E500E5E5E5009999
      99008080800000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF003399CC0099FFFF0099FFFF0099FFFF0099FFFF003399
      CC00006699000000000000000000000000000000000099999900000000000000
      0000000000000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      99009999990000000000000000000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500999999009999990099999900E5E5
      E500CC996600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999009999990099999900E5E5
      E5009999990000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF003399CC003399CC003399CC003399CC003399CC003399
      CC00000000000000000000000000000000000000000099999900000000000000
      0000000000000000000099999900999999009999990099999900999999009999
      99000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CC9966000000000000000000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009999990000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600000000000000
      0000000000000000000000000000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000099999900000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500FFFFFF00CC996600CC996600CC99
      6600CC996600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC000000000099999900999999009999
      99009999990000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC996600CC996600CC996600CC996600000000000000
      0000000000000000000000000000000000000000000099999900000000000000
      0000000000000000000099999900999999009999990099999900000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600E5E5E500CC99
      6600000000000000000000000000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000099999900E5E5E5009999
      99000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC996600E5E5E500CC99660000000000000000000000
      0000000000000000000000000000000000000000000099999900000000000000
      0000000000000000000099999900000000009999990000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600CC9966000000
      0000000000000000000000000000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000099999900999999000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC996600CC9966000000000000000000000000000000
      0000000000000000000000000000000000000000000099999900000000000000
      0000000000000000000099999900999999000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600000000000000
      0000000000000000000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900000000000000
      00000000000000000000000000000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099999900999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00C0C0C000E5E5
      E500000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC0066999900666699009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCCC00B2B2B200999999009999
      9900E5E5E5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF00000000000000000000000000000000009999
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000000000000CCCCCC00000000000000000066CCFF003399CC006666
      990099999900E5E5E50000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00B2B2B2009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000003333CC000000
      FF00000099000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCFF0066CCFF003399
      CC006666990099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E5E5E500CCCCCC00B2B2
      B2009999990099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000003333CC003399
      FF000000FF000000990000000000000000000000000000000000000000000000
      0000000000000000FF000000000000000000000000000000000099999900E5E5
      E500CCCCCC009999990000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000CCCCFF0066CC
      FF003399CC006666990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E5E5E500CCCC
      CC00B2B2B2009999990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000003333
      CC000066FF000000CC0000000000000000000000000000000000000000000000
      00000000FF000000000000000000000000000000000000000000000000009999
      9900E5E5E5009999990000000000000000000000000000000000000000000000
      0000CCCCCC00000000000000000000000000000000000000000000000000CCCC
      FF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC999900CC999900CC99
      9900CCCC9900E5E5E5000000000000000000000000000000000000000000E5E5
      E500CCCCCC00B2B2B20099999900CCCCCC00E5E5E50099999900999999009999
      9900B2B2B200E5E5E50000000000000000000000000000000000000000000000
      00000000CC000000FF0000009900000000000000000000000000000000000000
      FF00000099000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC009999990000000000000000000000000000000000CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      0000CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EABF00FFFFCC00F2EA
      BF00F2EABF00CC999900ECC6D900000000000000000000000000000000000000
      0000E5E5E500CCCCCC00B2B2B20099999900B2B2B200CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900E5E5E500000000000000000000000000000000000000
      0000000000000000CC000000FF000000990000000000000000000000FF000000
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00999999000000000000000000CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000E5E5E500CC999900FFCC9900FFFFCC00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E50099999900E5E5E5000000000000000000000000000000
      000000000000000000000000CC000000FF00000099000000FF00000099000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900CCCCCC0099999900CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFCC00F2EABF00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00F2EABF00CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E500CCCCCC00B2B2B2000000000000000000000000000000
      00000000000000000000000000000000CC000000FF0000009900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000099999900CCCCCC0099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCC9900FFCC9900F2EABF00F2EABF00FFFFCC00FFFFCC00FFFF
      CC00FFFFFF00FFFFFF00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00E5E5E500E5E5E500CCCCCC00999999000000000000000000000000000000
      000000000000000000000000CC000000FF00000099000000CC00000099000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900CCCCCC009999990099999900999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC999900F2EABF00F2EABF00F2EABF00F2EABF00FFFFCC00FFFF
      CC00FFFFCC00FFFFCC00FFFFCC00CC9999000000000000000000000000000000
      00000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      0000000000000000CC000000FF000000990000000000000000000000CC000000
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00999999000000000000000000999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000CCCC9900F2EABF00FFFFCC00F2EABF00F2EABF00F2EABF00FFFF
      CC00FFFFCC00FFFFCC00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      CC000000FF000000FF0000009900000000000000000000000000000000000000
      CC00000099000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC0099999900000000000000000000000000000000009999
      9900999999000000000000000000000000000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EABF00F2EABF00F2EA
      BF00F2EABF00FFFFCC00CCCC9900CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00B2B2B200B2B2B20000000000000000000000CC003399
      FF000000FF000000990000000000000000000000000000000000000000000000
      00000000CC00000099000000000000000000000000000000000099999900E5E5
      E500CCCCCC009999990000000000000000000000000000000000000000000000
      0000999999009999990000000000000000000000000000000000000000000000
      000000000000E5E5E500CC999900ECC6D900FFFFFF00FFFFCC00F2EABF00F2EA
      BF00F2EABF00FFCC9900CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00E5E5E50099999900E5E5E5000000000000000000666699000000
      CC00666699000000000000000000000000000000000000000000000000000000
      000000000000000000000000CC00000000000000000000000000CCCCCC009999
      9900CCCCCC000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900000000000000000000000000000000000000
      00000000000000000000FFCCCC00CC999900FFCCCC00F2EABF00F2EABF00F2EA
      BF00CCCC9900CC999900FFCCCC00000000000000000000000000000000000000
      00000000000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCC
      CC00B2B2B20099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500CCCC9900CC999900CC999900CC99
      9900CC999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500B2B2B20099999900999999009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000900000000100010000000000800400000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFF00000000C007C00700000000
      8003800300000000000100010000000000014001000000000001400100000000
      00007FF00000000000004000000000008000800000000000C000DFE000000000
      E001E82100000000E007EFF700000000F007F41700000000F003F7FB00000000
      F803F80300000000FFFFFFFF00000000FFFFFFFFC003C003FFFFFFFF80018001
      8007800780018001000300038001800100030003800180010003000380018001
      00030003800180010001000380018001000000008007800700000001C00FC00F
      00000000E01FE01F80008001F007F007C3C0C3D1F007F007FFF3FFFFF80FF80F
      FFFFFFFFF83FF83FFFFFFFFFFC7FFC7FF83FF83FFFFFFFFFF39FF39FFFFFFFFF
      F7DFF7DF80038003F45FF45F80038003F55FF55F80038003F55FF55F80038003
      F55FF55F80038003F55FF55FFFFFFFFFF55FF55FBFFBBFFBF55FF55FFFFFFFFF
      F55FF55FBFFBBFFBF55FF55FFFFFFFFFFDDFFDDFBFFBBFFBFDDFFDDFFFFFFFFF
      FDDFFDDFAAABAAABFE3FFE3FFFFFFFFFFFFFFFFF8FFF8FFFFFFFFFFF07FF07FF
      8003800383FF83FF8003800381FF81FF80038003C0FFC0FF80038003E003E003
      80038003F001F00180038003F800F80080038003F800F80080038003F800F800
      80038003F800F80080038003F800F80080038003F800F80080038003F800F800
      80038003FC01FC01FFFFFFFFFE03FE03FCFFFCFFFFFFFFFFF87FF87FFFFFFFFF
      F07FF07FFFFFFFFFE07FE07FFC3FFC3FC03FC03FC003C003803E803EC003C003
      001C001CE007E00700080008F00FF00F00010001F00FF00F80038003F00FF00F
      80078007F00FF00F800F800FF00FF00FC01FC01FF81FF81FE03FE03FFC3FFC3F
      F07FF07FFFFFFFFFF8FFF8FFFFFFFFFFFDFFFDFFFFFFFFFFE0FFE8FFC003C003
      801FA05FC003DFFB001F803FC003D00B001F001FC003DFFB000F000FC003D00B
      000F000FC003DFFB000F000FC003D00B00010001C003DFFB01010001C003D00B
      01010001C003DFFB000F000FC003D043008F000FC007DFD700AF002FC00FDFCF
      803F803FC01FC01FE1FFE1FFFFFFFFFFFFFFFFFFE000E000FFFFFFFFE000EFFE
      FFFFFFFFE000EFFE87C387C3E000EC068383838360006FFEC107C10720002802
      E00FE00F00000802F01FF01F20002802F83FF83F60006FFEF01FF01FE000EC06
      E00FE00FE000EFFEC107C107E000EC0683838383E000EFFE87C387C3E000EC06
      FFFFFFFFE000EFFEFFFFFFFFE000E000FC01FC01FFF8FFF8FC01FC0180008000
      FC01FC018000BFE0FC01FC018001A001FC01FC018003BC03800180018007A007
      8001BC018007BC078001BC018007A0078003BC038007BE078007BC078007A007
      800FBC0F8007BFF7803FBFBF8007A087803FBC3F800FBF8F807FBD7F801FBF9F
      80FFBCFF803F803F81FF81FFFFFFFFFF8FFF8FFFFFFFFFFF07FF07FFEFFDEFFD
      83FF83FFC7FFC7FF81FF81FFC3FBC3FBC0FFC0FFE3F7E3F7E003E003F1E7F1E7
      F001F001F8CFF8CFF800F800FC1FFC1FF800F800FE3FFE3FF800F800FC1FFC1F
      F800F800F8CFF8CFF800F800E1E7E1E7F800F800C3F3C3F3F800F800C7FDC7FD
      FC01FC01FFFFFFFFFE03FE03FFFFFFFF00000000000000000000000000000000
      000000000000}
  end
  object pm: TPopupMenu
    Left = 344
    Top = 64
    object N1: TMenuItem
      Caption = #20070'  '#21495
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #33258#32534#30721
      OnClick = N2Click
    end
    object N3: TMenuItem
      Caption = #20070#21517
      OnClick = N3Click
    end
    object N4: TMenuItem
      Caption = #23450#20215
      OnClick = N4Click
    end
    object N9: TMenuItem
      Caption = #20316#32773
      OnClick = N9Click
    end
  end
  object dsetbear: TADODataSet
    CommandText = 'select value from SYS_BSSET where name = '#39'bear'#39
    Parameters = <>
    Left = 72
    Top = 328
  end
  object query: TADOQuery
    Parameters = <>
    Left = 24
    Top = 184
  end
  object selectmenu: TPopupMenu
    Left = 512
    Top = 344
    object N5: TMenuItem
      Caption = #21333#36873
    end
    object N6: TMenuItem
      Caption = #20840#36873
      OnClick = N6Click
    end
    object N8: TMenuItem
      Caption = '--------'
      Visible = False
    end
    object N7: TMenuItem
      Caption = #25442#20070#22788#29702
      Visible = False
      OnClick = N7Click
    end
  end
  object aquery: TADOQuery
    Parameters = <>
    Left = 624
    Top = 376
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 616
    Top = 304
  end
  object ds: TDataSource
    DataSet = aq1
    Left = 784
    Top = 376
  end
  object aq1: TADOQuery
    Parameters = <>
    Left = 664
    Top = 408
  end
  object dshd: TDataSource
    DataSet = aqhd
    Left = 504
    Top = 32
  end
  object aqhd: TADOQuery
    Parameters = <>
    Left = 568
    Top = 40
  end
end