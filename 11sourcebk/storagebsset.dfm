object frmstoragebsset: Tfrmstoragebsset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #20837#24211#19994#21153#25511#21046
  ClientHeight = 342
  ClientWidth = 565
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poMainFormCenter
  Visible = True
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 565
    Height = 342
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    Ctl3D = False
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 0
    object sbok: TSpeedButton
      Left = 358
      Top = 303
      Width = 88
      Height = 33
      Caption = #30830#23450
      OnClick = sbokClick
    end
    object sbcancel: TSpeedButton
      Left = 456
      Top = 303
      Width = 89
      Height = 33
      Caption = #21462#28040
      OnClick = sbcancelClick
    end
    object GroupBox1: TGroupBox
      Left = 4
      Top = 4
      Width = 541
      Height = 293
      Caption = #20837#24211#19994#21153#25511#21046
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 0
      object Label1: TLabel
        Left = 319
        Top = 91
        Width = 60
        Height = 13
        Caption = #23567#25968#28857#20301#25968
      end
      object Label2: TLabel
        Left = 438
        Top = 91
        Width = 90
        Height = 13
        Caption = #65288#26368#22810#35774#32622'4'#20301#65289
      end
      object 进退货明细: TLabel
        Left = 319
        Top = 174
        Width = 112
        Height = 13
        Caption = #36827'/'#36864#36135#26126#32454#35760#24405#22825#25968
      end
      object Label3: TLabel
        Left = 24
        Top = 272
        Width = 132
        Height = 13
        Caption = #39044#35745#25209#38144#25240#25187#20197#20309#31181#20248#20808
      end
      object Label4: TLabel
        Left = 24
        Top = 91
        Width = 132
        Height = 13
        Caption = #26412#26399#20837#24211#36864#36135#29575#35745#31639#26102#38388
      end
      object Label5: TLabel
        Left = 222
        Top = 91
        Width = 12
        Height = 13
        Caption = #26376
      end
      object cbsameid: TCheckBox
        Left = 24
        Top = 24
        Width = 97
        Height = 17
        Caption = #20801#35768#37325#22797#24405#20837
        TabOrder = 0
      end
      object cborder: TCheckBox
        Left = 183
        Top = 24
        Width = 113
        Height = 17
        Caption = #26377#35746#36135#35760#24405#25552#31034
        TabOrder = 1
        Visible = False
      end
      object cbauto: TCheckBox
        Left = 24
        Top = 47
        Width = 154
        Height = 17
        Caption = #33258#21160#27880#38144#37319#36141#35760#24405
        TabOrder = 2
      end
      object cbtrace: TCheckBox
        Left = 24
        Top = 226
        Width = 129
        Height = 17
        Caption = #36319#36394#19978#27425#20837#24211#25240#25187
        TabOrder = 3
      end
      object etdot: TEdit
        Left = 397
        Top = 88
        Width = 35
        Height = 21
        MaxLength = 1
        NumbersOnly = True
        TabOrder = 4
      end
      object cbstoragehistory: TCheckBox
        Left = 24
        Top = 174
        Width = 170
        Height = 17
        Caption = #26174#31034#21382#21490#36827'/'#36864#36135#26126#32454
        TabOrder = 5
      end
      object edstorageday: TEdit
        Left = 438
        Top = 171
        Width = 49
        Height = 21
        NumbersOnly = True
        TabOrder = 6
      end
      object cbadddotenable: TCheckBox
        Left = 319
        Top = 226
        Width = 217
        Height = 17
        Caption = #39044#35745#25209#38144#25240#25187#26159#21542#21551#29992#38468#21152#28857#35774#32622
        TabOrder = 7
      end
      object cblastyjpxdiscount: TCheckBox
        Left = 24
        Top = 249
        Width = 145
        Height = 17
        Caption = #36319#36394#19978#27425#39044#35745#25209#38144#25240#25187
        TabOrder = 8
      end
      object cblastyjpx: TCheckBox
        Left = 238
        Top = 268
        Width = 122
        Height = 17
        Caption = #19978#27425#39044#35745#25209#38144#25240#25187
        Checked = True
        State = cbChecked
        TabOrder = 9
        OnClick = cblastyjpxClick
      end
      object cbadddot: TCheckBox
        Left = 416
        Top = 268
        Width = 82
        Height = 17
        Caption = #38468#21152#28857#35774#32622
        TabOrder = 10
        OnClick = cbadddotClick
      end
      object cbrkallsupplier: TCheckBox
        Left = 24
        Top = 197
        Width = 233
        Height = 17
        Caption = #20837#24211#26126#32454#26174#31034#25152#26377#20379#24212#21830#30340#21382#21490#35760#24405
        TabOrder = 11
      end
      object cbrkusefind: TCheckBox
        Left = 319
        Top = 122
        Width = 177
        Height = 17
        Caption = #21551#29992#20837#24211#26597#21333#23494#30721
        TabOrder = 12
      end
      object cbrkusedelete: TCheckBox
        Left = 24
        Top = 122
        Width = 209
        Height = 17
        Caption = #21551#29992#20837#24211#21024#21333#23494#30721
        TabOrder = 13
      end
      object cbrkusetuihuo: TCheckBox
        Left = 24
        Top = 143
        Width = 169
        Height = 17
        Caption = #21551#29992#20837#24211#36864#36135#23494#30721
        TabOrder = 14
      end
      object chmutisupplier: TCheckBox
        Left = 319
        Top = 47
        Width = 114
        Height = 17
        Caption = #21551#29992#22810#36135#28304
        TabOrder = 15
      end
      object chdeletestack: TCheckBox
        Left = 24
        Top = 70
        Width = 169
        Height = 17
        Caption = #26377#24211#23384#24341#29992#21487#21024#38500#24211#20301
        TabOrder = 16
      end
      object edmonth: TEdit
        Left = 167
        Top = 88
        Width = 49
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 17
        Text = '3'
      end
      object GroupBox4: TGroupBox
        Left = 24
        Top = 109
        Width = 521
        Height = 7
        TabOrder = 18
      end
      object GroupBox5: TGroupBox
        Left = 24
        Top = 161
        Width = 521
        Height = 7
        TabOrder = 19
      end
      object cbrkusechange: TCheckBox
        Left = 319
        Top = 143
        Width = 169
        Height = 17
        Caption = #21551#29992#20837#24211#20462#25913#21333#22836#23494#30721
        TabOrder = 20
      end
      object GroupBox3: TGroupBox
        Left = 24
        Top = 214
        Width = 521
        Height = 7
        TabOrder = 21
      end
      object cblastyjlsdiscount: TCheckBox
        Left = 319
        Top = 249
        Width = 145
        Height = 17
        Caption = #36319#36394#19978#27425#39044#35745#38646#21806#25240#25187
        TabOrder = 22
      end
      object chstoragesametishi: TCheckBox
        Left = 319
        Top = 24
        Width = 113
        Height = 17
        Caption = #37325#22797#24405#20837#25552#37266
        TabOrder = 23
      end
      object chrktuihuoguanli: TCheckBox
        Left = 318
        Top = 70
        Width = 114
        Height = 17
        Caption = #21551#29992#36864#36135#30417#31649
        TabOrder = 24
      end
    end
  end
  object aquery: TADOQuery
    Parameters = <>
    Left = 624
    Top = 296
  end
  object qryretairange: TADOQuery
    Parameters = <>
    Left = 488
    Top = 416
  end
  object dsrcretairange: TDataSource
    DataSet = qryretairange
    Left = 584
    Top = 368
  end
end
