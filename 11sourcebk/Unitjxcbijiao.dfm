object frmjxcbijiao: Tfrmjxcbijiao
  Left = 0
  Top = 0
  Caption = #36827#38144#23384#27604#36739
  ClientHeight = 646
  ClientWidth = 998
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
    Width = 998
    Height = 646
    Align = alClient
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object SpeedButton1: TSpeedButton
      Left = 800
      Top = 592
      Width = 81
      Height = 33
      Caption = #26368#23567#21270
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 912
      Top = 592
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
      Left = 400
      Top = 2
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
      Top = 14
      Width = 186
      Height = 21
      ItemHeight = 13
      TabOrder = 2
    end
    object charjxc: TChart
      Left = 32
      Top = 66
      Width = 945
      Height = 465
      Title.Text.Strings = (
        'TChart')
      Title.Transparency = 1
      DepthAxis.Automatic = False
      DepthAxis.AutomaticMaximum = False
      DepthAxis.AutomaticMinimum = False
      DepthAxis.Maximum = 2.500000000000000000
      DepthAxis.Minimum = -0.500000000000000000
      DepthTopAxis.Automatic = False
      DepthTopAxis.AutomaticMaximum = False
      DepthTopAxis.AutomaticMinimum = False
      DepthTopAxis.Maximum = 2.500000000000000000
      DepthTopAxis.Minimum = -0.500000000000000000
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMaximum = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Maximum = 443.975390624999700000
      LeftAxis.Minimum = -0.000000000000019540
      RightAxis.Automatic = False
      RightAxis.AutomaticMaximum = False
      RightAxis.AutomaticMinimum = False
      BevelInner = bvLowered
      Color = 16180174
      TabOrder = 3
      PrintMargins = (
        15
        33
        15
        33)
      object Series1: TBarSeries
        BarBrush.Color = clWhite
        Marks.Arrow.Visible = True
        Marks.Callout.Brush.Color = clBlack
        Marks.Callout.Arrow.Visible = True
        Marks.Shadow.Color = 8684676
        Marks.Shadow.Visible = False
        Marks.Visible = True
        BarStyle = bsRectGradient
        Gradient.Direction = gdTopBottom
        StackGroup = 1
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Bar'
        YValues.Order = loNone
      end
      object Series2: TBarSeries
        Marks.Arrow.Visible = True
        Marks.Callout.Brush.Color = clBlack
        Marks.Callout.Arrow.Visible = True
        Marks.Visible = True
        Gradient.Direction = gdTopBottom
        Shadow.Color = 8487297
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Bar'
        YValues.Order = loNone
      end
      object Series3: TFastLineSeries
        Marks.Arrow.Visible = True
        Marks.Callout.Brush.Color = clBlack
        Marks.Callout.Arrow.Visible = True
        Marks.Visible = False
        SeriesColor = clRed
        Title = #20837#24211
        LinePen.Color = clRed
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
        SeriesColor = clGreen
        Title = #20986#24211
        LinePen.Color = clGreen
        LinePen.Width = 5
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
    end
    object rg2: TRadioGroup
      Left = 632
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
      Left = 576
      Top = 584
      Width = 193
      Height = 41
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        #26609#29366#22270#26174#31034
        #36235#32447#22270#26174#31034)
      TabOrder = 5
      OnClick = rgviewClick
    end
  end
  object con: TADOConnection
    Left = 936
    Top = 80
  end
  object aqrk: TADOQuery
    Parameters = <>
    Left = 752
    Top = 64
  end
  object aqpx: TADOQuery
    Parameters = <>
    Left = 840
    Top = 56
  end
  object aqls: TADOQuery
    Parameters = <>
    Left = 952
    Top = 216
  end
end
