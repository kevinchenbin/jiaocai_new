object frmcorderfind: Tfrmcorderfind
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'C'#32593#35746#21333#26597#35810
  ClientHeight = 474
  ClientWidth = 637
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 637
    Height = 474
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object dtpstart: TDateTimePicker
      Left = 76
      Top = 7
      Width = 137
      Height = 21
      Date = 40362.764915000000000000
      Time = 40362.764915000000000000
      TabOrder = 0
    end
    object chstart: TCheckBox
      Left = 5
      Top = 11
      Width = 69
      Height = 17
      Caption = #36215#22987#26102#38388
      TabOrder = 8
    end
    object dtpend: TDateTimePicker
      Left = 295
      Top = 7
      Width = 105
      Height = 21
      Date = 40362.764915000000000000
      Time = 40362.764915000000000000
      TabOrder = 1
    end
    object chend: TCheckBox
      Left = 219
      Top = 11
      Width = 74
      Height = 17
      Caption = #32467#26463#26102#38388
      TabOrder = 9
    end
    object chclient: TCheckBox
      Left = 5
      Top = 34
      Width = 65
      Height = 17
      Caption = #23458#25143
      TabOrder = 10
    end
    object edtclient: TEdit
      Left = 76
      Top = 34
      Width = 137
      Height = 21
      TabOrder = 3
      OnChange = edtclientChange
    end
    object chcode: TCheckBox
      Left = 219
      Top = 34
      Width = 74
      Height = 17
      Caption = #21333#21495
      TabOrder = 11
    end
    object edcode: TEdit
      Left = 295
      Top = 34
      Width = 105
      Height = 21
      TabOrder = 4
      OnChange = edcodeChange
    end
    object DBGrid1: TDBGrid
      Left = 5
      Top = 115
      Width = 610
      Height = 318
      DataSource = ds
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      TabOrder = 12
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnDblClick = DBGrid1DblClick
      Columns = <
        item
          Expanded = False
          FieldName = 'OrderUser'
          Title.Alignment = taCenter
          Title.Caption = #23458#25143#21517#31216
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'OrderNtCode'
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 89
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
          FieldName = 'HdTime'
          Title.Alignment = taCenter
          Title.Caption = #26085#26399
          Width = 100
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
      Left = 445
      Top = 84
      Width = 75
      Height = 25
      Caption = #26597#35810
      TabOrder = 13
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 526
      Top = 84
      Width = 75
      Height = 25
      Caption = #36864#20986
      TabOrder = 14
      OnClick = Button2Click
    end
    object chinorder: TCheckBox
      Left = 5
      Top = 61
      Width = 65
      Height = 17
      Caption = #29366#24577
      TabOrder = 15
    end
    object cbzt: TComboBox
      Left = 76
      Top = 61
      Width = 137
      Height = 21
      ItemHeight = 13
      ItemIndex = 1
      TabOrder = 6
      Text = #24050#20184#27454
      Items.Strings = (
        #31561#24453#20184#27454
        #24050#20184#27454
        #37197#36135#20013
        #24050#20986#24211
        #24050#21462#28040
        #36135#21040#20184#27454)
    end
    object shouhuo: TCheckBox
      Left = 410
      Top = 11
      Width = 74
      Height = 17
      Caption = #25910#36135#22320#22336
      TabOrder = 16
    end
    object editaddress: TEdit
      Left = 490
      Top = 9
      Width = 125
      Height = 21
      TabOrder = 2
      OnChange = editaddressChange
    end
    object tel: TCheckBox
      Left = 410
      Top = 34
      Width = 85
      Height = 17
      Caption = #25910#36135#20154#30005#35805
      TabOrder = 17
    end
    object edittel: TEdit
      Left = 490
      Top = 36
      Width = 125
      Height = 21
      NumbersOnly = True
      TabOrder = 5
      OnChange = edittelChange
    end
    object danhao: TCheckBox
      Left = 219
      Top = 61
      Width = 70
      Height = 17
      Caption = #24555#36882#21333#21495
      TabOrder = 18
    end
    object Edit3: TEdit
      Left = 295
      Top = 61
      Width = 105
      Height = 21
      NumbersOnly = True
      TabOrder = 7
      OnChange = Edit3Change
    end
  end
  object aqfind: TADOQuery
    Parameters = <>
    Left = 488
    Top = 232
  end
  object ds: TDataSource
    DataSet = aqfind
    Left = 424
    Top = 240
  end
end
