object frmjichun: Tfrmjichun
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #24211#23384#32467#23384#26597#35810
  ClientHeight = 744
  ClientWidth = 1031
  Color = 16180174
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  WindowState = wsMaximized
  PixelsPerInch = 96
  TextHeight = 13
  object grpbx1: TRzGroupBox
    Left = 0
    Top = 29
    Width = 1031
    Height = 108
    Align = alTop
    Caption = #26597#35810#26465#20214
    ParentColor = True
    TabOrder = 0
    object chckbxStartTime: TRzCheckBox
      Left = 4
      Top = 21
      Width = 67
      Height = 15
      Caption = #36215#22987#26102#38388
      State = cbUnchecked
      TabOrder = 0
    end
    object dtedtStart: TRzDateTimeEdit
      Left = 77
      Top = 18
      Width = 122
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
      Left = 4
      Top = 48
      Width = 67
      Height = 15
      Caption = #32467#26463#26102#38388
      State = cbUnchecked
      TabOrder = 2
    end
    object dtedtEnd: TRzDateTimeEdit
      Left = 77
      Top = 45
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
      Left = 206
      Top = 21
      Width = 43
      Height = 15
      Caption = #20070#21517
      State = cbUnchecked
      TabOrder = 4
    end
    object chckbxISBN: TRzCheckBox
      Left = 206
      Top = 48
      Width = 43
      Height = 15
      Caption = #20070#21495
      State = cbUnchecked
      TabOrder = 5
    end
    object chckbxUserDefNum: TRzCheckBox
      Left = 4
      Top = 75
      Width = 61
      Height = 15
      Caption = #33258' '#32534' '#21495
      State = cbUnchecked
      TabOrder = 6
    end
    object chckbxPress: TRzCheckBox
      Left = 206
      Top = 75
      Width = 43
      Height = 15
      Caption = #29256#21035
      State = cbUnchecked
      TabOrder = 7
    end
    object chckbxRemarks: TRzCheckBox
      Left = 383
      Top = 74
      Width = 43
      Height = 15
      Caption = #22791#27880
      State = cbUnchecked
      TabOrder = 8
    end
    object chckbxStorage: TRzCheckBox
      Left = 734
      Top = 22
      Width = 43
      Height = 15
      Caption = #24215#21495
      State = cbUnchecked
      TabOrder = 9
    end
    object edtBookName: TRzEdit
      Left = 253
      Top = 18
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 10
      OnChange = edtBookNameChange
    end
    object edtISBN: TRzEdit
      Left = 253
      Top = 45
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      MaxLength = 13
      TabOrder = 11
      OnChange = edtISBNChange
    end
    object edtUserDefNum: TRzEdit
      Left = 77
      Top = 72
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 12
      OnChange = edtUserDefNumChange
    end
    object edtPress: TRzEdit
      Tag = 1
      Left = 253
      Top = 72
      Width = 32
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 13
      OnKeyPress = edtPressKeyPress
    end
    object edtRemarks: TRzEdit
      Left = 460
      Top = 72
      Width = 254
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 14
    end
    object chckbx1: TRzCheckBox
      Left = 381
      Top = 19
      Width = 67
      Height = 15
      Caption = #20379'  '#24212'  '#21830
      State = cbUnchecked
      TabOrder = 18
    end
    object chstaff: TCheckBox
      Left = 731
      Top = 46
      Width = 55
      Height = 17
      Caption = #25805#20316#21592
      TabOrder = 15
    end
    object cbstaff: TComboBox
      Left = 792
      Top = 46
      Width = 112
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 16
      OnChange = cbstaffChange
    end
    object edsuplier: TEdit
      Left = 461
      Top = 19
      Width = 50
      Height = 21
      ImeName = #29579#30721#20116#31508#22411#36755#20837#27861'86'#29256
      TabOrder = 17
      OnKeyPress = edsuplierKeyPress
    end
    object cbstg: TComboBox
      Left = 792
      Top = 19
      Width = 112
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 19
    end
    object cbsupplier: TComboBox
      Left = 511
      Top = 19
      Width = 203
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 20
      OnChange = cbsupplierChange
    end
    object cbpress: TComboBox
      Left = 284
      Top = 72
      Width = 91
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 21
      OnChange = cbpressChange
    end
    object ckdanhao: TRzCheckBox
      Left = 383
      Top = 48
      Width = 43
      Height = 15
      Caption = #21333#21495
      State = cbUnchecked
      TabOrder = 22
    end
    object editdanhao: TEdit
      Left = 460
      Top = 46
      Width = 254
      Height = 21
      NumbersOnly = True
      TabOrder = 23
      OnChange = editdanhaoChange
    end
  end
  object rztlbr1: TRzToolbar
    Left = 0
    Top = 0
    Width = 1031
    Height = 29
    AutoStyle = False
    ButtonWidth = 60
    ShowButtonCaptions = True
    TextOptions = ttoSelectiveTextOnRight
    BorderInner = fsNone
    BorderOuter = fsNone
    BorderSides = [sdTop]
    BorderWidth = 0
    Color = clSkyBlue
    GradientColorStyle = gcsMSOffice
    TabOrder = 1
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
  object pagecontrol: TRzPageControl
    Left = 8
    Top = 143
    Width = 1015
    Height = 602
    ActivePage = tabandan
    DragIndicatorColor = 5263440
    TabIndex = 0
    TabOrder = 2
    FixedDimension = 19
    object tabandan: TRzTabSheet
      Color = 16180174
      Caption = #25353#21333
      object dbgrid1: TDBGridEh
        Left = 17
        Top = 9
        Width = 984
        Height = 486
        DataSource = ds1
        Flat = True
        FooterColor = clWindow
        FooterFont.Charset = DEFAULT_CHARSET
        FooterFont.Color = clWindowText
        FooterFont.Height = -11
        FooterFont.Name = 'Tahoma'
        FooterFont.Style = []
        FooterRowCount = 1
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        SumList.Active = True
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        Columns = <
          item
            EditButtons = <>
            FieldName = 'danhaostr'
            Footer.Value = #21512#35745
            Footer.ValueType = fvtStaticText
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #21333#21495
            Width = 90
          end
          item
            EditButtons = <>
            FieldName = 'jzdatetime'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26085#26399
          end
          item
            EditButtons = <>
            FieldName = 'totalamount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24635#25968#37327
            Width = 80
          end
          item
            EditButtons = <>
            FieldName = 'totaldis'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24635#23454#27915
            Width = 80
          end
          item
            EditButtons = <>
            FieldName = 'totalfix'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24635#30721#27915
            Width = 80
          end
          item
            EditButtons = <>
            FieldName = 'name'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25805#20316#21592
            Width = 80
          end
          item
            EditButtons = <>
            FieldName = 'stgname'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24215#21495
            Width = 120
          end
          item
            EditButtons = <>
            FieldName = 'bk'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #22791#27880
            Width = 160
          end>
      end
    end
    object tabdetail: TRzTabSheet
      Color = 16180174
      Caption = #26126#32454
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object dbgrid2: TDBGridEh
        Left = 3
        Top = 8
        Width = 990
        Height = 481
        DataSource = ds2
        Flat = True
        FooterColor = clWindow
        FooterFont.Charset = DEFAULT_CHARSET
        FooterFont.Color = clWindowText
        FooterFont.Height = -11
        FooterFont.Name = 'Tahoma'
        FooterFont.Style = []
        FooterRowCount = 1
        Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
        SumList.Active = True
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        OnTitleClick = dbgrid2TitleClick
        Columns = <
          item
            EditButtons = <>
            FieldName = 'xuhao'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #24207#21495
            Width = 30
          end
          item
            EditButtons = <>
            FieldName = 'bkcatalogid'
            Footers = <>
            Title.Alignment = taCenter
            Visible = False
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'danhaostr'
            Footer.Value = #21512#35745
            Footer.ValueType = fvtStaticText
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #21333#21495
            Width = 65
          end
          item
            EditButtons = <>
            FieldName = 'jzdatetime'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #26085#26399
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'ISBN'
            Footers = <>
            Title.Alignment = taCenter
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'bookname'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20070#21517
            Width = 140
          end
          item
            EditButtons = <>
            FieldName = 'price'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23450#20215
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'userdefcode'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #33258#32534#30721
            Visible = False
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'amount'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25968#37327
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'Cbprice'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #25104#26412
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'tuihuochenben'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #36864#36135#25104#26412
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'shiyang'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #23454#27915
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'mayang'
            Footer.ValueType = fvtSum
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #30721#27915
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'suppliername'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20379#24212#21830
            Width = 70
          end
          item
            EditButtons = <>
            FieldName = 'author'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20316#32773
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'presscount'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #29256#27425
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'pressdate'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #20986#29256#26085#26399
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'huojiangstate'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #33719#22870#24773#20917
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'AbbreviatedName'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #29256#21035
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'bkharmnum'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #32570#37327
            Width = 60
          end
          item
            EditButtons = <>
            FieldName = 'bkdamnum'
            Footers = <>
            Title.Alignment = taCenter
            Title.Caption = #32570#37327
            Width = 60
          end>
      end
    end
  end
  object aqandan: TADOQuery
    Parameters = <>
    Left = 432
    Top = 336
  end
  object ds1: TDataSource
    DataSet = aqandan
    Left = 456
    Top = 264
  end
  object ds2: TDataSource
    DataSet = aqdetail
    Left = 296
    Top = 240
  end
  object aqdetail: TADOQuery
    Parameters = <>
    Left = 312
    Top = 328
  end
  object savedialog: TSaveDialog
    DefaultExt = 'xls'
    Filter = 'Excel '#25991#26723' (*.xls)|*.xls'
    Left = 368
    Top = 264
  end
end
