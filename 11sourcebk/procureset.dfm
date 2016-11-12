object frmprocureset: Tfrmprocureset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #37319#36141#19994#21153#25511#21046
  ClientHeight = 142
  ClientWidth = 554
  Color = clInactiveCaptionText
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
    Width = 554
    Height = 142
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    Ctl3D = True
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 0
    ExplicitHeight = 266
    object sbok: TSpeedButton
      Left = 340
      Top = 103
      Width = 98
      Height = 33
      Caption = #30830#23450
      OnClick = sbokClick
    end
    object sbcancel: TSpeedButton
      Left = 444
      Top = 103
      Width = 98
      Height = 33
      Caption = #21462#28040
      OnClick = sbcancelClick
    end
    object GroupBox1: TGroupBox
      Left = 5
      Top = 4
      Width = 537
      Height = 93
      Caption = #37319#36141#19994#21153
      TabOrder = 0
      object Label1: TLabel
        Left = 11
        Top = 70
        Width = 96
        Height = 13
        Caption = #39044#35745#21040#36135#40664#35748#22825#25968
      end
      object chprocurefindpwd: TCheckBox
        Left = 11
        Top = 17
        Width = 137
        Height = 17
        Caption = #21551#29992#37319#36141#21333#26597#21333#23494#30721
        TabOrder = 0
      end
      object chprocuredeletepwd: TCheckBox
        Left = 251
        Top = 17
        Width = 157
        Height = 17
        Caption = #21551#29992#37319#36141#21333#21024#34892#23494#30721
        TabOrder = 1
      end
      object chznprocurefindpwd: TCheckBox
        Left = 11
        Top = 44
        Width = 154
        Height = 17
        Caption = #21551#29992#26234#33021#37319#36141#21333#26597#21333#23494#30721
        TabOrder = 2
      end
      object chznprocuredeletepwd: TCheckBox
        Left = 251
        Top = 44
        Width = 157
        Height = 17
        Caption = #21551#29992#26234#33021#37319#36141#21333#21024#34892#23494#30721
        TabOrder = 3
      end
      object edday: TEdit
        Left = 115
        Top = 67
        Width = 50
        Height = 21
        Alignment = taRightJustify
        NumbersOnly = True
        TabOrder = 4
        Text = '0'
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
    Left = 72
    Top = 488
  end
  object dsrcretairange: TDataSource
    DataSet = qryretairange
    Left = 8
    Top = 480
  end
end
