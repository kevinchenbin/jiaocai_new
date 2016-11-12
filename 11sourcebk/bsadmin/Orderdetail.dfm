object frmOrderdetail: TfrmOrderdetail
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #35813#20070#35746#21333#26126#32454
  ClientHeight = 415
  ClientWidth = 981
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
    Width = 981
    Height = 415
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object DBGrid1: TDBGrid
      Left = 4
      Top = 4
      Width = 977
      Height = 374
      DataSource = ds
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
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
          FieldName = 'clientName'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #23458#25143
          Width = 86
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'OrderNtCode'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #21333#21495
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'HdTime'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #35746#21333#26085#26399
          Width = 59
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'xiaoqu'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #26657#21306
          Width = 58
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'xueyuan'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #23398#38498
          Width = 59
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'incode'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #20869#37096#35782#21035#30721
          Width = 61
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ISBN'
          Title.Alignment = taCenter
          Width = 88
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'bookname'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 111
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AbbreviatedName'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Width = 62
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Amount'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #25910#35746#25968#37327
          Width = 52
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Discount'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #25240#25187
          Width = 48
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'SendAmount'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #24050#21457#25968
          Width = 46
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'UnsendAmount'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #26410#21457#25968
          Width = 43
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'localnum'
          Title.Alignment = taCenter
          Title.Caption = #38145#23450#25968
          Width = 43
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'usableamount'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #24211#23384#21487#29992#25968
          Width = 62
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'stkamount'
          Title.Alignment = taCenter
          Title.Caption = #24211#23384#25968#37327
          Width = 54
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'state'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #29366#24577
          Width = 58
          Visible = True
        end>
    end
    object RzButton1: TRzButton
      Left = 896
      Top = 384
      Caption = #30830#23450
      TabOrder = 1
      OnClick = RzButton1Click
    end
  end
  object ds: TDataSource
    DataSet = aq
    Left = 472
    Top = 184
  end
  object aq: TADOQuery
    LockType = ltBatchOptimistic
    Parameters = <>
    Left = 296
    Top = 216
  end
  object fcon: TADOConnection
    Left = 768
    Top = 184
  end
end
