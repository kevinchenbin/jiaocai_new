object frmpsquery: Tfrmpsquery
  Left = 0
  Top = 0
  Caption = #37197#36865#26597#21333
  ClientHeight = 438
  ClientWidth = 437
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
    Width = 437
    Height = 438
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object Label1: TLabel
      Left = 133
      Top = 62
      Width = 12
      Height = 13
      Caption = #24215
    end
    object dtpstart: TDateTimePicker
      Left = 85
      Top = 5
      Width = 116
      Height = 21
      Date = 40362.764915000000000000
      Time = 40362.764915000000000000
      TabOrder = 0
      OnChange = dtpstartChange
    end
    object chstart: TCheckBox
      Left = 12
      Top = 9
      Width = 74
      Height = 17
      Caption = #36215#22987#26102#38388
      TabOrder = 1
    end
    object dtpend: TDateTimePicker
      Left = 306
      Top = 5
      Width = 116
      Height = 21
      Date = 40362.764915000000000000
      Time = 40362.764915000000000000
      TabOrder = 2
      OnChange = dtpendChange
    end
    object chend: TCheckBox
      Left = 231
      Top = 9
      Width = 74
      Height = 17
      Caption = #32467#26463#26102#38388
      TabOrder = 3
    end
    object choutstorage: TCheckBox
      Left = 12
      Top = 34
      Width = 65
      Height = 17
      Caption = #35843#20986#24215
      TabOrder = 4
    end
    object chcode: TCheckBox
      Left = 12
      Top = 61
      Width = 67
      Height = 17
      Caption = #21333#21495
      TabOrder = 5
    end
    object edcode: TEdit
      Left = 309
      Top = 59
      Width = 113
      Height = 21
      NumbersOnly = True
      TabOrder = 6
      OnChange = edcodeChange
    end
    object DBGrid1: TDBGrid
      Left = 12
      Top = 116
      Width = 410
      Height = 317
      DataSource = ds
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      TabOrder = 7
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnDblClick = DBGrid1DblClick
      Columns = <
        item
          Expanded = False
          FieldName = 'stgnameout'
          Title.Alignment = taCenter
          Title.Caption = #35843#20986#24215
          Width = 113
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ZNDiaoNtCode'
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 81
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HdTime'
          Title.Alignment = taCenter
          Title.Caption = #26085#26399
          Width = 73
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stgnamein'
          Title.Alignment = taCenter
          Title.Caption = #35843#20837#24215
          Width = 110
          Visible = True
        end>
    end
    object Button1: TButton
      Left = 253
      Top = 86
      Width = 75
      Height = 25
      Caption = #26597#35810
      TabOrder = 8
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 347
      Top = 86
      Width = 75
      Height = 25
      Caption = #36864#20986
      TabOrder = 9
      OnClick = Button2Click
    end
    object cboutstorage: TComboBox
      Left = 85
      Top = 32
      Width = 116
      Height = 21
      ItemHeight = 0
      TabOrder = 10
      OnChange = cboutstorageChange
    end
    object chinstorage: TCheckBox
      Left = 231
      Top = 34
      Width = 65
      Height = 17
      Caption = #35843#20837#24215
      TabOrder = 11
    end
    object cbinstorage: TComboBox
      Left = 306
      Top = 32
      Width = 116
      Height = 21
      ItemHeight = 0
      TabOrder = 12
      OnChange = cbinstorageChange
    end
    object dtedtDate: TRzDateTimeEdit
      Left = 148
      Top = 59
      Width = 115
      Height = 21
      EditType = etDate
      TabOrder = 13
      OnChange = dtedtDateChange
    end
    object spedtID: TRzSpinEdit
      Left = 262
      Top = 59
      Width = 47
      Height = 21
      AllowKeyEdit = True
      Max = 99999.000000000000000000
      TabOrder = 14
      OnChange = dtedtDateChange
    end
    object spstorage: TRzSpinEdit
      Left = 85
      Top = 59
      Width = 45
      Height = 21
      AllowKeyEdit = True
      Max = 99999.000000000000000000
      TabOrder = 15
      OnChange = dtedtDateChange
    end
  end
  object ds: TDataSource
    DataSet = query
    Left = 408
    Top = 208
  end
  object query: TADOQuery
    Parameters = <>
    Left = 304
    Top = 288
  end
  object fcon: TADOConnection
    Left = 464
    Top = 128
  end
end
