object frmSetunite: TfrmSetunite
  Left = 0
  Top = 0
  Caption = #32479#19968
  ClientHeight = 156
  ClientWidth = 469
  Color = 16180174
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 469
    Height = 156
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    Ctl3D = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentBackground = False
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 0
    object btok: TButton
      Left = 289
      Top = 122
      Width = 75
      Height = 25
      Caption = #30830#23450
      TabOrder = 0
      OnClick = btokClick
    end
    object btcancel: TButton
      Left = 381
      Top = 122
      Width = 75
      Height = 25
      Caption = #21462#28040
      TabOrder = 1
      OnClick = btcancelClick
    end
    object GroupBox1: TGroupBox
      Left = 8
      Top = 4
      Width = 448
      Height = 113
      Caption = #35774#32622#32479#19968#20449#24687
      Color = 16180174
      Ctl3D = True
      ParentBackground = False
      ParentColor = False
      ParentCtl3D = False
      TabOrder = 2
      object Label21: TLabel
        Left = 312
        Top = 80
        Width = 12
        Height = 13
        Caption = #31532
      end
      object Label22: TLabel
        Left = 413
        Top = 79
        Width = 12
        Height = 13
        Caption = #29256
      end
      object btaddtype: TSpeedButton
        Left = 183
        Top = 50
        Width = 23
        Height = 21
        Caption = '...'
        Flat = True
        OnClick = btaddtypeClick
      end
      object btaddpress: TSpeedButton
        Left = 408
        Top = 50
        Width = 25
        Height = 21
        Caption = '...'
        Flat = True
        OnClick = btaddpressClick
      end
      object editprice: TEdit
        Left = 57
        Top = 25
        Width = 79
        Height = 21
        Alignment = taRightJustify
        Ctl3D = True
        ParentCtl3D = False
        TabOrder = 0
        Text = #65509'0.00'
        OnKeyPress = editpriceKeyPress
      end
      object rcbtype: TComboBox
        Left = 57
        Top = 50
        Width = 127
        Height = 21
        BevelInner = bvNone
        BevelOuter = bvNone
        Ctl3D = False
        ItemHeight = 13
        ParentCtl3D = False
        TabOrder = 1
        OnKeyPress = rcbtypeKeyPress
      end
      object rcbpress: TComboBox
        Left = 281
        Top = 50
        Width = 126
        Height = 21
        Ctl3D = False
        ItemHeight = 13
        ParentCtl3D = False
        TabOrder = 2
        OnKeyPress = rcbpressKeyPress
      end
      object datapressday: TDateTimePicker
        Left = 81
        Top = 77
        Width = 121
        Height = 21
        Date = 40146.605024768520000000
        Time = 40146.605024768520000000
        TabOrder = 3
        OnKeyPress = datapressdayKeyPress
      end
      object sedpresscount: TRzSpinEdit
        Left = 330
        Top = 77
        Width = 77
        Height = 21
        Value = 1.000000000000000000
        TabOrder = 4
        OnKeyPress = sedpresscountKeyPress
      end
      object edbook: TEdit
        Left = 281
        Top = 25
        Width = 121
        Height = 21
        Ctl3D = True
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ParentCtl3D = False
        TabOrder = 5
        OnKeyPress = edbookKeyPress
      end
      object cbprice: TCheckBox
        Left = 8
        Top = 27
        Width = 43
        Height = 17
        Caption = #23450#20215
        TabOrder = 6
        OnKeyPress = cbpriceKeyPress
      end
      object cbtype: TCheckBox
        Left = 8
        Top = 54
        Width = 43
        Height = 17
        Caption = #31867#21035
        TabOrder = 7
        OnKeyPress = cbtypeKeyPress
      end
      object cbbook: TCheckBox
        Left = 221
        Top = 27
        Width = 41
        Height = 17
        Caption = #19995#20070
        TabOrder = 8
        OnKeyPress = cbbookKeyPress
      end
      object cbpress: TCheckBox
        Left = 221
        Top = 54
        Width = 60
        Height = 17
        Caption = #20986#29256#31038
        TabOrder = 9
        OnKeyPress = cbpressKeyPress
      end
      object cbpressday: TCheckBox
        Left = 8
        Top = 78
        Width = 67
        Height = 17
        Caption = #20986#29256#26085#26399
        TabOrder = 10
        OnKeyPress = cbpressdayKeyPress
      end
      object cbpresscount: TCheckBox
        Left = 258
        Top = 78
        Width = 48
        Height = 17
        Caption = #29256#27425
        TabOrder = 11
        OnKeyPress = cbpresscountKeyPress
      end
    end
  end
  object query: TADOQuery
    Parameters = <>
    Left = 496
    Top = 16
  end
end
