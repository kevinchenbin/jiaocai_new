inherited frmQryNoteCode: TfrmQryNoteCode
  Caption = #26597#35810#21333#21495
  ClientHeight = 149
  ClientWidth = 280
  OnShow = FormShow
  ExplicitWidth = 286
  ExplicitHeight = 181
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel2: TPanel
    Width = 280
    Height = 149
    Color = 16180174
    ParentBackground = False
    ExplicitWidth = 280
    ExplicitHeight = 149
    DesignSize = (
      280
      149)
    object lbl1: TRzLabel [0]
      Left = 32
      Top = 27
      Width = 52
      Height = 13
      Caption = #36873#25321#26085#26399':'
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl2: TRzLabel [1]
      Left = 32
      Top = 55
      Width = 52
      Height = 13
      Caption = #24215'        '#21495':'
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    object lbl3: TRzLabel [2]
      Left = 32
      Top = 81
      Width = 52
      Height = 13
      Caption = #21333'        '#21495':'
      BlinkIntervalOff = 600
      BlinkIntervalOn = 600
    end
    inherited btnOk: TRzButton
      Left = 87
      Top = 113
      ExplicitLeft = 87
      ExplicitTop = 113
    end
    inherited btnCancel: TRzButton
      Left = 178
      Top = 113
      ExplicitLeft = 178
      ExplicitTop = 113
    end
    object dtedtDate: TRzDateTimeEdit
      Left = 86
      Top = 24
      Width = 171
      Height = 21
      EditType = etDate
      TabOrder = 2
      OnChange = dtedtDateChange
    end
    object cbb1: TRzComboBox
      Left = 86
      Top = 51
      Width = 171
      Height = 21
      Enabled = False
      ItemHeight = 13
      TabOrder = 3
    end
    object spedtID: TRzSpinEdit
      Left = 86
      Top = 78
      Width = 51
      Height = 21
      AllowKeyEdit = True
      Max = 99999.000000000000000000
      TabOrder = 4
      OnChange = spedtIDChange
    end
    object edtCode: TRzEdit
      Left = 136
      Top = 78
      Width = 121
      Height = 21
      Color = clInfoBk
      ReadOnly = True
      TabOrder = 5
    end
  end
end
