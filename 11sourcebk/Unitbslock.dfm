object frmbslock: Tfrmbslock
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #19994#21153#38145#23450
  ClientHeight = 505
  ClientWidth = 804
  Color = 16180174
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 35
    Width = 788
    Height = 143
    Ctl3D = True
    ParentCtl3D = False
    TabOrder = 0
    object spselectClient: TSpeedButton
      Left = 746
      Top = 49
      Width = 23
      Height = 20
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
    object chstart: TCheckBox
      Left = 14
      Top = 20
      Width = 79
      Height = 17
      Caption = #36215#22987#26102#38388
      TabOrder = 0
    end
    object dtpstart: TDateTimePicker
      Left = 88
      Top = 20
      Width = 249
      Height = 21
      Date = 40359.672460208330000000
      Time = 40359.672460208330000000
      TabOrder = 1
    end
    object chend: TCheckBox
      Left = 410
      Top = 20
      Width = 79
      Height = 17
      Caption = #32467#26463#26102#38388
      TabOrder = 2
    end
    object dtpend: TDateTimePicker
      Left = 483
      Top = 20
      Width = 257
      Height = 21
      Date = 40359.672460208330000000
      Time = 40359.672460208330000000
      TabOrder = 3
    end
    object rg: TRadioGroup
      Left = 11
      Top = 100
      Width = 774
      Height = 40
      Columns = 6
      ItemIndex = 0
      Items.Strings = (
        #35746#21333
        #37319#36141
        #20837#24211
        #20837#24211#36864#36135
        #21457#36135
        #21457#36135#36864#36135)
      TabOrder = 4
    end
    object cksupplier: TCheckBox
      Left = 14
      Top = 51
      Width = 67
      Height = 17
      Caption = #20379#24212#21830
      TabOrder = 5
    end
    object chclient: TCheckBox
      Left = 410
      Top = 49
      Width = 67
      Height = 17
      Caption = #23458#25143
      TabOrder = 6
    end
    object edclient: TEdit
      Left = 483
      Top = 48
      Width = 56
      Height = 21
      TabOrder = 7
      OnKeyPress = edclientKeyPress
    end
    object edtclient: TEdit
      Left = 539
      Top = 48
      Width = 201
      Height = 21
      ReadOnly = True
      TabOrder = 8
      OnChange = edtclientChange
    end
    object editsupplier: TEdit
      Left = 87
      Top = 50
      Width = 71
      Height = 21
      TabOrder = 9
      OnKeyPress = editsupplierKeyPress
    end
    object cbsupplier: TComboBox
      Left = 160
      Top = 51
      Width = 177
      Height = 21
      ItemHeight = 0
      TabOrder = 10
      OnChange = cbsupplierChange
    end
    object chuser: TCheckBox
      Left = 410
      Top = 77
      Width = 58
      Height = 17
      Caption = #25805#20316#21592
      TabOrder = 11
    end
    object cbuser: TComboBox
      Left = 483
      Top = 76
      Width = 257
      Height = 21
      ItemHeight = 0
      TabOrder = 12
    end
  end
  object dg1: TDBGrid
    Left = 8
    Top = 184
    Width = 788
    Height = 297
    DataSource = ds
    FixedColor = 16180174
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect]
    PopupMenu = pm
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnMouseUp = dg1MouseUp
    Columns = <
      item
        Expanded = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #23458#25143#21517#31216
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #21333#21495
        Width = 95
        Visible = True
      end
      item
        Expanded = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #25968#37327
        Width = 65
        Visible = True
      end
      item
        Expanded = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #30721#27915
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #23454#27915
        Width = 70
        Visible = True
      end
      item
        Expanded = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #26085#26399
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #29366#24577
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #38145#23450
        Width = 65
        Visible = True
      end
      item
        Expanded = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #25805#20316#21592
        Width = 60
        Visible = True
      end
      item
        Expanded = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Alignment = taCenter
        Title.Caption = #22791#27880
        Width = 150
        Visible = True
      end
      item
        Expanded = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        Visible = True
      end>
  end
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 804
    Height = 29
    AutoStyle = False
    ButtonWidth = 60
    ShowButtonCaptions = True
    TextOptions = ttoSelectiveTextOnRight
    BorderInner = fsNone
    BorderOuter = fsNone
    BorderSides = [sdTop]
    BorderWidth = 0
    Color = clSkyBlue
    GradientColorStyle = gcsCustom
    TabOrder = 2
    VisualStyle = vsClassic
    ToolbarControls = (
      BtnView
      BtnAlignBottom
      RzToolButton1
      BtnExport
      BtnExit)
    object BtnExit: TRzToolButton
      Left = 252
      Top = -4
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 1
      ImageIndex = 0
      UseToolbarButtonSize = False
      Caption = #36864#20986#13'(&Q)'
      OnClick = BtnExitClick
    end
    object BtnAlignBottom: TRzToolButton
      Left = 64
      Top = -4
      Width = 64
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 3
      ImageIndex = 2
      UseToolbarButtonSize = False
      Caption = #38145#23450#13'(&N)'
      OnClick = BtnAlignBottomClick
    end
    object BtnView: TRzToolButton
      Left = 4
      Top = -4
      Width = 60
      Height = 36
      Hint = 'View'
      DisabledIndex = 5
      ImageIndex = 4
      UseToolbarButtonSize = False
      Caption = #26597#35810#13'(&F)'
      OnClick = BtnViewClick
    end
    object BtnExport: TRzToolButton
      Left = 192
      Top = -4
      Width = 60
      Height = 36
      Hint = 'Export'
      DisabledIndex = 7
      ImageIndex = 6
      UseToolbarButtonSize = False
      Caption = #25104#26412#13#32467#36716'(&J)'
    end
    object RzToolButton1: TRzToolButton
      Left = 128
      Top = -4
      Width = 64
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 3
      ImageIndex = 2
      UseToolbarButtonSize = False
      Caption = #35299#38145#13'(&J)'
      OnClick = RzToolButton1Click
    end
  end
  object con: TADOConnection
    LoginPrompt = False
    Left = 728
    Top = 176
  end
  object ds: TDataSource
    DataSet = aq
    Left = 504
    Top = 240
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 688
    Top = 216
  end
  object pm: TPopupMenu
    Left = 312
    Top = 320
    object Q1: TMenuItem
      Caption = #20840#36873'(Q)'
      OnClick = Q1Click
    end
    object L1: TMenuItem
      Caption = #38145#23450'(&L)'
      OnClick = BtnAlignBottomClick
    end
    object N1: TMenuItem
      Caption = #35299#38145'(&J)'
      OnClick = RzToolButton1Click
    end
  end
end
