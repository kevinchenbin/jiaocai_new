object frmnewbook1: Tfrmnewbook1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #26032#20070#24405#20837
  ClientHeight = 483
  ClientWidth = 614
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 614
    Height = 29
    AutoStyle = False
    Images = ImageList1
    BorderInner = fsNone
    BorderOuter = fsNone
    BorderSides = [sdTop]
    BorderWidth = 0
    Color = clSkyBlue
    GradientColorStyle = gcsMSOffice
    TabOrder = 0
    VisualStyle = vsClassic
    ToolbarControls = (
      BtnSave
      BtnExit)
    object BtnSave: TRzToolButton
      Left = 4
      Top = -4
      Width = 72
      Height = 36
      Hint = 'Save'
      DisabledIndex = 1
      ImageIndex = 0
      ShowCaption = True
      UseToolbarButtonSize = False
      UseToolbarShowCaption = False
      Caption = #20445#23384#13'[F4]'
      OnClick = BtnSaveClick
    end
    object BtnExit: TRzToolButton
      Left = 76
      Top = -4
      Width = 75
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
  object Panel1: TPanel
    Left = 0
    Top = 29
    Width = 614
    Height = 454
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 1
    object Label1: TLabel
      Left = 17
      Top = 15
      Width = 48
      Height = 13
      Caption = #32463#33829#31867#21035
    end
    object RzLine1: TRzLine
      Left = 4
      Top = 35
      Width = 405
      Height = 20
    end
    object Label36: TLabel
      Left = 198
      Top = 16
      Width = 198
      Height = 16
      Caption = 'F11'#21487#22312#22522#26412#23646#24615#21644#25193#23637#23646#24615#20043#38388#20999#25442
    end
    object dg: TDBGrid
      Left = 17
      Top = 249
      Width = 581
      Height = 193
      DataSource = dsinsert
      FixedColor = 16180174
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      ParentFont = False
      TabOrder = 6
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnCellClick = dgCellClick
    end
    object pcwenju: TPageControl
      Left = 17
      Top = 57
      Width = 357
      Height = 153
      ActivePage = TabSheet1
      Style = tsButtons
      TabOrder = 4
      Visible = False
      object TabSheet1: TTabSheet
        Caption = #22522#26412#23646#24615
        object Label30: TLabel
          Left = 6
          Top = 14
          Width = 24
          Height = 13
          Caption = #26465#30721
        end
        object Label32: TLabel
          Left = 6
          Top = 42
          Width = 26
          Height = 13
          Caption = #21697#21517
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label33: TLabel
          Left = 6
          Top = 74
          Width = 26
          Height = 13
          Caption = #23450#20215
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object editwenjutiaomao: TEdit
          Left = 36
          Top = 10
          Width = 91
          Height = 19
          Ctl3D = False
          NumbersOnly = True
          ParentCtl3D = False
          TabOrder = 0
          OnKeyPress = editwenjutiaomaoKeyPress
        end
        object editwenjuname: TEdit
          Left = 36
          Top = 38
          Width = 241
          Height = 19
          Ctl3D = False
          ParentCtl3D = False
          TabOrder = 1
          OnKeyPress = editwenjunameKeyPress
        end
        object editwenjuself: TEdit
          Left = 276
          Top = 38
          Width = 70
          Height = 19
          Ctl3D = False
          Enabled = False
          ParentCtl3D = False
          ReadOnly = True
          TabOrder = 2
        end
        object editwenjuprice: TEdit
          Left = 35
          Top = 70
          Width = 91
          Height = 19
          Alignment = taRightJustify
          Ctl3D = False
          ParentCtl3D = False
          TabOrder = 3
          Text = #65509'0.00'
          OnKeyPress = editwenjupriceKeyPress
        end
      end
    end
    object pcqikan: TPageControl
      Left = 17
      Top = 57
      Width = 480
      Height = 165
      ActivePage = TabSheet2
      Style = tsButtons
      TabOrder = 5
      Visible = False
      object TabSheet2: TTabSheet
        Caption = #22522#26412#23646#24615
        object Label2: TLabel
          Left = 3
          Top = 4
          Width = 24
          Height = 13
          Caption = #26465#30721
        end
        object Label3: TLabel
          Left = 196
          Top = 4
          Width = 23
          Height = 13
          Caption = 'ISSN'
        end
        object Label4: TLabel
          Left = 3
          Top = 31
          Width = 26
          Height = 13
          Caption = #21002#21517
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label5: TLabel
          Left = 338
          Top = 31
          Width = 26
          Height = 13
          Caption = #23450#20215
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label6: TLabel
          Left = 340
          Top = 4
          Width = 24
          Height = 13
          Caption = #24180#20221
        end
        object Label7: TLabel
          Left = 3
          Top = 55
          Width = 36
          Height = 13
          Caption = #20986#29256#31038
        end
        object Label21: TLabel
          Left = 340
          Top = 55
          Width = 24
          Height = 13
          Caption = #31867#21035
        end
        object Label22: TLabel
          Left = 3
          Top = 86
          Width = 24
          Height = 13
          Caption = #21002#26399
        end
        object Label31: TLabel
          Left = 316
          Top = 86
          Width = 48
          Height = 13
          Caption = #27599#26399#21002#25968
          Visible = False
        end
        object Label34: TLabel
          Left = 340
          Top = 112
          Width = 24
          Height = 13
          Caption = #24180#20215
        end
        object Label37: TLabel
          Left = 3
          Top = 112
          Width = 48
          Height = 13
          Caption = #20869#37096#21002#21495
        end
        object Label38: TLabel
          Left = 163
          Top = 112
          Width = 72
          Height = 13
          Caption = #22269#20869#32479#19968#21002#21495
        end
        object editqikanmao: TEdit
          Left = 40
          Top = 2
          Width = 112
          Height = 19
          Ctl3D = False
          MaxLength = 15
          NumbersOnly = True
          ParentCtl3D = False
          TabOrder = 0
          OnKeyPress = editqikanmaoKeyPress
        end
        object editqikanname: TEdit
          Left = 40
          Top = 27
          Width = 185
          Height = 19
          Ctl3D = False
          ParentCtl3D = False
          TabOrder = 1
          OnKeyPress = editqikannameKeyPress
        end
        object editqikanissn: TEdit
          Left = 224
          Top = 2
          Width = 89
          Height = 19
          Ctl3D = False
          ParentCtl3D = False
          TabOrder = 2
          OnKeyPress = editqikanissnKeyPress
        end
        object editqikanself: TEdit
          Left = 224
          Top = 27
          Width = 89
          Height = 19
          Ctl3D = False
          ParentCtl3D = False
          ReadOnly = True
          TabOrder = 3
        end
        object editqikanprice: TEdit
          Left = 365
          Top = 27
          Width = 95
          Height = 19
          Alignment = taRightJustify
          Ctl3D = False
          ParentCtl3D = False
          TabOrder = 4
          Text = #65509'0.00'
          OnExit = editqikanpriceExit
          OnKeyPress = editqikanpriceKeyPress
        end
        object editqikanqihao: TEdit
          Left = 151
          Top = 2
          Width = 34
          Height = 19
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          NumbersOnly = True
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 5
          OnKeyPress = editqikanqihaoKeyPress
        end
        object cbpress: TComboBox
          Left = 81
          Top = 52
          Width = 104
          Height = 21
          Ctl3D = False
          ItemHeight = 13
          ParentCtl3D = False
          TabOrder = 6
          OnKeyPress = cbpressKeyPress
        end
        object edpress: TEdit
          Left = 40
          Top = 52
          Width = 42
          Height = 21
          TabOrder = 7
          OnKeyPress = edpressKeyPress
        end
        object sedyear: TRzSpinEdit
          Left = 365
          Top = 1
          Width = 95
          Height = 21
          Max = 3000.000000000000000000
          Min = 2000.000000000000000000
          Value = 2000.000000000000000000
          TabOrder = 8
          OnKeyPress = sedyearKeyPress
        end
        object cbtype: TComboBox
          Left = 365
          Top = 52
          Width = 95
          Height = 21
          BevelInner = bvNone
          BevelOuter = bvNone
          Ctl3D = False
          ItemHeight = 13
          ParentCtl3D = False
          TabOrder = 9
          OnKeyPress = cbtypeKeyPress
        end
        object cbkanqi: TComboBox
          Left = 40
          Top = 83
          Width = 114
          Height = 21
          BevelInner = bvNone
          BevelOuter = bvNone
          Ctl3D = False
          ItemHeight = 13
          ParentCtl3D = False
          TabOrder = 10
          Text = #26376#21002
          OnExit = cbkanqiExit
          OnKeyPress = cbkanqiKeyPress
          Items.Strings = (
            #21608#21002
            #21322#26376#21002
            #26376#21002
            #21452#26376#21002
            #23395#21002
            #21322#24180#21002
            #24180#21002)
        end
        object cbduokan: TComboBox
          Left = 260
          Top = 83
          Width = 53
          Height = 21
          BevelInner = bvNone
          BevelOuter = bvNone
          Style = csDropDownList
          Ctl3D = False
          ItemHeight = 13
          ItemIndex = 0
          ParentCtl3D = False
          TabOrder = 11
          Text = #19978
          Visible = False
          OnKeyPress = cbduokanKeyPress
          Items.Strings = (
            #19978
            #19979)
        end
        object sedkannum: TRzSpinEdit
          Left = 365
          Top = 83
          Width = 95
          Height = 21
          Min = 2.000000000000000000
          Value = 2.000000000000000000
          TabOrder = 12
          Visible = False
          OnExit = sedkannumExit
          OnKeyPress = sedkannumKeyPress
        end
        object chduokan: TCheckBox
          Left = 181
          Top = 86
          Width = 54
          Height = 17
          Caption = #22810#21002
          Color = 16180174
          ParentColor = False
          TabOrder = 13
          OnClick = chduokanClick
          OnKeyPress = chduokanKeyPress
        end
        object edkanhao: TEdit
          Left = 57
          Top = 110
          Width = 95
          Height = 21
          TabOrder = 14
          OnKeyPress = edkanhaoKeyPress
        end
        object edtykanhao: TEdit
          Left = 237
          Top = 110
          Width = 76
          Height = 21
          TabOrder = 15
          OnKeyPress = edtykanhaoKeyPress
        end
        object edyearprice: TEdit
          Left = 365
          Top = 110
          Width = 95
          Height = 21
          TabOrder = 16
          OnKeyPress = edyearpriceKeyPress
        end
        object GroupBox1: TGroupBox
          Left = 9
          Top = 74
          Width = 448
          Height = 7
          Color = 16180174
          ParentBackground = False
          ParentColor = False
          TabOrder = 17
        end
      end
    end
    object RzDBGrid1: TRzDBGrid
      Left = 17
      Top = 249
      Width = 581
      Height = 193
      DataSource = ds
      DefaultDrawing = True
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
      OnCellClick = RzDBGrid1CellClick
      Columns = <
        item
          Expanded = False
          FieldName = 'ISBN'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'barcode'
          Title.Caption = #26465#30721
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'name'
          Title.Caption = #20070#21517
          Width = 130
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'userdefcode'
          Title.Caption = #33258#32534#30721
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'price'
          Title.Caption = #23450#20215
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'abbreviatedname'
          Title.Caption = #20986#29256#31038
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'PressCount'
          Title.Caption = #29256#27425
          Width = 28
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'author'
          Title.Caption = #20316#32773
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ID'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'pid'
          Visible = False
        end
        item
          Expanded = False
          FieldName = 'smallbooktypeid'
          Visible = False
        end>
    end
    object rzcbinput: TRzCheckBox
      Left = 516
      Top = 219
      Width = 70
      Height = 15
      BiDiMode = bdLeftToRight
      Caption = ' '#36830#32493#24405#20837
      ParentBiDiMode = False
      State = cbUnchecked
      TabOrder = 1
    end
    object PageControlBook: TPageControl
      Left = 17
      Top = 58
      Width = 476
      Height = 185
      ActivePage = tsbase
      ParentShowHint = False
      ShowHint = False
      Style = tsButtons
      TabOrder = 2
      object tsbase: TTabSheet
        Caption = #22522#26412#23646#24615
        ExplicitWidth = 456
        object Label8: TLabel
          Left = 3
          Top = 10
          Width = 24
          Height = 13
          Caption = #26465#30721
        end
        object Label9: TLabel
          Left = 215
          Top = 10
          Width = 23
          Height = 13
          Caption = 'ISBN'
        end
        object SpeedButton2: TSpeedButton
          Left = 365
          Top = 7
          Width = 28
          Height = 21
          Caption = '10'
          Flat = True
          OnClick = SpeedButton1Click
        end
        object Label10: TLabel
          Left = 3
          Top = 35
          Width = 26
          Height = 13
          Caption = #20070#21517
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label11: TLabel
          Left = 3
          Top = 60
          Width = 26
          Height = 13
          Caption = #23450#20215
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label12: TLabel
          Left = 148
          Top = 60
          Width = 24
          Height = 13
          Caption = #20316#32773
        end
        object Label13: TLabel
          Left = 3
          Top = 86
          Width = 24
          Height = 13
          Caption = #31867#21035
        end
        object Label14: TLabel
          Left = 202
          Top = 85
          Width = 36
          Height = 13
          Caption = #20986#29256#31038
        end
        object Label15: TLabel
          Left = 3
          Top = 112
          Width = 48
          Height = 13
          Caption = #20986#29256#26085#26399
        end
        object Label16: TLabel
          Left = 214
          Top = 112
          Width = 24
          Height = 13
          Caption = #29256#27425
        end
        object Label35: TLabel
          Left = 3
          Top = 135
          Width = 48
          Height = 13
          Caption = #33719#22870#24773#20917
        end
        object Label23: TLabel
          Left = 292
          Top = 60
          Width = 28
          Height = 13
          Caption = #20876'/'#21253
        end
        object editcode: TEdit
          Left = 33
          Top = 7
          Width = 147
          Height = 21
          Ctl3D = True
          MaxLength = 13
          NumbersOnly = True
          ParentCtl3D = False
          TabOrder = 0
          OnKeyPress = editcodeKeyPress
        end
        object editisbn: TEdit
          Left = 244
          Top = 7
          Width = 121
          Height = 21
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 1
          OnKeyPress = editisbnKeyPress
        end
        object editbookname: TEdit
          Left = 33
          Top = 32
          Width = 291
          Height = 21
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 2
          OnKeyPress = editbooknameKeyPress
        end
        object editbookself: TEdit
          Left = 322
          Top = 32
          Width = 71
          Height = 21
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 3
          OnKeyPress = editbookselfKeyPress
        end
        object editprice: TEdit
          Left = 33
          Top = 57
          Width = 79
          Height = 21
          Alignment = taRightJustify
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 4
          Text = #65509'0.00'
          OnKeyPress = editpriceKeyPress
        end
        object editauthor: TEdit
          Left = 177
          Top = 57
          Width = 76
          Height = 21
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 5
          OnKeyPress = editauthorKeyPress
        end
        object rcbtype: TComboBox
          Left = 33
          Top = 82
          Width = 147
          Height = 21
          BevelInner = bvNone
          BevelOuter = bvNone
          Ctl3D = True
          ItemHeight = 13
          ParentCtl3D = False
          TabOrder = 6
          OnKeyPress = rcbtypeKeyPress
        end
        object rcbpress: TComboBox
          Left = 288
          Top = 82
          Width = 107
          Height = 21
          Style = csDropDownList
          Ctl3D = True
          ItemHeight = 13
          ParentCtl3D = False
          TabOrder = 7
          OnKeyPress = rcbpressKeyPress
        end
        object datapressday: TDateTimePicker
          Left = 55
          Top = 108
          Width = 89
          Height = 21
          Date = 40146.605024768520000000
          Time = 40146.605024768520000000
          TabOrder = 8
          OnKeyPress = datapressdayKeyPress
        end
        object edquery: TEdit
          Left = 244
          Top = 82
          Width = 43
          Height = 21
          TabOrder = 9
          OnKeyPress = edqueryKeyPress
        end
        object edpresscount: TEdit
          Left = 244
          Top = 108
          Width = 149
          Height = 21
          TabOrder = 10
          OnKeyPress = edpresscountKeyPress
        end
        object edhuojiangstate: TEdit
          Left = 57
          Top = 131
          Width = 338
          Height = 21
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 11
          OnKeyDown = edhuojiangstateKeyDown
        end
        object spepack: TRzSpinEdit
          Left = 326
          Top = 57
          Width = 69
          Height = 21
          AllowKeyEdit = True
          Max = 10000.000000000000000000
          Value = 1.000000000000000000
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 12
          OnKeyDown = spepackKeyDown
        end
      end
      object tsdetail: TTabSheet
        Caption = #25193#23637#23646#24615
        ImageIndex = 1
        object Label17: TLabel
          Left = 3
          Top = 35
          Width = 48
          Height = 13
          Caption = #21360'        '#27425
        end
        object Label18: TLabel
          Left = 211
          Top = 60
          Width = 24
          Height = 13
          Caption = #35013#24103
        end
        object Label19: TLabel
          Left = 3
          Top = 86
          Width = 48
          Height = 13
          Caption = #19995'        '#20070
        end
        object Label20: TLabel
          Left = 3
          Top = 60
          Width = 48
          Height = 13
          Caption = #24320'        '#26412
        end
        object Label24: TLabel
          Left = 3
          Top = 9
          Width = 47
          Height = 13
          Caption = 'ISBN'#20998#31867
        end
        object Label25: TLabel
          Left = 211
          Top = 35
          Width = 24
          Height = 13
          Caption = #38468#20214
        end
        object Label26: TLabel
          Left = 211
          Top = 9
          Width = 24
          Height = 13
          Caption = #35793#32773
        end
        object Label27: TLabel
          Left = 3
          Top = 110
          Width = 48
          Height = 13
          Caption = #22791'        '#27880
        end
        object Label28: TLabel
          Left = 157
          Top = 35
          Width = 12
          Height = 13
          Caption = #27425
        end
        object Label29: TLabel
          Left = 83
          Top = 35
          Width = 12
          Height = 13
          Caption = #31532
        end
        object edISBNtype: TEdit
          Left = 55
          Top = 7
          Width = 114
          Height = 21
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 0
          OnKeyPress = edISBNtypeKeyPress
        end
        object edbook: TEdit
          Left = 55
          Top = 84
          Width = 325
          Height = 21
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 1
          OnKeyPress = edbookKeyPress
        end
        object edaffix: TEdit
          Left = 241
          Top = 32
          Width = 139
          Height = 21
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 2
          OnKeyPress = edaffixKeyPress
        end
        object edyizhe: TEdit
          Left = 242
          Top = 7
          Width = 138
          Height = 21
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 3
          OnKeyPress = edyizheKeyPress
        end
        object cbformat: TComboBox
          Left = 55
          Top = 57
          Width = 114
          Height = 21
          Ctl3D = False
          ItemHeight = 13
          ParentCtl3D = False
          TabOrder = 4
          Text = #21313#20845#24320
          OnKeyPress = cbformatKeyPress
          Items.Strings = (
            '16'#24320
            '32'#24320
            '48'#24320
            '64'#24320
            #22823'16'#24320
            #22823'32'#24320
            #22823'48'#24320
            #22823'64'#24320)
        end
        object cbbind: TComboBox
          Left = 241
          Top = 57
          Width = 139
          Height = 21
          Ctl3D = False
          ItemHeight = 13
          ItemIndex = 0
          ParentCtl3D = False
          TabOrder = 5
          Text = #31934#35013
          OnKeyPress = cbbindKeyPress
          Items.Strings = (
            #31934#35013
            #24179#35013
            #31616#35013)
        end
        object edbk: TEdit
          Left = 55
          Top = 108
          Width = 325
          Height = 21
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 6
          OnKeyPress = edbkKeyPress
        end
        object edprintcount: TRzSpinEdit
          Left = 99
          Top = 32
          Width = 56
          Height = 21
          TabOrder = 7
          OnKeyPress = edprintcountKeyPress
        end
      end
    end
    object cbsaletype: TComboBox
      Left = 80
      Top = 12
      Width = 92
      Height = 21
      Color = clWhite
      Ctl3D = False
      DoubleBuffered = True
      ItemHeight = 13
      ItemIndex = 0
      ParentCtl3D = False
      ParentDoubleBuffered = False
      TabOrder = 3
      Text = #22270#20070
      OnChange = cbsaletypeChange
      Items.Strings = (
        #22270#20070
        #26399#21002
        #25991#20855)
    end
  end
  object ImageList1: TImageList
    Left = 568
    Top = 352
    Bitmap = {
      494C010106000A00300010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000002000000001002000000000000020
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC996600CC996600CC9966000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000099999900FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF009933
      0000993300009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900FFFFFF00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF009933
      0000CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC99660099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900FFFFFF00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF009933
      0000993300009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900FFFFFF00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF009933
      0000CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC99660099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900FFFFFF00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF009933
      0000993300009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900FFFFFF00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF009933
      0000CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC99660099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900FFFFFF00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF009933
      0000993300009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900FFFFFF00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF009933
      0000CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC99660099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900FFFFFF00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF009933
      0000993300009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900FFFFFF00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF009933
      0000CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC99660099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900FFFFFF00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF009933
      0000993300009933000099330000993300009933000099330000993300009933
      00009933000099330000FFFFFF00CC9966000000000099999900FFFFFF009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900FFFFFF00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CC9966000000000099999900FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC996600CC996600CC996600CC9966000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999009999990099999900999999000000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000099330000000000000000000000000000999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      990099999900999999009999990000000000000000000000000000000000E2EF
      F100E5E5E500CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F10000000000CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      000099330000E5E5E500CC66000099330000E5E5E500E5E5E500E5E5E5009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC0099999900E5E5E500CCCCCC0099999900E5E5E500E5E5E500E5E5E5009999
      9900CCCCCC00CCCCCC00999999000000000000000000E2EFF100E5E5E500B2B2
      B200CC9999009966660099666600B2B2B200CCCCCC00E5E5E500E2EFF1000000
      00000000000000000000000000000000000000000000E2EFF10000000000B2B2
      B200999999009999990099999900B2B2B200CCCCCC0000000000E2EFF1000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      000099330000E5E5E500CC66000099330000E5E5E500E5E5E500E5E5E5009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC0099999900E5E5E500CCCCCC0099999900E5E5E500E5E5E500E5E5E5009999
      9900CCCCCC00CCCCCC009999990000000000E5E5E500CC99990099666600CC99
      9900CC999900FFFFFF00996666009999990099999900B2B2B200E5E5E5000000
      0000000000000000000000000000000000000000000099999900999999009999
      990099999900FFFFFF00999999009999990099999900B2B2B200000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      000099330000E5E5E500CC66000099330000E5E5E500E5E5E500E5E5E5009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC0099999900E5E5E500CCCCCC0099999900E5E5E500E5E5E500E5E5E5009999
      9900CCCCCC00CCCCCC00999999000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600336699003366990033669900E2EFF1000000
      0000000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900999999009999990099999900E2EFF1000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      000099330000E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E5009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC0099999900E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E5009999
      9900CCCCCC00CCCCCC00999999000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCCC000099CC00FFFFFF00FFCC
      CC000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000C0C0C00099999900FFFFFF00CCCC
      CC00000000000000000000000000000000000000000099330000CC660000CC66
      0000CC660000993300009933000099330000993300009933000099330000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00999999009999990099999900999999009999990099999900CCCC
      CC00CCCCCC00CCCCCC00999999000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCFF003399CC00FFCCCC00CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000CCCCCC0099999900CCCCCC009999
      9900000000000000000000000000000000000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC660000CC660000CC660000CC660000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00999999000000000099666600FFCC9900CC999900CC99
      6600FFCCCC00FFFFFF009966660099CCCC0099CCFF00B2B2B200FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000999999009999
      9900CCCCCC00FFFFFF0099999900CCCCCC00CCCCCC00B2B2B200999999009999
      9900000000000000000000000000000000000000000099330000CC660000CC66
      0000993300009933000099330000993300009933000099330000993300009933
      0000CC660000CC66000099330000000000000000000099999900CCCCCC00CCCC
      CC00999999009999990099999900999999009999990099999900999999009999
      9900CCCCCC00CCCCCC00999999000000000099666600FFCC990099666600FFFF
      FF00FFCCCC00FFFFFF009966660099CCCC00C0C0C000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C00066666600FFFF
      FF00CCCCCC00FFFFFF0099999900CCCCCC00C0C0C00099999900999999009999
      9900999999009999990099999900000000000000000099330000CC6600009933
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099330000CC66000099330000000000000000000099999900CCCCCC009999
      9900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099999900CCCCCC00999999000000000099666600FFCC9900CC9999009966
      6600FFCCCC00FFFFFF009966660000000000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000999999006666
      6600CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000099330000CC6600009933
      0000FFFFFF00993300009933000099330000993300009933000099330000FFFF
      FF0099330000CC66000099330000000000000000000099999900CCCCCC009999
      9900FFFFFF00999999009999990099999900999999009999990099999900FFFF
      FF0099999900CCCCCC00999999000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660000000000CC999900CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000099330000CC6600009933
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099330000CC66000099330000000000000000000099999900CCCCCC009999
      9900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099999900CCCCCC00999999000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00E2EFF100CC999900FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E2EFF10099999900999999009999
      9900000000000000000000000000000000000000000099330000E5E5E5009933
      0000FFFFFF00993300009933000099330000993300009933000099330000FFFF
      FF00993300009933000099330000000000000000000099999900E5E5E5009999
      9900FFFFFF00999999009999990099999900999999009999990099999900FFFF
      FF009999990099999900999999000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660099CCCC000000000099CCCC00FFCC9900CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E500CCCCCC00C0C0C0009999
      9900000000000000000000000000000000000000000099330000CC6600009933
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099330000CC66000099330000000000000000000099999900CCCCCC009999
      9900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0099999900CCCCCC00999999000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00000000003399CC0000000000FFCC
      9900000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E5009999990000000000C0C0
      C000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000099330000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900999999000000000000000000C0C0C000CC996600CC99
      9900CCCC9900FFFFFF00996666000099CC000099CC000099CC00000000000000
      00000000000000000000000000000000000000000000C0C0C000999999009999
      9900C0C0C000FFFFFF0099999900999999009999990099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00CC9999009966660099666600000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC00999999009999990099999900000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000200000000100010000000000000100000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFF000000008000800000000000
      8000800000000000800080000000000080008000000000008000800000000000
      8000800000000000800080000000000080008000000000008000800000000000
      8000800000000000800080000000000080008000000000008000800000000000
      80008000000000008000800000000000FFFFFFFFFDFFFDFFC001C001E0FFE8FF
      80018001801FA05F80018001001F803F80018001001F001F80018001000F000F
      80018001000F000F80018001000F000F80018001000100018001800101010001
      800180010101000180018001000F000F80018001008F000F8001800100AF002F
      80018001803F803FFFFFFFFFE1FFE1FF00000000000000000000000000000000
      000000000000}
  end
  object aquery: TADOQuery
    LockType = ltBatchOptimistic
    Parameters = <>
    Left = 416
    Top = 400
  end
  object ds: TDataSource
    DataSet = aquery
    Left = 376
    Top = 328
  end
  object aqinsert: TADOQuery
    Parameters = <
      item
        Name = '@type'
        DataType = ftInteger
        Value = Null
      end>
    SQL.Strings = (
      
        'select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.use' +
        'rdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.pric' +
        'e,A.Unavailable,A.date,A.Type,'
      
        ' A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.du' +
        'okannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,' +
        'A.PressCount,'
      
        ' B.abbreviatedname,C.name as typename from bs_bookcatalog A left' +
        ' join BS_PressInfo B '
      
        '  on A.pressid = B.ID left join BS_BookType C on A.smallbooktype' +
        'id = C.ID'
      ' where  and A.type = 1 and unavailable =1 and 1 = 2')
    Left = 256
    Top = 24
  end
  object dsinsert: TDataSource
    DataSet = aqinsert
    Left = 248
    Top = 328
  end
end
