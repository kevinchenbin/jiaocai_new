object frmcaigouquery: Tfrmcaigouquery
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #26597#21333
  ClientHeight = 442
  ClientWidth = 509
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
    Width = 509
    Height = 442
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object dtpstart: TDateTimePicker
      Left = 78
      Top = 5
      Width = 85
      Height = 21
      Date = 40362.764915000000000000
      Time = 40362.764915000000000000
      TabOrder = 0
      OnChange = dtpstartChange
    end
    object chstart: TCheckBox
      Left = 4
      Top = 9
      Width = 70
      Height = 17
      Caption = #36215#22987#26102#38388
      TabOrder = 1
    end
    object dtpend: TDateTimePicker
      Left = 251
      Top = 5
      Width = 88
      Height = 21
      Date = 40362.764915000000000000
      Time = 40362.764915000000000000
      TabOrder = 2
      OnChange = dtpendChange
    end
    object chend: TCheckBox
      Left = 178
      Top = 9
      Width = 74
      Height = 17
      Caption = #32467#26463#26102#38388
      TabOrder = 3
    end
    object chclient: TCheckBox
      Left = 4
      Top = 32
      Width = 65
      Height = 17
      Caption = #20379#24212#21830
      TabOrder = 4
    end
    object edclient: TEdit
      Left = 78
      Top = 32
      Width = 71
      Height = 21
      TabOrder = 5
      OnKeyPress = edclientKeyPress
    end
    object chcode: TCheckBox
      Left = 4
      Top = 59
      Width = 74
      Height = 17
      Caption = #21333#21495
      TabOrder = 6
    end
    object edcode: TEdit
      Left = 78
      Top = 59
      Width = 424
      Height = 21
      NumbersOnly = True
      TabOrder = 7
    end
    object DBGrid1: TDBGrid
      Left = 4
      Top = 116
      Width = 498
      Height = 320
      DataSource = ds
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      TabOrder = 8
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
          FieldName = 'clientname'
          Title.Alignment = taCenter
          Title.Caption = #20379#24212#21830#21517#31216
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'NtCode'
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 84
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
          FieldName = 'TotalAmount'
          Title.Alignment = taCenter
          Title.Caption = #25968#37327
          Width = 52
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'FixedPrice'
          Title.Alignment = taCenter
          Title.Caption = #30721#27915
          Width = 76
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'DiscountedPrice'
          Title.Alignment = taCenter
          Title.Caption = #23454#27915
          Width = 76
          Visible = True
        end>
    end
    object Button1: TButton
      Left = 333
      Top = 85
      Width = 75
      Height = 25
      Caption = #26597#35810
      TabOrder = 9
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 427
      Top = 85
      Width = 75
      Height = 25
      Caption = #36864#20986
      TabOrder = 10
      OnClick = Button2Click
    end
    object cbsupplier: TComboBox
      Left = 150
      Top = 32
      Width = 352
      Height = 21
      ItemHeight = 13
      TabOrder = 11
      OnChange = cbsupplierChange
    end
    object chuser: TCheckBox
      Left = 355
      Top = 9
      Width = 58
      Height = 17
      Caption = #25805#20316#21592
      TabOrder = 12
    end
    object cbuser: TComboBox
      Left = 413
      Top = 5
      Width = 89
      Height = 21
      ItemHeight = 13
      TabOrder = 13
    end
  end
  object fcon: TADOConnection
    Left = 192
    Top = 192
  end
  object ds: TDataSource
    DataSet = query
    Left = 336
    Top = 184
  end
  object query: TADOQuery
    Parameters = <>
    Left = 376
    Top = 288
  end
end
