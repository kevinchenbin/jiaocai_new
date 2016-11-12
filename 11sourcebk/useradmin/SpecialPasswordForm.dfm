inherited frmSpecialPassword: TfrmSpecialPassword
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #29305#27530#21475#20196#35774#32622
  ClientHeight = 239
  ClientWidth = 498
  FormStyle = fsNormal
  Position = poMainFormCenter
  ExplicitWidth = 504
  ExplicitHeight = 271
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TLabel [0]
    Left = 22
    Top = 41
    Width = 72
    Height = 13
    Caption = #38646#21806#29305#27530#21475#20196
  end
  object lbl2: TLabel [1]
    Left = 274
    Top = 41
    Width = 72
    Height = 13
    Caption = #25209#38144#29305#27530#21475#20196
  end
  object lbl3: TLabel [2]
    Left = 22
    Top = 76
    Width = 72
    Height = 13
    Caption = #35746#21333#29305#27530#21475#20196
  end
  object lbl4: TLabel [3]
    Left = 274
    Top = 76
    Width = 72
    Height = 13
    Caption = #36130#21153#29305#27530#21475#20196
  end
  object lbl5: TLabel [4]
    Left = 22
    Top = 108
    Width = 72
    Height = 13
    Caption = #20837#24211#29305#27530#21475#20196
  end
  object lbl6: TLabel [5]
    Left = 274
    Top = 108
    Width = 72
    Height = 13
    Caption = #31649#29702#29305#27530#21475#20196
  end
  object lbl7: TLabel [6]
    Left = 22
    Top = 142
    Width = 72
    Height = 13
    Caption = #37319#36141#29305#27530#21475#20196
  end
  object lbl8: TLabel [7]
    Left = 31
    Top = 19
    Width = 432
    Height = 13
    Caption = #23494#30721#26368#22810'12'#20301#65292#35831#22312#20320#38656#35201#20462#25913#23494#30721#30340#27169#22359#25152#23545#24212#30340#23494#30721#26694#20013#22635#20889#20320#35201#20462#25913#30340#23494#30721
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object edt1: TEdit [8]
    Left = 100
    Top = 38
    Width = 121
    Height = 21
    MaxLength = 12
    PasswordChar = '*'
    TabOrder = 0
  end
  object edt2: TEdit [9]
    Left = 352
    Top = 38
    Width = 121
    Height = 21
    MaxLength = 12
    PasswordChar = '*'
    TabOrder = 1
  end
  object edt3: TEdit [10]
    Left = 100
    Top = 73
    Width = 121
    Height = 21
    MaxLength = 12
    PasswordChar = '*'
    TabOrder = 2
  end
  object edt4: TEdit [11]
    Left = 352
    Top = 73
    Width = 121
    Height = 21
    MaxLength = 12
    PasswordChar = '*'
    TabOrder = 3
  end
  object edt5: TEdit [12]
    Left = 100
    Top = 105
    Width = 121
    Height = 21
    MaxLength = 12
    PasswordChar = '*'
    TabOrder = 4
  end
  object edt6: TEdit [13]
    Left = 352
    Top = 105
    Width = 121
    Height = 21
    MaxLength = 12
    PasswordChar = '*'
    TabOrder = 5
  end
  object edt7: TEdit [14]
    Left = 100
    Top = 139
    Width = 121
    Height = 21
    MaxLength = 12
    PasswordChar = '*'
    TabOrder = 6
  end
  object btn1: TRzButton [15]
    Left = 295
    Top = 204
    Caption = #30830#23450
    TabOrder = 7
    OnClick = btn1Click
  end
  object btn2: TRzButton [16]
    Left = 396
    Top = 204
    Width = 77
    Caption = #21462#28040
    TabOrder = 8
    OnClick = btn2Click
  end
  object cmd: TADOCommand
    Parameters = <>
    Left = 312
    Top = 64
  end
end
