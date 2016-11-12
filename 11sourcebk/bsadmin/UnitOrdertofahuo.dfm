object frmOrdertoFahuo: TfrmOrdertoFahuo
  Left = 0
  Top = 0
  Caption = #35746#21333#31579#36873
  ClientHeight = 573
  ClientWidth = 758
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 758
    Height = 573
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    ExplicitLeft = 88
    ExplicitTop = 16
    object GroupBox1: TGroupBox
      Left = 6
      Top = 11
      Width = 747
      Height = 134
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
      object chordercode: TCheckBox
        Left = 19
        Top = 24
        Width = 62
        Height = 17
        Caption = #35746#21333#21495
        TabOrder = 0
      end
      object edordercode: TEdit
        Left = 271
        Top = 22
        Width = 205
        Height = 21
        MaxLength = 15
        NumbersOnly = True
        TabOrder = 1
        OnChange = edordercodeChange
      end
      object chclient: TCheckBox
        Left = 19
        Top = 51
        Width = 49
        Height = 17
        Caption = #23458#25143
        TabOrder = 2
      end
      object edclient: TEdit
        Left = 79
        Top = 49
        Width = 56
        Height = 21
        TabOrder = 3
        OnKeyPress = edclientKeyPress
      end
      object edtclient: TEdit
        Left = 134
        Top = 49
        Width = 342
        Height = 21
        ReadOnly = True
        TabOrder = 4
        OnChange = edtclientChange
      end
      object RzButton1: TRzButton
        Left = 638
        Top = 101
        Caption = #26597#35810
        TabOrder = 5
        OnClick = RzButton1Click
      end
      object chxiaoqu: TCheckBox
        Left = 19
        Top = 76
        Width = 49
        Height = 17
        Caption = #26657#21306
        TabOrder = 6
      end
      object cbxiaoqu: TComboBox
        Left = 79
        Top = 74
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 7
        OnChange = cbxiaoquChange
      end
      object chxueyuan: TCheckBox
        Left = 277
        Top = 76
        Width = 49
        Height = 17
        Caption = #23398#38498
        TabOrder = 8
      end
      object cbxueyuan: TComboBox
        Left = 331
        Top = 74
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 9
        OnChange = cbxueyuanChange
      end
      object chclass: TCheckBox
        Left = 522
        Top = 76
        Width = 49
        Height = 17
        Caption = #29677#32423
        TabOrder = 10
      end
      object cbclass: TComboBox
        Left = 568
        Top = 74
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 11
        OnChange = cbclassChange
      end
      object chstart: TCheckBox
        Left = 19
        Top = 103
        Width = 97
        Height = 17
        Caption = #35746#21333#36215#22987#26102#38388
        TabOrder = 12
      end
      object dtpstart: TDateTimePicker
        Left = 122
        Top = 100
        Width = 102
        Height = 21
        Date = 40306.536538437500000000
        Time = 40306.536538437500000000
        TabOrder = 13
        OnChange = dtpstartChange
      end
      object chend: TCheckBox
        Left = 277
        Top = 103
        Width = 94
        Height = 17
        Caption = #35746#21333#32467#26463#26102#38388
        TabOrder = 14
      end
      object dtpend: TDateTimePicker
        Left = 377
        Top = 100
        Width = 99
        Height = 21
        Date = 40306.536538437500000000
        Time = 40306.536538437500000000
        TabOrder = 15
        OnChange = dtpendChange
      end
      object dtedtDate: TRzDateTimeEdit
        Left = 79
        Top = 22
        Width = 145
        Height = 21
        EditType = etDate
        TabOrder = 16
        OnChange = dtedtDateChange
      end
      object spedtID: TRzSpinEdit
        Left = 222
        Top = 22
        Width = 51
        Height = 21
        AllowKeyEdit = True
        Max = 99999.000000000000000000
        TabOrder = 17
        OnChange = spedtIDChange
      end
    end
    object DBGrid1: TDBGrid
      Left = 6
      Top = 151
      Width = 747
      Height = 386
      DataSource = ds
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
      ParentFont = False
      PopupMenu = pm
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnTitleClick = DBGrid1TitleClick
      Columns = <
        item
          Expanded = False
          FieldName = 'ClientName'
          Title.Alignment = taCenter
          Title.Caption = #23458#25143
          Width = 141
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HdTime'
          Title.Alignment = taCenter
          Title.Caption = #35746#21333#26085#26399
          Width = 59
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
          FieldName = 'stkamount'
          Title.Alignment = taCenter
          Title.Caption = #24211#23384#25968#37327
          Width = 52
          Visible = True
        end
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
          FieldName = 'AbbreviatedName'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Width = 60
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
          FieldName = 'class'
          Title.Alignment = taCenter
          Title.Caption = #29677#32423
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'xueyuan'
          Title.Alignment = taCenter
          Title.Caption = #23398#38498
          Width = 59
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'incode'
          Title.Alignment = taCenter
          Title.Caption = #20869#37096#35782#21035#30721
          Width = 75
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Remarks'
          Title.Alignment = taCenter
          Title.Caption = #22791#27880
          Width = 204
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'xiaoqu'
          Title.Alignment = taCenter
          Title.Caption = #26657#21306
          Width = 58
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'OrderNtCode'
          Title.Alignment = taCenter
          Title.Caption = #35746#21333#21495
          Width = 100
          Visible = True
        end>
    end
    object RzButton3: TRzButton
      Left = 646
      Top = 543
      Width = 107
      Caption = #30830#23450#21457#36135#35746#21333
      TabOrder = 2
      OnClick = RzButton3Click
    end
    object chall: TCheckBox
      Left = 528
      Top = 114
      Width = 109
      Height = 17
      Caption = #21482#26597#35810#26377#24211#23384#30340
      TabOrder = 3
    end
    object RzButton2: TRzButton
      Left = 510
      Top = 543
      Width = 107
      Caption = #28155#21152#21040#39044#21457#21333
      TabOrder = 4
      OnClick = RzButton2Click
    end
  end
  object ds: TDataSource
    DataSet = query
    Left = 664
    Top = 264
  end
  object query: TADOQuery
    Parameters = <>
    Left = 704
    Top = 256
  end
  object con: TADOConnection
    Left = 600
    Top = 256
  end
  object ds2: TDataSource
    DataSet = query2
    Left = 496
    Top = 400
  end
  object query2: TADOQuery
    Parameters = <>
    Left = 576
    Top = 400
  end
  object pm: TPopupMenu
    Left = 384
    Top = 232
    object N1: TMenuItem
      Caption = #20840#36873
      OnClick = N1Click
    end
  end
end
