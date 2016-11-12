inherited frmadd: Tfrmadd
  Caption = #35831#36755#20837#29992#25143#32452#21517
  ClientHeight = 147
  ClientWidth = 268
  OnClose = FormClose
  ExplicitWidth = 274
  ExplicitHeight = 179
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel2: TPanel
    Width = 268
    Height = 147
    ExplicitLeft = 0
    ExplicitTop = 0
    ExplicitWidth = 683
    ExplicitHeight = 373
    object Label1: TLabel [0]
      Left = 16
      Top = 36
      Width = 52
      Height = 13
      Caption = #29992#25143#32452#21517':'
    end
    inherited btnOk: TRzButton
      Left = 77
      Top = 98
      TabOrder = 1
      OnClick = btnOkClick
      ExplicitLeft = 77
      ExplicitTop = 98
    end
    inherited btnCancel: TRzButton
      Left = 169
      Top = 98
      TabOrder = 2
      ExplicitLeft = 169
      ExplicitTop = 98
    end
    object edt1: TEdit
      Left = 77
      Top = 32
      Width = 164
      Height = 21
      TabOrder = 0
    end
  end
  object cmd: TADOCommand
    Parameters = <>
    Left = 352
    Top = 32
  end
  object ds1: TDataSource
    DataSet = dsUserGroup
    Left = 24
    Top = 160
  end
  object dsUserGroup: TADODataSet
    Parameters = <>
    Left = 24
    Top = 256
  end
end
