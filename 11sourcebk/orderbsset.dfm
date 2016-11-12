object frmorderbsset: Tfrmorderbsset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #35746#21333#19994#21153#25511#21046
  ClientHeight = 150
  ClientWidth = 552
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
    Width = 552
    Height = 150
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    Ctl3D = False
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 0
    ExplicitHeight = 269
    object sbok: TSpeedButton
      Left = 317
      Top = 110
      Width = 98
      Height = 33
      Caption = #30830#23450
      OnClick = sbokClick
    end
    object sbcancel: TSpeedButton
      Left = 439
      Top = 110
      Width = 105
      Height = 33
      Caption = #21462#28040
      OnClick = sbcancelClick
    end
    object GroupBox3: TGroupBox
      Left = 7
      Top = 3
      Width = 537
      Height = 101
      Caption = #35746#21333#19994#21153
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 0
      object Label1: TLabel
        Left = 164
        Top = 21
        Width = 96
        Height = 13
        Caption = #39044#35745#21457#36135#40664#35748#22825#25968
      end
      object Label2: TLabel
        Left = 164
        Top = 49
        Width = 84
        Height = 13
        Caption = #25552#31034#26102#38388#20026#26368#36817
      end
      object Label3: TLabel
        Left = 310
        Top = 49
        Width = 12
        Height = 13
        Caption = #26376
      end
      object cbautolocalstockbyOrder: TCheckBox
        Left = 16
        Top = 20
        Width = 129
        Height = 18
        Caption = #33258#21160#38145#23450#24211#23384#37327
        TabOrder = 0
      end
      object edday: TEdit
        Left = 268
        Top = 19
        Width = 50
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 1
        Text = '0'
      end
      object chlastorderdiscount: TCheckBox
        Left = 357
        Top = 20
        Width = 137
        Height = 18
        Caption = #36319#36394#19978#27425#35746#36135#25240#25187
        TabOrder = 2
      end
      object chchongfuordertishi: TCheckBox
        Left = 16
        Top = 48
        Width = 129
        Height = 18
        BiDiMode = bdLeftToRight
        Caption = #35746#21333#37325#22797#35760#24405#25552#31034
        ParentBiDiMode = False
        TabOrder = 3
      end
      object edmonth: TEdit
        Left = 254
        Top = 46
        Width = 50
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 4
        Text = '0'
      end
      object chorderfind: TCheckBox
        Left = 16
        Top = 77
        Width = 129
        Height = 18
        BiDiMode = bdLeftToRight
        Caption = #35746#21333#26597#21333#23494#30721#21551#29992
        ParentBiDiMode = False
        TabOrder = 5
      end
      object chorderchange: TCheckBox
        Left = 164
        Top = 77
        Width = 153
        Height = 18
        BiDiMode = bdLeftToRight
        Caption = #35746#21333#20462#25913#21333#22836#23494#30721#21551#29992
        ParentBiDiMode = False
        TabOrder = 6
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
