object frmkucunpandian: Tfrmkucunpandian
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #23454#24211#30424#28857
  ClientHeight = 243
  ClientWidth = 264
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
    Width = 264
    Height = 243
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    ExplicitLeft = 144
    ExplicitTop = 48
    ExplicitWidth = 185
    ExplicitHeight = 41
    object DBGrid1: TDBGrid
      Left = 3
      Top = 16
      Width = 257
      Height = 217
      DataSource = ds
      FixedColor = 16180174
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnDblClick = DBGrid1DblClick
      OnKeyPress = DBGrid1KeyPress
      Columns = <
        item
          Expanded = False
          FieldName = 'checkstocknum'
          Title.Alignment = taCenter
          Title.Caption = #30424#28857#21333#21495
          Width = 138
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stackname'
          Title.Alignment = taCenter
          Title.Caption = #24211#20301
          Width = 98
          Visible = True
        end>
    end
  end
  object ds: TDataSource
    DataSet = query
    Left = 248
    Top = 80
  end
  object query: TADOQuery
    Parameters = <>
    Left = 328
    Top = 144
  end
end
