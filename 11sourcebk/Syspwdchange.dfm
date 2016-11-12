object frmsyspwdchange: Tfrmsyspwdchange
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #36827#20837#31995#32479#35774#32622#23494#30721#20462#25913
  ClientHeight = 178
  ClientWidth = 278
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
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 278
    Height = 178
    Align = alClient
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 24
      Width = 54
      Height = 13
      Caption = #26087' '#23494' '#30721#65306
    end
    object Label2: TLabel
      Left = 32
      Top = 56
      Width = 54
      Height = 13
      Caption = #26032' '#23494' '#30721#65306
    end
    object Label3: TLabel
      Left = 32
      Top = 89
      Width = 60
      Height = 13
      Caption = #30830#35748#23494#30721#65306
    end
    object edoldpwd: TEdit
      Left = 104
      Top = 21
      Width = 121
      Height = 21
      PasswordChar = '*'
      TabOrder = 0
    end
    object ednewpwd: TEdit
      Left = 104
      Top = 53
      Width = 121
      Height = 21
      PasswordChar = '*'
      TabOrder = 1
    end
    object edpwdagain: TEdit
      Left = 104
      Top = 86
      Width = 121
      Height = 21
      PasswordChar = '*'
      TabOrder = 2
    end
    object btOK: TButton
      Left = 64
      Top = 128
      Width = 75
      Height = 25
      Caption = #30830#23450
      ParentShowHint = False
      ShowHint = False
      TabOrder = 3
      OnClick = btOKClick
    end
    object btConcel: TButton
      Left = 160
      Top = 128
      Width = 75
      Height = 25
      Caption = #21462#28040
      TabOrder = 4
      OnClick = btConcelClick
    end
  end
  object fcon: TADOConnection
    Left = 264
    Top = 72
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 256
    Top = 16
  end
end
