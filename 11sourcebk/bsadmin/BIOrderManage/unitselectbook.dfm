object frmcomfigbook: Tfrmcomfigbook
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #30830#35748#20070#30446
  ClientHeight = 325
  ClientWidth = 586
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
  object frmselectbook: TPanel
    Left = 0
    Top = 0
    Width = 586
    Height = 325
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object DBGrid1: TDBGrid
      Left = 13
      Top = 54
      Width = 553
      Height = 218
      DataSource = ds
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'ISBN'
          Title.Alignment = taCenter
          Width = 84
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Name'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 193
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Price'
          Title.Alignment = taCenter
          Title.Caption = #23450#20215
          Width = 47
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Author'
          Title.Alignment = taCenter
          Title.Caption = #20316#32773
          Width = 63
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AbbreviatedName'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Width = 66
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Presscount'
          Title.Alignment = taCenter
          Title.Caption = #29256#27425
          Width = 49
          Visible = True
        end>
    end
    object chisbn: TCheckBox
      Left = 13
      Top = 16
      Width = 49
      Height = 17
      Caption = 'ISBN'
      TabOrder = 1
    end
    object edisbn: TEdit
      Left = 68
      Top = 14
      Width = 121
      Height = 21
      TabOrder = 2
    end
    object chname: TCheckBox
      Left = 229
      Top = 16
      Width = 49
      Height = 17
      Caption = #20070#21517
      TabOrder = 3
    end
    object edname: TEdit
      Left = 284
      Top = 14
      Width = 218
      Height = 21
      TabOrder = 4
    end
    object RzButton1: TRzButton
      Left = 517
      Top = 11
      Width = 49
      Caption = #26597#35810
      TabOrder = 5
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 389
      Top = 288
      Caption = #30830#23450
      TabOrder = 6
      OnClick = RzButton2Click
    end
    object RzButton3: TRzButton
      Left = 491
      Top = 288
      Caption = #21462#28040
      TabOrder = 7
      OnClick = RzButton3Click
    end
  end
  object ds: TDataSource
    DataSet = query
    Left = 88
    Top = 160
  end
  object query: TADOQuery
    Parameters = <>
    Left = 240
    Top = 184
  end
  object fcon: TADOConnection
    Left = 424
    Top = 96
  end
end
