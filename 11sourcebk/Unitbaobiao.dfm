object frmBaobiao: TfrmBaobiao
  Left = 0
  Top = 0
  Caption = #32479#35745#25253#34920
  ClientHeight = 646
  ClientWidth = 1017
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1017
    Height = 646
    Align = alClient
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object SpeedButton1: TSpeedButton
      Left = 776
      Top = 600
      Width = 81
      Height = 33
      Caption = #26368#23567#21270
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 904
      Top = 600
      Width = 81
      Height = 33
      Caption = #36864#20986
      OnClick = SpeedButton2Click
    end
    object chstorage: TCheckBox
      Left = 32
      Top = 16
      Width = 65
      Height = 17
      Caption = #24215#21495#65306
      Checked = True
      State = cbChecked
      TabOrder = 0
    end
    object rg1: TRadioGroup
      Left = 437
      Top = 0
      Width = 209
      Height = 33
      Columns = 3
      ItemIndex = 0
      Items.Strings = (
        #26085
        #21608
        #26376)
      TabOrder = 1
      OnClick = rg1Click
    end
    object cbstorage: TComboBox
      Left = 103
      Top = 12
      Width = 306
      Height = 21
      ItemHeight = 13
      TabOrder = 2
    end
    object charstorage: TChart
      Left = 16
      Top = 39
      Width = 993
      Height = 536
      Title.Text.Strings = (
        'TChart')
      BevelInner = bvLowered
      Color = 16180174
      TabOrder = 3
      object Series1: TBarSeries
        Marks.Arrow.Visible = True
        Marks.Callout.Brush.Color = clBlack
        Marks.Callout.Arrow.Visible = True
        Marks.Visible = True
        Title = #20837#24211
        Gradient.Direction = gdTopBottom
        Shadow.Color = 8487297
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Bar'
        YValues.Order = loNone
        Data = {
          00060000000000000000F06E400000000000B06D400000000000C87440000000
          0000A079400000000000D07B400000000000A07440}
      end
      object Series7: TBarSeries
        Marks.Arrow.Visible = True
        Marks.Callout.Brush.Color = clBlack
        Marks.Callout.Arrow.Visible = True
        Marks.Visible = True
        Title = #21457#36135
        Gradient.Direction = gdTopBottom
        Shadow.Color = 8618883
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Bar'
        YValues.Order = loNone
      end
      object Series8: TBarSeries
        Marks.Arrow.Visible = True
        Marks.Callout.Brush.Color = clBlack
        Marks.Callout.Arrow.Visible = True
        Marks.Visible = True
        Title = #38646#21806
        Gradient.Direction = gdTopBottom
        Shadow.Color = 8487297
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Bar'
        YValues.Order = loNone
      end
      object Series2: TFastLineSeries
        Marks.Arrow.Visible = True
        Marks.Callout.Brush.Color = clBlack
        Marks.Callout.Arrow.Visible = True
        Marks.Visible = False
        SeriesColor = clRed
        Title = #20837#24211
        LinePen.Color = clRed
        LinePen.Width = 6
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
      object Series3: TFastLineSeries
        Marks.Arrow.Visible = True
        Marks.Callout.Brush.Color = clBlack
        Marks.Callout.Arrow.Visible = True
        Marks.Visible = False
        SeriesColor = clGreen
        Title = #21457#36135
        LinePen.Color = clGreen
        LinePen.Width = 5
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
      object Series4: TFastLineSeries
        Marks.Arrow.Visible = True
        Marks.Callout.Brush.Color = clBlack
        Marks.Callout.Arrow.Visible = True
        Marks.Visible = False
        SeriesColor = clYellow
        Title = #38646#21806
        LinePen.Color = clYellow
        LinePen.Width = 5
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
    end
    object rg2: TRadioGroup
      Left = 687
      Top = 0
      Width = 209
      Height = 33
      Columns = 3
      ItemIndex = 0
      Items.Strings = (
        #25968#37327
        #30721#27915
        #23454#27915)
      TabOrder = 4
      OnClick = rg2Click
    end
    object rgview: TRadioGroup
      Left = 504
      Top = 598
      Width = 185
      Height = 35
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        #26609#29366#22270#26174#31034
        #36235#32447#22270#26174#31034)
      TabOrder = 5
      OnClick = rgviewClick
    end
    object GroupBox1: TGroupBox
      Left = 16
      Top = 583
      Width = 369
      Height = 50
      Caption = #26174#31034#35774#32622
      TabOrder = 6
      object ch1: TCheckBox
        Left = 16
        Top = 24
        Width = 73
        Height = 17
        Caption = #20837#24211
        Checked = True
        State = cbChecked
        TabOrder = 0
        OnClick = ch1Click
      end
      object ch2: TCheckBox
        Left = 136
        Top = 24
        Width = 73
        Height = 17
        Caption = #21457#36135
        TabOrder = 1
        OnClick = ch2Click
      end
      object ch3: TCheckBox
        Left = 256
        Top = 24
        Width = 73
        Height = 17
        Caption = #38646#21806
        TabOrder = 2
        OnClick = ch3Click
      end
    end
  end
  object con: TADOConnection
    Left = 736
    Top = 152
  end
  object aqrk: TADOQuery
    Parameters = <>
    Left = 568
    Top = 368
  end
  object aqpx: TADOQuery
    Parameters = <>
    Left = 648
    Top = 360
  end
  object aqls: TADOQuery
    Parameters = <>
    Left = 672
    Top = 440
  end
end
