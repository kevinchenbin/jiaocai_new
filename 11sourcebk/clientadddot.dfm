object frmclientadddot: Tfrmclientadddot
  Left = 0
  Top = 0
  Caption = #23458#25143#25240#25187#21152#28857#35774#32622
  ClientHeight = 400
  ClientWidth = 625
  Color = 16180174
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 17
  object Label1: TLabel
    Left = 17
    Top = 14
    Width = 24
    Height = 17
    Caption = #23458#25143
  end
  object spselectClient: TSpeedButton
    Left = 523
    Top = 11
    Width = 23
    Height = 25
    Flat = True
    Glyph.Data = {
      36040000424D3604000000000000360000002800000010000000100000000100
      2000000000000004000000000000000000000000000000000000FF00FF00CCCC
      CC00C0C0C000E5E5E500FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00CCCCCC006699
      99006666990099999900E5E5E500FF00FF00FF00FF00FF00FF00FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF0066CC
      FF003399CC006666990099999900E5E5E500FF00FF00FF00FF00FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00CCCC
      FF0066CCFF003399CC006666990099999900E5E5E500FF00FF00FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
      FF00CCCCFF0066CCFF003399CC006666990099999900E5E5E500FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00
      FF00FF00FF00CCCCFF0066CCFF003399CC0066669900CCCCCC00FFCCCC00CC99
      9900CC999900CC999900CCCC9900E5E5E500FF00FF00FF00FF00FF00FF00FF00
      FF00FF00FF00FF00FF00CCCCFF0066CCFF00B2B2B200CC999900CCCC9900F2EA
      BF00FFFFCC00F2EABF00F2EABF00CC999900ECC6D900FF00FF00FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00E5E5E500CC999900FFCC9900FFFFCC00FFFF
      CC00FFFFCC00FFFFFF00FFFFFF00FFFFFF00CC999900E5E5E500FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00FFCCCC00CCCC9900FFFFCC00F2EABF00FFFF
      CC00FFFFCC00FFFFFF00FFFFFF00FFFFFF00F2EABF00CCCC9900FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00CCCC9900FFCC9900F2EABF00F2EABF00FFFF
      CC00FFFFCC00FFFFCC00FFFFFF00FFFFFF00F2EABF00CC999900FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00CC999900F2EABF00F2EABF00F2EABF00F2EA
      BF00FFFFCC00FFFFCC00FFFFCC00FFFFCC00FFFFCC00CC999900FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00CCCC9900F2EABF00FFFFCC00F2EABF00F2EA
      BF00F2EABF00FFFFCC00FFFFCC00FFFFCC00F2EABF00CC999900FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00FFCCCC00CCCC9900FFFFFF00FFFFFF00F2EA
      BF00F2EABF00F2EABF00F2EABF00FFFFCC00CCCC9900CCCC9900FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00E5E5E500CC999900ECC6D900FFFFFF00FFFF
      CC00F2EABF00F2EABF00F2EABF00FFCC9900CC999900E5E5E500FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00FF00FF00FFCCCC00CC999900FFCCCC00F2EA
      BF00F2EABF00F2EABF00CCCC9900CC999900FFCCCC00FF00FF00FF00FF00FF00
      FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00E5E5E500CCCC9900CC99
      9900CC999900CC999900CC999900E5E5E500FF00FF00FF00FF00}
    OnClick = spselectClientClick
  end
  object Label2: TLabel
    Left = 17
    Top = 50
    Width = 60
    Height = 17
    Caption = #38468#21152#25240#25187#28857
  end
  object Label3: TLabel
    Left = 153
    Top = 51
    Width = 11
    Height = 17
    Caption = '%'
  end
  object DBGrid1: TDBGrid
    Left = 8
    Top = 80
    Width = 609
    Height = 313
    DataSource = ds
    FixedColor = 16180174
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentFont = False
    PopupMenu = PopupMenu1
    TabOrder = 0
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'xuhao'
        Title.Alignment = taCenter
        Title.Caption = #24207#21495
        Width = 48
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'clientname'
        Title.Alignment = taCenter
        Title.Caption = #23458#25143#21517#31216
        Width = 389
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'adddot'
        Title.Alignment = taCenter
        Title.Caption = #38468#21152#25240#25187#28857'(%)'
        Width = 92
        Visible = True
      end>
  end
  object edquery: TEdit
    Left = 83
    Top = 11
    Width = 64
    Height = 25
    AutoSize = False
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 1
    OnKeyPress = edqueryKeyPress
  end
  object edtclient: TEdit
    Left = 146
    Top = 11
    Width = 375
    Height = 25
    AutoSize = False
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 2
  end
  object eddot: TEdit
    Left = 83
    Top = 47
    Width = 64
    Height = 25
    AutoSize = False
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 3
  end
  object Button1: TButton
    Left = 446
    Top = 47
    Width = 75
    Height = 25
    Caption = #35774#32622
    TabOrder = 4
    OnClick = Button1Click
  end
  object fcon: TADOConnection
    Left = 512
    Top = 152
  end
  object ds: TDataSource
    DataSet = query
    Left = 272
    Top = 176
  end
  object query: TADOQuery
    Parameters = <>
    Left = 280
    Top = 240
  end
  object PopupMenu1: TPopupMenu
    Left = 440
    Top = 232
    object N1: TMenuItem
      Caption = #21024#38500
      OnClick = N1Click
    end
  end
end