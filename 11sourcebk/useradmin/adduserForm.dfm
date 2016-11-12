inherited frmadduser: Tfrmadduser
  Caption = #21592#24037#31649#29702
  ClientHeight = 186
  ClientWidth = 280
  OnClose = FormClose
  ExplicitWidth = 286
  ExplicitHeight = 218
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel2: TPanel
    Width = 280
    Height = 186
    ExplicitLeft = 0
    ExplicitTop = 0
    ExplicitWidth = 635
    ExplicitHeight = 491
    object lbl1: TLabel [0]
      Left = 24
      Top = 35
      Width = 72
      Height = 13
      Caption = #35831#36755#20837#29992#25143#21517
    end
    object lbl2: TLabel [1]
      Left = 24
      Top = 72
      Width = 60
      Height = 13
      Caption = #35831#36755#20837#23494#30721
    end
    object lbl3: TLabel [2]
      Left = 22
      Top = 107
      Width = 84
      Height = 13
      Caption = #35831#20877#27425#36755#20837#23494#30721
    end
    object lbl4: TLabel [3]
      Left = 22
      Top = 72
      Width = 72
      Height = 13
      Caption = #35831#36755#20837#26087#23494#30721
      Visible = False
    end
    object lbl5: TLabel [4]
      Left = 50
      Top = 8
      Width = 132
      Height = 13
      Caption = #28201#39336#25552#31034#65306#23494#30721#26368#22810'12'#20301
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    inherited btnOk: TRzButton
      Left = 48
      Top = 153
      OnClick = btnOkClick
      ExplicitLeft = 24
      ExplicitTop = 180
    end
    inherited btnCancel: TRzButton
      Left = 158
      Top = 153
      ExplicitLeft = 134
      ExplicitTop = 180
    end
    object edt1: TEdit
      Left = 112
      Top = 32
      Width = 132
      Height = 21
      TabOrder = 2
    end
    object edt2: TEdit
      Left = 112
      Top = 69
      Width = 132
      Height = 21
      MaxLength = 12
      PasswordChar = '*'
      TabOrder = 3
    end
    object edt3: TEdit
      Left = 112
      Top = 104
      Width = 132
      Height = 21
      MaxLength = 12
      PasswordChar = '*'
      TabOrder = 4
    end
    object edt4: TEdit
      Left = 112
      Top = 69
      Width = 132
      Height = 21
      MaxLength = 12
      PasswordChar = '*'
      TabOrder = 5
      Visible = False
    end
  end
  object ds1: TDataSource
    DataSet = dsUser
    Left = 24
    Top = 200
  end
  object dsUser: TADODataSet
    Parameters = <>
    Left = 104
    Top = 216
  end
  object cmd: TADOCommand
    Parameters = <>
    Left = 96
    Top = 272
  end
  object ds2: TDataSource
    DataSet = dsGroupID
    Left = 32
    Top = 216
  end
  object dsGroupID: TADODataSet
    Parameters = <>
    Left = 64
    Top = 224
  end
end
