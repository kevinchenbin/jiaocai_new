object frmpanbook: Tfrmpanbook
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #20070#30446#30424#28857
  ClientHeight = 324
  ClientWidth = 574
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
    Width = 574
    Height = 324
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    ExplicitLeft = -8
    ExplicitWidth = 472
    ExplicitHeight = 243
    object DBGrid1: TDBGrid
      Left = 6
      Top = 8
      Width = 555
      Height = 305
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
      OnCellClick = DBGrid1CellClick
      OnKeyDown = DBGrid1KeyDown
      Columns = <
        item
          Expanded = False
          FieldName = 'ISBN'
          Title.Alignment = taCenter
          Width = 77
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Name'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 153
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Price'
          Title.Alignment = taCenter
          Title.Caption = #23450#20215
          Width = 48
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Author'
          Title.Alignment = taCenter
          Title.Caption = #20316#32773
          Width = 55
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'UserDefCode'
          Title.Alignment = taCenter
          Title.Caption = #33258#32534#30721
          Width = 59
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AbbreviatedName'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Width = 56
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PressCount'
          Title.Alignment = taCenter
          Title.Caption = #29256#27425
          Width = 53
          Visible = True
        end>
    end
  end
  object ds: TDataSource
    DataSet = query
    Left = 320
    Top = 104
  end
  object query: TADOQuery
    Parameters = <>
    Left = 224
    Top = 120
  end
end
