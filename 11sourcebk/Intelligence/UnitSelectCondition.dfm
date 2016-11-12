object frmselectcondition: Tfrmselectcondition
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #35831#36873#25321#37319#36141#26465#20214
  ClientHeight = 214
  ClientWidth = 455
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 455
    Height = 214
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object sbok: TSpeedButton
      Left = 281
      Top = 175
      Width = 73
      Height = 25
      Caption = #30830#23450
      Flat = True
      OnClick = sbokClick
    end
    object sbcancel: TSpeedButton
      Left = 360
      Top = 175
      Width = 73
      Height = 25
      Caption = #21462#28040
      Flat = True
      OnClick = sbcancelClick
    end
    object GroupBox1: TGroupBox
      Left = 16
      Top = 16
      Width = 417
      Height = 153
      TabOrder = 0
      object cbclient: TCheckBox
        Left = 24
        Top = 32
        Width = 81
        Height = 17
        Caption = #23458#25143#35746#21333
        Checked = True
        State = cbChecked
        TabOrder = 0
      end
      object cbnet: TCheckBox
        Left = 280
        Top = 83
        Width = 97
        Height = 17
        Caption = #32593#19978#35746#21333
        TabOrder = 1
      end
      object cbsale: TCheckBox
        Left = 24
        Top = 83
        Width = 81
        Height = 17
        Caption = #38144#21806#24773#20917
        TabOrder = 2
        OnClick = cbsaleClick
      end
      object cbtime: TComboBox
        Left = 103
        Top = 81
        Width = 98
        Height = 21
        Style = csDropDownList
        Enabled = False
        ItemHeight = 13
        TabOrder = 3
        Items.Strings = (
          #26368#36817#19968#20010#26376
          #26368#36817#19977#20010#26376
          #26368#36817#21322#24180)
      end
      object cbinside: TCheckBox
        Left = 280
        Top = 32
        Width = 97
        Height = 17
        Caption = #20869#38656#35746#21333
        Checked = True
        State = cbChecked
        TabOrder = 4
      end
    end
  end
end
