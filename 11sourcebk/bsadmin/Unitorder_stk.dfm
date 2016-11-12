object frmorder_stk: Tfrmorder_stk
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #35746#21333#24211#23384#21305#37197
  ClientHeight = 291
  ClientWidth = 657
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 657
    Height = 291
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object Label1: TLabel
      Left = 10
      Top = 16
      Width = 23
      Height = 13
      Caption = 'ISBN'
    end
    object Label2: TLabel
      Left = 164
      Top = 16
      Width = 24
      Height = 13
      Caption = #20070#21517
    end
    object lable3: TLabel
      Left = 525
      Top = 16
      Width = 48
      Height = 13
      Caption = #25910#35746#25968#37327
    end
    object Label3: TLabel
      Left = 416
      Top = 16
      Width = 24
      Height = 13
      Caption = #20316#32773
    end
    object edisbn: TEdit
      Left = 37
      Top = 13
      Width = 116
      Height = 21
      TabOrder = 0
    end
    object edname: TEdit
      Left = 191
      Top = 13
      Width = 213
      Height = 21
      TabOrder = 1
    end
    object edamount: TEdit
      Left = 576
      Top = 13
      Width = 71
      Height = 21
      TabOrder = 2
    end
    object DBGrid1: TDBGrid
      Left = 8
      Top = 40
      Width = 639
      Height = 241
      DataSource = ds
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      TabOrder = 3
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnDblClick = DBGrid1DblClick
      Columns = <
        item
          Expanded = False
          FieldName = 'ISBN'
          Title.Alignment = taCenter
          Width = 93
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Name'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 234
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'price'
          Title.Alignment = taCenter
          Title.Caption = #23450#20215
          Width = 48
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'author'
          Title.Alignment = taCenter
          Title.Caption = #20316#32773
          Width = 49
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AbbreviatedName'
          Title.Alignment = taCenter
          Title.Caption = #29256#21035
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PressCount'
          Title.Alignment = taCenter
          Title.Caption = #29256#27425
          Width = 43
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'amount'
          Title.Alignment = taCenter
          Title.Caption = #24211#23384
          Width = 53
          Visible = True
        end>
    end
    object edauthor: TEdit
      Left = 443
      Top = 13
      Width = 71
      Height = 21
      TabOrder = 4
    end
  end
  object ds: TDataSource
    Left = 472
    Top = 120
  end
  object query: TADOQuery
    Parameters = <>
    Left = 424
    Top = 80
  end
end
