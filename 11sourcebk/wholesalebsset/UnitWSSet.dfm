object frmwsset: Tfrmwsset
  Left = 366
  Top = 200
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #20449#29992#31649#29702
  ClientHeight = 529
  ClientWidth = 787
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  Visible = True
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 29
    Width = 787
    Height = 500
    Align = alClient
    BevelInner = bvLowered
    Caption = 'Panel1'
    Color = 16180174
    Ctl3D = False
    ParentBackground = False
    ParentCtl3D = False
    ShowCaption = False
    TabOrder = 0
    object pc: TPageControl
      Left = 2
      Top = 2
      Width = 783
      Height = 496
      ActivePage = TS1
      Align = alClient
      Style = tsFlatButtons
      TabOrder = 0
      OnChange = pcChange
      object TS1: TTabSheet
        Tag = 1
        Caption = #23458#25143#20449#29992#39069#24230#35774#32622
        object GroupBox1: TGroupBox
          Left = 3
          Top = 3
          Width = 561
          Height = 158
          TabOrder = 0
          object Label1: TLabel
            Left = 32
            Top = 26
            Width = 48
            Height = 13
            Caption = #23458#25143#21517#31216
          end
          object spsearch: TSpeedButton
            Left = 511
            Top = 24
            Width = 23
            Height = 19
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
            OnClick = spsearchClick
          end
          object Label2: TLabel
            Left = 8
            Top = 66
            Width = 72
            Height = 13
            Caption = #25552#31034#20449#29992#39069#24230
          end
          object Label3: TLabel
            Left = 256
            Top = 66
            Width = 96
            Height = 13
            Caption = #38145#23450#21457#36135#20449#29992#39069#24230
          end
          object Label4: TLabel
            Left = 32
            Top = 100
            Width = 48
            Height = 13
            Caption = #21551#22987#26085#26399
          end
          object Label5: TLabel
            Left = 304
            Top = 100
            Width = 48
            Height = 13
            Caption = #32456#27490#26085#26399
          end
          object editclientname: TEdit
            Left = 86
            Top = 24
            Width = 427
            Height = 19
            TabOrder = 0
            OnKeyPress = editclientnameKeyPress
          end
          object editalarmcredit: TEdit
            Left = 86
            Top = 64
            Width = 152
            Height = 19
            Alignment = taRightJustify
            NumbersOnly = True
            TabOrder = 1
            Text = '0'
            OnExit = editalarmcreditExit
            OnKeyPress = editalarmcreditKeyPress
          end
          object editlockcredit: TEdit
            Left = 358
            Top = 64
            Width = 155
            Height = 19
            Alignment = taRightJustify
            NumbersOnly = True
            TabOrder = 2
            Text = '0'
            OnExit = editlockcreditExit
            OnKeyPress = editlockcreditKeyPress
          end
          object cridetbegin: TDateTimePicker
            Left = 86
            Top = 98
            Width = 152
            Height = 21
            Date = 40156.409092881940000000
            Time = 40156.409092881940000000
            TabOrder = 3
            OnKeyPress = cridetbeginKeyPress
          end
          object creditend: TDateTimePicker
            Left = 358
            Top = 98
            Width = 155
            Height = 21
            Date = 40156.409522743060000000
            Time = 40156.409522743060000000
            TabOrder = 4
            OnKeyPress = creditendKeyPress
          end
          object cbbalance: TCheckBox
            Left = 86
            Top = 132
            Width = 169
            Height = 17
            Caption = #20449#29992#39069#24230#21253#21547#23458#25143#20313#39069
            TabOrder = 5
            OnKeyPress = cbbalanceKeyPress
          end
        end
        object DBGrid1: TDBGrid
          Left = 3
          Top = 175
          Width = 699
          Height = 274
          FixedColor = 16180174
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
          ParentFont = False
          PopupMenu = pm
          TabOrder = 1
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clNavy
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
          OnCellClick = DBGrid1CellClick
          Columns = <
            item
              Expanded = False
              FieldName = 'Name'
              Title.Alignment = taCenter
              Title.Caption = #23458#25143#21517#31216
              Width = 130
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'proCredit'
              Title.Alignment = taCenter
              Title.Caption = #25552#31034#20449#29992#39069#24230
              Width = 80
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'LocalDeliveryCredit'
              Title.Alignment = taCenter
              Title.Caption = #38145#23450#21457#36135#20449#29992#39069#24230
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'Creditstartdate'
              Title.Alignment = taCenter
              Title.Caption = #21551#22987#26085#26399
              Width = 73
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'Creditenddate'
              Title.Alignment = taCenter
              Title.Caption = #32456#27490#26085#26399
              Width = 71
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'clientblance'
              Title.Alignment = taCenter
              Title.Caption = #20449#29992#39069#24230#21253#21547#23458#25143#20313#39069
              Width = 130
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'active'
              Title.Alignment = taCenter
              Title.Caption = #26159#21542#26377#25928
              Width = 90
              Visible = True
            end>
        end
        object GroupBox2: TGroupBox
          Left = 556
          Top = 3
          Width = 146
          Height = 158
          TabOrder = 2
          object creditsave: TSpeedButton
            Left = 24
            Top = 63
            Width = 105
            Height = 25
            Caption = #20445#23384
            OnClick = creditsaveClick
          end
          object creditenable: TSpeedButton
            Left = 24
            Top = 110
            Width = 105
            Height = 25
            Caption = #32622#20026#26377#25928
            OnClick = creditenableClick
          end
          object crditadd: TSpeedButton
            Left = 24
            Top = 22
            Width = 105
            Height = 25
            Caption = #26032#22686
            OnClick = crditaddClick
          end
        end
      end
      object TS2: TTabSheet
        Tag = 2
        Caption = #22238#27454#29575#35774#32622
        ImageIndex = 2
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object GroupBox9: TGroupBox
          Left = 3
          Top = 3
          Width = 561
          Height = 142
          TabOrder = 0
          object Label23: TLabel
            Left = 32
            Top = 26
            Width = 48
            Height = 13
            Caption = #23458#25143#21517#31216
          end
          object SpeedButton4: TSpeedButton
            Left = 511
            Top = 24
            Width = 23
            Height = 19
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
            OnClick = SpeedButton4Click
          end
          object Label24: TLabel
            Left = 20
            Top = 55
            Width = 60
            Height = 13
            Caption = #26376#24230#22238#27454#29575
          end
          object Label25: TLabel
            Left = 292
            Top = 55
            Width = 60
            Height = 13
            Caption = #24180#24230#22238#27454#29575
          end
          object Label26: TLabel
            Left = 20
            Top = 87
            Width = 60
            Height = 13
            Caption = #25552#31034#22238#27454#29575
          end
          object Label27: TLabel
            Left = 270
            Top = 87
            Width = 84
            Height = 13
            Caption = #38145#23450#21457#36135#22238#27454#29575
          end
          object Label33: TLabel
            Left = 30
            Top = 119
            Width = 48
            Height = 13
            Caption = #21551#22987#26085#26399
          end
          object Label34: TLabel
            Left = 304
            Top = 119
            Width = 48
            Height = 13
            Caption = #32456#27490#26085#26399
          end
          object backclientname: TEdit
            Left = 86
            Top = 24
            Width = 427
            Height = 19
            TabOrder = 0
            OnKeyPress = backclientnameKeyPress
          end
          object monthbakarate: TEdit
            Left = 86
            Top = 53
            Width = 152
            Height = 19
            Alignment = taRightJustify
            TabOrder = 1
            Text = '0'
            OnExit = monthbakarateExit
            OnKeyPress = monthbakarateKeyPress
          end
          object yearbackrate: TEdit
            Left = 358
            Top = 53
            Width = 155
            Height = 19
            Alignment = taRightJustify
            TabOrder = 2
            Text = '0'
            OnExit = yearbackrateExit
            OnKeyPress = yearbackrateKeyPress
          end
          object probackrate: TEdit
            Left = 86
            Top = 85
            Width = 152
            Height = 19
            Alignment = taRightJustify
            TabOrder = 3
            Text = '0'
            OnExit = probackrateExit
            OnKeyPress = probackrateKeyPress
          end
          object localdeliverybackrate: TEdit
            Left = 358
            Top = 85
            Width = 155
            Height = 19
            Alignment = taRightJustify
            TabOrder = 4
            Text = '0'
            OnExit = localdeliverybackrateExit
            OnKeyPress = localdeliverybackrateKeyPress
          end
          object dtpbackbegin: TDateTimePicker
            Left = 84
            Top = 114
            Width = 152
            Height = 21
            Date = 40156.452706886570000000
            Time = 40156.452706886570000000
            TabOrder = 5
            OnKeyPress = dtpbackbeginKeyPress
          end
          object dtpbackend: TDateTimePicker
            Left = 358
            Top = 114
            Width = 155
            Height = 21
            Date = 40156.453607488420000000
            Time = 40156.453607488420000000
            TabOrder = 6
            OnKeyPress = dtpbackendKeyPress
          end
        end
        object DBGrid2: TDBGrid
          Left = 3
          Top = 162
          Width = 699
          Height = 303
          FixedColor = 16180174
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
          ParentFont = False
          PopupMenu = pm
          TabOrder = 1
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clNavy
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
          OnCellClick = DBGrid2CellClick
          Columns = <
            item
              Expanded = False
              FieldName = 'Name'
              Title.Alignment = taCenter
              Title.Caption = #23458#25143#21517#31216
              Width = 120
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'monthbackrate'
              Title.Alignment = taCenter
              Title.Caption = #26376#24230#22238#27454#29575
              Width = 74
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'yearbackrate'
              Title.Alignment = taCenter
              Title.Caption = #24180#24230#22238#27454#29575
              Width = 74
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'probackrate'
              Title.Alignment = taCenter
              Title.Caption = #25552#31034#22238#27454#29575
              Width = 76
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'localDeliverybackrate'
              Title.Alignment = taCenter
              Title.Caption = #38145#23450#21457#36135#22238#27454#29575
              Width = 96
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'backratestartdate'
              Title.Alignment = taCenter
              Title.Caption = #36215#22987#26102#38388
              Width = 62
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'backrateenddate'
              Title.Alignment = taCenter
              Title.Caption = #32456#27490#26102#38388
              Width = 59
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'active'
              Title.Alignment = taCenter
              Title.Caption = #26159#21542#26377#25928
              Width = 66
              Visible = True
            end>
        end
        object GroupBox10: TGroupBox
          Left = 556
          Top = 3
          Width = 146
          Height = 142
          TabOrder = 2
          object backadd: TSpeedButton
            Left = 24
            Top = 24
            Width = 105
            Height = 25
            Caption = #26032#22686
            OnClick = backaddClick
          end
          object backsave: TSpeedButton
            Left = 24
            Top = 61
            Width = 105
            Height = 25
            Caption = #20445#23384
            OnClick = backsaveClick
          end
          object backactive: TSpeedButton
            Left = 24
            Top = 96
            Width = 105
            Height = 25
            Caption = #32622#20026#26377#25928
            OnClick = backactiveClick
          end
        end
      end
      object TS3: TTabSheet
        Tag = 3
        Caption = #36864#36135#29575#25353#23458#25143#35774#32622
        ImageIndex = 1
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object GroupBox3: TGroupBox
          Left = 0
          Top = 0
          Width = 561
          Height = 158
          TabOrder = 0
          object lb: TLabel
            Left = 24
            Top = 24
            Width = 48
            Height = 13
            Caption = #23458#25143#21517#31216
          end
          object Label6: TLabel
            Left = 12
            Top = 58
            Width = 60
            Height = 13
            Caption = #25552#31034#36864#36135#29575
          end
          object Label7: TLabel
            Left = 232
            Top = 59
            Width = 84
            Height = 13
            Caption = #38145#23450#36864#36135#36864#36135#29575
          end
          object Label8: TLabel
            Left = 24
            Top = 90
            Width = 48
            Height = 13
            Caption = #21551#22987#26085#26399
          end
          object Label9: TLabel
            Left = 266
            Top = 94
            Width = 48
            Height = 13
            Caption = #32456#27490#26085#26399
          end
          object spclientsearch: TSpeedButton
            Left = 464
            Top = 21
            Width = 25
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
            OnClick = spclientsearchClick
          end
          object returnclientname: TEdit
            Left = 80
            Top = 22
            Width = 385
            Height = 19
            TabOrder = 0
            OnKeyPress = returnclientnameKeyPress
          end
          object proreturnrate: TEdit
            Left = 82
            Top = 56
            Width = 131
            Height = 19
            Alignment = taRightJustify
            TabOrder = 1
            Text = '0'
            OnExit = proreturnrateExit
            OnKeyPress = proreturnrateKeyPress
          end
          object localreturnrate: TEdit
            Left = 322
            Top = 56
            Width = 143
            Height = 19
            Alignment = taRightJustify
            TabOrder = 2
            Text = '0'
            OnExit = localreturnrateExit
            OnKeyPress = localreturnrateKeyPress
          end
          object returnbegin: TDateTimePicker
            Left = 80
            Top = 88
            Width = 131
            Height = 21
            Date = 40156.452706886570000000
            Time = 40156.452706886570000000
            TabOrder = 3
            OnKeyPress = returnbeginKeyPress
          end
          object returnend: TDateTimePicker
            Left = 320
            Top = 90
            Width = 145
            Height = 21
            Date = 40156.453607488420000000
            Time = 40156.453607488420000000
            TabOrder = 4
            OnKeyPress = returnendKeyPress
          end
        end
        object GroupBox4: TGroupBox
          Left = 560
          Top = 0
          Width = 142
          Height = 158
          TabOrder = 1
          object returnadd: TSpeedButton
            Left = 29
            Top = 22
            Width = 97
            Height = 25
            Caption = #26032#22686
            OnClick = returnaddClick
          end
          object returnsave: TSpeedButton
            Left = 29
            Top = 67
            Width = 97
            Height = 25
            Caption = #20445#23384
            OnClick = returnsaveClick
          end
          object returnactive: TSpeedButton
            Left = 29
            Top = 112
            Width = 97
            Height = 25
            Caption = #32622#20026#26377#25928
            OnClick = returnactiveClick
          end
        end
        object DBGrid3: TDBGrid
          Left = 3
          Top = 176
          Width = 699
          Height = 287
          FixedColor = 16180174
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
          ParentFont = False
          PopupMenu = pm
          TabOrder = 2
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clNavy
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
          OnCellClick = DBGrid3CellClick
          Columns = <
            item
              Expanded = False
              FieldName = 'Name'
              Title.Alignment = taCenter
              Title.Caption = #23458#25143#21517#31216
              Width = 135
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'proreturnrate'
              Title.Alignment = taCenter
              Title.Caption = #25552#31034#36864#36135#29575
              Width = 67
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'localreturnrate'
              Title.Alignment = taCenter
              Title.Caption = #38145#23450#36864#36135#29575
              Width = 66
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'returnratestartdate'
              Title.Alignment = taCenter
              Title.Caption = #21551#22987#26085#26399
              Width = 68
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'returnrateenddate'
              Title.Alignment = taCenter
              Title.Caption = #32456#27490#26085#26399
              Width = 66
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'active'
              Title.Alignment = taCenter
              Title.Caption = #26159#21542#26377#25928
              Visible = True
            end>
        end
      end
      object TS4: TTabSheet
        Tag = 4
        Caption = #36864#36135#29575#25353#31867#21035#35774#32622
        ImageIndex = 3
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object GroupBox5: TGroupBox
          Left = 0
          Top = 3
          Width = 561
          Height = 153
          TabOrder = 0
          object Label10: TLabel
            Left = 24
            Top = 32
            Width = 48
            Height = 13
            Caption = #22270#20070#31867#21035
          end
          object Label11: TLabel
            Left = 10
            Top = 66
            Width = 60
            Height = 13
            Caption = #25552#31034#36864#36135#29575
          end
          object Label12: TLabel
            Left = 255
            Top = 67
            Width = 84
            Height = 13
            Caption = #38145#23450#36864#36135#36864#36135#29575
          end
          object Label13: TLabel
            Left = 22
            Top = 98
            Width = 48
            Height = 13
            Caption = #21551#22987#26085#26399
          end
          object Label14: TLabel
            Left = 289
            Top = 102
            Width = 48
            Height = 13
            Caption = #32456#27490#26085#26399
          end
          object typereturnrate: TEdit
            Left = 78
            Top = 64
            Width = 166
            Height = 19
            Alignment = taRightJustify
            TabOrder = 0
            Text = '0'
            OnExit = typereturnrateExit
            OnKeyPress = typereturnrateKeyPress
          end
          object localtypereturnrate: TEdit
            Left = 345
            Top = 64
            Width = 178
            Height = 19
            Alignment = taRightJustify
            TabOrder = 1
            Text = '0'
            OnExit = localtypereturnrateExit
            OnKeyPress = localtypereturnrateKeyPress
          end
          object typestart: TDateTimePicker
            Left = 76
            Top = 98
            Width = 166
            Height = 21
            Date = 40156.452706886570000000
            Time = 40156.452706886570000000
            TabOrder = 2
            OnKeyPress = typestartKeyPress
          end
          object typeend: TDateTimePicker
            Left = 343
            Top = 98
            Width = 180
            Height = 21
            Date = 40156.453607488420000000
            Time = 40156.453607488420000000
            TabOrder = 3
            OnKeyPress = typeendKeyPress
          end
          object cbbooktype: TComboBox
            Left = 78
            Top = 28
            Width = 445
            Height = 21
            ItemHeight = 0
            TabOrder = 4
            OnClick = cbbooktypeClick
            OnKeyPress = cbbooktypeKeyPress
          end
        end
        object DBGrid4: TDBGrid
          Left = 0
          Top = 176
          Width = 702
          Height = 287
          FixedColor = 16180174
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
          ParentFont = False
          PopupMenu = pm
          TabOrder = 1
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clNavy
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
          OnCellClick = DBGrid4CellClick
          Columns = <
            item
              Expanded = False
              FieldName = 'Name'
              Title.Alignment = taCenter
              Title.Caption = #22270#20070#31867#21035#21517#31216
              Width = 120
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'protypereturnrate'
              Title.Alignment = taCenter
              Title.Caption = #25552#31034#36864#36135#29575
              Width = 74
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'localtypereturnrate'
              Title.Alignment = taCenter
              Title.Caption = #38145#23450#36864#36135#29575
              Width = 78
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'typereturnstaetdate'
              Title.Alignment = taCenter
              Title.Caption = #21551#22987#26085#26399
              Width = 68
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'typereturnenddate'
              Title.Alignment = taCenter
              Title.Caption = #32456#27490#26085#26399
              Width = 68
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'active'
              Title.Alignment = taCenter
              Title.Caption = #26159#21542#26377#25928
              Width = 66
              Visible = True
            end>
        end
        object GroupBox6: TGroupBox
          Left = 560
          Top = 3
          Width = 142
          Height = 153
          TabOrder = 2
          object typeadd: TSpeedButton
            Left = 10
            Top = 30
            Width = 113
            Height = 25
            Caption = #26032#22686
            OnClick = typeaddClick
          end
          object typesave: TSpeedButton
            Left = 14
            Top = 66
            Width = 113
            Height = 25
            Caption = #20445#23384
            OnClick = typesaveClick
          end
          object typeactive: TSpeedButton
            Left = 14
            Top = 108
            Width = 113
            Height = 25
            Caption = #32622#20026#26377#25928
            OnClick = typeactiveClick
          end
        end
      end
      object TS5: TTabSheet
        Tag = 5
        Caption = #36864#36135#29575#25353#21333#21697
        ImageIndex = 4
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object GroupBox7: TGroupBox
          Left = 0
          Top = 3
          Width = 634
          Height = 166
          TabOrder = 0
          object Label15: TLabel
            Left = 32
            Top = 32
            Width = 24
            Height = 13
            Caption = #20070#21495
          end
          object Label16: TLabel
            Left = 10
            Top = 82
            Width = 60
            Height = 13
            Caption = #25552#31034#36864#36135#29575
          end
          object Label17: TLabel
            Left = 255
            Top = 83
            Width = 84
            Height = 13
            Caption = #38145#23450#36864#36135#36864#36135#29575
          end
          object Label18: TLabel
            Left = 22
            Top = 114
            Width = 48
            Height = 13
            Caption = #21551#22987#26085#26399
          end
          object Label19: TLabel
            Left = 289
            Top = 118
            Width = 48
            Height = 13
            Caption = #32456#27490#26085#26399
          end
          object Label20: TLabel
            Left = 32
            Top = 57
            Width = 24
            Height = 13
            Caption = #20070#21517
          end
          object Label21: TLabel
            Left = 216
            Top = 32
            Width = 24
            Height = 13
            Caption = #23450#20215
          end
          object Label22: TLabel
            Left = 384
            Top = 32
            Width = 36
            Height = 13
            Caption = #20986#29256#31038
          end
          object edBarcode: TEdit
            Left = 76
            Top = 30
            Width = 115
            Height = 19
            TabOrder = 0
            OnKeyPress = edBarcodeKeyPress
          end
          object bookproreturnrate: TEdit
            Left = 76
            Top = 80
            Width = 166
            Height = 19
            Alignment = taRightJustify
            TabOrder = 1
            Text = '0'
            OnExit = bookproreturnrateExit
            OnKeyPress = bookproreturnrateKeyPress
          end
          object localbookreturnrate: TEdit
            Left = 345
            Top = 80
            Width = 178
            Height = 19
            Alignment = taRightJustify
            TabOrder = 2
            Text = '0'
            OnExit = localbookreturnrateExit
            OnKeyPress = localbookreturnrateKeyPress
          end
          object bookbegin: TDateTimePicker
            Left = 78
            Top = 112
            Width = 166
            Height = 21
            Date = 40156.452706886570000000
            Time = 40156.452706886570000000
            TabOrder = 3
            OnKeyPress = bookbeginKeyPress
          end
          object bookend: TDateTimePicker
            Left = 343
            Top = 114
            Width = 180
            Height = 21
            Date = 40156.453607488420000000
            Time = 40156.453607488420000000
            TabOrder = 4
            OnKeyPress = bookendKeyPress
          end
          object edbookname: TEdit
            Left = 76
            Top = 55
            Width = 447
            Height = 19
            TabOrder = 5
          end
          object edprice: TEdit
            Left = 246
            Top = 30
            Width = 121
            Height = 19
            TabOrder = 6
          end
          object edpress: TEdit
            Left = 426
            Top = 30
            Width = 97
            Height = 19
            TabOrder = 7
          end
        end
        object GroupBox8: TGroupBox
          Left = 624
          Top = 3
          Width = 142
          Height = 166
          TabOrder = 1
          object bookadd: TSpeedButton
            Left = 16
            Top = 29
            Width = 113
            Height = 25
            Caption = #26032#22686
            OnClick = bookaddClick
          end
          object booksave: TSpeedButton
            Left = 16
            Top = 71
            Width = 113
            Height = 25
            Caption = #20445#23384
            OnClick = booksaveClick
          end
          object bookactive: TSpeedButton
            Left = 16
            Top = 114
            Width = 113
            Height = 25
            Caption = #32622#20026#26377#25928
            OnClick = bookactiveClick
          end
        end
        object DBGrid5: TDBGrid
          Left = 0
          Top = 183
          Width = 766
          Height = 281
          FixedColor = 16180174
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
          ParentFont = False
          PopupMenu = pm
          TabOrder = 2
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clNavy
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
          OnCellClick = DBGrid5CellClick
          Columns = <
            item
              Expanded = False
              FieldName = 'ISBN'
              Title.Alignment = taCenter
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'Name'
              Title.Alignment = taCenter
              Title.Caption = #20070#21517
              Width = 130
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'Price'
              Title.Alignment = taCenter
              Title.Caption = #23450#20215
              Width = 48
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'Author'
              Title.Alignment = taCenter
              Title.Caption = #20316#32773
              Width = 54
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'AbbreviatedName'
              Title.Alignment = taCenter
              Title.Caption = #29256#21035
              Width = 87
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'probookreturnrate'
              Title.Alignment = taCenter
              Title.Caption = #25552#31034#36864#36135#29575
              Width = 67
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'localbookreturnrate'
              Title.Alignment = taCenter
              Title.Caption = #38145#23450#36864#36135#29575
              Width = 68
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'bookreturnstartdate'
              Title.Alignment = taCenter
              Title.Caption = #21551#22987#26085#26399
              Width = 83
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'bookreturnenddate'
              Title.Alignment = taCenter
              Title.Caption = #32456#27490#26085#26399
              Width = 76
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'active'
              Title.Alignment = taCenter
              Title.Caption = #26159#21542#26377#25928
              Width = 58
              Visible = True
            end>
        end
      end
      object TS6: TTabSheet
        Tag = 6
        Caption = #36864#36135#29575#25353#29256#21035
        ImageIndex = 5
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object GroupBox11: TGroupBox
          Left = 0
          Top = 3
          Width = 641
          Height = 153
          TabOrder = 0
          object Label28: TLabel
            Left = 46
            Top = 32
            Width = 24
            Height = 13
            Caption = #29256#21035
          end
          object Label29: TLabel
            Left = 10
            Top = 66
            Width = 60
            Height = 13
            Caption = #25552#31034#36864#36135#29575
          end
          object Label30: TLabel
            Left = 255
            Top = 67
            Width = 84
            Height = 13
            Caption = #38145#23450#36864#36135#36864#36135#29575
          end
          object Label31: TLabel
            Left = 22
            Top = 98
            Width = 48
            Height = 13
            Caption = #21551#22987#26085#26399
          end
          object Label32: TLabel
            Left = 289
            Top = 102
            Width = 48
            Height = 13
            Caption = #32456#27490#26085#26399
          end
          object pressreturnrate: TEdit
            Left = 76
            Top = 64
            Width = 166
            Height = 19
            Alignment = taRightJustify
            TabOrder = 0
            Text = '0'
            OnExit = pressreturnrateExit
            OnKeyPress = pressreturnrateKeyPress
          end
          object localpressreturnrate: TEdit
            Left = 345
            Top = 64
            Width = 178
            Height = 19
            Alignment = taRightJustify
            TabOrder = 1
            Text = '0'
            OnExit = localpressreturnrateExit
            OnKeyPress = localpressreturnrateKeyPress
          end
          object pressstart: TDateTimePicker
            Left = 78
            Top = 96
            Width = 166
            Height = 21
            Date = 40156.452706886570000000
            Time = 40156.452706886570000000
            TabOrder = 2
            OnKeyPress = pressstartKeyPress
          end
          object pressend: TDateTimePicker
            Left = 343
            Top = 98
            Width = 180
            Height = 21
            Date = 40156.453607488420000000
            Time = 40156.453607488420000000
            TabOrder = 3
            OnKeyPress = pressendKeyPress
          end
          object cbpress: TComboBox
            Left = 78
            Top = 29
            Width = 443
            Height = 21
            ItemHeight = 0
            TabOrder = 4
            OnClick = cbpressClick
            OnKeyPress = cbpressKeyPress
          end
        end
        object DBGrid6: TDBGrid
          Left = 0
          Top = 176
          Width = 689
          Height = 287
          FixedColor = 16180174
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
          ParentFont = False
          PopupMenu = pm
          TabOrder = 1
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clNavy
          TitleFont.Height = -11
          TitleFont.Name = 'Tahoma'
          TitleFont.Style = []
          OnCellClick = DBGrid6CellClick
          Columns = <
            item
              Expanded = False
              FieldName = 'AbbreviatedName'
              Title.Alignment = taCenter
              Title.Caption = #22270#20070#31867#21035#21517#31216
              Width = 147
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'propressreturnrate'
              Title.Alignment = taCenter
              Title.Caption = #25552#31034#36864#36135#29575
              Width = 79
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'localpressreturnrate'
              Title.Alignment = taCenter
              Title.Caption = #38145#23450#36864#36135#29575
              Width = 74
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'pressreturnstartdate'
              Title.Alignment = taCenter
              Title.Caption = #21551#22987#26085#26399
              Width = 96
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'pressreturnenddate'
              Title.Alignment = taCenter
              Title.Caption = #32456#27490#26085#26399
              Width = 81
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'active'
              Title.Alignment = taCenter
              Title.Caption = #26159#21542#26377#25928
              Visible = True
            end>
        end
        object GroupBox12: TGroupBox
          Left = 544
          Top = 3
          Width = 145
          Height = 153
          TabOrder = 2
          object pressadd: TSpeedButton
            Left = 15
            Top = 28
            Width = 113
            Height = 25
            Caption = #26032#22686
            OnClick = pressaddClick
          end
          object presssave: TSpeedButton
            Left = 16
            Top = 68
            Width = 113
            Height = 25
            Caption = #20445#23384
            OnClick = presssaveClick
          end
          object pressactive: TSpeedButton
            Left = 17
            Top = 109
            Width = 113
            Height = 25
            Caption = #32622#20026#26377#25928
            OnClick = pressactiveClick
          end
        end
      end
    end
  end
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 787
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
    GradientColorStyle = gcsCustom
    TabOrder = 1
    VisualStyle = vsClassic
    ToolbarControls = (
      BtnAlignBottom
      BtnExit)
    object BtnAlignBottom: TRzToolButton
      Left = 4
      Top = -4
      Width = 60
      Height = 36
      Hint = 'Align Bottom'
      DisabledIndex = 1
      ImageIndex = 0
      UseToolbarButtonSize = False
      Caption = #26368#23567#21270#13'(&N)'
      OnClick = BtnAlignBottomClick
    end
    object BtnExit: TRzToolButton
      Left = 64
      Top = -4
      Width = 60
      Height = 36
      Hint = 'Exit'
      DisabledIndex = 3
      ImageIndex = 2
      UseToolbarButtonSize = False
      Caption = #36864#20986#13'(&Q)'
      OnClick = BtnExitClick
    end
  end
  object aq: TADOQuery
    LockType = ltBatchOptimistic
    Parameters = <>
    Left = 648
    Top = 256
  end
  object ds: TDataSource
    DataSet = aq
    Left = 352
    Top = 328
  end
  object pm: TPopupMenu
    Left = 680
    Top = 16
    object N1: TMenuItem
      Caption = #32622#20026#26080#25928
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #21024#38500
      OnClick = N2Click
    end
  end
  object ImageList1: TImageList
    Left = 24
    Top = 65472
    Bitmap = {
      494C010104000500100010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E2EFF100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F100E5E5E500CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E2EF
      F10000000000CCCCCC00E5E5E500E2EFF1000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900000000000000000000000000E2EFF100E5E5E500B2B2
      B200CC9999009966660099666600B2B2B200CCCCCC00E5E5E500E2EFF1000000
      00000000000000000000000000000000000000000000E2EFF10000000000B2B2
      B200999999009999990099999900B2B2B200CCCCCC0000000000E2EFF1000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00999999000000000000000000E5E5E500CC99990099666600CC99
      9900CC999900FFFFFF00996666009999990099999900B2B2B200E5E5E5000000
      0000000000000000000000000000000000000000000099999900999999009999
      990099999900FFFFFF00999999009999990099999900B2B2B200000000000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600336699003366990033669900E2EFF1000000
      0000000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900999999009999990099999900E2EFF1000000
      0000000000000000000000000000000000000000000099330000CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9966009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCCC000099CC00FFFFFF00FFCC
      CC000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000C0C0C00099999900FFFFFF00CCCC
      CC00000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300009933000099330000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      99009999990099999900000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660066CCCC0066CCFF003399CC00FFCCCC00CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900C0C0C000CCCCCC0099999900CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC9900CC999900CC99
      6600FFCCCC00FFFFFF009966660099CCCC0099CCFF00B2B2B200FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000999999009999
      9900CCCCCC00FFFFFF0099999900CCCCCC00CCCCCC00B2B2B200999999009999
      99000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000099666600FFCC990099666600FFFF
      FF00FFCCCC00FFFFFF009966660099CCCC00C0C0C000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C00066666600FFFF
      FF00CCCCCC00FFFFFF0099999900CCCCCC00C0C0C00099999900999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC9900CC9999009966
      6600FFCCCC00FFFFFF009966660000000000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000999999006666
      6600CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      99009999990099999900999999000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660000000000CC999900CC660000CC660000CC66
      0000CC660000CC660000CC6600000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900E5E5E5009999990099999900999999009999
      9900999999009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00E2EFF100CC999900FF660000CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E2EFF10099999900999999009999
      99000000000000000000000000000000000000000000CC996600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC996600000000000000000000000000CCCCCC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC00000000000000000099666600FFCC9900FFCC9900FFCC
      9900FFCCCC00FFFFFF009966660099CCCC000000000099CCCC00FFCC9900CC66
      00000000000000000000000000000000000099999900C0C0C000C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E500CCCCCC00C0C0C0009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099666600CC999900FFCC9900FFCC
      9900FFCCCC00FFFFFF0099666600CCCCCC00000000003399CC0000000000FFCC
      9900000000000000000000000000000000009999990099999900C0C0C000C0C0
      C000CCCCCC00FFFFFF0099999900CCCCCC00E5E5E5009999990000000000C0C0
      C0000000000000000000000000000000000000000000CC99660000000000CC99
      660000000000CC99660000000000CC99660000000000CC99660000000000CC99
      660000000000CC996600000000000000000000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC0000000000CCCCCC0000000000CCCCCC0000000000CCCC
      CC0000000000CCCCCC00000000000000000000000000C0C0C000CC996600CC99
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
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FFFFFFFFFDFFFDFFFFFFFFFFE0FFE8FF
      80038003801FA05F80038003001F803F80038003001F001F80038003000F000F
      80038003000F000FFFFFFFFF000F000FBFFBBFFB00010001FFFFFFFF01010001
      BFFBBFFB01010001FFFFFFFF000F000FBFFBBFFB008F000FFFFFFFFF00AF002F
      AAABAAAB803F803FFFFFFFFFE1FFE1FF00000000000000000000000000000000
      000000000000}
  end
end
