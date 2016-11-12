object frmchangeselect: Tfrmchangeselect
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #26356#25442#25968#30446#36873#25321
  ClientHeight = 377
  ClientWidth = 745
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
    Width = 745
    Height = 377
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    ExplicitLeft = 56
    ExplicitTop = 32
    ExplicitWidth = 185
    ExplicitHeight = 41
    object DBGrid1: TDBGrid
      Left = 16
      Top = 16
      Width = 705
      Height = 322
      DataSource = ds
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
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
      OnDblClick = DBGrid1DblClick
      OnKeyDown = DBGrid1KeyDown
      Columns = <
        item
          Expanded = False
          FieldName = 'ISBN'
          Title.Alignment = taCenter
          Width = 89
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Name'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 199
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'UserDefCode'
          Title.Alignment = taCenter
          Title.Caption = #33258#32534#30721
          Width = 85
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Price'
          Title.Alignment = taCenter
          Title.Caption = #23450#20215
          Width = 56
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Author'
          Title.Alignment = taCenter
          Title.Caption = #20316#32773
          Width = 56
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AbbreviatedName'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Width = 91
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PressCount'
          Title.Alignment = taCenter
          Title.Caption = #29256#27425
          Width = 62
          Visible = True
        end>
    end
    object btgenhuan: TButton
      Left = 630
      Top = 344
      Width = 91
      Height = 25
      Caption = #32487#32493#26356#25442#20070#30446
      TabOrder = 1
      OnClick = btgenhuanClick
    end
  end
  object ds: TDataSource
    DataSet = query
    Left = 576
    Top = 56
  end
  object query: TADOQuery
    Parameters = <>
    Left = 600
    Top = 136
  end
end
