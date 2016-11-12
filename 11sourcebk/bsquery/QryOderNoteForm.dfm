inherited frmQryOderNote: TfrmQryOderNote
  Caption = #35746#21333#26597#35810
  ClientHeight = 734
  ClientWidth = 1016
  Color = 16180174
  OnKeyDown = FormKeyDown
  ExplicitWidth = 1032
  ExplicitHeight = 772
  PixelsPerInch = 96
  TextHeight = 13
  object rztlbr1: TRzToolbar [0]
    Left = 0
    Top = 0
    Width = 1016
    Height = 29
    AutoStyle = False
    Images = ImageList1
    ButtonWidth = 60
    ShowButtonCaptions = True
    TextOptions = ttoSelectiveTextOnRight
    BorderInner = fsNone
    BorderOuter = fsNone
    BorderSides = [sdTop]
    BorderWidth = 0
    Color = clSkyBlue
    GradientColorStyle = gcsMSOffice
    TabOrder = 0
    VisualStyle = vsClassic
    ToolbarControls = (
      tlbtnQry
      tlbtnExport
      BtnAlignBottom
      tlbtnExit)
    object tlbtnQry: TRzToolButton
      Left = 4
      Top = -4
      Width = 60
      Height = 36
      ImageIndex = 0
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      Caption = #26597#35810#13'(&F)'
      OnClick = tlbtnQryClick
    end
    object tlbtnExport: TRzToolButton
      Left = 64
      Top = -4
      Width = 60
      Height = 36
      ImageIndex = 2
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      Caption = 'Excel'#23548#20986'[F6]'
      OnClick = tlbtnExportClick
    end
    object tlbtnExit: TRzToolButton
      Left = 184
      Top = -4
      Width = 60
      Height = 36
      ImageIndex = 4
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      Caption = #36864#20986#13'(&Q)'
      OnClick = tlbtnExitClick
    end
    object BtnAlignBottom: TRzToolButton
      Left = 124
      Top = -4
      Width = 60
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 7
      ImageIndex = 6
      UseToolbarButtonSize = False
      Caption = #26368#23567#21270#13'(&N)'
      OnClick = BtnAlignBottomClick
    end
  end
  object grpbx1: TRzGroupBox [1]
    Left = 0
    Top = 35
    Width = 1016
    Height = 157
    Caption = #26597#35810#26465#20214
    ParentColor = True
    TabOrder = 1
    object lbl1: TLabel
      Left = 652
      Top = 49
      Width = 16
      Height = 13
      Caption = '>='
    end
    object lbl2: TLabel
      Left = 713
      Top = 49
      Width = 16
      Height = 13
      Caption = '<='
    end
    object lbl3: TLabel
      Left = 283
      Top = 77
      Width = 16
      Height = 13
      Caption = '>='
    end
    object lbl4: TLabel
      Left = 343
      Top = 76
      Width = 16
      Height = 13
      Caption = '<='
    end
    object Label36: TLabel
      Left = 652
      Top = 22
      Width = 16
      Height = 13
      Caption = '>='
    end
    object Label37: TLabel
      Left = 715
      Top = 22
      Width = 16
      Height = 13
      Caption = '<='
    end
    object spselectClient: TSpeedButton
      Left = 383
      Top = 100
      Width = 23
      Height = 21
      Flat = True
      Glyph.Data = {
        36040000424D3604000000000000360000002800000010000000100000000100
        2000000000000004000000000000000000000000000000000000FF00FF00CCCC
        CC00C0C0C000E5E5E500FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00CCCCCC006699
        99006666990099999900E5E5E500FF00FF00FF00FF00FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0066CC
        FF003399CC006666990099999900E5E5E500FF00FF00FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00CCCC
        FF0066CCFF003399CC006666990099999900E5E5E500FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
        FF00CCCCFF0066CCFF003399CC006666990099999900E5E5E500FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
        FF00FF00FF00CCCCFF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC99
        9900CC999900CC999900CCCC9900E5E5E500FF00FF00FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EA
        BF00FFFFCC00F2EABF00F2EABF00CC999900ECC6D900FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00E5E5E500CC999900FFCC9900FFFFCC00FFFF
        CC00FFFFCC00FFFFFF00FFFFFF00FFFFFF00CC999900E5E5E500FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FFCCCC00CCCC9900FFFFCC00F2EABF00FFFF
        CC00FFFFCC00FFFFFF00FFFFFF00FFFFFF00F2EABF00CCCC9900FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00CCCC9900FFCC9900F2EABF00F2EABF00FFFF
        CC00FFFFCC00FFFFCC00FFFFFF00FFFFFF00F2EABF00CC999900FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00CC999900F2EABF00F2EABF00F2EABF00F2EA
        BF00FFFFCC00FFFFCC00FFFFCC00FFFFCC00FFFFCC00CC999900FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00CCCC9900F2EABF00FFFFCC00F2EABF00F2EA
        BF00F2EABF00FFFFCC00FFFFCC00FFFFCC00F2EABF00CC999900FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EA
        BF00F2EABF00F2EABF00F2EABF00FFFFCC00CCCC9900CCCC9900FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00E5E5E500CC999900ECC6D900FFFFFF00FFFF
        CC00F2EABF00F2EABF00F2EABF00FFCC9900CC999900E5E5E500FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FFCCCC00CC999900FFCCCC00F2EA
        BF00F2EABF00F2EABF00CCCC9900CC999900FFCCCC00FF00FF00FF00FF00FF00
        FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00E5E5E500CCCC9900CC99
        9900CC999900CC999900CC999900E5E5E500FF00FF00FF00FF00}
      OnClick = spselectClientClick
    end
    object SpeedButton1: TSpeedButton
      Left = 913
      Top = 99
      Width = 89
      Height = 22
      Caption = #26126#32454#27983#35272#35774#32622
      Flat = True
      OnClick = SpeedButton1Click
    end
    object chckbxStartTime: TRzCheckBox
      Left = 9
      Top = 22
      Width = 67
      Height = 15
      Caption = #36215#22987#26102#38388
      State = cbUnchecked
      TabOrder = 0
    end
    object dtedtStart: TRzDateTimeEdit
      Left = 82
      Top = 19
      Width = 121
      Height = 21
      CalendarElements = [ceYear, ceMonth, ceArrows, ceDaysOfWeek, ceFillDays, ceTodayButton]
      CaptionTodayBtn = #20170#22825
      Date = 40041.000000000000000000
      EditType = etDate
      Format = 'yyyy-mm-dd'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
    end
    object chckbxEndTime: TRzCheckBox
      Left = 210
      Top = 21
      Width = 67
      Height = 15
      Caption = #32467#26463#26102#38388
      State = cbUnchecked
      TabOrder = 2
    end
    object dtedtEnd: TRzDateTimeEdit
      Left = 284
      Top = 19
      Width = 122
      Height = 21
      CalendarElements = [ceYear, ceMonth, ceArrows, ceDaysOfWeek, ceFillDays, ceTodayButton]
      CaptionTodayBtn = #20170#22825
      Date = 40041.000000000000000000
      EditType = etDate
      Format = 'yyyy-mm-dd'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
    end
    object chckbxBookName: TRzCheckBox
      Left = 9
      Top = 49
      Width = 67
      Height = 15
      Caption = #20070'        '#21517
      State = cbUnchecked
      TabOrder = 4
    end
    object chckbxISBN: TRzCheckBox
      Left = 9
      Top = 76
      Width = 67
      Height = 15
      Caption = #20070'        '#21495
      State = cbUnchecked
      TabOrder = 5
    end
    object chckbxCustomer: TRzCheckBox
      Left = 9
      Top = 103
      Width = 67
      Height = 15
      Caption = #23458'        '#25143
      State = cbUnchecked
      TabOrder = 6
    end
    object chckbxBkstack: TRzCheckBox
      Left = 786
      Top = 76
      Width = 43
      Height = 15
      Caption = #24211#20301
      State = cbUnchecked
      TabOrder = 7
      OnClick = chckbxBkstackClick
    end
    object chckbxUserDefNum: TRzCheckBox
      Left = 210
      Top = 48
      Width = 61
      Height = 15
      Caption = #33258' '#32534' '#21495
      State = cbUnchecked
      TabOrder = 8
    end
    object chckbxPrice: TRzCheckBox
      Left = 210
      Top = 76
      Width = 61
      Height = 15
      Caption = #23450'      '#20215
      State = cbUnchecked
      TabOrder = 9
    end
    object chckbxAuthor: TRzCheckBox
      Left = 416
      Top = 102
      Width = 43
      Height = 15
      Caption = #20316#32773
      State = cbUnchecked
      TabOrder = 10
    end
    object chckbxAmount: TRzCheckBox
      Left = 605
      Top = 48
      Width = 43
      Height = 15
      Caption = #25968#37327
      State = cbUnchecked
      TabOrder = 11
    end
    object chckbxPress: TRzCheckBox
      Left = 416
      Top = 48
      Width = 43
      Height = 15
      Caption = #29256#21035
      State = cbUnchecked
      TabOrder = 12
    end
    object chckbxType: TRzCheckBox
      Left = 416
      Top = 75
      Width = 43
      Height = 15
      Caption = #31867#21035
      State = cbUnchecked
      TabOrder = 13
    end
    object chckbxRemarks: TRzCheckBox
      Left = 604
      Top = 102
      Width = 43
      Height = 15
      Caption = #22791#27880
      State = cbUnchecked
      TabOrder = 14
    end
    object chckbxStorage: TRzCheckBox
      Left = 605
      Top = 76
      Width = 43
      Height = 15
      Caption = #24215#21495
      State = cbUnchecked
      TabOrder = 15
    end
    object edtBookName: TRzEdit
      Left = 82
      Top = 46
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 16
      OnChange = edtBookNameChange
    end
    object edtISBN: TRzEdit
      Left = 82
      Top = 73
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      MaxLength = 13
      TabOrder = 17
      OnChange = edtISBNChange
    end
    object edtUserDefNum: TRzEdit
      Left = 284
      Top = 46
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 18
      OnChange = edtUserDefNumChange
    end
    object edtAuthor: TRzEdit
      Left = 472
      Top = 100
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 19
      OnChange = edtAuthorChange
    end
    object edtPress: TRzEdit
      Tag = 1
      Left = 472
      Top = 46
      Width = 37
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 20
      OnKeyPress = edtPressKeyPress
    end
    object edtRemarks: TRzEdit
      Left = 652
      Top = 100
      Width = 127
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 21
      OnChange = edtRemarksChange
    end
    object edtCustomer: TRzEdit
      Tag = 3
      Left = 82
      Top = 100
      Width = 63
      Height = 21
      TabOrder = 22
      OnKeyPress = edtCustomerKeyPress
    end
    object numedtMinPrice: TRzNumericEdit
      Left = 299
      Top = 73
      Width = 45
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 23
      OnChange = numedtMinPriceChange
      AllowBlank = True
      IntegersOnly = False
      DisplayFormat = '###,##0.00'
    end
    object numedtMinAmount: TRzNumericEdit
      Left = 667
      Top = 46
      Width = 45
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 24
      OnChange = numedtMinAmountChange
      AllowBlank = True
      DisplayFormat = '###,##0;-###,##0'
    end
    object numedtMaxPrice: TRzNumericEdit
      Left = 359
      Top = 73
      Width = 47
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 25
      OnChange = numedtMaxPriceChange
      AllowBlank = True
      IntegersOnly = False
      DisplayFormat = '###,##0.00'
    end
    object numedtMaxAmount: TRzNumericEdit
      Left = 732
      Top = 46
      Width = 47
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 26
      OnChange = numedtMaxAmountChange
      AllowBlank = True
      DisplayFormat = '###,##0;-###,##0'
    end
    object dblkpcbbPress: TRzDBLookupComboBox
      Left = 508
      Top = 46
      Width = 85
      Height = 21
      DataField = 'PressID'
      KeyField = 'ID'
      ListField = 'AbbreviatedName'
      ListSource = dsrcPress
      TabOrder = 27
      OnClick = dblkpcbbPressClick
    end
    object dblkpcbbBookType: TRzDBLookupComboBox
      Left = 472
      Top = 73
      Width = 121
      Height = 21
      DataField = 'BktypeID'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcBookType
      TabOrder = 28
      OnClick = dblkpcbbBookTypeClick
    end
    object dblkpcbbStorage: TRzDBLookupComboBox
      Left = 652
      Top = 73
      Width = 127
      Height = 21
      DataField = 'StorageID'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcStorage
      TabOrder = 29
      OnClick = dblkpcbbStorageClick
    end
    object dblkpcbbBookstack: TRzDBLookupComboBox
      Left = 832
      Top = 73
      Width = 100
      Height = 21
      DataField = 'BkstackID'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcBookstack
      TabOrder = 30
      OnClick = dblkpcbbBookstackClick
    end
    object chstaff: TCheckBox
      Left = 416
      Top = 23
      Width = 55
      Height = 17
      Caption = #25805#20316#21592
      TabOrder = 31
    end
    object cbstaff: TComboBox
      Left = 472
      Top = 19
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 32
      OnClick = cbstaffClick
    end
    object chdiscount: TCheckBox
      Left = 604
      Top = 23
      Width = 43
      Height = 17
      Caption = #25240#25187
      TabOrder = 33
    end
    object edmaxdiscount: TEdit
      Left = 732
      Top = 19
      Width = 47
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 34
      OnChange = edmaxdiscountChange
    end
    object edmindiscount: TEdit
      Left = 667
      Top = 19
      Width = 45
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 35
      OnChange = edmindiscountChange
    end
    object chactive: TCheckBox
      Left = 786
      Top = 21
      Width = 49
      Height = 17
      Caption = #26377#25928
      TabOrder = 36
    end
    object chnoactive: TCheckBox
      Left = 833
      Top = 21
      Width = 49
      Height = 17
      Caption = #26080#25928
      TabOrder = 37
    end
    object edtclient: TEdit
      Left = 146
      Top = 100
      Width = 236
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 38
      OnChange = edtclientChange
    end
    object chsendamount: TCheckBox
      Left = 786
      Top = 50
      Width = 49
      Height = 17
      Caption = #24050#21457
      TabOrder = 39
    end
    object chunsendamount: TCheckBox
      Left = 833
      Top = 50
      Width = 40
      Height = 17
      Caption = #26410#21457
      TabOrder = 40
    end
    object chunarrive: TCheckBox
      Left = 882
      Top = 50
      Width = 55
      Height = 17
      Caption = #26410#21040#36135
      TabOrder = 41
    end
    object chbaoxiao: TCheckBox
      Left = 882
      Top = 21
      Width = 46
      Height = 17
      Caption = #21253#38144
      TabOrder = 42
    end
    object chxiankuan: TCheckBox
      Left = 943
      Top = 21
      Width = 44
      Height = 17
      Caption = #20808#27454
      TabOrder = 43
    end
    object chconfrim: TCheckBox
      Left = 943
      Top = 50
      Width = 65
      Height = 17
      Caption = #30830#35748#37319#36141
      TabOrder = 44
    end
    object chlocal: TCheckBox
      Left = 943
      Top = 76
      Width = 51
      Height = 17
      Caption = #38145#23450
      TabOrder = 45
    end
    object chunconfrim: TCheckBox
      Left = 786
      Top = 102
      Width = 87
      Height = 17
      Caption = #26410#30830#35748#37319#36141
      TabOrder = 46
    end
    object chsupplier: TRzCheckBox
      Left = 9
      Top = 130
      Width = 67
      Height = 15
      Caption = #20379'  '#24212'  '#21830
      State = cbUnchecked
      TabOrder = 47
    end
    object edsupplier: TRzEdit
      Tag = 3
      Left = 82
      Top = 127
      Width = 63
      Height = 21
      TabOrder = 48
      OnKeyPress = edsupplierKeyPress
    end
    object cbsupplier: TComboBox
      Left = 146
      Top = 127
      Width = 260
      Height = 21
      ItemHeight = 13
      TabOrder = 49
    end
    object cbstate: TComboBox
      Left = 472
      Top = 127
      Width = 121
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 50
      Text = #26410#23457#26680
      Items.Strings = (
        #26410#23457#26680
        #24050#23457#26680
        #24050#30830#23450#38145#23450#25968#37327)
    end
    object chstate: TCheckBox
      Left = 416
      Top = 129
      Width = 55
      Height = 17
      Caption = #29366#24577
      TabOrder = 51
    end
  end
  object pgcntrlResult: TRzPageControl [2]
    Left = 1
    Top = 197
    Width = 1009
    Height = 537
    ActivePage = tbshtByNtHeader
    Anchors = [akLeft, akTop, akRight, akBottom]
    DragIndicatorColor = 5263440
    TabIndex = 0
    TabOrder = 2
    TabStyle = tsBackSlant
    FixedDimension = 19
    object tbshtByNtHeader: TRzTabSheet
      Tag = 1
      Color = 16180174
      Caption = #25353#21333
      object dbgrdByNtHeader: TDBGridEh
        Left = 0
        Top = 0
        Width = 1005
        Height = 514
        Align = alClient
        DataSource = dsrcByNtHeader
        FixedColor = 16180174
        Flat = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        FooterColor = clWindow
        FooterFont.Charset = DEFAULT_CHARSET
        FooterFont.Color = clWindowText
        FooterFont.Height = -11
        FooterFont.Name = 'Tahoma'
        FooterFont.Style = []
        FooterRowCount = 1
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ParentFont = False
        SumList.Active = True
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clNavy
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnDblClick = dbgrdByNtHeaderDblClick
        OnTitleClick = dbgrdByNtHeaderTitleClick
        Columns = <
          item
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Caption = #24207#21495
            Width = 32
          end
          item
            EditButtons = <>
            FieldName = 'Code'
            Footers = <>
            Title.Caption = #21333#21495
            Width = 89
          end
          item
            EditButtons = <>
            FieldName = 'CustomerName'
            Footers = <>
            Title.Caption = #23458#25143#21517#31216
            Width = 167
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25968#37327
            Width = 57
          end
          item
            EditButtons = <>
            FieldName = 'OrderNoteSendAmount'
            Footer.FieldName = 'OrderNoteSendAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #24050#21457
            Width = 49
          end
          item
            EditButtons = <>
            FieldName = 'OrderNoteUnsendAmount'
            Footer.FieldName = 'OrderNoteUnsendAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #26410#21457
            Width = 45
          end
          item
            EditButtons = <>
            FieldName = 'localnum'
            Footer.FieldName = 'localnum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #38145#23450#25968#37327
            Width = 67
          end
          item
            EditButtons = <>
            FieldName = 'shstate'
            Footers = <>
            Title.Caption = #23457#26680#29366#24577
            Width = 51
          end
          item
            EditButtons = <>
            FieldName = 'OrderNoteHeaderRemarks'
            Footers = <>
            Title.Caption = #22791#27880
            Width = 137
          end
          item
            EditButtons = <>
            FieldName = 'Date'
            Footers = <>
            Title.Caption = #26085#26399
            Width = 75
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30721#27915
            Width = 59
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #23454#27915
          end
          item
            EditButtons = <>
            FieldName = 'StgName'
            Footers = <>
            Title.Caption = #24215#21517
            Width = 87
          end
          item
            EditButtons = <>
            FieldName = 'Operatorname'
            Footers = <>
            Title.Caption = #25805#20316#20154#21592
            Width = 53
          end>
      end
    end
    object tbshtByNote: TRzTabSheet
      Tag = 2
      Color = 16180174
      Caption = #26126#32454
      object dbgrdByNote: TDBGridEh
        Left = 0
        Top = 0
        Width = 1005
        Height = 514
        Align = alClient
        DataSource = dsrcByNote
        FixedColor = 16180174
        Flat = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        FooterColor = clWindow
        FooterFont.Charset = DEFAULT_CHARSET
        FooterFont.Color = clWindowText
        FooterFont.Height = -11
        FooterFont.Name = 'Tahoma'
        FooterFont.Style = []
        FooterRowCount = 1
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ParentFont = False
        PopupMenu = PopupMenu1
        SumList.Active = True
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clNavy
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnTitleClick = dbgrdByNoteTitleClick
        Columns = <
          item
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Caption = #24207#21495
            Width = 37
          end
          item
            EditButtons = <>
            FieldName = 'ISBN'
            Footers = <>
            Width = 81
          end
          item
            EditButtons = <>
            FieldName = 'BookName'
            Footers = <>
            Title.Caption = #20070#21517
            Width = 159
          end
          item
            EditButtons = <>
            FieldName = 'PressName'
            Footers = <>
            Title.Caption = #29256#21035
            Width = 56
          end
          item
            EditButtons = <>
            FieldName = 'yprice'
            Footers = <>
            Title.Caption = #21407#23450#20215
            Width = 41
          end
          item
            EditButtons = <>
            FieldName = 'Price'
            Footers = <>
            Title.Caption = #23450#20215
            Width = 38
          end
          item
            EditButtons = <>
            FieldName = 'Author'
            Footers = <>
            Title.Caption = #20316#32773
            Width = 46
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25968#37327
            Width = 54
          end
          item
            EditButtons = <>
            FieldName = 'OrderNoteSendAmount'
            Footer.FieldName = 'OrderNoteSendAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #24050#21457
            Width = 56
          end
          item
            EditButtons = <>
            FieldName = 'OrderNoteUnsendAmount'
            Footer.FieldName = 'OrderNoteUnsendAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #26410#21457
            Width = 54
          end
          item
            EditButtons = <>
            FieldName = 'needprocurenum'
            Footers = <>
            Title.Caption = #37319#36141#25968#37327
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'localnum'
            Footer.FieldName = 'localnum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #38145#23450#25968#37327
            Width = 54
          end
          item
            EditButtons = <>
            FieldName = 'unarrivenum'
            Footer.FieldName = 'unarrivenum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #26410#21040#36135
            Width = 48
          end
          item
            EditButtons = <>
            FieldName = 'ordernotebk'
            Footers = <>
            Title.Caption = #22791#27880
            Width = 78
          end
          item
            EditButtons = <>
            FieldName = 'clientbk'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23458#25143#22238#21578
            Width = 81
          end
          item
            EditButtons = <>
            FieldName = 'Date'
            Footers = <>
            Title.Caption = #26085#26399
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'CustomerName'
            Footers = <>
            Title.Caption = #23458#25143
            Width = 73
          end
          item
            EditButtons = <>
            FieldName = 'xuxiao'
            Footers = <>
            Title.Caption = #23398#26657#24207#21495
            Visible = False
          end
          item
            EditButtons = <>
            FieldName = 'xiaoqu'
            Footers = <>
            Title.Caption = #26657#21306
            Visible = False
          end
          item
            EditButtons = <>
            FieldName = 'xueyuan'
            Footers = <>
            Title.Caption = #23398#38498
            Visible = False
          end
          item
            EditButtons = <>
            FieldName = 'class'
            Footers = <>
            Title.Caption = #29677#32423
            Visible = False
          end
          item
            EditButtons = <>
            FieldName = 'course'
            Footers = <>
            Title.Caption = #35838#31243#21517#31216
            Visible = False
          end
          item
            EditButtons = <>
            FieldName = 'incode'
            Footers = <>
            Title.Caption = #20869#37096#35782#21035#30721
            Visible = False
          end
          item
            EditButtons = <>
            FieldName = 'teacher'
            Footers = <>
            Title.Caption = #20219#35838#25945#24072
            Visible = False
          end
          item
            EditButtons = <>
            FieldName = 'telphone'
            Footers = <>
            Title.Caption = #32852#31995#26041#24335
            Visible = False
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30721#27915
            Width = 61
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #23454#27915
            Width = 59
          end
          item
            EditButtons = <>
            FieldName = 'Code'
            Footers = <>
            Title.Caption = #21333#21495
            Width = 83
          end
          item
            EditButtons = <>
            FieldName = 'SupplierName'
            Footers = <>
            Title.Caption = #37319#36141#20379#24212#21830
            Width = 94
          end
          item
            EditButtons = <>
            FieldName = 'CgDate'
            Footers = <>
            Title.Caption = #37319#36141#26085#26399
            Width = 62
          end
          item
            EditButtons = <>
            FieldName = 'ProcureNtCode'
            Footers = <>
            Title.Caption = #37319#36141#21333#21495
            Width = 69
          end
          item
            EditButtons = <>
            FieldName = 'UserDefCode'
            Footers = <>
            Title.Caption = #33258#32534#30721
            Width = 55
          end
          item
            EditButtons = <>
            FieldName = 'BktypeName'
            Footers = <>
            Title.Caption = #31867#21035
            Width = 46
          end
          item
            EditButtons = <>
            FieldName = 'Discount'
            Footers = <>
            Title.Caption = #25240#25187
            Width = 53
          end
          item
            EditButtons = <>
            FieldName = 'PressDate'
            Footers = <>
            Title.Caption = #20986#29256#26085#26399
            Width = 54
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Caption = #24215#21517
            Width = 77
          end>
      end
    end
    object tbshtByCustomer: TRzTabSheet
      Tag = 3
      Color = 16180174
      Caption = #23458#25143
      object dbgrdByCustomer: TDBGridEh
        Left = 0
        Top = 0
        Width = 1005
        Height = 514
        Align = alClient
        DataSource = dsrcByCustomer
        FixedColor = 16180174
        Flat = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        FooterColor = clWindow
        FooterFont.Charset = DEFAULT_CHARSET
        FooterFont.Color = clWindowText
        FooterFont.Height = -11
        FooterFont.Name = 'Tahoma'
        FooterFont.Style = []
        FooterRowCount = 1
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ParentFont = False
        SumList.Active = True
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clNavy
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnTitleClick = dbgrdByCustomerTitleClick
        Columns = <
          item
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Caption = #24207#21495
            Width = 32
          end
          item
            EditButtons = <>
            FieldName = 'CustomerName'
            Footers = <>
            Title.Caption = #23458#25143#21517#31216
            Width = 113
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30721#27915
            Width = 69
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #23454#27915
            Width = 69
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25968#37327
            Width = 69
          end
          item
            EditButtons = <>
            FieldName = 'OrderNoteSendAmount'
            Footer.FieldName = 'OrderNoteSendAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #24050#21457
            Width = 67
          end
          item
            EditButtons = <>
            FieldName = 'OrderNoteUnsendAmount'
            Footer.FieldName = 'OrderNoteUnsendAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #26410#21457
            Width = 68
          end
          item
            EditButtons = <>
            FieldName = 'localnum'
            Footer.FieldName = 'localnum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #38145#23450#25968#37327
            Width = 67
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Caption = #24215#21517
            Width = 187
          end>
      end
    end
    object tbshtByBktype: TRzTabSheet
      Tag = 4
      Color = 16180174
      Caption = #31867#21035
      object dbgrdByBktype: TDBGridEh
        Left = 0
        Top = 0
        Width = 1005
        Height = 514
        Align = alClient
        DataSource = dsrcByBktype
        FixedColor = 16180174
        Flat = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        FooterColor = clWindow
        FooterFont.Charset = DEFAULT_CHARSET
        FooterFont.Color = clWindowText
        FooterFont.Height = -11
        FooterFont.Name = 'Tahoma'
        FooterFont.Style = []
        FooterRowCount = 1
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ParentFont = False
        SumList.Active = True
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clNavy
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnTitleClick = dbgrdByBktypeTitleClick
        Columns = <
          item
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Caption = #24207#21495
            Width = 27
          end
          item
            EditButtons = <>
            FieldName = 'BktypeName'
            Footers = <>
            Title.Caption = #31867#21035
            Width = 161
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30721#27915
            Width = 74
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #23454#27915
            Width = 69
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25968#37327
            Width = 66
          end
          item
            EditButtons = <>
            FieldName = 'OrderNoteSendAmount'
            Footer.FieldName = 'OrderNoteSendAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #24050#21457
            Width = 67
          end
          item
            EditButtons = <>
            FieldName = 'OrderNoteUnsendAmount'
            Footer.FieldName = 'OrderNoteUnsendAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #26410#21457
            Width = 68
          end
          item
            EditButtons = <>
            FieldName = 'localnum'
            Footer.FieldName = 'localnum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #38145#23450#25968#37327
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Caption = #24215#21517
            Width = 164
          end>
      end
    end
    object tbshtByPress: TRzTabSheet
      Tag = 5
      Color = 16180174
      Caption = #29256#21035
      object dbgrdByPress: TDBGridEh
        Left = 0
        Top = 0
        Width = 1005
        Height = 514
        Align = alClient
        DataSource = dsrcByPress
        FixedColor = 16180174
        Flat = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        FooterColor = clWindow
        FooterFont.Charset = DEFAULT_CHARSET
        FooterFont.Color = clWindowText
        FooterFont.Height = -11
        FooterFont.Name = 'Tahoma'
        FooterFont.Style = []
        FooterRowCount = 1
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        ParentFont = False
        SumList.Active = True
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clNavy
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnTitleClick = dbgrdByPressTitleClick
        Columns = <
          item
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Caption = #24207#21495
            Width = 31
          end
          item
            EditButtons = <>
            FieldName = 'PressName'
            Footers = <>
            Title.Caption = #29256#21035
            Width = 188
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30721#27915
            Width = 72
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #23454#27915
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25968#37327
            Width = 56
          end
          item
            EditButtons = <>
            FieldName = 'OrderNoteSendAmount'
            Footer.FieldName = 'OrderNoteSendAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #24050#21457
            Width = 68
          end
          item
            EditButtons = <>
            FieldName = 'OrderNoteUnsendAmount'
            Footer.FieldName = 'OrderNoteUnsendAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #26410#21457
            Width = 66
          end
          item
            EditButtons = <>
            FieldName = 'localnum'
            Footer.FieldName = 'localnum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #38145#23450#25968#37327
            Width = 51
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Caption = #24215#21517
            Width = 156
          end>
      end
    end
  end
  object GroupBox4: TGroupBox [3]
    Left = 913
    Top = 162
    Width = 110
    Height = 197
    Ctl3D = True
    ParentCtl3D = False
    TabOrder = 3
    Visible = False
    object ch1: TCheckBox
      Left = 16
      Top = 16
      Width = 73
      Height = 17
      Caption = #23398#26657#24207#21495
      TabOrder = 0
      OnClick = ch1Click
    end
    object ch2: TCheckBox
      Left = 16
      Top = 36
      Width = 47
      Height = 17
      Caption = #26657#21306
      TabOrder = 1
      OnClick = ch2Click
    end
    object ch3: TCheckBox
      Left = 16
      Top = 59
      Width = 54
      Height = 17
      Caption = #23398#38498
      TabOrder = 2
      OnClick = ch3Click
    end
    object ch4: TCheckBox
      Left = 16
      Top = 82
      Width = 44
      Height = 17
      Caption = #29677#32423
      TabOrder = 3
      OnClick = ch4Click
    end
    object ch5: TCheckBox
      Left = 16
      Top = 105
      Width = 81
      Height = 17
      Caption = #35838#31243#21517#31216
      TabOrder = 4
      OnClick = ch5Click
    end
    object ch6: TCheckBox
      Left = 16
      Top = 128
      Width = 91
      Height = 17
      Caption = #20869#37096#35782#21035#30721
      TabOrder = 5
      OnClick = ch6Click
    end
    object ch7: TCheckBox
      Left = 16
      Top = 151
      Width = 91
      Height = 17
      Caption = #20219#35838#25945#24072
      TabOrder = 6
      OnClick = ch7Click
    end
    object ch8: TCheckBox
      Left = 16
      Top = 174
      Width = 81
      Height = 17
      Caption = #32852#31995#26041#24335
      TabOrder = 7
      OnClick = ch8Click
    end
  end
  inherited qryUserAuthority: TADOQuery
    Left = 248
    Top = 456
  end
  inherited aquerybs: TADOQuery
    Left = 464
    Top = 344
  end
  object dsetByNtHeader: TADODataSet
    Parameters = <>
    Left = 32
    Top = 328
  end
  object dsrcByNtHeader: TDataSource
    DataSet = dsetByNtHeader
    Left = 32
    Top = 272
  end
  object dsetByNote: TADODataSet
    Parameters = <>
    Left = 120
    Top = 328
  end
  object dsrcByNote: TDataSource
    DataSet = dsetByNote
    Left = 176
    Top = 320
  end
  object dsetByCustomer: TADODataSet
    Parameters = <>
    Left = 296
    Top = 288
  end
  object dsrcByCustomer: TDataSource
    DataSet = dsetByCustomer
    Left = 336
    Top = 336
  end
  object dsetByBktype: TADODataSet
    Parameters = <>
    Left = 504
    Top = 296
  end
  object dsrcByBktype: TDataSource
    DataSet = dsetByBktype
    Left = 400
    Top = 344
  end
  object dsetByPress: TADODataSet
    Parameters = <>
    Left = 448
    Top = 304
  end
  object dsrcByPress: TDataSource
    DataSet = dsetByPress
    Left = 304
    Top = 424
  end
  object spQryNote: TADOStoredProc
    ProcedureName = 'USP_QRY_Get_NoteInfo;1'
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Precision = 10
        Value = Null
      end
      item
        Name = '@Start'
        Attributes = [paNullable]
        DataType = ftDateTime
        Value = Null
      end
      item
        Name = '@End'
        Attributes = [paNullable]
        DataType = ftDateTime
        Value = Null
      end
      item
        Name = '@Name'
        Attributes = [paNullable]
        DataType = ftWideString
        Size = 100
        Value = Null
      end
      item
        Name = '@UserDefCode'
        Attributes = [paNullable]
        DataType = ftWideString
        Size = 10
        Value = Null
      end
      item
        Name = '@PressID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@ISBN'
        Attributes = [paNullable]
        DataType = ftString
        Size = 15
        Value = Null
      end
      item
        Name = '@MaxPrice'
        Attributes = [paNullable]
        DataType = ftBCD
        Precision = 19
        Value = Null
      end
      item
        Name = '@MinPrice'
        Attributes = [paNullable]
        DataType = ftBCD
        Precision = 19
        Value = Null
      end
      item
        Name = '@BktypeID'
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
        Name = '@Author'
        Attributes = [paNullable]
        DataType = ftWideString
        Size = 10
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
        Name = '@BkstackID'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@MaxAmount'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@MinAmount'
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
        Name = '@Bsmode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@SearchMode'
        Attributes = [paNullable]
        DataType = ftInteger
        Precision = 10
        Value = Null
      end
      item
        Name = '@type'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@return'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@lost'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@damage'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@staff'
        Attributes = [paNullable]
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@mindiscount'
        Attributes = [paNullable]
        DataType = ftFloat
        Value = Null
      end
      item
        Name = '@maxdiscount'
        Attributes = [paNullable]
        DataType = ftFloat
        Value = Null
      end
      item
        Name = '@check'
        DataType = ftInteger
        Size = 10
        Value = Null
      end
      item
        Name = '@nocheck'
        DataType = ftInteger
        Size = 10
        Value = Null
      end
      item
        Name = '@checkpart'
        DataType = ftInteger
        Size = 10
        Value = Null
      end
      item
        Name = '@checked'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@SupplierID'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@BKJYtype'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@MaxDamage'
        DataType = ftInteger
        Size = 10
        Value = Null
      end
      item
        Name = '@MinDamage'
        DataType = ftInteger
        Size = 10
        Value = Null
      end
      item
        Name = '@career'
        DataType = ftInteger
        Size = 10
        Value = Null
      end
      item
        Name = '@andan'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@outstorage'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@instorage'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@Maxyk'
        DataType = ftInteger
        Size = 10
        Value = Null
      end>
    Left = 368
    Top = 408
  end
  object dsetCustomer: TADODataSet
    CursorType = ctStatic
    CommandText = 
      'select ID, Name from CUST_CustomerInfo where Type in(2,3) order ' +
      'by name'
    Parameters = <>
    Left = 168
    Top = 416
  end
  object dsrcCustomer: TDataSource
    DataSet = dsetCustomer
    Left = 200
    Top = 376
  end
  object dsrcPress: TDataSource
    DataSet = dsetPress
    Left = 520
    Top = 344
  end
  object dsetBookType: TADODataSet
    CursorType = ctStatic
    CommandText = 'select ID, Name from BS_BookType where ParentID=1'
    Parameters = <>
    Left = 520
    Top = 424
  end
  object dsrcBookType: TDataSource
    DataSet = dsetBookType
    Left = 608
    Top = 424
  end
  object dsrcStorage: TDataSource
    DataSet = dsetStorage
    Left = 584
    Top = 360
  end
  object dsetStorage: TADODataSet
    CursorType = ctStatic
    CommandText = 'select ID, Name from SYS_StorageInfo'
    Parameters = <>
    Left = 160
    Top = 464
  end
  object dsrcBookstack: TDataSource
    DataSet = dsetBookstack
    Left = 216
    Top = 256
  end
  object dsetBookstack: TADODataSet
    CursorType = ctStatic
    CommandText = 'select ID, Name from STK_BookstackInfo where StgID=0'
    Parameters = <>
    Left = 80
    Top = 456
  end
  object qryItems: TADOQuery
    Parameters = <>
    Left = 640
    Top = 368
  end
  object ImageList1: TImageList
    Left = 432
    Top = 416
    Bitmap = {
      494C010108000A00A40010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000003000000001002000000000000030
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E2EFF100E5E5E500B2B2
      B200CC9999009966660099666600B2B2B200CCCCCC00E5E5E500E2EFF1000000
      00000000000000000000000000000000000000000000E2EFF10000000000B2B2
      B200999999009999990099999900B2B2B200CCCCCC0000000000E2EFF1000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      990099999900999999000000000000000000E5E5E500CC99990099666600CC99
      9900CC999900FFFFFF00996666009999990099999900B2B2B200E5E5E5000000
      0000000000000000000000000000000000000000000099999900999999009999
      990099999900FFFFFF00999999009999990099999900B2B2B200000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600336699003366990033669900E2EFF1000000
      0000000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900999999009999990099999900E2EFF1000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCCC000099CC00FFFFFF00FFCC
      CC000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000C0C0C00099999900FFFFFF00CCCC
      CC00000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCFF003399CC00FFCCCC00CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000CCCCCC0099999900CCCCCC009999
      9900000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900000000000000000099666600FFCC9900CC999900CC99
      6600FFCCCC00FFFFFF009966660099CCCC0099CCFF00B2B2B200FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000999999009999
      9900CCCCCC00FFFFFF0099999900CCCCCC00CCCCCC00B2B2B200999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC990099666600FFFF
      FF00FFCCCC00FFFFFF009966660099CCCC00C0C0C000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C00066666600FFFF
      FF00CCCCCC00FFFFFF0099999900CCCCCC00C0C0C00099999900999999009999
      99009999990099999900999999000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000099666600FFCC9900CC9999009966
      6600FFCCCC00FFFFFF009966660000000000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000999999006666
      6600CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660000000000CC999900CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      99009999990099999900999999000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00E2EFF100CC999900FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E2EFF10099999900999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660099CCCC000000000099CCCC00FFCC9900CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E500CCCCCC00C0C0C0009999
      99000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00000000003399CC0000000000FFCC
      9900000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E5009999990000000000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C0C000CC996600CC99
      9900CCCC9900FFFFFF00996666000099CC000099CC000099CC00000000000000
      00000000000000000000000000000000000000000000C0C0C000999999009999
      9900C0C0C000FFFFFF0099999900999999009999990099999900000000000000
      00000000000000000000000000000000000000000000CC99660000000000CC99
      660000000000CC99660000000000CC99660000000000CC99660000000000CC99
      660000000000CC996600000000000000000000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000CCCCCC0000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC000000000000000000000000000000000000000000CCCC
      CC00CC9999009966660099666600000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00999999009999990099999900000000000000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000066CCFF003399CC006666
      990099999900E5E5E50000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00B2B2B2009999
      990099999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      99000000000000000000000000000000000000000000CCCCFF0066CCFF003399
      CC006666990099999900E5E5E500000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E5E5E500CCCCCC00B2B2
      B2009999990099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300000000000000000000000000000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999000000000000000000000000000000000000000000CCCCFF0066CC
      FF003399CC006666990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E5E5E500CCCC
      CC00B2B2B2009999990099999900E5E5E5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300009933
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      990000000000000000000000000000000000000000000000000000000000CCCC
      FF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC999900CC999900CC99
      9900CCCC9900E5E5E5000000000000000000000000000000000000000000E5E5
      E500CCCCCC00B2B2B20099999900CCCCCC00E5E5E50099999900999999009999
      9900B2B2B200E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EABF00FFFFCC00F2EA
      BF00F2EABF00CC999900ECC6D900000000000000000000000000000000000000
      0000E5E5E500CCCCCC00B2B2B20099999900B2B2B200CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900E5E5E500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000E5E5E500CC999900FFCC9900FFFFCC00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E50099999900E5E5E500CC996600CC996600CC996600CC99
      6600CC996600CC996600CC99660000000000000000003399CC00006699000066
      9900006699000066990000669900006699009999990099999900999999009999
      9900999999009999990099999900000000000000000099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFCC00F2EABF00FFFFCC00FFFFCC00FFFF
      FF00FFFFFF00FFFFFF00F2EABF00CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00E5E5
      E500E5E5E500E5E5E500CCCCCC00B2B2B200CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CCCC9900FFCC9900F2EABF00F2EABF00FFFFCC00FFFFCC00FFFF
      CC00FFFFFF00FFFFFF00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00E5E5E500E5E5E500CCCCCC0099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CC999900F2EABF00F2EABF00F2EABF00F2EABF00FFFFCC00FFFF
      CC00FFFFCC00FFFFCC00FFFFCC00CC9999000000000000000000000000000000
      00000000000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC0099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000CCCC9900F2EABF00FFFFCC00F2EABF00F2EABF00F2EABF00FFFF
      CC00FFFFCC00FFFFCC00F2EABF00CC9999000000000000000000000000000000
      000000000000B2B2B200CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC0099999900CC996600FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00CC99660000000000000000003399CC0099FFFF0099FF
      FF0099FFFF0099FFFF0099FFFF00006699009999990000000000000000000000
      0000000000000000000099999900000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EABF00F2EABF00F2EA
      BF00F2EABF00FFFFCC00CCCC9900CCCC99000000000000000000000000000000
      000000000000E5E5E500B2B2B200E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00B2B2B200B2B2B200CC996600FFFFFF00FFFFFF00CC99
      6600CC996600CC996600CC99660000000000000000003399CC0099FFFF0099FF
      FF003399CC003399CC003399CC003399CC009999990000000000000000009999
      9900999999009999990099999900000000000000000099999900CCCCCC00CCCC
      CC00999999009999990099999900999999000000000000000000000000000000
      000000000000E5E5E500CC999900ECC6D900FFFFFF00FFFFCC00F2EABF00F2EA
      BF00F2EABF00FFCC9900CC999900E5E5E5000000000000000000000000000000
      000000000000E5E5E50099999900E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00E5E5E50099999900E5E5E500CC996600FFFFFF00FFFFFF00CC99
      6600E5E5E500CC9966000000000000000000000000003399CC0099FFFF0099FF
      FF003399CC00CCFFFF0000669900000000009999990000000000000000009999
      9900E5E5E5009999990000000000000000000000000099999900CCCCCC00CCCC
      CC0099999900CCCCCC0099999900000000000000000000000000000000000000
      00000000000000000000FFCCCC00CC999900FFCCCC00F2EABF00F2EABF00F2EA
      BF00CCCC9900CC999900FFCCCC00000000000000000000000000000000000000
      00000000000000000000E5E5E50099999900E5E5E500CCCCCC00CCCCCC00CCCC
      CC00B2B2B20099999900E5E5E50000000000CC996600FFFFFF00FFFFFF00CC99
      6600CC996600000000000000000000000000000000003399CC0099FFFF0099FF
      FF003399CC000066990000000000000000009999990000000000000000009999
      9900999999000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500CCCC9900CC999900CC999900CC99
      9900CC999900E5E5E50000000000000000000000000000000000000000000000
      0000000000000000000000000000E5E5E500B2B2B20099999900999999009999
      990099999900E5E5E5000000000000000000CC996600CC996600CC996600CC99
      660000000000000000000000000000000000000000003399CC003399CC003399
      CC003399CC000000000000000000000000009999990099999900999999009999
      9900000000000000000000000000000000000000000099999900999999009999
      990099999900000000000000000000000000424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FDFFFDFFFFFFFFFFE0FFE8FFFFFFFFFF
      801FA05F80038003001F803F80038003001F001F80038003000F000F80038003
      000F000F80038003000F000FFFFFFFFF00010001BFFBBFFB01010001FFFFFFFF
      01010001BFFBBFFB000F000FFFFFFFFF008F000FBFFBBFFB00AF002FFFFFFFFF
      803F803FAAABAAABE1FFE1FFFFFFFFFF8FFF8FFFFFFFFFFF07FF07FFFFDFFFDF
      83FF83FFFFCFFFCF81FF81FFE007E007C0FFC0FFFFCFFFCFE003E003FFDFFFDF
      F001F001FFFFFFFFF800F80001800180F800F80001807D80F800F80001807D80
      F800F80001807D80F800F80001807D80F800F80001806180F800F80003816381
      FC01FC0107836783FE03FE030F870F8700000000000000000000000000000000
      000000000000}
  end
  object dsetPress: TADODataSet
    CommandText = 'select ID,PresentNum, AbbreviatedName from BS_PressInfo'
    Parameters = <>
    Left = 368
    Top = 280
  end
  object savedlg: TSaveDialog
    Left = 720
    Top = 264
  end
  object PopupMenu1: TPopupMenu
    Left = 632
    Top = 264
    object N1: TMenuItem
      Caption = #21382#21490#26126#32454
      OnClick = N1Click
    end
  end
end
