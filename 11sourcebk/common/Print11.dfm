object frmPrint11: TfrmPrint11
  Left = 480
  Top = 96
  Caption = 'frmPrint11'
  ClientHeight = 463
  ClientWidth = 539
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object aquerybs: TADOQuery
    Parameters = <>
    Left = 392
    Top = 176
  end
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
    Left = 120
    Top = 312
  end
  object conRVretail: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aquerybs
    Left = 184
    Top = 232
  end
  object prjretail: TRvProject
    Engine = RvSystem1
    Left = 96
    Top = 216
  end
end
