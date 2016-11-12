object frmstockalarmbsset: Tfrmstockalarmbsset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #24211#23384#39044#35686#25511#21046
  ClientHeight = 130
  ClientWidth = 553
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
    Width = 553
    Height = 130
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    Ctl3D = False
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 0
    object sbok: TSpeedButton
      Left = 336
      Top = 88
      Width = 98
      Height = 33
      Caption = #30830#23450
      OnClick = sbokClick
    end
    object sbcancel: TSpeedButton
      Left = 440
      Top = 88
      Width = 105
      Height = 33
      Caption = #21462#28040
      OnClick = sbcancelClick
    end
    object GroupBox3: TGroupBox
      Left = 8
      Top = 6
      Width = 537
      Height = 73
      Caption = #24211#23384#39044#35686
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 0
      object Label2: TLabel
        Left = 184
        Top = 49
        Width = 60
        Height = 13
        Caption = #25552#31034#26102#38388#20026
      end
      object Label3: TLabel
        Left = 303
        Top = 49
        Width = 12
        Height = 13
        Caption = #26102
      end
      object chloginstockalarm: TCheckBox
        Left = 16
        Top = 20
        Width = 137
        Height = 18
        Caption = #27599#27425#30331#38470#26102#25552#31034
        TabOrder = 0
      end
      object chkucunstockalarm: TCheckBox
        Left = 16
        Top = 48
        Width = 121
        Height = 18
        BiDiMode = bdLeftToRight
        Caption = #24211#23384#31649#29702#26102#25552#31034
        ParentBiDiMode = False
        TabOrder = 1
      end
      object edtime: TEdit
        Left = 250
        Top = 47
        Width = 50
        Height = 21
        Alignment = taRightJustify
        TabOrder = 2
        Text = '0'
        OnKeyPress = edtimeKeyPress
      end
      object chtimestockalarm: TCheckBox
        Left = 184
        Top = 20
        Width = 105
        Height = 18
        Caption = #25353#26102#38388#28857#25552#31034
        TabOrder = 3
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
