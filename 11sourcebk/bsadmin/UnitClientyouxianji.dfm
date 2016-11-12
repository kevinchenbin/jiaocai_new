object frmClientyouxianji: TfrmClientyouxianji
  Left = 0
  Top = 0
  Caption = #23458#25143#20248#20808#32423#35774#32622
  ClientHeight = 641
  ClientWidth = 748
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
    Width = 748
    Height = 641
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object Label1: TLabel
      Left = 248
      Top = 14
      Width = 336
      Height = 13
      Caption = #25552#31034#65306#21482#26377#21516#19968#26412#20070#34987#22810#23478#23458#25143#35746#36141#26102#25165#38656#35201#35774#32622#23458#25143#20248#20808#32423#65281
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object RzButton1: TRzButton
      Left = 8
      Top = 8
      Width = 97
      Caption = #25353#20070#25353#23458#25143#35774#32622
      Color = clSkyBlue
      TabOrder = 0
      OnClick = RzButton1Click
    end
    object dbg1: TDBGrid
      Left = 8
      Top = 39
      Width = 729
      Height = 577
      DataSource = ds1
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'bookyouxianji'
          Title.Alignment = taCenter
          Title.Caption = #20248#20808#32423
          Width = 47
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ClientName'
          Title.Alignment = taCenter
          Title.Caption = #23458#25143#21517#31216
          Width = 106
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Name'
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 117
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ISBN'
          Title.Alignment = taCenter
          Width = 82
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Price'
          Title.Alignment = taCenter
          Title.Caption = #23450#20215
          Width = 51
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'AbbreviatedName'
          Title.Alignment = taCenter
          Title.Caption = #20986#29256#31038
          Width = 120
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PressCount'
          Title.Alignment = taCenter
          Title.Caption = #29256#27425
          Width = 39
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Author'
          Title.Alignment = taCenter
          Title.Caption = #20316#32773
          Width = 72
          Visible = True
        end>
    end
    object dbg2: TDBGrid
      Left = 8
      Top = 39
      Width = 401
      Height = 577
      DataSource = ds2
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clNavy
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'youxianji'
          Title.Alignment = taCenter
          Title.Caption = #20248#20808#32423
          Width = 57
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ClientName'
          Title.Alignment = taCenter
          Title.Caption = #23458#25143#21517#31216
          Width = 291
          Visible = True
        end>
    end
    object RzButton2: TRzButton
      Left = 127
      Top = 8
      Width = 97
      Caption = #25353#23458#25143#35774#32622
      Color = clSkyBlue
      TabOrder = 3
      OnClick = RzButton2Click
    end
    object RzButton3: TRzButton
      Left = 679
      Top = 8
      Width = 58
      Caption = #30830#23450
      Color = clSkyBlue
      TabOrder = 4
      OnClick = RzButton3Click
    end
  end
  object aq1: TADOQuery
    Parameters = <>
    Left = 504
    Top = 160
  end
  object ds1: TDataSource
    DataSet = aq1
    Left = 360
    Top = 168
  end
  object ds2: TDataSource
    DataSet = aq2
    Left = 432
    Top = 120
  end
  object aq2: TADOQuery
    Parameters = <>
    Left = 568
    Top = 176
  end
  object con: TADOConnection
    Left = 600
    Top = 176
  end
end
