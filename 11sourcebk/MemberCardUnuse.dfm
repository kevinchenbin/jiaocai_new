object frmMemberCardUnuse: TfrmMemberCardUnuse
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #20250#21592#21345#36864#21345
  ClientHeight = 157
  ClientWidth = 236
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 236
    Height = 157
    Align = alClient
    Color = 16180174
    Ctl3D = False
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 0
    object Label1: TLabel
      Left = 24
      Top = 24
      Width = 48
      Height = 13
      Caption = #20250#21592#21345#21495
    end
    object Label2: TLabel
      Left = 24
      Top = 86
      Width = 48
      Height = 13
      Caption = #39564'  '#35777'  '#30721
    end
    object Label3: TLabel
      Left = 24
      Top = 56
      Width = 48
      Height = 13
      Caption = #20250#21592#22995#21517
    end
    object btok: TButton
      Left = 48
      Top = 112
      Width = 75
      Height = 25
      Caption = #30830#23450
      TabOrder = 0
      OnClick = btokClick
    end
    object btconcel: TButton
      Left = 136
      Top = 112
      Width = 75
      Height = 25
      Caption = #21462#28040
      TabOrder = 1
      OnClick = btconcelClick
    end
    object edcard: TEdit
      Left = 90
      Top = 21
      Width = 121
      Height = 19
      TabOrder = 2
    end
    object edpassword: TEdit
      Left = 90
      Top = 83
      Width = 121
      Height = 19
      PasswordChar = '*'
      TabOrder = 3
    end
    object edname: TEdit
      Left = 90
      Top = 54
      Width = 121
      Height = 19
      TabOrder = 4
    end
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 256
    Top = 24
  end
  object fcon: TADOConnection
    Left = 120
    Top = 40
  end
end
