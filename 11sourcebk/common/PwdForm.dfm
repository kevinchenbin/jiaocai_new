inherited frmPwd: TfrmPwd
  Caption = #23494#30721
  ClientHeight = 84
  ClientWidth = 236
  OnShow = FormShow
  ExplicitWidth = 242
  ExplicitHeight = 116
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel2: TPanel
    Width = 236
    Height = 84
    Align = alClient
    Color = 16180174
    ParentBackground = False
    ExplicitWidth = 236
    ExplicitHeight = 84
    object lbl1: TRzLabel [0]
      Left = 8
      Top = 12
      Width = 60
      Height = 13
      Caption = #35831#36755#20837#23494#30721
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    inherited btnOk: TRzButton
      Left = 49
      Top = 42
      ExplicitLeft = 49
      ExplicitTop = 42
    end
    inherited btnCancel: TRzButton
      Left = 130
      Top = 42
      ExplicitLeft = 130
      ExplicitTop = 42
    end
    object edtPwd: TRzEdit
      Left = 74
      Top = 8
      Width = 131
      Height = 21
      MaxLength = 12
      PasswordChar = '*'
      TabOrder = 2
      OnChange = edtPwdChange
      OnKeyPress = edtPwdKeyPress
    end
  end
end
