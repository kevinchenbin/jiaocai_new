object frmExcelImport: TfrmExcelImport
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = 'Excel'#23548#20837
  ClientHeight = 238
  ClientWidth = 642
  Color = 16180174
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = True
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 29
    Width = 642
    Height = 209
    Align = alClient
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object lbl3: TLabel
      Left = 14
      Top = 117
      Width = 40
      Height = 13
      Alignment = taCenter
      Caption = #25991#20214#21517':'
    end
    object spselectpath: TSpeedButton
      Left = 446
      Top = 111
      Width = 44
      Height = 25
      Caption = '....'
      Flat = True
      OnClick = spselectpathClick
    end
    object Label1: TLabel
      Left = 15
      Top = 152
      Width = 48
      Height = 13
      Caption = #24635#35760#24405#65306
    end
    object Label2: TLabel
      Left = 56
      Top = 171
      Width = 180
      Height = 13
      Caption = #27491#22312#23548#20837#35746#21333#26126#32454#65292#35831#31245#20399#12290#12290#12290
      Visible = False
    end
    object edtExcelPath: TRzEdit
      Left = 60
      Top = 114
      Width = 380
      Height = 21
      TabOrder = 0
    end
    object chisbn: TCheckBox
      Left = 16
      Top = 9
      Width = 89
      Height = 17
      Caption = 'ISBN'
      Checked = True
      State = cbChecked
      TabOrder = 1
    end
    object chname: TCheckBox
      Left = 119
      Top = 9
      Width = 90
      Height = 17
      Caption = #20070#21517
      Checked = True
      Enabled = False
      State = cbChecked
      TabOrder = 2
    end
    object chprice: TCheckBox
      Left = 222
      Top = 9
      Width = 82
      Height = 17
      Caption = #23450#20215
      Checked = True
      State = cbChecked
      TabOrder = 3
    end
    object chpress: TCheckBox
      Left = 16
      Top = 32
      Width = 89
      Height = 17
      Caption = #20986#29256#31038
      Checked = True
      State = cbChecked
      TabOrder = 4
    end
    object chpresscount: TCheckBox
      Left = 119
      Top = 32
      Width = 90
      Height = 17
      Caption = #29256#27425
      Checked = True
      State = cbChecked
      TabOrder = 5
    end
    object chamount: TCheckBox
      Left = 222
      Top = 32
      Width = 82
      Height = 17
      Caption = #25968#37327
      Checked = True
      Enabled = False
      State = cbChecked
      TabOrder = 6
    end
    object chauthor: TCheckBox
      Left = 318
      Top = 9
      Width = 79
      Height = 17
      Caption = #20316#32773
      Checked = True
      State = cbChecked
      TabOrder = 7
    end
    object chbk: TCheckBox
      Left = 411
      Top = 32
      Width = 97
      Height = 17
      Caption = #22791#27880
      Checked = True
      State = cbChecked
      TabOrder = 9
    end
    object chdiscount: TCheckBox
      Left = 318
      Top = 32
      Width = 79
      Height = 17
      Caption = #25240#25187
      Checked = True
      State = cbChecked
      TabOrder = 8
    end
    object Panel1: TPanel
      Left = 530
      Top = 121
      Width = 55
      Height = 20
      TabOrder = 10
      Visible = False
    end
    object chclass: TCheckBox
      Left = 504
      Top = 8
      Width = 97
      Height = 17
      Caption = #29677#32423
      Checked = True
      State = cbChecked
      TabOrder = 11
    end
    object chxuexuao: TCheckBox
      Left = 411
      Top = 8
      Width = 79
      Height = 17
      Caption = #23398#26657#24207#21495
      Checked = True
      State = cbChecked
      TabOrder = 12
    end
    object chxiaoqu: TCheckBox
      Left = 15
      Top = 55
      Width = 89
      Height = 17
      Caption = #26657#21306
      Checked = True
      State = cbChecked
      TabOrder = 13
    end
    object chxueyuan: TCheckBox
      Left = 118
      Top = 55
      Width = 90
      Height = 17
      Caption = #23398#38498
      Checked = True
      State = cbChecked
      TabOrder = 14
    end
    object chcourse: TCheckBox
      Left = 221
      Top = 55
      Width = 82
      Height = 17
      Caption = #35838#31243#21517#31216
      Checked = True
      State = cbChecked
      TabOrder = 15
    end
    object chteacher: TCheckBox
      Left = 410
      Top = 55
      Width = 80
      Height = 17
      Caption = #20219#35838#25945#24072
      Checked = True
      State = cbChecked
      TabOrder = 16
    end
    object chincode: TCheckBox
      Left = 317
      Top = 55
      Width = 79
      Height = 17
      Caption = #20869#37096#35782#21035#30721
      Checked = True
      State = cbChecked
      TabOrder = 17
    end
    object chtelphone: TCheckBox
      Left = 504
      Top = 55
      Width = 81
      Height = 17
      Caption = #32852#31995#26041#24335
      Checked = True
      State = cbChecked
      TabOrder = 18
    end
    object chtishi: TCheckBox
      Left = 410
      Top = 82
      Width = 175
      Height = 17
      Caption = #23548#20837#36807#31243#20013#24314#26032#20070#26159#21542#25552#31034
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 19
    end
  end
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 642
    Height = 29
    AutoStyle = False
    Images = ImageList1
    ButtonWidth = 60
    ShowButtonCaptions = True
    TextOptions = ttoSelectiveTextOnRight
    BorderInner = fsNone
    BorderOuter = fsNone
    BorderSides = [sdTop]
    BorderWidth = 0
    Color = clSkyBlue
    GradientColorStyle = gcsMSOffice
    TabOrder = 1
    VisualStyle = vsClassic
    ToolbarControls = (
      BtnImport
      BtnExit)
    object BtnImport: TRzToolButton
      Left = 4
      Top = -4
      Width = 60
      Height = 36
      Hint = 'Import'
      DisabledIndex = 1
      ImageIndex = 0
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      Caption = #23548#20837#13'[F7]'
      OnClick = BtnImportClick
    end
    object BtnExit: TRzToolButton
      Left = 64
      Top = -4
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 3
      ImageIndex = 2
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      Caption = #36864#20986#13'(&Q)'
      OnClick = BtnExitClick
    end
  end
  object opndlgExcelPath: TRzOpenDialog
    Filter = 'Excel '#25991#20214'|*.xls'
    Left = 552
    Top = 40
  end
  object dset: TADODataSet
    CommandText = 
      'select ID, ParentID,BookTypeName, PressID,ISBN, Name, Price, Bar' +
      'code, UserDefCode, Date, Author, PressCount, Unavailable, bigBoo' +
      'kTypeID, smallBookTypeID, TotalAmount, PresentNum, AbbreviatedNa' +
      'me, FullName from UV_PressAndBookCatalogQuery'
    Parameters = <>
    Left = 448
    Top = 248
  end
  object con1: TADOConnection
    Left = 472
    Top = 64
  end
  object ImageList1: TImageList
    Left = 440
    Top = 184
    Bitmap = {
      494C010106000A00540010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000002000000001002000000000000020
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC99660000000000CC99
      660000000000CC99660000000000CC99660000000000CC99660000000000CC99
      660000000000CC996600000000000000000000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000CCCCCC0000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009933000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F100E5E5E500CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F10000000000CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000993300009933000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999009999990000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E2EFF100E5E5E500B2B2
      B200CC9999009966660099666600B2B2B200CCCCCC00E5E5E500E2EFF1000000
      00000000000000000000000000000000000000000000E2EFF10000000000B2B2
      B200999999009999990099999900B2B2B200CCCCCC0000000000E2EFF1000000
      0000000000000000000000000000000000000000000000000000000000009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300000000000000000000000000000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      990099999900000000000000000000000000E5E5E500CC99990099666600CC99
      9900CC999900FFFFFF00996666009999990099999900B2B2B200E5E5E5000000
      0000000000000000000000000000000000000000000099999900999999009999
      990099999900FFFFFF00999999009999990099999900B2B2B200000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000993300009933000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999009999990000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600336699003366990033669900E2EFF1000000
      0000000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900999999009999990099999900E2EFF1000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009933000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCCC000099CC00FFFFFF00FFCC
      CC000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000C0C0C00099999900FFFFFF00CCCC
      CC00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCFF003399CC00FFCCCC00CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000CCCCCC0099999900CCCCCC009999
      9900000000000000000000000000000000003399CC0000669900006699000066
      99000066990000669900006699000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC9966009999990099999900999999009999
      9900999999009999990099999900000000000000000099999900999999009999
      99009999990099999900999999009999990099666600FFCC9900CC999900CC99
      6600FFCCCC00FFFFFF009966660099CCCC0099CCFF00B2B2B200FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000999999009999
      9900CCCCCC00FFFFFF0099999900CCCCCC00CCCCCC00B2B2B200999999009999
      9900000000000000000000000000000000003399CC0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF00006699000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC99660099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000099999900000000000000
      00000000000000000000000000009999990099666600FFCC990099666600FFFF
      FF00FFCCCC00FFFFFF009966660099CCCC00C0C0C000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C00066666600FFFF
      FF00CCCCCC00FFFFFF0099999900CCCCCC00C0C0C00099999900999999009999
      9900999999009999990099999900000000003399CC0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF00006699000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC99660099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000099999900000000000000
      00000000000000000000000000009999990099666600FFCC9900CC9999009966
      6600FFCCCC00FFFFFF009966660000000000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000999999006666
      6600CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000003399CC0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF00006699000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC99660099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000099999900000000000000
      00000000000000000000000000009999990099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660000000000CC999900CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000003399CC0099FFFF0099FFFF0099FF
      FF0099FFFF0099FFFF00006699000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC99660099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000099999900000000000000
      00000000000000000000000000009999990099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00E2EFF100CC999900FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E2EFF10099999900999999009999
      9900000000000000000000000000000000003399CC0099FFFF0099FFFF003399
      CC003399CC003399CC003399CC000000000000000000CC996600FFFFFF00FFFF
      FF00CC996600CC996600CC996600CC99660099999900CCCCCC00CCCCCC009999
      9900999999009999990099999900000000000000000099999900000000000000
      00009999990099999900999999009999990099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660099CCCC000000000099CCCC00FFCC9900CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E500CCCCCC00C0C0C0009999
      9900000000000000000000000000000000003399CC0099FFFF0099FFFF003399
      CC00CCFFFF0000669900000000000000000000000000CC996600FFFFFF00FFFF
      FF00CC996600E5E5E500CC9966000000000099999900CCCCCC00CCCCCC009999
      9900CCCCCC009999990000000000000000000000000099999900000000000000
      000099999900E5E5E500999999000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00000000003399CC0000000000FFCC
      9900000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E5009999990000000000C0C0
      C000000000000000000000000000000000003399CC0099FFFF0099FFFF003399
      CC000066990000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00CC996600CC996600000000000000000099999900CCCCCC00CCCCCC009999
      9900999999000000000000000000000000000000000099999900000000000000
      00009999990099999900000000000000000000000000C0C0C000CC996600CC99
      9900CCCC9900FFFFFF00996666000099CC000099CC000099CC00000000000000
      00000000000000000000000000000000000000000000C0C0C000999999009999
      9900C0C0C000FFFFFF0099999900999999009999990099999900000000000000
      0000000000000000000000000000000000003399CC003399CC003399CC003399
      CC000000000000000000000000000000000000000000CC996600CC996600CC99
      6600CC9966000000000000000000000000009999990099999900999999009999
      9900000000000000000000000000000000000000000099999900999999009999
      990099999900000000000000000000000000000000000000000000000000CCCC
      CC00CC9999009966660099666600000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00999999009999990099999900000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000200000000100010000000000000100000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFF00000000FFFFFFFF00000000
      8003800300000000800380030000000080038003000000008003800300000000
      8003800300000000FFFFFFFF00000000BFFBBFFB00000000FFFFFFFF00000000
      BFFBBFFB00000000FFFFFFFF00000000BFFBBFFB00000000FFFFFFFF00000000
      AAABAAAB00000000FFFFFFFF00000000FFFFFFFFFDFFFDFFFBFFFBFFE0FFE8FF
      F3FFF3FF801FA05FE007E007001F803FF3FFF3FF001F001FFBFFFBFF000F000F
      FFFFFFFF000F000F01800180000F000F018001BE00010001018001BE01010001
      018001BE01010001018001BE000F000F018001B0008F000F038103B100AF002F
      078307B3803F803F0F870F87E1FFE1FF00000000000000000000000000000000
      000000000000}
  end
  object aq: TADOQuery
    Parameters = <>
    SQL.Strings = (
      'select * from BS_OrderNote where 1 = 0')
    Left = 416
    Top = 65528
  end
  object qry: TADOQuery
    Parameters = <>
    Left = 384
    Top = 65528
  end
  object ds: TDataSource
    Left = 376
    Top = 112
  end
  object query: TADOQuery
    Parameters = <>
    Left = 464
    Top = 65520
  end
  object comAddcatalog: TADOCommand
    CommandText = 'USP_BS_Add_Catalogid;1'
    CommandType = cmdStoredProc
    Parameters = <
      item
        Name = '@return_value'
        DataType = ftInteger
        Direction = pdReturnValue
        Size = 10
        Value = Null
      end
      item
        Name = '@ISBN'
        Attributes = [paNullable]
        DataType = ftString
        Size = 20
        Value = Null
      end
      item
        Name = '@Name'
        Attributes = [paNullable]
        DataType = ftString
        Size = 100
        Value = Null
      end
      item
        Name = '@Price'
        Attributes = [paNullable]
        DataType = ftFloat
        Size = 10
        Value = Null
      end
      item
        Name = '@Author'
        Attributes = [paNullable]
        DataType = ftString
        Size = 10
        Value = Null
      end
      item
        Name = '@PressCount'
        Attributes = [paNullable]
        DataType = ftString
        Size = 100
        Value = Null
      end
      item
        Name = '@Press'
        Attributes = [paNullable]
        DataType = ftString
        Size = 50
        Value = Null
      end
      item
        Name = '@pressindex'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@barcode'
        DataType = ftString
        Size = 20
        Value = Null
      end
      item
        Name = '@newbook'
        DataType = ftInteger
        Direction = pdOutput
        Size = 10
        Value = Null
      end>
    Left = 272
  end
end