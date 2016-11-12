object frmclientyouxian: Tfrmclientyouxian
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #23458#25143#20248#20808#32423
  ClientHeight = 440
  ClientWidth = 304
  Color = clInactiveCaptionText
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
  object RzDBGrid1: TRzDBGrid
    Left = 8
    Top = 8
    Width = 265
    Height = 417
    DataSource = ds
    DefaultDrawing = True
    FixedColor = clInactiveCaptionText
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'name'
        Title.Caption = #23458#25143#21517#31216
        Width = 113
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'jibie'
        PickList.Strings = (
          #19968#32423
          #20108#32423
          #19977#32423)
        Title.Caption = #20248#20808#32423
        Width = 80
        Visible = True
      end>
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 144
    Top = 208
  end
  object ds: TDataSource
    DataSet = aq
    Left = 176
    Top = 120
  end
end
