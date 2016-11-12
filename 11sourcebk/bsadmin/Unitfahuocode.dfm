object frmfahuocode: Tfrmfahuocode
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #36873#25321#36861#21152#21457#36135#21333
  ClientHeight = 265
  ClientWidth = 501
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
    Width = 501
    Height = 265
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object DBGrid1: TDBGrid
      Left = 8
      Top = 8
      Width = 481
      Height = 217
      DataSource = ds
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'clientname'
          Title.Alignment = taCenter
          Title.Caption = #23458#25143#21517#31216
          Width = 149
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'WsaleNtCodeStr'
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 87
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HdTime'
          Title.Alignment = taCenter
          Title.Caption = #26085#26399
          Width = 78
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Remarks'
          Title.Alignment = taCenter
          Title.Caption = #22791#27880
          Width = 136
          Visible = True
        end>
    end
    object RzButton1: TRzButton
      Left = 280
      Top = 231
      Caption = #30830#23450
      TabOrder = 1
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 375
      Top = 231
      Caption = #26032#21333
      TabOrder = 2
      OnClick = RzButton2Click
    end
  end
  object ds: TDataSource
    Left = 272
    Top = 96
  end
  object aquery: TADOQuery
    Parameters = <>
    Left = 288
    Top = 40
  end
end
