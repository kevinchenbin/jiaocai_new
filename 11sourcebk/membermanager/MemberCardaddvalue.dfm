object frmaddvalue: Tfrmaddvalue
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #20250#21592#21345#20805#20540
  ClientHeight = 145
  ClientWidth = 380
  Color = clBtnFace
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 380
    Height = 145
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    Ctl3D = True
    ParentBackground = False
    ParentCtl3D = False
    TabOrder = 0
    object Label1: TLabel
      Left = 13
      Top = 16
      Width = 48
      Height = 13
      Caption = #25345'  '#21345'  '#20154
    end
    object Label2: TLabel
      Left = 219
      Top = 16
      Width = 24
      Height = 13
      Caption = #21345#21495
    end
    object Label3: TLabel
      Left = 13
      Top = 88
      Width = 48
      Height = 13
      Caption = #20805#20540#37329#39069
    end
    object Label4: TLabel
      Left = 13
      Top = 51
      Width = 48
      Height = 13
      Caption = #21345#20869#20313#39069
    end
    object edtcardname: TEdit
      Left = 78
      Top = 13
      Width = 120
      Height = 21
      Enabled = False
      TabOrder = 0
      OnChange = edtcardnameChange
    end
    object edtcardnum: TEdit
      Left = 247
      Top = 13
      Width = 120
      Height = 21
      Enabled = False
      TabOrder = 1
      OnChange = edtcardnumChange
    end
    object edtvalue: TEdit
      Left = 77
      Top = 48
      Width = 290
      Height = 21
      TabOrder = 2
      OnChange = edtvalueChange
    end
    object edtaddvalue: TEdit
      Left = 76
      Top = 85
      Width = 292
      Height = 21
      TabOrder = 3
      OnChange = edtaddvalueChange
      OnKeyDown = edtaddvalueKeyDown
    end
    object btComfirm: TButton
      Left = 212
      Top = 112
      Width = 75
      Height = 25
      Caption = #20445#23384
      TabOrder = 4
      OnClick = btComfirmClick
    end
    object btConsel: TButton
      Left = 293
      Top = 112
      Width = 75
      Height = 25
      Caption = #25918#24323
      TabOrder = 5
      OnClick = btConselClick
    end
  end
  object MemberCardQuery: TADOQuery
    Parameters = <>
    Left = 24
    Top = 112
  end
  object quMemberRecord: TADOQuery
    Parameters = <>
    Left = 24
    Top = 112
  end
  object fcon: TADOConnection
    Left = 192
    Top = 120
  end
end
