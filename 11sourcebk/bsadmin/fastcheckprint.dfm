object frmfastcheckprint: Tfrmfastcheckprint
  Left = 0
  Top = 0
  Caption = 'frmfastcheckprint'
  ClientHeight = 433
  ClientWidth = 655
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object fastcheck: TRvProject
    Engine = RvSystem1
    Left = 208
    Top = 272
  end
  object aqdetail: TADOQuery
    CursorType = ctStatic
    Parameters = <>
    Left = 80
    Top = 176
  end
  object Rvfastcheck: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DisableDataSource = False
    DataSet = aqdetail
    Left = 288
    Top = 184
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
    Left = 216
    Top = 128
  end
end
