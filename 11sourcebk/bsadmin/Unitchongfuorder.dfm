object frmchongfuorder: Tfrmchongfuorder
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #35746#21333#37325#22797#35746#36135#35760#24405
  ClientHeight = 334
  ClientWidth = 827
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 827
    Height = 334
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object DBGrid1: TDBGrid
      Left = 16
      Top = 16
      Width = 785
      Height = 273
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
      Columns = <
        item
          Expanded = False
          FieldName = 'clientname'
          Title.Caption = #23458#25143
          Width = 156
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'OrderNtCode'
          Title.Caption = #35746#21333#21495
          Width = 96
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HdTime'
          Title.Caption = #26085#26399
          Width = 67
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ISBN'
          Width = 72
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Name'
          Title.Caption = #20070#21517
          Width = 163
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Amount'
          Title.Caption = #35746#36135#25968#37327
          Width = 54
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'SendAmount'
          Title.Caption = #24050#21457#25968#37327
          Width = 53
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'UnsendAmount'
          Title.Caption = #26410#21457#25968#37327
          Width = 55
          Visible = True
        end>
    end
    object quit: TRzButton
      Left = 726
      Top = 295
      Caption = #36864#20986'(&Q)'
      TabOrder = 1
      OnClick = quitClick
    end
    object RzButton1: TRzButton
      Left = 582
      Top = 295
      Width = 107
      Caption = #32487#32493#25910#35746#27492#20070'(&C)'
      TabOrder = 2
      OnClick = RzButton1Click
    end
  end
  object ds: TDataSource
    Left = 408
    Top = 152
  end
  object query: TADOQuery
    Parameters = <>
    Left = 640
    Top = 136
  end
end
