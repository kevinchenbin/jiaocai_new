object frmMasterset: TfrmMasterset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #24635#24215#35774#32622
  ClientHeight = 380
  ClientWidth = 318
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
  object pan1: TPanel
    Left = 0
    Top = 0
    Width = 318
    Height = 380
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object DBGridEh1: TDBGridEh
      Left = 16
      Top = 8
      Width = 289
      Height = 330
      DataSource = ds
      FixedColor = 16180174
      Flat = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      FooterColor = clWindow
      FooterFont.Charset = DEFAULT_CHARSET
      FooterFont.Color = clWindowText
      FooterFont.Height = -11
      FooterFont.Name = 'Tahoma'
      FooterFont.Style = []
      ParentFont = False
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          EditButtons = <>
          FieldName = 'Name'
          Footers = <>
          ReadOnly = True
          Title.Caption = #24215#21517
          Width = 181
        end
        item
          Checkboxes = True
          EditButtons = <>
          FieldName = 'Master'
          Footers = <>
          Title.Caption = #26159#21542#20026#24635#24215
          Width = 67
        end>
    end
    object btok: TRzButton
      Left = 133
      Top = 344
      Caption = #30830#23450
      TabOrder = 1
      OnClick = btokClick
    end
    object btconcel: TRzButton
      Left = 214
      Top = 344
      Caption = #21462#28040
      TabOrder = 2
      OnClick = btconcelClick
    end
  end
  object cn: TADOConnection
    Left = 288
    Top = 128
  end
  object ds: TDataSource
    DataSet = aq
    Left = 288
    Top = 224
  end
  object aq: TADOQuery
    AfterPost = aqAfterPost
    Parameters = <>
    Left = 272
    Top = 296
  end
  object query: TADOQuery
    Parameters = <>
    Left = 280
    Top = 64
  end
end
