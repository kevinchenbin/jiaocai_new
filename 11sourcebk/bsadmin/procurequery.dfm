object frmprocurequery: Tfrmprocurequery
  Left = 0
  Top = 0
  Caption = #26234#33021#20837#24211#37319#36141#20449#24687#26597#35810
  ClientHeight = 685
  ClientWidth = 1014
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Visible = True
  WindowState = wsMaximized
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1014
    Height = 685
    Align = alClient
    TabOrder = 0
    object SpeedButton2: TSpeedButton
      Left = 843
      Top = 655
      Width = 150
      Height = 22
      Caption = #36716#20837#20837#24211#32534#36753
      Flat = True
      OnClick = SpeedButton2Click
    end
    object GroupBox1: TGroupBox
      Left = 15
      Top = 0
      Width = 978
      Height = 41
      TabOrder = 0
      object SpeedButton1: TSpeedButton
        Left = 920
        Top = 13
        Width = 47
        Height = 22
        Caption = #26597#35810
        Flat = True
        OnClick = SpeedButton1Click
      end
      object chprocure: TCheckBox
        Left = 10
        Top = 16
        Width = 71
        Height = 17
        Caption = #37319#36141#21333#21495
        TabOrder = 0
      end
      object edprocurecode: TEdit
        Left = 87
        Top = 14
        Width = 121
        Height = 21
        MaxLength = 13
        NumbersOnly = True
        TabOrder = 1
      end
      object chsupplier: TCheckBox
        Left = 224
        Top = 16
        Width = 65
        Height = 17
        Caption = #20379#24212#21830
        TabOrder = 2
      end
      object edquery: TEdit
        Left = 287
        Top = 14
        Width = 50
        Height = 21
        TabOrder = 3
        OnKeyPress = edqueryKeyPress
      end
      object cbsupplier: TComboBox
        Left = 336
        Top = 14
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 4
      end
      object chstart: TCheckBox
        Left = 506
        Top = 16
        Width = 73
        Height = 17
        Caption = #36215#22987#26102#38388
        TabOrder = 5
      end
      object dtstart: TDBDateTimeEditEh
        Left = 585
        Top = 14
        Width = 103
        Height = 21
        EditButtons = <>
        Kind = dtkDateEh
        TabOrder = 6
        Visible = True
      end
      object chend: TCheckBox
        Left = 712
        Top = 16
        Width = 73
        Height = 17
        Caption = #32467#26463#26102#38388
        TabOrder = 7
      end
      object dtend: TDBDateTimeEditEh
        Left = 792
        Top = 14
        Width = 103
        Height = 21
        EditButtons = <>
        Kind = dtkDateEh
        TabOrder = 8
        Visible = True
      end
    end
    object DBGridEh1: TDBGridEh
      Left = 15
      Top = 47
      Width = 320
      Height = 623
      DataSource = ds1
      Flat = False
      FooterColor = clWindow
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -11
      FooterFont.Name = 'Tahoma'
      FooterFont.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete]
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnCellClick = DBGridEh1CellClick
      Columns = <
        item
          EditButtons = <>
          FieldName = 'ProcureNtCode'
          Footers = <>
          Title.Caption = #21333#21495
          Width = 92
        end
        item
          EditButtons = <>
          FieldName = 'Name'
          Footers = <>
          Title.Caption = #20379#24212#21830
          Width = 94
        end
        item
          EditButtons = <>
          FieldName = 'HdTime'
          Footers = <>
          Title.Caption = #26102#38388
          Width = 116
        end>
    end
    object DBGrid1: TDBGrid
      Left = 341
      Top = 47
      Width = 652
      Height = 602
      DataSource = ds2
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
      PopupMenu = pqpm
      TabOrder = 2
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'ISBN'
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Name'
          Title.Caption = #20070#21517
          Width = 128
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Price'
          Title.Caption = #23450#20215
          Width = 47
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AbbreviatedName'
          Title.Caption = #20986#29256#31038
          Width = 98
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Amount'
          Title.Caption = #37319#36141#25968#37327
          Width = 59
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Discount'
          Title.Caption = #25240#25187
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'FixedPrice'
          Title.Caption = #30721#27915
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'DiscountedPrice'
          Title.Caption = #23454#27915
          Width = 70
          Visible = True
        end>
    end
  end
  object ds1: TDataSource
    DataSet = aq1
    Left = 216
    Top = 112
  end
  object ds2: TDataSource
    DataSet = aq2
    Left = 672
    Top = 264
  end
  object aq1: TADOQuery
    Parameters = <>
    Left = 200
    Top = 184
  end
  object aq2: TADOQuery
    Parameters = <>
    Left = 680
    Top = 344
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 744
    Top = 104
  end
  object pqpm: TPopupMenu
    Left = 480
    Top = 184
    object N1: TMenuItem
      Caption = #20840#36873
      OnClick = N1Click
    end
  end
end
