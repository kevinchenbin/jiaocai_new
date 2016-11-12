inherited frmQryCheckNote: TfrmQryCheckNote
  Caption = #30424#28857#26597#35810
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
    Top = 33
    Width = 1008
    Height = 136
    Caption = #26597#35810#26465#20214
    ParentColor = True
    TabOrder = 1
    object lbl1: TLabel
      Left = 694
      Top = 76
      Width = 16
      Height = 13
      Caption = '>='
    end
    object lbl2: TLabel
      Left = 755
      Top = 76
      Width = 16
      Height = 13
      Caption = '<='
    end
    object lbl3: TLabel
      Left = 306
      Top = 76
      Width = 16
      Height = 13
      Caption = '>='
    end
    object lbl4: TLabel
      Left = 366
      Top = 76
      Width = 16
      Height = 13
      Caption = '<='
    end
    object Label7: TLabel
      Left = 886
      Top = 51
      Width = 16
      Height = 13
      Caption = '>='
    end
    object Label8: TLabel
      Left = 946
      Top = 49
      Width = 16
      Height = 13
      Caption = '<='
    end
    object Label9: TLabel
      Left = 886
      Top = 78
      Width = 16
      Height = 13
      Caption = '>='
    end
    object Label10: TLabel
      Left = 946
      Top = 76
      Width = 16
      Height = 13
      Caption = '<='
    end
    object chckbxStartTime: TRzCheckBox
      Left = 25
      Top = 22
      Width = 67
      Height = 15
      Caption = #36215#22987#26102#38388
      State = cbUnchecked
      TabOrder = 0
    end
    object dtedtStart: TRzDateTimeEdit
      Left = 98
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
      Left = 233
      Top = 21
      Width = 67
      Height = 15
      Caption = #32467#26463#26102#38388
      State = cbUnchecked
      TabOrder = 2
    end
    object dtedtEnd: TRzDateTimeEdit
      Left = 306
      Top = 19
      Width = 121
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
      Left = 25
      Top = 49
      Width = 67
      Height = 15
      Caption = #20070'        '#21517
      State = cbUnchecked
      TabOrder = 4
    end
    object chckbxISBN: TRzCheckBox
      Left = 25
      Top = 76
      Width = 67
      Height = 15
      Caption = #20070'        '#21495
      State = cbUnchecked
      TabOrder = 5
    end
    object chckbxCustomer: TRzCheckBox
      Left = 25
      Top = 103
      Width = 67
      Height = 15
      Caption = #20379'  '#24212'  '#21830
      State = cbUnchecked
      TabOrder = 6
    end
    object chckbxBkstack: TRzCheckBox
      Left = 637
      Top = 48
      Width = 43
      Height = 15
      Caption = #24211#20301
      State = cbUnchecked
      TabOrder = 7
      OnClick = chckbxBkstackClick
    end
    object chckbxUserDefNum: TRzCheckBox
      Left = 233
      Top = 48
      Width = 61
      Height = 15
      Caption = #33258' '#32534' '#21495
      State = cbUnchecked
      TabOrder = 8
    end
    object chckbxPrice: TRzCheckBox
      Left = 233
      Top = 75
      Width = 61
      Height = 15
      Caption = #23450'      '#20215
      State = cbUnchecked
      TabOrder = 9
    end
    object chckbxAuthor: TRzCheckBox
      Left = 233
      Top = 103
      Width = 61
      Height = 15
      Caption = #20316'      '#32773
      State = cbUnchecked
      TabOrder = 10
    end
    object chckbxAmount: TRzCheckBox
      Left = 637
      Top = 75
      Width = 43
      Height = 15
      Caption = #25968#37327
      State = cbUnchecked
      TabOrder = 11
    end
    object chckbxPress: TRzCheckBox
      Left = 443
      Top = 48
      Width = 43
      Height = 15
      Caption = #29256#21035
      State = cbUnchecked
      TabOrder = 12
    end
    object chckbxType: TRzCheckBox
      Left = 443
      Top = 76
      Width = 43
      Height = 15
      Caption = #31867#21035
      State = cbUnchecked
      TabOrder = 13
    end
    object chckbxRemarks: TRzCheckBox
      Left = 443
      Top = 103
      Width = 43
      Height = 15
      Caption = #22791#27880
      State = cbUnchecked
      TabOrder = 14
    end
    object chckbxStorage: TRzCheckBox
      Left = 637
      Top = 103
      Width = 43
      Height = 15
      Caption = #24215#21495
      State = cbUnchecked
      TabOrder = 15
    end
    object edtBookName: TRzEdit
      Left = 98
      Top = 46
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 16
      OnChange = edtBookNameChange
    end
    object edtISBN: TRzEdit
      Left = 98
      Top = 73
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      MaxLength = 13
      TabOrder = 17
      OnChange = edtISBNChange
    end
    object edtUserDefNum: TRzEdit
      Left = 306
      Top = 46
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 18
      OnChange = edtUserDefNumChange
    end
    object edtAuthor: TRzEdit
      Left = 306
      Top = 100
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 19
      OnChange = edtAuthorChange
    end
    object edtPress: TRzEdit
      Tag = 1
      Left = 499
      Top = 46
      Width = 37
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 20
      OnKeyPress = edtPressKeyPress
    end
    object edtRemarks: TRzEdit
      Left = 499
      Top = 100
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 21
      OnChange = edtRemarksChange
    end
    object edtCustomer: TRzEdit
      Tag = 2
      Left = 98
      Top = 100
      Width = 37
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 22
      OnKeyPress = edtPressKeyPress
    end
    object numedtMinPrice: TRzNumericEdit
      Left = 322
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
      Left = 709
      Top = 73
      Width = 45
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 24
      OnChange = numedtMinAmountChange
      AllowBlank = True
      IntegersOnly = False
      DisplayFormat = '###,##0;-###,##0'
    end
    object numedtMaxPrice: TRzNumericEdit
      Left = 382
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
      Left = 774
      Top = 73
      Width = 47
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 26
      OnChange = numedtMaxAmountChange
      AllowBlank = True
      IntegersOnly = False
      DisplayFormat = '###,##0;-###,##0'
    end
    object dblkpcbbPress: TRzDBLookupComboBox
      Left = 535
      Top = 46
      Width = 85
      Height = 21
      DataField = 'PressID'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'AbbreviatedName'
      ListSource = dsrcPress
      TabOrder = 27
      OnClick = dblkpcbbPressClick
    end
    object dblkpcbbCustomer: TRzDBLookupComboBox
      Left = 134
      Top = 100
      Width = 85
      Height = 21
      DataField = 'CustomerID'
      DropDownWidth = 150
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcCustomer
      TabOrder = 28
      OnClick = dblkpcbbCustomerClick
    end
    object dblkpcbbBookType: TRzDBLookupComboBox
      Left = 499
      Top = 73
      Width = 121
      Height = 21
      DataField = 'BktypeID'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcBookType
      TabOrder = 29
      OnClick = dblkpcbbBookTypeClick
    end
    object dblkpcbbStorage: TRzDBLookupComboBox
      Left = 694
      Top = 100
      Width = 127
      Height = 21
      DataField = 'StorageID'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcStorage
      TabOrder = 30
      OnClick = dblkpcbbStorageClick
    end
    object dblkpcbbBookstack: TRzDBLookupComboBox
      Left = 694
      Top = 46
      Width = 127
      Height = 21
      DataField = 'BkstackID'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcBookstack
      TabOrder = 31
      OnClick = dblkpcbbBookstackClick
    end
    object chstaff: TCheckBox
      Left = 443
      Top = 21
      Width = 55
      Height = 17
      Caption = #25805#20316#21592
      TabOrder = 32
    end
    object cbstaff: TComboBox
      Left = 499
      Top = 19
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 33
      OnClick = cbstaffClick
    end
    object cbdamage: TCheckBox
      Left = 838
      Top = 48
      Width = 41
      Height = 17
      Caption = #25439#37327
      TabOrder = 34
    end
    object minnu: TRzNumericEdit
      Left = 964
      Top = 46
      Width = 40
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 35
      AllowBlank = True
      IntegersOnly = False
      DisplayFormat = '###,##0;-###,##0'
    end
    object maxnu: TRzNumericEdit
      Left = 903
      Top = 46
      Width = 37
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 36
      AllowBlank = True
      IntegersOnly = False
      DisplayFormat = '###,##0;-###,##0'
    end
    object chchayi: TCheckBox
      Left = 838
      Top = 103
      Width = 78
      Height = 17
      Caption = #24046#24322#26597#35810
      TabOrder = 37
    end
    object chyingkui: TCheckBox
      Left = 838
      Top = 75
      Width = 41
      Height = 17
      Caption = #30408#20111
      TabOrder = 38
    end
    object numykmax: TRzNumericEdit
      Left = 964
      Top = 73
      Width = 40
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 39
      AllowBlank = True
      IntegersOnly = False
      DisplayFormat = '###,##0;-###,##0'
    end
    object numykmin: TRzNumericEdit
      Left = 903
      Top = 73
      Width = 37
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 40
      AllowBlank = True
      IntegersOnly = False
      DisplayFormat = '###,##0;-###,##0'
    end
  end
  object pgcntrlResult: TRzPageControl [2]
    Left = 1
    Top = 175
    Width = 1007
    Height = 558
    ActivePage = tbshtByNtHeader
    Anchors = [akLeft, akTop, akRight, akBottom]
    DragIndicatorColor = 5263440
    ShowShadow = False
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
        Height = 537
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
            Width = 31
          end
          item
            EditButtons = <>
            FieldName = 'checkstockNum'
            Footers = <>
            Title.Caption = #21333#21495
            Width = 89
          end
          item
            EditButtons = <>
            FieldName = 'checkdate'
            Footers = <>
            Title.Caption = #26085#26399
            Width = 107
          end
          item
            EditButtons = <>
            FieldName = 'ShouldAmount'
            Footer.FieldName = 'ShouldAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30424#28857#25968
            Width = 71
          end
          item
            EditButtons = <>
            FieldName = 'ActualAmount'
            Footer.FieldName = 'ActualAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #24211#23384#25968
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'Balance'
            Footer.FieldName = 'Balance'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30408#20111#25968
            Width = 68
          end
          item
            EditButtons = <>
            FieldName = 'BFixedPrice'
            Footer.FieldName = 'BFixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30408#20111#30721#27915
            Width = 67
          end
          item
            EditButtons = <>
            FieldName = 'BDiscountPrice'
            Footer.FieldName = 'BDiscountPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30408#20111#23454#27915
            Width = 69
          end
          item
            EditButtons = <>
            FieldName = 'totaldamagenum'
            Footer.FieldName = 'totaldamagenum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25439#37327
            Width = 55
          end
          item
            EditButtons = <>
            FieldName = 'opname'
            Footers = <>
            Title.Caption = #25805#20316#21592
            Width = 48
          end
          item
            EditButtons = <>
            FieldName = 'BookstackInfoName'
            Footers = <>
            Title.Caption = #24211#20301
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'StorageInfoName'
            Footers = <>
            Title.Caption = #24215#21517
            Width = 117
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
        Height = 537
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
            Width = 39
          end
          item
            EditButtons = <>
            FieldName = 'ISBN'
            Footers = <>
            Width = 82
          end
          item
            EditButtons = <>
            FieldName = 'BookName'
            Footers = <>
            Title.Caption = #20070#21517
            Width = 185
          end
          item
            EditButtons = <>
            FieldName = 'UserDefCode'
            Footers = <>
            Title.Caption = #33258#32534#30721
            Width = 71
          end
          item
            EditButtons = <>
            FieldName = 'Price'
            Footers = <>
            Title.Caption = #23450#20215
            Width = 40
          end
          item
            EditButtons = <>
            FieldName = 'Author'
            Footers = <>
            Title.Caption = #20316#32773
            Width = 43
          end
          item
            EditButtons = <>
            FieldName = 'BktypeName'
            Footers = <>
            Title.Caption = #31867#21035
            Width = 42
          end
          item
            EditButtons = <>
            FieldName = 'PressName'
            Footers = <>
            Title.Caption = #29256#21035
            Width = 49
          end
          item
            EditButtons = <>
            FieldName = 'Code'
            Footers = <>
            Title.Caption = #21333#21495
            Width = 74
          end
          item
            EditButtons = <>
            FieldName = 'ShouldAmount'
            Footer.FieldName = 'ShouldAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30424#28857#25968
            Width = 54
          end
          item
            EditButtons = <>
            FieldName = 'ActualAmount'
            Footer.FieldName = 'ActualAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #24211#23384#25968
            Width = 52
          end
          item
            EditButtons = <>
            FieldName = 'Balance'
            Footer.FieldName = 'Balance'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30408#20111#25968
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'BFixedPrice'
            Footer.FieldName = 'BFixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30408#20111#30721#27915
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'BDiscountPrice'
            Footer.FieldName = 'BDiscountPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30408#20111#23454#27915
            Width = 74
          end
          item
            EditButtons = <>
            FieldName = 'BookstackInfoName'
            Footers = <>
            Title.Caption = #24211#20301
            Width = 59
          end
          item
            EditButtons = <>
            FieldName = 'totaldamagenum'
            Footers = <>
            Title.Caption = #25439#37327
            Width = 51
          end
          item
            EditButtons = <>
            FieldName = 'Date'
            Footers = <>
            Title.Caption = #26085#26399
            Width = 76
          end
          item
            EditButtons = <>
            FieldName = 'CustomerName'
            Footers = <>
            Title.Caption = #20379#24212#21830
            Width = 58
          end
          item
            EditButtons = <>
            FieldName = 'PressDate'
            Footers = <>
            Title.Caption = #20986#29256#26085#26399
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Caption = #24215#21517
            Width = 97
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
        Height = 537
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
            Width = 30
          end
          item
            EditButtons = <>
            FieldName = 'BktypeName'
            Footers = <>
            Title.Caption = #31867#21035
            Width = 158
          end
          item
            EditButtons = <>
            FieldName = 'ShouldAmount'
            Footer.FieldName = 'ShouldAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30424#28857#25968
            Width = 75
          end
          item
            EditButtons = <>
            FieldName = 'ActualAmount'
            Footer.FieldName = 'ActualAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #24211#23384#25968
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'Balance'
            Footer.FieldName = 'Balance'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30408#20111#25968
            Width = 50
          end
          item
            EditButtons = <>
            FieldName = 'BFixedPrice'
            Footer.FieldName = 'BFixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30408#20111#30721#27915
            Width = 69
          end
          item
            EditButtons = <>
            FieldName = 'BDiscountPrice'
            Footer.FieldName = 'BDiscountPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30408#20111#23454#27915
            Width = 69
          end
          item
            EditButtons = <>
            FieldName = 'totaldamagenum'
            Footers = <>
            Title.Caption = #25439#37327
            Width = 53
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Caption = #24215#21517
            Width = 140
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
        Height = 537
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
            Width = 184
          end
          item
            EditButtons = <>
            FieldName = 'ShouldAmount'
            Footer.FieldName = 'ShouldAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30424#28857#25968
            Width = 73
          end
          item
            EditButtons = <>
            FieldName = 'ActualAmount'
            Footer.FieldName = 'ActualAmount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #24211#23384#25968
            Width = 73
          end
          item
            EditButtons = <>
            FieldName = 'Balance'
            Footer.FieldName = 'Balance'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30408#20111#25968
            Width = 56
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Caption = #24215#21517
            Width = 187
          end
          item
            EditButtons = <>
            FieldName = 'BFixedPrice'
            Footer.FieldName = 'BFixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30408#20111#30721#27915
            Width = 67
          end
          item
            EditButtons = <>
            FieldName = 'BDiscountPrice'
            Footer.FieldName = 'BDiscountPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30408#20111#23454#27915
            Width = 69
          end
          item
            EditButtons = <>
            FieldName = 'totaldamagenum'
            Footer.FieldName = 'totaldamagenum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25439#37327
            Width = 60
          end>
      end
    end
  end
  object rgtype: TRadioGroup [3]
    Left = 637
    Top = 42
    Width = 367
    Height = 31
    Columns = 3
    ItemIndex = 0
    Items.Strings = (
      #23616#37096#30424#28857
      #23454#24211#30424#28857
      #24211#23384#35843#25972)
    TabOrder = 3
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
    Left = 120
    Top = 272
  end
  object dsetByCustomer: TADODataSet
    Parameters = <>
    Left = 296
    Top = 288
  end
  object dsrcByCustomer: TDataSource
    DataSet = dsetByCustomer
    Left = 344
    Top = 288
  end
  object dsetByBktype: TADODataSet
    Parameters = <>
    Left = 392
    Top = 312
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
        DataType = ftFloat
        Value = Null
      end
      item
        Name = '@maxdiscount'
        DataType = ftFloat
        Value = Null
      end
      item
        Name = '@check'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@nocheck'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@checkpart'
        DataType = ftInteger
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
        Name = '@MinDamage'
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
        Name = '@career'
        DataType = ftInteger
        Size = 10
        Value = Null
      end
      item
        Name = '@andan'
        DataType = ftInteger
        Size = 10
        Value = Null
      end
      item
        Name = '@outstorage'
        DataType = ftInteger
        Size = 10
        Value = Null
      end
      item
        Name = '@instorage'
        DataType = ftInteger
        Size = 10
        Value = Null
      end
      item
        Name = '@Maxyk'
        DataType = ftInteger
        Size = 10
        Value = Null
      end
      item
        Name = '@Minyk'
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
      'select ID, Name from CUST_CustomerInfo where Type=1 order by nam' +
      'e'
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
    Left = 248
    Top = 392
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
      494C010108000A00580010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
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
    Left = 656
    Top = 280
  end
  object PopupMenu1: TPopupMenu
    Left = 584
    Top = 264
    object N1: TMenuItem
      Caption = #21382#21490#26126#32454
      OnClick = N1Click
    end
  end
end
