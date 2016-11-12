inherited frmQryNoteCode1: TfrmQryNoteCode1
  Caption = #26597#35810#21333#21495
  ClientHeight = 421
  ClientWidth = 489
  OnShow = FormShow
  ExplicitWidth = 495
  ExplicitHeight = 449
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel2: TPanel
    Width = 489
    Height = 465
    Color = 16180174
    ParentBackground = False
    ExplicitWidth = 489
    ExplicitHeight = 465
    DesignSize = (
      489
      465)
    object spselectClient: TSpeedButton [0]
      Left = 439
      Top = 72
      Width = 26
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
    end
    inherited btnOk: TRzButton
      Left = 150
      Top = 440
      ExplicitLeft = 150
      ExplicitTop = 440
    end
    inherited btnCancel: TRzButton
      Left = 272
      Top = 440
      ExplicitLeft = 272
      ExplicitTop = 440
    end
    object dtedtDate: TRzDateTimeEdit
      Left = 83
      Top = 42
      Width = 120
      Height = 21
      EditType = etDate
      TabOrder = 2
      OnChange = dtedtDateChange
    end
    object spedtID: TRzSpinEdit
      Left = 200
      Top = 42
      Width = 51
      Height = 21
      AllowKeyEdit = True
      Max = 99999.000000000000000000
      TabOrder = 3
      OnChange = spedtIDChange
    end
    object edtCode: TRzEdit
      Left = 247
      Top = 42
      Width = 192
      Height = 21
      ReadOnly = True
      ReadOnlyColor = clWindow
      TabOrder = 4
      OnChange = edtCodeChange
    end
    object edtclient: TEdit
      Left = 137
      Top = 71
      Width = 302
      Height = 21
      TabOrder = 5
      OnChange = edtclientChange
    end
    object cbselect: TRzComboBox
      Left = 137
      Top = 71
      Width = 303
      Height = 21
      DisabledColor = clWhite
      ItemHeight = 13
      TabOrder = 6
      OnChange = cbselectChange
    end
    object edtQryVendor: TRzEdit
      Left = 83
      Top = 71
      Width = 54
      Height = 21
      DisabledColor = clWhite
      TabOrder = 7
      OnKeyPress = edtQryVendorKeyPress
    end
    object ch1: TCheckBox
      Left = 16
      Top = 72
      Width = 59
      Height = 19
      Caption = #20379#24212#21830
      TabOrder = 8
    end
    object chstart: TCheckBox
      Left = 16
      Top = 15
      Width = 73
      Height = 17
      Caption = #36215#22987#26102#38388
      TabOrder = 9
    end
    object dtpstart: TDateTimePicker
      Left = 83
      Top = 12
      Width = 106
      Height = 21
      Date = 40432.409794375000000000
      Time = 40432.409794375000000000
      TabOrder = 10
      OnChange = dtpstartChange
    end
    object chend: TCheckBox
      Left = 255
      Top = 15
      Width = 73
      Height = 17
      Caption = #32467#26463#26102#38388
      TabOrder = 11
    end
    object dtpend: TDateTimePicker
      Left = 333
      Top = 12
      Width = 106
      Height = 21
      Date = 40432.409794375000000000
      Time = 40432.409794375000000000
      TabOrder = 12
      OnChange = dtpendChange
    end
    object chcode: TCheckBox
      Left = 16
      Top = 44
      Width = 49
      Height = 17
      Caption = #21333#21495
      TabOrder = 13
    end
    object DBGrid1: TDBGrid
      Left = 8
      Top = 127
      Width = 465
      Height = 289
      DataSource = ds
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      TabOrder = 14
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnDblClick = DBGrid1DblClick
      OnKeyPress = DBGrid1KeyPress
      Columns = <
        item
          Expanded = False
          FieldName = 'custmername'
          Title.Alignment = taCenter
          Title.Caption = #20379#24212#21830#21517#31216
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'MoneyCode'
          Title.Alignment = taCenter
          Title.Caption = #32467#31639#21333#21495
          Width = 84
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'clearingtype'
          Title.Alignment = taCenter
          Title.Caption = #32467#31639#31867#22411
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'clearingstyle'
          Title.Alignment = taCenter
          Title.Caption = #32467#31639#26041#24335
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'date'
          Title.Alignment = taCenter
          Title.Caption = #32467#31639#26085#26399
          Width = 67
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'state'
          Title.Alignment = taCenter
          Title.Caption = #32467#31639#29366#24577
          Width = 59
          Visible = True
        end>
    end
    object RzButton1: TRzButton
      Left = 312
      Top = 96
      Caption = #26597#35810
      TabOrder = 15
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 398
      Top = 96
      Caption = #21462#28040
      TabOrder = 16
      OnClick = RzButton2Click
    end
  end
  object ds: TDataSource
    DataSet = query
    Left = 264
    Top = 232
  end
  object query: TADOQuery
    Parameters = <>
    Left = 280
    Top = 168
  end
  object fcon: TADOConnection
    Left = 352
    Top = 168
  end
end
