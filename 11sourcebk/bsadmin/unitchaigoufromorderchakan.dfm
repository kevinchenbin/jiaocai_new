object frmdaochu: Tfrmdaochu
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #35810#38382
  ClientHeight = 277
  ClientWidth = 477
  Color = clSkyBlue
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object RzSeparator1: TRzSeparator
    Left = 16
    Top = 159
    Width = 425
    Height = 4
    ShowGradient = True
    Color = clSkyBlue
  end
  object RzSeparator2: TRzSeparator
    Left = 8
    Top = 211
    Width = 433
    Height = 4
    ShowGradient = True
    Color = clSkyBlue
  end
  object SpeedButton1: TSpeedButton
    Left = 336
    Top = 131
    Width = 105
    Height = 25
    Caption = #26597#30475
    Flat = True
    OnClick = SpeedButton1Click
  end
  object SpeedButton2: TSpeedButton
    Left = 336
    Top = 166
    Width = 105
    Height = 25
    Caption = #23548#20986
    Flat = True
    OnClick = SpeedButton2Click
  end
  object Label1: TLabel
    Left = 40
    Top = 169
    Width = 169
    Height = 13
    Caption = #26159#21542#38656#35201#23548#20986#25104'Excel'#26684#24335#25991#20214#65311
  end
  object SpeedButton3: TSpeedButton
    Left = 336
    Top = 232
    Width = 105
    Height = 25
    Caption = #32467#26463
    Flat = True
    OnClick = SpeedButton3Click
  end
  object rp: TRzProgressBar
    Left = 40
    Top = 192
    Width = 290
    Height = 16
    BarStyle = bsGradient
    BorderWidth = 0
    InteriorOffset = 0
    PartsComplete = 0
    Percent = 0
    TotalParts = 0
  end
  object Memo1: TMemo
    Left = 16
    Top = 24
    Width = 453
    Height = 97
    TabStop = False
    BorderStyle = bsNone
    Color = clSkyBlue
    ReadOnly = True
    TabOrder = 0
  end
  object condddd: TADOConnection
    Left = 216
    Top = 88
  end
  object ADOQuery1: TADOQuery
    Parameters = <>
    Left = 296
    Top = 104
  end
end
