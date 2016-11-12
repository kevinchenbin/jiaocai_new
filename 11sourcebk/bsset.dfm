object frmbsset: Tfrmbsset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #19994#21153#35774#32622
  ClientHeight = 606
  ClientWidth = 582
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 582
    Height = 606
    Align = alClient
    BevelInner = bvLowered
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 0
    ExplicitHeight = 601
    object sbok: TSpeedButton
      Left = 328
      Top = 551
      Width = 98
      Height = 33
      Caption = #30830#23450
      OnClick = sbokClick
    end
    object sbcancel: TSpeedButton
      Left = 440
      Top = 551
      Width = 105
      Height = 33
      Caption = #21462#28040
      OnClick = sbcancelClick
    end
    object 销售业务: TGroupBox
      Left = 8
      Top = 8
      Width = 537
      Height = 170
      Caption = #38144#21806#19994#21153
      TabOrder = 0
      object Label23: TLabel
        Left = 335
        Top = 57
        Width = 100
        Height = 13
        Caption = #25209#38144#26126#32454#35760#24405#22825#25968':'
      end
      object cbstorezero: TCheckBox
        Left = 24
        Top = 24
        Width = 129
        Height = 17
        Caption = #22270#20070#24211#23384#20026'0'#26102#21015#20986
        TabOrder = 0
      end
      object cbbear: TCheckBox
        Left = 24
        Top = 56
        Width = 145
        Height = 17
        Caption = #20801#35768#36127#24211#23384#38144#21806
        TabOrder = 1
      end
      object cbpxdiscount: TCheckBox
        Left = 176
        Top = 24
        Width = 129
        Height = 17
        Caption = #25209#38144#36319#36394#19978#27425#25240#25187
        Color = clBtnFace
        ParentColor = False
        TabOrder = 2
      end
      object CheckBox2: TCheckBox
        Left = 175
        Top = 56
        Width = 146
        Height = 17
        Caption = #20801#35768#20462#25913#25240#25187#30340#35774#32622
        TabOrder = 3
      end
      object cbwosalehistory: TCheckBox
        Left = 335
        Top = 24
        Width = 154
        Height = 17
        Caption = #26159#21542#26174#31034#21382#21490#25209#38144#26126#32454
        TabOrder = 4
      end
      object edwosaleday: TEdit
        Left = 441
        Top = 52
        Width = 49
        Height = 19
        NumbersOnly = True
        TabOrder = 5
      end
      object cbcheckedview: TCheckBox
        Left = 24
        Top = 88
        Width = 193
        Height = 17
        Caption = #26159#21542#26174#31034#24403#21069#23458#25143#32467'/'#27424#27454#24773#20917
        TabOrder = 6
      end
      object cbwosalereturn: TCheckBox
        Left = 335
        Top = 88
        Width = 146
        Height = 17
        Caption = #26159#21542#20801#35768#26080#25209#38144#36864#36135
        TabOrder = 7
      end
      object cbalarmcredit: TCheckBox
        Left = 24
        Top = 116
        Width = 97
        Height = 17
        Caption = #35686#21578#20449#29992#39069#24230
        Color = clBtnFace
        ParentColor = False
        TabOrder = 8
      end
      object cbforbidcredit: TCheckBox
        Left = 24
        Top = 143
        Width = 97
        Height = 17
        Caption = #31105#27490#20449#29992#39069#24230
        Color = clBtnFace
        ParentColor = False
        TabOrder = 9
      end
      object cbforbidbackrate: TCheckBox
        Left = 175
        Top = 143
        Width = 97
        Height = 17
        Caption = #31105#27490#36864#36135#29575
        Color = clBtnFace
        ParentColor = False
        TabOrder = 10
      end
      object cbalarmbackrate: TCheckBox
        Left = 175
        Top = 116
        Width = 97
        Height = 17
        Caption = #35686#21578#36864#36135#29575
        Color = clBtnFace
        ParentColor = False
        TabOrder = 11
      end
    end
    object GroupBox1: TGroupBox
      Left = 8
      Top = 184
      Width = 537
      Height = 122
      Caption = #20837#24211#19994#21153#25511#21046
      TabOrder = 1
      object Label1: TLabel
        Left = 24
        Top = 88
        Width = 72
        Height = 13
        Caption = #23567#25968#28857#20301#25968#65306
      end
      object Label2: TLabel
        Left = 143
        Top = 88
        Width = 90
        Height = 13
        Caption = #65288#26368#22810#35774#32622'4'#20301#65289
      end
      object 进退货明细: TLabel
        Left = 335
        Top = 88
        Width = 124
        Height = 13
        Caption = #36827'/'#36864#36135#26126#32454#35760#24405#22825#25968#65306
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
        Left = 24
        Top = 56
        Width = 113
        Height = 17
        Caption = #26377#35746#36135#35760#24405#25552#31034
        TabOrder = 1
      end
      object cbauto: TCheckBox
        Left = 175
        Top = 24
        Width = 154
        Height = 17
        Caption = #33258#21160#27880#38144#37319#36141#35760#24405
        TabOrder = 2
      end
      object cbtrace: TCheckBox
        Left = 176
        Top = 56
        Width = 129
        Height = 17
        Caption = #36319#36394#19978#27425#20837#24211#25240#25187
        TabOrder = 3
      end
      object etdot: TEdit
        Left = 102
        Top = 86
        Width = 35
        Height = 19
        MaxLength = 1
        NumbersOnly = True
        TabOrder = 4
      end
      object cbstoragehistory: TCheckBox
        Left = 335
        Top = 24
        Width = 170
        Height = 17
        Caption = #26159#21542#26174#31034#21382#21490#36827'/'#36864#36135#26126#32454
        TabOrder = 5
      end
      object edstorageday: TEdit
        Left = 456
        Top = 86
        Width = 49
        Height = 19
        NumbersOnly = True
        TabOrder = 6
      end
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 367
      Width = 537
      Height = 178
      Caption = #38646#21806#19994#21153
      TabOrder = 2
      object Label3: TLabel
        Left = 24
        Top = 47
        Width = 48
        Height = 13
        Caption = #25910#27454#33539#22260
      end
      object Label4: TLabel
        Left = 131
        Top = 47
        Width = 12
        Height = 13
        Caption = #21040
      end
      object Label5: TLabel
        Left = 211
        Top = 48
        Width = 48
        Height = 13
        Caption = #21487#20197#23569#25910
      end
      object Label6: TLabel
        Left = 335
        Top = 48
        Width = 12
        Height = 13
        Caption = #20803
      end
      object Label7: TLabel
        Left = 24
        Top = 71
        Width = 48
        Height = 13
        Caption = #25910#27454#33539#22260
      end
      object Label8: TLabel
        Left = 131
        Top = 71
        Width = 12
        Height = 13
        Caption = #21040
      end
      object Label9: TLabel
        Left = 211
        Top = 72
        Width = 48
        Height = 13
        Caption = #21487#20197#23569#25910
      end
      object Label10: TLabel
        Left = 335
        Top = 72
        Width = 12
        Height = 13
        Caption = #20803
      end
      object Label11: TLabel
        Left = 24
        Top = 95
        Width = 48
        Height = 13
        Caption = #25910#27454#33539#22260
      end
      object Label12: TLabel
        Left = 131
        Top = 95
        Width = 12
        Height = 13
        Caption = #21040
      end
      object Label13: TLabel
        Left = 211
        Top = 96
        Width = 48
        Height = 13
        Caption = #21487#20197#23569#25910
      end
      object Label14: TLabel
        Left = 335
        Top = 96
        Width = 12
        Height = 13
        Caption = #20803
      end
      object Label15: TLabel
        Left = 24
        Top = 119
        Width = 48
        Height = 13
        Caption = #25910#27454#33539#22260
      end
      object Label16: TLabel
        Left = 131
        Top = 119
        Width = 12
        Height = 13
        Caption = #21040
      end
      object Label17: TLabel
        Left = 211
        Top = 120
        Width = 48
        Height = 13
        Caption = #21487#20197#23569#25910
      end
      object Label18: TLabel
        Left = 335
        Top = 120
        Width = 12
        Height = 13
        Caption = #20803
      end
      object Label19: TLabel
        Left = 24
        Top = 143
        Width = 48
        Height = 13
        Caption = #25910#27454#33539#22260
      end
      object Label20: TLabel
        Left = 131
        Top = 143
        Width = 12
        Height = 13
        Caption = #21040
      end
      object Label21: TLabel
        Left = 211
        Top = 144
        Width = 48
        Height = 13
        Caption = #21487#20197#23569#25910
      end
      object Label22: TLabel
        Left = 335
        Top = 144
        Width = 12
        Height = 13
        Caption = #20803
      end
      object cbnosalereturn: TCheckBox
        Left = 24
        Top = 24
        Width = 113
        Height = 17
        Caption = #20801#35768#26080#38144#21806#36864#36135
        TabOrder = 0
      end
      object edmin1: TEdit
        Left = 78
        Top = 44
        Width = 47
        Height = 19
        TabOrder = 1
      end
      object edmax1: TEdit
        Left = 149
        Top = 44
        Width = 56
        Height = 19
        TabOrder = 2
      end
      object edlost1: TEdit
        Left = 265
        Top = 44
        Width = 64
        Height = 19
        TabOrder = 3
      end
      object edlost2: TEdit
        Left = 265
        Top = 68
        Width = 64
        Height = 19
        TabOrder = 4
      end
      object edmax2: TEdit
        Left = 149
        Top = 68
        Width = 56
        Height = 19
        TabOrder = 5
      end
      object edmin2: TEdit
        Left = 78
        Top = 68
        Width = 47
        Height = 19
        TabOrder = 6
      end
      object edlost3: TEdit
        Left = 265
        Top = 92
        Width = 64
        Height = 19
        TabOrder = 7
      end
      object edmax3: TEdit
        Left = 149
        Top = 92
        Width = 56
        Height = 19
        TabOrder = 8
      end
      object edmin3: TEdit
        Left = 78
        Top = 92
        Width = 47
        Height = 19
        TabOrder = 9
      end
      object edlost4: TEdit
        Left = 265
        Top = 116
        Width = 64
        Height = 19
        TabOrder = 10
      end
      object edmax4: TEdit
        Left = 149
        Top = 116
        Width = 56
        Height = 19
        TabOrder = 11
      end
      object edmin4: TEdit
        Left = 78
        Top = 116
        Width = 47
        Height = 19
        TabOrder = 12
      end
      object edlost5: TEdit
        Left = 265
        Top = 140
        Width = 64
        Height = 19
        TabOrder = 13
      end
      object edmax5: TEdit
        Left = 149
        Top = 140
        Width = 56
        Height = 19
        TabOrder = 14
      end
      object edmin5: TEdit
        Left = 78
        Top = 140
        Width = 47
        Height = 19
        TabOrder = 15
      end
      object cbeffect1: TCheckBox
        Left = 360
        Top = 48
        Width = 81
        Height = 17
        Caption = #26159#21542#26377#25928
        TabOrder = 16
        OnClick = cbeffect1Click
      end
      object cbeffect2: TCheckBox
        Left = 360
        Top = 71
        Width = 81
        Height = 17
        Caption = #26159#21542#26377#25928
        TabOrder = 17
        OnClick = cbeffect2Click
      end
      object cbeffect3: TCheckBox
        Left = 360
        Top = 94
        Width = 81
        Height = 17
        Caption = #26159#21542#26377#25928
        TabOrder = 18
        OnClick = cbeffect3Click
      end
      object cbeffect4: TCheckBox
        Left = 360
        Top = 117
        Width = 81
        Height = 17
        Caption = #26159#21542#26377#25928
        TabOrder = 19
        OnClick = cbeffect4Click
      end
      object cbeffect5: TCheckBox
        Left = 360
        Top = 140
        Width = 81
        Height = 17
        Caption = #26159#21542#26377#25928
        TabOrder = 20
        OnClick = cbeffect5Click
      end
      object cbRetailDiscountChange: TCheckBox
        Left = 152
        Top = 24
        Width = 145
        Height = 17
        Caption = #26159#21542#21487#26356#25913#38646#21806#25240#25187
        Color = clBtnFace
        ParentColor = False
        TabOrder = 21
      end
    end
    object GroupBox3: TGroupBox
      Left = 8
      Top = 312
      Width = 537
      Height = 49
      Caption = #35746#21333#19994#21153
      TabOrder = 3
      object cbautolocalstockbyOrder: TCheckBox
        Left = 16
        Top = 20
        Width = 137
        Height = 18
        Caption = #33258#21160#38145#23450#24211#23384#37327
        Color = clBtnFace
        ParentColor = False
        TabOrder = 0
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
    Left = 528
    Top = 368
  end
end
