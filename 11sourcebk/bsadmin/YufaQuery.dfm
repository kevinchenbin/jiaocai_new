object frmYufaQuery: TfrmYufaQuery
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #39044#21457#21333#21495#26597#35810
  ClientHeight = 391
  ClientWidth = 378
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
    Width = 378
    Height = 391
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object spselectClient: TSpeedButton
      Left = 329
      Top = 43
      Width = 20
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
    object dtpstart: TDateTimePicker
      Left = 89
      Top = 13
      Width = 83
      Height = 21
      Date = 40672.505766898150000000
      Time = 40672.505766898150000000
      TabOrder = 0
    end
    object dtpend: TDateTimePicker
      Left = 266
      Top = 13
      Width = 83
      Height = 21
      Date = 40672.505766898150000000
      Time = 40672.505766898150000000
      TabOrder = 1
    end
    object chclient: TCheckBox
      Left = 18
      Top = 44
      Width = 50
      Height = 17
      Caption = #23458#25143
      TabOrder = 2
    end
    object edclient: TEdit
      Left = 74
      Top = 42
      Width = 60
      Height = 21
      TabOrder = 3
      OnKeyPress = edclientKeyPress
    end
    object edtclient: TEdit
      Left = 135
      Top = 42
      Width = 192
      Height = 21
      ReadOnly = True
      TabOrder = 4
    end
    object DBGrid1: TDBGrid
      Left = 18
      Top = 112
      Width = 331
      Height = 257
      DataSource = ds
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      TabOrder = 5
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnDblClick = DBGrid1DblClick
      Columns = <
        item
          Expanded = False
          FieldName = 'yufacode'
          Title.Caption = #39044#21457#21333#21495
          Width = 72
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'headtime'
          Title.Caption = #26085#26399
          Width = 69
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ClientName'
          Title.Caption = #23458#25143
          Width = 167
          Visible = True
        end>
    end
    object RzButton1: TRzButton
      Left = 274
      Top = 73
      Caption = #26597#35810
      TabOrder = 6
      OnClick = RzButton1Click
    end
    object chstart: TCheckBox
      Left = 18
      Top = 15
      Width = 65
      Height = 17
      Caption = #36215#22987#26102#38388
      TabOrder = 7
    end
    object chend: TCheckBox
      Left = 195
      Top = 15
      Width = 65
      Height = 17
      Caption = #32467#26463#26102#38388
      TabOrder = 8
    end
  end
  object fcon: TADOConnection
    Left = 168
    Top = 64
  end
  object ds: TDataSource
    DataSet = query
    Left = 24
    Top = 64
  end
  object query: TADOQuery
    Parameters = <>
    Left = 104
    Top = 64
  end
end
