object frmMemberCardChange: TfrmMemberCardChange
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #20462#25913'('#35774#32622')'#39564#35777#30721
  ClientHeight = 153
  ClientWidth = 329
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
    Width = 329
    Height = 153
    Align = alClient
    Color = 16180174
    Ctl3D = False
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 0
    ExplicitWidth = 333
    ExplicitHeight = 163
    object Label2: TLabel
      Left = 64
      Top = 32
      Width = 48
      Height = 13
      Caption = #26032#39564#35777#30721
    end
    object Label3: TLabel
      Left = 52
      Top = 64
      Width = 60
      Height = 13
      Caption = #30830#35748#39564#35777#30721
    end
    object Button1: TButton
      Left = 96
      Top = 104
      Width = 75
      Height = 25
      Caption = #30830#23450
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 192
      Top = 104
      Width = 75
      Height = 25
      Caption = #21462#28040
      TabOrder = 1
      OnClick = Button2Click
    end
    object ednew: TEdit
      Left = 128
      Top = 29
      Width = 121
      Height = 19
      PasswordChar = '*'
      TabOrder = 2
    end
    object edconfirm: TEdit
      Left = 128
      Top = 61
      Width = 121
      Height = 19
      PasswordChar = '*'
      TabOrder = 3
    end
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 272
    Top = 40
  end
  object fcon: TADOConnection
    Left = 272
    Top = 8
  end
end
