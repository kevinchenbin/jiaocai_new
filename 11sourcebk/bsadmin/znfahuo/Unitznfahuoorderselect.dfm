object frmzinengfahuo: Tfrmzinengfahuo
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #26234#33021#21457#36135
  ClientHeight = 674
  ClientWidth = 941
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 941
    Height = 674
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 6
      Top = 11
      Width = 923
      Height = 118
      Caption = #26597#35810#26465#20214
      TabOrder = 0
      object spselectClient: TSpeedButton
        Left = 475
        Top = 50
        Width = 23
        Height = 20
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
      object Label1: TLabel
        Left = 746
        Top = 52
        Width = 156
        Height = 26
        Caption = #35828#26126#65306#34013#33394#20026#37096#20998#28385#36275#21457#36135#13#12288#12288#12288#32418#33394#20026#20840#37096#19981#28385#36275#21457#36135
      end
      object chordercode: TCheckBox
        Left = 19
        Top = 24
        Width = 62
        Height = 17
        Caption = #35746#21333#21495
        TabOrder = 0
      end
      object chclient: TCheckBox
        Left = 19
        Top = 51
        Width = 49
        Height = 17
        Caption = #23458#25143
        TabOrder = 1
      end
      object edclient: TEdit
        Left = 79
        Top = 49
        Width = 56
        Height = 21
        TabOrder = 2
        OnKeyPress = edclientKeyPress
      end
      object edtclient: TEdit
        Left = 134
        Top = 49
        Width = 342
        Height = 21
        ReadOnly = True
        TabOrder = 3
      end
      object RzButton1: TRzButton
        Left = 609
        Top = 14
        Width = 104
        Height = 100
        Caption = #26597#35810
        TabOrder = 4
        OnClick = RzButton1Click
      end
      object chstart: TCheckBox
        Left = 19
        Top = 76
        Width = 97
        Height = 17
        Caption = #35746#21333#36215#22987#26102#38388
        TabOrder = 5
      end
      object dtpstart: TDateTimePicker
        Left = 122
        Top = 73
        Width = 102
        Height = 21
        Date = 40306.536538437500000000
        Time = 40306.536538437500000000
        TabOrder = 6
      end
      object chend: TCheckBox
        Left = 277
        Top = 76
        Width = 94
        Height = 17
        Caption = #35746#21333#32467#26463#26102#38388
        TabOrder = 7
      end
      object dtpend: TDateTimePicker
        Left = 377
        Top = 73
        Width = 99
        Height = 21
        Date = 40306.536538437500000000
        Time = 40306.536538437500000000
        TabOrder = 8
      end
      object edordercode: TEdit
        Left = 79
        Top = 22
        Width = 397
        Height = 21
        MaxLength = 15
        NumbersOnly = True
        TabOrder = 9
      end
      object rg: TRadioGroup
        Left = 512
        Top = 10
        Width = 91
        Height = 105
        ItemIndex = 0
        Items.Strings = (
          #28385#36275#21457#36135
          #37096#20998#28385#36275
          #20840#37096#19981#28385#36275
          #20840#37096)
        TabOrder = 10
      end
    end
    object DBGrid1: TDBGrid
      Left = 6
      Top = 464
      Width = 923
      Height = 201
      DataSource = DataSource1
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
      ParentFont = False
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'isbn'
          Title.Alignment = taCenter
          Title.Caption = 'ISBN'
          Width = 58
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'name'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 96
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'price'
          Title.Alignment = taCenter
          Title.Caption = #23450#20215
          Width = 40
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AbbreviatedName'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'amount'
          Title.Alignment = taCenter
          Title.Caption = #25910#35746#25968#37327
          Width = 55
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'kc'
          Title.Alignment = taCenter
          Title.Caption = #24211#23384#25968#37327
          Width = 52
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'kykc'
          Title.Alignment = taCenter
          Title.Caption = #21487#29992#24211#23384
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'locknum'
          Title.Alignment = taCenter
          Title.Caption = #38145#23450#25968#37327
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'UnsendAmount'
          Title.Alignment = taCenter
          Title.Caption = #26410#21457#36135#25968#37327
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ylockkc'
          Title.Alignment = taCenter
          Title.Caption = #24050#38145#23450#24211#23384
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'backInfo'
          Title.Alignment = taCenter
          Title.Caption = #23458#25143#22238#21578
          Width = 180
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Orderdetailbk'
          Title.Alignment = taCenter
          Title.Caption = #22238#21578
          Width = 180
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'corderid'
          Visible = False
        end>
    end
    object dbgrid: TRzDBGrid
      Left = 6
      Top = 144
      Width = 923
      Height = 314
      DataSource = ds
      DefaultDrawing = True
      FixedColor = 16180174
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
      PopupMenu = PopupMenu1
      TabOrder = 2
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnCellClick = dbgridCellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'OrderNtCode'
          Title.Alignment = taCenter
          Title.Caption = #35746#21333#21495
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'OrderUser'
          Title.Alignment = taCenter
          Title.Caption = #23458#25143
          Width = 80
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'hdtime'
          Title.Alignment = taCenter
          Title.Caption = #26102#38388
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'TotalAmount'
          Title.Alignment = taCenter
          Title.Caption = #25968#37327
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'FixedPrice'
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'DiscountedPrice'
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stateaa'
          Title.Alignment = taCenter
          Title.Caption = #29366#24577
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AddCosts'
          Title.Alignment = taCenter
          Title.Caption = #36816#36153
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'OrderAddress'
          Title.Alignment = taCenter
          Title.Caption = #21457#36135#22320#22336
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Remarks'
          Title.Alignment = taCenter
          Title.Caption = #22791#27880
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ID'
          Visible = False
        end>
    end
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 464
    Top = 256
  end
  object ds: TDataSource
    DataSet = aq
    Left = 256
    Top = 304
  end
  object DataSource1: TDataSource
    DataSet = adoquery
    Left = 512
    Top = 592
  end
  object adoquery: TADOQuery
    Parameters = <>
    Left = 320
    Top = 568
  end
  object PopupMenu1: TPopupMenu
    Left = 368
    Top = 312
    object N1: TMenuItem
      Caption = #20840#36873'(&S)'
      OnClick = N1Click
    end
    object H1: TMenuItem
      Caption = #29983#25104#21457#36135#21333'(&H)'
      OnClick = H1Click
    end
  end
  object sp: TADOStoredProc
    Parameters = <>
    Left = 312
    Top = 240
  end
end
