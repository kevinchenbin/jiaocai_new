object frmaddvalue: Tfrmaddvalue
  Left = 0
  Top = 0
  Caption = #20250#21592#21345#20805#20540
  ClientHeight = 143
  ClientWidth = 393
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
    Width = 393
    Height = 143
    Align = alClient
    BevelInner = bvLowered
    TabOrder = 0
    ExplicitLeft = 160
    ExplicitTop = 32
    ExplicitWidth = 185
    ExplicitHeight = 41
    object Label1: TLabel
      Left = 24
      Top = 16
      Width = 48
      Height = 13
      Caption = #25345#21345#20154#65306
    end
    object Label2: TLabel
      Left = 205
      Top = 16
      Width = 24
      Height = 13
      Caption = #21345#21495
    end
    object Label3: TLabel
      Left = 10
      Top = 88
      Width = 60
      Height = 16
      Caption = #20805#20540#37329#39069#65306
    end
    object Label4: TLabel
      Left = 11
      Top = 51
      Width = 60
      Height = 13
      Caption = #21345#20869#20313#39069#65306
    end
    object Edit1: TEdit
      Left = 78
      Top = 13
      Width = 121
      Height = 21
      Enabled = False
      TabOrder = 0
      Text = 'edtname'
    end
    object edtcardnum: TEdit
      Left = 247
      Top = 13
      Width = 121
      Height = 21
      Enabled = False
      TabOrder = 1
      Text = 'edtcardnum'
    end
    object edtvalue: TEdit
      Left = 78
      Top = 46
      Width = 290
      Height = 20
      TabOrder = 2
      Text = 'edtvalue'
    end
    object edtaddvalue: TEdit
      Left = 90
      Top = 85
      Width = 278
      Height = 21
      TabOrder = 3
      Text = 'edtaddvalue'
    end
  end
end
