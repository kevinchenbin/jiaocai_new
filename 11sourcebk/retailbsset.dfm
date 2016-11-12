object frmretailbsset: Tfrmretailbsset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #38646#21806#19994#21153#25511#21046
  ClientHeight = 422
  ClientWidth = 683
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
    Width = 683
    Height = 422
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    Ctl3D = True
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 0
    object sbok: TSpeedButton
      Left = 449
      Top = 383
      Width = 98
      Height = 33
      Caption = #30830#23450
      Layout = blGlyphBottom
      OnClick = sbokClick
    end
    object sbcancel: TSpeedButton
      Left = 566
      Top = 383
      Width = 105
      Height = 33
      Caption = #21462#28040
      OnClick = sbcancelClick
    end
    object GroupBox2: TGroupBox
      Left = 7
      Top = 3
      Width = 664
      Height = 374
      Caption = #38646#21806#19994#21153#25511#21046
      TabOrder = 0
      object Label3: TLabel
        Left = 16
        Top = 31
        Width = 48
        Height = 13
        Caption = #25910#27454#33539#22260
      end
      object Label4: TLabel
        Left = 123
        Top = 31
        Width = 12
        Height = 13
        Caption = #21040
      end
      object Label5: TLabel
        Left = 203
        Top = 32
        Width = 48
        Height = 13
        Caption = #21487#20197#23569#25910
      end
      object Label6: TLabel
        Left = 327
        Top = 32
        Width = 12
        Height = 13
        Caption = #20803
      end
      object Label7: TLabel
        Left = 16
        Top = 62
        Width = 48
        Height = 13
        Caption = #25910#27454#33539#22260
      end
      object Label8: TLabel
        Left = 123
        Top = 62
        Width = 12
        Height = 13
        Caption = #21040
      end
      object Label9: TLabel
        Left = 203
        Top = 63
        Width = 48
        Height = 13
        Caption = #21487#20197#23569#25910
      end
      object Label10: TLabel
        Left = 327
        Top = 63
        Width = 12
        Height = 13
        Caption = #20803
      end
      object Label11: TLabel
        Left = 16
        Top = 93
        Width = 48
        Height = 13
        Caption = #25910#27454#33539#22260
      end
      object Label12: TLabel
        Left = 123
        Top = 93
        Width = 12
        Height = 13
        Caption = #21040
      end
      object Label13: TLabel
        Left = 203
        Top = 94
        Width = 48
        Height = 13
        Caption = #21487#20197#23569#25910
      end
      object Label14: TLabel
        Left = 327
        Top = 94
        Width = 12
        Height = 13
        Caption = #20803
      end
      object Label15: TLabel
        Left = 16
        Top = 124
        Width = 48
        Height = 13
        Caption = #25910#27454#33539#22260
      end
      object Label16: TLabel
        Left = 123
        Top = 124
        Width = 12
        Height = 13
        Caption = #21040
      end
      object Label17: TLabel
        Left = 203
        Top = 125
        Width = 48
        Height = 13
        Caption = #21487#20197#23569#25910
      end
      object Label18: TLabel
        Left = 327
        Top = 125
        Width = 12
        Height = 13
        Caption = #20803
      end
      object Label19: TLabel
        Left = 16
        Top = 155
        Width = 48
        Height = 13
        Caption = #25910#27454#33539#22260
      end
      object Label20: TLabel
        Left = 123
        Top = 155
        Width = 12
        Height = 13
        Caption = #21040
      end
      object Label21: TLabel
        Left = 203
        Top = 156
        Width = 48
        Height = 13
        Caption = #21487#20197#23569#25910
      end
      object Label22: TLabel
        Left = 327
        Top = 156
        Width = 12
        Height = 13
        Caption = #20803
      end
      object Label1: TLabel
        Left = 16
        Top = 321
        Width = 72
        Height = 13
        Caption = #23567#25968#28857#20301#25968#65306
      end
      object Label2: TLabel
        Left = 137
        Top = 320
        Width = 90
        Height = 13
        Caption = #65288#26368#22810#35774#32622'2'#20301#65289
      end
      object Label23: TLabel
        Left = 16
        Top = 297
        Width = 84
        Height = 13
        Caption = #24403#21069#25171#25240#26041#26696#65306
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object cbnosalereturn: TCheckBox
        Left = 16
        Top = 215
        Width = 113
        Height = 17
        Caption = #20801#35768#26080#38144#21806#36864#36135
        TabOrder = 0
      end
      object edmin1: TEdit
        Left = 70
        Top = 28
        Width = 47
        Height = 21
        TabOrder = 1
      end
      object edmax1: TEdit
        Left = 141
        Top = 28
        Width = 56
        Height = 21
        TabOrder = 2
      end
      object edlost1: TEdit
        Left = 257
        Top = 28
        Width = 64
        Height = 21
        TabOrder = 3
      end
      object edlost2: TEdit
        Left = 257
        Top = 59
        Width = 64
        Height = 21
        TabOrder = 4
      end
      object edmax2: TEdit
        Left = 141
        Top = 59
        Width = 56
        Height = 21
        TabOrder = 5
      end
      object edmin2: TEdit
        Left = 70
        Top = 59
        Width = 47
        Height = 21
        TabOrder = 6
      end
      object edlost3: TEdit
        Left = 257
        Top = 90
        Width = 64
        Height = 21
        TabOrder = 7
      end
      object edmax3: TEdit
        Left = 141
        Top = 90
        Width = 56
        Height = 21
        TabOrder = 8
      end
      object edmin3: TEdit
        Left = 70
        Top = 90
        Width = 47
        Height = 21
        TabOrder = 9
      end
      object edlost4: TEdit
        Left = 257
        Top = 121
        Width = 64
        Height = 21
        TabOrder = 10
      end
      object edmax4: TEdit
        Left = 141
        Top = 121
        Width = 56
        Height = 21
        TabOrder = 11
      end
      object edmin4: TEdit
        Left = 70
        Top = 121
        Width = 47
        Height = 21
        TabOrder = 12
      end
      object edlost5: TEdit
        Left = 257
        Top = 152
        Width = 64
        Height = 21
        TabOrder = 13
      end
      object edmax5: TEdit
        Left = 141
        Top = 152
        Width = 56
        Height = 21
        TabOrder = 14
      end
      object edmin5: TEdit
        Left = 70
        Top = 152
        Width = 47
        Height = 21
        TabOrder = 15
      end
      object cbeffect1: TCheckBox
        Left = 352
        Top = 31
        Width = 81
        Height = 17
        Caption = #26159#21542#26377#25928
        TabOrder = 16
        OnClick = cbeffect1Click
      end
      object cbeffect2: TCheckBox
        Left = 352
        Top = 62
        Width = 81
        Height = 17
        Caption = #26159#21542#26377#25928
        TabOrder = 17
        OnClick = cbeffect2Click
      end
      object cbeffect3: TCheckBox
        Left = 352
        Top = 93
        Width = 81
        Height = 17
        Caption = #26159#21542#26377#25928
        TabOrder = 18
        OnClick = cbeffect3Click
      end
      object cbeffect4: TCheckBox
        Left = 352
        Top = 124
        Width = 81
        Height = 17
        Caption = #26159#21542#26377#25928
        TabOrder = 19
        OnClick = cbeffect4Click
      end
      object cbeffect5: TCheckBox
        Left = 352
        Top = 154
        Width = 81
        Height = 17
        Caption = #26159#21542#26377#25928
        TabOrder = 20
        OnClick = cbeffect5Click
      end
      object cbRetailDiscountChange: TCheckBox
        Left = 16
        Top = 246
        Width = 114
        Height = 17
        Caption = #21487#26356#25913#38646#21806#25240#25187
        TabOrder = 21
      end
      object etdot: TEdit
        Left = 91
        Top = 317
        Width = 35
        Height = 21
        MaxLength = 1
        NumbersOnly = True
        TabOrder = 22
      end
      object cbxiaopiaoprint: TCheckBox
        Left = 16
        Top = 192
        Width = 136
        Height = 17
        Caption = #23567#31080#25910#27454#30452#25509#25171#21360
        TabOrder = 23
      end
      object cblsusefind: TCheckBox
        Left = 487
        Top = 31
        Width = 153
        Height = 17
        Caption = #21551#29992#38646#21806#26597#21333#23494#30721
        TabOrder = 24
      end
      object cblsusedelete: TCheckBox
        Left = 487
        Top = 93
        Width = 161
        Height = 17
        Caption = #21551#29992#38646#21806#21024#21333#23494#30721
        TabOrder = 25
      end
      object cblsusetuihuo: TCheckBox
        Left = 487
        Top = 62
        Width = 145
        Height = 17
        Caption = #21551#29992#38646#21806#36864#36135#23494#30721
        TabOrder = 26
      end
      object edlsprintbk: TEdit
        Left = 135
        Top = 410
        Width = 513
        Height = 21
        TabOrder = 27
        Visible = False
      end
      object cblsprintbk: TCheckBox
        Left = 16
        Top = 412
        Width = 113
        Height = 17
        Caption = #38646#21806#25171#21360#22791#27880#65306
        TabOrder = 28
        Visible = False
      end
      object GroupBox1: TGroupBox
        Left = 454
        Top = 19
        Width = 3
        Height = 275
        TabOrder = 29
      end
      object chjiaojieprint: TCheckBox
        Left = 297
        Top = 192
        Width = 112
        Height = 17
        Caption = #20132#25509#29677#25171#21360#23567#31080
        TabOrder = 30
      end
      object chlsdiscount: TCheckBox
        Left = 160
        Top = 246
        Width = 119
        Height = 17
        Caption = #21551#29992#20837#24211#38646#21806#25240#25187
        TabOrder = 31
        OnClick = chlsdiscountClick
      end
      object chretailbear: TCheckBox
        Left = 297
        Top = 215
        Width = 118
        Height = 17
        Caption = #20801#35768#36127#24211#23384#38144#21806
        TabOrder = 32
      end
      object GroupBox3: TGroupBox
        Left = 16
        Top = 179
        Width = 632
        Height = 7
        TabOrder = 33
      end
      object GroupBox4: TGroupBox
        Left = 16
        Top = 233
        Width = 433
        Height = 7
        TabOrder = 34
      end
      object chMemberdiscountyouxian: TCheckBox
        Left = 297
        Top = 246
        Width = 152
        Height = 17
        Caption = #20250#21592#26102#20197#20250#21592#21345#25240#25187#20248#20808
        TabOrder = 35
        OnClick = chlsdiscountClick
      end
      object chRetaiview: TCheckBox
        Left = 297
        Top = 271
        Width = 145
        Height = 17
        Caption = #38646#21806#30028#38754#26174#31034#25171#25240#26041#26696
        TabOrder = 36
      end
      object chRetailsingle: TCheckBox
        Left = 16
        Top = 271
        Width = 113
        Height = 17
        Caption = #21551#29992#21333#21697#25171#25240
        TabOrder = 37
        OnClick = chlsdiscountClick
      end
      object chRetaitype: TCheckBox
        Left = 160
        Top = 271
        Width = 113
        Height = 17
        Caption = #21551#29992#20070#30446#31867#21035#25171#25240
        TabOrder = 38
        OnClick = chlsdiscountClick
      end
      object chguadan: TCheckBox
        Left = 487
        Top = 192
        Width = 118
        Height = 17
        Caption = #20801#35768#21069#21488#25346#21333
        TabOrder = 39
        OnClick = chguadanClick
      end
      object chretailtuihuan: TCheckBox
        Left = 487
        Top = 246
        Width = 118
        Height = 17
        Caption = #20801#35768#21069#21488#36864#25442
        TabOrder = 40
      end
      object chretailprice: TCheckBox
        Left = 487
        Top = 271
        Width = 118
        Height = 17
        Caption = #20801#35768#21069#21488#36755#20837#21806#20215
        TabOrder = 41
      end
      object chguadantishi: TCheckBox
        Left = 487
        Top = 215
        Width = 118
        Height = 17
        Caption = #36864#20986#26102#25552#31034#25346#21333
        Enabled = False
        TabOrder = 42
      end
      object chhuanjiapwd: TCheckBox
        Left = 487
        Top = 154
        Width = 161
        Height = 17
        Caption = #21551#29992#38646#21806#25442#20215#23494#30721
        TabOrder = 43
      end
      object chhuankoupwd: TCheckBox
        Left = 487
        Top = 124
        Width = 145
        Height = 17
        Caption = #21551#29992#38646#21806#25442#25187#23494#30721
        TabOrder = 44
      end
      object chminlsdiscount: TCheckBox
        Left = 16
        Top = 346
        Width = 97
        Height = 17
        Caption = #26368#20302#38646#21806#25240#25187
        TabOrder = 45
      end
      object edlsdiscount: TEdit
        Left = 132
        Top = 344
        Width = 95
        Height = 21
        Alignment = taRightJustify
        TabOrder = 46
      end
      object chstorage: TCheckBox
        Left = 297
        Top = 346
        Width = 200
        Height = 17
        Caption = #26368#20302#38646#21806#25240#25187#20197#20837#24211#25240#25187#20248#20808
        TabOrder = 47
      end
    end
  end
  object aquery: TADOQuery
    Parameters = <>
    Left = 624
    Top = 32
  end
  object qryretairange: TADOQuery
    Parameters = <>
    Left = 584
    Top = 65520
  end
  object dsrcretairange: TDataSource
    DataSet = qryretairange
    Left = 416
    Top = 65512
  end
end
