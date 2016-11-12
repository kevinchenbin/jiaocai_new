object frmIntelligence: TfrmIntelligence
  Left = 0
  Top = 0
  Caption = #26234#33021#37319#36141#21521#23548
  ClientHeight = 427
  ClientWidth = 720
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
  WindowState = wsMaximized
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 720
    Height = 427
    Align = alClient
    BevelInner = bvLowered
    TabOrder = 0
    object sbselect: TSpeedButton
      Left = 40
      Top = 144
      Width = 169
      Height = 121
      Caption = #36873#25321#26465#20214
      Flat = True
      OnClick = sbselectClick
    end
    object SpeedButton1: TSpeedButton
      Left = 240
      Top = 144
      Width = 177
      Height = 121
      Caption = #36873#25321#35746#21333
      Flat = True
      OnClick = SpeedButton1Click
    end
  end
  object StoreSelect: TADOStoredProc
    ProcedureName = 'BSI_SelectCondition'
    Parameters = <
      item
        Name = '@RETURN_VALUE'
        DataType = ftInteger
        Direction = pdReturnValue
        Value = Null
      end
      item
        Name = '@ClientOrder'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@NetOrder'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@InsideOrder'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@sale'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@time'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@mode'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@ID'
        DataType = ftInteger
        Value = Null
      end>
    Left = 168
    Top = 144
  end
end
