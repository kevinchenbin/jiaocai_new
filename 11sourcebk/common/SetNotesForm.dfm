inherited frmSetNotes: TfrmSetNotes
  Caption = #32479#19968
  ClientHeight = 196
  ClientWidth = 206
  Color = 16180174
  ExplicitWidth = 212
  ExplicitHeight = 228
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel2: TPanel
    Top = 116
    Height = 85
    Color = 16180174
    ParentBackground = False
    TabOrder = 1
    ExplicitTop = 116
    ExplicitHeight = 85
    inherited btnOk: TRzButton
      Left = 25
      Top = 43
      ExplicitLeft = 25
      ExplicitTop = 43
    end
    inherited btnCancel: TRzButton
      Left = 121
      Top = 43
      ExplicitLeft = 121
      ExplicitTop = 43
    end
  end
  object grpbx1: TRzGroupBox
    Left = 0
    Top = 8
    Width = 206
    Height = 135
    Anchors = [akLeft, akTop, akRight, akBottom]
    BorderColor = clInactiveCaptionText
    Caption = #35774#32622#25968#37327#21644#25240#25187
    Color = 16180174
    GradientColorStop = clInactiveCaptionText
    TabOrder = 0
    ExplicitWidth = 238
    object chckbxAmount: TRzCheckBox
      Left = 4
      Top = 21
      Width = 43
      Height = 15
      Caption = #25968#37327
      State = cbUnchecked
      TabOrder = 0
      OnClick = chckbxAmountClick
      OnKeyPress = chckbxAmountKeyPress
    end
    object chckbxDiscount: TRzCheckBox
      Left = 4
      Top = 50
      Width = 43
      Height = 15
      Caption = #25240#25187
      State = cbUnchecked
      TabOrder = 2
      OnClick = chckbxDiscountClick
      OnKeyPress = chckbxAmountKeyPress
    end
    object numedtDiscount: TRzNumericEdit
      Left = 79
      Top = 48
      Width = 102
      Height = 21
      TabOrder = 3
      OnChange = numedtDiscountChange
      OnKeyPress = numedtDiscountKeyPress
      BlankValue = 100.000000000000000000
      IntegersOnly = False
      Max = 100.000000000000000000
      DisplayFormat = '##0.00'#13#10
    end
    object numedtAmount: TRzNumericEdit
      Left = 79
      Top = 19
      Width = 102
      Height = 21
      TabOrder = 1
      OnChange = numedtAmountChange
      OnKeyPress = numedtAmountKeyPress
      DisplayFormat = '###,##0;'
    end
    object chpixiaodiscount: TCheckBox
      Left = 4
      Top = 78
      Width = 69
      Height = 17
      Caption = #25209#38144#25240#25187
      TabOrder = 4
      Visible = False
    end
    object edpixiaodiscount: TRzNumericEdit
      Left = 79
      Top = 76
      Width = 102
      Height = 21
      TabOrder = 5
      Visible = False
      OnChange = edpixiaodiscountChange
      OnKeyPress = edpixiaodiscountKeyPress
      DisplayFormat = '##0.00'
    end
    object chlsdiscount: TCheckBox
      Left = 4
      Top = 107
      Width = 69
      Height = 17
      Caption = #38646#21806#25240#25187
      TabOrder = 6
      Visible = False
    end
    object edlsdiscount: TRzNumericEdit
      Left = 79
      Top = 105
      Width = 102
      Height = 21
      TabOrder = 7
      Visible = False
      OnChange = edlsdiscountChange
      OnKeyPress = edlsdiscountKeyPress
      DisplayFormat = '##0.00'
    end
  end
end
