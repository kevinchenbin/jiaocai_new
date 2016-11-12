object frmjifendh: Tfrmjifendh
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #31215#20998#20817#25442
  ClientHeight = 190
  ClientWidth = 397
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
    Width = 397
    Height = 190
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object Label1: TLabel
      Left = 24
      Top = 24
      Width = 24
      Height = 13
      Caption = #21345#21495
    end
    object Label2: TLabel
      Left = 221
      Top = 24
      Width = 24
      Height = 13
      Caption = #22995#21517
    end
    object Label3: TLabel
      Left = 24
      Top = 56
      Width = 24
      Height = 13
      Caption = #31215#20998
    end
    object Label4: TLabel
      Left = 24
      Top = 100
      Width = 72
      Height = 13
      Caption = #36873#25321#20817#25442#31215#20998
    end
    object Label5: TLabel
      Left = 221
      Top = 100
      Width = 12
      Height = 13
      Caption = #33719
    end
    object Label6: TLabel
      Left = 296
      Top = 100
      Width = 72
      Height = 13
      Caption = #20803#20248#24800#21048#19968#24352
    end
    object edcard: TEdit
      Left = 56
      Top = 21
      Width = 130
      Height = 21
      Enabled = False
      TabOrder = 0
    end
    object edname: TEdit
      Left = 248
      Top = 21
      Width = 130
      Height = 21
      Enabled = False
      TabOrder = 1
    end
    object edjifen: TEdit
      Left = 56
      Top = 53
      Width = 130
      Height = 21
      Enabled = False
      TabOrder = 2
    end
    object cbtype: TComboBox
      Left = 96
      Top = 97
      Width = 90
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
      OnClick = cbtypeClick
    end
    object RzButton1: TRzButton
      Left = 221
      Top = 144
      Caption = #30830#23450
      TabOrder = 4
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 302
      Top = 144
      Caption = #21462#28040
      TabOrder = 5
      OnClick = RzButton2Click
    end
    object GroupBox1: TGroupBox
      Left = 24
      Top = 80
      Width = 353
      Height = 7
      TabOrder = 6
    end
    object edyouhui: TEdit
      Left = 236
      Top = 97
      Width = 54
      Height = 21
      Enabled = False
      TabOrder = 7
    end
  end
  object fcon: TADOConnection
    Left = 168
  end
end
