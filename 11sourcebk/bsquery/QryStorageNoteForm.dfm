inherited frmQryStorageNote: TfrmQryStorageNote
  Anchors = [akLeft, akTop, akRight, akBottom]
  Caption = #20837#24211#26597#35810
  ClientHeight = 734
  ClientWidth = 1028
  Color = 16180174
  OnKeyDown = FormKeyDown
  ExplicitWidth = 1044
  ExplicitHeight = 772
  DesignSize = (
    1028
    734)
  PixelsPerInch = 96
  TextHeight = 13
  object rztlbr1: TRzToolbar [0]
    Left = 0
    Top = 0
    Width = 1028
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
    Width = 1020
    Height = 156
    Anchors = [akLeft, akTop, akRight]
    Caption = #26597#35810#26465#20214
    ParentColor = True
    TabOrder = 1
    object lbl1: TLabel
      Left = 681
      Top = 75
      Width = 16
      Height = 13
      Caption = '>='
    end
    object lbl2: TLabel
      Left = 742
      Top = 75
      Width = 16
      Height = 13
      Caption = '<='
    end
    object lbl3: TLabel
      Left = 297
      Top = 75
      Width = 16
      Height = 13
      Caption = '>='
    end
    object lbl4: TLabel
      Left = 357
      Top = 75
      Width = 16
      Height = 13
      Caption = '<='
    end
    object Label36: TLabel
      Left = 870
      Top = 75
      Width = 16
      Height = 13
      Caption = '>='
    end
    object Label37: TLabel
      Left = 933
      Top = 75
      Width = 16
      Height = 13
      Caption = '<='
    end
    object chckbxStartTime: TRzCheckBox
      Left = 16
      Top = 21
      Width = 67
      Height = 15
      Caption = #36215#22987#26102#38388
      State = cbUnchecked
      TabOrder = 0
    end
    object dtedtStart: TRzDateTimeEdit
      Left = 89
      Top = 18
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
      Left = 224
      Top = 20
      Width = 67
      Height = 15
      Caption = #32467#26463#26102#38388
      State = cbUnchecked
      TabOrder = 2
    end
    object dtedtEnd: TRzDateTimeEdit
      Left = 297
      Top = 18
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
      Left = 16
      Top = 48
      Width = 67
      Height = 15
      Caption = #20070'        '#21517
      State = cbUnchecked
      TabOrder = 4
    end
    object chckbxISBN: TRzCheckBox
      Left = 16
      Top = 75
      Width = 67
      Height = 15
      Caption = #20070'        '#21495
      State = cbUnchecked
      TabOrder = 5
    end
    object chckbxCustomer: TRzCheckBox
      Left = 16
      Top = 102
      Width = 67
      Height = 15
      Caption = #20379'  '#24212'  '#21830
      State = cbUnchecked
      TabOrder = 6
    end
    object chckbxBkstack: TRzCheckBox
      Left = 624
      Top = 47
      Width = 43
      Height = 15
      Caption = #24211#20301
      State = cbUnchecked
      TabOrder = 7
      OnClick = chckbxBkstackClick
    end
    object chckbxUserDefNum: TRzCheckBox
      Left = 224
      Top = 47
      Width = 61
      Height = 15
      Caption = #33258' '#32534' '#21495
      State = cbUnchecked
      TabOrder = 8
    end
    object chckbxPrice: TRzCheckBox
      Left = 224
      Top = 74
      Width = 61
      Height = 15
      Caption = #23450'      '#20215
      State = cbUnchecked
      TabOrder = 9
    end
    object chckbxAuthor: TRzCheckBox
      Left = 224
      Top = 101
      Width = 61
      Height = 15
      Caption = #20316'      '#32773
      State = cbUnchecked
      TabOrder = 10
    end
    object chckbxAmount: TRzCheckBox
      Left = 624
      Top = 74
      Width = 43
      Height = 15
      Caption = #25968#37327
      State = cbUnchecked
      TabOrder = 11
    end
    object chckbxPress: TRzCheckBox
      Left = 434
      Top = 48
      Width = 43
      Height = 15
      Caption = #29256#21035
      State = cbUnchecked
      TabOrder = 12
    end
    object chckbxType: TRzCheckBox
      Left = 434
      Top = 76
      Width = 43
      Height = 15
      Caption = #31867#21035
      State = cbUnchecked
      TabOrder = 13
    end
    object chckbxRemarks: TRzCheckBox
      Left = 821
      Top = 102
      Width = 43
      Height = 15
      Caption = #22791#27880
      State = cbUnchecked
      TabOrder = 14
    end
    object chckbxStorage: TRzCheckBox
      Left = 821
      Top = 47
      Width = 43
      Height = 15
      Caption = #24215#21495
      State = cbUnchecked
      TabOrder = 15
    end
    object edtBookName: TRzEdit
      Left = 89
      Top = 45
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 16
      OnChange = edtBookNameChange
    end
    object edtISBN: TRzEdit
      Left = 89
      Top = 72
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      MaxLength = 13
      TabOrder = 17
      OnChange = edtISBNChange
    end
    object edtUserDefNum: TRzEdit
      Left = 297
      Top = 45
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 18
      OnChange = edtUserDefNumChange
    end
    object edtAuthor: TRzEdit
      Left = 297
      Top = 99
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 19
      OnChange = edtAuthorChange
    end
    object edtPress: TRzEdit
      Tag = 1
      Left = 490
      Top = 46
      Width = 37
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 20
      OnKeyPress = edtPressKeyPress
    end
    object edtRemarks: TRzEdit
      Left = 870
      Top = 99
      Width = 125
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 21
      OnChange = edtRemarksChange
    end
    object edtCustomer: TRzEdit
      Tag = 2
      Left = 89
      Top = 99
      Width = 37
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 22
      OnKeyPress = edtPressKeyPress
    end
    object numedtMinPrice: TRzNumericEdit
      Left = 313
      Top = 72
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
      Left = 696
      Top = 72
      Width = 45
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 24
      OnChange = numedtMinAmountChange
      AllowBlank = True
      DisplayFormat = '###,##0;-###,##0'
    end
    object numedtMaxPrice: TRzNumericEdit
      Left = 373
      Top = 72
      Width = 45
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 25
      OnChange = numedtMaxPriceChange
      AllowBlank = True
      IntegersOnly = False
      DisplayFormat = '###,##0.00'
    end
    object numedtMaxAmount: TRzNumericEdit
      Left = 761
      Top = 72
      Width = 47
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 26
      OnChange = numedtMaxAmountChange
      AllowBlank = True
      DisplayFormat = '###,##0;-###,##0'
    end
    object dblkpcbbBookType: TRzDBLookupComboBox
      Left = 490
      Top = 73
      Width = 121
      Height = 21
      DataField = 'BktypeID'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcBookType
      TabOrder = 27
      OnClick = dblkpcbbBookTypeClick
    end
    object dblkpcbbStorage: TRzDBLookupComboBox
      Left = 870
      Top = 45
      Width = 125
      Height = 21
      DataField = 'StorageID'
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcStorage
      TabOrder = 28
      OnClick = dblkpcbbStorageClick
    end
    object dblkpcbbBookstack: TRzDBLookupComboBox
      Left = 681
      Top = 45
      Width = 127
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcBookstack
      TabOrder = 29
      OnClick = dblkpcbbBookstackClick
    end
    object cboutstorage: TRzCheckBox
      Left = 490
      Top = 20
      Width = 43
      Height = 15
      Caption = #36864#36135
      State = cbUnchecked
      TabOrder = 30
    end
    object cbreturnstorage: TCheckBox
      Left = 544
      Top = 20
      Width = 67
      Height = 17
      Caption = #36820#36135#20837#24211
      TabOrder = 31
    end
    object cbinstorage: TRzCheckBox
      Left = 434
      Top = 20
      Width = 43
      Height = 15
      Caption = #20837#24211
      State = cbUnchecked
      TabOrder = 32
    end
    object cblost: TCheckBox
      Left = 624
      Top = 20
      Width = 51
      Height = 17
      Caption = #25439#21333
      TabOrder = 33
    end
    object cbdamage: TCheckBox
      Left = 678
      Top = 20
      Width = 50
      Height = 17
      Caption = #32570#21333
      TabOrder = 34
    end
    object chdiscount: TCheckBox
      Left = 821
      Top = 74
      Width = 43
      Height = 17
      Caption = #25240#25187
      TabOrder = 35
    end
    object edmaxdiscount: TEdit
      Left = 955
      Top = 72
      Width = 40
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 36
      OnChange = edmaxdiscountChange
    end
    object chstaff: TCheckBox
      Left = 434
      Top = 102
      Width = 55
      Height = 17
      Caption = #25805#20316#21592
      TabOrder = 37
    end
    object cbstaff: TComboBox
      Left = 490
      Top = 99
      Width = 87
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 38
      OnClick = cbstaffClick
    end
    object chnocheck: TCheckBox
      Left = 733
      Top = 20
      Width = 55
      Height = 17
      Caption = #26410#32467#36807
      TabOrder = 39
    end
    object chcheckpart: TCheckBox
      Left = 802
      Top = 20
      Width = 67
      Height = 17
      Caption = #24050#32467#37096#20998
      TabOrder = 40
    end
    object chchecked: TCheckBox
      Left = 879
      Top = 20
      Width = 78
      Height = 17
      Caption = #24050#32467#20840#37096
      TabOrder = 41
    end
    object edmindiscount: TEdit
      Left = 886
      Top = 72
      Width = 41
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 42
      OnChange = edmindiscountChange
    end
    object chjytype: TCheckBox
      Left = 589
      Top = 102
      Width = 68
      Height = 17
      Caption = #32463#33829#31867#21035
      TabOrder = 43
    end
    object cbjytype: TComboBox
      Left = 659
      Top = 99
      Width = 82
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 44
      OnClick = cbjytypeClick
      Items.Strings = (
        #22270#20070
        #26399#21002
        #25991#20855)
    end
    object dblkpcbbPress: TRzDBLookupComboBox
      Left = 527
      Top = 46
      Width = 84
      Height = 21
      DataField = 'PressID'
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      KeyField = 'ID'
      ListField = 'AbbreviatedName'
      ListSource = dsrcPress
      TabOrder = 45
      OnClick = dblkpcbbPressClick
    end
    object chzengshu: TCheckBox
      Left = 955
      Top = 20
      Width = 44
      Height = 17
      Caption = #26679#20070
      TabOrder = 46
    end
    object chandan: TCheckBox
      Left = 747
      Top = 102
      Width = 68
      Height = 17
      Caption = #26126#32454#25353#21333
      Checked = True
      State = cbChecked
      TabOrder = 47
      Visible = False
    end
    object dblkpcbbCustomer: TRzDBLookupComboBox
      Left = 124
      Top = 99
      Width = 86
      Height = 21
      KeyField = 'ID'
      ListField = 'Name'
      ListSource = dsrcCustomer
      TabOrder = 48
      OnClick = dblkpcbbCustomerClick
    end
    object cbkaipiao: TComboBox
      Left = 870
      Top = 121
      Width = 125
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 49
      Text = #24050#24320#31080
      OnClick = cbstaffClick
      Items.Strings = (
        #24050#24320#31080
        #26410#24320#31080)
    end
    object ckkaipiao: TCheckBox
      Left = 821
      Top = 123
      Width = 43
      Height = 17
      Caption = #24320#31080
      TabOrder = 50
    end
  end
  object pgcntrlResult: TRzPageControl [2]
    Left = 0
    Top = 175
    Width = 1022
    Height = 560
    ActivePage = tbshtByNtHeader
    Anchors = [akLeft, akTop, akRight, akBottom]
    DragIndicatorColor = 5263440
    TabIndex = 0
    TabOrder = 2
    TabStyle = tsBackSlant
    OnChange = pgcntrlResultChange
    FixedDimension = 19
    object tbshtByNtHeader: TRzTabSheet
      Tag = 1
      Color = 16180174
      Caption = #25353#21333
      object dbgrdByNtHeader: TDBGridEh
        Left = 0
        Top = 0
        Width = 1018
        Height = 537
        Align = alClient
        Ctl3D = True
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
        ParentCtl3D = False
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
            FieldName = 'CodeStr'
            Footers = <>
            Title.Caption = #21333#21495
            Width = 93
          end
          item
            EditButtons = <>
            FieldName = 'Code'
            Footers = <>
            Title.Caption = #21333#21495
            Visible = False
            Width = 89
          end
          item
            EditButtons = <>
            FieldName = 'CustomerName'
            Footers = <>
            Title.Caption = #20379#24212#21830
            Width = 178
          end
          item
            EditButtons = <>
            FieldName = 'Date'
            Footers = <>
            Title.Caption = #26085#26399
            Width = 108
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30721#27915
            Width = 71
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
            Title.Caption = 'B'#25968#37327
            Width = 59
          end
          item
            EditButtons = <>
            FieldName = 'camount'
            Footer.FieldName = 'camount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = 'C'#24211#25968#37327
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'totalamount'
            Footer.FieldName = 'totalamount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24635#25968#37327
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'checked'
            Footer.FieldName = 'checked'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #24050#32467
            Width = 68
          end
          item
            EditButtons = <>
            FieldName = 'nochecked'
            Footer.FieldName = 'nochecked'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #26410#32467
            Width = 67
          end
          item
            EditButtons = <>
            FieldName = 'harmnum'
            Footer.FieldName = 'harmnum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25439#37327
            Width = 42
          end
          item
            EditButtons = <>
            FieldName = 'damagenum'
            Footer.FieldName = 'damagenum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #32570#37327
            Width = 43
          end
          item
            EditButtons = <>
            FieldName = 'cwstate'
            Footers = <>
            Title.Caption = #29366#24577
            Width = 56
          end
          item
            EditButtons = <>
            FieldName = 'fapiao'
            Footers = <>
            Title.Caption = #21457#31080
            Width = 54
          end
          item
            EditButtons = <>
            FieldName = 'zengshu'
            Footers = <>
            Title.Caption = #26679#20070
            Width = 37
          end
          item
            EditButtons = <>
            FieldName = 'StorageNoteHeaderRemarks'
            Footers = <>
            Title.Caption = #22791#27880
            Width = 72
          end
          item
            EditButtons = <>
            FieldName = 'StgName'
            Footers = <>
            Title.Caption = #24215#21517
            Width = 93
          end
          item
            EditButtons = <>
            FieldName = 'Operatorname'
            Footers = <>
            Title.Caption = #25805#20316#21592
            Width = 71
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
        Width = 1018
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
            Title.Alignment = taCenter
            Title.Caption = #24207#21495
            Width = 36
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
            Width = 187
          end
          item
            EditButtons = <>
            FieldName = 'UserDefCode'
            Footers = <>
            Title.Caption = #33258#32534#30721
            Width = 70
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
            Width = 46
          end
          item
            EditButtons = <>
            FieldName = 'BktypeName'
            Footers = <>
            Title.Caption = #31867#21035
            Width = 80
          end
          item
            EditButtons = <>
            FieldName = 'PressName'
            Footers = <>
            Title.Caption = #29256#21035
            Width = 85
          end
          item
            EditButtons = <>
            FieldName = 'Code'
            Footers = <>
            Title.Caption = #21333#21495
            Visible = False
            Width = 88
          end
          item
            EditButtons = <>
            FieldName = 'stkamount'
            Footers = <>
            Title.Caption = #24211#23384#25968#37327
            Width = 51
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25968#37327
            Width = 53
          end
          item
            EditButtons = <>
            FieldName = 'camount'
            Footer.FieldName = 'camount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = 'C'#25968#37327
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'totalamount'
            Footer.FieldName = 'totalamount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #24635#25968#37327
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'Discount'
            Footers = <>
            Title.Caption = #25240#25187
            Width = 55
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
            FieldName = 'CodeStr'
            Footers = <>
            Title.Caption = #21333#21495
            Width = 83
          end
          item
            EditButtons = <>
            FieldName = 'zengshu'
            Footers = <>
            Title.Caption = #36192#20070
            Width = 40
          end
          item
            EditButtons = <>
            FieldName = 'Date'
            Footers = <>
            Title.Caption = #21333#25454#26085#26399
            Width = 71
          end
          item
            EditButtons = <>
            FieldName = 'CustomerName'
            Footers = <>
            Title.Caption = #20379#24212#21830
            Width = 95
          end
          item
            EditButtons = <>
            FieldName = 'PressDate'
            Footers = <>
            Title.Caption = #20986#29256#26085#26399
            Width = 59
          end
          item
            EditButtons = <>
            FieldName = 'harmnum'
            Footer.FieldName = 'harmnum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25439#37327
            Width = 39
          end
          item
            EditButtons = <>
            FieldName = 'damagenum'
            Footer.FieldName = 'damagenum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #32570#37327
            Width = 41
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Caption = #24215#21517
            Width = 90
          end>
      end
    end
    object tbshtByCustomer: TRzTabSheet
      Tag = 3
      Color = 16180174
      Caption = #20379#24212#21830
      object dbgrdByCustomer: TDBGridEh
        Left = 0
        Top = 0
        Width = 1018
        Height = 537
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
            Width = 28
          end
          item
            EditButtons = <>
            FieldName = 'CustomerName'
            Footers = <>
            Title.Caption = #20379#24212#21830#21517#31216
            Width = 114
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30721#27915
            Width = 70
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
            Width = 68
          end
          item
            EditButtons = <>
            FieldName = 'harmnum'
            Footer.FieldName = 'harmnum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25439#37327
            Width = 62
          end
          item
            EditButtons = <>
            FieldName = 'damagenum'
            Footer.FieldName = 'damagenum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #32570#37327
            Width = 62
          end
          item
            EditButtons = <>
            FieldName = 'checked'
            Footer.FieldName = 'checked'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #24050#32467
            Width = 75
          end
          item
            EditButtons = <>
            FieldName = 'nochecked'
            Footer.FieldName = 'nochecked'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #26410#32467
            Width = 78
          end
          item
            EditButtons = <>
            FieldName = 'totalyue'
            Footer.FieldName = 'totalyue'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #20313#39069
            Width = 68
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Caption = #24215#21517
            Width = 106
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
        Width = 1018
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
        FooterFont.Color = clNavy
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
            Width = 26
          end
          item
            EditButtons = <>
            FieldName = 'BktypeName'
            Footers = <>
            Title.Caption = #31867#21035
            Width = 160
          end
          item
            EditButtons = <>
            FieldName = 'FixedPrice'
            Footer.FieldName = 'FixedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #30721#27915
            Width = 76
          end
          item
            EditButtons = <>
            FieldName = 'DiscountedPrice'
            Footer.FieldName = 'DiscountedPrice'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #23454#27915
            Width = 68
          end
          item
            EditButtons = <>
            FieldName = 'Amount'
            Footer.FieldName = 'Amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25968#37327
            Width = 67
          end
          item
            EditButtons = <>
            FieldName = 'harmnum'
            Footer.FieldName = 'harmnum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25439#37327
            Width = 67
          end
          item
            EditButtons = <>
            FieldName = 'damagenum'
            Footer.FieldName = 'damagenum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #32570#37327
            Width = 67
          end
          item
            EditButtons = <>
            FieldName = 'StorageName'
            Footers = <>
            Title.Caption = #24215#21517
            Width = 165
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
        Width = 1018
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
            Width = 32
          end
          item
            EditButtons = <>
            FieldName = 'PressName'
            Footers = <>
            Title.Caption = #29256#21035
            Width = 185
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
            Width = 75
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
            FieldName = 'harmnum'
            Footer.FieldName = 'harmnum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #25439#37327
            Width = 61
          end
          item
            EditButtons = <>
            FieldName = 'damagenum'
            Footer.FieldName = 'damagenum'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Caption = #32570#37327
            Width = 60
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
    Left = 240
    Top = 328
  end
  object dsrcByCustomer: TDataSource
    DataSet = dsetByCustomer
    Left = 192
    Top = 280
  end
  object dsetByBktype: TADODataSet
    Parameters = <>
    Left = 440
    Top = 288
  end
  object dsrcByBktype: TDataSource
    DataSet = dsetByBktype
    Left = 400
    Top = 344
  end
  object dsetByPress: TADODataSet
    Parameters = <>
    Left = 304
    Top = 272
  end
  object dsrcByPress: TDataSource
    DataSet = dsetByPress
    Left = 320
    Top = 448
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
        Attributes = [paNullable]
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@nocheck'
        Attributes = [paNullable]
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@checkpart'
        Attributes = [paNullable]
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@checked'
        Attributes = [paNullable]
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
        Value = Null
      end
      item
        Name = '@MinDamage'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@career'
        DataType = ftInteger
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
    Left = 112
    Top = 408
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
    Left = 288
    Top = 384
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
      494C010108000A00AC0010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
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
    Left = 336
    Top = 320
  end
  object dsrcSupplier: TDataSource
    DataSet = dsetSupplier
    Left = 264
    Top = 568
  end
  object dsetSupplier: TADODataSet
    CommandText = 
      'select ID, Name from CUST_CustomerInfo where  Type in(1) order b' +
      'y name'
    Parameters = <>
    Left = 408
    Top = 496
  end
  object savedlg: TSaveDialog
    Left = 736
    Top = 248
  end
  object PopupMenu1: TPopupMenu
    Left = 544
    Top = 224
    object N1: TMenuItem
      Caption = #21382#21490#26126#32454
      OnClick = N1Click
    end
  end
end