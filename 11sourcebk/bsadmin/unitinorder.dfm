object frminorder: Tfrminorder
  Left = 0
  Top = 0
  Caption = #35746#21333#31579#36873
  ClientHeight = 573
  ClientWidth = 743
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
    Width = 743
    Height = 573
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 6
      Top = 11
      Width = 723
      Height = 110
      Caption = #26597#35810#26465#20214
      TabOrder = 0
      object spselectClient: TSpeedButton
        Left = 465
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
        Width = 192
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
        Width = 329
        Height = 21
        ReadOnly = True
        TabOrder = 4
        OnChange = edtclientChange
      end
      object RzButton1: TRzButton
        Left = 616
        Top = 80
        Caption = #26597#35810
        TabOrder = 5
        OnClick = RzButton1Click
      end
      object chstart: TCheckBox
        Left = 19
        Top = 79
        Width = 97
        Height = 17
        Caption = #35746#21333#36215#22987#26102#38388
        TabOrder = 6
      end
      object dtpstart: TDateTimePicker
        Left = 122
        Top = 77
        Width = 102
        Height = 21
        Date = 40306.536538437500000000
        Time = 40306.536538437500000000
        TabOrder = 7
        OnChange = dtpstartChange
      end
      object chend: TCheckBox
        Left = 264
        Top = 80
        Width = 94
        Height = 17
        Caption = #35746#21333#32467#26463#26102#38388
        TabOrder = 8
      end
      object dtpend: TDateTimePicker
        Left = 364
        Top = 77
        Width = 99
        Height = 21
        Date = 40306.536538437500000000
        Time = 40306.536538437500000000
        TabOrder = 9
        OnChange = dtpendChange
      end
      object dtedtDate: TRzDateTimeEdit
        Left = 79
        Top = 22
        Width = 145
        Height = 21
        EditType = etDate
        TabOrder = 10
        OnChange = dtedtDateChange
      end
      object spedtID: TRzSpinEdit
        Left = 222
        Top = 22
        Width = 51
        Height = 21
        AllowKeyEdit = True
        Max = 99999.000000000000000000
        TabOrder = 11
        OnChange = spedtIDChange
      end
    end
    object DBGrid1: TDBGrid
      Left = 6
      Top = 127
      Width = 723
      Height = 410
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
          FieldName = 'OrderNtCode'
          Title.Alignment = taCenter
          Title.Caption = #35746#21333#21495
          Width = 83
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ClientName'
          Title.Alignment = taCenter
          Title.Caption = #24215#21517
          Width = 118
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
          Width = 44
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'author'
          Title.Alignment = taCenter
          Title.Caption = #20316#32773
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AbbreviatedName'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Width = 41
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'presscount'
          Title.Alignment = taCenter
          Title.Caption = #29256#27425
          Width = 44
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'amount'
          Title.Alignment = taCenter
          Title.Caption = #25968#37327
          Width = 47
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'discount'
          Title.Alignment = taCenter
          Title.Caption = #25240#25187
          Width = 48
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'UnsendAmount'
          Title.Alignment = taCenter
          Title.Caption = #26410#21457#25968#37327
          Width = 53
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'usableamount'
          Title.Alignment = taCenter
          Title.Caption = #21487#29992#24211#23384#25968
          Width = 59
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Remarks'
          Title.Alignment = taCenter
          Title.Caption = #22791#27880
          Width = 204
          Visible = True
        end>
    end
    object RzButton3: TRzButton
      Left = 622
      Top = 543
      Width = 107
      Caption = #28155#21152#21040#19968#33324#37319#36141#21333
      TabOrder = 2
      OnClick = RzButton3Click
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
    Left = 352
    Top = 280
    object N1: TMenuItem
      Caption = #20840#36873
      OnClick = N1Click
    end
  end
end
