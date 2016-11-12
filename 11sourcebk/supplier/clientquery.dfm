object frmclientquery: Tfrmclientquery
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #23458#25143#26597#35810
  ClientHeight = 90
  ClientWidth = 367
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
    Width = 367
    Height = 90
    Align = alClient
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    ExplicitWidth = 425
    object Label1: TLabel
      Left = 32
      Top = 24
      Width = 60
      Height = 13
      Caption = #23458#25143#21517#31216#65306
    end
    object SpeedButton1: TSpeedButton
      Left = 192
      Top = 56
      Width = 65
      Height = 22
      Caption = #30830#23450
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 272
      Top = 56
      Width = 65
      Height = 22
      Caption = #21462#28040
      OnClick = SpeedButton2Click
    end
    object edclientname: TEdit
      Left = 98
      Top = 21
      Width = 239
      Height = 21
      TabOrder = 0
      OnKeyPress = edclientnameKeyPress
    end
  end
end
