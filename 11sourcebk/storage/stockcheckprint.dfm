object frmstoragecheck: Tfrmstoragecheck
  Left = 0
  Top = 0
  Caption = 'frmstoragecheck'
  ClientHeight = 638
  ClientWidth = 812
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
    Left = 112
    Top = 256
  end
  object aqcheckreport: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'code'
        Attributes = [paNullable]
        DataType = ftString
        NumericScale = 255
        Precision = 255
        Size = 50
        Value = Null
      end>
    SQL.Strings = (
      
        'select top 10 RANK() OVER(order by B.ID desc) as xuhao,B.supplie' +
        'rname,B.bookname,B.ISBN,B.abbreviatedname,B.shouldamount,'
      
        'B.balance,B.actualamount,A.checkdate from STK_CheckStockinfo A  ' +
        ' join STK_StockInventories B '
      'on A.checkstocknum = B.NoteCode '
      'where B.NoteCode =:code')
    Left = 264
    Top = 400
  end
  object RvDataSetConnection2: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DisableDataSource = False
    DataSet = aqcheckreport
    Left = 216
    Top = 336
  end
  object t: TRvProject
    Engine = RvSystem1
    Left = 256
    Top = 248
  end
end
