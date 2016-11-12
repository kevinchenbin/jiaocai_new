object frmsalebsset: Tfrmsalebsset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #25209#38144#19994#21153#25511#21046
  ClientHeight = 459
  ClientWidth = 664
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
    Width = 664
    Height = 459
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    Ctl3D = True
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 0
    ExplicitHeight = 437
    object sbok: TSpeedButton
      Left = 444
      Top = 418
      Width = 98
      Height = 33
      Caption = #30830#23450
      OnClick = sbokClick
    end
    object sbcancel: TSpeedButton
      Left = 553
      Top = 418
      Width = 105
      Height = 33
      Caption = #21462#28040
      OnClick = sbcancelClick
    end
    object 销售业务: TGroupBox
      Left = 6
      Top = 5
      Width = 651
      Height = 220
      Caption = #25209#38144#19994#21153
      TabOrder = 0
      object Label23: TLabel
        Left = 439
        Top = 72
        Width = 96
        Height = 13
        Caption = #25209#38144#26126#32454#35760#24405#22825#25968
      end
      object Label1: TLabel
        Left = 438
        Top = 42
        Width = 60
        Height = 13
        Caption = #23567#25968#28857#20301#25968
      end
      object Label2: TLabel
        Left = 547
        Top = 42
        Width = 90
        Height = 13
        Caption = #65288#26368#22810#35774#32622'4'#20301#65289
      end
      object Label11: TLabel
        Left = 24
        Top = 170
        Width = 132
        Height = 13
        Caption = #26412#26399#25209#38144#36864#36135#29575#35745#31639#26102#38388
      end
      object Label12: TLabel
        Left = 205
        Top = 170
        Width = 12
        Height = 13
        Caption = #26376
      end
      object Label13: TLabel
        Left = 24
        Top = 194
        Width = 72
        Height = 13
        Caption = #25209#38144#36864#36135#26399#38480
      end
      object Label14: TLabel
        Left = 158
        Top = 194
        Width = 12
        Height = 13
        Caption = #26376
      end
      object cbstorezero: TCheckBox
        Left = 24
        Top = 19
        Width = 129
        Height = 17
        Caption = #22270#20070#24211#23384#20026'0'#26102#21015#20986
        TabOrder = 0
      end
      object cbbear: TCheckBox
        Left = 24
        Top = 41
        Width = 145
        Height = 17
        Caption = #20801#35768#36127#24211#23384#38144#21806
        TabOrder = 1
      end
      object cbwosalehistory: TCheckBox
        Left = 24
        Top = 71
        Width = 154
        Height = 17
        Caption = #26174#31034#21382#21490#25209#38144#26126#32454
        TabOrder = 2
      end
      object edwosaleday: TEdit
        Left = 545
        Top = 69
        Width = 49
        Height = 21
        NumbersOnly = True
        TabOrder = 3
      end
      object cbcheckedview: TCheckBox
        Left = 24
        Top = 146
        Width = 193
        Height = 17
        Caption = #26174#31034#24403#21069#23458#25143#32467'/'#27424#27454#24773#20917
        TabOrder = 4
      end
      object cbwosalereturn: TCheckBox
        Left = 232
        Top = 41
        Width = 146
        Height = 17
        Caption = #20801#35768#26080#25209#38144#36864#36135
        TabOrder = 5
      end
      object cblowcostalter: TCheckBox
        Left = 24
        Top = 102
        Width = 129
        Height = 17
        Caption = #20302#20110#25104#26412#25240#25187#25552#37266
        TabOrder = 6
      end
      object cblownormalalter: TCheckBox
        Left = 24
        Top = 124
        Width = 119
        Height = 17
        Caption = #20302#20110#27491#24120#25240#25187#25552#37266
        TabOrder = 7
      end
      object cblownormalenable: TCheckBox
        Left = 232
        Top = 124
        Width = 146
        Height = 17
        Caption = #20302#20110#27491#24120#25240#25187#21457#36135
        TabOrder = 8
      end
      object cblowcostenable: TCheckBox
        Left = 232
        Top = 102
        Width = 146
        Height = 17
        Caption = #20302#20110#25104#26412#25240#25187#21457#36135
        Ctl3D = True
        ParentCtl3D = False
        TabOrder = 9
      end
      object etdot: TEdit
        Left = 509
        Top = 37
        Width = 35
        Height = 21
        MaxLength = 1
        NumbersOnly = True
        TabOrder = 10
      end
      object cbpxtuihuocatch: TCheckBox
        Left = 438
        Top = 19
        Width = 97
        Height = 17
        Caption = #36864#36135#30417#31649
        TabOrder = 11
      end
      object chxianchangrecive: TCheckBox
        Left = 232
        Top = 19
        Width = 169
        Height = 17
        Caption = #25209#38144#30028#38754#29616#22330#25910#27454#21487#29992
        TabOrder = 12
      end
      object cbpxallclientdetail: TCheckBox
        Left = 232
        Top = 71
        Width = 199
        Height = 17
        Caption = #25209#38144#26126#32454#26174#31034#25152#26377#23458#25143#21382#21490#35760#24405
        TabOrder = 13
      end
      object cbpxdeleteusepassword: TCheckBox
        Left = 438
        Top = 146
        Width = 145
        Height = 17
        Caption = #21551#29992#25209#38144#21024#21333#23494#30721
        TabOrder = 14
      end
      object cbpxnobkinfosale: TCheckBox
        Left = 398
        Top = 294
        Width = 97
        Height = 17
        Caption = #26080#24211#23384#25209#38144
        TabOrder = 15
        Visible = False
      end
      object cbpxnobkinfotuihuo: TCheckBox
        Left = 533
        Top = 294
        Width = 130
        Height = 17
        Caption = #26080#24211#23384#25209#38144#36864#36135
        TabOrder = 16
        Visible = False
      end
      object cbpxfindusepassword: TCheckBox
        Left = 438
        Top = 124
        Width = 154
        Height = 17
        Caption = #21551#29992#25209#38144#26597#21333#23494#30721
        TabOrder = 17
      end
      object cbpxtuihuousepassword: TCheckBox
        Left = 438
        Top = 102
        Width = 186
        Height = 17
        Caption = #21551#29992#25209#38144#36864#36135#23494#30721
        TabOrder = 18
      end
      object GroupBox2: TGroupBox
        Left = 21
        Top = 58
        Width = 628
        Height = 7
        TabOrder = 19
      end
      object chnokucunpxth: TCheckBox
        Left = 232
        Top = 146
        Width = 154
        Height = 17
        Caption = #20801#35768#26080#24211#23384#25209#38144#36864#36135
        TabOrder = 20
      end
      object edmonth: TEdit
        Left = 164
        Top = 167
        Width = 37
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 21
        Text = '3'
      end
      object chpxusechange: TCheckBox
        Left = 438
        Top = 169
        Width = 193
        Height = 17
        Caption = #21551#29992#25209#38144#20462#25913#21333#22836#23494#30721
        TabOrder = 22
      end
      object chwsalesametishi: TCheckBox
        Left = 232
        Top = 169
        Width = 113
        Height = 17
        Caption = #37325#22797#24405#20837#25552#37266
        TabOrder = 23
      end
      object GroupBox3: TGroupBox
        Left = 21
        Top = 90
        Width = 628
        Height = 7
        TabOrder = 24
      end
      object edpxtuihuoqixian: TEdit
        Left = 117
        Top = 191
        Width = 37
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 25
        Text = '3'
      end
    end
    object GroupBox1: TGroupBox
      Left = 6
      Top = 226
      Width = 651
      Height = 189
      Caption = #25209#38144#25240#25187#35774#32622
      TabOrder = 1
      object Label3: TLabel
        Left = 596
        Top = 72
        Width = 11
        Height = 13
        Caption = '%'
      end
      object Label4: TLabel
        Left = 24
        Top = 53
        Width = 48
        Height = 13
        Caption = #20248#20808#32423#21035
      end
      object Label5: TLabel
        Left = 89
        Top = 53
        Width = 48
        Height = 13
        Caption = #25240#25187#31867#22411
      end
      object Label6: TLabel
        Left = 32
        Top = 75
        Width = 24
        Height = 13
        Caption = #19968#32423
      end
      object Label7: TLabel
        Left = 32
        Top = 102
        Width = 24
        Height = 13
        Caption = #20108#32423
      end
      object Label8: TLabel
        Left = 32
        Top = 129
        Width = 24
        Height = 13
        Caption = #19977#32423
      end
      object Label9: TLabel
        Left = 32
        Top = 158
        Width = 24
        Height = 13
        Caption = #22235#32423
      end
      object Label10: TLabel
        Left = 438
        Top = 128
        Width = 156
        Height = 52
        Caption = #27880#65306#22312#25240#25187#35774#32622#20013#65292#25209#38144#36319#36394#13#19978#27425#25240#25187#21644#25209#38144#40664#35748#25240#25187#24517#39035#13#26377#25928#25165#33021#22312#20248#20808#32423#21035#21644#26368#20302#25240#13#25187#20013#29983#25928
      end
      object RadioGroup1: TRadioGroup
        Left = 21
        Top = 14
        Width = 273
        Height = 33
        Columns = 2
        ItemIndex = 0
        Items.Strings = (
          #20248#20808#32423#21035#35774#32622
          #26368#20302#25240#25187)
        TabOrder = 0
      end
      object cbpxdefaultdiscount: TCheckBox
        Left = 438
        Top = 71
        Width = 97
        Height = 17
        Caption = #25209#38144#40664#35748#25240#25187
        TabOrder = 1
      end
      object cbpxdiscount: TCheckBox
        Left = 438
        Top = 23
        Width = 129
        Height = 17
        Caption = #25209#38144#36319#36394#19978#27425#25240#25187
        TabOrder = 2
      end
      object cbwsaledisscountchange: TCheckBox
        Left = 438
        Top = 46
        Width = 146
        Height = 17
        Caption = #20801#35768#20462#25913#25240#25187#30340#35774#32622
        TabOrder = 3
      end
      object eddefaultdiscount: TEdit
        Left = 541
        Top = 69
        Width = 49
        Height = 21
        Alignment = taRightJustify
        TabOrder = 4
        Text = '100'
        OnKeyPress = eddefaultdiscountKeyPress
      end
      object cb1: TComboBox
        Left = 89
        Top = 72
        Width = 208
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 5
        Items.Strings = (
          #33829#38144#31649#29702#25209#38144#25171#25240#35774#32622
          #20837#24211#39044#35745#25209#38144#25240#25187
          #36319#36394#19978#27425#25240#25187
          #25209#38144#40664#35748#25240#25187)
      end
      object cb2: TComboBox
        Left = 89
        Top = 99
        Width = 208
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 6
        Items.Strings = (
          #33829#38144#31649#29702#25209#38144#25171#25240#35774#32622
          #20837#24211#39044#35745#25209#38144#25240#25187
          #36319#36394#19978#27425#25240#25187
          #25209#38144#40664#35748#25240#25187)
      end
      object cb3: TComboBox
        Left = 89
        Top = 126
        Width = 208
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 7
        Items.Strings = (
          #33829#38144#31649#29702#25209#38144#25171#25240#35774#32622
          #20837#24211#39044#35745#25209#38144#25240#25187
          #36319#36394#19978#27425#25240#25187
          #25209#38144#40664#35748#25240#25187)
      end
      object cb4: TComboBox
        Left = 89
        Top = 155
        Width = 208
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 8
        Items.Strings = (
          #33829#38144#31649#29702#25209#38144#25171#25240#35774#32622
          #20837#24211#39044#35745#25209#38144#25240#25187
          #36319#36394#19978#27425#25240#25187
          #25209#38144#40664#35748#25240#25187)
      end
      object chclientaddyx: TCheckBox
        Left = 438
        Top = 96
        Width = 169
        Height = 17
        Caption = #23458#25143#35774#32622#21152#28857#25240#25187#20248#20808
        TabOrder = 9
      end
    end
  end
  object aquery: TADOQuery
    Parameters = <>
    Left = 424
    Top = 504
  end
  object qryretairange: TADOQuery
    Parameters = <>
    Left = 344
    Top = 240
  end
  object dsrcretairange: TDataSource
    DataSet = qryretairange
    Left = 344
    Top = 200
  end
end
