inherited frmRecMoney: TfrmRecMoney
  Caption = #29616#22330#32467#27454
  ClientHeight = 215
  ClientWidth = 243
  Color = clInactiveCaptionText
  OnShow = FormShow
  ExplicitWidth = 249
  ExplicitHeight = 243
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel2: TPanel
    Width = 243
    Height = 215
    Align = alClient
    Color = 16180174
    ParentBackground = False
    ExplicitWidth = 220
    ExplicitHeight = 219
    inherited btnOk: TRzButton
      Left = 66
      Top = 178
      ExplicitLeft = 66
      ExplicitTop = 178
    end
    inherited btnCancel: TRzButton
      Left = 147
      Top = 178
      ExplicitLeft = 147
      ExplicitTop = 178
    end
    object grpbx1: TRzGroupBox
      Left = 8
      Top = 0
      Width = 214
      Height = 167
      Anchors = [akLeft, akTop, akRight, akBottom]
      Color = 16180174
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 2
      ExplicitHeight = 237
      object lbl1: TRzLabel
        Left = 8
        Top = 56
        Width = 64
        Height = 16
        Caption = #24050#32467#37329#39069
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = True
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl2: TRzLabel
        Left = 8
        Top = 136
        Width = 64
        Height = 16
        Caption = #29616#22330#20184#27454
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = True
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object lbl3: TRzLabel
        Left = 8
        Top = 96
        Width = 64
        Height = 16
        Caption = #26410#32467#37329#39069
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = True
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object RzLabel1: TRzLabel
        Left = 8
        Top = 16
        Width = 64
        Height = 16
        Caption = #24212#20184#37329#39069
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        Transparent = True
        BlinkIntervalOff = 600
        BlinkIntervalOn = 600
      end
      object numedtChecked: TRzNumericEdit
        Left = 78
        Top = 53
        Width = 115
        Height = 24
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        FocusColor = clInfoBk
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
        IntegersOnly = False
        DisplayFormat = '###,##0.0;-###,##0.0'
      end
      object numedtReceive: TRzNumericEdit
        Left = 78
        Top = 133
        Width = 115
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        OnChange = numedtReceiveChange
        OnExit = numedtReceiveExit
        OnKeyPress = numedtReceiveKeyPress
        IntegersOnly = False
        DisplayFormat = '###,##0.0;-###,##0.0'
      end
      object numedtUnchecked: TRzNumericEdit
        Left = 78
        Top = 93
        Width = 115
        Height = 24
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        FocusColor = clInfoBk
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
        IntegersOnly = False
        DisplayFormat = '###,##0.0;-###,##0.0'
      end
      object numedtshoud: TRzNumericEdit
        Left = 78
        Top = 13
        Width = 115
        Height = 24
        DisabledColor = clWindow
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        FocusColor = clInfoBk
        ParentFont = False
        ReadOnly = True
        TabOrder = 3
        IntegersOnly = False
        DisplayFormat = '###,##0.0;-###,##0.0'
      end
    end
  end
end
