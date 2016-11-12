inherited frmSelectMember: TfrmSelectMember
  Caption = #36873#25321#20250#21592
  ClientHeight = 236
  ClientWidth = 250
  ExplicitWidth = 256
  ExplicitHeight = 264
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel2: TPanel
    Width = 250
    Height = 236
    Align = alClient
    Color = 16180174
    Ctl3D = False
    ParentBackground = False
    ParentCtl3D = False
    ExplicitWidth = 242
    ExplicitHeight = 236
    object lbl1: TRzLabel [0]
      Left = 8
      Top = 11
      Width = 60
      Height = 16
      Caption = #20250#21592#21345#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object RzLine1: TRzLine [1]
      Left = 1
      Top = 61
      Width = 233
      Height = 20
    end
    object lbl2: TRzLabel [2]
      Left = 9
      Top = 92
      Width = 60
      Height = 16
      Caption = #20250#21592#21345#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl4: TRzLabel [3]
      Left = 9
      Top = 117
      Width = 60
      Height = 16
      Caption = #20250#21592#21517#31216
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl5: TRzLabel [4]
      Left = 9
      Top = 144
      Width = 60
      Height = 16
      Caption = #20248#24800#25240#25187
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl6: TRzLabel [5]
      Left = 9
      Top = 172
      Width = 60
      Height = 16
      Caption = #21345#20869#20313#39069
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object Label1: TLabel [6]
      Left = 7
      Top = 36
      Width = 61
      Height = 16
      Caption = #39564'  '#35777'  '#30721
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    inherited btnOk: TRzButton
      Left = 86
      Top = 201
      Caption = #30830#35748'[Ent]'
      Font.Height = -13
      ParentFont = False
      TabOrder = 1
      ExplicitLeft = 78
      ExplicitTop = 201
    end
    inherited btnCancel: TRzButton
      Left = 167
      Top = 201
      Caption = #21462#28040'[Esc]'
      Font.Height = -13
      ParentFont = False
      TabOrder = 2
      OnClick = btnCancelClick
      ExplicitLeft = 159
      ExplicitTop = 201
    end
    object edtMember: TRzEdit
      Left = 74
      Top = 6
      Width = 160
      Height = 24
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      MaxLength = 13
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
      OnKeyPress = edtMemberKeyPress
    end
    object dbedtCardSN: TRzDBEdit
      Left = 74
      Top = 86
      Width = 160
      Height = 22
      DataSource = dsrc1
      DataField = 'CardSN'
      ReadOnly = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      FocusColor = clInfoBk
      FrameColor = clMedGray
      ParentFont = False
      ReadOnlyColor = clWindow
      TabOrder = 3
      OnKeyPress = dbedtCardSNKeyPress
    end
    object dbedtName: TRzDBEdit
      Left = 74
      Top = 113
      Width = 160
      Height = 22
      DataSource = dsrc1
      DataField = 'Name'
      ReadOnly = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      FocusColor = clInfoBk
      ParentFont = False
      ReadOnlyColor = clWindow
      TabOrder = 4
    end
    object dbnbedtDiscount: TRzDBNumericEdit
      Left = 74
      Top = 141
      Width = 160
      Height = 22
      DataSource = dsrc1
      DataField = 'Discount'
      ReadOnly = True
      Alignment = taLeftJustify
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnlyColor = clWindow
      TabOrder = 5
      DisplayFormat = '0.00'
    end
    object dbnbedtBalance: TRzDBNumericEdit
      Left = 74
      Top = 168
      Width = 160
      Height = 22
      DataSource = dsrc1
      DataField = 'Balance'
      ReadOnly = True
      Alignment = taLeftJustify
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnlyColor = clWindow
      TabOrder = 6
      DisplayFormat = '##0.00;-##0.00'
    end
    object edpassword: TEdit
      Left = 74
      Top = 33
      Width = 160
      Height = 24
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      PasswordChar = '*'
      TabOrder = 7
      Visible = False
      OnKeyPress = edpasswordKeyPress
    end
  end
  object dsetMember: TADODataSet
    CursorType = ctStatic
    CommandText = 
      'select Name,CardSN,Balance,Discount '#13#10'from CUST_MemberInfo left ' +
      'join CUST_MemberType on CUST_MemberInfo.MemberType=CUST_MemberTy' +
      'pe.IDType'
    Parameters = <>
    Left = 16
    Top = 206
  end
  object dsrc1: TDataSource
    DataSet = dsetMember
    Left = 40
    Top = 232
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 240
    Top = 96
  end
end
