object frmPrint: TfrmPrint
  Left = 0
  Top = 0
  Caption = 'frmPrint'
  ClientHeight = 463
  ClientWidth = 616
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object RvSystem1: TRvSystem
    TitleSetup = 'Output Options'
    TitleStatus = 'Report Status'
    TitlePreview = 'Report Preview'
    SystemFiler.StatusFormat = 'Generating page %p'
    SystemPreview.ZoomFactor = 100.000000000000000000
    SystemPrinter.ScaleX = 100.000000000000000000
    SystemPrinter.ScaleY = 100.000000000000000000
    SystemPrinter.StatusFormat = 'Printing page %p'
    SystemPrinter.Title = 'Rave Report'
    SystemPrinter.UnitsFactor = 1.000000000000000000
    Left = 176
    Top = 88
  end
  object prjretail: TRvProject
    Engine = RvSystem1
    Left = 360
    Top = 136
  end
  object conRVretail: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aquerybs
    Left = 216
    Top = 216
  end
  object aquerybs: TADOQuery
    Parameters = <>
    Left = 360
    Top = 232
  end
end
