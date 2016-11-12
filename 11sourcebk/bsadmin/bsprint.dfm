object frmwsaleprinta: Tfrmwsaleprinta
  Left = 0
  Top = 0
  Caption = 'frmwsaleprinta'
  ClientHeight = 454
  ClientWidth = 784
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object wholesale: TRvProject
    Engine = RvSystem1
    Left = 192
    Top = 160
  end
  object aqHeader: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        Attributes = [paSigned]
        DataType = ftInteger
        Precision = 10
        Size = 4
        Value = Null
      end>
    Prepared = True
    SQL.Strings = (
      
        'select A.Remarks,D.printtitle as Name,A.WsaleNtCodeStr,F.Address' +
        ',F.Contact,D.tel,A.WsaleNtCode,F.Name,F.telephone,A.hdtime ,A.hd' +
        'time  as maketime ,A.fixedprice,A.discountedprice,'
      
        'A.totalamount,A.addcosts,C.name as maker  from BS_WsaleNoteHeade' +
        'r A'
      'left join sys_staffinfo B on A.staffid = B.ID'
      'left join sys_user C on A.operatorid = C.ID'
      'left join SYS_StorageInfo D on A.stgID = D.ID'
      'left join CUST_CustomerInfo F on A.vendorid = F.ID'
      'where A.ID =:ID'
      '')
    Left = 224
    Top = 280
  end
  object RvDataSetConnection1: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqHeader
    Left = 344
    Top = 120
  end
  object aqdetail: TADOQuery
    CursorType = ctStatic
    Parameters = <>
    Left = 200
    Top = 360
  end
  object RvDataSetConnection2: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqdetail
    Left = 232
    Top = 96
  end
  object aqtotalnum: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'headID'
        Attributes = [paSigned]
        DataType = ftInteger
        Precision = 10
        Size = 4
        Value = Null
      end>
    SQL.Strings = (
      'select count(*) as num from BS_WsaleNote'
      'where wsalentheaderid=:headID')
    Left = 280
    Top = 64
  end
  object RvDataSetConnection3: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqtotalnum
    Left = 352
    Top = 104
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
    Top = 192
  end
  object rvstorage1: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqhead
    Left = 336
    Top = 192
  end
  object rvstorage2: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqrvstoragedetail
    Left = 240
    Top = 128
  end
  object aqrvstoragedetail: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        Attributes = [paSigned]
        DataType = ftInteger
        Precision = 10
        Size = 4
        Value = Null
      end>
    Prepared = True
    SQL.Strings = (
      
        'select ROW_NUMBER() OVER(order by A.amount asc) as xuhao,rtrim(C' +
        '.ISBN) as ISBN,rtrim(C.Name) as Name,rtrim(C.PressCount) as Pres' +
        'sCount,rtrim(C.UserDefCode) as UserDefCode,rtrim(E.abbreviatedna' +
        'me) as abbreviatedname ,rtrim(C.author) as author ,rtrim(C.price' +
        ') as price,A.amount,A.discount,A.fixedprice,discountedprice,isnu' +
        'll(at.camount,0) camount '
      'from BS_StorageNote A'
      'left join STK_BookInfo B on A.bkinfoid = B.ID'
      'left join BS_BookCatalog C on B.bkcatalogID = C.ID'
      'left join BS_PressInfo E on E.ID = C.pressID'
      
        'left join BS_StorageNote_attachment at on at.BS_StorageNoteID=a.' +
        'ID'
      'where stgNtHeaderid =:ID'
      'order by A.amount asc')
    Left = 184
    Top = 24
  end
  object aqhead: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        Attributes = [paSigned]
        DataType = ftInteger
        Precision = 10
        Size = 4
        Value = Null
      end>
    Prepared = True
    SQL.Strings = (
      
        'select A.remarks,D.printtitle as Name,D.Address,D.Contact,D.tel,' +
        'A.Stgntcode,A.stgntcodestr,F.Name,F.address as saddress,F.teleph' +
        'one,A.hdtime,A.totalfixedprice,A.totaldiscountedprice,'
      
        'A.totalamount,A.stgntcodestr,A.addcosts,C.name as op  from BS_St' +
        'orageNoteHeader A'
      'left join sys_staffinfo B on A.staffid = B.ID'
      'left join sys_user C on A.operatorid = C.ID'
      'left join SYS_StorageInfo D on A.stgID = D.ID'
      'left join CUST_CustomerInfo F on A.supplierid = F.ID'
      'where A.ID = :ID')
    Left = 72
    Top = 112
  end
  object aqorderhead: TADOQuery
    CursorType = ctStatic
    EnableBCD = False
    Parameters = <
      item
        Name = 'ID'
        Attributes = [paSigned]
        DataType = ftString
        Precision = 10
        Size = 4
        Value = Null
      end>
    SQL.Strings = (
      
        'select D.printtitle as Name,D.Address,D.Contact,D.tel,A.OrderNtC' +
        'ode,A.remarks,F.Name,F.telephone,convert(varchar(20),A.hdtime,23' +
        ') as hdtime,convert(varchar(20),A.hdtime,23) as maketime ,A.fixe' +
        'dprice,A.discountedprice,'
      
        'A.totalamount,A.addcosts,C.name as maker ,F.address as clientadd' +
        ' from bs_ordernoteheader A'
      'left join sys_staffinfo B on A.staffid = B.ID'
      'left join sys_user C on A.operatorid = C.ID'
      'left join SYS_StorageInfo D on A.stgID = D.ID'
      'left join CUST_CustomerInfo F on A.vendorid = F.ID'
      'where A.ID =:ID')
    Left = 320
    Top = 24
  end
  object aqorderdetail: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        Attributes = [paSigned]
        DataType = ftString
        Precision = 10
        Size = 4
        Value = Null
      end>
    SQL.Strings = (
      
        'select RANK() OVER(order by A.ID asc) as xuhao,rtrim(C.ISBN) as ' +
        'ISBN,rtrim(C.Name) as Name,rtrim(C.UserDefCode) as UserDefCode,r' +
        'trim(C.PressCount) as PressCount,rtrim(E.abbreviatedname) as abb' +
        'reviatedname,rtrim(C.author) as author,rtrim(C.price) as price,'
      'A.amount,A.discount,A.fixedprice,discountedprice'
      ' from bs_ordernote A'
      'left join BS_BookCatalog C on A.bkcatalogID = C.ID'
      'left join BS_PressInfo E on E.ID = C.pressID'
      'where A.OrderNtHeaderID=:ID and A.state = 0'
      'order by A.id asc')
    Left = 464
    Top = 8
  end
  object rvorderdetail: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqorderdetail
    Left = 472
    Top = 112
  end
  object rvorderhead: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqorderhead
    Left = 576
    Top = 112
  end
  object aqProcureHeader: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        DataType = ftString
        Size = 10
        Value = Null
      end>
    SQL.Strings = (
      
        'select D.printtitle as Name,D.Address,F.Contact,D.tel,A.ProcureN' +
        'tCode,A.remarks,F.Name,F.telephone,convert(varchar(20),A.hdtime,' +
        '23) as hdtime,convert(varchar(20),A.hdtime,23) as maketime ,A.fi' +
        'xedprice,A.discountedprice,A.inorder,'
      
        'A.totalamount,A.addcosts,C.name as maker ,F.address as clientadd' +
        ',F.Fax,C.tel as usertel from BS_ProcureNoteHeader A'
      'left join sys_staffinfo B on A.staffid = B.ID'
      'left join sys_user C on A.operatorid = C.ID'
      'left join SYS_StorageInfo D on A.stgID = D.ID'
      'left join CUST_CustomerInfo F on A.supplierid = F.ID'
      'where A.ID =:ID')
    Left = 448
    Top = 168
  end
  object aqProcureDetail: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        DataType = ftString
        Size = 10
        Value = Null
      end>
    Prepared = True
    SQL.Strings = (
      
        'select RANK() OVER(order by A.ID asc) as xuhao,C.ISBN,C.Name , C' +
        '.PressCount,C.UserDefCode,E.abbreviatedname,rtrim(C.author) as a' +
        'uthor,C.price,'
      
        'A.amount,A.discount,A.fixedprice,discountedprice,rtrim(A.clientn' +
        'ame) as clientname,rtrim(A.ordercode) as ordercode'
      ' from bs_procurenote A'
      'left join BS_BookCatalog C on A.bkcatalogID = C.ID'
      'left join BS_PressInfo E on E.ID = C.pressID'
      'where A.ProcureNtHeaderID=:ID'
      'order by A.ID asc')
    Left = 560
    Top = 152
  end
  object rvProcureDetail: TRvDataSetConnection
    RuntimeVisibility = rtEndUser
    DisableDataSource = False
    RestoreDataSet = False
    DataSet = aqProcureDetail
    Left = 456
    Top = 240
  end
  object rvProcureHead: TRvDataSetConnection
    RuntimeVisibility = rtEndUser
    DisableDataSource = False
    RestoreDataSet = False
    DataSet = aqProcureHeader
    Left = 552
    Top = 216
  end
  object rvstoragechashu: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    DataSet = aqstoragechashu
    Left = 128
    Top = 128
  end
  object aqstoragechashu: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        DataType = ftInteger
        Value = Null
      end>
    SQL.Strings = (
      
        'select RANK() OVER(order by A.ID asc) as xuhao,C.ISBN,C.Name,E.a' +
        'bbreviatedname,C.author,C.UserDefCode,C.PressCount,C.price,F.har' +
        'mnum, F.damagenum,(F.harmnum + F.damagenum) as amount,A.discount' +
        ',(F.harmnum + F.damagenum)*C.price as fixedprice,(F.harmnum + F.' +
        'damagenum)*C.price*A.discount/100 as discountedprice '
      'from BS_StorageNote A'
      'left join STK_BookInfo B on A.bkinfoid = B.ID'
      'left join BS_BookCatalog C on B.bkcatalogID = C.ID'
      'left join BS_PressInfo E on E.ID = C.pressID'
      
        'left join BS_StorageNote_attachment F on A.id = F.BS_StorageNote' +
        'ID'
      
        'where A.stgNtHeaderid = :ID and (F.harmnum > 0 or F.damagenum > ' +
        '0)'
      'order by A.ID asc')
    Left = 400
    Top = 40
  end
  object fcon: TADOConnection
    Left = 392
    Top = 232
  end
  object frxProcure: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = '\\WIN-66QK65T9K6A\Canon LBP2900'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 40494.609668310200000000
    ReportOptions.LastChange = 41225.468287974540000000
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      ''
      '{                                              '
      '}')
    OnGetValue = frxProcureGetValue
    Left = 40
    Top = 272
    Datasets = <
      item
        DataSet = frxdbprodetail
        DataSetName = 'frxdbprodetail'
      end
      item
        DataSet = frxdbprohead
        DataSetName = 'frxdbprohead'
      end>
    Variables = <>
    Style = <>
    object Data: TfrxDataPage
      Height = 1000.000000000000000000
      Width = 1000.000000000000000000
    end
    object Page1: TfrxReportPage
      PaperWidth = 210.000000000000000000
      PaperHeight = 297.000000000000000000
      PaperSize = 256
      BottomMargin = 10.000000000000000000
      object PageHeader1: TfrxPageHeader
        Height = 46.677180000000000000
        Top = 18.897650000000000000
        Width = 793.701300000000000000
        object Memo42: TfrxMemoView
          Left = 689.000000000000000000
          Top = 21.968460000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533'[Page#]'#1203#65533#65533'[TotalPages#]'#1203)
          ParentFont = False
        end
      end
      object MasterData1: TfrxMasterData
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = []
        Height = 178.527520000000000000
        ParentFont = False
        Top = 124.724490000000000000
        Width = 793.701300000000000000
        AllowSplit = True
        DataSet = frxdbprohead
        DataSetName = 'frxdbprohead'
        RowCount = 0
        Stretched = True
        object Memo5: TfrxMemoView
          Left = 19.000000000000000000
          Top = 64.598020000000000000
          Width = 177.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftTop]
          Memo.UTF8W = (
            #65533#633#65533#65533#65533#65533#355#65533'[frxdbprohead."ProcureNtCode"]')
          ParentFont = False
        end
        object Memo6: TfrxMemoView
          Left = 195.000000000000000000
          Top = 64.598020000000000000
          Width = 384.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftTop]
          Memo.UTF8W = (
            #65533#65533#1254#65533#65533#65533#65533#65533#419#65533'[frxdbprohead."Name_1"]')
          ParentFont = False
        end
        object Memo7: TfrxMemoView
          Left = 579.000000000000000000
          Top = 64.598020000000000000
          Width = 202.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop]
          Memo.UTF8W = (
            #65533#65533#1013#65533#739#65533'[frxdbprohead."Contact"]')
          ParentFont = False
        end
        object Memo8: TfrxMemoView
          Left = 19.000000000000000000
          Top = 84.598020000000000000
          Width = 175.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftTop]
          Memo.UTF8W = (
            #65533#633#65533#65533#65533#65533#1699#65533'[frxdbprohead."hdtime"]')
          ParentFont = False
        end
        object Memo9: TfrxMemoView
          Left = 195.000000000000000000
          Top = 84.598020000000000000
          Width = 384.708720000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftTop]
          Memo.UTF8W = (
            #65533#65533#1254#65533#821#32496#65533#65533'[frxdbprohead."telephone"]')
          ParentFont = False
        end
        object Memo10: TfrxMemoView
          Left = 579.000000000000000000
          Top = 84.598020000000000000
          Width = 202.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop]
          Memo.UTF8W = (
            #65533#65533#65533#26874'[frxdbprohead."Fax"]')
          ParentFont = False
        end
        object Memo11: TfrxMemoView
          Left = 19.000000000000000000
          Top = 103.598020000000000000
          Width = 762.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          Memo.UTF8W = (
            #65533#65533#1506#65533#65533'[frxdbprohead."remarks"]')
          ParentFont = False
        end
        object Memo18: TfrxMemoView
          Left = 52.000000000000000000
          Top = 151.535250000000000000
          Width = 98.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #65533#65533#65533)
          ParentFont = False
        end
        object Memo20: TfrxMemoView
          Left = 150.000000000000000000
          Top = 151.535250000000000000
          Width = 228.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #65533#65533#65533#65533)
          ParentFont = False
        end
        object Memo22: TfrxMemoView
          Left = 379.000000000000000000
          Top = 150.771572990000000000
          Width = 50.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #65533#65533#65533#65533)
          ParentFont = False
        end
        object Memo24: TfrxMemoView
          Left = 471.000000000000000000
          Top = 151.535250000000000000
          Width = 61.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #65533#65533#65533)
          ParentFont = False
        end
        object Memo28: TfrxMemoView
          Left = 578.267716540000000000
          Top = 151.535250000000000000
          Width = 45.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #65533#65533#65533#65533)
          ParentFont = False
        end
        object Memo32: TfrxMemoView
          Left = 623.622047240000000000
          Top = 151.535250000000000000
          Width = 157.606370000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #65533#65533#65533#65533)
          ParentFont = False
        end
        object Memo16: TfrxMemoView
          Left = 19.000000000000000000
          Top = 151.094310000000000000
          Width = 33.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          HAlign = haCenter
          Memo.UTF8W = (
            #65533#65533#65533)
          ParentFont = False
        end
        object Memo1: TfrxMemoView
          Align = baCenter
          Left = 67.106525000000000000
          Top = 19.598020000000000000
          Width = 659.488250000000000000
          Height = 32.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -21
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          HAlign = haCenter
          Memo.UTF8W = (
            '["Name"]')
          ParentFont = False
        end
        object Memo46: TfrxMemoView
          Left = 430.000000000000000000
          Top = 151.275510000000000000
          Width = 41.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #65533#65533#65533#65533)
          ParentFont = False
        end
        object Memo26: TfrxMemoView
          Left = 532.913385830000000000
          Top = 151.330860000000000000
          Width = 45.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #65533#65533#65533)
          ParentFont = False
        end
        object Line1: TfrxLineView
          Left = 18.897650000000000000
          Top = 148.504020000000000000
          Width = 763.465060000000000000
          ShowHint = False
          Diagonal = True
        end
        object Line2: TfrxLineView
          Left = 18.897650000000000000
          Top = 174.960730000000000000
          Width = 763.465060000000000000
          ShowHint = False
          Diagonal = True
        end
      end
      object ReportSummary1: TfrxReportSummary
        Height = 269.842610000000000000
        Top = 411.968770000000000000
        Width = 793.701300000000000000
        object Memo37: TfrxMemoView
          Left = 19.000000000000000000
          Top = 55.133580000000000000
          Width = 207.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #1205#65533#65533#65533#65533#1013#65533#739#65533'[frxdbprohead."maker"]')
          ParentFont = False
        end
        object Memo38: TfrxMemoView
          Left = 19.000000000000000000
          Top = 75.031230000000000000
          Width = 207.527520000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#1403#65533#65533#65533#1013#65533#739#65533'["shcontact"]')
          ParentFont = False
        end
        object Memo39: TfrxMemoView
          Left = 226.874150000000000000
          Top = 75.133580000000000000
          Width = 249.102350000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#1013#65533#32496#65533#65533'["shtel"]')
          ParentFont = False
        end
        object Memo40: TfrxMemoView
          Left = 18.779530000000000000
          Top = 95.692640000000000000
          Width = 762.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#1403#65533#65533#65533#1463#65533#65533'["shaddress"]')
          ParentFont = False
        end
        object Memo41: TfrxMemoView
          Left = 19.000000000000000000
          Top = 158.826530000000000000
          Width = 762.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smActualHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533#419#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#315#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#953#65533#766)
          ParentFont = False
        end
        object Memo43: TfrxMemoView
          Left = 555.000000000000000000
          Top = 245.401360000000000000
          Width = 226.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533#1447#65533#1443#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533'028-85225892 ')
          ParentFont = False
        end
        object Memo4: TfrxMemoView
          Left = 226.771800000000000000
          Top = 55.015770000000000000
          Width = 248.826840000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #1205#65533#65533#65533#65533#1013#65533#32496#65533#65533'[frxdbprohead."usertel"]')
          ParentFont = False
        end
        object Memo13: TfrxMemoView
          Left = 18.897650000000000000
          Top = 37.795300000000000000
          Width = 570.323130000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #65533#65533#1506#65533#65533#65533#65533#65533#65533#65533#40750#65533#65533#65533#1074#65533#65533#65533#65533#65533#65533#49057#65533#65533#65533#65533#65533#65533#1592#26860#1083#1083'!')
          ParentFont = False
        end
        object Memo2: TfrxMemoView
          Left = 18.897650000000000000
          Top = 116.165430000000000000
          Width = 762.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#766#65533#65533#1463#65533#65533'["address"]')
          ParentFont = False
        end
        object Memo44: TfrxMemoView
          Left = 476.220780000000000000
          Top = 55.692950000000000000
          Width = 166.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #1205#65533#65533#65533#65533#65533':023-62602233')
          ParentFont = False
        end
        object Memo12: TfrxMemoView
          Left = 476.220780000000000000
          Top = 75.590600000000000000
          Width = 166.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533#756#65533#65533#65533#65533':023-86716786')
          ParentFont = False
        end
        object Memo3: TfrxMemoView
          Left = 18.897650000000000000
          Top = 137.063080000000000000
          Width = 570.323130000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #65533#1209#65533#766#65533#65533#433#65533#65533#752#65533#65533#994#65533#65533#65533#163#65533)
          ParentFont = False
        end
        object Memo14: TfrxMemoView
          Left = 18.897650000000000000
          Top = 221.212740000000000000
          Width = 570.323130000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #65533#32226#65533#65533#65533#65533#49057#65533#52523#65533#65533#65533#65533#433#65533#65533#1083#1083#65533#65533)
          ParentFont = False
        end
        object Memo15: TfrxMemoView
          Left = 18.897650000000000000
          Top = 179.417440000000000000
          Width = 762.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smActualHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#752#65533#65533#694#65533#65533#65533':500112736590015')
          ParentFont = False
        end
        object Memo30: TfrxMemoView
          Left = 18.897650000000000000
          Top = 200.315090000000000000
          Width = 762.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smActualHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533#65533#65533#1084#65533#65533#762#355#65533#65533#1081#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#65533#1447#65533#65533' 1108014210008385')
          ParentFont = False
        end
        object Memo31: TfrxMemoView
          Left = 18.897650000000000000
          Top = 7.559059999999990000
          Width = 52.527520000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#1020#65533)
          ParentFont = False
        end
        object Memo34: TfrxMemoView
          Left = 578.268090000000000000
          Top = 7.559059999999990000
          Width = 45.488250000000000000
          Height = 18.897637800000000000
          ShowHint = False
          StretchMode = smMaxHeight
          DataSet = frxdbprodetail
          DataSetName = 'frxdbprodetail'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[SUM(<frxdbprodetail."amount">,DetailData1)]')
          ParentFont = False
        end
        object Line8: TfrxLineView
          Left = 18.897650000000000000
          Top = 26.456710000000000000
          Width = 763.465060000000000000
          ShowHint = False
          Diagonal = True
        end
      end
      object DetailData1: TfrxDetailData
        Height = 27.677180000000000000
        Top = 325.039580000000000000
        Width = 793.701300000000000000
        AllowSplit = True
        DataSet = frxdbprodetail
        DataSetName = 'frxdbprodetail'
        RowCount = 0
        Stretched = True
        object Memo21: TfrxMemoView
          Left = 153.000000000000000000
          Top = 1.086580000000030000
          Width = 223.708720000000000000
          Height = 18.897637800000000000
          ShowHint = False
          StretchMode = smActualHeight
          DataSet = frxdbprodetail
          DataSetName = 'frxdbprodetail'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxdbprodetail."Name"]')
          ParentFont = False
        end
        object Memo23: TfrxMemoView
          Left = 378.000000000000000000
          Top = 1.086580000000030000
          Width = 50.488250000000000000
          Height = 18.897637795275600000
          ShowHint = False
          StretchMode = smMaxHeight
          DataField = 'author'
          DataSet = frxdbprodetail
          DataSetName = 'frxdbprodetail'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxdbprodetail."author"]')
          ParentFont = False
          WordWrap = False
        end
        object Memo25: TfrxMemoView
          Left = 470.866141730000000000
          Top = 1.086580000000030000
          Width = 61.590551180000000000
          Height = 18.897637795275600000
          ShowHint = False
          StretchMode = smMaxHeight
          DataField = 'abbreviatedname'
          DataSet = frxdbprodetail
          DataSetName = 'frxdbprodetail'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxdbprodetail."abbreviatedname"]')
          ParentFont = False
          WordBreak = True
        end
        object Memo29: TfrxMemoView
          Left = 578.267716540000000000
          Top = 1.086580000000030000
          Width = 45.488250000000000000
          Height = 18.897637800000000000
          ShowHint = False
          StretchMode = smMaxHeight
          DataField = 'amount'
          DataSet = frxdbprodetail
          DataSetName = 'frxdbprodetail'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxdbprodetail."amount"]')
          ParentFont = False
        end
        object Memo17: TfrxMemoView
          Left = 19.000000000000000000
          Top = 1.086580000000030000
          Width = 33.000000000000000000
          Height = 18.897637795275600000
          ShowHint = False
          StretchMode = smMaxHeight
          DataField = 'xuhao'
          DataSet = frxdbprodetail
          DataSetName = 'frxdbprodetail'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          HAlign = haCenter
          Memo.UTF8W = (
            '[frxdbprodetail."xuhao"]')
          ParentFont = False
        end
        object Memo19: TfrxMemoView
          Left = 53.000000000000000000
          Top = 1.086580000000030000
          Width = 98.708720000000000000
          Height = 18.897637800000000000
          ShowHint = False
          StretchMode = smMaxHeight
          DataField = 'ISBN'
          DataSet = frxdbprodetail
          DataSetName = 'frxdbprodetail'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxdbprodetail."ISBN"]')
          ParentFont = False
        end
        object Memo33: TfrxMemoView
          Left = 623.622047240000000000
          Top = 1.086580000000030000
          Width = 160.385900000000000000
          Height = 18.897637795275600000
          ShowHint = False
          StretchMode = smMaxHeight
          DataField = 'clientname'
          DataSet = frxdbprodetail
          DataSetName = 'frxdbprodetail'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxdbprodetail."clientname"]')
          ParentFont = False
        end
        object Line3: TfrxLineView
          Left = 19.000000000000000000
          Top = 23.133580000000000000
          Width = 763.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Memo47: TfrxMemoView
          Left = 430.000000000000000000
          Top = 0.810760000000016000
          Width = 41.488250000000000000
          Height = 18.897637795275600000
          ShowHint = False
          DisplayFormat.FormatStr = '##0.00'
          DisplayFormat.Kind = fkNumeric
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxdbprodetail."price"]')
          ParentFont = False
        end
        object Memo27: TfrxMemoView
          Left = 532.913730000000000000
          Top = 1.000000000000000000
          Width = 45.354330710000000000
          Height = 18.897637795275600000
          ShowHint = False
          StretchMode = smMaxHeight
          DataSet = frxdbprodetail
          DataSetName = 'frxdbprodetail'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxdbprodetail."presscount"]')
          ParentFont = False
          WordBreak = True
        end
      end
    end
  end
  object frxdbprohead: TfrxDBDataset
    UserName = 'frxdbprohead'
    CloseDataSource = False
    DataSet = aqProcureHeader
    Left = 608
    Top = 368
  end
  object frxdbprodetail: TfrxDBDataset
    UserName = 'frxdbprodetail'
    CloseDataSource = False
    DataSet = aqProcureDetail
    Left = 504
    Top = 264
  end
  object frxDBwsalehead: TfrxDBDataset
    UserName = 'frxDBwsalehead'
    CloseDataSource = False
    DataSet = aqHeader
    Left = 304
    Top = 224
  end
  object frxCrossObject1: TfrxCrossObject
    Left = 272
    Top = 360
  end
  object frxRichObject1: TfrxRichObject
    Left = 312
    Top = 304
  end
  object frxOrder: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 40497.477826932900000000
    ReportOptions.LastChange = 40498.490023217600000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    OnGetValue = frxOrderGetValue
    Left = 152
    Top = 224
    Datasets = <
      item
        DataSet = frxDBorddetail
        DataSetName = 'frxDBorddetail'
      end
      item
        DataSet = frxDBordhead
        DataSetName = 'frxDBordhead'
      end>
    Variables = <>
    Style = <>
    object Data: TfrxDataPage
      Height = 1000.000000000000000000
      Width = 1000.000000000000000000
    end
    object Page1: TfrxReportPage
      PaperWidth = 210.000000000000000000
      PaperHeight = 297.000000000000000000
      PaperSize = 9
      TopMargin = 2.000000000000000000
      BottomMargin = 5.000000000000000000
      object PageHeader1: TfrxPageHeader
        Height = 27.000000000000000000
        Top = 154.960730000000000000
        Width = 793.701300000000000000
        object Memo1: TfrxMemoView
          Left = 600.000000000000000000
          Top = 3.102350000000001000
          Width = 190.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533'[Page#]'#1203' '#65533#65533'[TotalPages#]'#1203)
          ParentFont = False
        end
      end
      object ReportTitle1: TfrxReportTitle
        Height = 112.000000000000000000
        Top = 18.897650000000000000
        Width = 793.701300000000000000
        object Memo2: TfrxMemoView
          Align = baCenter
          Left = 117.106525000000000000
          Top = 21.102350000000000000
          Width = 559.488250000000000000
          Height = 23.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          HAlign = haCenter
          Memo.UTF8W = (
            '["title"]')
          ParentFont = False
        end
        object Memo3: TfrxMemoView
          Left = 22.000000000000000000
          Top = 69.102350000000000000
          Width = 358.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#32496#65533#65533'["tel"]')
          ParentFont = False
        end
        object Memo4: TfrxMemoView
          Left = 389.000000000000000000
          Top = 69.102350000000000000
          Width = 382.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#1013#65533#739#65533'["contact"]')
          ParentFont = False
        end
        object Memo5: TfrxMemoView
          Left = 22.000000000000000000
          Top = 90.102350000000000000
          Width = 749.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#1463#65533#65533'["address"]')
          ParentFont = False
        end
      end
      object MasterData1: TfrxMasterData
        Height = 135.677180000000000000
        Top = 241.889920000000000000
        Width = 793.701300000000000000
        DataSet = frxDBordhead
        DataSetName = 'frxDBordhead'
        RowCount = 0
        object Memo6: TfrxMemoView
          Left = 22.000000000000000000
          Top = 5.110080000000011000
          Width = 172.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533#65533#65533#355#65533'[frxDBordhead."OrderNtCode"]')
          ParentFont = False
        end
        object Memo7: TfrxMemoView
          Left = 193.000000000000000000
          Top = 5.110080000000011000
          Width = 388.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#891#65533#65533#65533#65533#419#65533'["ClientName"]')
          ParentFont = False
        end
        object Memo8: TfrxMemoView
          Left = 584.000000000000000000
          Top = 6.110080000000010000
          Width = 187.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#891#65533#65533#32496#65533#65533'[frxDBordhead."telephone"]')
          ParentFont = False
        end
        object Memo9: TfrxMemoView
          Left = 22.000000000000000000
          Top = 26.110080000000010000
          Width = 172.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533#65533#65533#65533#65533#1699#65533'[frxDBordhead."hdtime"]')
          ParentFont = False
        end
        object Memo10: TfrxMemoView
          Left = 195.000000000000000000
          Top = 26.110080000000010000
          Width = 576.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#1506#65533#65533'[frxDBordhead."remarks"]')
          ParentFont = False
        end
        object Memo11: TfrxMemoView
          Left = 22.000000000000000000
          Top = 47.110080000000010000
          Width = 749.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#891#65533#65533#65533#1463#65533#65533'[frxDBordhead."clientadd"]')
          ParentFont = False
        end
        object Memo12: TfrxMemoView
          Left = 22.000000000000000000
          Top = 79.110080000000010000
          Width = 199.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533#65533#65533#65533#65533#65533'[frxDBordhead."totalamount"]')
          ParentFont = False
        end
        object Memo13: TfrxMemoView
          Left = 222.000000000000000000
          Top = 79.110080000000010000
          Width = 279.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          DisplayFormat.FormatStr = '##0.00'
          DisplayFormat.Kind = fkNumeric
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533#65533#65533#65533'[frxDBordhead."fixedprice"]')
          ParentFont = False
        end
        object Memo14: TfrxMemoView
          Left = 504.000000000000000000
          Top = 79.110080000000010000
          Width = 267.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#693#65533#65533'[frxDBordhead."discountedprice"]')
          ParentFont = False
        end
        object Line1: TfrxLineView
          Left = 22.000000000000000000
          Top = 5.110080000000011000
          Width = 749.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line2: TfrxLineView
          Left = 22.000000000000000000
          Top = 5.110080000000011000
          Height = 62.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Line3: TfrxLineView
          Left = 23.000000000000000000
          Top = 67.110080000000010000
          Width = 749.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line4: TfrxLineView
          Left = 23.000000000000000000
          Top = 25.110080000000010000
          Width = 749.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line5: TfrxLineView
          Left = 23.000000000000000000
          Top = 47.110080000000010000
          Width = 748.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line6: TfrxLineView
          Left = 194.000000000000000000
          Top = 6.110080000000010000
          Height = 19.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Line7: TfrxLineView
          Left = 583.000000000000000000
          Top = 5.110080000000011000
          Height = 19.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Line8: TfrxLineView
          Left = 772.000000000000000000
          Top = 5.110080000000011000
          Height = 63.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Line9: TfrxLineView
          Left = 22.000000000000000000
          Top = 79.110080000000010000
          Width = 750.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line10: TfrxLineView
          Left = 21.000000000000000000
          Top = 98.110080000000010000
          Width = 751.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line11: TfrxLineView
          Left = 21.000000000000000000
          Top = 80.110080000000010000
          Height = 18.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Line12: TfrxLineView
          Left = 772.000000000000000000
          Top = 79.110080000000010000
          Height = 18.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Line13: TfrxLineView
          Left = 222.000000000000000000
          Top = 79.110080000000010000
          Height = 18.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Line14: TfrxLineView
          Left = 502.000000000000000000
          Top = 80.110080000000010000
          Height = 18.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Memo15: TfrxMemoView
          Left = 21.000000000000000000
          Top = 114.110080000000000000
          Width = 33.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533)
          ParentFont = False
        end
        object Memo16: TfrxMemoView
          Left = 55.000000000000000000
          Top = 114.110080000000000000
          Width = 101.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533)
          ParentFont = False
        end
        object Memo17: TfrxMemoView
          Left = 157.000000000000000000
          Top = 114.110080000000000000
          Width = 188.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533#65533)
          ParentFont = False
        end
        object Memo18: TfrxMemoView
          Left = 346.000000000000000000
          Top = 114.110080000000000000
          Width = 51.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533#65533)
          ParentFont = False
        end
        object Memo19: TfrxMemoView
          Left = 399.000000000000000000
          Top = 114.110080000000000000
          Width = 62.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533)
          ParentFont = False
        end
        object Memo20: TfrxMemoView
          Left = 463.000000000000000000
          Top = 114.110080000000000000
          Width = 51.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533)
          ParentFont = False
        end
        object Memo21: TfrxMemoView
          Left = 515.000000000000000000
          Top = 114.110080000000000000
          Width = 40.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533#65533)
          ParentFont = False
        end
        object Memo22: TfrxMemoView
          Left = 555.000000000000000000
          Top = 114.110080000000000000
          Width = 37.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533#65533)
          ParentFont = False
        end
        object Memo23: TfrxMemoView
          Left = 593.000000000000000000
          Top = 114.110080000000000000
          Width = 42.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#1791#65533)
          ParentFont = False
        end
        object Memo24: TfrxMemoView
          Left = 636.000000000000000000
          Top = 114.110080000000000000
          Width = 64.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#65533#65533#65533)
          ParentFont = False
        end
        object Memo25: TfrxMemoView
          Left = 700.000000000000000000
          Top = 114.110080000000000000
          Width = 71.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #693#65533#65533)
          ParentFont = False
        end
      end
      object DetailData1: TfrxDetailData
        Height = 25.677180000000000000
        Top = 400.630180000000000000
        Width = 793.701300000000000000
        AllowSplit = True
        DataSet = frxDBorddetail
        DataSetName = 'frxDBorddetail'
        RowCount = 0
        Stretched = True
        object Memo26: TfrxMemoView
          Left = 21.000000000000000000
          Top = 2.369820000000004000
          Width = 33.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBorddetail."xuhao"]')
          ParentFont = False
        end
        object Memo27: TfrxMemoView
          Left = 54.000000000000000000
          Top = 2.369820000000004000
          Width = 102.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBorddetail."ISBN"]')
          ParentFont = False
        end
        object Memo28: TfrxMemoView
          Left = 157.000000000000000000
          Top = 2.369820000000004000
          Width = 188.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBorddetail."Name"]')
          ParentFont = False
        end
        object Memo29: TfrxMemoView
          Left = 346.000000000000000000
          Top = 2.369820000000004000
          Width = 51.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBorddetail."author"]')
          ParentFont = False
        end
        object Memo30: TfrxMemoView
          Left = 398.000000000000000000
          Top = 2.369820000000004000
          Width = 63.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBorddetail."abbreviatedname"]')
          ParentFont = False
        end
        object Memo31: TfrxMemoView
          Left = 461.000000000000000000
          Top = 2.369820000000004000
          Width = 53.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBorddetail."PressCount"]')
          ParentFont = False
        end
        object Memo32: TfrxMemoView
          Left = 514.000000000000000000
          Top = 2.369820000000004000
          Width = 41.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBorddetail."price"]')
          ParentFont = False
        end
        object Memo33: TfrxMemoView
          Left = 556.000000000000000000
          Top = 2.369820000000004000
          Width = 36.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBorddetail."amount"]')
          ParentFont = False
        end
        object Memo34: TfrxMemoView
          Left = 593.000000000000000000
          Top = 2.369820000000004000
          Width = 42.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          DisplayFormat.FormatStr = '#00%'
          DisplayFormat.Kind = fkNumeric
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBorddetail."discount"]')
          ParentFont = False
        end
        object Memo35: TfrxMemoView
          Left = 636.000000000000000000
          Top = 2.369820000000004000
          Width = 65.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          DisplayFormat.FormatStr = '##0.00'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBorddetail."fixedprice"]')
          ParentFont = False
        end
        object Memo36: TfrxMemoView
          Left = 700.000000000000000000
          Top = 2.369820000000004000
          Width = 71.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          DisplayFormat.FormatStr = '##0.00'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBorddetail."discountedprice"]')
          ParentFont = False
        end
        object Line15: TfrxLineView
          Align = baBottom
          Left = 21.000000000000000000
          Top = 25.677180000000000000
          Width = 750.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
      object ReportSummary1: TfrxReportSummary
        Height = 85.677180000000000000
        Top = 487.559370000000000000
        Width = 793.701300000000000000
        object Memo37: TfrxMemoView
          Left = 21.000000000000000000
          Top = 4.440629999999999000
          Width = 65.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#1020#65533)
          ParentFont = False
        end
        object Memo38: TfrxMemoView
          Left = 555.000000000000000000
          Top = 4.440629999999999000
          Width = 80.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[SUM(<frxDBorddetail."amount">,DetailData1)]')
          ParentFont = False
        end
        object Memo39: TfrxMemoView
          Left = 636.000000000000000000
          Top = 4.440629999999999000
          Width = 65.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          DisplayFormat.FormatStr = '##0.00'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[SUM(<frxDBorddetail."fixedprice">,DetailData1)]')
          ParentFont = False
        end
        object Memo40: TfrxMemoView
          Left = 702.000000000000000000
          Top = 4.440629999999999000
          Width = 69.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          DisplayFormat.FormatStr = '##0.00'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[SUM(<frxDBorddetail."discountedprice">,DetailData1)]')
          ParentFont = False
        end
        object Memo41: TfrxMemoView
          Left = 21.000000000000000000
          Top = 28.440630000000000000
          Width = 189.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #65533#437#65533#1329#65533#65533'[frxDBordhead."maker"]')
          ParentFont = False
        end
        object Memo42: TfrxMemoView
          Left = 21.000000000000000000
          Top = 49.440630000000000000
          Width = 750.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '["printbk"]')
          ParentFont = False
        end
        object Line16: TfrxLineView
          Left = 21.000000000000000000
          Top = 24.440630000000000000
          Width = 751.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
    end
  end
  object frxDBorddetail: TfrxDBDataset
    UserName = 'frxDBorddetail'
    CloseDataSource = False
    DataSet = aqorderdetail
    Left = 520
    Top = 64
  end
  object frxDBordhead: TfrxDBDataset
    UserName = 'frxDBordhead'
    CloseDataSource = False
    DataSet = aqorderhead
    Left = 592
    Top = 48
  end
  object frxstorage: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 40497.719494537000000000
    ReportOptions.LastChange = 42151.588679039350000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    OnGetValue = frxstorageGetValue
    Left = 104
    Top = 224
    Datasets = <
      item
        DataSet = frxDBstodetail
        DataSetName = 'frxDBstodetail'
      end
      item
        DataSet = frxDBstohead
        DataSetName = 'frxDBstohead'
      end>
    Variables = <>
    Style = <>
    object Data: TfrxDataPage
      Height = 1000.000000000000000000
      Width = 1000.000000000000000000
    end
    object Page1: TfrxReportPage
      PaperWidth = 210.000000000000000000
      PaperHeight = 297.000000000000000000
      PaperSize = 9
      TopMargin = 6.000000000000000000
      BottomMargin = 16.000000000000000000
      object ReportTitle1: TfrxReportTitle
        Height = 51.677180000000000000
        Top = 18.897650000000000000
        Width = 793.701300000000000000
        object Memo1: TfrxMemoView
          Align = baCenter
          Left = 55.106525000000000000
          Top = 23.102350000000000000
          Width = 683.488250000000000000
          Height = 24.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          HAlign = haCenter
          Memo.UTF8W = (
            '["title"]')
          ParentFont = False
        end
      end
      object PageHeader1: TfrxPageHeader
        Height = 37.677180000000000000
        Top = 94.488250000000000000
        Width = 793.701300000000000000
        object Memo2: TfrxMemoView
          Left = 600.000000000000000000
          Top = 14.511750000000000000
          Width = 187.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #31532'[Page#]'#39029#20849'[TotalPages#]'#39029)
          ParentFont = False
        end
      end
      object MasterData1: TfrxMasterData
        Height = 112.677180000000000000
        Top = 192.756030000000000000
        Width = 793.701300000000000000
        DataSet = frxDBstohead
        DataSetName = 'frxDBstohead'
        RowCount = 0
        object Memo3: TfrxMemoView
          Left = 18.897637800000000000
          Top = 6.243969999999990000
          Width = 183.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #20837#24211#21333#21495#65306'["Danhao"]')
          ParentFont = False
        end
        object Memo4: TfrxMemoView
          Left = 203.000000000000000000
          Top = 6.243969999999990000
          Width = 565.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #20379#24212#21830#21517#31216#65306'[frxDBstohead."Name_1"]')
          ParentFont = False
        end
        object Memo5: TfrxMemoView
          Left = 19.000000000000000000
          Top = 28.243970000000000000
          Width = 182.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #20837#24211#26085#26399#65306'[frxDBstohead."hdtime"]')
          ParentFont = False
        end
        object Memo6: TfrxMemoView
          Left = 202.000000000000000000
          Top = 28.243970000000000000
          Width = 270.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #20379#36135#32534#21495#65306'["supplycode"]')
          ParentFont = False
        end
        object Memo7: TfrxMemoView
          Left = 474.000000000000000000
          Top = 28.243970000000000000
          Width = 294.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #38468#21152#36153#29992#65306'[frxDBstohead."addcosts"]')
          ParentFont = False
        end
        object Memo8: TfrxMemoView
          Left = 19.000000000000000000
          Top = 50.243970000000000000
          Width = 182.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #24635#25968#37327#65306'[frxDBstohead."totalamount"]')
          ParentFont = False
        end
        object Memo9: TfrxMemoView
          Left = 205.000000000000000000
          Top = 50.243970000000000000
          Width = 267.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          DisplayFormat.FormatStr = '##0.00'
          DisplayFormat.Kind = fkNumeric
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #24635#30721#27915#65306'[frxDBstohead."totalfixedprice"]')
          ParentFont = False
        end
        object Memo10: TfrxMemoView
          Left = 474.000000000000000000
          Top = 50.243970000000000000
          Width = 294.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          DisplayFormat.FormatStr = '##0.00'
          DisplayFormat.Kind = fkNumeric
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #24635#23454#27915#65306'[frxDBstohead."totaldiscountedprice"]')
          ParentFont = False
        end
        object Line1: TfrxLineView
          Left = 20.000000000000000000
          Top = 6.243969999999990000
          Width = 749.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line2: TfrxLineView
          Left = 19.000000000000000000
          Top = 5.243969999999990000
          Height = 65.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Line3: TfrxLineView
          Left = 20.000000000000000000
          Top = 71.243970000000000000
          Width = 749.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line4: TfrxLineView
          Left = 769.000000000000000000
          Top = 7.243969999999990000
          Height = 63.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Line5: TfrxLineView
          Left = 20.000000000000000000
          Top = 27.243970000000000000
          Width = 749.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line6: TfrxLineView
          Left = 20.000000000000000000
          Top = 49.243970000000000000
          Width = 749.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Memo11: TfrxMemoView
          Left = 20.000000000000000000
          Top = 87.243970000000000000
          Width = 35.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #24207#21495)
          ParentFont = False
        end
        object Memo12: TfrxMemoView
          Left = 56.000000000000000000
          Top = 87.243970000000000000
          Width = 92.929190000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #20070#21495)
          ParentFont = False
        end
        object Memo13: TfrxMemoView
          Left = 149.440940000000000000
          Top = 87.243970000000000000
          Width = 225.504020000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #20070#21517)
          ParentFont = False
        end
        object Memo15: TfrxMemoView
          Left = 373.322820000000000000
          Top = 87.243970000000000000
          Width = 87.944960000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #20986#29256#31038)
          ParentFont = False
        end
        object Memo16: TfrxMemoView
          Left = 461.000000000000000000
          Top = 87.243970000000000000
          Width = 41.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #29256#27425)
          ParentFont = False
        end
        object Memo17: TfrxMemoView
          Left = 503.000000000000000000
          Top = 87.243970000000000000
          Width = 44.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #23450#20215)
          ParentFont = False
        end
        object Memo18: TfrxMemoView
          Left = 548.000000000000000000
          Top = 87.243970000000000000
          Width = 59.165430000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #25968#37327'(BC)')
          ParentFont = False
        end
        object Memo19: TfrxMemoView
          Left = 614.236240000000000000
          Top = 87.243970000000000000
          Width = 30.370130000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #25240#25187)
          ParentFont = False
        end
        object Memo20: TfrxMemoView
          Left = 644.118120000000000000
          Top = 87.243970000000000000
          Width = 51.370130000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #30721#27915)
          ParentFont = False
        end
        object Memo21: TfrxMemoView
          Left = 695.000000000000000000
          Top = 87.243970000000000000
          Width = 73.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #23454#27915)
          ParentFont = False
        end
        object Line7: TfrxLineView
          Left = 203.000000000000000000
          Top = 7.243969999999990000
          Height = 64.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Line8: TfrxLineView
          Left = 473.000000000000000000
          Top = 27.243970000000000000
          Height = 44.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
      end
      object DetailData1: TfrxDetailData
        Height = 28.960420000000000000
        Top = 328.819110000000000000
        Width = 793.701300000000000000
        AllowSplit = True
        DataSet = frxDBstodetail
        DataSetName = 'frxDBstodetail'
        RowCount = 0
        Stretched = True
        object Memo22: TfrxMemoView
          Left = 20.000000000000000000
          Top = 5.180889999999980000
          Width = 35.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBstodetail."xuhao"]')
          ParentFont = False
        end
        object Memo24: TfrxMemoView
          Left = 149.440940000000000000
          Top = 5.180889999999980000
          Width = 225.504020000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBstodetail."Name"]')
          ParentFont = False
        end
        object Memo26: TfrxMemoView
          Left = 374.322820000000000000
          Top = 5.180890000000000000
          Width = 86.165430000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBstodetail."abbreviatedname"]')
          ParentFont = False
        end
        object Memo27: TfrxMemoView
          Left = 461.000000000000000000
          Top = 5.180889999999980000
          Width = 41.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBstodetail."PressCount"]')
          ParentFont = False
        end
        object Memo28: TfrxMemoView
          Left = 503.000000000000000000
          Top = 5.180889999999980000
          Width = 46.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBstodetail."price"]')
          ParentFont = False
        end
        object Memo29: TfrxMemoView
          Left = 548.000000000000000000
          Top = 5.180890000000000000
          Width = 36.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBstodetail."amount"]')
          ParentFont = False
        end
        object Memo30: TfrxMemoView
          Left = 614.236240000000000000
          Top = 5.180890000000000000
          Width = 30.370130000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          DisplayFormat.FormatStr = '#00%'
          DisplayFormat.Kind = fkNumeric
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBstodetail."discount"]')
          ParentFont = False
        end
        object Memo31: TfrxMemoView
          Left = 644.118120000000000000
          Top = 5.180890000000000000
          Width = 51.370130000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          DisplayFormat.FormatStr = '##0.00'
          DisplayFormat.Kind = fkNumeric
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBstodetail."fixedprice"]')
          ParentFont = False
        end
        object Memo32: TfrxMemoView
          Left = 695.000000000000000000
          Top = 5.180889999999980000
          Width = 73.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          DisplayFormat.FormatStr = '##0.00'
          DisplayFormat.Kind = fkNumeric
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBstodetail."discountedprice"]')
          ParentFont = False
        end
        object Line9: TfrxLineView
          Left = 21.000000000000000000
          Top = 25.180890000000000000
          Width = 749.000000000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Diagonal = True
        end
        object Memo14: TfrxMemoView
          Left = 56.692950000000000000
          Top = 4.779530000000020000
          Width = 93.220470000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBstodetail."ISBN"]')
          ParentFont = False
        end
        object Memo44: TfrxMemoView
          Left = 583.937385000000000000
          Top = 4.779530000000000000
          Width = 28.346475000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[frxDBstodetail."camount"]')
          ParentFont = False
        end
      end
      object ReportSummary1: TfrxReportSummary
        Height = 171.944650000000000000
        Top = 419.527830000000000000
        Width = 793.701300000000000000
        object Memo33: TfrxMemoView
          Left = 20.000000000000000000
          Top = 5.472170000000010000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #21512#35745)
          ParentFont = False
        end
        object Memo34: TfrxMemoView
          Left = 536.220470000000000000
          Top = 5.472170000000000000
          Width = 49.252010000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[SUM(<frxDBstodetail."amount">,DetailData1)]')
          ParentFont = False
        end
        object Memo35: TfrxMemoView
          Left = 635.118120000000000000
          Top = 5.472170000000000000
          Width = 61.929190000000000000
          Height = 18.897650000000000000
          ShowHint = False
          DisplayFormat.FormatStr = '##0.00'
          DisplayFormat.Kind = fkNumeric
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[SUM(<frxDBstodetail."fixedprice">,DetailData1)]')
          ParentFont = False
        end
        object Memo36: TfrxMemoView
          Left = 696.559060000000000000
          Top = 5.472170000000000000
          Width = 71.929190000000000000
          Height = 18.897650000000000000
          ShowHint = False
          DisplayFormat.FormatStr = '##0.00'
          DisplayFormat.Kind = fkNumeric
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[SUM(<frxDBstodetail."discountedprice">,DetailData1)]')
          ParentFont = False
        end
        object Line10: TfrxLineView
          Left = 21.000000000000000000
          Top = 24.472170000000000000
          Width = 748.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Memo37: TfrxMemoView
          Left = 19.000000000000000000
          Top = 32.472170000000000000
          Width = 188.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #21046#21333#21592#65306'[frxDBstohead."op"]')
          ParentFont = False
        end
        object Memo38: TfrxMemoView
          Left = 19.000000000000000000
          Top = 53.692640000000000000
          Width = 749.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #22791#27880#65306'[frxDBstohead."remarks"]')
          ParentFont = False
        end
        object Memo39: TfrxMemoView
          Left = 19.000000000000000000
          Top = 121.606060000000000000
          Width = 749.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '["rkbk"]')
          ParentFont = False
        end
        object Memo40: TfrxMemoView
          Left = 516.000000000000000000
          Top = 147.826530000000000000
          Width = 252.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #36719#20214#25903#25345#65306#20808#34892#32773#22270#20070#36719#20214'028-85225892')
          ParentFont = False
        end
        object Memo23: TfrxMemoView
          Left = 19.236240000000000000
          Top = 74.811070000000000000
          Width = 188.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #32852#31995#20154#65306'["contact"]')
          ParentFont = False
        end
        object Memo25: TfrxMemoView
          Left = 381.732530000000000000
          Top = 76.590600000000000000
          Width = 388.803340000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #32852#31995#30005#35805#65306'["telephone"]')
          ParentFont = False
        end
        object Memo41: TfrxMemoView
          Left = 18.897650000000000000
          Top = 98.267780000000000000
          Width = 751.638220000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #22320#22336#65306'["address"]')
          ParentFont = False
        end
        object Memo42: TfrxMemoView
          Left = 254.669450000000000000
          Top = 32.015770000000000000
          Width = 188.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #23457#26680#21592#65306)
          ParentFont = False
        end
        object Memo43: TfrxMemoView
          Left = 515.441250000000000000
          Top = 31.015770000000000000
          Width = 188.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            #25171#21253#21592#65306)
          ParentFont = False
        end
        object Memo45: TfrxMemoView
          Left = 583.827150000000000000
          Top = 4.889765000000000000
          Width = 37.795300000000000000
          Height = 20.787415000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Memo.UTF8W = (
            '[SUM(<frxDBstodetail."camount">,DetailData1)]')
          ParentFont = False
        end
      end
    end
  end
  object frxDBstohead: TfrxDBDataset
    UserName = 'frxDBstohead'
    CloseDataSource = False
    DataSet = aqhead
    Left = 32
    Top = 64
  end
  object frxDBstodetail: TfrxDBDataset
    UserName = 'frxDBstodetail'
    CloseDataSource = False
    DataSet = aqrvstoragedetail
    Left = 88
    Top = 16
  end
  object frxBarCodeObject1: TfrxBarCodeObject
    Left = 376
    Top = 264
  end
  object frxWsale: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 38006.786384259300000000
    ReportOptions.LastChange = 42157.624081342600000000
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      ''
      
        'void Cross1OnCalcWidth(int ColumnIndex, variant ColumnValues, fl' +
        'oat &Width)'
      '{'
      '       if (VarToStr(ColumnValues[0]) == "'#24207#21495'")   '
      '       {'
      '               Width = <"xuhao"> ;  '
      '       }'
      '       if (VarToStr(ColumnValues[0]) == "'#20869#37096#35782#21035'")     '
      '       {'
      '               Width = <"incode"> ;  '
      '       }           '
      '       if (VarToStr(ColumnValues[0]) == "'#20070#21495'")   '
      '       {'
      '               Width = <"ISBN"> ;  '
      '       }    '
      '       if (VarToStr(ColumnValues[0]) =="'#20070#21517'")'
      '       {'
      '               Width = <"CatalogName">;'
      '       }  '
      '       if (VarToStr(ColumnValues[0]) == "'#23450#20215'")   '
      '       {'
      '               Width = <"Price">;'
      '       }'
      '       if (VarToStr(ColumnValues[0]) == "'#20316#32773'")   '
      '       {'
      '               Width = <"Author">;'
      '       }    '
      '       if (VarToStr(ColumnValues[0]) =="'#20986#29256#31038'")'
      '       {  '
      '               Width = <"AbbreviatedName">;  '
      '       }'
      '       if (VarToStr(ColumnValues[0]) == "'#20986#29256#26085#26399'")   '
      '       {'
      '               Width = <"Pressdate">;'
      '       }'
      '       if (VarToStr(ColumnValues[0]) == "'#29256#27425'")   '
      '       {'
      '               Width = <"PressCount">;'
      '       }    '
      '       if (VarToStr(ColumnValues[0]) =="'#23383#25968'")'
      '       {  '
      '               Width = <"BookWords">;'
      '       }                            '
      '       if (VarToStr(ColumnValues[0]) =="'#25968#37327'")'
      '       {  '
      '               Width = <"Amount">;'
      '       }'
      '       if (VarToStr(ColumnValues[0]) =="'#25240#25187'")'
      '       {  '
      '               Width = <"Discount">;'
      '       }'
      ''
      '       if (VarToStr(ColumnValues[0]) =="'#30721#27915'")'
      '       {  '
      '               Width = <"FixedPrice">;'
      '       }    '
      '       if (VarToStr(ColumnValues[0]) =="'#23454#27915'")'
      '       {  '
      '               Width = <"DiscountedPrice">;'
      '       }'
      '    '
      '       if (VarToStr(ColumnValues[0]) =="'#33719#22870#24773#20917'")'
      '       {  '
      '               Width = <"huojiangstate">;'
      '       }'
      '       if (VarToStr(ColumnValues[0]) == "'#26657#21306'")   '
      '       {'
      '               Width = <"xiaoqu">;'
      '       }'
      '       if (VarToStr(ColumnValues[0]) == "'#23398#38498'")   '
      '       {'
      '               Width = <"xueyuan">;'
      '       }    '
      '       if (VarToStr(ColumnValues[0]) =="'#35838#31243#21517#31216'")'
      '       {  '
      '               Width = <"course">;'
      '       }'
      '       if (VarToStr(ColumnValues[0]) =="'#24180#32423'")    '
      '       {  '
      '               Width = <"class">;'
      '       }'
      '       if (VarToStr(ColumnValues[0]) =="'#31867#21035'")    '
      '       {  '
      '               Width = <"typename">;'
      '       }           '
      ''
      '}'
      ''
      '{}    '
      '      ')
    OnBeforePrint = frxWsaleBeforePrint
    OnGetValue = frxWsaleGetValue
    Left = 144
    Top = 352
    Datasets = <
      item
        DataSet = frxDBwsalehead
        DataSetName = 'frxDBwsalehead'
      end>
    Variables = <>
    Style = <>
    object Data: TfrxDataPage
      Height = 1000.000000000000000000
      Width = 1000.000000000000000000
    end
    object Page1: TfrxReportPage
      PaperWidth = 230.000000000000000000
      PaperHeight = 297.000000000000000000
      PaperSize = 256
      LeftMargin = 5.000000000000000000
      RightMargin = 10.000000000000000000
      TopMargin = 3.000000000000000000
      BottomMargin = 10.000000000000000000
      object MasterData2: TfrxMasterData
        Height = 81.000000000000000000
        Top = 321.260050000000000000
        Width = 812.598950000000000000
        AllowSplit = True
        RowCount = 1
        Stretched = True
        object Cross3: TfrxCrossView
          Left = 18.897637800000000000
          Width = 99.000000000000000000
          Height = 81.000000000000000000
          ShowHint = False
          Border = False
          DownThenAcross = False
          MaxWidth = 210
          RepeatHeaders = False
          ShowColumnTotal = False
          ShowCorner = False
          ShowRowHeader = False
          ShowRowTotal = False
          ShowTitle = False
          OnCalcWidth = 'Cross1OnCalcWidth'
          Memos = {
            3C3F786D6C2076657273696F6E3D22312E312220656E636F64696E673D227574
            662D38223F3E3C63726F73733E3C63656C6C6D656D6F733E3C546672784D656D
            6F5669657720416C69676E3D2262614C65667422204C6566743D2233382E3839
            37363337382220546F703D223336312E3236303035222057696474683D223539
            22204865696768743D22323122205265737472696374696F6E733D2232342220
            53686F7748696E743D2246616C73652220537472657463684D6F64653D22736D
            4D61784865696768742220416C6C6F7745787072657373696F6E733D2246616C
            73652220446973706C6179466F726D61742E446563696D616C53657061726174
            6F723D22322220446973706C6179466F726D61742E466F726D61745374723D22
            25322E326D2220466F6E742E436861727365743D22312220466F6E742E436F6C
            6F723D22302220466F6E742E4865696768743D222D31322220466F6E742E4E61
            6D653D22417269616C2220466F6E742E5374796C653D223022204672616D652E
            536861646F77436F6C6F723D22313637373732313522204672616D652E536861
            646F7757696474683D223022204672616D652E5479703D223822204672616D65
            2E4C6566744C696E652E57696474683D223022204672616D652E546F704C696E
            652E436F6C6F723D223533363837303931312220476170583D22332220476170
            593D22332220506172656E74466F6E743D2246616C73652220546578743D2230
            222F3E3C546672784D656D6F56696577205461673D223122204C6566743D2230
            2220546F703D223431222057696474683D22353922204865696768743D223232
            22205265737472696374696F6E733D223234222053686F7748696E743D224661
            6C73652220416C6C6F7745787072657373696F6E733D2246616C736522204672
            616D652E5479703D2231352220476170583D22332220476170593D2233222048
            416C69676E3D226861526967687422205374796C653D2263656C6C222056416C
            69676E3D22766143656E7465722220546578743D22222F3E3C546672784D656D
            6F56696577205461673D223222204C6566743D2235392220546F703D22323222
            2057696474683D22383122204865696768743D22323122205265737472696374
            696F6E733D223234222053686F7748696E743D2246616C73652220416C6C6F77
            45787072657373696F6E733D2246616C736522204672616D652E5479703D2231
            352220476170583D22332220476170593D2233222048416C69676E3D22686152
            6967687422205374796C653D2263656C6C222056416C69676E3D22766143656E
            7465722220546578743D22222F3E3C546672784D656D6F56696577205461673D
            223322204C6566743D22302220546F703D2230222057696474683D2230222048
            65696768743D223022205265737472696374696F6E733D2238222053686F7748
            696E743D2246616C73652220416C6C6F7745787072657373696F6E733D224661
            6C736522204672616D652E5479703D2231352220476170583D22332220476170
            593D2233222048416C69676E3D226861526967687422205374796C653D226365
            6C6C222056416C69676E3D22766143656E7465722220546578743D22222F3E3C
            2F63656C6C6D656D6F733E3C63656C6C6865616465726D656D6F733E3C546672
            784D656D6F56696577204C6566743D22302220546F703D223022205769647468
            3D223022204865696768743D223022205265737472696374696F6E733D223822
            2053686F7748696E743D2246616C73652220416C6C6F7745787072657373696F
            6E733D2246616C736522204672616D652E5479703D2231352220476170583D22
            332220476170593D2233222056416C69676E3D22766143656E74657222205465
            78743D22222F3E3C546672784D656D6F56696577204C6566743D22302220546F
            703D2230222057696474683D223022204865696768743D223022205265737472
            696374696F6E733D2238222053686F7748696E743D2246616C73652220416C6C
            6F7745787072657373696F6E733D2246616C736522204672616D652E5479703D
            2231352220476170583D22332220476170593D2233222056416C69676E3D2276
            6143656E7465722220546578743D22222F3E3C2F63656C6C6865616465726D65
            6D6F733E3C636F6C756D6E6D656D6F733E3C546672784D656D6F566965772054
            61673D223130302220416C69676E3D2262614C65667422204C6566743D223338
            2E383937363337382220546F703D223334312E3236303035222057696474683D
            22353922204865696768743D22323022205265737472696374696F6E733D2232
            34222053686F7748696E743D2246616C73652220416C6C6F7745787072657373
            696F6E733D2246616C73652220436F6C6F723D2231363737373231352220466F
            6E742E436861727365743D22312220466F6E742E436F6C6F723D22302220466F
            6E742E4865696768743D222D31322220466F6E742E4E616D653D22417269616C
            2220466F6E742E5374796C653D22312220476170583D22332220476170593D22
            332220506172656E74466F6E743D2246616C736522205374796C653D22636F6C
            756D6E2220546578743D22222F3E3C2F636F6C756D6E6D656D6F733E3C636F6C
            756D6E746F74616C6D656D6F733E3C546672784D656D6F56696577205461673D
            2233303022204C6566743D2235392220546F703D2230222057696474683D2238
            3122204865696768743D22323222205265737472696374696F6E733D22382220
            56697369626C653D2246616C7365222053686F7748696E743D2246616C736522
            20416C6C6F7745787072657373696F6E733D2246616C73652220466F6E742E43
            6861727365743D22312220466F6E742E436F6C6F723D22302220466F6E742E48
            65696768743D222D31332220466F6E742E4E616D653D22417269616C2220466F
            6E742E5374796C653D223122204672616D652E5479703D223135222047617058
            3D22332220476170593D2233222048416C69676E3D22686143656E7465722220
            506172656E74466F6E743D2246616C736522205374796C653D22636F6C677261
            6E64222056416C69676E3D22766143656E7465722220546578743D224772616E
            6420546F74616C222F3E3C2F636F6C756D6E746F74616C6D656D6F733E3C636F
            726E65726D656D6F733E3C546672784D656D6F56696577204C6566743D223022
            20546F703D2230222057696474683D2232313022204865696768743D22302220
            5265737472696374696F6E733D2238222056697369626C653D2246616C736522
            2053686F7748696E743D2246616C73652220416C6C6F7745787072657373696F
            6E733D2246616C736522204672616D652E5479703D2231352220476170583D22
            332220476170593D2233222048416C69676E3D22686143656E74657222205641
            6C69676E3D22766143656E7465722220546578743D22222F3E3C546672784D65
            6D6F56696577204C6566743D2233382E383937363337382220546F703D223334
            312E3236303035222057696474683D22353922204865696768743D2230222052
            65737472696374696F6E733D2238222056697369626C653D2246616C73652220
            53686F7748696E743D2246616C73652220416C6C6F7745787072657373696F6E
            733D2246616C736522204672616D652E5479703D2231352220476170583D2233
            2220476170593D2233222048416C69676E3D22686143656E746572222056416C
            69676E3D22766143656E7465722220546578743D22222F3E3C546672784D656D
            6F56696577204C6566743D22302220546F703D2230222057696474683D223022
            204865696768743D223022205265737472696374696F6E733D22382220566973
            69626C653D2246616C7365222053686F7748696E743D2246616C73652220416C
            6C6F7745787072657373696F6E733D2246616C736522204672616D652E547970
            3D2231352220476170583D22332220476170593D2233222048416C69676E3D22
            686143656E746572222056416C69676E3D22766143656E746572222054657874
            3D22222F3E3C546672784D656D6F56696577204C6566743D22302220546F703D
            2230222057696474683D2232313022204865696768743D223022205265737472
            696374696F6E733D2238222053686F7748696E743D2246616C73652220416C6C
            6F7745787072657373696F6E733D2246616C736522204672616D652E5479703D
            2231352220476170583D22332220476170593D2233222048416C69676E3D2268
            6143656E746572222056416C69676E3D22766143656E7465722220546578743D
            22222F3E3C2F636F726E65726D656D6F733E3C726F776D656D6F733E3C546672
            784D656D6F56696577205461673D2232303022204C6566743D22302220546F70
            3D223230222057696474683D2232313022204865696768743D22323122205265
            737472696374696F6E733D223234222053686F7748696E743D2246616C736522
            20416C6C6F7745787072657373696F6E733D2246616C736522204672616D652E
            5479703D2231352220476170583D22332220476170593D2233222048416C6967
            6E3D22686143656E74657222205374796C653D22726F77222056416C69676E3D
            22766143656E7465722220546578743D22222F3E3C2F726F776D656D6F733E3C
            726F77746F74616C6D656D6F733E3C546672784D656D6F56696577205461673D
            2234303022204C6566743D22302220546F703D2230222057696474683D223230
            3022204865696768743D223022205265737472696374696F6E733D2238222056
            697369626C653D2246616C7365222053686F7748696E743D2246616C73652220
            416C6C6F7745787072657373696F6E733D2246616C73652220466F6E742E4368
            61727365743D22312220466F6E742E436F6C6F723D22302220466F6E742E4865
            696768743D222D31332220466F6E742E4E616D653D22417269616C2220466F6E
            742E5374796C653D223122204672616D652E5479703D2231352220476170583D
            22332220476170593D2233222048416C69676E3D22686143656E746572222050
            6172656E74466F6E743D2246616C736522205374796C653D22726F776772616E
            64222056416C69676E3D22766143656E7465722220546578743D224772616E64
            20546F74616C222F3E3C2F726F77746F74616C6D656D6F733E3C63656C6C6675
            6E6374696F6E733E3C6974656D20302F3E3C2F63656C6C66756E6374696F6E73
            3E3C636F6C756D6E736F72743E3C6974656D20322F3E3C2F636F6C756D6E736F
            72743E3C726F77736F72743E3C6974656D20302F3E3C2F726F77736F72743E3C
            2F63726F73733E}
        end
      end
      object ReportSummary1: TfrxReportSummary
        Height = 72.322510000000000000
        Top = 506.457020000000000000
        Width = 812.598950000000000000
        object Memo29: TfrxMemoView
          Left = 4.677167800000000000
          Top = 3.322510000000000000
          Width = 198.488250000000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            #21046#21333#21592':[frxDBwsalehead."maker"]')
          ParentFont = False
        end
        object Memo30: TfrxMemoView
          Left = 238.000000000000000000
          Top = 3.267577400000000000
          Width = 50.988250000000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            #25315#36135#21592':')
          ParentFont = False
        end
        object Memo31: TfrxMemoView
          Left = 398.000000000000000000
          Top = 4.488047400000000000
          Width = 164.488250000000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            #25315#36135#21592':')
          ParentFont = False
        end
        object Memo33: TfrxMemoView
          Left = 1.000000000000000000
          Top = 29.881570000000000000
          Width = 754.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #26412#21333#22791#27880':[frxDBwsalehead."Remarks"]')
          ParentFont = False
        end
        object Memo37: TfrxMemoView
          Left = 288.500000000000000000
          Top = 3.488047400000000000
          Width = 109.988250000000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Memo1: TfrxMemoView
          Left = 1.000000000000000000
          Top = 45.779220000000000000
          Width = 754.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            '["pxbk"]')
          ParentFont = False
        end
        object Line1: TfrxLineView
          Left = 3.000000000000000000
          Top = 1.322510000000000000
          Width = 752.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line10: TfrxLineView
          Left = 2.000000000000000000
          Top = 27.779220000000000000
          Width = 754.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
      object MasterData1: TfrxMasterData
        Height = 183.677180000000000000
        Top = 113.385900000000000000
        Width = 812.598950000000000000
        DataSet = frxDBwsalehead
        DataSetName = 'frxDBwsalehead'
        RowCount = 0
        object Memo3: TfrxMemoView
          Align = baCenter
          Left = 52.555350000000000000
          Top = 20.432900000000000000
          Width = 707.488250000000000000
          Height = 26.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -21
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          HAlign = haCenter
          Memo.UTF8W = (
            '["title"]')
          ParentFont = False
        end
        object Memo5: TfrxMemoView
          Left = 1.889763780000000000
          Top = 86.929133860000000000
          Width = 73.228346460000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = []
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            #23458#25143#21517#31216':')
          ParentFont = False
        end
        object Memo6: TfrxMemoView
          Left = 1.889763780000000000
          Top = 109.606299210000000000
          Width = 73.228346460000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = []
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            #23458#25143#22320#22336':')
          ParentFont = False
        end
        object Memo7: TfrxMemoView
          Left = 1.889763780000000000
          Top = 132.283464570000000000
          Width = 73.238250000000000000
          Height = 22.397650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = []
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            #32852#31995#30005#35805':')
          ParentFont = False
        end
        object Memo8: TfrxMemoView
          Left = 1.889763780000000000
          Top = 154.960629920000000000
          Width = 108.488250000000000000
          Height = 26.078742600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = []
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            #21512#35745'('#20154#27665#24065#22823#24065')')
          ParentFont = False
        end
        object Memo10: TfrxMemoView
          Left = 542.889763780000000000
          Top = 87.929133860000000000
          Width = 61.047310000000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = []
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            #24635#25968#37327#65306)
          ParentFont = False
        end
        object Memo11: TfrxMemoView
          Left = 541.889763780000000000
          Top = 111.606299210000000000
          Width = 58.238250000000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = []
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            #24635#30721#27915#65306)
          ParentFont = False
        end
        object Memo12: TfrxMemoView
          Left = 541.889763780000000000
          Top = 133.283464570000000000
          Width = 58.267780000000000000
          Height = 23.049212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = []
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            #24635#23454#27915#65306)
          ParentFont = False
        end
        object Memo13: TfrxMemoView
          Left = 309.889763780000000000
          Top = 134.283464570000000000
          Width = 69.488250000000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = #23435#20307
          Font.Style = []
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            #32852#31995#20154#65306)
          ParentFont = False
        end
        object Memo14: TfrxMemoView
          Left = 1.889763780000000000
          Top = 59.682900000000000000
          Width = 486.635900000000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            #21457#36135#21333#21495#65306'["Danhao"]')
          ParentFont = False
        end
        object Memo17: TfrxMemoView
          Left = 76.889763780000000000
          Top = 135.403384650000000000
          Width = 224.488250000000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            '[frxDBwsalehead."telephone"]')
          ParentFont = False
        end
        object Memo18: TfrxMemoView
          Left = 374.889763780000000000
          Top = 133.456534250000000000
          Width = 165.238250000000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            '[frxDBwsalehead."Contact"]')
          ParentFont = False
        end
        object Memo19: TfrxMemoView
          Left = 107.889763780000000000
          Top = 154.960629920000000000
          Width = 644.488250000000000000
          Height = 26.078742600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            '["heji"]')
          ParentFont = False
        end
        object Memo20: TfrxMemoView
          Left = 601.889763780000000000
          Top = 60.936849210000000000
          Width = 152.488250000000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            #21457#36135#26085#26399#65306'[frxDBwsalehead."hdtime"]')
          ParentFont = False
        end
        object Memo22: TfrxMemoView
          Left = 601.889763780000000000
          Top = 111.606299210000000000
          Width = 152.238250000000000000
          Height = 22.299212600000000000
          ShowHint = False
          DisplayFormat.FormatStr = '##0.00'
          DisplayFormat.Kind = fkNumeric
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            '[frxDBwsalehead."fixedprice"]')
          ParentFont = False
        end
        object Memo23: TfrxMemoView
          Left = 601.889763780000000000
          Top = 134.456534250000000000
          Width = 151.238250000000000000
          Height = 22.299212600000000000
          ShowHint = False
          DisplayFormat.FormatStr = '##0.00'
          DisplayFormat.Kind = fkNumeric
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            '[frxDBwsalehead."discountedprice"]')
          ParentFont = False
        end
        object Memo4: TfrxMemoView
          Left = 76.889763780000000000
          Top = 87.929133860000000000
          Width = 465.228346460000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            '["ClientName"]')
          ParentFont = False
        end
        object Memo9: TfrxMemoView
          Left = 601.889763780000000000
          Top = 87.929133860000000000
          Width = 148.047310000000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #23435#20307
          Font.Style = [fsBold]
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            '[frxDBwsalehead."totalamount"]')
          ParentFont = False
        end
        object Memo15: TfrxMemoView
          Left = 76.889763780000000000
          Top = 110.606299210000000000
          Width = 465.228346460000000000
          Height = 22.299212600000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          GapX = 5.000000000000000000
          GapY = 4.000000000000000000
          Memo.UTF8W = (
            '[frxDBwsalehead."Address"]')
          ParentFont = False
        end
        object Line2: TfrxLineView
          Left = 1.889763779527560000
          Top = 86.495980000000000000
          Width = 752.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line3: TfrxLineView
          Left = 0.889763780000000000
          Top = 181.495980000000000000
          Width = 753.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line4: TfrxLineView
          Left = 1.889763779527560000
          Top = 87.495980000000000000
          Height = 92.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Line5: TfrxLineView
          Left = 1.889763780000000000
          Top = 86.495980000000000000
          Height = 95.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Line6: TfrxLineView
          Left = 2.889763780000000000
          Top = 110.495980000000000000
          Width = 752.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line7: TfrxLineView
          Left = 1.889763780000000000
          Top = 133.495980000000000000
          Width = 751.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line8: TfrxLineView
          Left = 1.889763780000000000
          Top = 156.495980000000000000
          Width = 751.000000000000000000
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Line9: TfrxLineView
          Left = 1.889763780000000000
          Top = 87.495980000000000000
          Height = 68.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Line11: TfrxLineView
          Left = 753.000000000000000000
          Top = 86.495980000000000000
          Height = 95.000000000000000000
          ShowHint = False
          Frame.Typ = [ftLeft]
        end
        object Picture1: TfrxPictureView
          Left = 3.779530000000000000
          Top = 3.779530000000000000
          Width = 105.826840000000000000
          Height = 56.692950000000000000
          ShowHint = False
          Picture.Data = {
            0A544A504547496D616765E0400100FFD8FFE000104A46494600010101012C01
            2C0000FFE11F164578696600004D4D002A000000080007011200030000000100
            010000011A00050000000100000062011B0005000000010000006A0128000300
            00000100020000013100020000001B0000007201320002000000140000008E87
            69000400000001000000A2000000CE0000012C000000010000012C0000000141
            646F62652050686F746F73686F702043532057696E646F77730000323031353A
            30363A30322030393A30323A3134000003A001000300000001FFFF0000A00200
            04000000010000020CA0030004000000010000020C0000000000000006010300
            030000000100060000011A0005000000010000011C011B000500000001000001
            2401280003000000010002000002010004000000010000012C02020004000000
            0100001DE10000000000000048000000010000004800000001FFD8FFDB004300
            080606070605080707070909080A0C140D0C0B0B0C1912130F141D1A1F1E1D1A
            1C1C20242E2720222C231C1C2837292C30313434341F27393D38323C2E333432
            FFDB0043010909090C0B0C180D0D1832211C2132323232323232323232323232
            3232323232323232323232323232323232323232323232323232323232323232
            3232323232FFC0001108006700A003012100021101031101FFC4001F00000105
            01010101010100000000000000000102030405060708090A0BFFC400B5100002
            010303020403050504040000017D010203000411051221314106135161072271
            14328191A1082342B1C11552D1F02433627282090A161718191A25262728292A
            3435363738393A434445464748494A535455565758595A636465666768696A73
            7475767778797A838485868788898A92939495969798999AA2A3A4A5A6A7A8A9
            AAB2B3B4B5B6B7B8B9BAC2C3C4C5C6C7C8C9CAD2D3D4D5D6D7D8D9DAE1E2E3E4
            E5E6E7E8E9EAF1F2F3F4F5F6F7F8F9FAFFC4001F010003010101010101010101
            0000000000000102030405060708090A0BFFC400B51100020102040403040705
            040400010277000102031104052131061241510761711322328108144291A1B1
            C109233352F0156272D10A162434E125F11718191A262728292A35363738393A
            434445464748494A535455565758595A636465666768696A737475767778797A
            82838485868788898A92939495969798999AA2A3A4A5A6A7A8A9AAB2B3B4B5B6
            B7B8B9BAC2C3C4C5C6C7C8C9CAD2D3D4D5D6D7D8D9DAE2E3E4E5E6E7E8E9EAF2
            F3F4F5F6F7F8F9FAFFDA000C03010002110311003F00F72D4B58D3B4783CED46
            F60B54209065700B6064851D49F61CD79AEB9F19920B99E0D1AC22B88D48F2AE
            E5760ADC0CFEEF00F5C8EBDAB0AD5D53D16E7B794E4B531D2E69DE30EF6DFC97
            F9EB630FFE173788BFE7CF4BFF00BF527FF175049F17FC4CFF00756C63FF0076
            13FD58D72BC5D43E9A3C2D824F5727F35FA22ABFC55F163138BD857E96E9FD45
            307C52F170393A9211E86DE3FF00E26A7EB353B9D0B8732F4BE07F7BFF0032E4
            3F17BC4F1637FD8A6FF7E123FF004122A7FF0085CDE22FF9F3D2FF00EFD49FFC
            5D52C5D439E7C2D8293BA725F35FAA6397E33F88011BAC74C23B811C83FF0067
            ABD0FC6CBC503CED12073DF64E57F9834D62E5D518D4E13C3B5FBBA8D7AD9FF9
            163FE177FF00D4BDFF0093BFFDAE8FF85DFF00F52F7FE4EFFF006BAAFAE7F74E
            7FF547FE9F7FE4BFFDB07FC2EFFF00A97BFF00277FFB5D3E2F8DD19900974074
            4EE52EC31FC8A0FE74FEB9E427C22EDA56FF00C97FE09A49F1A34023E7B0D481
            F648CFFECE2ACDBFC5EF0CCDFEB3EDB07FD74841FF00D049AB58B83DCE19F0B6
            362AF1717F37FAA3A0B1F19681A9D85D5E59EA31CB15AC6D2CCBB583A2A8C93B
            080C463B8153E97E29D1359B3B8BBB1D462920B7FF005CCD98FCB18CE5830040
            EBCF4E0FA1AD95583B599E4D4CB7154949CE1F0B49FABDBEFF0022EB6A56290C
            12B5E5BAC570556173200252DF7429EF9ED8EB5681CD5A699C7284A3F12B1F39
            7C486BB1E3BD4A2BBBA6B831B2888918091950CA807B06C7B9C9EA6BB2D2FE0C
            C3369B049A86A6E974E32EB6F8641CF182473C63F1AF3E34BDA5495DEC7DEE27
            3559760683A50F892D3A5ACAFF003D57E25CFF00852BA67FD05AEFFEF85A9A1F
            82FA1AA9F3B50D41DB3C146451FAA9AD96123DCF2A5C5789B7BB08FE3FE6893F
            E14C787BFE7F354FFBFB1FFF001159DAF7C31F0CF87B43BCD5E77D72EA0B38CC
            B2C56F2445CA0FBC402AA3819279E80D3FAA43BB33FF005AB1BFCB1FB9FF00F2
            463783BC3DF0F3C7B1CADA46A1AC453C00196D6778D64519C06C6D208F704E38
            CE335D57FC298F0EFF00CFEEA9FF007F63FF00E228FAA43BB05C558DFE58FDCF
            FCC3FE14C7877FE7F754FF00BFB1FF00F114E8FE0D786D1B2D73A938F469531F
            A20A3EA90EEC4F8AB1AD7C31FB9FF997A2F853E138C61ACE694FABDC3FF422A6
            1F0BFC1E3FE6144FD6E65FFE2AAFEAD4FB1CB2E22CC5BBA9DBE4BFC85FF8561E
            0FFF00A047FE4CCDFF00C5D1FF000AC3C1FF00F408FF00C999BFF8BA3EAF4BB1
            3FEB0663FF003F3F08FF00907FC2B0F07FFD023FF2666FFE2EACC9F0FF00C30F
            A51D386951243BB7065CF980E73F7CE5BF5E9C53FABD35B22259EE6126B9AA6C
            EFB25F92575E41A67803C35A45F457D65A7B477311252433C8D8C823A16C7427
            B54165F0F746D37C4326AF64D71099432BDA2BAF90CAC3054AE33B73CE338040
            EC3147B082B5BA09E758B9B9BA8D4B9A3CBAAFB9AB5B5577666178ABE13586A0
            B2DDE8856CAEB96F23FE58B9E4F03F80F3DB8E3A0EB557E10F8A2E2F629B40BA
            6797ECD1F9B6F21E76C608050F7E0918F6247400564A1ECAB2B6CCF5658A7996
            573557E3A5677EFF00F06D7FC0F36F195C4975E34D66490E596F248C7D158A8F
            D00AFA4F4FB7369A6DADB13930C291F5CF4007F4A586D67265F115A385C34176
            FC9444D4750B6D274DB9D42F6431DADB46D2CCE119B6A019270A09381E82BCCB
            52F8F3A1B5C8B2F0CE97A96BF7AD8F2D2084C68FEA06417C8FF72BB0F9238AD6
            FE2CFC44F0AF8D6D0F88ECA0B2B1942CA74D458DC180B152448A4B6FE0F7EA3E
            EE38AF52F8BDE204F0F7C34D5642CA27BD8FEC502907E669010D8C742137B73F
            DDA00E1FE05F85AD7C35E1DB8F196B8FF6096E94C50C975308E316C7690C738C
            6E61C13D400470727AAD6FE39F81F46768E3BE9F52955F632D843BC0F7DEC555
            87B8268017C2DF1B3C2DE2BD761D1EDE2BFB3B99F2216BB8D151D8745055CE18
            8E99E3B672403E8F4005140051400573BE26F1D7873C1D25BA6BDA81B46B90C6
            2FDC4926E0B8CFDC53D322803674FD46CF55B18AFB4FBA86EAD6504C7342E1D5
            B0707047A1047D4559A002BC23E0ECC91F8D26463832D93A2FB9DC8DFC81AE6A
            DFC481F4394A6F018BB768FF00EDC729E2A3FF00157EB47FE9FE7FFD18D5F510
            E95185F8A475F12FF070DE8FF2899DAFD947A9787354B095B6C773692C2EDE81
            90827F5AF23F016B90781FE025AF896DB4B82E984EC6F8097CA7706768C1CED3
            96194E0E38CF3EBD87C999FF001A1ADF5EF157802144602F58128E30C1247880
            04763D7F5AEA3C4FE11D43E21FC465B7D66292DBC29A1852064AFDBA575576C1
            E30A32149E71B480416254037BC5FF000AFC3BE359AD25D41AF607B54F2E316B
            3ED509FDD08C0AA8FF007403EBD0559D2FE17F82748B436F0786F4F9949DC5EE
            E1170E4E00FBD2648E9D0607B50078BFC31F07D95C7C72D6D16D9869DA15CDC3
            DBA72CAAEB2948949393C0CB0E7394AF56F8AFE36D63C07A469DAAE9B6D63716
            F25D791729701F772A597615200E15B24E7B71401D37847C49078BBC2B61AEDB
            C2D0C776849898E4A32B1565CF701948CE067AD45E2FD6AE345D22392D149B8B
            898428E223208860B3B9507242A2B1C0EE054CDB516D1D184A4AB578C25B37AF
            A753CFFC21E25D6ECBC47A7DADEEA5717FA5DF611A5B8407CB99932143024E72
            00C13DC9C77AF5FACA84A4E3691E8E7742952AF19528F2A92BD9747769FE8647
            88759BAD1AC964B2D16F756B9918A4705AED186C120BB3101572319E7AF435E0
            3AA5CF8B7E32F8D23F0AEA763068115887BA68E4B72D2C49C2E496C16CEE5185
            DAA720E38046E78C7ADFC36F872DF0F6D2F6DFFB72E3504B970FE598BCB89081
            8C85CB7CC7B9CF200E3815DD50007A57CCDE08BE9AC3C6DA3CB091B9EE9216CF
            42AE7637E8C7F1AE4C4BB4A0FF00AE87D570EC14F0F8A8BD9A5F948ABE2739F1
            66B27FE9FA7FFD18D5F51D2C2EF2FEBB97C4DFC1C37A3FCA273FE3ABA165E01F
            10DC1956264D3A7D8CCD8F98C6428FA92401EE6BC2659A5FF8675F0CE8364CAD
            7BAF6A6D02C248CB813BF4FF0081AC43F1AEC3E48D6F8A3F2FED01E088D7845F
            B0ED51D07FA53FF80AF61F1BDC59DAF8135E96FDC25A9B09924CB05DDB90A850
            4F724803DC8A00F39F016B32FC36F859A66A9E2DBBBF96D751B945B789409459
            C4EA4A13CE42955DC402719002839CFACD9EAB61A8E931EA9697714D63247E6A
            CE8D952BDCE7B63073E98A00F1BFD9E1AF3507F16EBB764335FDDC459C71BA41
            E63BF1FF006D05761F1B6059FE12EB44A8668FC97527B113264FE44D002784B5
            DF0DF827E15F870EA3AA5B5942FA7C738577CBBB380EFB50659BE673D01A8F5B
            D5348F89BE16917C2BA9C37D776570970B064C6CC57230CAFB580218E0F0091D
            6A2A45CA2D23AF035A347130A93D9357F4EA65F837C2DAC5F788AD754D7B4B4B
            55D3D42C4D9DAD2155C282BCEEC1CB6E3C927A91C0F59A8A11718EAB53B73AC4
            D3AD5D468CB9A31564FF001398F16F8FFC39E0A8036B17C16E1937C76910DF34
            839C617B0241196C0CF7AF9F6FFE30EB1A87C4D7D7BC3DA5C3E74D6A34BB4B79
            A3691DE3326E048561FBC2DD8640CE39EA763C73BE83C03F157C4574B7BAFF00
            8E64D2034431069F2B650E73B59232899193F36E63C0EB5EB7A2698DA3E8F6DA
            7BDFDE5FB42A41B9BC93CC964C927E66C73D703D80A005D72E1AD340D46E14E1
            A2B595C1F70A4D7877C27D3A0BFF001B2493E0FD92069D1480416C851F96ECFD
            40AE5ACAF5608FA7CA24E9E5D8A9C77B5BF07FE6735E2421BC53ABB020837B31
            047FBE6BEA51D2A70BBC8DB89BF8586F47F944E6BE2078726F16781755D12DE6
            58A7B88D4C4CC382E8EAEA0FA02540CF6CE79E95E2BE07B59B5BF1B6836D696C
            9368DE0CB1DD7231E706BA60CD218C01CB994FCBC91FBADC09E01EC3E484B8D7
            B4DF891FB42F872E74C95FEC76EB1EC7642A58C3E64C783EFC545F17FE2A695E
            257D2F4AD1E592F3488A51717EB8787CF21B88B90080002738232CA7AAD00747
            6F73F153E26E9EF6175A6E9BA0E8B3FCB34D71684B3A6470B1C8589383904051
            C7DE0715A3A1785BC41E03F0BF8BFC3B7539BFD13FB2E5BAB2BF004612431B07
            8CA16241C8DDC64719C82D8A003F671E3E1EEA071CFF006AC9FF00A2A2AE43E2
            F6BDF121A0D42DF51D37FB3FC332CBE528448DFCC40F942EE0B10C700E011401
            C9683F0B8EA1E00BAF19EAFACC7A6E99123342A9079D24DB58A118DCA1497014
            73C93D863347E18786BC43E21F18DB3F87EE24B17B3712CDA80195B75E9C8E8C
            586404FE2E73F2EE2003ECB1C0AF31F19F803C69E21F14ADF695E39B9D334C70
            11ADA16923F21401CA84602425B71258A919032401800E6BE21E87E04F87DE18
            95EEF4EFED9F10DF82B14B7F70F24B33F795CE78033FC38CF033C92383F81DA2
            5CC9F166DCCF1B41269D6F2DCC914A855B057CB0307A1CCAA7F0A00F5BF1078A
            BE2CDB5E4CDA5781AC7EC5192AAD25C8B879304FCC02BA9008C71B73593E1BF8
            C5E264F11D8E93E32F0A4BA78D466586DA68EDA58486271F71F3BC64AF4231E8
            6803D47C5AC17C1DAD12703EC338FCD0D7CF9E0C9A783C69A33DBB9473791A12
            3FBACC1587E2A48AE2C4BFDE44FB1E1E8A960710A5B6BF919FABBF99ACDF3E31
            BAE2438FAB1AFAB074A309BC89E2956861D793FF00DB4E1BC7DA87882FEDE4F0
            C784ED27FED2BA8BF7FA8366386CE22704F98472E46400B96032DC6056C782BC
            2365E09F0C5BE8D667CC29979E72BB4CD29FBCE476E8001CE00032719AED3E40
            F3BD4BE11EA769F17AC3C57A0DD471D8CB7E2E6F10B9578B3932E3FBCAFF0030
            C0EEF8C6DC91DC7863E1AF85BC277535DE9BA6C7F69925691269C091E1078D91
            B119550091EA73C93401D6D78FFC4CF8BDE1CB7F0CEAFA269D7125D6AB711496
            6D1792E8202C0AB172C060804F03272002073400FF00D9D2278FE1D5E33290B2
            6A72321F51E5C433F9834CFDA2EFA383C056569E6A09AE2FD088CB00CC8A8E58
            81D4804A03E9B87AD007816A5E30BFD43C1BA3785C288B4FD34C9210AD93348F
            23B6E3E8007C01F539E401DEF82BE35D97827C35069163E11326CF9E79CEA183
            34871B9C8F2B8E8001CE00032719A00F4CF087C77F0E788EEA1B1BF825D22FA5
            3B504AC1E166270144800C13FED281EF5D8F8875FD4AD6E4693A0E9325F6AD2C
            5E62C928296B6EA5B687964EFCE4EC5CB10A7A75A00C8F0F7C37B3B3D57FE121
            F115D36B9E226C31BAB851E54041C810C7D140E307939191B7245717E0DB3B7F
            0B7C5DF186B5E25D574DD34DC4922D9A5CDFC2AD2C524BBC36DDD9002A27503A
            E3B1C0075A9F1A3C193789E0D0E0BF925699BCB176B1FF00A3893380BB8F3C9F
            E200AF239AF41EBCD0072FF1167FB3F807567F58D53FEFA755FEB5E35F0E7CA9
            3C71A5C334719066320723E652B1B90076C138FC87BD7157FE347FAEA7D8E4B1
            7FD938892DFDEFC228C092CE7B8D69AC614DF7125C1851738DCE5B0073EFEB5E
            F9E07D67C45A84BA858F88ECD6DEE6C962DAC232A65DDBC1627254F29D578EB5
            1867253D36675711C30F530C9CA5EFC55D2EE9B499B1AD78974CF0FB2FF68C92
            A29B796E4B4703C9B638CA0762141381E62F6EE4F406A4D47C43A7E9772B6D39
            BA96729E618AD2CE6B9645E4066112B150486009C6769C67071E81F08467C53A
            47F66417EB7324915C332C51C76F23CCECA486511053212A41DC36E570738C1A
            65B78BB45BA8A7912E64436F710DACD14F6D2C52C724ACAB1868DD4300C5D707
            18EBCF0700124FE26D2ADD6E19A791CC171F666586092567976EE288AAA4C842
            E49080EDDAD9C6D38E1FC63F0D7C37F126F9EEE192EB4FD5A3822692E56DCA87
            0DCAACA8C012E157A6559432EEE368A00C6BE1F123C2127FC225E08F0DDBB689
            0C452CAFA621E524AE5E46632040DBD9880CA07A0C57917C4AF06789FC2F7965
            7DE28D521D42EB51DFB6449DE561B36E43165181F38C0191F4A00F66F85FF0A3
            C323C1DA3EB1AB6910DE6A7730FDA19AE18BA6D7E507964ECFBA57A83CE6BD66
            D6D2DAC6D92DAD2DE2B7B78C612289022A8F400702803E51D7747B6F887F1C6F
            74DF0F88A1B3B8B90A668631B1551009651B78392AC41CFCC48E79AFAD050078
            FF00FC33D68373AA5DDEEA5ACEAB73E74E644457552149CED7660C5CF6CE4561
            EBF3F81FC05E219BC37A1F8116EFC453B451DA3EA1896DDDA403630691C91866
            C1C05C907E61D68036BC11F02B4ED3645D53C56D1EA7A9B3B486DD7FE3D90939
            19181BCF1DF0BF311B4E01AF49B9F15E8167AFC1A15C6AB6D16A93AE63B667C3
            1E981E809C8C03C9ED9A00E77E2DDF1B5F03490840C2EEE23849CE36E32F9F7F
            B98FC6BC83C121CF8DB4608C41FB521E3D33CFE99AE0AEEF597C8FBAC8E0A394
            D46FAF33FC2DFA1D8F81F4A8EEBE2D6AD33A9D96335C4883191BB79419FC189F
            A8AF69C56F865683F53C1CFEA39E262BB463FE7FA9C5F8CB401AE6B761F68B3B
            EB9B24D36FA3916CEE0C459DCC1B5090CA0EE0AFC39DA71CD43A2BF883C3B777
            8BAAE9171AACF7C2DE66BED3DA22AD2ADBC713A32B142BF3C4CC081B7127F0F2
            2BA0F0CAFA6697AA786B543ADCBA3DC5E7DBFED32DC5BDA346EF6724B2AB0003
            32EE0515036D27E68F20107226D5F45D535C86FF00505B6B9D3EE2F27D3218A2
            0D199A18A0BAF31A63CB206FDE4842FCDC22E79254003574FB8B1D062D075AD3
            6EE436CC4D96A9A306DEF29DD87C64BC52905B733E63258EE7F9CAD759A0477B
            1E8360DA9AA8D51EDA237A4051BA7D8A1C9DBC67231C71C71C5006957CFF00FB
            4D7FCCADFF006F7FFB46803D6F5692FBC1FE088D341D224D5A5D3EDE3862B512
            6D764550B91804B100670064F6AF07F14FC7AD73C43A3B68FA6E9434B9E7CC53
            CB1CC649181E36A0DA3693C8EE7D31401DEFC10F86D77E15B49F5ED66330EA77
            B108E2B63C3430E437CFE8CC429C755006792408BC496FF1AD7C5D7B0E817E92
            68CF3E6DA778ED156346C1C10C0B90992B9C1276E71CD006BE93E19F8AF20B81
            AC78F2CE0253F72D676314B86DC3960D12E46370C023920E78C1F19F89BA06A7
            A2FC48D32D759F11DCEAB71731432FDB3CBF29E2532B2E14648182A48C7AF4A0
            0F723F0A2331ECFF0084E3C6BB4E491FDADC1C9C9E367AD6249FB3B784E67792
            5D535E924762CCED7111249EA49F2F934017FE2B598D3FE1F69564279A716F75
            0C4269DF74926D89C6E63DD8E324FAD79E7C3B4F33C7DA40F4958FE48C7FA579
            F5BF8EBE47DDE52ED92D47E53FC8EDFC024AFC58F13A6E206EB93B73C1C4E39F
            D7F5AF5AAE9C3FC1F367CE679FEF2BFC31FC8CCBDD58DBEAF67A6416C66B9B88
            DE624C8A8A91A322B1E7927F783000FA95E2A1D3B58BCD466668F4E5168B7735
            B34A6E06E1E5B3297DB8E859318CE79071D6B73C7123F11DBC9E2A9342589F7A
            425FCFC8DA5D76178F1D7216589B3D086E3956C578BC57149A65C6ABF6398D82
            C9E4DBB46CAF25C4BE69882041F7497DA06E231BBE6D983400FB7F10DD26AB69
            63AAE932D8FDBF70B4904AB282CAACC63936F0926C566C02CA429C367835B4CF
            1BD8EADE12B6D76D6195BCE92085EDB80F14B2BA2856CE3FE7A2B67BA9046411
            401D4578CFC6BB58AFBC6BF0E6D2740F0CFA8BC522B7465692DC107F03401ECD
            545F45D2A4D553547D36CDB518C6D4BB3029954608C07C640C123AF7A00BD450
            065788B579B42D1E7D4A2D3A6BF4B75324B140CA1C20196601880D803A6727B5
            7CF51CD73F18FE355A6A7A7594A347B036ED29B950BE5C2877156DA48DCCDBC0
            0093CFA024007D35450079CFC67FF9142D3FEBFD3FF45C95E75F0C467E21E95C
            7797FF00453D7055FE3AF91F7395FF00C892AFA4FF0023ABF0C1934AF8DDAB5A
            CE007BB7B80B8F462265FD00AF60AE8A1F0B5E6CF033CB3AD4E6B69422CE5BC5
            DA3DFEBFE4D841A6D898D59268F539AE1965B3903F2F1A2A64B80011F300790D
            C70D434FF0FEADA3DE6A57767E1EF0EB5F4D2DE4B16A46E184EFE63BC91AB810
            E71928A7F79C01C7402B73C51F2F817EC1696373A45CDC4BAC59DCA5C2CB797D
            379323B37FA4318F2C8AD223CDCAA705F8C55397C23AB5FEA52EB915A69FA2EA
            31B473C304331963B99D0B82D3E117AABB28600B00D9392A14006E2D8EBDA96A
            56D7BAA5BE9D6CBA78792D2DEDAE5E6124EC8C81DDCC69B405671B42B677E7F8
            45629F87F76961E1D96DAF63B7D4ACA3B087525424C17B1DBBC6F8231F794A12
            8F80704A9E1B800EFEBCDFE2368179AC78EBC017505ACF2DBD8DFC924EF1C658
            44331BA9623A0CC78C9A00F48A2800A2800EB54B4DD234CD1A07834BD3AD2C61
            76DED1DAC0B12B363192140E7007E5401768A00F3AF8CFFF002285A7FD7FA7FE
            8B92BCFBE16C124BF102C1D119961595DC819DA3CB65C9F4E580FC6B82AFF1D7
            C8FB8CB5A591D56FB4FF0023D6757F08CD378D34DF136992C31DCC2C12E63981
            DB24782A5811CEFDA48E78E9D31CB7C5BE2FD4FC2F2074F0EC97D63B3735D473
            ED0873C86010E3B727839AE977A4A524AE7CFD2F6798D4A346A4F91A8F2DF74E
            CDDBAAEF6392FF0085DFFF0052EFFE4EFF00F6BA3FE177FF00D4BBFF0093BFFD
            AEB0FAE2FE53DAFF00547FE9F7FE4BFF00DB07FC2EFF00FA977FF277FF00B5D1
            FF000BBFFEA5DFFC9DFF00ED747D717F287FAA3FF4FBFF0025FF00ED83FE177F
            FD4BBFF93BFF00DAE8FF0085DFFF0052EFFE4EFF00F6BA3EB8BF943FD51FFA7D
            FF0092FF00F6C1FF000BBFFEA5DFFC9DFF00ED747FC2EFFF00A977FF00277FFB
            5D1F5C5FCA1FEA8FFD3EFF00C97FFB60FF0085DFFF0052EFFE4EFF00F6BA3FE1
            77FF00D4BBFF0093BFFDAE8FAE2FE50FF547FE9F7FE4BFFDB0A7E3730009F0E1
            008C83F6DEBFF90E93FE177FFD4BBFF93BFF00DAE8FAE7F743FD52BFFCBEFF00
            C97FFB60FF0085DFFF0052EFFE4EFF00F6BA3FE177FF00D4BBFF0093BFFDAE8F
            AE2FE50FF547FE9F7FE4BFFDB07FC2EFFF00A977FF00277FFB5D1FF0BBFF00EA
            5DFF00C9DFFED747D717F287FAA3FF004FBFF25FFED88E5D76EFE2C35B68D168
            EF676B05CA5C5CDD0B8DE1102B0C7DC1F31C9C7D3D32477FE18F06693E1359BF
            B3C4CF2CD80F2CEC19881D00C0000E7B0FE55A524AA4BDAB47066752580A3FD9
            B09732DE4ED67ABBA5BBF53A1A08CD749F38725AE7C37F0E6B9279CF6AD69393
            9696D088CB75EA3054F5EB8CFBD73D77F0574A751F63D56F216EE6655907E402
            D734F0B093BAD0FA1C1F1262B0F08D392524BBDEFF007FFC028FFC2901FF0043
            0FFE49FF00F6747FC290FF00A987FF0024BFFB6567F53FEF1E8FFADCFF00E7CF
            FE4DFF00DA87FC290FFA987FF24BFF00B654727C11987FABD791B8FE2B523FF6
            734BEA6FF986B8B95F5A3FF937FC02B49F0575307F77AB5A30FF0069187F8D40
            DF05F5D1F7750D38FD59C7FECB53F549773A23C5787FB5097E1FE6867FC298F1
            17FCFEE97FF7F64FFE22B574AF82D2182E3FB635255988C41F633B941F56DCA3
            3F418FAD38E1257F79935F8AE8727EE60F9BCED6FC19A9A6FC3DD76C6DE4D127
            D56C6F3C3F2E7724D09F36327AB460E42B75C1DC403CE0F359DACFC17188CE87
            A81CF4916F9BF50517F4C7E356F0CDC6CDEA8E3A5C474A8D6E6A706A12D64BAF
            37F775B7ADF7F23317E0BEB87EF6A3A78FA173FF00B2D4F1FC14D44FFACD5ED5
            7FDD8D9BFC2A3EA72EE76CB8B30FF669BFC3FE09657E08391F3F88141F6B3CFF
            00ECF5A369F05B49487179A9DECD2E7EF421235C7D086FE7571C1AEACE4ADC59
            51C6D4A924FCDDFF00056FCCEF746D12C340D392C74E80450A9C9EE598F5663D
            CFFF00587402B42BAE2945591F295AACEB549549BBB6EECFFFD900FFED245850
            686F746F73686F7020332E30003842494D04040000000000101C020000020002
            1C02050004B4F2D3A13842494D042500000000001059995C3196786529E618D9
            2773A732BD3842494D03ED000000000010012C000000010002012C0000000100
            023842494D042600000000000E000000000000000000003F8000003842494D04
            0D0000000000040000001E3842494D04190000000000040000001E3842494D03
            F3000000000009000000000000000001003842494D040A000000000001000038
            42494D271000000000000A000100000000000000023842494D03F50000000000
            48002F66660001006C66660006000000000001002F6666000100A1999A000600
            0000000001003200000001005A00000006000000000001003500000001002D00
            0000060000000000013842494D03F80000000000700000FFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFF03E800000000FFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFF03E800000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFF03E800000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FF03E800003842494D040000000000000200023842494D040200000000000800
            000000000000003842494D040800000000001000000001000002400000024000
            0000003842494D041E000000000004000000003842494D041A00000000033900
            00000600000000000000000000020C0000020C000000024E667B7E0000000100
            0000000000000000000000000000000000000100000000000000000000020C00
            00020C0000000000000000000000000000000001000000000000000000000000
            0000000000000010000000010000000000006E756C6C0000000200000006626F
            756E64734F626A6300000001000000000000526374310000000400000000546F
            70206C6F6E6700000000000000004C6566746C6F6E6700000000000000004274
            6F6D6C6F6E670000020C00000000526768746C6F6E670000020C00000006736C
            69636573566C4C73000000014F626A6300000001000000000005736C69636500
            00001200000007736C69636549446C6F6E67000000000000000767726F757049
            446C6F6E6700000000000000066F726967696E656E756D0000000C45536C6963
            654F726967696E0000000D6175746F47656E6572617465640000000054797065
            656E756D0000000A45536C6963655479706500000000496D672000000006626F
            756E64734F626A6300000001000000000000526374310000000400000000546F
            70206C6F6E6700000000000000004C6566746C6F6E6700000000000000004274
            6F6D6C6F6E670000020C00000000526768746C6F6E670000020C000000037572
            6C54455854000000010000000000006E756C6C54455854000000010000000000
            004D7367655445585400000001000000000006616C7454616754455854000000
            0100000000000E63656C6C54657874497348544D4C626F6F6C01000000086365
            6C6C546578745445585400000001000000000009686F727A416C69676E656E75
            6D0000000F45536C696365486F727A416C69676E0000000764656661756C7400
            00000976657274416C69676E656E756D0000000F45536C69636556657274416C
            69676E0000000764656661756C740000000B6267436F6C6F7254797065656E75
            6D0000001145536C6963654247436F6C6F7254797065000000004E6F6E650000
            0009746F704F75747365746C6F6E67000000000000000A6C6566744F75747365
            746C6F6E67000000000000000C626F74746F6D4F75747365746C6F6E67000000
            000000000B72696768744F75747365746C6F6E6700000000003842494D042800
            000000000C000000013FF00000000000003842494D0411000000000001010038
            42494D0414000000000004000000063842494D040C000000001E660000000100
            0000A0000000A0000001E000012C0000001E4A00180001FFD8FFE000104A4649
            4600010201004800480000FFED000C41646F62655F434D0002FFEE000E41646F
            626500648000000001FFDB0084000C08080809080C09090C110B0A0B11150F0C
            0C0F1518131315131318110C0C0C0C0C0C110C0C0C0C0C0C0C0C0C0C0C0C0C0C
            0C0C0C0C0C0C0C0C0C0C0C0C0C0C010D0B0B0D0E0D100E0E10140E0E0E14140E
            0E0E0E14110C0C0C0C0C11110C0C0C0C0C0C110C0C0C0C0C0C0C0C0C0C0C0C0C
            0C0C0C0C0C0C0C0C0C0C0C0C0C0C0CFFC000110800A000A00301220002110103
            1101FFDD0004000AFFC4013F0000010501010101010100000000000000030001
            020405060708090A0B0100010501010101010100000000000000010002030405
            060708090A0B1000010401030204020507060805030C33010002110304211231
            054151611322718132061491A1B14223241552C16233347282D14307259253F0
            E1F163733516A2B283264493546445C2A3743617D255E265F2B384C3D375E3F3
            462794A485B495C4D4E4F4A5B5C5D5E5F55666768696A6B6C6D6E6F637475767
            778797A7B7C7D7E7F71100020201020404030405060707060535010002110321
            3112044151617122130532819114A1B14223C152D1F0332462E1728292435315
            637334F1250616A2B283072635C2D2449354A317644555367465E2F2B384C3D3
            75E3F34694A485B495C4D4E4F4A5B5C5D5E5F55666768696A6B6C6D6E6F62737
            475767778797A7B7C7FFDA000C03010002110311003F00F55492492529249249
            4A4924925292492494A4924925292492494A4924925292492494A49249252924
            92494FFFD0F554924C92974953B7ACF48A5C5B76763D6E1CB5F6B1A47F9CE43F
            F9C1D07FF2CB13FEDFAFFF00268710EE19061CA7518E67FC193A092CE3F58BA0
            0E7A962FCAEACFE47280FACFF57498FDA38F3FF18D03EF9438E3FBC3ED4FDDF3
            FF009A9FF892751259FF00F383A07FE59627FDBF5FFE4D119D63A459FCDE763B
            FF00AB6B0FE4723C43B841C3946F8E63FC19371243664E3D9FCDDAC7FF0055C0
            FE4444561046E29492492485249249294924924A5249249294924924A7FFD1EA
            3EB4FD7A6F48CA774FC1A5B9196C00DAFB2456C2407319B5BB5D73B61F7FBD9B
            3FCFF4FCF3AA754CEEAD96ECCCD7EFB1FA00043401A06B1A16BFF8C07B1FF59F
            25AC686BAB654D791F9CED8D7EE77F61EC62F45FAB18F4E3FD5FE9EDA582B6BF
            1EBB5C04EAFB1ADB6C76BFBCF72AA44B2CE5132A112F4D0C9CBFC3793E5F988E
            0E3CB9E238A46552F5478E5EAF5FA7FABC2F8C4797E0894E3DF7BB65153ED77E
            EB1A5C7FE885EEE923F75FEB7E0C67FE329AD396FF00C73FF5DBE22EE89D698D
            DCFE9F94D6F89A6C03FEA1333A2F59B04D78192F1FC9A6C3F918BD76EFAC9D06
            8EA6CE936E7D0CEA1610D6E3978DDB9D1B2B77E6B2DB3737D3A9FF00A4B3F314
            FAEED1D173DCFC8B30DADC7B5CECAABE9D61AC73CDD5C6DF757B7725F751FBDF
            82CFF94996BF988FF8D27C8BFE6FF5EFFCADCBFF00B62CFF00C825FF0037FAEF
            FE5665FF00DB167FE416D7F8ABFAE1F59FAA751B3A6E7FA9D430995971CB7005
            D43B5757EB5FEDF51B91B5EC6B2CF52EFF0047FA2AEE5EA497DD47EF7E0AFF00
            9499BFCCC3FC693E27FF0037FAEFFE56E5FF00DB167FE4137FCDFEBBFF0095B9
            7FF6C59FF905EDA925F758FEF7E0AFF9499BFCCC3FC693E28DFABDD7C9F6F4DC
            B07FE26C1FF7D562BFAB7F5A4FD0C2C96FC65BFF00545ABD8D24472B1FDE2B65
            FF0018F31FF238FEBC45F25AFEACFD75FCCA321BDBF9E6B7F2DA11DBF57BFC60
            54658325A7C5B94D9FFA390BD4D247EED1FDE9311F8F673FE4707D6123FF0076
            F9957D33FC64D665AFCB3FD6C96BBFEAEE72BA5BFE3371B01F966E71D8EDBF67
            DB55B791FE918C6D56EE67FD73D5FF00835E809223001B4E7F6B1CBE3129D717
            2BCB1A3AFEAAF4EDEA3278EE83D53EBA6431F89D470EC69B9AE6D3D40D6CADD4
            B8876DB2DC77FA75DD5D6EDAEFA3FF006F29748FAC3F58C675DD0FAA50DFDA45
            8F3879258452E735A5EDF5FD2DBFA07C7F3B57F5175E9270C6457AE5A77ECC13
            E77148E4BE571444C7A783D3EDE48FCB38FF0057F7F17C8F1DD5BEBCF53E90EA
            A9CDE90E65C7E9BCD9FA27907DDF66B1B5BF7EE66D77EFD3FE118BA1E89D6B13
            ADE08CDC5DCD6EE2CB2B7C6E6387E6BB69737E8FBDAAD65E262E6E3BF1B2EA6D
            D45821CC78907FF326FE6B979D7F8B0B9E3AC655209D966317B9B3A1731F5B58
            63F93EABD34CA50C9104F1467B7F5699E38797E6792CD931E2F67372DC32998C
            A53C796393FAB397A3E57FFFD2A5F5C5C5DF59BA812662C035F2631ABD57A256
            6AE8D8153BE9578D4B4FC431AD5E4DF5B0CFD63EA279FD3387DDA2F5EC020E06
            311C1A99FF0052156C1FCE643E3FB5DFF8D69C97231FEA8FC31C19667DA7EC97
            FD8F68CAF4DFE8178967A9B4FA5EA3416FB37FD2F72F2DFABB47D77FAFF8B666
            6675C76074DAED7526AC66EC738C31F657B28F43753E9DBF4B22EBBFE297AC2F
            19FABEEA9BFE283ADD97377FA59B351D416D8460B69B58E6ED735D5D8F565C06
            A7F8CDFA9DD27EAC7ECB774BF540C86DACB8D8EDC4BAAF48B6EE1BB6CB3D6F7E
            CFD17E8FF9B5DBFF008D3EB76E2F42ABA163136F54EB0E6D2DAEB9DE6B05BEA9
            6B59FE9ECD98CCAFFC2FAB6FFA35CBFF008CAFB45FD37EA7E3E53DD665BF1BF4
            EE799739EF6E135EE7BBE939CEB03D7A3DBF57F1E9EB597F59B63B3BA90A0578
            54D8406D4D635DBA9C5747E89D95639DBEE77D0F56CFF0765A929E53029EA1FE
            2EFA1D38983D1B27ACF52CE02ECBC8A44D2CB08D8DC7FD00BEFF00D5FF009555
            6CBF7FA95DDFE06A035DFE38BEB0D66C6FA3D0F1DCCF6B0814B9DF278CBCFA6C
            FEBFA0BADFA9FF005CFA77D6BC4B2DC563E8C8C6D832B1DFAEC2F0ED9B2D1ECB
            6B77A76ECFF09ECFD2555AE81253E21F547EB0FD77C6FAE78DD1F232F2326C76
            4FD9F371326C37343184FDADCC363DED63A8A9965CCB28B3FC1FF85ABF46FF00
            6BBB231E82C17DACA8DAED9587B837738EBB19BBE93D79BFD4967DBBFC66FD63
            EA25A0B318DB4B4E861C6D6D2C7B4FF2AAC6B16BFF008DCE9ECCBFA9D6E41FA7
            817557B20493B9DF657B7FABB723D4FF00ADA4A7B551B2CAEAADD6DAE15D6C05
            CF7B880D6B46AE739CEFA2D6AE6BFC5ADD9777D4AE9AFCB717BF6D8D639C4977
            A6DB6CAE90777EED6D6B6BFF0082D8ACFD702DFB0E2576879C6B7329664358D6
            B816FBDD57AA2EFD17A3F6A6E3FA9BFF00E2D091A04F664C18FDCCB185D711DD
            B1D33EB4F42EAB9071B07285970048639AE61701C967AAD66F5ACBCDF0ABB5DD
            43A05D8CC363EBB2AADD763C7A6C616FEB1464FA7BBF5A7B5B6E53FF00E0AEFF
            000D5FE917A42662999037D0F46CFC4395C78270F6C9E19826A644A719465C1F
            A3C0A5C07F8CEFADBD4FA09C27746EA38F5DCD7B9B978045765CE0E02CA6D7D6
            F6BDF5D0DD8F6FF81FE77FC27F83EBFACF483D5A86E39CECBC1AC197FD8DEDA9
            CF1FB8FB8D765AD67FC4BEA5E6987F55FEADFD58FF0018B562E6E4D57600C339
            75BB3DD5B7D3B4B9D535B6BDFE9D1759EC7DD57E8FF3FF009BFD0FACA4693D77
            D40FAF3FF3AF16E6E451F67CEC4DBEB7A61C6A735F3B1F5B9DBBD377B5DFA17B
            FF00F51F5AB8CEA5FE353EA6F4AB4635363F336921DF6260756DFF00AE58FA2A
            B3FEB0EB5751D2FA963755E9F4751C5DE28C96EFAFD46963A276FB98FF00776F
            EDFF0083F624A6DAF27FF17F96CC6FAC94B5EE0D190C7D209D04902C637FB4FA
            F6AF55BAC1554FB0F0C6971F9095E39F55316ECAFAC3D3EBA84965CCB9D3C06D
            47D6B3FE8B3DBFCB55F39A9E3AEFFF007AEDFC1E11972BCF891A89C71D7B5472
            BFFFD3CBFACC67EB0F523FF762C1F73A17AFF4B33D3310F8D159FF00A0D5E3DF
            588CF5EEA5FF0086AEFF00AB72F5FE8E49E91824F271EA3FF41AAB72FF003CFF
            009757A1F8E0FE89C9F80FFB8835FEB4665B83F573A9E5D33EAD38B6BAB204C3
            B63B63FF00AAC77BDCBC930EB16FD4BE85F56EAB765DF58FA93AEB882DF6D35B
            C617E9187DDEFB6B65B57EFF00D997B2F54C9E9F8BD372723A9960C1AEA71C91
            60DCD35C43D8EACEEF57D4FA1E97F85FE6D79F7D40FABFFB6B3BFE75665231F0
            3199F65E8389AB8D55D52C6E47BE5AF7D7FA4FD23F7FAB9B664E4ECAFF0042AC
            BCF357FC64C5FF005FBEAE74F021BFABC0EDFA5C9357FE8A5DAFD77FAC83EAEF
            42B726A1BF3B20FD9F06B1A9373C1DAFDBB5FF00CCB7F4BFF09FCCFF00855E65
            976756ABFC68F4EA3EB3DCECCB317269AB1AF15D756FA8D86CC0BB6D4DAEAD9E
            BDDBEEFDCFD2D5FE0D5BEA3F55BFC60FD72EAF6D5D4DC29C3E9D7DB551764359
            5B5AD7398EFD0D78ECF53277D3E8B996FF0034FF00F4E929E83231B1BEAA7D4B
            AFA474FEB78DD2BAD525B95905EFADCEB6ED1D7D26B2D7DBE96E0CAABFD07F35
            4555DDECF556B7D41FAEA3EB2746B6DCA01BD43034CB630101CD21CEAAF67E6F
            E9763FD9BBF9CAFF00D1FA6AB7D5FF00F14FF56BA4965D98D3D5729BF9D9000A
            41D47B3106E67D177FDA87E4ADBCEE8DD1F072F33EB2967A590DC17D3905B0D6
            3AA60F5BD4B58D037DAC654DAFD4FF0044929E33FC495563B1BAC6758E2E7645
            D53093DDCC16DAF77F6BED2B7FFC6175DE854FD5EEA7D33273696E6DB416B317
            76EB77902CA43A9AF7D95EEF67F38B2FFC49EDFF009B399FBDF6E7CFC3D2C785
            43FC667D45E8387D2F3FEB2506FAF39F635E6BDE1D53ACBAD6FACF736C63EDFC
            FB1DECB92538785FE3673BA5FD5EC3E91D370AB6DF8D50ADF95712E1CBBF9BA1
            9E9FBBE87BECB7FEB4AD744FF1AC736BB3A57D70A5B9383930C3954B36BD927E
            9DD557F4D95FB6CDD437D6AFD3FE6EF51E93D63A47D56FF17F4750C7A2BFF9C5
            D51D7B31AF2C0FB1A1963A97646FB3F9AAA8635BE9B1BFCE64FF0082FE7D5AFF
            0015DFE2FDF73EAFAC7D62A8A1B0FE9F8CF1ABCF2DCCB5A7FC0B7FED37FA6FE7
            FF0099F4BD75BA63231225124106C11B821EFBA1FD4FE8DD1B20E5E2FA975CE1
            0CB6E7076D69FA5E96C6D6DF7FEFAABD7FFC62FD5AE819CFE9F9965B665D401B
            2AA6B2EDBB80B181CE79AEBF731CD77D25D3AA799D2BA465DACCACEC3C7C8B68
            1FA3BAFA98F73003BFD9658D73ABDAEF7A118888A88A0BF366C99A7C7966672D
            B8A4F13D67EB2FD7CEB581F6AFAAFD31DD3FA6399EA7DBB31F457739901E6CAE
            AC8B7D2A28DBBBF4FF00A5F52BFD3556D4BCC3EAF74DC8FAD3F59B17072B25EE
            B336C26FC9B1C5F616D6C75D69F51FEA39D6FA356DAF7FE7AF4DFAC7D4FAD7D7
            6B6CFABFF5546DE90D71AFA8F59748A5E5BEE76363583F9DABE8FA9E87BF23FE
            0F07F4D938BFE2F3A1E274FF00F1919D834DAEC8674BC7B036E734349B41A31A
            FF006B4BB6377DB91B3DDF411637D03A7FD5CFA9FF0057BD26D18D8B8D733DD5
            DD76D377F29E2FBF75DFE6B96CD1938F900BB1ED65C1A6096383803FD95C8F50
            FF0014FF0054F3EFBB21E326ABB21EEB6C7D76C9DCF25EEFE799737E93952E9D
            FE2A9DD13AD63F53E89D62EC7654F6FAB558C6BDCFAA41BA975B59AAB736CDBF
            9F8FFF0009F98929ECFADD86BE8B9F60E598D7387CAB795E69F507A9D3D3FAFB
            1970F6E6B3ECCD7F76BDEE63AAE3F35F633D35E89F59ECF4BEAEF51778E3D8DF
            F3DA6BFF00BF2F2FFAAD88FBBAE74F7B4B486E5572DDC37FB66FDDE94FA9E9ED
            ABF9C55B3123242BF95BBFF08C7097C3F9C13D232B17B7CB0E27FFD4C8FAC1FF
            002F753FFC377FFE7C7AF5CE8393897F49C4FB2DCCBD95D35B0B98660B5A1BEE
            1F49AED3F3D797E574EB3A97D71C9C0AE41C8CEB5A5C352D6FA8F7DB647FC1D5
            BEC5E8DD0FEABE1F43CAC8BB09EF3564B18D353FDC5AE617FB9B6E9ED7EFFA1B
            7FB6AAE012E291034BA25E8FE353C2796E5E1299196301921002E3307861EA3F
            A3FD45BAE7D58ABAF6554DEA591659D2AA6827A6326B65974BBF4F91915B9B7D
            8C635CCF4E86FA7FA5AFD4FE42D8A69AA8A994D2C6D5554D0CAEB600D6B5AD1B
            58C631BED6B1AD5CFF00D72CFEAD88CC0AFA559736EC9B6DACD78CCA5F6BCB71
            B2722ADADCD6BEADACBA9ADD6FFC128F4EEA79FF00580B29C4CE18B5E2D18F66
            5E5E2D6D26EBEE639EFA719BD42BBBECD8F46DFD27AF8AFC9F51FE87EAFF0066
            BBD5B4F38EB750E87D23A96462E56762B2EC8C1B05B8D6990E639A7737DCDDBB
            99BBDFE93FF45BD5F5CA51D4BAF6466BBEAF5596C19345F70BBAA1ADA5E71A9A
            F0723F458E07D97F683ACEAF8F8FB9CCFB333D1BEEFB3FF3742AFD63ABF5CE8C
            FEA383F6E764B6AA713328CEB2AAFD4A596E4B30B2B1AE66354CA323D4AD96DD
            89B313D6FE7AAFD37A75A4A7B35E4FFE35B2BEBC6307E3DB6077D5EBB8BB1EBD
            B20BBDB467BFF48F65ADFA1ECF4B1B2BFE33D4A69EC1BD5FAD67F46BBADF4E70
            B3172AC68C5AB1C32DBAAC3ADEFAF23329696B9B91D4EF6FE97EC56FF45FD1E3
            FD9EECBA6FA32B4FA25B766359D42AEA1F6EE9B6E3D6DC5743039EE97BB232B2
            3D3A68F4EEFE6E8FB3B7F98F46CFD1FAB67A75253C8FF8B0C8C0FABFF557FCB1
            97460DB9B63F3AAA6FB1B5D9F672DAF1EABBD1B4B6C7576BB1DEFA9ED6FE918B
            9EFF0018BFE323A7F5DC07746E935BDF8E6C6BEDCBB06D0E0C24B5B4527F49B5
            CED8EF52DF4DFF00F02BB9EB9FE2DBEADF5CEB07ABE6FAE2FB367AD5D7606D76
            6C6B6B6FA80B1D637F46C633F416D4B8FF00F1B7D0BA2746E93D32AE99834E29
            75AF69B2B600F735AD1EDB6EFE76DFA5FE15CF494F19D13EA57D67EBD536FE9D
            84F7E3130322C2DAEBD0ED76C7DAE6FABB1FBB7FA3EA2ED317FC4C75AB31FF00
            5EEB2CA6D688657535F73207D01EA58FC5DBFF006D2EF3EA2E0B707EA7F49A1B
            3EEC665C679DD7FEB6F1FE7DCAF75CEBBD37A0F4EB3A8F52B3D3A6BD1AD105F6
            3C8259450CD3D4B5FB7FF4659FA2DEF494F8E3FAE7D6FF00F17DD7474EBF3C67
            D35358E7E29B1D6D2EADD25AC6FAC3D4C4B7F3BF45FF008354BD6BA97426F5DB
            29767DF70E97B1AE7F4A03D31659EF3BB3ADACFAD6D6CDF5FEA9BD94FAD4EFB7
            D65E5BF5371ADFAEDF5FEFEB79F57EAD43BED76B209602DDB574FC4758D0C66E
            66D63BDFFD22BC5B97A864FD75FAA98975B8F91D531EBBA87BABB6B2EF735ED3
            B5EC7347EEB824A798FF00C742AA726CE91D17EAEE5DEFC2269FB356D0C2CF4C
            9ADCCF4315993E9B59B503A2D5F59A9EA1D4BAE74EFABF474677500FB72B27AB
            6539CC6381F56C2CAABAA9C9A697BF7DD77A8CFF00AF53557E9AE91FFE323EA4
            B0171EA9590DE76B2D77FD454E5E67F5E7EB7E2754FAC0D1D3FA864E6740BC50
            ECDC46BADAD8E2C7116D35536FA5F4EB6B1FF459FA7494DDE8DF5BBFC61F5CFA
            D0DBBA7119B8F4D9E959552D75781E993EE73ECB9BEA55EAB6A75B45B93FAE7E
            6575FF00DA75EC8B89C2FAE3D2BA3E0D78B85F567ACE2625421AC6E16D6E9F9E
            E73AEF7BDFF9F63FF48FFF0008B2723FC65FD6BB3A80C8E9FF0057321FD1EA96
            58D7D369B5E67E99BEA63A9C67EDD9FA1D97FF0084FD23FD9E9253D77D797967
            D56CE20C122B6FF9D6D6D5E75F53EFF43EB374FB3C6C35FF00DB8D753FFA3175
            DFE3032FED7F55707298CB286E4DF55869B5BB2C68755759E9DF5FE6D8CFCF67
            EFAE3FEA9B37FD64E9C3C2E07FCD05DFC154CC7F5D1F0E1FCDE9FE13003E15CC
            13A89FBA4F97B7C1FF0072FF00FFD5D7FABD5D43FC62753F51B2E1EBBAA31C39
            CFAE5DFF006D3EC6AEF9705D32D147F8CBCCACFF00DA816307F98CC8FF00D14B
            BD5161DA5FDE93A3F16B397013FA5CBE123FC573FAAF46AFA9598B71C8BF16DC
            27BECA5F416033656FC67EEF5ABB9BFCD5D67F2D8AA3FEAA60B1F559D372327A
            5594D2DC6DD88F10FAABDEEA99915E5B32A9B9F5BADB5FF687D7F69FD27F3C85
            F5BD97B311B9EF6D991D3705B65B9F8945EFC6B5CC1B1FF6AA6FA5F4BAD76154
            CC87FD8ACBE9AB23D4FF004F463AA9858B9399F59BA85B65365B8D8F9CD0DC81
            9B7D5E96CC5C4BEBA474EAFF00417D4FBECF7FA8FF00F0B67AB5A95CE749FF00
            55BA77D971E8C7B2FC4BB11CF7D39B55A4E407DAE1765BECBAFF0059B93F6BB0
            7EB0CC9AEEAECFFB6D487D59C23896E3DB75F7DD916D37E46658E06FB1D8F633
            271D8EB1AC6D75D15BABD8DA28AA9A99BEDF4FF4D7596AC0B3EB064FEDAA7AEB
            9B92CE922E1821CE66CC538776D657D57D5B1DB5CFB7A9B68D990C76CFD93E9F
            E894FA9E5E5745CCCA76558FA733348FB375475EFB31D9896E6E3625BBB02E7B
            30F0B27A563E7E37A767A16517FF003F6DCFF572E8494EEDDF5769FB5BF33A76
            55FD2AFB89391F6535FA76B9C5AE7DD762E555938BF69F67F4AF47ED1FF08AF6
            060E3F4FC4AF13181155731B897389713659658F77BACB6DB1CFB6DB1DFCE58B
            032FA7D7D1FAB748FD9775E7273724D7934DF9375E2DC76D56D9937D95E55D6F
            BB19DE8B9990CFF0BE8E3FF87584DEADD4B0BEA8D1879B917B8F56C3AEEE99D4
            CD8EDFEADAD6DF7F4CBB2B77A8CCA66EB1D8163BFA563FEAFF00CFE3FE9929F4
            45E65FE3B98F7E1F4863752EBAD01BDC92DAF6AF4D5C37F8CAC66E466FD586BC
            4B1FD52AA9DF0B1D5FFE45253D3F56E8181D57A33FA2E46FAF11EC6D63D276C7
            00C8F4E3F35DB76FD07B7D35E5F6FF00895EB9F6C652CEA343F001FE79C1E2C6
            B4FD370C4F757BBF91F6AFEDB17B124929CCFABDF57BA6FD5DE9CCE9FD398456
            0EEB2C76AFB1E7E95B6BB4F72CFEABFE2FBEAB757EAB6755EA18AEBB26E0D168
            F56C6B5C58D1531DB6B7B3FC1B18DF6AE8D2494E6E0FD5CFABFD388760F4EC6C
            7786EDF5195303CB643B6BADDBEA3BDCDFCE72F2DFF1AB5BEEFAFBD368C31FAC
            3A8C6ADA1BA1F51D7DDE97FD556BD5BACF4B1D5705F8C322FC4B609A7231AD7D
            4F63F6B98DB3F40FABD56B777F3567E8D70BF53BFC5BF54A3ADBBAF7D6ABC65E
            5D0E0719AEB1D739CF67B2BC9BEEB3FD1318CFB333FF003D7A5E9A4A7D212492
            494F21FE337FE42C7FFC36CFFCF77AE3FEA4B77FD69C01FCA79FBABB1DFC1761
            FE337FE42C7FFC36CFFCF77AE47EA27FE2AF07FEBBFF009E6E5532FF003E3CE2
            F51F0ED3E0D98FF533FF00D07FFFD6DAEB341E9BFE30BA7E7804559C58DDE47B
            77B9A709EC69FEA7A4FF00FAE2EED072B131332AF472E9AF22A99D96B43DB23F
            3B6BC1F72CCEBFF56EBEB1B6D6655F8792C6EC6D9538ED22770F56996EFDBB9F
            F41D53D462261C440E2E23C55B79B73267C7CC7DDE3964717B58FD9964AF7070
            43F9BF48F5373A8746E9BD4DF4BF3E9FB40A092CADCE77A664B5DFA6C70EF432
            36BAB63D9F68AEDF4DFF00CDAAD9DF557EAF67BEDB32F06BB5F7926D7EAD712E
            6FA6E7EE639AEDFB3DBBD703D57EAD7D70E9CFD1D7E6544C36DC67D9678FD2A8
            7E999FE67A7FF08B16FC8EB58E76E4599549F0B1D634FF00D28519E608DE0479
            96FE2F8143280717378E60FEEC7F671BECC70309D85FB3CD0C387E98A7ECFB47
            A7E981B055B3E8FA7B3DBB5029E85D2697E4BDB8CDB1F9A1CDC975C5D717B1F2
            5F47EB0EB76E2FB9DFAAB3F57FF825E37FB4BA87FDCABBFEDC7FFE492FDA5D43
            FEE55DFF006E3BFF002487DE87EEFE2CDFF26A7FE7E3FE27FE84FB1F4DFABFD1
            3A53DF674EC2A71ACB06D73D8D01DB6777A7BFE936ADC3F9AFE6D19FD2FA7598
            0DE9AFC6ADD82D6B58DC62D1B036B2D754367FC1B98C73178B7ED2EA1FF72AEF
            FB71DFF924BF69750FFB9577FDB8EFFC925F7A1FBBF8A3FE4D4FFF001447FC4F
            FD09F7359BD67A0E27587E03F25F631DD372ABCDA7D3204BEAFA2CB37B5FFA27
            7E76D5E3DFB4BA87FDCABBFEDC77FE492FDA5D43FEE55DFF006E3FFF002497DE
            87EEFE29FF009353FF003F1FF13FF427DCD25E19FB47A87FDCABBFEDC7FF00E4
            94EBCCEAD6879AEFC878ADBBEC2D7BCED6821BBDFB4FB59B9DF492FBD7F57F14
            1FF8B731BF311FF13FF427DC125E3F81464F50C1B2DA3AC166756481816BDEC7
            D823F46312CDEEFB45D6BBF46CA367F38A964DDD6F11C1994FCAC77B84B5B69B
            1848F101FB51FBCE97C3F8AC8FC038A4603998F144D18984A32FA714BD51FEB3
            EDA92F0CFDA5D43FEE55DFF6E3FF00F2497ED2EA1FF72AEFFB71DFF9243EF43F
            77F164FF009353FF003F1FF13FF427DCD25E19FB4BA87FDCABBFEDC77FE491F1
            ACEBB9648C4765E411C8A8DAFF00FA8DC97DE87EEFE283FF001725116798881D
            CC7FF427BDFF0019A09E878C06A4E5B001FF005BBD657D41FAB7D42BEAA7A967
            516E2B315A454DB5858E7BEC06BFA3637F9B6565FF00DBF4FF0096B43EA8FD54
            CE69A7A9F5BB2C7D8C22CC6C3B5C5DB1D1ECBEE6BF76DB9BFE0EBFF03FF1BFCD
            F689D1C7C7219243876A8B5B373A395E5E7C861947283C432671A0F5FCD0C7FE
            0FE9BFFFD7F554924925292492494A512C63BE9341F8852492521762623BE953
            5BBE2D07F821BBA574C77D2C3A1DF1AD87FEFAAD249505C324C6D223EAD17742
            E88EFA5D3F14FC69ACFF00DF147FE6FF0041FF00CADC4FFB62BFFC82D0490E18
            F60BBDFCBFE727FE349CC77D5AFABCFE7A6E37CAA60FFA96856707A5F4EE9C1E
            3071ABC716106CF4DA01747D1DC7F93BBDAAD24908C46A0054B3659478659272
            89FD132918FD8D43D23A51CA19870E83920EE177A6DDFBB9DFBF6EEDFF00CB44
            CAC1C2CD6B5B998F564B5865ADB58D7807C5BEA0723A4950EDBA3DC9D83C52B8
            E9137F2FF75CFF00F9BFD07FF2B713FED8AFFF0020A4DE87D15BF47A7E2B7E14
            D63FEF8AF24970C7B04FBF97FCE4FF00C693599D37A73082CC5A5A4190456D1A
            FF009AACA4922B0CA52DC93E6A49249243FFD0F554924925292492494A492492
            5292492494A4924925292492494A4924925292492494A4924925292492494FFF
            D93842494D042100000000005300000001010000000F00410064006F00620065
            002000500068006F0074006F00730068006F00700000001200410064006F0062
            0065002000500068006F0074006F00730068006F007000200043005300000001
            003842494D04060000000000070004000100010100FFE12097687474703A2F2F
            6E732E61646F62652E636F6D2F7861702F312E302F003C3F787061636B657420
            626567696E3D27EFBBBF272069643D2757354D304D7043656869487A7265537A
            4E54637A6B633964273F3E0D0A3C783A786D706D65746120786D6C6E733A783D
            2261646F62653A6E733A6D6574612F2220783A786D70746B3D22584D5020746F
            6F6C6B697420332E302D32382C206672616D65776F726B20312E36223E0D0A09
            3C7264663A52444620786D6C6E733A7264663D22687474703A2F2F7777772E77
            332E6F72672F313939392F30322F32322D7264662D73796E7461782D6E732322
            20786D6C6E733A69583D22687474703A2F2F6E732E61646F62652E636F6D2F69
            582F312E302F223E0D0A09093C7264663A4465736372697074696F6E20726466
            3A61626F75743D22757569643A30313861323438632D303863332D313165352D
            393437322D3834663362306666383334372220786D6C6E733A657869663D2268
            7474703A2F2F6E732E61646F62652E636F6D2F657869662F312E302F223E0D0A
            0909093C657869663A436F6C6F7253706163653E343239343936373239353C2F
            657869663A436F6C6F7253706163653E0D0A0909093C657869663A506978656C
            5844696D656E73696F6E3E3532343C2F657869663A506978656C5844696D656E
            73696F6E3E0D0A0909093C657869663A506978656C5944696D656E73696F6E3E
            3532343C2F657869663A506978656C5944696D656E73696F6E3E0D0A09093C2F
            7264663A4465736372697074696F6E3E0D0A09093C7264663A44657363726970
            74696F6E207264663A61626F75743D22757569643A30313861323438632D3038
            63332D313165352D393437322D3834663362306666383334372220786D6C6E73
            3A696C6C7573747261746F723D22687474703A2F2F6E732E61646F62652E636F
            6D2F696C6C7573747261746F722F312E302F223E0D0A0909093C696C6C757374
            7261746F723A5374617274757050726F66696C653E5072696E743C2F696C6C75
            73747261746F723A5374617274757050726F66696C653E0D0A09093C2F726466
            3A4465736372697074696F6E3E0D0A09093C7264663A4465736372697074696F
            6E207264663A61626F75743D22757569643A30313861323438632D303863332D
            313165352D393437322D3834663362306666383334372220786D6C6E733A7064
            663D22687474703A2F2F6E732E61646F62652E636F6D2F7064662F312E332F22
            3E0D0A0909093C7064663A50726F64756365723E41646F626520504446206C69
            627261727920392E39303C2F7064663A50726F64756365723E0D0A09093C2F72
            64663A4465736372697074696F6E3E0D0A09093C7264663A4465736372697074
            696F6E207264663A61626F75743D22757569643A30313861323438632D303863
            332D313165352D393437322D3834663362306666383334372220786D6C6E733A
            70686F746F73686F703D22687474703A2F2F6E732E61646F62652E636F6D2F70
            686F746F73686F702F312E302F223E0D0A0909093C70686F746F73686F703A48
            6973746F72793E3C2F70686F746F73686F703A486973746F72793E0D0A09093C
            2F7264663A4465736372697074696F6E3E0D0A09093C7264663A446573637269
            7074696F6E207264663A61626F75743D22757569643A30313861323438632D30
            3863332D313165352D393437322D3834663362306666383334372220786D6C6E
            733A746966663D22687474703A2F2F6E732E61646F62652E636F6D2F74696666
            2F312E302F223E0D0A0909093C746966663A4F7269656E746174696F6E3E313C
            2F746966663A4F7269656E746174696F6E3E0D0A0909093C746966663A585265
            736F6C7574696F6E3E3330302F313C2F746966663A585265736F6C7574696F6E
            3E0D0A0909093C746966663A595265736F6C7574696F6E3E3330302F313C2F74
            6966663A595265736F6C7574696F6E3E0D0A0909093C746966663A5265736F6C
            7574696F6E556E69743E323C2F746966663A5265736F6C7574696F6E556E6974
            3E0D0A09093C2F7264663A4465736372697074696F6E3E0D0A09093C7264663A
            4465736372697074696F6E207264663A61626F75743D22757569643A30313861
            323438632D303863332D313165352D393437322D383466336230666638333437
            2220786D6C6E733A7861703D22687474703A2F2F6E732E61646F62652E636F6D
            2F7861702F312E302F2220786D6C6E733A78617047496D673D22687474703A2F
            2F6E732E61646F62652E636F6D2F7861702F312E302F672F696D672F223E0D0A
            0909093C7861703A4D65746164617461446174653E323031352D30362D303254
            30393A30323A31342B30383A30303C2F7861703A4D6574616461746144617465
            3E0D0A0909093C7861703A4D6F64696679446174653E323031352D30362D3032
            5430393A30323A31342B30383A30303C2F7861703A4D6F64696679446174653E
            0D0A0909093C7861703A437265617465446174653E323031352D30362D303254
            30393A30323A31342B30383A30303C2F7861703A437265617465446174653E0D
            0A0909093C7861703A43726561746F72546F6F6C3E41646F62652050686F746F
            73686F702043532057696E646F77733C2F7861703A43726561746F72546F6F6C
            3E0D0A09093C2F7264663A4465736372697074696F6E3E0D0A09093C7264663A
            4465736372697074696F6E207264663A61626F75743D22757569643A30313861
            323438632D303863332D313165352D393437322D383466336230666638333437
            2220786D6C6E733A73744576743D22687474703A2F2F6E732E61646F62652E63
            6F6D2F7861702F312E302F73547970652F5265736F757263654576656E742322
            20786D6C6E733A73745265663D22687474703A2F2F6E732E61646F62652E636F
            6D2F7861702F312E302F73547970652F5265736F75726365526566232220786D
            6C6E733A7861704D4D3D22687474703A2F2F6E732E61646F62652E636F6D2F78
            61702F312E302F6D6D2F223E0D0A0909093C7861704D4D3A496E7374616E6365
            49443E786D702E6969643A383132463444353436453038453531313839383643
            44393242303536413545393C2F7861704D4D3A496E7374616E636549443E0D0A
            0909093C7861704D4D3A4F726967696E616C446F63756D656E7449443E757569
            643A354432303839323439334246444231313931344138353930443331353038
            43383C2F7861704D4D3A4F726967696E616C446F63756D656E7449443E0D0A09
            09093C7861704D4D3A4465726976656446726F6D207264663A70617273655479
            70653D225265736F75726365223E0D0A090909093C73745265663A696E737461
            6E636549443E786D702E6969643A383032463444353436453038453531313839
            38364344393242303536413545393C2F73745265663A696E7374616E63654944
            3E0D0A090909093C73745265663A646F63756D656E7449443E786D702E646964
            3A38313246344435343645303845353131383938364344393242303536413545
            393C2F73745265663A646F63756D656E7449443E0D0A090909093C7374526566
            3A6F726967696E616C446F63756D656E7449443E757569643A35443230383932
            343933424644423131393134413835393044333135303843383C2F7374526566
            3A6F726967696E616C446F63756D656E7449443E0D0A090909093C7374526566
            3A72656E646974696F6E436C6173733E70726F6F663A7064663C2F7374526566
            3A72656E646974696F6E436C6173733E0D0A0909093C2F7861704D4D3A446572
            6976656446726F6D3E0D0A0909093C7861704D4D3A486973746F72793E0D0A09
            0909093C7264663A5365713E0D0A09090909093C7264663A6C69207264663A70
            61727365547970653D225265736F75726365223E0D0A0909090909093C737445
            76743A616374696F6E3E73617665643C2F73744576743A616374696F6E3E0D0A
            0909090909093C73744576743A696E7374616E636549443E786D702E6969643A
            3744324634443534364530384535313138393836434439324230353641354539
            3C2F73744576743A696E7374616E636549443E0D0A0909090909093C73744576
            743A7768656E3E323031352D30362D30315432323A35363A30352B30383A3030
            3C2F73744576743A7768656E3E0D0A0909090909093C73744576743A736F6674
            776172654167656E743E41646F626520496C6C7573747261746F72204353353C
            2F73744576743A736F6674776172654167656E743E0D0A0909090909093C7374
            4576743A6368616E6765643E2F3C2F73744576743A6368616E6765643E0D0A09
            090909093C2F7264663A6C693E0D0A09090909093C7264663A6C69207264663A
            7061727365547970653D225265736F75726365223E0D0A0909090909093C7374
            4576743A616374696F6E3E73617665643C2F73744576743A616374696F6E3E0D
            0A0909090909093C73744576743A696E7374616E636549443E786D702E696964
            3A38303246344435343645303845353131383938364344393242303536413545
            393C2F73744576743A696E7374616E636549443E0D0A0909090909093C737445
            76743A7768656E3E323031352D30362D30315432323A35373A30342B30383A30
            303C2F73744576743A7768656E3E0D0A0909090909093C73744576743A736F66
            74776172654167656E743E41646F626520496C6C7573747261746F7220435335
            3C2F73744576743A736F6674776172654167656E743E0D0A0909090909093C73
            744576743A6368616E6765643E2F3C2F73744576743A6368616E6765643E0D0A
            09090909093C2F7264663A6C693E0D0A09090909093C7264663A6C6920726466
            3A7061727365547970653D225265736F75726365223E0D0A0909090909093C73
            744576743A616374696F6E3E73617665643C2F73744576743A616374696F6E3E
            0D0A0909090909093C73744576743A696E7374616E636549443E786D702E6969
            643A383132463444353436453038453531313839383643443932423035364135
            45393C2F73744576743A696E7374616E636549443E0D0A0909090909093C7374
            4576743A7768656E3E323031352D30362D30315432323A35373A31332B30383A
            30303C2F73744576743A7768656E3E0D0A0909090909093C73744576743A736F
            6674776172654167656E743E41646F626520496C6C7573747261746F72204353
            353C2F73744576743A736F6674776172654167656E743E0D0A0909090909093C
            73744576743A6368616E6765643E2F3C2F73744576743A6368616E6765643E0D
            0A09090909093C2F7264663A6C693E0D0A090909093C2F7264663A5365713E0D
            0A0909093C2F7861704D4D3A486973746F72793E0D0A0909093C7861704D4D3A
            446F63756D656E7449443E61646F62653A646F6369643A70686F746F73686F70
            3A35303363346532302D303863312D313165352D393437322D38346633623066
            66383334373C2F7861704D4D3A446F63756D656E7449443E0D0A09093C2F7264
            663A4465736372697074696F6E3E0D0A09093C7264663A446573637269707469
            6F6E207264663A61626F75743D22757569643A30313861323438632D30386333
            2D313165352D393437322D3834663362306666383334372220786D6C6E733A64
            633D22687474703A2F2F7075726C2E6F72672F64632F656C656D656E74732F31
            2E312F223E0D0A0909093C64633A666F726D61743E696D6167652F6A7065673C
            2F64633A666F726D61743E0D0A0909093C64633A7469746C653E0D0A09090909
            3C7264663A416C743E0D0A09090909093C7264663A6C6920786D6C3A6C616E67
            3D22782D64656661756C74223EE68993E58DB03C2F7264663A6C693E0D0A0909
            09093C2F7264663A416C743E0D0A0909093C2F64633A7469746C653E0D0A0909
            3C2F7264663A4465736372697074696F6E3E0D0A093C2F7264663A5244463E0D
            0A3C2F783A786D706D6574613E0D0A2020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            202020202020202020202020202020202020200A202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020200A20202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            20202020202020202020202020202020202020202020202020202020200A2020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            20200A2020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            202020202020200A202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020200A20202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            20202020202020202020202020202020200A2020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            202020202020202020202020202020202020202020200A202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020200A20202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            0A20202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            20202020200A2020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            202020202020202020200A202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020200A20202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            20202020202020202020202020202020202020200A2020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            202020202020202020202020202020202020202020202020200A202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020200A20
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020200A20202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            20202020202020200A2020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            202020202020202020202020200A202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020200A20202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            20202020202020202020202020202020202020202020200A2020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            202020202020202020202020202020202020202020202020202020200A202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            200A202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020200A20202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            20202020202020202020200A2020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            202020202020202020202020202020200A202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020200A20202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            20202020202020202020202020202020202020202020202020200A2020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            202020202020202020202020202020202020202020202020202020202020200A
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            202020200A202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020200A20202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            20202020202020202020202020200A2020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            202020202020202020202020202020202020200A202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020200A20202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            20202020202020202020202020202020202020202020202020202020200A2020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            20200A2020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            202020202020200A202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020200A20202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            2020202020202020202020202020202020202020202020202020202020202020
            20202020202020202020202020202020200A2020202020202020202020202020
            2020202020202020202020202020202020202020202020202020203C3F787061
            636B657420656E643D2777273F3EFFDB00430002010102010102020202020202
            02030503030303030604040305070607070706070708090B0908080A0807070A
            0D0A0A0B0C0C0C0C07090E0F0D0C0E0B0C0C0CFFDB0043010202020303030603
            03060C0807080C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C
            0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0CFFC0001108015102
            0A03012200021101031101FFC4001F0000010501010101010100000000000000
            000102030405060708090A0BFFC400B510000201030302040305050404000001
            7D01020300041105122131410613516107227114328191A1082342B1C11552D1
            F02433627282090A161718191A25262728292A3435363738393A434445464748
            494A535455565758595A636465666768696A737475767778797A838485868788
            898A92939495969798999AA2A3A4A5A6A7A8A9AAB2B3B4B5B6B7B8B9BAC2C3C4
            C5C6C7C8C9CAD2D3D4D5D6D7D8D9DAE1E2E3E4E5E6E7E8E9EAF1F2F3F4F5F6F7
            F8F9FAFFC4001F01000301010101010101010100000000000001020304050607
            08090A0BFFC400B5110002010204040304070504040001027700010203110405
            2131061241510761711322328108144291A1B1C109233352F0156272D10A1624
            34E125F11718191A262728292A35363738393A434445464748494A5354555657
            58595A636465666768696A737475767778797A82838485868788898A92939495
            969798999AA2A3A4A5A6A7A8A9AAB2B3B4B5B6B7B8B9BAC2C3C4C5C6C7C8C9CA
            D2D3D4D5D6D7D8D9DAE2E3E4E5E6E7E8E9EAF2F3F4F5F6F7F8F9FAFFDA000C03
            010002110311003F00FDFCA28A2800A28A65C3B470B32805874CD1706C7D0C48
            0481935F9B5E37FF008399FE12E948C340F04F8FB59900255AEA2B6B289BA118
            22591BBFF778E3D78F1CF1EFFC1D03E22BC574F0DFC24D174D233B64D4F5B96E
            F3C9C12B1C5163A0E371AF0AAF1265D0FF009797F44D9FB4E59F479F1031B671
            CBDC1779CE9C6DF273E6FC0FD84698AE70381FEC9A5F34E402383FA57E08F8FB
            FE0E24FDA1BC58C4E9D2781FC319E9FD9BA3194AFD4DC492827F0AF1DF187FC1
            5CFF00692F1C5C79B7BF173C516ED9C81A798B4E51F85BA20AE0ABC63838FC31
            93F97FC13EFB2DFA2371857D7155A8525D9CE527F74616FF00C98FE947CCF423
            34D69580042E41EFDABF990BBFF82947ED037B6EF13FC67F894A8FD4C7AFDCC6
            C3E8CAC08FC0D6637EDF5F1DA442AFF1ABE2CBA9EA1BC5DA8107F0F3715CCF8D
            685F4A72FBD1EE43E8739E5BDECC297CA337FE47F50467E8460AFAF6A46B9038
            1824751D08AFE5A9BF6C2F8B6EC49F8A3F114963924F892F493FF912B32EFF00
            68EF887A84CF2DC78EFC65712C830D249AD5CB39FC4BE6A65C6B4BA527F7A3B6
            9FD0D7316FDFCCE0BD29C9FF00EDC8FEA9CDC10E06539FCFEB4EF3F1839520F4
            F7AFE50F53F8B3E2AD6A6592F7C4BAFDE488BB55E7BF964603D325B3599A9789
            352D69156F750BDBC54FBA2799A403F3359BE365D28FFE4DFF0000EDA7F432AC
            EDCF9B25FF00702FFF00B951FD655EEAD06996CF3DD4D0DB411E37492B8445C9
            C0C93C7520566DC7C49F0FDB42D249AEE8F1A2F259AF23007E25ABF93ACFA806
            9777A000FE750F8D65FF003E7FF26FF808EBA7F43282F8F376FD285BFF007333
            FAAD93F687F01C7907C6BE12CA9C30FED7B7CAFD7E7ACD7FDAE3E1625C3407E2
            578016756D8633E20B40E0FA60C99AFE58C6477381F87F2A50E41CE0027F0A87
            C6B53A525F7B3AE1F435C0FDACD26FFEE1457FEDE7F569A67C71F06EB3308AD3
            C5BE18BA94F3B21D52091B1EBC39ED5BBA7F88ACB564DF6979697480FDE86557
            03F106BF92E2D9007391DF273F9D1E61F400FD2AA3C6B2EB497DFF00F00E6ADF
            432A4FF859B35EB46FFF00B951FD6DB4D86001520F4A6B5C95C6428CFE15FC9E
            D87C43D7F4B309B6D6F5780DB8023F2EF244098E98C1E2BA0D33F69AF891A34C
            65B3F881E36B49194AB343AE5D2161F83D6D1E3587DAA4FEFF00F807975BE867
            8C5FC2CD62FD68B5FF00B925FD743FAA459F72E40047A8E4529980049231EBDA
            BF976D3FF6EAF8DDA4C4B1DAFC63F8A96F1A1C848FC577E8A3F012E2BA1D37FE
            0A73FB42E95345245F18FE203B43F77CED5E5981E31C87273F8E6B58F1AE1FAD
            397DE8F32B7D0E73C57F6598527EB19AFC933FA67F3F9EAA73E9D68694827033
            8F6AFE6DF4AFF82C1FED2DA396317C5BF113EEEBE7C76F3FFE8719ADCB0FF82E
            2FED49A7C51C69F14A5748CF49341D2E42DCF425AD89FD6B58F19611EF092FBB
            FCCF2EB7D0FF008B63FC2C5E1DFACAA2FF00DC4CFE8ACDC12B90AC0FA119341B
            9CFDDC123B57F3F1A6FF00C1C03FB4C58CE1E5F14E83788063CB9740B5553C75
            F9154FBF5ADCD2FF00E0E2DFDA22C226598F816FC9E8D3E8CEACBF4F2E55ADA3
            C5F817BA92F92FF33CDADF44BE3787C33A12F4A92FD608FDEE8DCBE32314EAFC
            31D2FF00E0E60F8EB666159FC2BF0AAE638F01CFF665FAC920EFC8BCC03F863D
            ABA2D33FE0E78F8A11DC96BCF873E02B88369C085EF226CE78393230C63DBAD6
            AB8AF2F7F69AF91E5D5FA2DF1F43E1A34E5E9563FAD8FDACA2BF1A2C7FE0E83F
            1AC5748D75F0ABC2F34033B922D52E2273C71862AC0738EC6B447FC1D1DAF67F
            E48E6927E9E21909FF00D1156B8A32E7F6DFDCFF00C8E1A9F466F10A2ECB0517
            E95697EB347EC3515F9156DFF074B5C450AADC7C0F82597F8993C606353F406C
            8FF3AB9A77FC1D2B6D35C85BAF8233C310EAD0F8B44AFD3B0366A0FE62AD7136
            5BFF003F3F07FE472CBE8DFE22AFF9977FE56A1FFCB6E7EB4D15F94E7FE0E8AD
            10838F837AB823D7C43181FF00A22B4ED7FE0E81F0435B234FF0B7C551CA572C
            A9A8C0CA0FB1207F2AB5C47973FF0097ABEE7FE472D4FA3D78850DF2D97CA749
            FE533F5168AFCC4D2BFE0E7BF87734F8BDF86BE33B78B6E7741776B39FC8B2FF
            003AD11FF0738FC256200F017C43C9FF0066C8FF00ED7AA8F10E5CF6AABF139A
            7E0271FC5D9E593F9383FCA4CFD2AA2BF3A62FF8399BE06145F33C21F1611CF5
            034DD3C81F426F467F2AB7A6FF00C1CAFF00012F64713E81F142C42F433E9366
            437D365DB552CFB2FF00F9FA8E59F823C771BDF2BABF72FF0033F42E8AF8047F
            C1C87FB3EBB05165F10D493D4E8F0607BF1715AA9FF0711FECE0C013A978B146
            3241D11F23DBEF63F5AA59E601FF00CBE8FDE72CFC1CE388EF9557F941BFCAE7
            DD3457C49A57FC1C1BFB34EA018CDE23F10D891D04DA0DCB13FF007C2B0FD6AE
            A7FC17E3F66377553E34D5901382CDE1FBEC0F7E23AD166F817B568FDE8E6978
            4FC689DBFB2B11F2A537F944FB3A8AF94345FF0082DF7ECBDAF4A6387E29DA44
            EB8045CE8BA95BE33EF25B807F035DAE83FF000542FD9EFC47B3ECFF0018BE1F
            421DB6E6F3578ACF07DFCE2B8FC6B686618597C3522FE68F2F15C03C4F8657C4
            65B8882FEF51A8BF389EF54579BE83FB60FC29F14AA9D2FE267C3ED4C38257EC
            9E23B39B763FDD90D76FA3F8AF4EF10C464D3EFECAFA218F9EDE75954E471CA9
            35BC6B5396B1927F33E7B159762F0DFEF14A50FF00145AFCD23468A89A72AC01
            0003435D00B91FC8D68B5D8E2BF525A2A3F3CE460020D0672141C0E4FBD1604C
            928A8D66264553B79A92818514D99CA46C40048F5E0522CA4C8060107BFAD170
            1F451450014514500145145001451450014514500365731C648EA3FC6A2FB530
            76521495F7E4561FC4BF899A37C26F026A9E23F11EA367A4689A3426E6F2EEE5
            F6C7020EE7D4E70001924900726BF04BFE0A79FF000577F167ED9FE3DBAD27C2
            9A86B1E17F86FA7B3416B656F72F6F2EADCF33DD6C61BB70E5633C28C672791E
            466F9CD1C05352A9AC9ECBABFF00807EA7E16784B9BF1C63654704FD9D187C75
            649B8C7B2566B9A4FA46FB6ADA563F607F697FF82AF7C0DFD954CF6FE22F1C69
            B7DAC5B92ADA468C7FB46F838EA8CB192911FF00AEAC95F9EFFB4BFF00C1CC9E
            29F11F9F61F0B3C13A6F87ACDCED5D475E737978CB9EA218CAC51B76E5E5E09E
            87047E5BAB140A005C20C28C0C0A0B92589032DFE7FC8E95F078DE2AC6D66D53
            6A11F2DFEF67F72707FD17783F28E5AB8F8CB175575A8ED04FCA11B26BCA6E60
            5C1C92AA4B75E3FCE2933C93C8CFBD1457CCD8FE8FE48F60CF1803F5268A28A6
            914905145140051451400514AA3730078CD236DC90A7700719E99A01B0A28A28
            00A28A2800A281EF4AE8541203151DF069360D894503904E4714509826145145
            300A28A2800A28A2800A32718CF1E9DA8A2806833F4FC85193EB9A075E84D285
            1939C607BE38F5A4D85EC1B8EDDB81B7D30282C718E00FA5201C9E41C7BE3F1A
            5283AAB2903AF229929A101C7607F5A5DC474C67E9D2855DD8C6727B62809860
            0E73424869A14C858E4E29379F41428C9201248ED8EB4152599429DC3B1CFF00
            8517129210704900027BF4347A76C7E14A50EF206DC76E6808383BB39E9F29C1
            FC684C1B427D791EFC8A5572A0004E0741D851B4E718604F4E080DF8D2950072
            1B3D87F7A8482F110B939E00DDD7031480E0F73F8D38A6D03218E46738C03F9D
            2600EA180FC3FC686985D06474C0C7A5018AF4CE739EA7AD01095C80723F0A36
            37B51CBE4175D84E32080011E9C53E3B992190488EE92290432B10C08F7A6EC6
            F6A3637B5349AD90AD1EDB9D6787BE3EF8EFC25B3FB2BC69E2CD33CB24AFD935
            7B8836923071B5C63824576BA0FF00C1437E3CF86987D93E32FC4E540BB024BE
            24BB99147A0579081F8578F6C3DF181EF8AD8F01FC3FD6FE28F8B74FD07C37A4
            EA1AE6B5AA4822B5B1B284CD3CEC7B2AAF38EB93C01C93C035B42B575A424D7A
            37FA1E363B25C9EA465571B87A6D24DB73845A496EDB6B6EF7D0FA0340FF0082
            C77ED31E1B756B7F8B1AE4BB48602EED6D2EC703FE9AC4D9FC6BB2D0FF00E0BE
            5FB4D696A82EBC63A46AC54104DD68164A5F3EBE5469D3DB1F8D7B27807FE0DA
            8F1EF897E0A45AB6B3E36D13C3BE36B8FDEA68925B3DCDAC084711CB72872B27
            AEC8DD47405BA8F80FE3EFC05F137ECCFF0015F58F05F8BF4D9B4CD7B4599A29
            A26C949173F2CB1B1037C6E082AC319073F4F57112CD70718CEACA514F6D5FE2
            7E5390C7C2AE2BC556C1E5986C2D7A94BE24A8C13B5EDCD16E0B9A37D39A2DAB
            B5AEA8FB4BC3FF00F0725FC7CD21905CE8BF0CF525000267D26E90FBB7EEEE94
            67F4FA57DEFF00F04F9FF82E2FC3EFDAFCD97873C546CFC03E3F9FE44B4B99FF
            00E25FA9BF03FD1A66C7CC4F489F0DD94BF5AFC07DA2390021D581C8CF142C84
            B0248604F4383DF9FAF3CF35584E26C6D19A94A7CCBB339B8BBE8E7C179BE0E5
            430986585A9F667495ACFCE3F0C9775A3ECD6E7F5A72DD19232070A41F981191
            83D79AFC4ED3FF00E0E41F8CFE04F16EA165AB785BC01AF58DA5CCA88DF66BAB
            6B87018A81BD662A3FEF8CF34DFF00823E7FC1587E2C695F1AFC17F0875B59FC
            7FE1EF115EC5A6DA35E4BFF131D1907DE91262099228A305CA3EE202614A8E2B
            B0FF0082D2FF00C11EDFC2AFA8FC5EF857A4B1D2DF75CF89B44B64CFD8D8F2F7
            B0A019F2F8CC8A33B725C700E3E971F99627178358BCBDB8F23F7975FF008363
            F9CF81FC3AC8784B8A6AF0AF1FD2A75962A31787A97F71DA52567AA95373BA4A
            F65CD1B26F73DEBF61FF00F83837C29FB4DFC54B1F07F8CBC2F0FC3DBDD54886
            C2FCEAA6F2CAE6E09C2C2E4C51F92CDD14B16058A8C8CD7E858BB6272141423A
            8F5AFE4AF2C240F9DCCBDD860FD7D7A75C1C8F5E86BF5ABFE08E3FF05A09EF2F
            741F847F16EF9E5798A58787FC4539667663F2C7677479CB1E1525EFF286E7E6
            ACF22E279549FD5F1AF57B4B6F93FF0033D1F1C3E8DB4B2FC33CEF83E93F6705
            7A946F293496F3A6E4DC9A5F6A2DB7D63D97DF3E27FF008298FC0FF06FC5DB8F
            01EADF11345D2FC556B78B63359DDC73C2B0CC71856959046B9C8E4B01C8E6BD
            BA3D43CC58D97632CA01520E4107BF1F873D2BF32FFE0AA9FF000441D67F699F
            8A3AF7C54F86BADC0FE23D5C4726A1E1ED436C305DC9142B0EFB69F808CCB12F
            C92705998F9880803E32F879FF000545FDA6BFE09D5E1BD47E15EAD6C2DA7D34
            A0B583C57A7493DE68A9CE05BB165DD11FE1DC248F1F7703AFA55F3DAB83AD28
            63A9DA177CB25AE9E7E67E7994782794F15E514317C179829E29463EDE8566A3
            2849A5CCE2D453E48BBEEA49ADA57F74FE814DCE00C6093F864FA551D27C5FA7
            EBE671617F617CD6B279338B79D6530C9FDD6DA4E08F438AFE67BE3A7FC1443E
            36FED1ED37FC25BF11FC4F7F653821ACEDEE3EC562C0FF00098200919FC56B88
            F81FFB44F8DFF66EF1926BFE05F13EAFE18D5578796CA728B72067092A1CA48B
            93D1D48EF5E7CB8D292A968D36E3DEEBF2B7EA7DE61FE8739A3C0CEA62331A71
            AF6D22A1270BF54E6DC5DBCF934ECCFEA9E1B832EDF94807D463B54B5F985FF0
            4C6FF82F1CDF1F7E2268DF0EFE2A69FA4699AFEACE6DB4ED7ACE430DB5E5C63E
            48A68589F2DDFEE8656DACE40DAB9E3F4E21B832B72460F4E39AFAAC06614719
            4FDAD0775F8A3F98F8DB81739E14CC3FB373AA5C936B9A2D3BC671BDB9A2FAAF
            27669E8D225A28A2BB4F903F297FE0E6D8BC6561E07F871756BAADEA781AF2E6
            E2D750B043B216BE016481E4C0CB131897009C031E40079AFC7ADE704600278F
            4E3D2BFA35FF0082D27C2BD1FE25FF00C1377E23AEAB22C2DA0DAC7ACD8CEC01
            305C412A95C71FC6A5E3FA4A6BF9CA650003823238C91F957E5BC5B41C31FCED
            DF9927E9D0FF004C7E8A99DD3C6F052C22828CB0F52706D2B73735A6A4FBBB4B
            95F5F75094019206702818EF9C57E85FFC122FFE08EFE12FDBD3E14DEF8F3C55
            E2DF1058E9FA7EB1368EDA569314514BE6470C32EF371207054ACE9F288C743F
            3578981C0D5C5D654692D5FE47ED9C69C6795F0BE592CDB379B8D24D4748B936
            DECACBBF76D2F3472EBFF06F47ED1AFB40D33C29961919D6A307F1E38A7FFC43
            C5FB47FF00D033C25FF83C8FFF0089AFDF648150019269DE50F4AFD0FF00D4FC
            07797DE7F9FCBE969C71D6143FF05CBFF933F01FFE21E2FDA3FF00E819E12FFC
            1E47FF00C4D1FF0010F17ED1FF00F40CF097FE0F23FF00E26BF7E3CA1E947943
            D28FF53F01DE5F78FF00E26D38DFF9287FE0B97FF2C3F01FFE21E2FDA3FF00E8
            19E12FFC1E47FF00C4D1FF0010F17ED1FF00F40CF097FE0F23FF00E26BF7E3CA
            1E947943D28FF53F01DE5F787FC4DA71BFF250FF00C172FF00E587E04C3FF06F
            07ED1AF2A2BE9FE118D0900B7F6DA1C0F5E1735DAF83FF00E0D9DF8C7AA3236B
            7E32F875A446C012B05CDDDDCABC1CE47908B9CE3A357EE0F94293C85CE72DF9
            E2AE1C2397AD5A93F57FE472E2BE959C775636A72A307DE34F5FFC99C97E07E4
            9F83FF00E0D7A822DAFE21F8C32CA4F5874EF0F84238FEFC939FFD02BD3F46FF
            0083673E0A5AE9C5751F18FC4EBBB9650BE643796102AF3D554DAB633D3927AD
            7E8F18549C9E4FAF7A3CA18201233EF5D94F8772F86D4AFEB77FA9F1F8EFA407
            8818A95EA66525FE18D387FE9315F89F997AFF00FC1B25F0B2E25234AF883E3F
            B452D902EBEC77042FA7CB1202735C86B7FF0006B969B38CE9BF1A2F6D7E6271
            73E1959FE5EC32B729CFBFE95FAC66204609269040A08200E289F0E65D2FF977
            F8BFF32B0DF483F10A87C19949FAC29CBFF4A833F21B4FFF00835C6F6567FB57
            C6BB68429F9447E14690B8F7CDDAE3F5AE9B4AFF00835F3C330737DF16F5EB90
            546041A2C5010DEBF34AFC57EAA940DD72690C20F192054C786B2E5FF2EFF17F
            E674D7FA46F889574798B5E94E8AFCA99F9ADA27FC1B29F08209221A8F8EBE24
            DD00BF38B796CA024E3A8DD6EF819EC735D2E9FF00F06DCFECFB6768B1C9AAFC
            49BB9232434B2EB36C1DB3EBB2D82FE82BEACFDBA3C7BF107E12FEC7BF11FC4F
            F0A341B3F13FC45D0742B8BDD0B4CBB0CD15DCE8BBB1B5482EC14332C6082ECA
            AB91BB35FCC7E87FF0767FEDA1A0EB86E2E7C5FE11D5608DB3F62BCF0B5AAC38
            CE76931AA498ED9DF9C7BF35B4721CBD6D491E356F1C38F2ABBCF34ABF2697E4
            91FB8B7DFF0006DA7ECFD7903471EAFF00132D647E9245ABDB174E73D1ED987B
            720F5FC6A87FC432FF0001FF00E86DF8B9FF00834D3BFF00906BE45FF82747FC
            1E59A07C4BF1669DE18FDA37C17A7F81DEFD9635F167871A6974B85C9C66E2D2
            4679A18F1FC6924BC9FB80648FDBCF0B78B34EF1BF87B4ED6347BEB2D5749D56
            DE3BBB4BCB4984F6F750BAEE492375CABA3290430382083E996F22C03DE92261
            E36F1DC55966957EF5FE47E7EFFC432FF01FFE86DF8B9FF834D3BFF9068FF886
            5FE03FFD0DBF173FF069A77FF20D7E8A514BFB072FFF009F48BFF88E3C79FF00
            434ABF7AFF0023F3AFFE2197F80FFF00436FC5CFFC1A69DFFC8347FC432FF01F
            FE86DF8B9FF834D3BFF906BF4528A3FB072FFF009F483FE238F1E7FD0D2AFDEB
            FC8FCEBFF8865FE03FFD0DBF173FF069A77FF20D0DFF0006CC7C07033FF096FC
            5DFF00C1A69DFF00C835FA29430DC083900D1FD8397FFCFA40FC71E3CFFA1A55
            FBD7F91F9BDA9FFC1B2DF0565082CBC69F1460607E6335ED84C08F6C5A2D536F
            F8363FE128191E3DF88A4FFBF65FFC62BF4AC443209C9C74F6A5D83D293C832F
            FF009F48D21E3B71F455BFB4EA7FE4AFF389F9C1A47FC1B31F04E35C5EF8CFE2
            8DC3939061BEB08971EE0DA356DE97FF0006D7FECFFA7DB949759F89D7AC5F70
            79F56B4DC07F77E4B5518FC2BF41360DC0E4E47BF14B4E390E017FCBA46353C6
            FE3BA9F166757E4D2FC923E11D2FFE0DD2FD9CEC2DCA4B0F8E2F98BEE0F3EB60
            30FF0067E48D463F0AD7D33FE0DF8FD99AC2DC24BE18D7EF583160F36BD72186
            474F91947E95F6BD15A4726C0ADA8C7EE470D5F17B8DA7F166B5FE5524BF268F
            902C7FE0839FB2D5ADB88E5F86F7178DDE497C47AA2B1FFBE2E147E95ADA7FFC
            112FF65FD32D84317C2AB1641DE4D5B5095BF369C9FD6BEA9A2B4595E0D6D4A3
            F72382A7899C5F53E3CD712FFEE3D5FF00E48F9BB4FF00F82427ECD9A6DB88A3
            F849E1A641FF003D4CD2B1FC59C9AD7B2FF825CFECEF616C90C7F077C04C89D3
            CCD2A395BF36049FCEBDEA8AD56070CB6A71FB91C1578E388EA7F1330AEFD6AD
            47FF00B71E3763FF0004EDF807A7DB2C31FC16F856CA9DE5F0AD8CAC7F16889A
            D8B2FD8B3E0EE9B6CB05B7C29F86F040BD238FC3364A83F01157A65156B0B456
            D05F72386A71266F3F8F1551FACE5FE671769FB37FC3CD3EDD61B7F02783ADE1
            4E891E8B6C8A3F0098AD7B5F861E1BB0B6586DF40D16DE24E891D9448A3F00B8
            ADDA2AD5282DA2BEE386AE618AA9FC4AB27EB26FF521B5D3E1B1852282248638
            C6155142A8FC0548D18752093834EA2AD451C6F5DCCCBDF0568FA95C99AE74BD
            3EE666E0BCB6C8ECDF524545FF000AF340FF00A01E8FFF0080517FF135B1452E
            48F6368E26AA56537F7B31FF00E15E681FF403D1FF00F00A2FFE268FF8579A07
            FD00F47FFC028BFF0089AD8A28E48F62BEB55BF9DFDECC7FF8577E1F3FF303D1
            FF00F00A2FFE26934FF877A0E93AB25FDAE8DA5DB5F2218C5C456B1A4A13FBBB
            80CE2B668A1423D84F1559A69CDD9F9B216B147392589FAE2BC3FF006B7FF826
            F7C25FDB7356D1750F1F68135EEA1A1234305D5A5D3DA4D242DCF9323260BA06
            F9803CA9CE08DCD9F76A2A2B50A7560E15629A7D19D7946718ECAF151C6E5B5A
            546AC6F69424E325756766ACF547CA1E1CFF00821FFECBFE1951E4FC30B7B971
            825AEF57BFB8DD8F50F395FD2BBDF0EFFC1333F67CF0BA2ADAFC1BF8772AA823
            177A241779FA995589AF72A2B186030D0F869C57C91ED62F8F789B157FACE635
            E77EF5AA3FCE471DE0BFD9E3C05F0DEEE2B8F0E782BC27A05C424B472E9BA45B
            DA3A12BB4E0C6808CA920E3A826BA7B9D3A26858302CA782AD823078EFD78AB5
            48EA1D4839C1AE88538C55A2AC7CD627155B113F695E6E52EEDB6FEF7A9F97BF
            B6D7FC1BC1A6FC67F8AF7DE27F861E22D27C156FAAB19EE346BBB477B48EE096
            CBC2C87E446E0F97B48524EDC2FCB5E5FF00B37FFC1B8DE3DF09FED0DE1EBFF8
            81E23F08DDF82F4CB9FB65D1D0F50BA37972633BA38807813665C2EE2AD90BBB
            041C57EC81814B64F2739ED41B643DB1F4E2BC5A9C37809D5F6CE1ADEF6BE9F7
            1FB265FF00485E38C2658F2A8E294A1C8E0A528A734AD6BF3EF74B693BB5A6AC
            AD6F689BC1C3023DCE471FE00579E7ED3DFB1FFC3CFDAE7C0ADA1F8F7C3563AE
            C11E7ECB70EBB2EEC1891F3C332FCF19E0670707A3061907D3446030209E33F4
            34AE82452A7A1AF6AA5384E2E13574FA1F8F6031D89C0D78E2B0751D3A917752
            8B7169F74D34D7DE7E19FEDD1FF06FB78F7E078BFF0010FC2D9AE3E20F85E106
            46B0F2C0D72D933D3628DB7007AC7863FDCEF5F9E97FA7CFA35FCD6D7504F6D7
            56CE63962990A3C4E0E19594E08607823A83D457F5A8D6A8C083939EBDF35F1E
            7FC157FF00E0995E0CFDACFE0478AFC47A6F87AC6DBE28693A7B5E699AADB810
            4F7AD0E1FECF315C0943A2B2297C952C082318AF89CDF84A1CAEAE0DD9AD795F
            5F4FEAC7F65F853F4A7C6C2BD1CAB8B23ED2326A2ABC6CA51BBB5EA4748C92DD
            C95A4926DA933F9EAB7BA96D6686586478A681C3C6E8C55D08390411D083C823
            1835FD00FF00C1187FE0A449FB6B7C151E1FF125EA37C47F05C0916A5E6380FA
            B5B0C225E8F56246D930301C83C07503F9FC6010A9E80F63DFDBF9FE55EDFF00
            F04D7F8A7AAFC23FDBBBE156A5A55FCDA71BCF12D8E977AF19C096D2E6E23867
            461D0831B1383C0214F502BE6B21CCA784C5C7F96564D7EBF23FA33C6FF0E309
            C5BC37562D72D7A11954A52B6A9A5771FF000CD2B3F3B4B747F4D71CACC40214
            83DC549505B26C7C1C020E00E9C54F5FAF1FE4EA6FA9F197FC17ABE209F067FC
            133BC696C2458E6F10DE69DA5C471CB13771CCEBF8C70B8FA135FCF687213680
            02FA0AFDA8FF00839B7C7234CFD993C01E1BDFB5F58F13BEA181D5D2DAD6443F
            866E97F102BF15ABF2EE2EA9CD9872FF002C52FD7F53FD33FA2865BF56E06588
            6B5AD56A4FEEE587FED82A677AE3D6BF64FF00E0D7EF160BDF84BF15B412D93A
            5EB3657E17FBBF688248F3F8FD97F4AFC6B19EDD6BF5FF00FE0D71D20C3E19F8
            CBA880E45DDCE916C58FDD3E5A5EB71EFF00BDE7F0AE7E176D6630B79FE4CF6F
            E9354A9CBC3DC6B9EEA549AF5F6B05F9367EB0D14515FAC9FE59051451400514
            51400514523B6C52C780393400B45442E32A0801988CE07A7E3FD6BE74FDBF7F
            E0ABDF043FE09ADE099B53F8A1E33D3EC355784C963E1EB375BAD6B533DBCAB6
            53BB69381E63ED8C67971401F48515FCDBFC61FF0083D7FE346ABF11A793E1E7
            C27F85FA3F84C4B882D7C422FF0052D45E307EF3CD05C5BC6ACC3F8444C14F01
            9FA9FD0AFF00823AFF00C1CD7F0EBFE0A57E2DB2F879E32D1A2F861F15AFBE5D
            3ECDEF3ED1A5F88080495B69880C936013E4C8327185773C000FD3EA2A38E632
            30C01B4FBF3525003655DF1B0209C8EC706BF8EBFF00838EFE02F83BF673FF00
            82C17C5AD0FC10D045A65F5C5AEB777650A858F4DBDBDB58EEA78540180A5E53
            22A8E15650BFC35FD876B1AB5B683A55CDF5E4F15B5A59C4D3CF348DB5228D46
            59893D0000927DABF866FDBC3F695B8FDB0FF6C9F89FF13EE4CC3FE137F125EE
            A96D1CBCB5B5ABCCDF67849EFE5C22341EC9401E4D1C855891824F5CF3FCEBF7
            53FE0D12FF0082B7EA3E18F8A03F65BF1B6A53DDF87FC411DC5FF81659C96FEC
            CBB8D5E7B8B104FDD8658D6495013859236519329AFC32D1749BAD7B58B4B0B1
            B6B8BDBDBE992DEDEDE08CC92CF2390AA88A3966624000724915FD247FC1BF5F
            F06CF6BDFB157C63F0E7C77F8D7ABDA8F1BE93692C9A1F84F4F3E6C5A34B3C0F
            0B4B7738F96499629645112028ACDBBCC7200001FB52AE58E0803233EF4EA40A
            010724E296800A28A2800A28A2800A28A2800A28A2800A28A2800A28A2800A28
            A2800A28A2800A28A2800A28A2800A28A2800A28A2800A28A2800A28A2800A28
            A2800A28A2800A28A2800A28A2800AC8F88203780F5A07A7D866FF00D16D5AF5
            91F103FE444D6FFEBC27FF00D16D5151FBACDF0DFC687AAFCCFE4E08C2903A03
            FD056DFC2DF140F047C4DF0E6B44851A46A96B7B9C918F2E657EDF4AC46FE2FC
            3F90A6A9C1072463DF15F8645F2CAEBA33FDBBAF4635294A94B69269FCF43FAD
            AB7E4827049E454D5CAFC16F137FC26DF097C27AC862E355D1AD2F771392DE64
            28F9FD735D557EE9092945497547F8855E8CA8D49519EF16D7DCEC7E337FC1CF
            9E3196EFE327C2CF0E93FBAD3345BCD471CE33713A47FF00B6DFCEBF2E2BF4A3
            FE0E6E73FF000D67E02520103C24BCE471FE9973DBF035F9AF5F91710CAF98D5
            F5FD11FEB07D1FA8469787D96460ADEE49FCDCE6DFE62C78DE339C035FB57FF0
            6C468C2DFF00664F887A865B375E264B7DA4703CBB489B8FFBFD5F8A91FDF5FA
            D7EEB7FC1B61A41D2FF60CD6A605CAEA3E33BD9C065DB8C5A59C7C7A8CC67F5A
            EAE1385F318BEC9BFD3F53E5BE94F88F67C055637F8EA528FF00E4DCDFFB69FA
            13451457EAA7F986145145000C481C0CD304A7201C027A03C73E9FA53A450EA4
            100835FCACFF00C1CF5F1CBE3AFC14FF00829BF8FF00C0971F163E248F877ADD
            BD9EBBA268BFDBF77169F1DB5CDBA8745815C2145B88E7400838D9EBCD007F45
            3FB4DFFC1537F677FD8E84E9F11FE30F817C377B6D9F334E3A8ADD6A4B8EBFE8
            906F9CFE095F9B5FB59FFC1E8FF06FE1D9BAB0F845F0F7C57F122FA3CAC5A86A
            922E87A637F7645DC24B871DF6B45193EA3AD7F352AED239246F241278E7EB5E
            E7FB217FC1363E39FEDEDACB59FC24F86BE26F17C114A609F528615834BB6900
            C9496F25296E8D8390AD20623A039A00FA63F6C7FF00839DBF6B5FDAE56EAC2D
            FC6B07C2FF000FDD640D3FC150BE9D2633C66F199EEF7763B255523236E0915F
            055C9D6FE216AFA86A73B6ABADEA32EEBBBEB972F753BE48DD2CAE72D8C9E59B
            B9EB5FB9FF00B0DFFC1969ACDD6A765ACFED09F122C2C74F475965F0DF8437CD
            3CEBC1F2E5BD99156339E1845149919DB203861FB8BFB2CFEC77F0CBF628F863
            6FE0FF0085BE0CD13C17A144A37C5610059AF1C0C096E253992797FDB9199B1C
            671C5007F0ACE8426ECE718E873EA3F0FA55CF0CF89AFF00C23E23D3F56D2EEE
            7D3F53D2EE63BCB3BAB76F2E5B799183248AC3952AC01047422BF537FE0EDAFF
            00827FF86BF639FDB97C3BE31F0568B69A0786BE2FE9536A13D9DAC623823D56
            DA6DB76D1A280115D26B572A382EF21EE00FCA353839E9401FDBEFFC12E3F6A2
            BAFDB57FE09F5F08FE296A251B59F16787609B55645088F7D18305D32A8E154C
            F0C981D8715EFAC48524633EF5F05FFC1B19A65C693FF0437F8131DD0612C906
            B13283C9D8FAE6A1227E1B196BEF47FB87A5007C1BFF000722FED9A9FB1C7FC1
            26BE235CDBDD7D9B5FF8811A782B460ADB5DE4BD0CB70C0FF095B44BA607B32A
            FA8AFE3E826E60002C07A7535FAF3FF0782FEDE89FB41FEDC5A2FC20D0EF4CFE
            1FF8356446A2118F972EB176A924C08CE0F9508823F5576997D6BF283E1D7C3D
            D73E2BF8EF47F0BF86F4BBBD6BC41E21BD8B4FD3AC6D63DF35DCF230448D0772
            5881D87B81CD007D73FF000401FD8ABC59FB637FC1513E168F0D5BC674AF875A
            F5878D35FBEB984C96B6567617714FB241919333A2C4AB9E4C99E42B63FB218D
            5490473B7D793FE715F1A7FC1107FE0957A3FF00C1287F639B1F0B4896B7BE3F
            F13F97A9F8CF548C065B9BD29F2DB44C7936F6EA4A27663E63E019180D9FDB63
            FE0B7DFB33FF00C13FAE750D3BC7DF137499FC55A72812F86B45FF008996AEB2
            7FCF39228B2207208389DA318EFD2803EB6270334CF3490081D4E3A8F4AFE78F
            F6BFFF0083D7FC51ACBDD69FF033E13E91A25A12563D63C6570F7B732291F785
            A5BBA47138EA374D28F55AFCC8FDA93FE0B59FB527ED94F73078E3E3378C65D2
            AEC149749D26E0691A7327F71ADED4469201FF004D031E339CD007F59DFB507F
            C1593F671FD8D0DD43F123E31F81FC3DA959FF00ADD292FC5F6A91FA13676FE6
            5C0049EA631FA1AF847E377FC1E63FB337802E2E2DBC21E16F89FE3D9E23FBBB
            88F4FB7D32CA61EA1A7984C3F18457F2FF00969301B71279C96CE33D7E94D2B9
            1C0FA81F4FF3CD007EFB78ABFE0F8E9DE464D0FF0066D8911240566BEF1C1732
            C78E479696236B671FC6C07BD779F057FE0F75F87BE23D760B7F881F033C5BE1
            4B192408F77A1EBF06B8C8381BFCB961B53819E4024E3A64F15FCE6C849CB7CA
            0924F5069AB2B2918EA381401FDD27EC7DFB6D7C32FDBD3E11DB78E7E14F8AF4
            FF00167876790C12C90078E7B198004C13C2E1648640083B5D47041190413EAD
            5FC8DFFC1B07FB6CEBBFB28FFC154FC0DE1CB6BEB84F08FC5AB91E16D6EC572D
            15CC92ABFD8E5DA7812477262C3F508F2AF01DB3FD70C72338195C13F90A007D
            1451400514514005145140051451400514523B1552475A02E2D14C5918B80470
            7BE29F40051451400514514005145140052392A84820103BF4A5A494031B03D0
            8E7BD00723F173E3EF823F67CF0A8D7BE2078C7C29E06D09A55B71A8EBFAB5BE
            9B69E631F953CD99D5771EC33CFBD54F851FB4EFC39F8EE33E07F1FF0082BC66
            02EE2742D72D75100633D61761EFF4AFC2DFF83D5BF663F1F6A3E2CF857F176D
            EEEE750F867A669E7C2D7164ACCD168DA93CD34FF6971D07DA63291EFF005B45
            07EF0CFE0E697AB5E681A95BDE595CCF657B6AC2486781CC72C4C0F0CACB8208
            23AE723AD007F7D8AECCFDB6FD3E9FFD7A7D7F281FF04C7FF83A3BE3DFEC49E2
            0D3F48F887AA5FFC66F870ACB15C58EB57464D634F8B382F6B7AF976600E424E
            64421768F2C9DEBFD34FEC61FB6AFC39FDBF7E03E97F11FE1878820D7FC39A96
            62906D31DCE9B72A0192D6E223F345326E5CA9EA19594B232B100F56A28A2800
            A28A2800A28A2800AC8F881FF2226B7FF5E13FFE8B6AD7AC8F881FF2226B7FF5
            E13FFE8B6A8A9F0B37C37F1A1EABF33F9386FE2FC3F90A44FBC3248A56FE2FC3
            F90A6AE370DC70A3A9F415F854B767FB827F4EBFF04E6F120F167EC1DF06EF77
            891FFE10ED2E176DFB8B3C76B1C6D9F7DC86BDAEBE53FF008227788CF8A3FE09
            97F0B2E19B2F6F6B7966CB904A98AFEE63E71EC83F022BEACAFDB701514F0D4E
            6BAC57E47F8C1C7383FAA71266185FE4AF563F754923F0CBFE0E6262DFB76784
            C12481E03B3207607FB4351E7FCFA57E7657E86FFC1CB374B71FB78F8610105A
            1F02D9A363B1FB7DFB7F2615F9E55F9467DFF230ADEA7FA93E072B701E57FF00
            5E97E2DB0CE327193838FAE2BFA12FF82077865743FF0082677826E8001B56BD
            D4EEDB924B117B3420F3ED10AFE7B57391DABFA3DFF822E46BFF000EC9F84ECA
            A17361727009233F6DB8C9E7B93CFE35EBF06C53C64A5DA2FF00347E53F4BEAF
            2870861A9ADA58885FE54EABFF0023EA3A28A2BF4B3FCE30A28A28011CE14E46
            735FCF07FC1EE7F04E1B3F8A9F01BE23411069B59D2F52F0DDDCCA074B69A1B8
            814F39E7ED97047D2BFA206200248C81ED9AFC63FF0083D77C1EB77FB00FC2CD
            78AA1934DF8809A7AB9621945C69D7B2118E983F6553FF0001A00FC5AFF82177
            EC59E1BFDBEBFE0A7DF0CFE1CF8C04B27856E67B9D5356B74628D7D0D9DB4B73
            F67C8C30591E25462A430476C107047F64BE01F00E87F0BBC1DA6E81E1BD174D
            F0F687A45BADB5969DA7DB25ADAD9C4BD2348D0055007603BFBD7F27DFF06A2A
            86FF0082D9FC3724839D2F5BFC0FF665C7EB5FD527ED25ABF8DBC2FF00B3F78D
            352F869A5E95AD7C41B1D16EA6F0ED86A6E52CEF2F962630C7295653B0BED070
            CB9E9B9739001DAA057270060F191CFAE07B53B663A135FCF17EC7BFF078AFC4
            DF01FC7D6F0C7ED2FF000F7C3F178723BF7D3F53BBD074FBAD3B57F0E4AAFE5C
            8D2DB4B2CA2658D9595A21B2418272C5761FDFFF0086BF13B41F8C9E01D1FC53
            E16D5F4DD7FC37E20B54BED3B51B0B859E0BB81D772488E0E0823F2FCE803F14
            BFE0F7AF0B457DFB3C7C07D75A291A7D3BC45A9582C800D8A27B689D81EF96FB
            3A91CF453D78C7F3A28096000249F4E6BFA3BFF83DCF5E36DFB2C7C11D2FED18
            177E2BBDB9F2B18DFE55A05DDFF011301FF02AFE711080C09CE2803FB5CFF822
            EFC3F1F0BBFE0937FB3CE94A8D1B3F8134AD4244618647BAB75BA70476C34C6B
            43FE0AADFF00050AD0BFE099DFB12F8BFE28EACD6B36A76507D8BC3BA7CA491A
            AEA92822DE1C020B26E0647C104471487B57A27EC7BA6C7A2FEC8DF0BAD6188C
            315B78474989221D500B28801F800057F333FF00075A7FC1466F7F6BBFF8283D
            EFC33D1EF663E05F82524BA2C502B7EEEEF57CE2FAE081F78A328B719FBBE439
            18DE7201F9A7F127C79AC7C59F883AEF89FC45A84FA9EBDE22D427D4B51BC9DF
            7C97571348D24B2311DCB313C0C7271E95FD16FF00C1AC7FF04396FD9EBC15A7
            7ED23F15B4911F8E3C4D6BE6783748B988893C3F612A11F6D933F76E27463B57
            FE59C4C09CBC988BE54FF83653FE0816FF00B5278BB4BFDA07E3168C7FE159E8
            773E7785F44BC878F155DC6C36DCCA8EB87B18DB380789A45C1F91595FFA5910
            A83919FE98F4FA5007CDDFF0544FD9B7E2DFED61FB24EBDE0AF82FF1421F84DE
            2ED4C8126A8F6D23C9776E1583DA09E26F36D4392099A3476C0C01F3135FC92F
            EDDDFF0004B0F8F7FF0004F8F184F65F15BC0BACD85B4D331B7D7ADD4DEE93A9
            F058B477680A3123E628E56419F990735FDB57923B963CE7939A5F257D38A00F
            E147E0EFEC6FF16FF686D4A0B4F027C33F1FF8C26BB6509FD8FA05DDEA9079DC
            5A3421540E4B13800127815FA2FF00B177FC1A0BFB487C7E9ED750F89773E1FF
            00835E1F9082EB7D3C7AAEACE87BA5B5BB98C1ED8966461D769C60FF00531B06
            491C123146C0460F22803F333F652FF83503F64AFD9F34EB67F1378735DF8B1A
            DC615A4BDF12EA32476FBF1CECB5B63147B0F6497CC23D4F5AF71F8A9FF0408F
            D8F7E2C7826EF44BCF80BE03D2A2B942AB77A2D9FF00655E5BB1180EB34051F2
            A79C3120E30410483F60AC2A841192452B8CA91C0CFE3401FC66FF00C170BFE0
            9597DFF049AFDB32E7C156D7D7BADF81BC4168359F09EA976A05C4D665D91A09
            CA80A6786456462A0075F2E40A82408BF1BA637024E00AFE8D3FE0F76F8716B7
            FF00B36FC0EF1718A3FB5E8FE25BFD2164CE1B65D5AACC4631C8CD983D78C9F5
            AFE72E32438C0273DBD7DA803F577FE0D3EFF8269DF7ED65FB7541F17B588678
            7C0DF04EE12FBCCC151A86B0E8DF64814FFD33C34EE47DDD9083FEB057F53BB4
            6413924735F0FF00FC1BB3FB2241FB1FFF00C125FE14E9D25A4706BDE35B1FF8
            4D359900F9E6B8D415668F7FA325A9B6888FFA655F70D002336D52719C53239F
            CD63B4AB8070707A76C7D720D3DC80A493803AD7F1DFFF00058BF8F7F197F679
            FF0082B9FC77D3ECFC7BE3EF085CD8F8D6FAF2C20D33C49796C2D2D6E1FCFB66
            8FCB75D81EDE68D86DE81F1401FD87AB96E838CE3D714EAFE557FE099DFF0007
            547C7CFD937C77A6697F16F5BD43E327C3A96548AFA2D59964D72C2327E696DE
            ECE1E57039D93B386C6D0509DE3FA7FF00827F1ABC35FB44FC28F0E78DFC1FAA
            5BEB5E18F15E9D0EA9A6DEC3F72E20950329C755619C329C32B02A40231401D5
            D14514005248C55491814B4CB850F0B020107D7A1E680B191E38F1D58FC3DF07
            EADAEEA93C56BA6E8B6735F5CCCEEAAA914485DD8962000154E492057E367C40
            FF00839A7E28DF788B555F0DF813C0BA7E8F28DBA7ADFA5DDCDDDBE5B8795D65
            447F97F85635C13D4E39E4FF00E0A35FB4078C7FE0A6BFF050EB7F845E09D6AD
            1FC2B16A2344D1923B8952CAEB0A8F3DCDC94DDBD55E395810876A20E09193E3
            DFB2CFFC13367FDA4FE36EAFE00B8F899E0ED0B5DD1757BCD266B6B7B6BCD4E4
            945AAB192E95E2845B0B73B5C2BC93A6482300B283F039A6758CC45754701751
            4DC6FA6ACFEE2F0C7C1DE16C8F289E6BC73CB52ACE942B7B371A92F634DDDF34
            94756DB5693E5F7795C7BB3EBAFD977FE0E59D42C229EDFE2EF8462D499AE233
            6F7BE1A84C26180822469239656DE41E46D2BC57EAAFC1CF8D5E1BF8FF00F0FF
            004AF15F84357B3D73C3DAC4465B6BCB724AC982432907956560432B00548208
            041AFE727F6DCFD91B45FD93B50D2EC34FB8F88DA9DCDE4D3A2EA1AEF84D743D
            3B508E26552F66C6E2569802E37642EDDCBFDEE3EBAFF836EBF6AFD4BC2DF1BF
            5CF8477B70D3E89E26B59B56D32367056DEF2055F342F7FDE42B923BF90A7D73
            59367B8A862960B1AEF7D2FD53DD5DF5B9978BDE0AF0DE2B86AA718707C1D3F6
            779CA09494254D3E59351925283859BED64EEAFB7ED3D14D490B6338C1FD69D5
            F7699FC4298514514C614523121490326B3FC49E2AD3FC1FA0DE6A9AB5F59697
            A6E9F119EE6EEF27482DEDA303259E4621540F5240A00D076DAA4F3C7E34C694
            9046D391CFBFD6BF2BBFE0A05FF076A7ECF5FB2A8BED17E1B0B9F8DBE2C8098B
            3A44DF67D0EDDFA65EF5948940EBFE8E9229E9BD7A8FC45FDBF7FE0E27FDA7BF
            6F817BA6EA5E3597C05E0EBA665FF8473C225F4EB774E06D9E70C6E2E011D55E
            42848C841401FD007FC16A3FE0A77FB1F783FF00666F1F7C21F8C5E3BB3F10DE
            78A74B9B4E9FC39E1609ABEB16B31C18E5D8A7C9B79A2955254370F18DD18E0E
            769FE46AE9121924F2999D3380586D623DC027078E99EBEBD6A2476661C92464
            E7A9F7AFD03FF8245FFC1BC3F16FFE0AB9E1B7F1845A8D87C3AF8631DC3DAC5E
            22D52D9EE24D56542448967002BE6AA302ACECE881B2A0B3232A807E7E46C4C8
            B8001CF1C67F0AFB6BFE0861FF000569F11FFC12AFF6BDD3F530F7DA9FC37F18
            4D0E99E30D1215676B9877158EEA1419CDC5B972C800CBA978F8DFB87EAB786B
            FE0C86F86F6B6F00D63E3AF8E2FE5570666B3D0AD6D15D7B8557794A9F725BE9
            5F70FEC03FF06F07ECC9FF0004F3F1359F887C39E15BDF17F8D34FF9AD7C45E2
            BB95D46F2CDB07E686358D2DE16193874883F3F78D007DBDA5EA6BAA5A433C61
            C473C6B22EE4646C119E55B054E08C82320F06AD53561546DC324F4E4E7FCF7F
            CE9D40051451400514514005647C40FF0091135BFF00AF09FF00F45B56BD607C
            56D45348F85FE23BB949115AE99732B9C670AB1313FA0A8A8FDD6746122E55E0
            96EDAFCCFE501BF8BF0FE42911B6B027181ED9A56395240CE4F3CE31C0ED4D07
            07A57E15267FB7E9DCFD94FF00836BBF6AB4F107C3AF14FC20D4654179E1C99B
            5DD2012034B6B33059D07FD7394A374FF96D9AFD48F358F20AE0FF00B26BF9CF
            FF0082266BF7BA2FFC14D7E18A5A5CCB6CB7D3DDDA4E11B02588D94E4A1F5195
            53CF7507B57F463E42FAB0FC4D7EA5C2B8A956C0A8CBEC371F968D7E67F981F4
            A1E18A393F1ACEBE1F6C542359AED26E5197DEE3CDEAD9F83FFF00071FAFFC6C
            16C7AF1E11B1FF00D1F735F0157DEFFF00071ADFC779FF00050B48D0EE6B3F0B
            584327B1325C38FD1857C115F039DBFF00850ADFE267F79782CADC0B957FD798
            7E403A8AFE8FBFE08B7FF28C6F84FF00F60FB9FF00D2DB8AFE70738C1C138AFE
            8E3FE08AB74B71FF0004C7F84E51964416376A5874CADF5C823F020D7B5C1AFF
            00DAE6BFBBFAA3F1BFA60AFF008C4F08FF00EA263FFA6AAFF91F54514515FA51
            FE748514514008F9DA71C9FCABF1EFFE0F54BD8A3FF82607C3FB732A09E4F8A5
            6122A672595749D5813F8175FCEBF611BEE9E09C57E1D7FC1EEDE2F96C7F667F
            817A00DE62D4FC4DA85F37036E6DED638C67DFFD24E3DA803F303FE0D8CF11AF
            87BFE0B8DF036694BF973CBAC5A909D58C9A25FC6A31E9B8A9FC2BFB01666236
            B00738C63AF6E7F3AFE397FE0DBEFF0094DA7C03E9FF00215BDEBFF60CBBAFEC
            6778C7DE200E4E47A751401FC767FC1C8577A7DEFF00C16CBE3C3E95676B656C
            353B08E48ADF011A74D32CD66738C0DCF3091DBB966627935FBF3FF06A5F83EF
            BC33FF000457F877797D71753C7AEEA7ACDFDAA4D2338B6846A13401101276A9
            6819F6AE0658B632493FCD77FC15CBE252FC5BFF0082A17C7FD79255B982E7C7
            DAC436F2A91892086F248626E38E6345AFEB43FE08BFF0BD7E117FC1283F67CD
            0C462290F8174CD4264C00525BB816EA4070073BE76F7F5CF5A00FC93FF83E27
            C68B71E20FD9CBC3AB200F696DE20D46540E092246D3A38C95EDFEAA4C1FAD7E
            08202CE001924F4F5AFD98FF0083D83C54D77FF0502F85DA21776161F0F62BE0
            A570ABE76A57C9907AE4FD9FF202BF1E7C17A18F13F8C34AD30BB44351BC8ADB
            7AF55DEE1723E99A00FEF23E1A694FA0FC32F0ED8BC2216B3D32DA068B90232B
            122951F4C7E95F823FB2AFFC1AA3E36F8BDFF053DF897E2AFDA05625F847A5F8
            A2EB58B336F7AAD71E3F13CEF3C6B9462F0438753396C396CC687932A7F41607
            9AA012083CE71CD39620AFB867278A00A3A078734FF06E8363A6697656DA6E99
            A5DBC76B696B6D188A0B686350891A22E02AAA28500600007A53B4FF0012596A
            B713436B776B7535B398E648A40ED03038218024839F5AB8FF002A12090179AF
            E3E3FE0AF3E3CF8A1FB087FC1723E39EB3E13F146BDE07F157FC25B36B9657DA
            35EBDBC925B5E05BBB7076101D0C3328646054E59581191401FD832485C8E833
            F8FE34FAFC3FFF0082257FC1D6167F1DFC43A37C2AFDA525D2F43F155F48969A
            3F8DA18D6DB4ED565621522BE8D7096D3331C099008989C32C5C16FDBA82EBCD
            2A38218751C83FFD6E68026A28A2800A0E4838245141381DE803F09BFE0F80F8
            82B63F06BE0078543B799AB6B3ABEAA5031DB8B682DA2048F5CDD903F1AFC07F
            80DF0BEE7E37FC71F06782EC8B8BCF17EBB65A241B786F32E6E1215C7BE5C57E
            B37FC1E95F19478BFF00E0A0BF0FBC1514C64B7F06782D2EA541FF002CAE2F2E
            A6671F8C50407FC8AF897FE083DF0CC7C57FF82C2FECF5A518FCD16DE2FB6D5C
            8C647FA0AB5EE7F0FB3E7F0A00FECDFC39A1DA785F42B1D334FB74B4B0D3E04B
            6B685061618D142AA01D80000ABD4C8C9E339C1E99A7D0007A1E719AFE683FE0
            F48FD9853E1E7EDADF0E7E29D95AA456BF11FC39269B7B228E66BED3A50A647F
            736D716A83DA1F6AFE979FEE9E9815F92DFF00078DFC0A8FE22FFC12D34BF17A
            421AF7E1E78BEC6F1A7DB92B6D731CB6922FB06965B627DD16803F96F4725803
            8207B03C57F4FF00FF000667FC7BD43E247FC137BC53E0CD42E1AE13E1CF8BA7
            B7D3C127FD1ECEEE18EE5631FF006F0D74DD7F8EBF981D8108243607515FD497
            FC19CFFB384DF09FFE097FA978E2F04827F8A5E29BBBFB619C27D92D02D92718
            EA668AE4E7A11B7F100FD67A28A2800AF3BFDAF7C7D3FC2BFD947E267896D661
            05DE81E16D4EFEDDF382258AD6474C7B96000F7AF44AF26FDBD7C391F8BBF623
            F8BBA74A6455B9F07EA801443230616923290A3963B80E0727A563886D52935D
            9FE47B1C3D4E94F35C342BFC0EA413F47257FC0FC6AFF825C7EC79E3E87E007C
            58F8FBA169574DA9F87FC2FA8E9FE0D2D1324F717B247B2E6F2DF23E730C0665
            52321A472A39461573F608F1AE85F0EBF616F88BE11D6AE34783C4FE20F12E99
            72DA4DEADA2CEF6242448F325F5BC96C61324B105591A23FBEDDE6C7B97760FF
            00C13BFF006D1F8A1E2FF8E9729A8F8A3527B2F0A7C33F10D9E916F691259D9E
            8D143A6BCF198A0855224224B787E6DB93B5724915DAFF00C13BB54F12FC6EF1
            4E9DE2FF008B5AE78624B18575AB3F0ADB7895E04BAF88FAD6A16D15A8B697CF
            0CB730466DEDD7CC75654758139E157F35C13A528D1F617BDA516DA56BBB734B
            C9EBA2F24B73FD10E2EA799C2AE67533DF67282742AC54252E64A1CF2A545271
            F7D73537294BDDE5739CFE08B64BE3AFD98757FF008280FECB7F07BC3DF0DB46
            F1911F0FADB59B086F2FB4AB6834CBFB891BED8CA648AEE53046763C50CDB648
            A57DA86446C81E01FF0004A39E5F877FF052FF00864BA8DD26817767AE3E9D3A
            DE2BC6CB3491C96C6DC800912333F9601E0161B88EDE89FF000566F1FF008F3E
            0B7C5BF0778317C4BE2FD0E4D0BC2F6525C69104169A569FA3CF3A79925A5AB6
            9D0DBC5710C67E512ECFBC1C020000797FFC128BC3FA878FFF00E0A47F09E1B5
            9A492F175E1A848F9E59208DA79B9046731C6DD73C5615E70FED0A51827CF194
            53ECED64AC8F7729C3631F02E638AC4D683C2D7A188A90514DB8AA9ED67294AA
            492535252525EE249DD45B8B47F4936F21691411D49F4C8AB15042A7CC0C4004
            E7D3353D7EAF73FCB9885145140C4719423079E383835F9DFF00F0572FF82063
            FF00C1563C4FFDA779FB40FC53F08DA448820F0E3F95A8F866D6441812C762AD
            0ED90FF13B48CC71D457E88919041E869A620C4125881C633C5007E1FF00843F
            E0C8FF0086163A0CF1F88BE3978F354D55976C33E9DA35A69F6EA40E4985CCCC
            C33E8E0FB9EB5F117FC148BFE0D33F8DBFB1A785751F17FC3CD66C7E32F82F4A
            81EEAFBEC769FD9FAD69F0A0DCCED68CEE26503BC3233F0498D54123FA9DF287
            382C33EF4D9604F2986D183C6074FF003FCE803F80A8CEC60C08C8AFEE1FFE09
            9DE11D33C15FF04EBF815A6E91636DA758C5E01D11D6181022EE7B089DD8E3AB
            33B3312724B312724935FC7D7FC156FE0DE83FB3F7FC14A3E38F833C30D02787
            F41F19EA50584317DCB488CECEB067FE996EF2FEA95FD8A7FC13DDC8FD823E07
            000F1E00D04763FF0030D83F2A00F61F2948C100A8E831C0A508063031B78159
            1E37F883A17C34F0CDDEB7E22D6B48D0746B08FCDB9BFD4AF23B4B6B741D59E4
            9085503D4902BF30BF6E8FF83B7BF675FD97AEAE746F8790EA7F1BBC496EC519
            B4593EC5A2C4C382A6F6456F30F70608E6423F8C5007EAAD15FCDAF89FFE0F6D
            F8CF79AC349A27C1BF863616047CB05EDD5F5ECC39EF2249103C7FB02BD57E01
            7FC1EEB0CFABDBDA7C50F81524366D26D9B50F0AEB8269547FB169708A18E7D6
            E17F4C100FDF5A2B87FD9B7E3FE85FB53FC06F07FC47F0B8BDFF008477C6FA54
            1ACE9E2EE110DC2C1320741220660AE01008C9E7BD771400514514005799FEDA
            5AE0F0C7EC77F15F5225C0D3FC1FAB5CFCBF7BE4B295B8F7E2BD32BC1FFE0A85
            AD9F0FFF00C13C7E31DC0F33F79E17BCB6F90E09F353CAC7D3E7E7DAB0C54B96
            8CE5D93FC8F7B8570FEDF3AC1D0FE6AB4D7DF348FE665D4A6010724771823A7F
            4229B91DC903E99A7B152AD8604F7C9E7B7F9FC299C77CE3BE3AD7E1B13FDA85
            A23E9BFF0082395F45A57FC14B7E12CF316446D52683A64077B49D147E2CCB5F
            D200B8E06783F435F889FF0006E4FEC943E297ED2BABFC4ED56D9DB4DF87B6E6
            1B0665CA4BA85CA320209E0F970EF63DC192239EB9FDBD1028006071ED5FA770
            75194304E53DA526D7E0BF43FCD6FA58E7185C6F19430D45DE5428C213F29394
            A76F9466AFEB6E87E03FFC1C3636FF00C147B520727FE243A71E7FDC6AF86ABE
            DBFF008382F535D43FE0A4FE2188021AC748D3A03EE4DBAC9FCA4AF892BE1339
            77C7D67FDE67F72783F16B8232ABFF00CF8A6FEF8A61CF6241AFE89BFE084E80
            7FC12BFE169031FF002163FF00957BDAFE766BFA28FF0082147FCA2B7E16FF00
            DC5BFF004EF7B5ED706FFBECBFC2FF00389F8DFD2FFF00E48EC37FD84C3FF4D5
            63EB8A28A2BF4C3FCE20A28A28006E9DF9F4AFE7BFFE0F86F1E4577E2EFD9CBC
            2F1CCCB2D95A6BDAA5CC79E0ACCF61144C7E9E44C07E35FD081CE0E300D7F297
            FF0007787ED049F17FFE0AE97BE1DB6918C1F0CBC2DA6E8122A9CA79F287D41C
            8E7A85BD8D0FBC78ED401E71FF0006BBF86BFE123FF82E37C152F6FE7DBD8FF6
            D5DCB93C47B744BFD8DF84863FC6BFACDF8F9F15EC7E01FC0AF1A78EB533FF00
            12EF05E857DAEDD67FE795ADBBCEFF00F8EC66BF983FF833E7C027C61FF057B4
            D482AB1F0A782F56D572464A877B7B3E0E7839BA1DBA66BF643FE0E9AFDA907E
            CE3FF047BF1B585BDC88357F89B7969E0FB3C1C314998CD74319CE0DADBCE87B
            02E339CE2803F936927D47E2478E19A566BDD5F5EBD259B1F34D3CCFC938EA4B
            37EB5FDE37C32F055B7C37F871A07872C822D9F87F4EB7D36054185090C4B128
            1F82815FC5F7FC11A7F66CB9FDACFF00E0A89F047C176F1EE86E3C536BAA5FFC
            859459D931BDB907D330C0EA09E3730EBD2BFB5AC9DE380093D7BFD2803F959F
            F83C37C4FF00F0907FC15D52DB326345F0469566033EE03325CCF803B7FAFCE3
            DEBF3D3F63BD01FC57FB5BFC2DD2E3852E1F52F176956A227C6D90BDE44BB4E7
            B1CE2BEC2FF83A5FC4E3C43FF05BEF8C112346F1E97068966195B76EC68F64ED
            F4219D871E95F37FFC12C3C3EBE2AFF829BFECEDA73C52CD0DE7C4BF0EC732C6
            096F2FFB4EDF791F45C9CF6C5007F6FF00103B81C82071C0C77E7F0E9525317E
            F018200E9F975A79CE38C0A001B915FCB5FF00C1E51A469BA77FC1597C3F3D91
            8CDCEA3F0EF4CB8D40602E2617BA8C433819FF00531C3D72718ED803FA90BAB8
            8ED2DE4965748A2886F7763855039249EC00EF5FC647FC16FF00F6CBB6FF0082
            867FC1523E2378DBC37236A1E1E6BF8FC3FE1D680997EDB69668B6F1CF181C91
            70CAD3281CFEF80EB4015BFE08D1FF0004CAD6BFE0A9FF00B6D687E03517969E
            0ED30FF6B78BB54894AFD834D8D806456C616599B1147D70CC5B0551ABFB2EF0
            9F8634FF0001F86B4DD1B4AB74B3D2F48B48ACAD600C4F910C6811132C492154
            01924F7EF5F137FC1BE7FF0004B583FE0989FB09E9763ADD9A27C4DF1F08B5CF
            174CCA0496F2B27EE2C3D76DB46C548C90657998603003CDFF00E0E97FF8281F
            C46FD837F608D09BE195E6A3E1ED7BC7FE244D125F105A9292E9302432DC3889
            F3F24D298C2A920FEEC4D8C100800FD34494B30041CFD0FF009F5A7D7F313FF0
            4DEFF83BCFE327C01F1069FA27C78B61F177C14764326A514115A78874F41C6F
            475DB15CE1724ACA03B1FF0096A3BFF46DFB317ED47E05FDB1FE0AE87F10FE1B
            F886CBC4FE12F104464B5BCB7CA956070D1488D868E543956460194820806803
            D0286C1041E868AA3E29F115AF843C35A86AD7D22C365A65B49753BB1C044452
            CC7F206803F8E3FF008384BE399FDA07FE0B23F1E3554766B5D1F5FF00F84660
            51CAC634D863B16039E864B791BEAE4FB57B57FC1A37F0B9FE20FF00C1657C3B
            AB04320F04786B58D6D8EDC840F00B1DD9E839BD03F1AFCE5F8AFF00106F7E2D
            7C50F1278AF51667D43C4DAA5CEAD74CCDB8B4B3CAF2B927FDE735FB61FF0006
            41FC2C5D4FE3AFC7AF1B34685F41D0B4BD0E3939CE2F2E2799947B66C509FC28
            03FA2958C29246466968A280023231EB5F1FFF00C17D3E17AFC5AFF82387ED05
            A5324928B4F0B49AD61464E6C258AFB71E0F03ECD938EC0F4EB5F605790FFC14
            17C2E3C71FB057C6ED14C6251ABF8075DB2D84901FCCD3A74C71EB9A00FE1988
            1C6E27278FAFD7DBA57F6B3FF045AF8770FC2CFF00824DFECEDA44312C024F00
            E93A94B185DBB65BBB64BB933EE5E7627DF35FC52E48254E7702460739F6AFEE
            17FE0999E238FC55FF0004E4FD9FF5485488B51F86FE1E9D578F933A65B9DBF5
            1923F0A00F73A2B98F8ADF19BC27F02BC1377E25F1B789741F08F87AC5435C6A
            5AC5F47656B0E7A069242A013D00CE49200C9E2BF2F7F6AEFF0083C3BF66DF81
            FE21B9D1FC05A478C3E2DDE5A821AFB4E8134ED2598641559AE0895F91D56128
            47218D007EB4D43A844B3D94B1BA2C8922ED653D181E08E7D457E30FC11FF83D
            6BE0C78C3C45159F8EFE14F8FF00C156B349B05ED85D5BEB31423B3C8BFB9703
            D422B9F407A57EAB7ECC1FB617C34FDB5FE15DBF8CBE1678CB44F1A787EE30AD
            358C87CCB593AF953C4C0490483FB92AAB720E3D40D7A1F833F18EF35BFF0082
            52FEDCDF15343F0CE85A2DE4135A5F685A62F882C8EA10C3A5DF223472AA3304
            95C40CA9FBD5922397568DB240F36D37F6F0F88FA76B373ACFF6B59CDE289A25
            B6B7F104D6114BA9E936EA85160B1761B6C9002D8FB3AC6C371C1AFDB8FF0082
            A8FF00C129B46FF8285F86EC754D3EF61F0EFC41D06030586A5226F82EE02DBB
            ECF7007CC5412CCACBCA963C3038AFCA7F887FF0422FDA57C0379E5DBF82ECFC
            430332C62E74AD5ADA58C1638C9591D24DB93C9280019278AFCC734CA31D86AA
            E341370BB6ADD2FE9D4FF49FC33F15781F88B2BA75F3DA9469E3B9234EAFB671
            4E7C8AC9A94F494656E6E5BE8DD9AEA51FD967FE0A972FC18F81F75F0EBC7BF0
            F3C31F187C292DF4DA85AC3E2391A49F4F79706411B3A481033A9932003BD99B
            70CF1F78FF00C10CFF00665F861F173C43ADFED0BE1FF0B5D7842F6DB51B8D0B
            4BD0175292FAD3476FB346679A3964512319127D81492A837F249013E7FF00D8
            DBFE0DDBF88DE2BF8876379F184587853C276D31373A6DB6A515CEA77EA14950
            8D0F9912216DB925F7633800E08FD8AF825F03FC29FB3C7C3DD2FC29E0CD16DF
            41D074A8CADBDA45B9B6E4F2CCCC4B3B939259896249249AF6387F2DC5CA71AB
            8C8FBB0F8535EF5FA3EFA1F92F8EFE22F0A61F0988CB3842AB962316D3AD3A55
            24E8B8BBF345AE774DCA7A5DC237B369CACDA7D7AC61000090052D1457DB1FC6
            414514312012064D00148E76A939031EB4C339542CDB5428C9C9C01DFA9E3A57
            C51FF052EFF82F9FC01FF826425DE8FE27D7DBC59F10228C94F08F878A5D5FC6
            D8F945CBE7CBB553904F98C1F6F2A8F401F6C79A78F94F3CF4E82BE11FF82C77
            FC178FE187FC12BBE1CEA7A5A6A1A6F8B3E325DDA9FEC6F09DB4C246B59187EE
            EE2FCA9CC100C86DA48924C61060975FC26FDBFBFE0EA1FDA57F6C49B50D2FC1
            FA9C3F05BC19745923B1F0CCAC3549633FF3DB50204BBFB6E8042319183CE7F3
            5F58D72F7C45AADCDFEA377737F7D79234D3DC5C4AD2CB3C8C725D99892CC4F2
            493CD0068FC41F1FEAFF00143C7BADF8A35FBF9F54D7BC477D3EA5A8DDCC7325
            DDC4EE6496463C72CECC4FD6BEB5D3BFE0E17FDB1F47F861A278334DF8D9AAE8
            FE1DF0F69F0695A75BE9DA36996525ADBC31AC71A09A2B6594ED545192E4F1D7
            9AF8C77190807049EF9AB1A669371ACEA16F67670CD777B792AC304112969267
            63B555540C92490001D73401DAFC72FDA93E267ED3BAC2EA3F11BE2078CFC7B7
            711262975ED62E3503067FB82576D83D9702B8658CBC81554BB36028033B8FD0
            7BD7F405FF000493FF008342B49BEF0BE99E38FDA9E7D464D4AF556783C05A6D
            DFD9D2CD0AE40BFB98FE7690E73E540C9B768CC8D9641FB1BFB3BFFC13ABE047
            EC98901F871F08FE1FF846EADD762DF58E8902DFB0C630F7454CCFFF00027279
            A00FE447F65AFF00822BFED49FB63B5A4DE08F831E31974BBBC347ABEAD6A347
            D39D08FBCB7176638E418ED19627A004902BF4FF00F637FF00832A35CD4DAD75
            1F8F3F15ECF4CB71CCBA1F82E33713907F84DEDC4611180CE5560907A377AFE8
            53CA5C938E4F39A0C2A401C800631401C67ECF1F03340FD98FE07F847E1DF85A
            3BB8BC39E0AD2ADF47D396EA633CC20823089BDC8E5B0324F0327800715DAD34
            44030396E33DF8A7500145145000C481915F297FC16D3C40DA0FFC12FF00E2AC
            EA18992DEC2DC05386612EA36B191F931FC2BEAC7195239AF877FE0E09D6BFB2
            7FE09B3E2180ED63A8EAFA6DAF2D83C5C2CBD3BFFAAAF3B3795B0559FF00765F
            91F79E16E19D7E32CAA9F7C4517F25522DFE47E023391942436DC76E071D0524
            79F3171C1CF141624609C815DA7ECD9A8D8E91FB44F80AEF538E2974DB5F1169
            F2DD24A0146896E632E1B3C636839CF6AFC6A9C39A4A3DCFF60B1759D0C34EAC
            57338C5BB77B2BDBE67F435FF04A3FD94C7EC83FB14F847C37736C2DF5ED4A23
            AD6B791F31BBB801CA31EE63411C5FF6CABE91AAB6D3079576B065624E7D7DFF
            00CFBD5AAFDBF0D4234694694368A497C8FF0015B3DCEB119BE635F34C5BBD4A
            D394E5EB277B2F25B25D11FCF6FF00C17E33FF000F37F190EB8B0D33FF0048A2
            AF8C6BEC0FF82F16A725FF00FC1523E23C4CA816C61D2A142010483A65AC9CFB
            E5CFE0057C7F5F8F66CFFDB6B7F89FE67FAEBE14C1C782F294FF00E81A8BFBE9
            C5FE415FD0CFFC104F5492FBFE0981E0085950258DCEA90A100E483A8DCC993E
            F973F862BF9E607073806BFA10FF008201FF00CA327C1BEF7DA9FF00E96CD5ED
            F077FBEBFF000BFCD1F8C7D2EE29F05D06FA6261FF00A6EA9F68514515FA69FE
            6E0514514008DF74FB57F0A7FB667C7FBBFDAB3F6B3F891F122F2492697C6FE2
            3BFD5D379398A2967768A3E790A91EC5009E0281935FDD649F708CE09FC2BF84
            6FDAABE016A7FB2D7ED25E3CF871ACC37116A5E08D76F34697CD5DAD28866654
            97A0F95D02B820608208E08A00FD92FF0083227E13B6A9F19FE3D78EA58805D1
            B45D33428E46C8DFF6B9E799D476C0FB1A13E9915C47FC1E5FFB6747F157F6C2
            F04FC19D2EECC961F0B74A6D435640C40FED2D402385619C131DAA40C0E063ED
            2E3E9F5EFF00C1AE8FA0FEC19FF043CF895F1E3C692FD9345D4F59D53C4934CA
            A0492D858411DB24480FDE91AE21B9541DDA450064F3FCF37ED3BFB406BBFB56
            FED0FE34F897E269564D7BC73AC5CEB1780125223348CC224C924246A4228CF0
            AAA3B5007EC87FC1947FB251F11FC6CF8AFF001AEFEDC9B5F0CE990F8534A675
            0CAF7374C27B87538E1A38A185783F76E8E739E3FA2874E0904923A57E57FF00
            C1A31E2DF0A5C7FC13222F0EF857C3FE24825D1F579EEBC47E21BDB58ADEC359
            D66E096920B5C48D249F66B45B28DDDD154B11B73860BFAA521C46C48240E700
            649A00FE317FE0BF1E2E5F1AFF00C162FF00681BC59125583C53258E5576806D
            E18ADCAE0F71E563F0AABFF041BF0ABF8CBFE0B13FB3CD9A094B43E2FB6BEFDD
            E01C5BABDC1EBDB1173ED9AE0FFE0A9BE283E36FF82997ED0BAA79AF2C77BF11
            FC42F0B3801847FDA571B063D94015F4B7FC1ABDF0F7FE138FF82DA7C2BB8641
            25BF876D359D5265201181A5DD42A4F3C6249A33DF91401FD73A93B947181C75
            C1FCA9D2B6C8C9E303D7A505428C838C74CF415CCFC61F8B7A1FC0CF855E25F1
            9F89EFA2D37C39E13D2EE358D4AE98F105B411B49238FEF6154E0773C77A00FC
            AEFF0083AFFF00E0ACB2FEC8FF00B3141F047C17AA1B5F885F162D5C6A93DB4A
            566D1744CEC9482082B25CB068549CFEEC4E701B630FCB6FF83573FE09E10FED
            AFFF00051AB4F187882C7ED5E0AF82F145E24BB0D1830DCEA45C8D3E06F41E62
            493E0F045A953F7ABE30FF008283FED9FE22FF0082817ED85E39F8AFE257992E
            7C57A8B49696AEDBC6976483CBB6B55F41142A8A71F798331C924D7ED9FF00C1
            B9FF00B7D7ECA9FF0004B6FF0082674377F11FE2F784746F1F7C42D66E75CD63
            4FB449F53D4ACE246FB3DADBCB15AC523A62388CA030E3ED2D401FBB7E500A39
            63818CE706BCBFF6C0FD90BC01FB747C01D7BE1B7C47D0E2D73C33E2088074C8
            4B8B3997262B981F04C7346C772B0CF7043292A7F34FE3EFFC1E6DFB387C3F49
            E0F037847E23FC42BB4CF9537D921D22C26E7FE7A4CE6603EB07E15F08FED2DF
            F079D7C7DF8906E6D7E1BF80FC03F0DAC27198E7B9F375ED461ED912398E03F4
            6B76A00F8C3FE0B03FF047EF1FFF00C1247E3EBE85AEA4DAE78135C92493C2DE
            298E2DB6FAB420E7CA900E22B98C101E327D1972A41AF4CFF8379FFE0B0DA8FF
            00C12FFF006B2B6D2FC45A8CCDF077E20DCC565E26B376261D2A427645AA46BC
            ED78810242BF7E2DC086658CAFCE3FB597FC14BFF681FDBE6E62B6F8ABF13FC5
            BE35B5372B3C1A44B2AC3A6ADC7DD574B28152057C310196307E6201E4E7C5FC
            55E0DD5BC11AB3E9FACE99A96917D1A890DBDEDAC96F2853CAB6D700E08E871C
            D007F7BDA76A316A96D15C5BCB1CF6F70A248A58C8649108043020E181EA08E0
            8C7D6BC17FE0AC7E3D93E197FC1307F684D72191A1B9B2F879AE7D99C1C1499E
            C66488FE0ECB5F137FC1A71FF05267FDAF3F61C93E167893536BCF1BFC1531E9
            D119E4DD35E68AE0FD89F2796F276BDB9206156387392F5F4E7FC17E0E3FE08D
            BFB421C67FE29593FF0046C7401FC6387E80FDD04671C57F499FF064A7C3E1A7
            7EC55F183C562300EB5E368F4A2F8193F64B1865C7AE07DB4FE66BF9B00E4018
            001FE75FD55FFC19F1E125F0E7FC12192F150AB6BDE35D56F998A6D2E425BDBE
            73DF8800FC2803F53E91C90A48192286240C819C5737F16BE2F786FE04FC33D7
            7C65E2FD5ECF40F0CF86ACE4BFD4B50BA6DB15AC318E58F724F45500B3120004
            902803A2129E011863DBD2BCFBF6B1B9F2BF65AF8945CAA11E15D50927A7FC79
            CB93EBC57E09FEDC5FF079EF8F757F1A6A7A5FC01F01F87741F0CDB4AF15BEB5
            E298A5BDD47514CFCB3AC11C91C76E08E423F9BC10720F15F9FDFB4CFF00C1C0
            FF00B5E7ED5FA3DF695E25F8CDAFE9DA1EA08D0CDA6F87A1834481E26186899A
            D51259118641123B64120F071401F1CB2150412BC7A7B719F7FC2BF48FE1CFFC
            1D19FB46FC06FD8E7C11F07FE1DDBF827C296BE08D1A3D1E1F101D38EA1AACC9
            1F11902776B75DA9C60C2DD057E6D19D8E70719EB8A133290B81C0FF00EBD007
            A1FED19FB5E7C50FDAEFC5CDAEFC4EF1F78AFC73A9EE668E4D635296E52D831C
            9586363B224CFF00046AAA3B015E7665248242F1ED4E310E464FCA39FF0022B4
            AD7C0BAC5E688DA9C7A56A7269CAA5CDCADA48D08519DCC5C2EDC0C73CD00656
            F3E83D3A66BDBFF606FF0082857C4FFF008270FC7AB0F1F7C33D767D3AF21645
            D474E91D9F4FD72D94E4DB5D4408124646707EF21C3295600D788C91F97C1393
            8078208FD2923387072011DFA62803FAD5FF0082407FC1C87F0B3FE0A87E298F
            C09AB68D37C30F8A6D197B4D16EAFD6F2CB5A5452CC2CEE0221670A0B189D158
            0FBA640188FD1F8D5490A54824E7B8FF00F57FFAEBF832F84B77E28D37E29F86
            AE3C0E757FF84C6DF54B57D0C6991B35E9BEF313C8102AE59A532EDDA1412C71
            C76AFEE1FF0063DD67E20F893F663F00EA1F15B48B2D07E255CE876CDE25B1B4
            9D66860BDF2C79A015F9412DF3155DCA858A8671F3900F4A5815727924D39230
            9D093F5E6968A6D8AC365629192A324741EB5C97C61F8F5E0CFD9E3C112F89BC
            7FE2DF0CF82BC3F0308E4D435AD4A2B0B60E7A28925650589CE1472DC62BAD9C
            662618CE7E9CFE75FC827FC1C6DF15BE3C7C4EFF00828EF8BD7E34689E22F0AE
            93A65E4D6FE0AD22F726C60D2164D90CF6CCB98E4332A2BCB22162642CA48DA1
            4219FD167883FE0E1EFD8C3C312225D7C7EF0848CE481F6482EEF00C7A986170
            07D4F3DB35E4DF16BFE0EC9FD8C3E1BD9C8DA5F8D7C53E3BB88867ECFA07862F
            11E439FBAAD78B6F193FF02C7BD7F26230C48248EDF4FD2BD77F62CFD84FE28F
            FC140FE3358F81BE167856FF00C47AB4ECAD7738531D8E91093837175391B218
            8007963963F2A8662AA403F4B7FE0A9BFF00076A7C42FDA93C2F3F843E03693A
            BFC21F0C5E4662D435B9A746F10DEA9FF9671B444AD9A63BA3339ED228C83F93
            9E1BF869E33F8BF75737BA4787BC4DE27B891DA4B9B8B2B09EF5E4766C967645
            63B8939249C926BFA96FF8263FFC1AEBF00BF62CF0F69FABFC44D234EF8CFF00
            11590493DEEB96A25D1EC24C7296B64D98CA827224983B92372F97D07E9768FA
            058F85F4782C74CB3B5D3EC6CD04705B5B44B1430A8E8AAAB8007B0C5007F049
            E28F07EB1E0AD524B2D6F4AD4748BC43F3C17D6CF6F30FAAB8073F856749188C
            004156F439CFF2AFEAABFE0E8AFF00829EF843F639FD902E3E19C3A67877C4FF
            0013BE27DACB6BA658EA36515EAE8562D949F5168E4042B71E5C39C664CBE088
            994FF2AD33EF24E1413D401800D00313EF7AE6BF6E3FE0CF0FF8266697F1BBE2
            E788FF0068BF16D85BEA1A47C38BC1A3F85A09943C7FDB2D124B35C953C6EB78
            6587613D1E70C30D1835F88E84EEE066BFACEFF834DBE140F869FF000464F076
            A7E48826F1BEBBABEB7202A559C8BB6B2566FAA59A7E005007E95AC2A8C08C80
            06001D053AB94F897F1CBC1BF062C22BBF18F8B3C33E12B39F718E7D6B54834F
            8A40B8DC55A565071B973FEF0AF8D7F6A7FF0083967F642FD95A616B3FC4CB6F
            1EEA61F63D9F82A31AC941903719D585B719E9E6E783C6700807DEB457E50FFC
            4645FB247FD033E2FF00FE13F6BFFC9747FC4645FB249E0699F17FFF0009EB63
            FF00B77401FABD457E5F7C3DFF0083BCBF63BF1B6B49677FAAFC41F0A4523051
            75AAF869E48867B916AF3363F0CD7DFF00FB3AFED59F0E7F6B8F87F178ABE197
            8D3C39E37F0FCA76B5DE9578B3881F19F2E551F344FEA920561DC5007A1514C4
            90B3918E3F91A7D002498D8739AFCEEFF8395758FECEFD83FC396C8518DFF8D2
            D2320F5DA2CEF1C91FF02551CE7AFE5FA21367CB38CE47A57E60FF00C1CEDAF1
            B7FD9EFE1AE987C91F6CF10CF73839DFFBAB62BC738C7EFB9FC2BC7E2095B2FA
            AFCBF547EB3E04E1BDBF1F6590ED52FF00F80C652FD0FC5FA000C707183C1CF4
            A280483915F8FB3FD6E6B43F7A3FE084DFF05053FB527C083E05F135E197C79E
            0081622D2B6E9753D3B3B629F9EAD19C44FF00F006FE3AFBDC30FAD7F399FF00
            0451D7EF74AFF829A7C304B4BA9ED56F2E2F2DA7113902689ACA7251867E6525
            54E0E79507A818FE8B8853CEE515FAB70D63AA62706B9F57176BF7D13FD4FF00
            2CFE921C1185E1BE2F92C02B53C4C156E55B41CA528C92F2728B925D13B6C8FE
            777FE0BA9F37FC153FE291E847F64F18C7FCC22CABE47AFA9BFE0B577F36A1FF
            00053CF8ACF339775BBB28813FDD4D3ED9147E4A2BE59AFCDF3477C6557FDE97
            E6CFF45BC33838707E5507D30D417FE528057F41BFF04019437FC1337C1E8195
            9A3D435357C763F6C94FF222BF9F2AFDFAFF008378D8BFFC138B4B249E35DD40
            01D87CEA7FAD7B7C1EFF00DB9FF85FE87E2BF4B7A7CDC134E5DB114DFF00E495
            17EA7DCD451457E9E7F9B01451450024840439381EBE95F873FF0007557FC10F
            F57F8F293FED2FF09F469F51F14691669178DB46B388BDC6A96B0A6D8F508906
            4BCB0C616391472638D180CA36EFDC59480873C0AF963FE0ADDFF0534F0B7FC1
            2BBF643D5BE20EB91DB6A7E22BB63A7786744797E7D62FD958AAE01CF9318CBC
            AC31855C672E9900FC47FF0082F2FED4C3F62BFF00826BFC00FD85BC353ADAEB
            3A3785F4CD6BE252C2C418AE0C6B72B62D8E3F797724B72C3A8096E7277357E6
            4FEC23FB16F8BFFE0A0BFB54F843E14782A12755F13DD88A7BB910BC1A4DAAE5
            AE2EE503A47126E6C672C76A8F99D41E47E3BFC70F167ED3FF001ABC49E3CF18
            6A33EBBE2DF17EA325FEA372E803DC4F21FBAAA3EEAA8C22AAE02A850001815F
            D46FFC1B4DFF000475FF008771FECD0DE39F1B69CF6FF18BE28594536A71CEBB
            66D034EC87874FC755909DB24DDF7ED53FEA81600F7BF893F12BE1C7FC103FFE
            09C3E1D6B3F0378EBC43F0DBE1B5BDB697763C316969737D6C246C3EA374B35C
            400896E1B748EB921EE33B42E48F8FA4FF0083D37F65C923207807E3E027A6ED
            1749033DB246A448191D707A74AFD5CF8A7F0AF40F8CDF0C75FF0007F89B4CB7
            D63C37E26D3E7D2F52B09C7EEAEADE642924671D32AC464723AF5AFE343FE0B1
            BFF04D1D57FE094FFB6AEB5F0D2E7507D6BC3F776D1EB5E1AD4E440B2DEE9B33
            C891F98070258DE29626C603184B000301401F3F7C65F1D2FC54F8C1E2BF1428
            9A35F126B377AA959399104F3BC837633C8DFCE09FAD7EB7FF00C1957F099FC4
            7FF0500F899E31922125B7853C0EF60A4E7F7571797B6E508C71FEAEDA71CFF7
            BDABF1A518BB8030A474E2BFA01FF8324FE21F80B46D33E377859B578A1F899A
            E4D63AA0D32488A99B49B5464134721186DB3DDB2B2E72374679049001FA7FFB
            72FF00C1713F671FF8275FC5AB3F02FC55F19DEE8DE27BCD362D596CED346BBB
            FD96F23BA2166851954931BF04E7033DC57E517FC1C41FF0714FC24FDB17F618
            5F855F01BC4DACEAF73E30D5A1FF00849A79B4ABAD3921D3601E688019550B19
            671093B7236248A41DC31F3EFF00C1E2F2786A5FF82ACE9A3478EF935E8FC17A
            78D7B781E449379D72613193CE7C831838E3800721B3F94182E002411D08FEEF
            3FFEBFCE80186424F6C7A76A50E6560188EE7A57A3FECD1FB1F7C4EFDB23C791
            F867E17781FC49E38D69C8DF0E9766D2A5AA9380F3CA711C099FE3919547AD7E
            C3FEC13FF066078A7C56965AE7ED13E3B8BC2967201237863C2AD1DE6A3823EE
            CD78E1A08D81EA2249C11D1D7A800FC3FF000EF87B50F166B96DA6693657BA9E
            A77F2AC16D6B6B13CD717323101511132CCC4E300727EB5FA87FF04E8FF834EF
            F680FDAEE6B1D77E26A7FC292F04CCC2463AC5B9975FBB4EB88ECB2AD167A66E
            1A32B9C8470307FA24FD8A3FE096FF0001BFE09F1A22DA7C28F873A1786EFCC7
            E5DC6B2F19BBD62E81C7125E4BBA62A719D81820CF0A0715F40FD9D3716C6493
            9E79A00F943FE09EBFF045AFD9EBFE09B7A3599F007826CAEFC5B6D1049BC5BA
            D2A5F6BB3B11876598AE2DC302414B758D08EA09E6B5FF00E0AA1FF04BDF007F
            C1513F65ED6BC13E29D3ECADFC4515BC937867C44600D75A05F6D26395587CCD
            116C0922CE1D4B746DAC3E9A0B820E49C529018107A1A00FE55BFE0DB3F82BFB
            43FECFDFF05694D43C27F0EBC4BAC683E13BFBAF05FC48963F2EDACB4EB591F6
            4AB24D3BC685E19638AE046A4C8DE46021DC057EF9FF00C17674897C47FF0004
            80FDA1ED617895D3C1D75704B9DA02C4165619F5DA878F715F599882C64067C1
            FC48FF003FE735F22FFC1797C467C27FF047AFDA0EEB7C5199BC2571640C99DA
            05C3A418EBD4F9981EE47D2803F8C31B739048033C1F4FF3ED5FD72FFC1AABA1
            49A47FC1113E14CF2142BA9DF6B97098CE405D5EF22E7DF311FC315FC8D2B6D0
            32A0E3A9EF5FD7CFFC1AE849FF008217FC0D39CE7FB7B9E79FF8A8753FF3F8D0
            07DFEFF77B67DCE057E6D7FC1CCBFB23FED05FB717EC41A4780BE07E8B67AE5A
            3EB0353F1569DFDA71D9DF6A16D6EBBADE18965DB1C89E69F3594C8ADBE18B60
            7C9AFD26601860F4A62DBA2000018F7E73401FC2AFC79FD8D3E2DFECC778F07C
            46F865E39F03344FB4BEB3A1DC5944E49032B248811813D0AB1073C75AF3368B
            6A96009518E723BF4FD3B57F7ED344AF13A95560C30548E187A57E207FC1E8BF
            0FBC29E0CFD8CBE185DE97A0E87A5EB5AA78E7335CDAD8450CF731A69F721833
            AA82C0314E09EB401FCE28192071CD7DE5FF000434FF008223788FFE0AEDF18A
            FE5B9D51FC2FF0BFC1D2447C45AC2286BA99A40C52D2D1482AD330524B37CB1A
            E49C9DAADF0729C1CE335FD1DFFC191F893F65CF8E2D85561E29B21903191F64
            3D7D8751E9CE3193401FA67FB267FC1293F67AFD88BC2D65A7FC3BF851E10D26
            EAD22546D5EEAC52F757B823AB4B7928695892325430407EEA81815F9C1FF078
            17FC14D61F831FB3CE91FB3AF852FC47E29F88CB1EA5E2530C8049A7E911481A
            285B1CAB5CCE9C63FE59DBC808C48A6BF533F6E4FDB2BC21FB027ECC1E2DF8AB
            E36B98E1D1BC2F66648EDFCC092EA572DF2C1691673992572AA300E0658F0A71
            FC59FED97FB55F8B7F6DFF00DA63C63F153C6D76D75E20F175FB5DCA809F2ACE
            21858ADA30DC88E28C246A393841924E4900F31DFBB8C003FCFF00853E2B6779
            008D5A4624050A09249E9F9D468BBDC0C139AFDF2FF835BBFE08323C40743FDA
            77E31E8C4D844C2F3C01A05EC18FB4B67E4D5E653FC239F215873812F4F2CB00
            7BB7FC1B57FF0006FCA7EC8DE18D2FE3AFC68D0E3FF85A9ABC026F0F68779103
            2783EDDC1C4D203D2F6446E9D6053B4E1CB08FF647CA1BC37248CD0910462467
            269D4005145140011918E45713F1CBF66EF00FED37E0697C33F117C1FE1CF1C7
            87E67121B0D6F4F8AF605719C3AAC8A7638CF0CB861EB5DB51401F06BFFC1B23
            FB0E3EB4750FF851768B7064F376AF89F5B1006CE7887ED9E585FF00642E3DAB
            EBAF80DFB337C3DFD973C050F85FE1CF82FC37E08F0FC2DE60B1D1AC23B489DF
            BC8FB002EE7BBB12C7D6BB8A4918AA120648E94009B02720B1C7BE6BE75FF829
            CFFC149FC0BFF04BFF00D97756F887E34B88EE2ECE6CF40D1A372B73AFEA0559
            A3B68F83B47CBB9E42308A093C95077BF6F5FDBEFE1E7FC13A3F673D57E24FC4
            7D563B2D32C7F7565651307BCD6AE981315ADB21C6F91C8EA70AAA19D885526B
            F908FF0082A3FF00C14D7C7DFF00054EFDA62EFC7FE359458D85BA35A7877408
            242D67A0596ECAC499C6E91B8692520348C070A8115403CEFF006C4FDADFC6FF
            00B747ED15E26F89DF10B526D4BC4DE27BB32CBB188B7B1887CB15B40849D90C
            481515724E172492C58F97907CA249017B7B9AFB0FFE097FFF00044AF8DDFF00
            054DF16412F83F4693C3FE02B7B8D9A878CB578DE2D2ED957EFAC3C6EB998630
            12207071BDA31F357D73FF00070E7FC123BE107FC1237F624F833E1AF05C773A
            CF8E3C55E21BB9F5BF136A6A0DF6AA96D6A8A5230BF25BC0AF383E52727285D9
            D941A00FC814E580C139F4EA6BFB64FF008239FC2FFF008539FF0004ACFD9F74
            2685A19E3F0269579709DD67B9B65B9941F7F3267CFD6BF8A9F0AF87EEBC5BE2
            7D374AB252F79A9DD456B0281925DDC2A8FCC8AFEF57C11E13B4F03783F49D06
            CD3659E8B650E9F00E07EEE28D51471ECA074A00FC37FF0083B8BFE09CDF1C3F
            6B2F8F7F09BC5FF0BFC13E2AF887A159E8173A45D59687652DEBE977097065F3
            5D133B44B1CA8A0E39FB39AFC74D77FE08FBFB56786E2492E7F671F8D8F1C992
            1ADBC1DA85CEC03A93E544D8E3D6BFB691105248CE4D285C7724D007F07FE3FF
            00D993E24FC27467F157807C6FE1A441966D5743BAB20BEB9F351715C498C8CE
            77B01C1CE473FF00EAAFEFD4C0AD1852A19718C10315E4BF18BF604F81BFB423
            4AFE39F83DF0CBC5B3CDCB5C6ABE1AB3BAB80718C891E32EA71DC106803F863E
            4F0327771D70335EC7FB0EFEDEBF13BFE09E1F1BB4FF001E7C2FF125D68BAA5A
            C882F2CF73358EB3006C9B6BA8410B2C4DC8E7E653CA956008FE9AFF00687FF8
            34F3F63AF8DB1CF3691E13F13FC36D427258DC78675D9B6163D3F7377F688954
            7A222F1E9D6BF3EBF69AFF0083277C77E1F9DAEBE107C62F0C789AD8B7CB61E2
            AB197499E319E144F009D2538EE5231401FB2BFF0004A4FF00829BF82BFE0AA7
            FB2C69BF10BC2EA34AD62DDBEC3E23D0249965B8D0AF40C98C91F7A271F3C526
            06F4238560CABF4D57C61FF0443FF824E689FF0004A0FD946DFC3D25BE9D75F1
            23C51E5DEF8D359B595E54BFB94DFE543133AA9F220572AA368C97763966627E
            CFA00490663619C57E47FF00C1D1BAD848BE0AE98AE84B1D66E644C7CC3FE3C5
            50E7D3EFFE55FADF3E7CA603826BF183FE0E79D785C7C76F863A5976CD9E8573
            77B31C0F36E36E7F1F28FE55F3FC512B65B3F3B7E68FDE3E8D186F6BE226065F
            CAAABFFCA535FA9F98142804804803F2A0027381934F4849620838248E9EF835
            F9349D8FF542FA9F58FF00C10DB445D6BFE0A8FF000BE39239248A16D4AE18AF
            44D9A65D95627D3785FCEBFA2AF287B9AFE7FF00FE0DF2D2BFB53FE0A57E1D9D
            599069DA36A53100160C4C063DA7A63064CE7D80EF5FD0157E9BC1D1B60A4FBC
            9FE48FF36FE97188F69C65422BECE1A0BEFA955FEA7F381FF05A050BFF000537
            F8B19C926FADB07B7FC795BD7CBD5F467FC15BEE249FFE0A41F177CC72E575C6
            504F5C08D001F80007E15F39D7E7D983BE2AA3FEF3FCCFEF5F0FA0E1C2F96C1F
            4C3D15FF0094E215FBF3FF0006F07FCA3834BFFB0F6A1FFA1AD7E030E481EB5F
            BDFF00F06E9DECB71FF04EF8229223125B7893508E363FF2D46226DC3F1623F0
            AF7B841FFB7DBFBAFF0043F13FA59C6FC0F1FF00AFF4FF00299F78D14515FA79
            FE69050738A4918AA123191D2AAEA3ABC3A3D9CF75793C169676C8669A699C46
            90A28259998F014019249000CD0043E23F11D9F857C3F7DA9EA7756F61A6E9B6
            F25DDD5D4EE2286DE28D4B3C8EC7EEA2A82493C000D7F1D3FF0005D4FF0082A6
            6A1FF054FF00DB6B56F1159DDDC2FC37F09B4BA3F82ECA4531ECB30E37DDBA1E
            92DCBA891B23217CB43C462BED4FF838FF00FE0E268FF6A67D5BE037C0BD6037
            C37825F23C4FE26B4988FF0084AA453CDA5B329E6C948C33FF00CB76C6DFDD0C
            CBF33FFC1227FE0DF2F8C1FF00050AF8D3E18D43C5FE13F14781FE0C34BF6CD5
            BC45A8DAB58C9A85AAFCDE4D92CA034CF2E7689154C681998962BB4807D33FF0
            6A7FFC1159BF68AF89567FB497C4BD2449E02F085E9FF8442C2EA20535FD5223
            CDD9047CD05B3F4ECF3A8E4F92EA7FA505842B9604E4FE35CFFC2BF85FE1FF00
            82FF000FB45F09F85349B1D07C35E1CB38F4FD374FB3409059C11A8548D475C0
            03A924924924935D1500248372100907D7D3DEBF283FE0EBAFF825E5F7EDA9FB
            1D587C4DF0569726A1E3DF839E7DD4B6B6D1EE9F54D1A400DD44AA3977859166
            51CFCAB3000B38AFD602334C78D4C6411B8631C806803F80A9231100412491C7
            BFF9FE95F7A7FC1B29F11AE7C03FF05B3F82ED14A22B6D625D4F4ABA40E22599
            26D2EEC286383902511B81DCA01C57E88FFC1723FE0D59BCF1AF8975BF8B7FB3
            0D8DA1B9D46596FB59F002BA428F21CB492E984E146482C6D988C1244671B62A
            F96FFE0D8CFF00824D7C46F8B7FF00051A8FE216BF637FE08D1BF67CD5A39759
            B6D5ACA5B7BE9F52789FCAB111385656507CC93772ABB0119914800FD50FF838
            BBFE083527FC150BC1BA7FC44F87324367F19BC19A7FD861B6B990476BE28B05
            77916D1DCFFAB9E36791A29090A7CC647E0ABC7F187FC1027FE0D89D03E2B784
            B5DF881FB53784FC516D7DA56B93693A4F82AF0CDA6C6EB6E312DD5D15DB24B1
            BCAC04423754658598991240A3FA1111ABB00411D7D88CFD3A53C44030396247
            BF5A00E5BE0F7C0AF067ECF7E06B5F0CF813C2BE1FF07787ACFF00D4E9DA369F
            1595B2718CEC8D402C7BB1C927A935D4F9233D5BF3EA7D69D45002040BD38A5A
            28A0028A4762AA4819C546256E33B413CE3AFE1FCE8025600820E706BF2C3FE0
            EF0FDA4ACFE0EFFC126EFF00C1A6EA35D5FE2AEBF61A4436E1C091E0B6996FA6
            940EA514DBC519F79D7D6BF40FF6A3FDB07E1A7EC5FF000C6F3C5FF147C69A17
            83341B5477135FCE04B72547FAB8215CC93C9C8C244ACC73D2BF92EFF82EE7FC
            15AEF7FE0ACFFB5B7FC241A7DBDF695F0E3C1F0BE97E11D3AE0012F92CFBA5BB
            9802409A7655C8538548A35E4866201F112BE08E0002BFAE2FF8354350B8BDFF
            008225FC2E8A690BC767A86B9044A707CB5FED6BB7C7D37331AFE471704F3C0A
            FEBDBFE0D70D01744FF821F7C1897CA9219B507D6EE640C31BF3ADDF853F428A
            87F1A00FD05A28A28011C12A474FC335F863FF0007BE6B496FFB3F7C04D39918
            C979E21D52E5587014456D0291F52651F957EE7390179C63F2AFC0BFF83E4358
            9A0D0BF667D3D590DBDC4FE269DC639DD1AE92ABCFFDB56CFE1EF900FE7E5002
            D83C66BFA1AFF832CFE25695E0CFD997F68E7D66F74FD234AF0F6ABA6EAF7DA8
            5E5DA4505B40D6B73B9E46380888B012598E304F4C73FCF20241AF42F87FFB53
            78E7E15FC0BF1DFC38F0F6B971A5784BE25CFA74FE24B483E53A98B1370D6F1B
            B75F2C35CBB320E18AA673B6803ED6FF008386FF00E0B4D79FF054FF00DA0E1D
            0BC25717769F063C0171247A05BB831B6B573CA49A9CAB8055997E58D1B98E3C
            9F95A475AFCEA129932AC7018E4FF4FE748D2B36724734D0C54823822803F523
            FE0DBAFF00821D4BFF00051DF8D8BF127E2169932FC12F025E813C532155F15E
            A0986162BC7302021A67E0E0AC63990B47FD5569BA65B6876105A59DBC56B6B6
            91AC30C512858E28D461555474007000E8057F1D3FB357FC1C49FB59FEC95F08
            B44F017823E20E8BA6783FC37682CF4BD33FE10FD1CC76680962C185B0777662
            599E466666259896249E927FF83A3FF6E99A5761F1BD2356390ABE0CD0084F61
            9B1271F526803FAFADE707A123F5A0392C070413F957F1E32FFC1CC1FB704DAD
            1D40FC76D484E483B57C3BA3AC3D31FEA85A6CFF00C76BD8BE067FC1DFDFB5D7
            C32BC887896E7E1FFC48B60DFBC1AC787D2CE62B8E42BD9340AA7BE4A37D2803
            FAAEA2BF1FBF624FF83C67E057C74BCB4D23E2E786F5CF83BAB4FB53FB415DB5
            AD14B74CB4B122CF165B03E684AAE797C026BF57FE1AFC58F0DFC66F02E9FE27
            F086BFA278A7C3BAB4426B2D4B49BD8EF2D2ED7D52542558678C83D78EB401D1
            5151898819619C1C1E318A6CD7AB023BB9091C6ACCEEC400A07527DBAFE46802
            591F62127A0AF95BFE0A95FF000575F857FF0004A8F83B26BBE39BF8F51F13EA
            313FF607852CAE146A5AD4801008073E5401B01E760553A00CDB55BE29FF0082
            C2FF00C1D5DE03FD93EDB56F00FC039348F895F12D375B4FAE093CDF0F787E4E
            8C43A9FF004C997FBA8444A7969095311FCE7FD88BFE0835FB507FC16BFE2E1F
            8C5F1DBC43AFF84BC2DE25916EEEFC4BE238D9F58D661EAAB6368DB42C446023
            30485130515C00A403E4BFDAF3F6C2F8F3FF0005C3FDB0AD6FAF74FD5FC5BE25
            D4E5367E1BF08E816B34F6DA45B1F98C56F10C9000F9A599F96DBB99B68F97F5
            C3FE0925FF000685E99E0E9F4AF1CFED4B750EB9A94645CDBF8134DB826C606E
            0817F70B83391D4C311119230CF22EE43FAABFF04FBFF825F7C18FF8268FC384
            F0FF00C2BF0A5BD85D5C44B1EA7AF5E6DB9D6758200C9B8B923715CA82224DB1
            29FBA8BCD7D0A9184391D4D0066784BC11A37C3CF0A58687E1FD274CD0F46D2A
            15B6B1B0B0B54B5B5B48D7858E38A301514760A0015FCECFFC1EEFF147FB57F6
            97F819E09122B0F0F786350D6F6E3E65FB75DA419CFA1FECEE9EC6BFA3A90ED5
            2704E2BF997FF83D67C17A8D97FC1443E18788E6B775D2755F8730E996D3E0ED
            927B6D4F50926507182556EE02476DE3DA803F3B7FE0941F0D07C61FF829BFC0
            0F0E491996DB51F1FE8C6E940C96B78EF62926EC7FE59A3F518AFEDE23206D18
            C71C0E98F6AFE4BFFE0D4AFD9A2FFE397FC160FC19AF476734FA2FC33D3AFF00
            C49A94A63CC51936CF696E0B1E371B8B84603A911311F7491FD6891B141CB123
            F1CD003A8A6F998C67BFEBF857C71FF0544FF82E47C12FF8256F87961F176A92
            7897C7174C16D3C23A1CB14BA990467CE9C1602DA1C7469082DFC0AF83800FB2
            68AF98BFE09AFF00F056DF83BFF054CF86336BBF0DF5B78B58D3154EB3E1BD49
            561D5B4524E019235621E227EECD1B3467A6430651F4CC72B3B0076839391DE8
            024232319229BE48CB724EEEBC0E69D450035620AD904E3D38029D4514008F9D
            A71D6BF0BFFE0E58D68DF7EDD1E19B34919A3B0F04DA8643D15DAF6F5BF552B5
            FBA120DC8471CD7F3FDFF0707EB6356FF82906B501690B695A2E9D6DF30C004C
            3E6E07B7EF735F2FC5F2B602DDE4BF53FA57E8A386F6BC74A7FC946A3FC631FF
            00DB8F8840C90319CFE15F49FEC3FE35FD9FED7E1E7C44F0DFC68D0B57FED0D7
            AC0CDA2F88AD242EFA64B0A3BAC4A8AA4C7248F81BC8756E015039AF9B031539
            04834120AE08FBA0807B8E2BF34C3D774AA2A8927BE8F55A9FE8C710E470CDB0
            72C1D4A93A77717CD4E4E324E3252566BA5D6A9E8D68F73F4A3FE0D99F05B6AD
            FB5FF8E75F742D1E8DE166B519E4A49717501073EBB6071F89AFDB8AFC91FF00
            835BEDEC9D7E354E371D455B4656CE30233F6F3C77E5B767E8BF8FEB757EA3C2
            D4F972E83EEDBFC59FE677D2671D3C478838C84BFE5DC69457A7B38CBF3933F9
            A8FF0082B390FF00F051CF8BCC0823FB7E41C1C8FB8BFD735F3B57BA7FC14D38
            FF008281FC645E4EDF16EA0324E490276007E42BC2EBF33C77FBCD4FF13FCD9F
            E92F044393877011ED4697FE9B880CE46339F6AFE833FE0805E1F3A37FC133FC
            1F7010AA6A9A86A774A739071792C271ED98ABF9F44C96000273E9DBDFF0EB5F
            BAFF00F0423FDB5BE1CF8AFF00652F077C27B3D66D34CF1BF8622BA5974ABBC4
            2F7C24B99EE0C96E492251B64C90A770C1254015EFF084E9C71AF9DA4DC5DAE7
            E0FF004B2C263311C1D4D61694A718D68CA6E29BE58A854D656D97338DDECBA9
            FA114542B72C240AEA17774C7352863BB040C7AFAD7E9E7F9AA983AEE420F435
            F9D3FF000718FEC5DFB44FEDEFFB33F843E1D7C07BCB3874FD4B5B27C5F6B3EA
            834E37569E5A8877B92375BABEF678C025884201C153FA2E40604100834DF257
            1820303D7207340CFCC3FF00823B7FC1B3FF000C3FE09E30D8F8BFE2245A37C5
            4F8B8A5664BF9ED8C9A47879C720594120C193273F68957782A3CB58B2D9FD3B
            308285724034A2150CA79F97A0ED4EA006AC613A13FA7E54EA28A002861B9482
            48CFA7068A2801A6107392493DFBD352D238CCA55154CC773903058E3193EF80
            067D87A54945003444030396E33DF8A75145001451450014514500637C42F0AC
            BE36F05EA3A55BEB1AB787EE2F22DB0EA5A63AA5DD8C80865963DEAC84AB0076
            BAB230CAB2B292A7F9CCFF0082CFFF00C147BFE0A3BFF04D2F8C971E02F15FC5
            655F086BFE6CBE1CF16E8DE16D36D175DB50464090405A0B94CAF991AB074241
            5631BA337F49846463915E45FB6DFEC47F0F3F6FFF00D9E35BF86BF127454D57
            40D5D43C72A90975A65C28223BAB79083E5CB1E49047041652195994807F11DF
            18BE3AF8DBF682F17CBE21F1E78C3C4BE34D767E1AFF005CD4E6BFB865CF4DF2
            B3301ED9C0AE524B869170718273F5AFB03FE0ADBFF0466F8A1FF049BF8AAD65
            E27B67D77C03ABDCB2787BC5B6709FB1EA0BC958A6EBE45D04193131C36D728C
            EAA4D7C80D0AA83F31257AF18A0062F2C0640CD7F6C1FF000467F83937C01FF8
            2577C02F0BDD4325ADF5BF832C6F6EEDE4043DB4F7518BB96361D99249D94FB8
            AFE51BFE08E7FF0004EFD5BFE0A57FB7B782FE1F5ADADC3F86ADAE5758F165D8
            8F29A7E9303AB4E58F38694ED81320FCF3212319C7F697691C7670450C091C50
            C48112351855000000F6006062802CD248C550904023B9E9597E33F1C68FF0EF
            C25A9EBDAFEABA7689A268D6EF777DA85F5C25BDB59428A59E49647215154024
            9620002BF10BFE0A9DFF000786687E04FED3F077ECC3A45BF89B548CBDBCBE36
            D6ADD974C858100B59DA9C3DC1C124492EC40403E5CAA73401FB25FB477ED41E
            02FD923E14EA5E36F891E2BD17C1DE19D310B4B7BA84DB03B63E58E34FBF2CAD
            D04680BB1200049AFE49FF00E0BCFF00F056EB8FF82B4FED6D1EBBA4DBDDE97F
            0DBC176EFA5F84B4FB85C4CD1B3033DE4A3A2C93BAA9DA38548E153965663F32
            7ED3DFB607C4EFDB3FE22CDE2CF8A5E36D7BC6DAECA4EC9B51B82F1DAA939F2E
            088623823CFF00044AABED5E70F3338C1C11F4C9EDDFF0A006D14AA3270735DC
            FC0FFD99BE217ED33E271A2FC3AF0478B3C75AA92A1AD342D2A7BF96207382E2
            356D8B856393C00A49E013401C3282CC0609A77959C60E4E7047715FA8DFB2C7
            FC1A2FFB56FC7692DAEFC6169E12F849A3C84348DAF6A6B777CC87BA5BDA79BF
            37FB32C911FC78AFD27FD94BFE0CCFF805F0BFC8B9F8A7E30F1A7C54D422C6FB
            580AE85A5C83A9063899EE3AF713AFD39A00FE652D6CE4BEBA8E0811E69A6711
            C71A2966762700003A927B0AFA1FE18FFC1223F6A2F8C9690DCF877E007C5ABD
            B2B85DD0DDCBE1ABAB5B6986DDD95966444231DC1F6EB5FD85FECC9FF04F1F81
            BFB1A58C30FC2FF857E09F06CD0C7E57DB6C74B8CEA122FA4976E1A793EAEEC6
            BD9360F5241FC6803F897F899FF0475FDA9FE1058CF75AFF00ECFDF162DACED9
            37CD736FE1CB9BD82118EAF240AEAA3DC9AF9D6F34BB8D2AF66B7BA865B6B981
            8C72C52A1492361D4153C83FCABFBF17895D58103E6F6CD7807EDB7FF04B8F81
            1FF050AF0D4F65F14FE1DE87AF5FBC5E541AD4517D9758B3FEE98EEE3C4A029C
            1D858A1C60A9190403F888618F9B00E7D483CD7D1DFF0004E3FF0082A9FC60FF
            0082627C5983C41F0DFC433C5A4DCCE8FACF876E9DA5D2B5C4046566889C2BE3
            812A6D75E81B1907CCBF6BAF879A0FC21FDAABE26F84BC2B777B7FE17F0B78AF
            55D1F47BABC7492E6E6CEDEF258A0791955559CC68A4B2A80493800715E769F7
            867A5007F707FF0004E2FDBF3C15FF00052DFD953C3FF157C0ED2DBD96A9BAD7
            50D36670F73A2DF458F3AD25C606E52C0AB0037C6C8E30180AF15FF82F77EC81
            F177F6EAFD8974FF00861F06B526D2F5EF10789ACD758B993566D36D63D24457
            1E7FDA0A9DF2445FCACA2AB9638E0D7C0BFF00063FEA1AEDC7C2EFDA1ED2E4CC
            3C3706ABA1CBA792A447F6B686F56E71DB77969699EF8DBDB15FBB42203A1603
            AE33C5007E6A7FC12ABFE0D93F823FF04FA7D33C51E2EB783E2E7C4EB42B709A
            AEAF68BFD99A54E0020D9D9B1650CA7959A42EE08DCBE59E2BF4ADD55016C018
            EA7DBBD0912C6C4AF19EDC57CADFF05BFD73E237857FE0949F1AF58F84FAD6B1
            E1DF1D689A226A567A8E944ADEDB5BC1730CD786223956368970BB97E65DD95E
            40A00FA6B57F10587866D05D6A57D6B616C485F32E665893383C65C8038FC6B8
            3F11FEDA5F07BC1E01D5BE2C7C34D33E62A7ED7E26B28064751F34A3A57F0F1F
            11FE2BF8B7E2EEAEDA8F8B7C4FE22F14EA4C49FB4EAFA8CB7B31279277CACCC7
            3C1F7EBDAB9C25B6E09C2F242E78CFAFA5007F6C7E2AFF0082C5FECA3E148C8B
            DFDA33E0AC8086252D3C5F6378C31D411148D83EC7AD7C8FFF000513FF00829D
            FF00C1333F6BEF8530E8DF19BC73E13F88B63A497B9D3A1D36CF529B51B591F0
            ADF679ED515E366C267F7815B60DD902BF970F87DF0B7C4FF1635E5D2BC29E1D
            D7BC4DAA49F72CF49D3E5BD9DB3FF4CE35663F957D2DF0A3FE084FFB5FFC69D4
            EDEDB49FD9F7E2458B5D1F965D734C6D1214193CB3DE794A3819EBCF6C920500
            7E8BFECF7FF07247EC93FF0004BC82FBC31FB327ECC7E2C97C3DAD5CF9DACEAF
            ACEBEB63A95FB20611B12E2EE49517710A8CF185DCC4282CD9EE7E3D7FC1EE96
            C745B58BE187C0E9CEA12AE6E27F146B004309C11B523B7197E7077175E33C0E
            A380FD8DBFE0CB0F1E78AE5B4D47E39FC4AD1BC21644879347F0BC6752D41C77
            46B9902C3130EB9459871F88FD3AFD9BFF00E0D9EFD8E7F671D3E2D9F0AEDFC7
            5A946A51F51F17DE49AB4B30F530B6DB507FDD845007E12FED77FF0007567ED6
            7FB51F87EEB46D335FF0F7C29D26EC14947832C64B4BC9908C60DD4D24B346DD
            F742D19F7ED5F9C5ACEBF7BE22D5AEB50D42EEE2FAFEF6569AE2E6E2469669E4
            63967776259989E492739AFD2EFF0083A33E217C09FF0086D9D2BE197C0AF007
            C39F07D9FC31B39ECFC4D7FE13D12D74B8B51D5277467B693ECE8A928B548917
            71195925990F295F9922204124903F21401E85FB2CFED53E3AFD8D3E39E83F11
            7E1DEBD75E1EF15787E7F360BA8892B329E1E1950F1244EB95643C303EB823FB
            1AFF0082477FC146F44FF82A47EC59E1CF8A1A65BC5A66B0D23E97E23D2A372E
            BA4EA70AA9961527931B2BA4B1E727CB9933C8207F2F1FF04A1FF82177C62FF8
            2A878AE0BDD0ECA4F08FC36B69B66A1E32D52D9BEC4847DE8AD9383753F41B10
            ED191BD93807FA9AFF0082657FC135FC01FF0004B4FD9BA0F86FE007D52FAD27
            BD9356D4F53D4E457BCD52F64444799F6AAAA8D91C68A8ABF2AA004B1CB100FA
            2A8A28A0028A28A00493EE1AFE743FE0B7FAA8D5FF00E0A83F149D7798E0974E
            B74CB642F97A65AA103D3907F1CD7F45D3922224751CD7F33DFF000545F1147E
            2AFF008283FC5FBB8D91D13C4B756DB95F78630B7907E8331D7C7F19CED84847
            BCBF43FAD3E87D8573E29C657FE5C3B5FF008154A6FF00F6D3C0A8520104E703
            AD14024648C71ED9AFCDD1FE8A376D4FD3AFF83623C5E74FFDA47E23F87CB281
            AA786E2D43192371B7B958F3F87DA4FE75FB4D5F815FF06F078A5FC35FF0520D
            3EC9482BAEE81A969EC79C10A91DC76EF9B71FAFE1FBEB5FA8F08D4E6CBD2ECD
            AFD7F53FCC5FA53E03EAFC7952AFFCFDA54A5F8387FED963F995FF00829CC6D0
            FF00C141BE322BA9573E2CBF639F4699981FC88AF09AFA2FFE0AD71987FE0A37
            F174152A5B5E738C63831A303F8835F3A609E06013EBD2BF37C73B626A7F89FE
            6CFF0044B81EA73F0E65F3EF4293FBE9C43B83807156B48D6EF340D4EDEFAC2E
            EE6CAF6D1C4B04F04AD1CB0BA9CABAB020AB020608E9815B1F0A3E196A9F19BE
            26787FC27A1C2D73AB789350874EB48C027324AE10671D86724F400135FAA5E3
            4FF8362B4FB7F86D747C3DF14AF6EFC5D180F6E6FF004C5874E9BEF651823348
            99E3E705B18FBA7231D181CAB158B8CA7878DF97E5F7799E271AF8A1C31C2D5A
            8E173EC42A72AE9D972CA4B96E9372E54D28DDDB5DF5F33CC7FE0955FF000555
            F8F7F193F6D3F86FF0FF00C53E3E9F5CF0B6AB34D6D756F71A659F9D32A5A4CE
            A5A75884CCC1914EE2E49C7390483FB6E839FD6BF037FE09F9FB21FC43FD8FBF
            E0AD5F0AB44F1FF86AFF00459DAFEEBECD7457CCB2D417EC371F3C13AE5241DF
            00EE1FC414F15FBE484870322BF40E16A95E5869AC437CCA56D77D91FC13F49B
            C164543883075787A9D2850AB878CEF4541424DD4A8B9BDCD1B7649BDDDB7D07
            D23B6C524F414B4921C293C715F4E7F380C5B8DCC00C10C3208E41A72B12DD00
            1FAD7E177C4FF88FFB5DFED45FF071A7C5CF80BE07FDA5B58F855A1784F495D4
            EC4C5A5C3A958D9D835958DCC512D93ED8E4999EEA2579598B81BC8247C87AAF
            857FF0555FDACBFE09C7FF000567F00FECD9FB51EBDE16F8B7E19F8AD7D6767A
            0F8AF4AD1E2D36E87DB676B4B49556DE38A32AB723CB9A29119D73B964601778
            07ED4D23121490338A6094B0040500F4EFF4AFCB8FDAB7FE0BEBE3DF8B3F1BB5
            EF843FB107C2297E3D78C7C33235BEBDE2BB8C8F0BE87286202095648D262DB2
            601DA7890B2031F9E320007EA4190F40013F5CE2943FCC07009ED9E457E3DD8F
            C0DFF82C7F8A7421E267F8D1F047C3376CEF21F094FA758C8CA3AAC6265D3665
            24F419B9EDCB560FEC1DFF0007157C66F85BFB76D8FECE1FB6B780748F01F89B
            55B94D374FF10595B35A24775236C80DC28924826B79DC144B9B72230C5720AE
            E7400FDA4A0E7B6335435FF1358785344BDD5354BDB3D374BD36DE4BABCBBBA9
            96182D218D4B3CB23B10A88AA096662028049E39AFC98F8B1FF05DCFDA07F6EE
            F196AFE18FD82BE06CFE3AD0345BCFECFD43E22F8A2116BA4999490EB6A92CB0
            C7950D0C81A572E558E6DC7CAC403F5CC4BBB241180707A1FEB4AAE598823047
            D6BF1E2FFE05FF00C1647C33E134F1443F1A7E0AF886FD20FB43F843FB3B4F8A
            766CE7C8594E9D1C458F0326E40E7EF77ADFFF008235FF00C1C47E2CFDA83F6A
            8D4BF674FDA53C0F65F0D7E30C0CF0E94F6F653D841A84F1233C9673DBCEECF0
            5C79637C6C1B64A370011BCB12007EB4B92149032476A6A485D41F9707A735F1
            97FC17B7F6EBF883FF0004EEFF00826FF89FE257C36B3D1A6F135B5FD969C975
            A8C5E7C5A647732888DCAC59024756640A1BE50CE0B2B852A7D2BFE0951F18FC
            71FB42FF00C13ABE11F8E3E246A3A76ADE34F15F87A1D5352BCB181208AE4CC4
            BC6FE5A00AAC6231EE0A00DDBB000C0001F41F9DD31800FA9C1A50E4005B0BEB
            9AFCC7FDBABFE0B05F17359FF829AF84BF65FF00D947C33E19F1B78AB4A297DF
            11357D52DE6B8D3FC3F01285A2691248D22F2A26DD2392F99268A251E6864AFB
            87F6D1FDB17C17FB057ECC7E2BF8ADE3DB9B8B7F0DF84AD44F2476A825B8BE99
            D8470DB40B901A59646445C90A0BEE7288198007AB190819C020F4A495F208C8
            00F4F7FA57E3B693FB527FC14FFF00E0A5DF0CADFE26FC16F0D7C2FF00D9EBE1
            F5F40DA9F872CFC42F1DE6B7E27B42A4C449B882640AE36B233456AAC0AB8668
            D958FDE9FB2AFC77F893F06BFE099F61F117F6AA8B4EF0F78F7C2BE1FBFD6BC6
            8961E514B786DE4B878F0B0BB46666B5484911B60C8CC001C2800F71F89BF0A3
            C31F1C7C05A8F853C61E1FD27C4DE1AD621F26F74CD4AD56E2D2E1320A828E0A
            E4150411CA9008C1C11F97BF1C3FE0CE5FD97FE2678EEE358F0DEBBF13BE1F59
            5D39924D1F4AD4EDEE6C62CF684DCC124A99C9E1A4603B002BD6FF00E0DF2F1D
            FC70FDAABE1478F7F68AF8CBE25D71ECBE346B02E3C19E12924DBA6F86B47B56
            99227B78B8D9E7348CA4E374896D0C8CCE5C1AFD0DF286ECE4F18FC2803F3FFE
            21FC17F84FFF0006E37FC1283E29F8BFE11785C7DB3C3BA6C73C97FA9C86F2FB
            5DD4E6962B3B396F24006E459E78CF971AC68ABBF6AA6E24FF002ADF1FBF6CCF
            8ADFB4F7C48BBF16F8FBC7FE2AF12EBF71399D6E6EB5194ADB364E0428084894
            76540A07615FDAFF00ED7DFB237823F6E5FD9E7C45F0BFE22D85E6A7E10F13C7
            125EDBDBDECB6921314C93C4EAF1907724B146E33904A0C82320FE227ED15FF0
            648DDBEBF7573F09BE375AFF00654CC4DBE9DE2BD2584F6C39214DD5BB1593EA
            204A00FC54F891FB647C5EF8D5E08B5F0B78C7E2A7C46F16786AC8836DA4EB3E
            25BCBEB0B72A411B2196468D7040C600E82B85D1745BFF00156B1169FA75A5C5
            FDF5E3EC8A0B689A69656CF4555049F5EF5FBCDFB3AFFC191B709AFDADD7C59F
            8DD6EDA646419F4EF0A692DE7CE31C85BAB83B53071FF2C1F38C71D47EC57EC4
            1FF04CAF821FF04EFF0008A693F0A3C05A47876791365DEACE9F69D5B51E9933
            5DC9995812376CC8407EEAAD007F1E36BFF04C5FDA4AFB445D520FD9EFE384DA
            594F305E47E05D51ADD907F109041B71EF9AF18D6744BBF0E6A97361A85B5C59
            5FD94AF05C5B4F198E5B79118AB23A9C1560410411918AFEFC360C11C907D4D7
            F0A7FB6AEBD2789BF6C5F8B5A8CCA892EA1E32D5EE1D5010819AFA6620024E00
            C903DB1401E62840604E715FD487FC19C7FB3FAFC36FF82616AFE349E0417BF1
            17C5F79750CE3ABD9DA247688B9EA409E2B9EF8E477CE7F96F4386E99C83FCAB
            FB5EFF008230FC0F8FF675FF0082567C05F0A2DB9B59E0F08596A37711EB1DD5
            E27DB270781CF9B70FD79F5C9E6803E9C3182304934823018119E3A7A0A75140
            0514514008EDB14938AF33FDB1FF0068FD37F64AFD953E227C4CD524812CBC0F
            E1FBCD5F6C8DB7CF962898C508F56925D9181DD9C0AF4C9090848C835F847FF0
            78DFFC14CEDBC3DF0E743FD98FC2FA8249AAEBD2C1E20F19985F22DAD11B7D95
            9B63F8A49409C8E081042791262803F9EDD5B53B8F116AF757F7B3493DD5ECCD
            3DC4AC01691D8EE673EE58E7F1A93C2DE18D43C65E25D3B48D22CEEF51D5754B
            A8ECECED6DE3324D733C8E1238914725D98A8007526A80739E46457EC6FF00C1
            A05FF04E24FDA17F6B4D5FE39F892C56E3C2DF080F91A2891034775AE4C87638
            CF07ECF093274C8792DD811B48201FB5FF00F0443FF826DC5FF04B9FD82BC33F
            0FEF043378CB5476D7BC5B710E1A3935399103C68C3EF242891C2A7F8FCADFC6
            EC0FAFA9896EB1904646093ED4FA002A1D42CA1D4AC66B6B98A39EDEE10C7247
            228649148C156078208E083C11535079E2803F257E257FC19C7FB30FC43F8CFA
            AF892DBC49F14FC31A1EAB76F79FF08EE91A859AD9D93312DE542D35AC8EB102
            4E1599880701BA63DFBE03FF00C1B59FB197C038E192DFE0EE9BE2ABF8B05AF3
            C4F7D71AB34A47730C8FE40FA2C407B57DD61429C81CD2D0073DF0E7E127857E
            0F78662D13C23E1AD03C2DA340731D8691A743636B19F511C4AAA3F2A67C58F8
            A5E1DF815F0DB5AF1878AF54B7D13C37E1EB56BDD46FEE33E55A42BCB3B10090
            06793DBAD7495E39FF000512F854FF001CBF606F8D7E0E8A332DCF897C0FACE9
            F6CA0907CF92CA6588F1DC4854FE1DE802FF00C3DFDB63E0E7C5EF033F897C31
            F147E1EEBFE1F890C936A365E20B4960B75EE6460FFBB23D1B18AFC66FF82EE7
            FC1D2DA3BF83B50F855FB2D7896E67D5EF6792CF5CF1E5B46520B68142829A5C
            84E5DDDB7A9B80A15554988B165913F9F472D8DC3040EE06067DBD3A57A3FEC6
            9F0CB44F8E5FB607C29F0578A2E6F2CFC33E30F18693A26AF3DA36C9E1B3B9BD
            8619DE338601C46EC41DA790383D28029FC06FD9EBC7DFB5CFC59B1F07FC3EF0
            CEB5E32F176B32E62B2B188CD237CC034B2B1F9638D4B02D2C8CA8A325980C9A
            FE967FE08B5FF06C3F80FF0061FD36C3C71F1A6CF42F893F14E6883C763716EB
            77A278689E891248B8B89C73FBE65DA0FDC5180E7F42BF64DFD87BE127EC39E0
            B3E1DF851E02F0F78234E971F6836100FB55FB0E8F713B9334CC3D64662071D0
            62BD612158F1B72028C019E28022B3D2EDF4EB48ADEDA18EDEDE05091C51A844
            451D1401C003D3B74E952AC6171C938A71CE38C0A6BB155246001CF3D2801D45
            7CC1FF00053AFF0082B2FC2CFF0082547C134F157C41BD9AF757D50BC1A0F873
            4FC36A3AE4EA3E60809C470A646F99FE54CE3972A8DF9B7FB2BFFC1EA1E0BF88
            DF19EDF45F8A9F09AEBE1E784F529FCA8B5DD3B5B3AB9D3413856B987C8898A0
            FE278C9201C8438A00FDC3A463819E0561FC3EF893A1FC57F05697E24F0CEAFA
            67883C3FADDBADD69FA969F70B716B79130E2447524153EC7B1F438D97625704
            FA1E053426CE23F693F8CF6BFB3EFC02F1978DAF446D0785B47B9D4823E76CCF
            1C64A47D472EFB540F56AFE59FC49AEDDF8A3C417FA9DF4AF737DA8DCC973713
            31CB4B23B16773EA4B31AFDF3FF8382B57BAD23FE09B9AFA5B4F2431DFEAFA75
            B5C2A9C0963F3C3ED3EDBA353F857E001627A81C0C7F2FF3F89AFCDB8CB10E58
            9851E9157F9B7FE48FF42FE87F9053A3C3F8CCDFEDD6ABC9E91A714D7DEE72BF
            A21285EA0E01C7AF028A55243023191CD7C733FAF8FB6FFE0DF1D286A1FF0005
            29F0DCDE604363A4EA5700633E666D4A607A11BF3F857F4095F827FF0006E5E9
            A97FFF00051512B3B86B2F0B5FCEB8FBAE4BC11FF273F957EF657EA1C20AD817
            FE27FA1FE68FD2C6AF371B423FCB429AFF00C9A6FF0053F9C0FF0082CEA08FFE
            0A67F1554673F6DB66C118EB656CD9FD6BE5F404B003A9E2BEB6FF0082E9029F
            F054CF8A4BB485274A238C75D26CCE7F3CD7C928A19B046477E335F9F668AD8C
            ABFE297E6CFEF7F0D2A73F0865735D70D41FFE5289FA51FF0006DF7ECA09F127
            F687D7BE296A76EADA6F80ADBEC7A612A087BFB9460CC3208FDDC3BF23AE658C
            E7839FDB25B2452482D83C638C57CABFF045AFD9D7FE19CFFE09FDE0AB7B880C
            1ABF8B236F136A20AED6F32E8031023A865B7581483DD4F4E95F57D7EA390609
            61B050835ABD5FABFF002D8FF32BC73E2EFF005878CF198A83BD3A52F654FF00
            C34F4BAF294B9A5F329DE68169A8CB0497104733DB4A2688BA8631B852BB8123
            8382467AE091D091569230849049CFAD3A8AF6123F24726D24DEC148FF0074F5
            A5A4906508CE3DFD2988FE77FF006AFF00F8291785BFE0989FF0755FC6FF0089
            9E2FD13C45AC6811785AC345B8B7D0ADE2B8BB95E6D0F4996370249625550EA8
            A4963804F04E0572FF00B357FC1427E1CFFC162BFE0BF3E09F8A7F1C3C43A57C
            20F0AFC338EDA3F879E14D4E69B7EA3A841334B6C26BA545822945C133319193
            718E0857CC196AFABBF66AB649BFE0F34FDA1E5918811780ACD947182C748D04
            7E78DE335EB7FF00074D7EC53F0CBE2DFF00C132BC77F14F5BD134BB1F881F0D
            A1B2BBD17C430C2B1DDE1EF60B7FB248EBF3490C8262A109C248518630D900EC
            7FE0E68FDB8F54FD89FF00E096DE233E1DB9B9B1F167C50BD8BC15A65D42DB26
            B35B88A492EA60410CA7ECD0CD1AB21CA3CD1B76AF74FF0082487FC13D740FF8
            2697EC43E0FF00873A5DAC435E16C9A8F8A6FC0532EA9AACA80DC48CC00CA21C
            45183CAC70C609620B1FC4EFF82BC7893C6BF15BFE0DC9FD88FE2578BDAEAEB5
            5D2B588B4FBB92E09925BC8BECD76B673CAC5B2C64B7B2590BB64B19739E727F
            A17FD9F3E3CF863F69DF82BE18F885E0CD4ADB57F0CF8BB4E8B51B1BA8A4570C
            8EB928F83F2C88DB91D0F28E8EA40208001D9989724E0024633DEBF187FE0F42
            FD9DF43D77F623F86FF13A3B18FF00E12AF08F8C13464BC56D8EF637B6D3BC91
            B11CB626B580AE4E10193006E35FB3A6420138538E7AE38C75FCEBF1BFFE0E89
            F13EA1FB67FC5CFD9DBF62BF042ACDE34F88FE268BC51A9C8033AE9161125C5B
            C734807DE8C23DECEE01DCAB639E8C0900C6FF0082D67ED89E38F8F5FF0004DD
            FD8E3E0668FAAFD9BC7DFB655BF87A1D6B514CA2F91243A7999582905566BBBC
            809EC638A553904D7EB2FEC9FF00B2EF843F632FD9E7C25F0C7C0BA7A69DE19F
            07E9F1D85B0F2E3496E9947EF2E6631AAABCF2B969247DA37BC8CD8E6BF1A7FE
            0E14D3740FD85BFE0A5BFF0004FCF1C5D799A7FC3AF004D6BA615506416165A5
            DFD8B48E140E59609930303714038C647EE5F86BC4D63E2ED0AC356D2AF6C752
            D2B55B68EF2CAF2CE759EDEEE0914324B1BAE55D195948652410411C7500BEF1
            855240E40AFC0DFF0083BAFC116DFB38FEDA9FB2D7C7EF0A451E9FE393A84B05
            C5CC60299E4D2EEACAE6C9D801F3329B8954B1C92A117A28AFDF096460846012
            457E2BFF00C15D3454FF0082AF7FC17DFF0067DFD9C345B65BFF000DFC0946F1
            678F2E704C56F14EF697535BBF4E1ADE1B28D597387D4003F74E003E9FFF0083
            A5F46FED0FF82217C5BB9DE11B4DBAD12E36904890B6B3670E3AF1832EEEE3E5
            FC4780DBFF00C15BE3FD913FE0919FB3CFC1BF83B25BF8D7F6A8F883E05D074B
            F0B78574E68EF2E7466BCB08668AFEF01CC50848244923498FCC5D1997CA5959
            7DE3FE0E9FD51F4EFF008224FC55803A2C37F79A2DBCA0A82768D5AD25500FAE
            E8D3EB8AFCB9B3FF0082087C7AFD91FE0C7C10FDB03F653F115DF887C5F17837
            46F14EA1E187B649F55B09EE74784DE0B52494BE824F3AE54C1B55FCB7089E71
            E6803F63BFE08C7FF04ADD3BFE099BFB38CE9AD5E3788FE2FF00C4175D67C7FE
            259E66967BFBF6DCC60495BE66861692401C9CC8ECF21C170ABC6FFC1C93FB11
            78DFF6EDFF0082617883C37F0EED6EB56F14787357B3F12C1A3DBF32EB496E24
            8E5B78D7F8DC472B48A9825DA250A37119E77FE08D5FF070FF00C3DFF8297DA4
            3E08F18C563F0CFE37DA298AE340BA94C765AE48B90EF60F21DC5F8C9B672654
            01B065547907E8D29DD823201C8C9E0FF9E2803F287FE08DFF00F07227C1DF8D
            3F0A7C29F0A7E2DDD5AFC1BF8ADE14B3B6F0F496BABC42CB48D565811600D0CA
            5552D9C9519B79426D66DA86400E3EFDFDBA7F634F0E7FC1417F65AF10FC27F1
            56B1E20D1FC35E2B7B36D426D16E2382EE58A0BB86E7CB0EF1BAED730AA37CA7
            2A48046735F32FFC16DFFE08A3F093FE0A15FB3FF8BFC587C3FA5786FE2F681A
            3DD6A1A478A6CD52CE7BB9A18772437CC062781BCA54DF265A2524A328DC1B0B
            FE0D64FDA97C55FB537FC1277423E30BB9F53D43C01AE5E7846D6FE762F35E5A
            411C1340598FDEF2E3B958013C9100CE5B24807E827803C0BA47C30F0668DE1C
            D02C20D2B43D02C61D334EB287223B4B686358E1897393854555193D077ADAA4
            09B7B934B4008CA1D483D0D06307A8CE7D79A5A2801A220063248FAF14246131
            8C814EA28011C954240C91DBD6BF835FDA135A3E26F8F3E37D4DA310B6A3AFDF
            5C94FEE17B891B1FAD7F794C32A735FC137C5819F8A3E2550300EAB75C75FF00
            96AD40173F67FF0085773F1D3E3CF823C1167E67DAFC63AFD868706C2036FB9B
            88E15C64119CB8EC6BFBC3D174BB6D0F4DB7B2B48920B5B589628A241811A2A8
            5551EC14015FC71FFC1BBDF0707C6CFF0082CD7C08D31A1DF0E95AE49AFC8597
            7245FD9F6B35EA31FF00B690201EE457F649CEE07078E9D2801F4556BFD4E2D2
            EC66B9B892386DEDE3324B24876A46A064B313C000724F602BF35FF6A1FF0083
            B1FF0064BFD9A7E20CFE1CB4D47C6BF136EAC9CC57575E0CD2E0BAB285C120AA
            CF737104730047DE84BAFA31E7001FA6348EC554900123D7A57E6D7ECF1FF075
            FF00EC75F1E2E45AEA5E2BF147C34BD91B6C50F8B742789643FF005D6D1AE214
            1EEF22FE75C0FF00C145BFE0ED2F80BFB3B7C3BD46CBE0BEA0BF17FC7F346D15
            9982D278344B093A092E279150CAA064ED8776E3805941DC003E9AFF0082CD7F
            C1607C19FF00049BFD9B2E75BD424B1D5FE22F8822783C23E19694897509C706
            7942FCC96D09219DB23710115833823F8F9F8E3F1A3C4DFB457C5BF11F8EBC65
            AB5C6B7E28F15DFC9A96A57B31CB5C4EEC598E070AA33B555405550140000ADA
            FDA93F6A7F1F7ED95F1A359F883F12BC497BE28F166B5266E2EE7C28545E1628
            D061628901C2C68A140ED9C9AF3B42D2B85E496E3DCD002479DE39C67DB35FD9
            87FC1033F63F8FF628FF008254FC26F0CCD662D35ED7B4D1E28D7014DB2B5E5F
            E2E0AC838F9E289A1B7FA40BEE4FE027FC1B73FF000457BBFF008291FED1F0F8
            F3C6DA5CE3E0AFC3CBB49F51328DB1F88EF94078B4E438E5012AF311D1004CAB
            4AACBFD60ADBAC112A44A2348D708AA30AA3D001400E329DC000083FE34BBC90
            08C649EDCD7CDBFF000563F80BF163F694FD843C71E14F823E37D4BC05F11EEE
            282E34AD46C6F9F4F9AE4C33472B5A8BA8C8783CD5468F72B2FDFC31D8581FE4
            33C6DFB6B7ED23F0F7C61AC683AEFC61F8D3A5EB7A25ECD61A8D9DD78BF5249E
            D6E6291A3963914CB90CAEACA41E41041E6803FB85DEDDC01F99A527A720135F
            C2B6BBFB70FC69F14F96352F8BDF13EFC43CA0B9F155FCBB3E9BA538AE7B5DF8
            F9E3CF144AB2EA5E35F16EA3227DD7B9D5EE252BED9663401FDE2DD5F476503C
            B33A45146373331C051EA7D29C2E01018152ADC839E31EB5FC095D6A573AA5DB
            DC5D4F35CCF29C3C9339766FAB3735EC1FB16FC181FB6B7ED5BF0EFE15F89BC6
            FACF86AC3C5FAA45A35BEA234C9F5B6B2965CA42AB6C8EACC1A5F2D0904040C5
            CE4291401FDA5FC49FDB07E137C1B80CBE2FF89FF0F3C2B1A8C96D5FC4567640
            7FDFC917BD7CD7F15FFE0E24FD8C7E1758DFADFF00C74F0B6AD2DA46C5A0D1AD
            EEB5537240FB88F6F13A12C78C96C73C9039AFE6CF45FF00837AFF006C4F16F8
            F758D0346F817E3498E9534D12DD6A2B6FA55B5CAA3B0DE92DCCA9136E0BB804
            76C83C13DFA58FFE0D91FDB5CF81750D7A4F839241169F1C929B17F10699F6E9
            55012C5215B82CC700E17AB7400920100F84B5F368FABDE3580956C5A6736E25
            C6FF002F71DBBB071BB6E338CF39AD4F841F12751F835F163C31E30D1FECFF00
            DADE13D5AD759B2F3D4BC5E75BCCB347BC0C12BB90640238EE2B1F54B49B4CBC
            9ED6E2292DEE60731CD148851E3704EE4604020A9E08E30452E83A4CDAF6B767
            616EA1AE2F66482207BB390A07E645007EF0789FFE0F7FD6BFE11FB08B46FD9F
            34A8F5610C6D79717DE2D91EDDA4E3CD11C296A194373B774876E4677639EC5B
            FE0F87F0DC5A7407FE19DB5C92ECC0AD32FF00C25D14718971CAA9FB21253D18
            8CFB57B2FC26FF008333BF665F0B59D8BF89FC57F173C51A9C712FDB17FB62D2
            D2CA493A931A476A255527D6427E5EB5E8BE23FF008347FF00633D634B8A0B5F
            0CF8E348922428D3DA78A2E1E4949C7CE44BE62EEE3B281ED401F16EB7FF0007
            C7EA3736CABA6FECD16369306F99EE7C7AD7085707F8534F420E71DCFF005AF1
            EFDA73FE0F36F8DDF16BE19EB3A17813E1FF00853E196A5A9A2C306B51DE4BAA
            5EE9C847CE63122245E693F759908504FCA5B0C3EE2F15FF00C1967FB346A929
            9349F1FF00C6BD2D9DF7149352D36E620BE8B9B2561CFAB1AE035CFF008321FE
            1ADC5B4ABA6FC73F1C5A4A5FF76D73A25ADC2A2E7A10AF1EE24719C8E71F4201
            FCFC7C66F8FBE37FDA3FC7771E27F881E2DF1178D3C45768B1CBA9EB7A84B7D7
            4635CED41248C4845C9C2821467802B9542782148200FE10735FD27FC19FF832
            8BE0A78575CB7B8F1C7C56F887E30B6872CD6BA7DBDAE9114E7B06244EFB7D76
            B03EE2BDB3C7BFF068A7EC6DE2FD1C5B69DA178F7C2B70148377A5F89A592662
            46338BA59A3CFD100A00FE7EFF00E0971FF059BF8CBFF04AEF88F6973E10D72E
            757F01DDDE2CBADF83EFE62FA76A2858798630D9FB3DC1038993072177891328
            7FAFFF00D987F689F0EFED6BFB3D783BE25784A5965F0EF8D74A8755B2F346D9
            6159141686403859236CA30E70CAC3B66BF2BA4FF832A3F672FEDA320F89DF1A
            C58641F24DF697E78007FCF4FB163FF1CAFD4FFD96BF66CF0C7EC7DFB3AF843E
            1878361BB87C33E09D3A3D3B4F1752896E2445C969256014348ECCCEC4003731
            C0030034267CB3FF00070E7FCA37F54FFB0F69DFFA31ABF022BF7DFF00E0E1CF
            F946FEA9FF0061ED3BFF0046357E0457E5FC5FFEFCBFC2BF53FD2CFA257FC911
            3FFAFF0053FF0049805009192081C1F7ED45033D41008E6BE591FD392D99FA1D
            FF0006D369B0DD7EDF1E227704BD9F81EF658C83D0FDBAC50E7F0735FBA55F88
            BFF06C959C52FED8BE39BA2A04D1F83E48D4FF00B2D7B6991F89407F0AFDBAAF
            D4B84A36CBE3EACFF313E94D579B8F6AC7F969D35FF92DFF0053F9EAFF0082FA
            44917FC14EBC6A5148325969658FF7BFD06100FE431F857CDBFB307C33B7F8D1
            FB49FC3EF085E1996CFC53E23D3F4A9DA219748E7B98E3661F45627D38AFAA7F
            E0E16B7483FE0A3FAB32280D2687A733903EF1F2D803F9003F0AF0CFF826A6BB
            A6786FF6FCF84379ABCA20B18FC51648D213808ED2048C93D8798C95F0B8EA6A
            59A4E12D9CFF00367F6E704E36AD1F0C70989A37E7860E2D5B7BC68E96F9AD0F
            E99B48B28349B182CEDA3486DED6358E28D06D545518000EC00156EA18387009
            393DAA6AFD7CFF00261C9B6DB0A28A298829B2FF00AB2338CF1D338A75046411
            EB401F84D0FC32FDAD3F657FF83837E36FED01E17FD98BC4FF0014BC39E2AF3F
            40B010EAF6DA45BDCDA14B48E0B84B9977A8C0B64C865C60B64A8E47BCFED07F
            B047ED5DFF0005B3F13681A2FED0BA7787BF670F805A0DF47AA5D7827C3FAEC5
            E21F107886E102ED5B8BD8945B04552FB194614B7314842BAFEAF0880C724EDE
            9486DD4800E481D39E9401E21FB4FF00FC13F7E1AFED65FB175FFC08F1068C6C
            BC053E956FA569D069EE23934216AA82CE5B562182BC06342BB83290BB5C3A16
            53F8E3E08FF827C7FC148BFE0869E27B8D27F678D5F4CF8E9F0867BA92E61D1E
            6589A084919DD2D8CF34735B48E4B126CE7646280BB6484AFDFEF257AF7E84F1
            C8F4A5F2C719C923B9EB401F8CD67FF0507FF82B1FC76D0CF87FC39FB2C780FC
            03ACDE46619BC41A8A1B78B4FDC3027852EEF8A6E43F3619260718D8DC03F4BF
            FC11FF00FE08B573FB0F7C41F157C65F8BDE336F8ADFB457C42563AD6BED96B3
            D312460F24569BD559B7B00A646541B23548E3893707FD02D8324F7348B12AB6
            4019EB401F347FC1563FE097FE08FF0082ADFECB573F0EFC5F7975A25ED9DD2E
            A7A0EBD6B12CD71A25EAAB20936310258991D92488B28753C3238575FCA0F84D
            F087FE0AA5FF000460922F027C3ED1F41FDA17E15696AD16910CA5753B3B58C9
            C0454335BDFDB955507CA0CD0217214BF24FEFC75A431820825B07DF1401F8CD
            77FB5AFF00C159BF6C8D15FC27E1AF813E00F810350516F7DE2DD45C45369B93
            CC912DC5CCC4295057E5B699C6ECAED2030FB27FE08E9FF047EF0C7FC128FE15
            EB2AFAD4FE36F89BE3C996F7C59E2BBB4DB2DF4A096F2220C4B0815DDDF2CCCF
            2348CCC47CA8BF68040083C922916154C81900D007E72FFC1CE1FB337C65FDB0
            7FE09DD61E01F833E149FC5DA95F78AACAEF5CB1B7BA861B85B08639D832891D
            030FB47904E09200CE3838FB03F611F865ACFC1BFD88BE0E783BC496F15B788F
            C29E07D1745D5A18D83A43776F610453A065241024471C1C57AC9B742A410181
            F51FE7D697CA1EF8FE5401F9ADFF000597FF0083787C0BFF00050AB5BDF88FF0
            E05BFC35F8F9603EDF6DAE58836F6FAFDCC63746B78A98DB2EE002DCA6245254
            B79811507CCDF043FE0A09FB67FF00C111FF0062FB7F10FED5DE03F127C57B2D
            53C591F87F4D864D76D67D4BC3D6515AB933CD796EB702659E40044B3B063E4C
            877E1D2BF70842A1B21403408800073C0C5007E27FC54FF828A7ED95FF0005C1
            F85DA97C2FF815FB3B6B3F04FC05E37B5363AE7C40F18DDC91C2FA6CEA525101
            7823521D0B230805CBED7380870EBFA73FF04D7FD85FC3DFF04E0FD8FBC23F08
            FC39773EA96DE1D8A492F3529E2114DAA5E4D219AE2E19013B0348E42AEE6D88
            88BB98824FBB988124E5B27DF14242A84919CB1C9F73400EA28A2800A28A2800
            A28A28011CE10927000AFE087E23DF43AA7C45D7AE606F320B9D46E258D81FBC
            AD2311FA115FDEFB72A6BF819F1BE8917867C69AB69D6ED2341A7DECD6F1B484
            172A8E54124003381D80A00FD5FF00F83347E15278D7FE0A8BE24F115C401E1F
            07F80EF6E21908C84B89EEAD6DC01E998DE7EB9E057F50A220339C907D6BF01B
            FE0C7BF86408FDA1FC652C4DC1D1346B4930307FE3F66986719CFF00A8E847D0
            F18FDFBA00F26FDB8FF64BD1FF006E2FD943C71F0AB5CD5B5AD0B4EF1A69AD62
            F7FA5DCBC37168DB95D1FE561BD03AAEF8D8ED9137237CAC6BF8E9FF0082907F
            C131BE2AFF00C1303E365D7837E23E8F247652BB368DAF5AA3BE99AFC008C4B0
            484603600DD1361D09C118C13FDB7901860D703FB467ECC7F0FBF6AFF8577DE0
            CF891E12D17C63E18BFC79961A940248D1C7DD9233C34720ECE855876233401F
            C2282CA848CED1C7B534CA4B024038AFE827F6E8FF00832D6D758D46F357FD9E
            7E23C7A646EC593C37E31569238875DB15F4285F18E1564898F4064EA6BF31FE
            3B7FC1BC9FB637ECFD7E62D4FE0678B75F819F64573E1758F5F8A519C06C5A34
            9228EFF3A29C7502803E2E0C5CE09E0D7DCDFF00045CFF00821C7C40FF0082B4
            FC56170AB79E14F849A14E175DF154B6E4A48C064D9D983C4D72C08CFF000C4A
            773F25124FBB7FE0935FF06816BBE2FD4B4BF1AFED4972FE1ED1D08B88BC0BA6
            5E2BDFDE8EAA2F2E63256043C66384B484641789862BFA07F861F0ABC37F057C
            03A57857C23A1E99E1BF0DE876EB6B61A6E9F6EB05B5AC6338554500752493D4
            9249C924D00627ECE1FB38F82FF64DF835E1FF0087DF0FFC3F65E1AF09F866DB
            ECD63656C0E14672D23B1C9795D8B33BB12CCCCC49249AEEB6F006480280807B
            E2968023997646CCA06E1C8192013F857E047FC16FFF00E0D83F8CBFB5AFEDE9
            E31F8B7F062E3C137BA0F8EDADEFAF34ABFD41B4FBBB0BD58238A76C142922CA
            F179BBB786DD2B82BC64FEFD3287520E707F0A410AA9C8C8E9C76A00FE60FE16
            7FC1981FB4B78A2F6DDFC53E34F84FE13B0723CD29A85DEA177103E91A5BAC6C
            47A1947D6BEF4FD967FE0CCCF801F0CADE1B8F8A3E32F1AFC51D507FAC82D997
            41D35863A7951179FAF7F3C671D2BF623CA5E38E076E82942850000001D2803E
            50F845FF00042BFD907E08246344FD9F3E1C5CBC58D926B7A77F6E48B8E8435E
            99981F70735F47F80FE12F857E1669E2D3C2FE1BD03C3768A028874BD3E1B388
            007A6D8D547E95D0D1400D5882938279FCBEB4188724924F51ED4EA1BA1EB401
            FC3E7FC151F49B6F0E7FC14C3F68BD36C618EDAC6C3E26F896DEDE141858634D
            5AE55507B0000C578669D7B269D7F0DC42EF1CB03891191B6B29072083D8D7AE
            7FC1427C711FC4EFDBDFE38F8962689E2F10F8FF005ED491A2C88C89B529E51B
            7249C7CDC7278AF23B0B39351BD8ADE14792599B622A825998F00000124E6803
            FBE2F07EB5FF00092F8674CD4BCA10B6A16915C94CE766F40D8F7EA6B4D9430C
            1C81EC71593E05D165F0E783347D3E76579AC2CA1B772BF74B246AA48C8CE320
            D6BD0026D19CE39346C19CE4FE74B450026D19046463F2A5233C514500205000
            00703B535E3032C33B88C67D69F4927DC34D099F0BFF00C1C39FF28DFD53FEC3
            DA77FE8C6AFC08AFDF7FF83873FE51BFAA7FD87B4EFF00D18D5F8115F97F17FF
            00BF2FF0AFD4FF004B3E895FF2444FFEBFD4FF00D26014A9F78719C76A4A55EB
            C80457CB23FA74FD3FFF008360ED51BF680F89B3140648F408103639506E7919
            F7C7E95FB415F8F3FF0006BBDA93E3EF8C3308C955B1D2D437F7433DD71F8ECF
            D2BF61ABF57E1656CBA1F3FCD9FE597D266AF3F8858C8FF2C692FF00CA507FA9
            F82FFF00071C5AC76FFF000507B678D40697C2960D21F53E6DC807F20057C57F
            06F4F9356F8BDE15B4864F266BAD5ED218DFA6C6699003F8120D7DD3FF00072C
            DB4707EDE5E1A78D706E3C0B652B1F53F6FBF5FE4A2BE33FD92A3865FDAAFE18
            A5C8436EDE2CD284A1BEEEDFB6459CFB62BE073687FC2A548FF78FEEBF0A714E
            3E1BE06B257E5C3FFE929AFD0FEA62DD48718FBA38153D45029560320E054B5F
            AFA3FC984AC145145030A28A6CAE638C9F4A00576DAB924003D69A2463D46DCF
            B1FF0039AFC9BF1B7FC15EBF697FF82997C77F1E7C37FD867C23E0BB3F08F816
            EFFB2359F8AFE2F9B7594773B9807B38C0746426362A4C5705A3218C71EE535E
            F5FF000496D0FF006E6F057C5DF893A1FED67ADF82FC5FE18D3ED2C5FC31E20D
            161B3893509D8C9E7AC4B6F140E11401BFED1023172A532B9A00FBA84A588001
            00FAE45297233C648F635F8B7FF053CFF82887ED9DA7FF00C1757C35FB33FC06
            F1A7837C27A6F89B4AB7BED1A1D4F4286E6DAED0D9CB3DC4B792B433CDF23DB5
            C63C90802AA8607E66AF5BF14FC14FF82B558584B7361F17FF0065CBF78E37FF
            00418B4BB889E6201C6C3258852E4F23732AE7A9C66803F52119D9B950053989
            5524638AF94FFE091A7F6A83FB3DEA8FFB5A3F870F8FA4D6A53A7C7A52DAEF8A
            C7CA8F6899AD4980B79864DA1790A06EC9AFAAE5244648078F6CD0037CD619CA
            E00FE54E46638CE39F4AFC0EFF0082A67FC17E3C65F0AFFE0B47E02B0F09F887
            5AB0FD9EFE0DF8AADB40F175D696673A77882F250BFDA71CEE9F2CED6B13B2A4
            0C0ED96DDDC641561FBD76D791DEC314D03A4D0CAA1D1D1B723291C30238231E
            9D88A009D890A4800914DF348C02073F515F307FC156FF00E0A93E10FF008255
            FECD83C6FE21D36F3C4BAE6B376349F0D7876C2511DCEB97CC8CCA9BC83E5C4A
            002F2057DA380ACC554FC21F102F3FE0B09F1BFC02FF0012FC3773F083E16DB3
            DAADC5B7C38B4B6B59358B88D8EE50ED7905C22CFB0FCCAD77110411B15BE400
            1FB1CAEDB8060013C7D78FFF005D398E0679FCB35CA7C22BEF125B7C1AF0CDCF
            8F069769E2D4D16D25F111B36DB650DF0814DD79793811097CCC1C9C2F73D6BF
            31BF682FF82F07C6BFDADBE29F88BE1EFEC15F0693E2C27856E1AC75AF883ADA
            88FC3B1CC0ED2968CD343148790C924928DE158AC32200E403F588CDF2823193
            D39E2943FCC01E33FAD7E3D7FC332FFC161E5F0FC3E245FDA27E0CC3AA185E59
            BC353697A7831E0B6D85645D29A2663C0C99801DDAA8FF00C1327FE0E1BF8B4B
            FB77AFECCBFB61F82346F0278EEEEE068FA5EB56D6EF6224D409FDD43711991E
            2912E7A43716E446CC630159640EA01FB28EDB149209029B1C8CC012A003D2BE
            71FF0082B8FED2DE2AFD917FE09B5F17FE2478265B2B6F15F857436B9D32E2EA
            DD678EDA669638C4BE5B7CACC81CB286054BA00430C83F37FF00C1BCFF00F05B
            7B4FF82A47C079BC39E36BED320F8E5E0A8FFE2756D0C42D86BB679554D4A188
            7CA392A932A7CA9260ED449631401FA42CDB549F4A8CCC42640E4F4CF03F5A16
            52CA09DA01E983907E95F97DFF000536FF0082967C74F837FF0005B5FD9ABF67
            6F86579A0E9FE12F8870E9BABF884CDA625CDEDE40FA85DC7769BDC9F2D12D6D
            59D7600DBB39623E5A00FD435662791C74E98A754712631C018FE5CFE5525001
            451450007A1AFE097E2CFF00C951F12678FF0089ADD7FE8D6AFEF65C90A48049
            F4AFE0BBE366993E8BF18FC596772862B9B5D66F21953A94659981FD73401FD2
            97FC1971F0F87877FE099DE38D7A45613F88BE215DAA1FE16820B1B145238CE7
            CC69875C74E9CE7F602BF3B7FE0D5CF040F07FFC113BE165CB23452F882F35AD
            4DD08208FF0089ADD42A4FAE52143F8D7E895001430DC08C919A28A004D838F6
            A468838604B0DC307048A75140082301B3924D2D145001451450014514500145
            1450007A530CA77000633ED4E97263600649E2BE65FF008296E93FB53EB1F0EB
            4493F658D57E18E9BE20B4B8967D617C5C266FB742231E5436BB6378C396DD93
            2151D391CD007D33E611C9038F7AE17F69CF8AB69F04BF672F1EF8C2FF0053B5
            D1ACFC2FE1FBED525BEB804C76A21B777DEC0104E0A8E01049E072457F38BF1C
            3FE0E70FDBE7F635F8BBADF817E27F877C0BA2F8AF4893CBB9D3B58F0BB44D08
            C655E27867559236182B22B323AB02A4839AF14FF8285FFC1CD3F1DFFE0A33FB
            285DFC28F13E89E03F0AE97AD5E433EB173E1AB7BA824D5608984896CE26B89B
            6C7E60476008DC500E0120807E775F4EF7D7524D2BBCD3CEC5DDD89DCEC4E4B1
            CF73D7F1AFA3FF00E08E9FB364BFB59FFC1503E08F82628C4D697BE29B5D4351
            42320D8D9B7DB2E81E303304120C9E3247D2BE698DDB76060679CF5FC6BF7FFF
            00E0CF1FF8259F89FC25E26D6BF69AF1AE912699A46A7A349A2782A1BA52B35F
            2CD221B8D4154F2B1ED8BC9463C38965206002C01FBF080027031CD3A902E0E7
            249A5A0028A28A0028A28A0029B29C467834EA49798CF5A684CF85FF00E0E179
            10FF00C137F560C198FF006EE9C1483801BCC3D41ED8CD7E0457EFB7FC1C38A3
            FE1DC3AA1EBFF13ED3BFF436AFC09AFCBF8BFF00DF97F857EA7FA57F44AFF922
            27FF005FEA7FE9300A3AF1EBC514A9F786064E7A7AD7CB23FA799FAE1FF06B5D
            B383F1C6728C2363A1C6AC7A123FB44903F315FADF5F955FF06BBD9CABF0EBE2
            EDCB21114BA9E9C8BFEF08AE091F4F987E75FAAB5FAD70CAFF0084DA7F3FCD9F
            E51FD22EA73F8899935DE9AFBA8D347E217FC1CD7A7C31FED85E06BA0805C4DE
            0D8E373DCAADEDD103F3735F9D5E19D7A6F0AF8934FD52D8E2E34EB98EE623CF
            0E8E194F1EE057E95FFC1CF365147FB447C34BA03134FE1C9A263EA12E5881F9
            B9FD2BF3194E0E72462BF3DCFDF266355AE8FF00447F7D780D255BC3DCB54B54
            E9C97DD3923FAD3D13518758D36DAF2DDFCC82F2259E26FEF2B0041FC460D5DA
            F28FD867C61FF0B0BF637F855AE799E636A5E13D32590F7F33ECB1871FF7DEE1
            F857ABD7EB9466A74E335D527F79FE53E6782783C655C24B7A72947FF016D7E8
            14514568708554D7B4F6D5B44BCB55B89ED1AE617884F01C4B0965237A9ECC33
            91EE2ADD0C37023919A00FE783FE0925FF000507D43FE0DC9F8D3E3AFD977F6A
            2F08EA7E18F086B5E2297C41A478CAC2C66B9B632491456E6EB0A0B5C58CB15B
            4455E15696274747424B087F7AFE04FC7EF05FED39F0C749F1AFC3EF12E8FE2E
            F0A6B685ECF51D367134320524329C728E8C0AB46E03232B2B00C08AC7FDAA7F
            63CF867FB6B7C27BBF057C52F0668FE33F0F5D02561BD8BF7D68E463CDB79948
            92DE503A49132B0F5AFC82FF008212FC35D77FE099FF00F05E0FDA07F64CD0FC
            4FA9789BE15C5E1F5F12D9C774E18DB4A534F9AD6660A360985B5E9825745413
            1589CE0222D00723FF000530FDB53C1FFB16FF00C1D99F0DFE23FC47B892C3C1
            BE0DF07C5A75E5E416D25C4968975A6EA312CBE5A659F12DD8CED04EDCE0122B
            EE4F11FF00C1D41FB11687116B7F8B37DABB0DC0A59F84B570571D3996D901CF
            B13EE457CCFF00163E10F857E35FFC1E19A5693E2FD1746F11E9567F0EC5E269
            DAA5A45796B34ABA74AABBA3901562A1CB8C8382A08C100D7E9C5CFF00C1323F
            66F7D56C7513F007E0C2DFE9930B8B5B84F0569CB2C0E1B7065610E73BBE6FA8
            07AD007B6962A03053BBA0CE48FCC74FE55F187FC172BFE0A0DA9FEC47FB1EBE
            91E06596F7E35FC5EBB5F06FC3ED36DB06EA5D42E4AC4D731AE7398165575246
            3CD78148C39C7D8BAE6B569E1BD16F353D46EA1B1D3F4E81EE6E6E2E240915BC
            68A5DE466380142824938C01DABF9FCD17C05FB54FFC177FFE0A4FAEFED4FF00
            B3D78BBC21E05F007C22D5E5F0B7C3ED5FC5D089A13124244D35BD93DADC0696
            513F9CCF346A53CF8C2BEF840400FAC7F683FF008209E99E1BFF00837AB5BF81
            BA558C3AEFC50D0AD1FC7F26A51234D71ACF8A634335C18DB00C8658BCDB188B
            0CF96D116E46EAF4FF00F8364BF6F24FDB6BFE0977E17D3B53BD49BC65F094AF
            83F585665F3248608C7D8672B9276BDA98E32C705E4B798F6E390F0CFEC3FF00
            F053BD66EAE4EBDFB6BFC3BD06211FEEE3D23E1DE9B7E4B12463F7B651320C00
            77658E4F4AF83FFE0995E0EF885FF06F27FC16F746F853F1675AD1F51F0A7ED0
            FA6416926ABA5078B4B9EEA699FEC770A85102C915E096D98101638EED9FA328
            A00FB23FE0EA7FD953E287C47F867F053E35FC2DD1EE3C51AAFECFBAF5D6B77F
            A2C1686F2468256B4905E1857E6923824B250E106424ECFC2A311ED9FF0004C5
            FF0083893E027FC14934FD13C3E7588FE1EFC58D480824F08EB6E636B99F6A96
            16772544372ACC4844CACC76F312F53F7C264E08071D47078FF0FCBD6BF1DBFE
            0E68FF00823FFC30BBFD96FC59FB4BF80B4BB2F879F16FE1F3DB6B1777FA3916
            116BD1FDAD15DA68D485174AF2F9AB3A8123B28462F942A01EA1FF0007517ED7
            1AE7C10FD8234AF855E0B9E68FC6FF00B426B91784AD92DDDD6E64D3C6D37810
            8232642F6D6CC0FDE4BB71DB35F69FFC13D7F624F097FC13C7F64CF08FC2AF07
            DBC2967A05AAFDB6F442B1CDAC5F3283717929006E791877FBA8A88384007E18
            7FC15EFF00695F177C40FD857FE099DFB4CF8C2CEEF55BAF0BDF4B71AFCE5006
            D42EE3934D91646270A249D74C9E403A64B11802BFA1AF861F13342F8C3F0F34
            5F15F85F56B1D7BC3DE21B38F50D3AFED24DF05E4122EE4756C72083EC473900
            8C5006FBA0DA7A9CFA1C57E1DFFC1E89F022D344F845F04FE3A6908DA678BFC3
            7E26FF00845FFB46DB11DCC914D0CD7D6C378F9BF732D9CEF1E38533C8782D5F
            B86D233292847B1C6474AFC5BFF83864CDFF00052CFF00828FFECE1FB16F84A5
            B997C9D45FC5DE389E1DBB74BB42A70DBF0424896A976F87182D716C392D8A00
            FA87FE0BDFE399BC43FF0006FDFC53F105E896C2F35BF0CE8B3CB1A8C9492E2F
            EC0797863D0B49B4F700E7935F973FB55FFC129FC6BFF04F2FD95FF670FDB77F
            6616BBD375DF0E780FC3FAB78EF4EB30D2A24ADA65B9B8D4F62B12F6B30665BA
            897E501CC9F74B94FD46FF00839CEEECFC3BFF00042CF8CD6EF0A2C6E9A15ADB
            C414AAA9FEDBD3CA8F60A17383FDD02BE8BFF82704165E31FF008266FC0449ED
            E0BBD3F53F863E1EDF04F18923962934AB7CA329E194AB1041E08241E28038CF
            F82457FC1543C19FF055FF00D97ED7C6DE1FD9A5F8AB47D961E2CF0F3CA1A7D1
            2F4A6EE3BB5BCB8668A420060ACA76BA488BF23FEDC6906ADFF0764FEC716335
            B5BB247E02D62E4C8011248C2D35D74048EC8F12B0F727AE715F1BFEDE1FB2F7
            C41FF83643FE0A29A5FED1BF03EC66D5FE0178DAF4D96ADE1F3332416692B179
            748958676A9D8D25A4C54EC7408CB26C226FA1F45FDB13E1EFEDF1FF0007247E
            C77F13BE1D6B31EB3E1FD5FE13EAB2796C42DD69773E4EB425B5B88C13E5CF19
            62ACA4E3A32965656600FDA60801079E3A52D355D8B818F9719CFAD3A800A28A
            280124198D872323B75AFE12BF6B8824B1FDAB7E274532345343E2BD55190F55
            61792823F035FDDAC99D8700935FC37FFC147B499F43FF0082867C79B1B9411D
            C59FC44F10432A7F759752B8047E631401FD6D7FC107FC1EBE09FF00823EFECF
            3668AA8B3783ED6FF00119FB496B8CF3EBE6E7F1AFADEBC5BFE09C1E171E07FF
            00827BFC07D1556441A4FC3BF0FDA112637E63D36DD3E6C0033C738039AF69A0
            028A28A0028A28A0028A28A0028A28A0028A28A0028A28A0008078232298615C
            938049C7614FA0F3DC8A00FCC0FF00839EBFE094167FB78FEC657BF10FC31A4C
            327C54F8456726A5652C31627D5F4B40D25D69E71CB90374D129048752AB8F35
            F3FCA46D52849276020640E7FC3DF1FAD7F7E52DA4732B2BA8757041520608F4
            3EBF8FAD7C7565FF0006F97EC6961F164F8D53E01F841F5B3299BCA966BB974C
            DE5B767EC0D31B4EBDBCAC0A00FC26FF008374FF00E0807A87FC1427E225A7C5
            5F8A3A5DF69DF04BC37741EDEDE6531378D6E91BFE3DE36E08B4423F7B2AFDE2
            0C68436F68FF00A96D0BC3F63E18D22CF4ED36CADB4FD3F4E812DAD6DADE258A
            1B689142A4688B80A8AA000A380053B45D0ECFC39A5DB5869F6D05958D94296F
            6F6D0208E1B78906D54445C2AAA800000000003A0156B18C60918A0028A28A00
            28A28A0028A28A002924FB8696924FB869A133E17FF83873FE51BFAA7FD87B4E
            FF00D18D5F8115FBEFFF00070E7FCA37F54FFB0F69DFFA31ABF022BF2FE2FF00
            F7E5FE15FA9FE967D12BFE4889FF00D7FA9FFA4C028076E49EDCD147D4640AF9
            647F4EBD8FDA4FF8361B4D787F67BF8957646239BC470C03DD92D949FF00D087
            E75FA795F9BBFF0006CA698F17EC6FE35BDDCA639FC67345B7B865B1B327FF00
            43AFD22AFD7B8795B2EA5E87F929E3CD5E7E3FCCE5FF004F12FBA115FA1F90DF
            F073FF00C39B9FB6FC27F17471BBD96CBED22793F86293314D12FD594CA7FED9
            9AFC985E4E39E6BFA1EFF82E4FC0A3F1BBFE09D7E327860171A8F839A1F12DA0
            E3E516ED89DB38ED6D25C57F3C60600651920E79F4AF85E2CC3FB2C7B9F49A4F
            F4FD0FEDCFA2DF114730E06A7837F161673A7EA9BF6917FF0093F2FC8FE8B3FE
            0883E333E35FF82657C3395E40F369F0DE69D20EE9E4DEDC2A0FFBF7B3F3AFAC
            ABF3C7FE0DAFF199F10FEC33AE698EF99341F16DDC4ABFDD8E4B7B6907E6ED27
            E55FA1D5FA164D57DA60694FFBABF0D0FE0AF1732FFA971AE6987E9EDEA497A4
            E4E6BF0920A28A2BD23F3B0AE27F695F893ACFC1BFD9CFC7FE2FF0EF87E7F167
            883C2BE1CD4357D334487799759BAB7B69258AD1762B36E95D1506D5272DC03D
            2BB6A080C30471401F8BDE06FF00839ABF685FDAEBC36FA27C0FFD88BC6DABF8
            D6622C64D42F2FEE2E743D12F083B4DC38B585366549C4B3C19C7DE18AFA3BFE
            08B3FF00049BF1EFEC9BF13FE23FED01F1FF00C4965E2EFDA1FE30A05D55EC7E
            6B6D0AD1A4595ED11D400ECCF140182288D16DA248F2AA59BF4416055E99C761
            D87F9FE947D9D783CE47E9FE1401F88DFB5E7EC95FB5F782BFE0E2FF0010FED3
            1F087E058F895E18F0BD8D9E9FA7FDBFC47A768D6BA943368496B36C7B89E373
            E5CD24FD14F31807AE6BD83C67FB797FC1546D749BB9ECFF0062DF8636AA8018
            CC9E31B2D41A3F9BBC70EA4AEFDBEEE31D4E0038FD59581536ED18DBC0C7000F
            4A704C0E0B67D7AD007F3EBFF053EFDB43FE0A21F12FFE09FB71F0CBC79F01FC
            4DA1F8AFE2B7886E20D4EFFC15A14F7565A7E8012D63874DF32DA5B92B25D5D3
            4E1C4928630C617F7826629FB1DFF04C3FD91ACBF619FD833E17FC2CB5B38ECA
            EFC33A141FDAEAADBFCDD4A65F3AF64DDFC41AE64948EA02E17A28C7BD0B7518
            C0202F3F8FAFD695630A4903934003460A918CE7D7915F95FF00F074CFFC136F
            C7BFB7D7ECFF00F092EFE11F83F50F167C4BF0978B5AD6D92D2E60B6FB269F75
            6B234D2492CCC888A27B5B30096014B1F5AFD52233C11914D585541033CE79CF
            3CF5A00FCB4FDB2FFE0B59F183FE0925A0FC0AF0BFC4FF00817ABFC50D5FC55E
            06B27F10788344D50C48DE224FDD5CDAA6DB678A47CAA48C032F3382B9039F14
            F8D769FB697FC1C49A569FE00D5BE145F7ECA1FB39CB7905C788E7F10B4B26B5
            AE88A4491638E295219264DCA8E80411C7B941333ED0A7F6D844AA72320FF3A3
            C9057049618C726803E65FDA5BFE0955F0AFF69FFF00827E587ECE7AE69F756B
            E0AF0F69765A6F87EE2DDC1BED124B284436B75139EB2AA83BB230E1DD4E4331
            AFCA5F865FB047FC14CBFE0893AEAF867E016A9A0FC75F844F7335C59E953B40
            6D22258B624B4B99629ECDDCB33B2DA5C3445B71672CC057EF9ADBAAE48CE4F1
            D71C7A52B44186324718F7A00FC664FDB0FF00E0AE9FB4D6952F86745FD9FBE1
            97C219AFFF00D16E3C5377B616D2C7433469737B386C67F86DE73E8A4D7D69FF
            00046FFF00823168DFF04C7D33C49E2EF11F896E7E24FC71F88B99BC57E2EBB0
            C776F93CD7B7B62F993CA697E77773BA6744760A16344FB9BCB18C0C81EC6904
            2AAD9000E318C0C0A00FCFBFF8392FF65CF8C3FB65FF00C1385BE1D7C15D025F
            14EBFACF89F4F9755D3E2BCB6B569B4F8966958EFB8911302E12D9BEF03F2F7E
            87E88FF825D7C26F18FC08FF0082797C1BF03FC41D3E2D2FC5FE12F0AD8E8DA8
            D9A5DADD2DBB5BC42244F31094622355CED2475E6BDF0C409392483D8F22848C
            274CD00729F1BFE07F84FF0068AF84BE21F0478E344B3F12F857C4F66F61A969
            D780B4571138ED8C147070CAE843A3056520AA91F859FB06FF00C102BE2D7FC1
            377FE0E1BF02EAFE19D2B57F10FC11D25755D56C7C5F308CA5A58CDA65CDB0B4
            BB236FFA52CB3A441428F307EF55428754FE80186E041E869AB0AAA80012074C
            F38A0048CE0F0A406E7E94FA40B8C12492296800A28A28011C16423919AFE25F
            FE0B07A28F0E7FC156BF68EB76984FE6FC4AD7EEF728C05F3B509A6C75EC24C7
            D457F6D123154240248E83D6BF12BFE0A11FF068D6A9FB667ED91E3DF8AFA37C
            6ED27C370F8F75797567D2A6F08BBFD85E40BB904AB75FBC258125B62F527140
            1FB13F01B424F0C7C12F06E991195A2D3744B2B5432637911DBA28CE00E78F41
            5D6D456E76E10050178C05DA0607A761FE22A5A0028A28A0028A28A0028A28A0
            028A28A0028A28A0028A28A0028A28A0028A28A0028A28A0028A28A0028A28A0
            028A28A002924FB8696924FB869A133E17FF0083873FE51BFAA7FD87B4EFFD18
            D5F8115FBEFF00F070E7FCA37F54FF00B0F69DFF00A31ABF022BF2FE2FFF007E
            5FE15FA9FE967D12BFE4889FFD7FA9FF00A4C0280704719A2A5B1B496FEF2282
            18E496699822222966624F0001C924F6EF5F2CB73FA75B3F73FF00E0DABD2CD8
            7EC19AECDBCB0BDF1ADECD8230571656298FFC733F8D7E8657CCFF00F049AFD9
            22F3F631FD8C7C35E16D55A4FEDFD48BEB7AC44C322D2EA70A4C19F58D5510F5
            CB2B1070401F4C57ECD9451952C152A72566A28FF1D7C53CE30D9A7176639860
            E7CF4E7564E2D6CD2764D7934B4F2323C71E0FB1F1DF82757D0751844FA6EB56
            53585D447A490CA851D79F55622BF95CF8B5F0CEF3E0EFC50F12785352C9D43C
            2FAA5C695727615512432B44C7193C1D99C73C1EA4609FEAE2650F1904900FF8
            D7C13FF0562FF823B695FB66E9975E35F0425A68DF13AD6151217FDD5A6BE8A0
            E229B68F965032164EFC06C8C32F95C4F94D4C5D18D4A3F142FA7747EA7F470F
            15303C279A57C166CDC70F8AE55CFD2138DECE5FDD6A4D37D2C9ECB4F11FF835
            EFC623FB37E2FF0087E490AEC9F4CD4604393BF72DD24847A6364609F715FACD
            5FCF1FFC1387C63F11BFE09D3FB6BE97ACEBFE0BF16E95A299DB44F14C52E937
            0161B491B0CEC42E3F74FB660413B821C641AFE84ADB50FB4C4AE8F1B8701948
            070C0F7FC6AF856B7360BD8C934E0ECEFF0087F97C8E7FA4E647F56E319E6D46
            719D1C646338CA2D3578C63092BA7BE8A5E9245AA2BE69FDA3FF00E0AC7F06BF
            64AF8A53783FC79AE6ABA4EB70C11DD7969A2DD4E8F148B95757442A41395E0F
            055876AE1BFE1FF5FB31FF00D0E5AC7FE13D7BFF00C6EBD6A999E1212709D58A
            6BCD1F96607C36E2CC661E18BC265B5EA539A4E328D29B8C93D9A6959A67D9F4
            57C61FF0FF00AFD98FFE872D63FF0009EBDFFE3747FC3FEBF663FF00A1CB58FF
            00C27AF7FF008DD4FF006B60BFE7EC7EF4757FC428E34FFA14E23FF04D4FFE44
            FB3E8AF8C3FE1FF5FB31FF00D0E5AC7FE13D7BFF00C6E8FF0087FD7ECC7FF439
            6B1FF84F5EFF00F1BA3FB5B05FF3F63F7A0FF8851C69FF00429C47FE09A9FF00
            C89F67D15F187FC3FEBF663FFA1CB58FFC27AF7FF8DD1FF0FF00AFD98FFE872D
            63FF0009EBDFFE3747F6B60BFE7EC7EF41FF0010A38D3FE85388FF00C1353FF9
            13ECFA2BE30FF87FD7ECC7FF004396B1FF0084F5EFFF001BA3FE1FF5FB31FF00
            D0E5AC7FE13D7BFF00C6E8FED6C17FCFD8FDE83FE21471A7FD0A711FF826A7FF
            00227D9F457C61FF000FFAFD98FF00E872D63FF09EBDFF00E3747FC3FEBF663F
            FA1CB58FFC27AF7FF8DD1FDAD82FF9FB1FBD07FC428E34FF00A14E23FF0004D4
            FF00E44FB3E8AF8C3FE1FF005FB31FFD0E5AC7FE13D7BFFC6E8FF87FD7ECC7FF
            004396B1FF0084F5EFFF001BA3FB5B05FF003F63F7A0FF008851C69FF429C47F
            E09A9FFC89F67D15F187FC3FEBF663FF00A1CB58FF00C27AF7FF008DD1FF000F
            FAFD98FF00E872D63FF09EBDFF00E3747F6B60BFE7EC7EF41FF10A38D3FE8538
            8FFC1353FF00913ECFA2BE30FF0087FD7ECC7FF4396B1FF84F5EFF00F1BA3FE1
            FF005FB31FFD0E5AC7FE13D7BFFC6E8FED6C17FCFD8FDE83FE21471A7FD0A711
            FF00826A7FF227D9F457C61FF0FF00AFD98FFE872D63FF0009EBDFFE3747FC3F
            EBF663FF00A1CB58FF00C27AF7FF008DD1FDAD82FF009FB1FBD07FC428E34FFA
            14E23FF04D4FFE44FB3E8AF8C3FE1FF5FB31FF00D0E5AC7FE13D7BFF00C6E8FF
            0087FD7ECC7FF4396B1FF84F5EFF00F1BA3FB5B05FF3F63F7A0FF8851C69FF00
            429C47FE09A9FF00C89F67D15F187FC3FEBF663FFA1CB58FFC27AF7FF8DD1FF0
            FF00AFD98FFE872D63FF0009EBDFFE3747F6B60BFE7EC7EF41FF0010A38D3FE8
            5388FF00C1353FF913ECFA2BE30FF87FD7ECC7FF004396B1FF0084F5EFFF001B
            A3FE1FF5FB31FF00D0E5AC7FE13D7BFF00C6E8FED6C17FCFD8FDE83FE21471A7
            FD0A711FF826A7FF00227D9E464629A611DB233FAD7C65FF000FFAFD98FF00E8
            72D63FF09EBDFF00E3747FC3FEBF663FFA1CB58FFC27AF7FF8DD1FDAD82FF9FB
            1FBD07FC428E34FF00A14E23FF0004D4FF00E44FB3563098C64E3D69D5F187FC
            3FEBF663FF00A1CB58FF00C27AF7FF008DD1FF000FFAFD98FF00E872D63FF09E
            BDFF00E3747F6B60BFE7EC7EF41FF10A38D3FE85388FFC1353FF00913ECFA2BE
            30FF0087FD7ECC7FF4396B1FF84F5EFF00F1BA3FE1FF005FB31FFD0E5AC7FE13
            D7BFFC6E8FED6C17FCFD8FDE83FE21471A7FD0A711FF00826A7FF227D9F457C6
            1FF0FF00AFD98FFE872D63FF0009EBDFFE3747FC3FEBF663FF00A1CB58FF00C2
            7AF7FF008DD1FDAD82FF009FB1FBD07FC428E34FFA14E23FF04D4FFE44FB3E8A
            F8C3FE1FF5FB31FF00D0E5AC7FE13D7BFF00C6E8FF0087FD7ECC7FF4396B1FF8
            4F5EFF00F1BA3FB5B05FF3F63F7A0FF8851C69FF00429C47FE09A9FF00C89F67
            D15F187FC3FEBF663FFA1CB58FFC27AF7FF8DD1FF0FF00AFD98FFE872D63FF00
            09EBDFFE3747F6B60BFE7EC7EF41FF0010A38D3FE85388FF00C1353FF913ECFA
            2BE30FF87FD7ECC7FF004396B1FF0084F5EFFF001BA3FE1FF5FB31FF00D0E5AC
            7FE13D7BFF00C6E8FED6C17FCFD8FDE83FE21471A7FD0A711FF826A7FF00227D
            9F457C61FF000FFAFD98FF00E872D63FF09EBDFF00E3747FC3FEBF663FFA1CB5
            8FFC27AF7FF8DD1FDAD82FF9FB1FBD07FC428E34FF00A14E23FF0004D4FF00E4
            4FB3E8AF8C3FE1FF005FB31FFD0E5AC7FE13D7BFFC6E8FF87FD7ECC7FF004396
            B1FF0084F5EFFF001BA3FB5B05FF003F63F7A0FF008851C69FF429C47FE09A9F
            FC89F67D15F187FC3FEBF663FF00A1CB58FF00C27AF7FF008DD1FF000FFAFD98
            FF00E872D63FF09EBDFF00E3747F6B60BFE7EC7EF41FF10A38D3FE85388FFC13
            53FF00913ECFA2BE30FF0087FD7ECC7FF4396B1FF84F5EFF00F1BA3FE1FF005F
            B31FFD0E5AC7FE13D7BFFC6E8FED6C17FCFD8FDE83FE21471A7FD0A711FF0082
            6A7FF227D9F457C61FF0FF00AFD98FFE872D63FF0009EBDFFE3747FC3FEBF663
            FF00A1CB58FF00C27AF7FF008DD1FDAD82FF009FB1FBD07FC428E34FFA14E23F
            F04D4FFE44FB3E8AF8C3FE1FF5FB31FF00D0E5AC7FE13D7BFF00C6E8FF0087FD
            7ECC7FF4396B1FF84F5EFF00F1BA3FB5B05FF3F63F7A0FF8851C69FF00429C47
            FE09A9FF00C89F67D15F187FC3FEBF663FFA1CB58FFC27AF7FF8DD1FF0FF00AF
            D98FFE872D63FF0009EBDFFE3747F6B60BFE7EC7EF41FF0010A38D3FE85388FF
            00C1353FF913ECFA493EE1AF8C7FE1FF005FB31FFD0E5AC7FE13D7BFFC6E9B27
            FC17EBF663D87FE2B2D6067FEA5EBDFF00E3742CDF05FF003F63F7A13F0A38D3
            FE85388FFC1353FF009131FF00E0E1CFF946FEA9FF0061ED3BFF0046357E0464
            282589000AFD6BFF0082C1FF00C1557E0B7ED77FB195F783BC0DE23BED4F5D9B
            54B3BB5825D2AE6D8148DD8B7CCE817A7BD7CE3FF0458FF826AC3FB6F7C68B8F
            10F8B2CAE24F86BE106FF4E52ED17F6ADDB2EE8AD55860ED008924C745D8BC79
            808F83CF60B1F99469E164A57495D6A96F7BDBB6E7F6FF008218C9702F87589C
            7713D29E1D52AB524E338B8CE575051518CAD7729691D526FAA49B3E246550A4
            EF538CE4F618EFF4AFBF7FE0813FB092FED1BFB492FC42D7AD44DE13F8712A5C
            C28E014BCD488DD021047222FF005A7FDA58C74241FD80F037FC13EFE07FC35F
            2DB44F84FE00B19A2C6D9FFB0EDE59C639FF0058E85FF5AF56D2F42B4D12DA28
            2CE08AD6DE1E1228902469F450302BD5CBB845D1AD1AD5E69A8BBD92FBB5F53F
            2BF10BE95AB36C9F1195649849D29568F2FB49495E317A4AD149EAD5D27CCAD7
            BAD51612DD63DA416257B939CF14FA28AFB73F8D120650C30464547F675E0E49
            23BE066A4A28190BD846E003B80E73EE0F6FA506D56252CA5C0C63AFF9E95350
            46462815BB1F0E7FC15AFF00E0930DFF00050B7D0BC45E1DD7B4EF0F78CFC3D6
            9259A1BD859A0D4E02FBD2291D32D1947672AC15BFD630239047E327ED43FB05
            7C57FD8F3587B7F1DF84354D36CF7EC8B54854DCE9B724F40970994C9FEEB157
            E465457F4F6F6EB22904B73EFD2A96BBE1AB1F1168F7161A85ADB5FD95D218E6
            B7B985668A552305595810C08EC462BE6F35E1AA18C93AD16E137D7A3F97EBB9
            FD0BE18FD22B3EE13C353CAEB538E23090DA0FDD9C536DB519A4F4BBDA4A5D95
            91FC9898C8427E6E3BE723E94DE7D4FE75FBBFFB5FFF00C1BF7F087E3BC773A9
            F81BCDF865E2193E641609E76952367A35A923667A7EE9900CE76B6307F2EBF6
            BAFF008247FC6AFD8E96EAFB5AF0DBF883C376E377F6E683BAF2D117D655C096
            2EDCC88A327009AF85CC387F1984BCA51E68F7577F7F547F6EF01F8F1C23C50A
            34B0F88F635DFF00CBBAB68CAFDA2EFCB2D76516E5DD23E65E7D4FE7473EA7F3
            A7BC5B0B0C3657E9F9FAFE94CAF113BEC7ECC920E7D4FE7473EA7F3A28A6160E
            7D4FE7473EA7F3A28A02C1CFA9FCE8E7D4FE7451405839F53F9D1CFA9FCE8A28
            0B073EA7F3A39F53F9D1450160E7D4FE7473EA7F3A28A02C1CFA9FCE8E7D4FE7
            451405839F53F9D1CFA9FCE8A280B073EA7F3A39F53F9D1450160E7D4FE7473E
            A7F3A28A02C1CFA9FCE8E7D4FE7451405839F53F9D1CFA9FCE8A280B073EA7F3
            A39F53F9D1450160E7D4FE7473EA7F3A28A02C1CFA9FCE8E79196C9E9D4F3453
            A01999471C9EFD2930690E921299C06E99CEEE31EBFCC7A71D69871CE1BA7FB5
            9CD7EECFEC37F003F65EFF008286FEC47E0FD1E3F0C68DAEDFF83F48B4D27533
            245F62D734CBA58C06692588AC855DC3B2B64C6FF30ECCA3E6BFF8281FFC1BE3
            69F04FE13F89FC79F0BFC53AC6AB63E1CB46D426D0353B713DCB409CC862B88F
            687D8BB98298F24291B89C57D0D6E1AC4C68AC45192A91B5F4FEB53F9F726FA4
            570F56CE2790E6F4AAE0F111A9ECD2A91BC5BBDA3AC7E1E6D1FBC946CEFCCD1F
            973CFA9FCE8E7D4FE74E922319209191E873DFAFE87F4A6D7CF9FD05CA1CFA9F
            CE8E7D4FE7451405839F53F9D1CFA9FCE8A280B073EA7F3A39F53F9D1450160E
            7D4FE7473EA7F3A28A02C1CFA9FCE8E7D4FE7451405839F53F9D1CFA9FCE8A28
            0B073EA7F3A39F53F9D1401920609FA734059073EA7F3A002C703713E99EB4E8
            E2321C02092703AE0FE55F47FF00C13B3FE09B5E31FF0082807C4530694B2695
            E10D1E55FEDAD7A55C450024110C3FDF9D979006428219B8C06D70F42A57A8A8
            D24DB7D0F1F3ECFB2FC97015332CCEAAA54A9ABB949D9795BBB6F4495DB7A24D
            9CCFEC49FB0BF8D7F6F2F8B11F873C256BE5D9DB0171AA6AD3A9169A4C0CD8DC
            EC3EF31C30541F33907180ACCBFD15FECA3FB36786FF0064BF81FE1FF027862D
            FCAD3F43B708F332812DF4E72649E4F5776258FA0C0180000BFB2EFECBFE0EFD
            91FE1269BE0BF05698BA769163966763BAE2F6520069E67EAF2360727A000001
            4003D1D6155604678E95FAA64591C7010729BBD47BBEDE48FF0030FC69F1AB19
            C6F8B587A09D3C15277843AC9EDCF3F3B6D1D5453B5DBBB6EA28A2BDF3F0C0A2
            8A2800A28A2800A28A2800A475DEA4648CF70706968A006340AC4939049CF5C5
            06DD4FA807AF4E7DA9F452680F947F6ACFF82317C07FDABAEE5D46FF00C3B3F8
            475D9DC34BAA786648EC269F9C9F32328F03927AB3465CFF007ABE5CF18FFC1B
            05E10BB2FF00F08FFC56F1369C4FDD17FA4437D8FA947873FA57EA891B8107A1
            A6F92BDF2735E5E2725C15797354A6AFF77E47E9D9178CDC6D93D18E1F0198D4
            508ED1972CD2F25ED14ACBCB6F23F187C5FF00F06C278EACDDC787FE28784F53
            00FCA750D3E7B12793D4219B1C63D6BCBFC63FF06E9FED11E19DC2C97C0FE212
            0F1FD9FACB2161F4B88E2AFDED6855863240F6E29442063AF15E7D4E13CBE5B2
            6BD1BFD6E7DEE03E94DC7B42DED6AD3ABFE2A7157FFC0393F0B1FCF26A7FF041
            8FDA82C22468BE1FD9DF3375583C45A6A94FAEF9D6B3EE7FE0869FB535AC0D23
            7C2C7654E485F11692EDF805B924FE02BFA2BF2578E09C7BD288D41C81CD733E
            0EC1F49497CD7F91EF43E97BC6495A587C33FF00B72AFF00F2EFD0FE703FE1CC
            5FB4DE3FE493EAE3DFEDF6447E93735973FF00C1247F690B69DE36F845E2C668
            CE0948E2607E843907F3AFE948C2A460E4F39FA527920F52C6A7FD4BC27F3CBF
            0FF23AE1F4C1E2A5F1E0F0EFE5517FEE467F33BA97FC12E7F687D26658E6F83D
            E3A776191E469AF38FCD0102A86A1FF04DCF8FFA65B1964F833F132451D443E1
            DBA95873E8A849FC057F4E42303A134BB1720E00C543E0BC3F4A92FC0EBA7F4C
            5E2056E7C0517E8E6BF567F2F52FEC0BF1DA08D9DFE0AFC5A5451924F8435000
            7FE41AC9FF008642F8B3B883F0BFE222B29C153E1CBC0C0FD3CBAFEA70A82318
            C537C85E38C62A1F0552E955FDC8EB87D323375F165D4DFF00DBF25FA33F955B
            EFD9C3E2169770D0DD7813C656D3A7DE8A5D16E5197F34AA3AA7C19F17E891AB
            DEF853C4966ADD0CFA6CF1E7FEFA415FD5C7960003278A5F2C7E23BF7A87C130
            E959FDC8ECA7F4CAC62B73E5717E955AFCE0CFE4D2E7C11ACD940F2CDA46A70C
            518CB3BDBBAA8FC7159A13A03BB27B63047E75FD6E347B860B3114790A536900
            A9ED8A89704AE95BFF0025FF008274C3E99D3FB5947FE5C5BFF70B3F92160402
            7A01DFA81ED4282D8F42339E7FA8AFEB267F00E897533492E93A748ECC58B35B
            23127D72466A86A7F05FC1FAD4AAF7BE15F0E5E3A0C03369904847E256A1F04C
            BA55FC3FE09D90FA66516FDFCAA4BD2B27FF00B891FCA31538CE08FAF7A4C1F4
            27F3AFEAA751FD9A3E1CEB16E61BBF00F82EEA13D639744B6743DF9053079E6B
            3A4FD8DBE10CD1B23FC2CF872CADC107C356441FFC8750F82AAF4AABEE675D3F
            A64E5EFE3CB26BD2A45FFEDA8FE5A36E4020A95F5CF142A1DA095CE3AE0F4AFE
            A09BFE09FDF021B3BBE0AFC26258E493E10D3F27FF0020D665FF00FC134BF67D
            D46E5A593E0D7C37466EA22D02DA25FC9500A97C175FA548FDCCEB87D31B26BF
            BF97D55E9281FCC8AA0652402403F90A465006464FE47FAD7F4BDAA7FC12A3F6
            74D5D819BE0FF8290818C43642007EA10806B1F54FF82387ECCFABCE924DF097
            414283004371730AFE212500D43E0BC574A91FC7FC99DB4FE985C34FE3C1575E
            8A9BFF00DBD1FCDC80BFDE27079DAB9C0FCE908FAF2703D6BFA2FD57FE0875FB
            2DEB170259BE16C2AC06310EBDAA42BF925C81593A8FFC1047F65EBDB8DF1780
            AFECD48C1487C43A8153FF007DCCC7F5ACDF06E316D28BF9BFF23BA9FD2F783E
            5A4B0F895FF6E537FF00B9AE7F3D0A9B9B681B8E78208E7F0EB404C9207241EC
            7AD7F403A8FF00C1BDDFB35DFDC178F42F135A4671FBA875D98A7FE3DB8FEB58
            DA87FC1B8DFB3BDF5C33C7278FAD236FF9650EB31ED1F8B425BF5ACDF086397F
            2BF9BFF23BE9FD2CB8265A38D78FAD38FE937FD743F0604649550AC58E78E793
            D80E2BE88FF82707FC13C7C41FF0509F8D3FD8761712693E18D2A2175ADEB423
            F316CE239D8880E03CB21E157230016390A6BF54EC7FE0DB3FD9F6D3C4905FC9
            AAFC4BBAB68A4577D3E5D5ED85B4C07F0315B659403DF6C8A7DC57DA9F07BE02
            F83FF67EF05DB7877C15E1FD3BC37A2DA7DCB5B2882066E32EEDF79DCE396624
            9EE4D7665DC215BDB29629A515D16B7F9F43E3B8FF00E961967F664F0FC2B19B
            C44D594E71518D3FEF59DF9A4BECAB72DECDB6972BFC65FDA0BFE0DBAF8ADF0F
            926BAF01F88B40F1E5B2E4C76B27FC4B2FD875C6D919A2381D4F9A33D876AF89
            7E36FECBFF0010FF0066FD53EC7E3AF05F88FC2D333EC46BFB3648272064F972
            E0C720F75635FD4F1B6538CE6ABEB1E1FB2F10E9B3D95FDB417D6774A5268278
            D648A553FC2CAC0823D88AF5317C1F85A9AD09383FBD7F99F99F0AFD2DB89B05
            6A79D50862A3DD7EEE7F7C5383FF00C017A9FCB27C04FDA27C6BFB31F8F62F13
            F80BC437BE1AD7208DA21716F87478D8729223864913BED75201008E82BEFBFD
            8CFF00E0BD3F1BFE21FC60F06F80FC47A2783FC670F8B756B4D1A49DEC9ED2EC
            09E64859CF94C21DB87C91E5638E78AFD00F8CDFF0451FD9C7E366B4351BBF00
            5BE837A64124ADA0DC3E9B1CC01E54C519F2803DCAA06E7A83CD7A67C09FD813
            E0E7ECD31DBB7827E1EF86F46BDB5188F50FB28B9D417DFED32EF97D7F8BBD72
            E0387731C3D4E58D6B42FD2FAFC9E87D1F1D78F7E1F710E01D5C4E4F2AB8B716
            939C69C5C5DB4FDEC64E6D27AA497C933E2EF88FFF0006D47C38F18F8AB57D4F
            45F1D789BC3B6BA9DC4B716F60B6905CC1601DCB0893EE131A642A83CE00C927
            9AF11FDA0FFE0DA6F11F823E1FEA1AB7803C7D1F8CB57B28C491E8D77A5AD849
            76003B847379CCA5CF18465507A6EE457ECDFD9D78E4F07343DAA38C1C8F71D6
            BDCADC3797D4BFEEECDF54DFF9D8FC6B28FA4471F60274DAC7B9C20D7BB38539
            2925D1BE5E7B35BB5252ECEE7F265AF786EF7C2BAD5E69BAA5A5DE9DA8D84CF0
            5CDADCC4629ADE443B591D5B05594F04102A9142A06700FD6BFA69F8FF00FF00
            04D0F81DFB517C404F1578EBC01A76B5AFAC4207BC5BAB9B46B85030BE688244
            59481C0670C40000200C5724BFF045CFD9894823E13E9448F5D42F8FF39ABE52
            7C1789526A15135D2F7BFCF43FA7F03F4C2E1D78683C660ABAAB65CCA3ECDC54
            BAA52734DAECDC53F2EAFF009C200100056DDF9D0CA773280430EC7B7E95FD2A
            27FC1247F66E44551F087C26420C02D1C8C7F32D93F8D68D8FFC12EBF678D3ED
            9228FE0EF809923E9E66951CADFF007D3027F5A6B82F13D6A47F1154FA61F0F2
            5EE60ABBF5F66BFF006E67F332D8038041F7A30707835FD3B699FF0004E0F803
            A416317C18F862E1FA89FC35673FFE8719AD3B0FD837E076977493DAFC1AF853
            6D3C79DB245E12D3D1D72307044591C122AD70557EB517DCCE5A9F4C7C9D37C9
            97557EB282FF0033F9760093820FE54A50838D8C48EBDB15FD4D47FB207C2686
            4578FE187C3C8DD4E432F872CC11F8F975A89FB3C78050003C13E1100703FE24
            F6C3FF0064AA8F0555EB557DCCE49FD32701F632C9BF5AB15FFB633F95264DB8
            E18E7A7BD20438270723D307F0AFEB0ADFE17F86ED2DD228740D1A08A3FBAB1D
            944AABF805C568E9DE1FB2D1E364B4B582D519B7111461067E82B45C12FAD6FF
            00C97FE09C553E99B4D7C194B7EB5D2FFDC2CFE4DF47D06F3C41762DEC2CEEEF
            A762309042D231CF6C004E6BD7BE1FFF00C139BE3B7C4F9A35D1BE12F8F268E5
            236CD71A4CD690383DC4932A263DF35FD39F903D4F5CD06104100B007D2B6A5C
            154EFF00BCAADFA24BFCCF2330FA64E63385B0396420FF00BF52535F74610FCC
            FE7FFE1D7FC1BE5FB4778D954EA3A3F867C2658671AB6B31391CFA5AF9E7A763
            8AF77F877FF06C0EBD791A49E2CF8ADA4D8B0237C1A4E8F25E07F612492458FA
            9435FB126056CEE2581EC7914BE52818000C7E95E9D2E14CBE1F145BF57FE563
            F39CDBE94DC798BBAA1569D04FF929A7F8D47519F9DFF0E3FE0DB0F81DE1D78A
            6D7B5EF1FF0089264E1E37BEB7B4B67E3A6D8A2DE3FEFE57DD3F07FE0A785FE0
            1FC39D2FC25E10D22DB44F0FE8D17936B6B0E4851DD999896776249666259892
            4926BA758C21CE58D3ABD8C265D86C35DD0828DFEF3F23E26E3EE22E218C619D
            63275A31774A4FDD4FBA8AB46FAB57B5EDA0C480464105895E39A7D145769F20
            1451450014514500145145001451450014514500145145001451450014514500
            1451450014514500145145001451450014514500145145001451450014514500
            1451450014514500145145001451450014514500145145001451450014514500
            1451450014514500145145001451450014514500145145001451450014514500
            1451450014514500145145007FFFD9}
          HightQuality = False
        end
      end
      object PageHeader1: TfrxPageHeader
        Height = 35.188930000000000000
        Top = 18.897650000000000000
        Width = 812.598950000000000000
        object Memo2: TfrxMemoView
          Left = 672.000000000000000000
          Top = 13.291280000000000000
          Width = 166.488250000000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8W = (
            #31532'[Page#]'#39029#20849'[TotalPages#]'#39029)
          ParentFont = False
        end
      end
      object GroupHeader1: TfrxGroupHeader
        Height = 22.677180000000000000
        Top = 423.307360000000000000
        Width = 812.598950000000000000
      end
    end
  end
  object frxretail: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41052.608859328700000000
    ReportOptions.LastChange = 41052.608859328700000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    ShowProgress = False
    StoreInDFM = False
    Left = 168
    Top = 288
  end
  object frxReport1: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 42142.974423576380000000
    ReportOptions.LastChange = 42142.974423576380000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    Left = 40
    Top = 352
    Datasets = <>
    Variables = <>
    Style = <>
  end
  object frxWsalemuilprint: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41257.682618506900000000
    ReportOptions.LastChange = 42246.888146307870000000
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      ''
      '{'
      ''
      '}')
    StoreInDFM = False
    OnGetValue = frxWsalemuilprintGetValue
    Left = 576
    Top = 296
  end
  object queryA5: TADOQuery
    Parameters = <>
    Left = 624
    Top = 192
  end
  object queryA4: TADOQuery
    Parameters = <>
    Left = 632
    Top = 264
  end
  object frxReportA5: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41257.682618506900000000
    ReportOptions.LastChange = 41406.584407384260000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    StoreInDFM = False
    Left = 704
    Top = 160
  end
  object aqmuildetail: TADOQuery
    CursorType = ctStatic
    Parameters = <>
    Left = 728
    Top = 384
  end
  object aqmuilprinthead: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'id'
        Attributes = [paSigned]
        DataType = ftInteger
        Precision = 10
        Size = 4
        Value = Null
      end>
    SQL.Strings = (
      
        'select  a.id,a.totalamount,a.addcosts,a.fixedprice,right(a.remar' +
        'ks,16) ordercode,a.remarks,a.discountedprice,a.wsalentcodestr as' +
        ' wsalentcode,convert(varchar(10),a.hdtime,120) as hdtime,c.name ' +
        'as clientname,u.name as opname'
      ' from dbo.BS_WsaleNoteHeader a left join dbo.CUST_CustomerInfo c'
      'on a.vendorid = c.id left join sys_user u'
      'on a.operatorid = u.id'
      'where a.id=:id')
    Left = 648
    Top = 312
  end
  object frxmutildetail: TfrxDBDataset
    UserName = 'frxmutildetail'
    CloseDataSource = False
    DataSet = aqmuildetail
    Left = 680
    Top = 368
  end
  object frxdbwsalemuilprint: TfrxDBDataset
    UserName = 'frxdbwsalemuilprint'
    CloseDataSource = False
    DataSet = aqmuilprinthead
    Left = 736
    Top = 328
  end
  object adoqueryjianhuo: TADOQuery
    CursorType = ctStatic
    Parameters = <>
    Left = 368
    Top = 400
  end
  object frxreportjianhuo: TfrxReport
    Version = '4.7.18'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.AllowEdit = False
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = #39044#35774
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41257.682618506900000000
    ReportOptions.LastChange = 42157.701989120400000000
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      ''
      '{'
      ''
      '}')
    ShowProgress = False
    StoreInDFM = False
    Left = 408
    Top = 312
  end
  object frxDBDatasetjianhuo: TfrxDBDataset
    UserName = 'frxDBDatasetjianhuo'
    CloseDataSource = False
    DataSet = adoqueryjianhuo
    Left = 368
    Top = 360
  end
  object frxDBDatasetmiandan: TfrxDBDataset
    UserName = 'frxDBDatasetmiandan'
    CloseDataSource = False
    DataSet = adomiandan
    Left = 496
    Top = 352
  end
  object adomiandan: TADOQuery
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'ID'
        DataType = ftString
        Size = -1
        Value = Null
      end>
    Left = 504
    Top = 400
  end
  object frxDBDatasetxiaopiao: TfrxDBDataset
    UserName = 'frxDBDatasetxiaopiao'
    CloseDataSource = False
    DataSet = adoxiaopiao
    Left = 696
    Top = 216
  end
  object adoxiaopiao: TADOQuery
    Parameters = <>
    Left = 696
    Top = 256
  end
end
