object frmbookhistory: Tfrmbookhistory
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #21382#21490#26126#32454
  ClientHeight = 474
  ClientWidth = 883
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 883
    Height = 474
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    Ctl3D = False
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 4
      Top = 2
      Width = 870
      Height = 79
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 0
      object Label1: TLabel
        Left = 518
        Top = 53
        Width = 60
        Height = 13
        Caption = #24403#21069#24215#24211#23384
      end
      object chstart: TCheckBox
        Left = 14
        Top = 15
        Width = 79
        Height = 17
        Caption = #36215#22987#26102#38388
        TabOrder = 0
      end
      object dtpstart: TDateTimePicker
        Left = 99
        Top = 11
        Width = 110
        Height = 21
        Date = 40359.672460208330000000
        Time = 40359.672460208330000000
        TabOrder = 1
      end
      object chend: TCheckBox
        Left = 300
        Top = 15
        Width = 79
        Height = 17
        Caption = #32467#26463#26102#38388
        TabOrder = 2
      end
      object dtpend: TDateTimePicker
        Left = 385
        Top = 11
        Width = 110
        Height = 21
        Date = 40359.672460208330000000
        Time = 40359.672460208330000000
        TabOrder = 3
      end
      object rg: TRadioGroup
        Left = 14
        Top = 38
        Width = 481
        Height = 34
        Columns = 6
        ItemIndex = 0
        Items.Strings = (
          #35746#21333
          #37319#36141
          #20837#24211
          #21457#36135
          #38646#21806
          #37197#36865)
        TabOrder = 4
        OnClick = rgClick
      end
      object edamount: TEdit
        Left = 584
        Top = 51
        Width = 89
        Height = 21
        Enabled = False
        TabOrder = 5
      end
    end
    object dg1: TDBGridEh
      Left = 4
      Top = 82
      Width = 870
      Height = 389
      Ctl3D = True
      DataSource = ds1
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
      PopupMenu = pm
      SumList.Active = True
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnTitleClick = dg1TitleClick
      Columns = <
        item
          EditButtons = <>
          FieldName = 'Name'
          Footer.Alignment = taCenter
          Footer.Value = #21512#35745
          Footer.ValueType = fvtStaticText
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #23458#25143#21517#31216
          Width = 221
        end
        item
          EditButtons = <>
          FieldName = 'Amount'
          Footer.FieldName = 'Amount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #35746#36135#25968#37327
          Width = 45
        end
        item
          EditButtons = <>
          FieldName = 'Discount'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #25240#25187
          Width = 51
        end
        item
          EditButtons = <>
          FieldName = 'FixedPrice'
          Footer.FieldName = 'FixedPrice'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Width = 61
        end
        item
          EditButtons = <>
          FieldName = 'DiscountedPrice'
          Footer.FieldName = 'DiscountedPrice'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Width = 67
        end
        item
          EditButtons = <>
          FieldName = 'SendAmount'
          Footer.FieldName = 'SendAmount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #24050#21457#25968#37327
          Width = 60
        end
        item
          EditButtons = <>
          FieldName = 'UnsendAmount'
          Footer.FieldName = 'UnsendAmount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #26410#21457#25968#37327
          Width = 61
        end
        item
          EditButtons = <>
          FieldName = 'localnum'
          Footer.FieldName = 'localnum'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Caption = #38145#23450#25968#37327
          Width = 60
        end
        item
          EditButtons = <>
          FieldName = 'class'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #29677#32423
          Width = 56
        end
        item
          EditButtons = <>
          FieldName = 'Code'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 84
        end
        item
          EditButtons = <>
          FieldName = 'HdTime'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #26085#26399
          Width = 63
        end
        item
          EditButtons = <>
          FieldName = 'opname'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #25805#20316#21592
          Width = 55
        end>
    end
    object dbgridcg: TDBGridEh
      Left = 4
      Top = 80
      Width = 813
      Height = 389
      Ctl3D = True
      DataSource = ds3
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
      PopupMenu = pm
      SumList.Active = True
      TabOrder = 2
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnTitleClick = dbgridcgTitleClick
      Columns = <
        item
          EditButtons = <>
          FieldName = 'Name'
          Footer.Alignment = taCenter
          Footer.Value = #21512#35745
          Footer.ValueType = fvtStaticText
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #20379#24212#21830#21517#31216
          Width = 221
        end
        item
          EditButtons = <>
          FieldName = 'Amount'
          Footer.FieldName = 'Amount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #37319#36141#25968#37327
          Width = 45
        end
        item
          EditButtons = <>
          FieldName = 'Discount'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #25240#25187
          Width = 51
        end
        item
          EditButtons = <>
          FieldName = 'FixedPrice'
          Footer.FieldName = 'FixedPrice'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Width = 61
        end
        item
          EditButtons = <>
          FieldName = 'DiscountedPrice'
          Footer.FieldName = 'DiscountedPrice'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Width = 67
        end
        item
          EditButtons = <>
          FieldName = 'SendAmount'
          Footer.FieldName = 'SendAmount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #24050#21040#25968#37327
          Width = 60
        end
        item
          EditButtons = <>
          FieldName = 'UnsendAmount'
          Footer.FieldName = 'UnsendAmount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #26410#21040#25968#37327
          Width = 61
        end
        item
          EditButtons = <>
          FieldName = 'class'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #29677#32423
          Visible = False
          Width = 56
        end
        item
          EditButtons = <>
          FieldName = 'Code'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 84
        end
        item
          EditButtons = <>
          FieldName = 'HdTime'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #26085#26399
          Width = 63
        end
        item
          EditButtons = <>
          FieldName = 'opname'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #25805#20316#21592
          Width = 55
        end>
    end
    object dbgridrk: TDBGridEh
      Left = 4
      Top = 80
      Width = 813
      Height = 389
      Ctl3D = True
      DataSource = ds4
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
      TabOrder = 3
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnTitleClick = dbgridrkTitleClick
      Columns = <
        item
          EditButtons = <>
          FieldName = 'Name'
          Footer.Alignment = taCenter
          Footer.Value = #21512#35745
          Footer.ValueType = fvtStaticText
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #20379#24212#21830#21517#31216
          Width = 221
        end
        item
          EditButtons = <>
          FieldName = 'Amount'
          Footer.FieldName = 'Amount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = 'B'#20837#24211#25968#37327
          Width = 70
        end
        item
          EditButtons = <>
          FieldName = 'camount'
          Footer.FieldName = 'camount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Caption = 'C'#20837#24211#25968#37327
          Width = 70
        end
        item
          EditButtons = <>
          FieldName = 'totalamount'
          Footer.FieldName = 'totalamount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Caption = #24635#25968#37327
          Width = 68
        end
        item
          EditButtons = <>
          FieldName = 'Discount'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #25240#25187
          Width = 51
        end
        item
          EditButtons = <>
          FieldName = 'totalfixedprice'
          Footer.FieldName = 'totalfixedprice'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Width = 61
        end
        item
          EditButtons = <>
          FieldName = 'totaldiscountprice'
          Footer.FieldName = 'totaldiscountprice'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Width = 67
        end
        item
          EditButtons = <>
          FieldName = 'Code'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 84
        end
        item
          EditButtons = <>
          FieldName = 'HdTime'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #26085#26399
          Width = 63
        end
        item
          EditButtons = <>
          FieldName = 'opname'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #25805#20316#21592
          Width = 55
        end>
    end
    object dbgridfh: TDBGridEh
      Left = 4
      Top = 80
      Width = 685
      Height = 389
      Ctl3D = True
      DataSource = ds5
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
      TabOrder = 4
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnTitleClick = dbgridfhTitleClick
      Columns = <
        item
          EditButtons = <>
          FieldName = 'Name'
          Footer.Alignment = taCenter
          Footer.Value = #21512#35745
          Footer.ValueType = fvtStaticText
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #23458#25143#21517#31216
          Width = 221
        end
        item
          EditButtons = <>
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #35843#20837#24215
          Visible = False
        end
        item
          EditButtons = <>
          FieldName = 'Amount'
          Footer.FieldName = 'Amount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #21457#36135#25968#37327
          Width = 45
        end
        item
          EditButtons = <>
          FieldName = 'Discount'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #25240#25187
          Width = 51
        end
        item
          EditButtons = <>
          FieldName = 'FixedPrice'
          Footer.FieldName = 'FixedPrice'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Width = 61
        end
        item
          EditButtons = <>
          FieldName = 'DiscountedPrice'
          Footer.FieldName = 'DiscountedPrice'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Width = 67
        end
        item
          EditButtons = <>
          FieldName = 'SendAmount'
          Footer.FieldName = 'SendAmount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Visible = False
          Width = 60
        end
        item
          EditButtons = <>
          FieldName = 'UnsendAmount'
          Footer.FieldName = 'UnsendAmount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Visible = False
          Width = 61
        end
        item
          EditButtons = <>
          FieldName = 'class'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #29677#32423
          Visible = False
          Width = 56
        end
        item
          EditButtons = <>
          FieldName = 'Code'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 84
        end
        item
          EditButtons = <>
          FieldName = 'HdTime'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #26085#26399
          Width = 63
        end
        item
          EditButtons = <>
          FieldName = 'opname'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #25805#20316#21592
          Width = 55
        end>
    end
    object dbgridls: TDBGridEh
      Left = 4
      Top = 80
      Width = 685
      Height = 389
      Ctl3D = True
      DataSource = ds6
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
      TabOrder = 5
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnTitleClick = dbgridlsTitleClick
      Columns = <
        item
          EditButtons = <>
          FieldName = 'Name'
          Footer.Alignment = taCenter
          Footer.Value = #21512#35745
          Footer.ValueType = fvtStaticText
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #20250#21592#21517#31216
          Width = 221
        end
        item
          EditButtons = <>
          FieldName = 'Amount'
          Footer.FieldName = 'Amount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #38646#21806#25968#37327
          Width = 45
        end
        item
          EditButtons = <>
          FieldName = 'Discount'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #25240#25187
          Width = 51
        end
        item
          EditButtons = <>
          FieldName = 'FixedPrice'
          Footer.FieldName = 'FixedPrice'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Width = 61
        end
        item
          EditButtons = <>
          FieldName = 'DiscountedPrice'
          Footer.FieldName = 'DiscountedPrice'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Width = 67
        end
        item
          EditButtons = <>
          FieldName = 'SendAmount'
          Footer.FieldName = 'SendAmount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Visible = False
          Width = 60
        end
        item
          EditButtons = <>
          FieldName = 'UnsendAmount'
          Footer.FieldName = 'UnsendAmount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Visible = False
          Width = 61
        end
        item
          EditButtons = <>
          FieldName = 'class'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #29677#32423
          Visible = False
          Width = 56
        end
        item
          EditButtons = <>
          FieldName = 'Code'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 84
        end
        item
          EditButtons = <>
          FieldName = 'HdTime'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #26085#26399
          Width = 63
        end
        item
          EditButtons = <>
          FieldName = 'opname'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #25805#20316#21592
          Width = 55
        end>
    end
    object dbgridps: TDBGridEh
      Left = 4
      Top = 80
      Width = 773
      Height = 389
      Ctl3D = True
      DataSource = ds7
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
      TabOrder = 6
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnTitleClick = dbgridpsTitleClick
      Columns = <
        item
          EditButtons = <>
          FieldName = 'Name'
          Footer.Alignment = taCenter
          Footer.Value = #21512#35745
          Footer.ValueType = fvtStaticText
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #35843#20986#24215
          Width = 221
        end
        item
          EditButtons = <>
          FieldName = 'outname'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #35843#20837#24215
          Width = 80
        end
        item
          EditButtons = <>
          FieldName = 'Amount'
          Footer.FieldName = 'Amount'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #37197#36865#25968#37327
          Width = 60
        end
        item
          EditButtons = <>
          FieldName = 'Discount'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #25240#25187
          Width = 51
        end
        item
          EditButtons = <>
          FieldName = 'FixedPrice'
          Footer.FieldName = 'FixedPrice'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Width = 61
        end
        item
          EditButtons = <>
          FieldName = 'DiscountedPrice'
          Footer.FieldName = 'DiscountedPrice'
          Footer.ValueType = fvtSum
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Width = 67
        end
        item
          EditButtons = <>
          FieldName = 'Code'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 84
        end
        item
          EditButtons = <>
          FieldName = 'HdTime'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #26085#26399
          Width = 63
        end
        item
          EditButtons = <>
          FieldName = 'opname'
          Footers = <>
          Title.Alignment = taCenter
          Title.Caption = #25805#20316#21592
          Width = 55
        end>
    end
  end
  object pm: TPopupMenu
    Left = 16
    Top = 136
    object N1: TMenuItem
      Caption = #26356#25913#35746#21333#24050#21457#25968#37327
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object N3: TMenuItem
      Caption = #26356#25913#37319#36141#21040#36135#25968#37327
      OnClick = N3Click
    end
  end
  object fcon: TADOConnection
    Left = 520
    Top = 280
  end
  object ds1: TDataSource
    DataSet = aq1
    Left = 168
    Top = 216
  end
  object aq1: TADOQuery
    Parameters = <>
    Left = 120
    Top = 208
  end
  object ds2: TDataSource
    DataSet = aq2
    Left = 368
    Top = 208
  end
  object aq2: TADOQuery
    Parameters = <>
    Left = 728
    Top = 344
  end
  object ImageList1: TImageList
    Left = 760
    Top = 184
    Bitmap = {
      494C010108000A00500010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
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
      9900999999000000000000000000000000000000000000000000000000000000
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
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000008FFF8FFFFFFFFFFF07FF07FFFFDFFFDF
      83FF83FFFFCFFFCF81FF81FFE007E007C0FFC0FFFFCFFFCFE003E003FFDFFFDF
      F001F001FFFFFFFFF800F80001800180F800F80001807D80F800F80001807D80
      F800F80001807D80F800F80001807D80F800F80001806180F800F80003816381
      FC01FC0107836783FE03FE030F870F87FDFFFDFFFFFFFFFFE0FFE8FFFFFFFFFF
      801FA05F80038003001F803F80038003001F001F80038003000F000F80038003
      000F000F80038003000F000FFFFFFFFF00010001BFFBBFFB01010001FFFFFFFF
      01010001BFFBBFFB000F000FFFFFFFFF008F000FBFFBBFFB00AF002FFFFFFFFF
      803F803FAAABAAABE1FFE1FFFFFFFFFF00000000000000000000000000000000
      000000000000}
  end
  object savedlg: TSaveDialog
    Left = 704
    Top = 216
  end
  object PopupMenu1: TPopupMenu
    Left = 480
    Top = 208
  end
  object aq6: TADOQuery
    Parameters = <>
    Left = 264
    Top = 264
  end
  object aq5: TADOQuery
    Parameters = <>
    Left = 216
    Top = 264
  end
  object aq3: TADOQuery
    Parameters = <>
    Left = 88
    Top = 256
  end
  object aq4: TADOQuery
    Parameters = <>
    Left = 168
    Top = 272
  end
  object ADOQuery5: TADOQuery
    Parameters = <>
    Left = 400
    Top = 264
  end
  object DataSource1: TDataSource
    DataSet = aq2
    Left = 368
    Top = 208
  end
  object ds6: TDataSource
    DataSet = aq6
    Left = 264
    Top = 320
  end
  object ds5: TDataSource
    DataSet = aq5
    Left = 216
    Top = 320
  end
  object ds4: TDataSource
    DataSet = aq4
    Left = 160
    Top = 320
  end
  object ds3: TDataSource
    DataSet = aq3
    Left = 88
    Top = 304
  end
  object aq7: TADOQuery
    Parameters = <>
    Left = 336
    Top = 264
  end
  object ds7: TDataSource
    DataSet = aq7
    Left = 328
    Top = 320
  end
end
