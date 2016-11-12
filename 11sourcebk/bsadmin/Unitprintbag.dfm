object frmprintbag: Tfrmprintbag
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #21333#20070#25171#21253#35774#32622
  ClientHeight = 409
  ClientWidth = 360
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 360
    Height = 409
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object DBGrid1: TDBGrid
      Left = 0
      Top = 6
      Width = 344
      Height = 330
      DataSource = ds
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'name'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #20070#21517
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'Amount'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #21457#36135#25968#37327
          Width = 55
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'BookWords'
          ReadOnly = True
          Title.Alignment = taCenter
          Title.Caption = #20876'/'#21253
          Width = 37
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'printbag'
          Title.Alignment = taCenter
          Title.Caption = #27599#21253#20876#25968
          Width = 55
          Visible = True
        end>
    end
    object RzButton1: TRzButton
      Left = 262
      Top = 342
      Caption = #30830#23450
      TabOrder = 1
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 262
      Top = 373
      Caption = #21462#28040
      TabOrder = 2
      OnClick = RzButton2Click
    end
    object RzButton3: TRzButton
      Tag = 1
      Left = 16
      Top = 342
      Caption = #25171#21253#21333#39044#35272
      TabOrder = 3
      OnClick = RzButton3Click
    end
    object RzButton4: TRzButton
      Tag = 2
      Left = 16
      Top = 373
      Caption = #25171#21360#25171#21253#21333
      TabOrder = 4
      OnClick = RzButton3Click
    end
    object RzButton5: TRzButton
      Tag = 1
      Left = 112
      Top = 342
      Width = 97
      Caption = #31934#31616#25171#21253#21333#39044#35272
      TabOrder = 5
      OnClick = RzButton5Click
    end
    object RzButton6: TRzButton
      Tag = 2
      Left = 112
      Top = 373
      Width = 97
      Caption = #31934#31616#25171#21360#25171#21253#21333
      TabOrder = 6
      OnClick = RzButton5Click
    end
  end
  object fcon: TADOConnection
    Left = 320
    Top = 40
  end
  object ImageList1: TImageList
    Left = 320
    Top = 88
    Bitmap = {
      494C010102000800380010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      9900000099000000990000009900000099000000990000009900000099000000
      9900000099000000000000000000000000000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099000000
      CC000000CC000000CC000000CC000000CC00000099000000CC00000099000000
      990000009900000099000000000000000000000000000000000099999900B2B2
      B200B2B2B200B2B2B200B2B2B200B2B2B20099999900B2B2B200999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099000000
      FF000000CC000000CC000000CC000000CC000000CC00000099000000CC000000
      990000009900000099000000000000000000000000000000000099999900CCCC
      CC00B2B2B200B2B2B200B2B2B200B2B2B200B2B2B20099999900B2B2B2009999
      9900999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099000000
      CC000000FF000000CC000000CC000000CC000000CC000000CC00000099000000
      CC0000009900000099000000000000000000000000000000000099999900B2B2
      B200CCCCCC00B2B2B200B2B2B200B2B2B200B2B2B200B2B2B20099999900B2B2
      B200999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099000000
      FF000000CC000000FF000000CC000000CC000000CC000000CC000000CC000000
      99000000CC00000099000000000000000000000000000000000099999900CCCC
      CC00B2B2B200CCCCCC00B2B2B200B2B2B200B2B2B200B2B2B200B2B2B2009999
      9900B2B2B2009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099000000
      FF000000FF000000CC000000FF000000CC000000CC000000CC000000CC000000
      CC0000009900000099000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00B2B2B200CCCCCC00B2B2B200B2B2B200B2B2B200B2B2B200B2B2
      B200999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099009999
      FF000000FF000000FF000000CC000000FF000000CC000000CC000000CC000000
      CC000000CC00000099000000000000000000000000000000000099999900E5E5
      E500CCCCCC00CCCCCC00B2B2B200CCCCCC00B2B2B200B2B2B200B2B2B200B2B2
      B200B2B2B2009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000099009999
      FF009999FF000000FF000000FF000000CC000000FF000000CC000000CC000000
      CC000000CC00000099000000000000000000000000000000000099999900E5E5
      E500E5E5E500CCCCCC00CCCCCC00B2B2B200CCCCCC00B2B2B200B2B2B200B2B2
      B200B2B2B2009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      9900000099000000990000009900000099000000990000009900000099000000
      9900000099000000000000000000000000000000000000000000000000009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFF00000000FFFFFFFF00000000
      FFFFFFFF00000000FFFFFFFF00000000E007E00700000000C003C00300000000
      C003C00300000000C003C00300000000C003C00300000000C003C00300000000
      C003C00300000000C003C00300000000E007E00700000000FFFFFFFF00000000
      FFFFFFFF00000000FFFFFFFF0000000000000000000000000000000000000000
      000000000000}
  end
  object query: TADOQuery
    Parameters = <>
    Left = 256
    Top = 48
  end
  object ds: TDataSource
    DataSet = query
    Left = 120
    Top = 152
  end
  object spdabao: TADOStoredProc
    ProcedureName = 'DaBaoA'
    Parameters = <
      item
        Name = '@DanHaoID'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@CatalogiD'
        DataType = ftString
        Size = -1
        Value = Null
      end
      item
        Name = '@xuhaostr'
        DataType = ftString
        Size = -1
        Value = Null
      end
      item
        Name = '@wsids'
        DataType = ftString
        Size = -1
        Value = Null
      end
      item
        Name = '@userid'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@stgid'
        DataType = ftInteger
        Value = Null
      end>
    Left = 56
    Top = 232
  end
  object rp: TRvProject
    Engine = rs
    Left = 312
    Top = 280
  end
  object rv: TRvDataSetConnection
    RuntimeVisibility = rtDeveloper
    Left = 192
    Top = 280
  end
  object querydabao: TADOQuery
    AutoCalcFields = False
    CursorType = ctStatic
    Parameters = <>
    Left = 272
    Top = 224
  end
  object rs: TRvSystem
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
    Top = 280
  end
  object frxpbag1: TfrxReport
    Version = '4.7.147'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 38006.786384259300000000
    ReportOptions.LastChange = 40612.669043229170000000
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      ''
      '{'
      ''
      '}')
    Left = 152
    Top = 216
    Datasets = <
      item
        DataSet = frxdbpbag
        DataSetName = 'frxdbpbag'
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
      LeftMargin = 5.000000000000000000
      RightMargin = 5.000000000000000000
      TopMargin = 10.000000000000000000
      BottomMargin = 10.000000000000000000
      Columns = 1
      ColumnWidth = 200.000000000000000000
      ColumnPositions.Strings = (
        '0')
      Duplex = dmHorizontal
      ResetPageNumbers = True
      object MasterData1: TfrxMasterData
        Height = 215.433210000000000000
        Top = 18.897650000000000000
        Width = 755.906000000000000000
        Columns = 3
        ColumnWidth = 252.094488188976000000
        DataSet = frxdbpbag
        DataSetName = 'frxdbpbag'
        RowCount = 0
        object Line2: TfrxLineView
          Left = 4.779532440000000000
          Top = 3.779527559055120000
          Height = 200.315090000000000000
          ShowHint = False
          Diagonal = True
        end
        object Line3: TfrxLineView
          Left = 243.755905511811000000
          Top = 3.779527560000000000
          Height = 200.315090000000000000
          ShowHint = False
          Diagonal = True
        end
        object Memo14: TfrxMemoView
          Left = 5.779530000000000000
          Top = 30.236220470000000000
          Width = 238.110236220472000000
          Height = 37.795275590000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #20070#21517#65306'[frxdbpbag."bookname"]')
          ParentFont = False
        end
        object Memo15: TfrxMemoView
          Left = 5.779530000000000000
          Top = 71.811023620000000000
          Width = 117.165354330000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #21333#20215#65306'[frxdbpbag."price"]')
          ParentFont = False
        end
        object Memo16: TfrxMemoView
          Left = 122.944884330000000000
          Top = 71.811023620000000000
          Width = 120.944881889764000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #24207#21495#65306'[frxdbpbag."xuhao"]')
          ParentFont = False
        end
        object Memo17: TfrxMemoView
          Left = 5.779530000000000000
          Top = 94.488188980000000000
          Width = 117.165354330000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #20316#32773#65306'[frxdbpbag."author"]')
          ParentFont = False
          WordWrap = False
        end
        object Memo18: TfrxMemoView
          Left = 122.944884330000000000
          Top = 94.488250000000000000
          Width = 120.944881889764000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            '[frxdbpbag."changvalue"]')
          ParentFont = False
        end
        object Memo19: TfrxMemoView
          Left = 5.779530000000000000
          Top = 117.165354330000000000
          Width = 238.110236220472000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #25968#37327#65306'[frxdbpbag."amount"]')
          ParentFont = False
        end
        object Memo20: TfrxMemoView
          Left = 5.779530000000000000
          Top = 139.842519690000000000
          Width = 79.370078740000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #26412#20214#65306'[frxdbpbag."bengjian"]')
          ParentFont = False
        end
        object Memo21: TfrxMemoView
          Left = 85.149608740000000000
          Top = 139.842519690000000000
          Width = 79.370078740000000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #21253#21495#65306'[frxdbpbag."baohao"]')
          ParentFont = False
        end
        object Memo22: TfrxMemoView
          Left = 164.519687480000000000
          Top = 139.842519690000000000
          Width = 79.370078740157500000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #29256#27425#65306'[frxdbpbag."press"]')
          ParentFont = False
        end
        object Memo23: TfrxMemoView
          Left = 5.779530000000000000
          Top = 162.519685040000000000
          Width = 238.110236220472000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #20986#29256#31038#65306'[frxdbpbag."pressname"]')
          ParentFont = False
        end
        object Memo24: TfrxMemoView
          Left = 5.779530000000000000
          Top = 185.196850390000000000
          Width = 238.110236220472000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #20379#24212#21830#65306'[frxdbpbag."supplier"]')
          ParentFont = False
        end
        object Memo13: TfrxMemoView
          Left = 5.779532440000000000
          Top = 7.559060000000000000
          Width = 238.110236220472000000
          Height = 18.897650000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #25910#36135#21333#20301#65306'[frxdbpbag."receiver"]')
          ParentFont = False
        end
        object Line1: TfrxLineView
          Left = 5.779530000000000000
          Top = 3.779530000000000000
          Width = 238.110236220472000000
          ShowHint = False
          Diagonal = True
        end
        object Line4: TfrxLineView
          Left = 122.944960000000000000
          Top = 68.031540000000000000
          Height = 45.354360000000000000
          ShowHint = False
          Diagonal = True
        end
        object Line5: TfrxLineView
          Left = 85.149660000000000000
          Top = 136.063080000000000000
          Height = 22.677165354330700000
          ShowHint = False
          Diagonal = True
        end
        object Line6: TfrxLineView
          Left = 164.519790000000000000
          Top = 136.063080000000000000
          Height = 22.677180000000000000
          ShowHint = False
          Diagonal = True
        end
      end
    end
  end
  object frxdbpbag: TfrxDBDataset
    UserName = 'frxdbpbag'
    CloseDataSource = False
    BCDToCurrency = False
    Left = 248
    Top = 160
  end
  object frxpbag: TfrxReport
    Version = '4.7.147'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 40612.668684201400000000
    ReportOptions.LastChange = 40739.742398622690000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    Left = 240
    Top = 272
    Datasets = <
      item
        DataSet = frxdbpbag
        DataSetName = 'frxdbpbag'
      end>
    Variables = <>
    Style = <>
    object Data: TfrxDataPage
      Height = 1000.000000000000000000
      Width = 1000.000000000000000000
    end
    object Page1: TfrxReportPage
      Orientation = poLandscape
      PaperWidth = 297.000000000000000000
      PaperHeight = 210.000000000000000000
      PaperSize = 9
      LeftMargin = 10.000000000000000000
      RightMargin = 10.000000000000000000
      TopMargin = 10.000000000000000000
      BottomMargin = 10.000000000000000000
      Duplex = dmVertical
      object MasterData1: TfrxMasterData
        Height = 230.551330000000000000
        Top = 18.897650000000000000
        Width = 1046.929810000000000000
        Columns = 3
        ColumnWidth = 340.157480314961000000
        DataSet = frxdbpbag
        DataSetName = 'frxdbpbag'
        RowCount = 0
        object Memo1: TfrxMemoView
          Left = 3.779527560000000000
          Top = 5.228351340000000000
          Width = 328.818953780000000000
          Height = 26.456710000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #20869#37096#35782#21035#30721#65306'[frxdbpbag."incode"]')
          ParentFont = False
        end
        object Memo2: TfrxMemoView
          Left = 3.779527560000000000
          Top = 45.354342910000000000
          Width = 328.819110000000000000
          Height = 98.267755590000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #20070#21517#65306'[frxdbpbag."bookname"]')
          ParentFont = False
        end
        object Memo3: TfrxMemoView
          Left = 3.779527560000000000
          Top = 189.866219840000000000
          Width = 328.819005040000000000
          Height = 26.456710000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #21333#20215#65306'[frxdbpbag."price"]')
          ParentFont = False
        end
        object Memo7: TfrxMemoView
          Left = 3.779530000000000000
          Top = 150.291358110000000000
          Width = 328.818953780000000000
          Height = 30.236240000000000000
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftBottom]
          Memo.UTF8W = (
            #25968#37327#65306'[frxdbpbag."bengjian"]')
          ParentFont = False
        end
        object Line1: TfrxLineView
          Left = 3.779530000000000000
          Width = 328.818897637795000000
          ShowHint = False
          Diagonal = True
        end
        object Line3: TfrxLineView
          Left = 332.598640000000000000
          Height = 215.433210000000000000
          ShowHint = False
          Diagonal = True
        end
        object Line2: TfrxLineView
          Left = 3.779530000000000000
          Height = 215.433210000000000000
          ShowHint = False
          Diagonal = True
        end
      end
    end
  end
end
