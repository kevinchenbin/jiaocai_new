object frmunitfapiao: Tfrmunitfapiao
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #32479#19968#21457#31080#21495
  ClientHeight = 64
  ClientWidth = 287
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 287
    Height = 64
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    ExplicitWidth = 198
    ExplicitHeight = 59
    object Label1: TLabel
      Left = 2
      Top = 23
      Width = 36
      Height = 13
      Caption = #21457#31080#21495
    end
    object ed: TEdit
      Left = 58
      Top = 20
      Width = 215
      Height = 21
      TabOrder = 0
      OnKeyPress = edKeyPress
    end
  end
end
