object frmfahuoclass: Tfrmfahuoclass
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #21457#36135#38468#21152#20449#24687
  ClientHeight = 176
  ClientWidth = 424
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
    Width = 424
    Height = 176
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    ExplicitHeight = 168
    object ch5: TCheckBox
      Left = 16
      Top = 97
      Width = 73
      Height = 17
      Caption = #35838#31243#21517#31216
      TabOrder = 0
    end
    object ch6: TCheckBox
      Left = 16
      Top = 13
      Width = 85
      Height = 17
      Caption = #20869#37096#35782#21035#30721
      TabOrder = 1
    end
    object ch3: TCheckBox
      Left = 16
      Top = 68
      Width = 54
      Height = 17
      Caption = #23398#38498
      TabOrder = 2
    end
    object ch2: TCheckBox
      Left = 16
      Top = 40
      Width = 47
      Height = 17
      Caption = #26657#21306
      TabOrder = 3
    end
    object ed2: TEdit
      Left = 96
      Top = 38
      Width = 310
      Height = 21
      TabOrder = 4
      OnChange = ed2Change
    end
    object ed3: TEdit
      Left = 96
      Top = 66
      Width = 97
      Height = 21
      TabOrder = 5
      OnChange = ed3Change
    end
    object ed5: TEdit
      Left = 96
      Top = 95
      Width = 310
      Height = 21
      TabOrder = 6
      OnChange = ed5Change
    end
    object ed6: TEdit
      Left = 96
      Top = 11
      Width = 310
      Height = 21
      TabOrder = 7
      OnChange = ed6Change
    end
    object RzButton1: TRzButton
      Left = 250
      Top = 133
      Caption = #30830#23450
      TabOrder = 8
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 331
      Top = 133
      Caption = #21462#28040
      TabOrder = 9
      OnClick = RzButton2Click
    end
    object chclass: TCheckBox
      Left = 229
      Top = 68
      Width = 54
      Height = 17
      Caption = #24180#32423
      TabOrder = 10
    end
    object edclass: TEdit
      Left = 289
      Top = 66
      Width = 117
      Height = 21
      TabOrder = 11
      OnChange = edclassChange
    end
  end
end
