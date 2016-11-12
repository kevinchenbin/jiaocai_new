object frmcfpandian: Tfrmcfpandian
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #37325#22797#30424#28857
  ClientHeight = 169
  ClientWidth = 233
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
    Width = 233
    Height = 169
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 88
      Width = 60
      Height = 13
      Caption = #36861#21152#30424#28857#25968
    end
    object Label2: TLabel
      Left = 22
      Top = 24
      Width = 195
      Height = 39
      Caption = '     '#35813#20070#27491#22312#30424#28857#65292#22914#38656#36861#21152#30424#28857#35831#22312#13#13#19979#21015#26694#20013#24405#20837#36861#21152#30424#28857#25968#21518#30830#23450#12290
    end
    object Label3: TLabel
      Left = 22
      Top = 43
      Width = 3
      Height = 13
    end
    object RzButton1: TRzButton
      Left = 127
      Top = 128
      Caption = #21462#28040
      TabOrder = 2
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 32
      Top = 128
      Caption = #30830#23450
      TabOrder = 1
      OnClick = RzButton2Click
    end
    object edamount: TEdit
      Left = 98
      Top = 85
      Width = 104
      Height = 21
      NumbersOnly = True
      TabOrder = 0
      OnKeyPress = edamountKeyPress
    end
  end
  object con: TADOConnection
    Left = 16
  end
end
