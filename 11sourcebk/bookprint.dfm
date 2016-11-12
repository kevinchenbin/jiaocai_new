object frmbookprint: Tfrmbookprint
  Left = 0
  Top = 0
  Caption = 'frmbookprint'
  ClientHeight = 488
  ClientWidth = 749
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object rvdatacondiaobo11: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    RestoreDataSet = False
    Left = 400
    Top = 232
  end
  object RvProject11: TRvProject
    Engine = RvSystem11
    LoadDesigner = True
    Left = 424
    Top = 104
  end
  object RvSystem11: TRvSystem
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
    Left = 296
    Top = 152
  end
  object con: TADOConnection
    Left = 192
    Top = 144
  end
  object aqprint1: TADOQuery
    Parameters = <
      item
        Name = 'Code'
        DataType = ftString
        Size = 20
        Value = Null
      end>
    SQL.Strings = (
      
        'select RANK() OVER(order by BS_ZN_DiaoNote.ID ) as xuhao,BS_ZN_D' +
        'iaoNote.*,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog' +
        '.PressCount,BS_BookCatalog.Author,STK_BookstackInfo.Name as stac' +
        'kname,STK_BookstackInfo.id as instkid,'
      
        #9#9#9'BS_BookCatalog.Pressdate,BS_BookCatalog.huojiangstate,BS_Book' +
        'Catalog.BookWords,BS_BookCatalog.Price,BS_PressInfo.AbbreviatedN' +
        'ame,STK_BookInfo.amount as bkamount,STK_BookInfo.amount - BS_ZN_' +
        'DiaoNote.amount as afteramount,BS_ZN_DiaoNoteHeader.Remarks,sys_' +
        'user.name as opname'
      
        #9#9'from BS_ZN_DiaoNote left join BS_ZN_DiaoNoteHeader on BS_ZN_Di' +
        'aoNote.DiaoNtHeaderID = BS_ZN_DiaoNoteHeader.id '
      
        #9#9#9' left join STK_BookInfo on BS_ZN_DiaoNote.Bkinfoid = STK_Book' +
        'Info.id '
      
        #9#9#9' left join BS_BookCatalog on STK_BookInfo.BkcatalogID = BS_Bo' +
        'okCatalog.id '
      
        #9#9#9' left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressI' +
        'nfo.id'
      
        #9#9#9' left join sys_user on BS_ZN_DiaoNoteHeader.inuser = sys_user' +
        '.id'
      
        #9#9#9' left join STK_BookInfo as  STK_BookInfo1 on BS_ZN_DiaoNote.i' +
        'nBkinfoid = STK_BookInfo1.id'
      
        #9#9#9' left join STK_BookstackInfo on STK_BookInfo1.BkstackID = STK' +
        '_BookstackInfo.id'
      #9#9'where BS_ZN_DiaoNoteHeader.ZNDiaoNtCode = :Code')
    Left = 504
    Top = 104
  end
end
