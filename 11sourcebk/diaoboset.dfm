object frmdiaoboset: Tfrmdiaoboset
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #37197#36865#19994#21153#25511#21046
  ClientHeight = 169
  ClientWidth = 359
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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 359
    Height = 169
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    Ctl3D = True
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 0
    object Label3: TLabel
      Left = 178
      Top = 14
      Width = 11
      Height = 13
      Caption = '%'
    end
    object Label1: TLabel
      Left = 21
      Top = 14
      Width = 96
      Height = 13
      Caption = #26368#36817#20837#24211#25240#25187#21152#28857
    end
    object Label2: TLabel
      Left = 221
      Top = 14
      Width = 48
      Height = 13
      Caption = #40664#35748#25240#25187
    end
    object Label4: TLabel
      Left = 330
      Top = 14
      Width = 11
      Height = 13
      Caption = '%'
    end
    object RadioGroup1: TRadioGroup
      Left = 21
      Top = 33
      Width = 320
      Height = 78
      Caption = #37197#36865#25240#25187#35774#32622
      Columns = 2
      ItemIndex = 1
      Items.Strings = (
        #20837#24211#24179#22343#25240#25187
        #26368#36817#20837#24211#25240#25187
        #26368#36817#20837#24211#25240#25187#21152#25187
        #40664#35748#25240#25187)
      TabOrder = 0
    end
    object edadddiscount: TEdit
      Left = 123
      Top = 11
      Width = 49
      Height = 21
      Alignment = taRightJustify
      TabOrder = 1
      Text = '100'
      OnKeyPress = edadddiscountKeyPress
    end
    object eddefaultdiscount: TEdit
      Left = 275
      Top = 11
      Width = 49
      Height = 21
      Alignment = taRightJustify
      TabOrder = 2
      Text = '100'
      OnKeyPress = edadddiscountKeyPress
    end
    object RzButton1: TRzButton
      Left = 178
      Top = 139
      Caption = #30830#23450
      TabOrder = 3
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 266
      Top = 139
      Caption = #21462#28040
      TabOrder = 4
      OnClick = RzButton2Click
    end
    object chpeisongsametishi: TCheckBox
      Left = 21
      Top = 117
      Width = 132
      Height = 17
      Caption = #37325#22797#24405#20837#25552#37266
      TabOrder = 5
    end
  end
  object aquery: TADOQuery
    Parameters = <>
    Left = 624
    Top = 296
  end
  object qryretairange: TADOQuery
    Parameters = <>
    Left = 72
    Top = 488
  end
  object dsrcretairange: TDataSource
    DataSet = qryretairange
    Left = 8
    Top = 480
  end
end
