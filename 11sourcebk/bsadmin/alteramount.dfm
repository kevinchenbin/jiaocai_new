object frmalteramount: Tfrmalteramount
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #20462#25913#25968#37327
  ClientHeight = 75
  ClientWidth = 192
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
    Width = 192
    Height = 75
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object Label1: TLabel
      Left = 24
      Top = 16
      Width = 84
      Height = 13
      Caption = #36755#20837#25968#37327#21518#22238#36710
    end
    object ednum: TEdit
      Left = 24
      Top = 35
      Width = 121
      Height = 21
      NumbersOnly = True
      TabOrder = 0
      OnKeyPress = ednumKeyPress
    end
  end
end
