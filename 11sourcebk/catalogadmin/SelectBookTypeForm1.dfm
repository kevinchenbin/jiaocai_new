inherited frmSelectBookType1: TfrmSelectBookType1
  Caption = #37197#32622'Excel'#25968#25454#28304
  ClientHeight = 236
  ClientWidth = 246
  Position = poScreenCenter
  ExplicitWidth = 252
  ExplicitHeight = 268
  PixelsPerInch = 96
  TextHeight = 13
  object lbl4: TLabel [0]
    Left = 4
    Top = 38
    Width = 54
    Height = 13
    Caption = 'EXCEL'#25991#20214
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object lbl3: TLabel [1]
    Left = 4
    Top = 65
    Width = 108
    Height = 13
    Caption = #35831#36873#25321#35201#23548#20837#30340#23383#27573
  end
  object lblExcel: TLabel [2]
    Left = 8
    Top = 215
    Width = 124
    Height = 13
    Caption = #23548#20837#27491#22312#36827#34892','#35831#31245#21518'...'
    Visible = False
  end
  inherited rztlbr2: TRzToolbar
    Width = 246
    ShowDivider = False
    BorderOuter = fsNone
    ExplicitWidth = 246
    ToolbarControls = (
      btnExit1
      btnExit2
      btnExit3)
    inherited btnExit1: TRzToolButton
      Width = 88
      Alignment = taLeftJustify
      Caption = #23548#20837#25968#25454#24211
      ExplicitWidth = 72
    end
    inherited btnExit2: TRzToolButton
      Left = 92
      Caption = ''
      Visible = False
      ExplicitLeft = 92
    end
    inherited btnExit3: TRzToolButton
      Left = 152
      Caption = ''
      Visible = False
      ExplicitLeft = 152
      ExplicitWidth = 60
    end
  end
  inherited Panel2: TPanel
    Width = 246
    Height = 207
    inherited Splitter1: TSplitter
      Height = 203
    end
    inherited RzDBGrid1: TRzDBGrid
      Left = 228
      Top = 244
      Visible = False
    end
    inherited tvbookclass: TTreeView
      Height = 203
    end
    inherited Panel3: TPanel
      Width = 80
      Height = 203
      inherited lbl1: TLabel
        Left = 115
        Top = 305
        Visible = False
        ExplicitLeft = 115
        ExplicitTop = 305
      end
      inherited lbl2: TLabel
        Left = 182
        Top = 305
        Visible = False
        ExplicitLeft = 182
        ExplicitTop = 305
      end
      inherited dbedtCode: TRzDBEdit
        Left = 140
        Top = 302
        ExplicitLeft = 140
        ExplicitTop = 302
      end
      inherited dbedtTypeName: TRzDBEdit
        Left = 164
        Top = 302
        ExplicitLeft = 164
        ExplicitTop = 302
      end
    end
  end
  object btn2: TButton [6]
    Left = 199
    Top = 34
    Width = 22
    Height = 25
    Caption = '...'
    TabOrder = 3
    OnClick = btn2Click
  end
  object edtExcelPath: TRzEdit [7]
    Left = 57
    Top = 32
    Width = 133
    Height = 21
    TabOrder = 5
  end
  object rdgrp1: TRzRadioGroup [8]
    Left = 4
    Top = 78
    Width = 193
    Height = 123
    TabOrder = 4
    VisualStyle = vsGradient
    object chckbxBarcode: TRzCheckBox
      Left = 16
      Top = 16
      Width = 43
      Height = 15
      Caption = #26465#30721
      State = cbUnchecked
      TabOrder = 0
    end
    object chckbxName: TRzCheckBox
      Left = 16
      Top = 37
      Width = 43
      Height = 15
      Caption = #20070#21517
      State = cbUnchecked
      TabOrder = 1
    end
    object chckbxUserDefCode: TRzCheckBox
      Left = 16
      Top = 58
      Width = 55
      Height = 15
      Caption = #33258#32534#21495
      State = cbUnchecked
      TabOrder = 2
    end
    object chckbxPress: TRzCheckBox
      Left = 16
      Top = 79
      Width = 55
      Height = 15
      Caption = #20986#29256#31038
      State = cbUnchecked
      TabOrder = 3
    end
    object chckbxISBN: TRzCheckBox
      Left = 107
      Top = 16
      Width = 42
      Height = 15
      Caption = 'ISBN'
      State = cbUnchecked
      TabOrder = 4
    end
    object chckbxAuthor: TRzCheckBox
      Left = 107
      Top = 37
      Width = 43
      Height = 15
      Caption = #20316#32773
      State = cbUnchecked
      TabOrder = 5
    end
    object chckbxPrice: TRzCheckBox
      Left = 107
      Top = 58
      Width = 43
      Height = 15
      Caption = #23450#20215
      State = cbUnchecked
      TabOrder = 6
    end
    object chckbxDate: TRzCheckBox
      Left = 107
      Top = 79
      Width = 67
      Height = 15
      Caption = #20986#29256#26085#26399
      State = cbUnchecked
      TabOrder = 7
    end
    object chckbxTotalAmount: TRzCheckBox
      Left = 16
      Top = 104
      Width = 43
      Height = 15
      Caption = #24211#23384
      State = cbUnchecked
      TabOrder = 8
    end
  end
  inherited dsource: TDataSource
    Left = 256
    Top = 260
  end
  inherited dsetBookType: TADODataSet
    Left = 304
    Top = 248
  end
  object opndlgExcelPath: TRzOpenDialog [13]
    Left = 184
    Top = 112
  end
  object con1: TADOConnection [14]
    LoginPrompt = False
    Mode = cmRead
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 120
    Top = 64
  end
  object qry1: TADOQuery [15]
    Parameters = <>
    Left = 192
    Top = 64
  end
  object ds1: TDataSource [16]
    Left = 88
    Top = 64
  end
  object dset1: TADODataSet [17]
    ConnectionString = 
      'Provider=SQLOLEDB.1;Password=123456;Persist Security Info=True;U' +
      'ser ID=sa;Initial Catalog=book;Data Source=pddata\sql2005'
    CommandText = 
      'select ID, PressID,ISBN, Name, Price, Barcode, UserDefCode, Date' +
      ', Author, PressCount, Unavailable, bigBookTypeID, smallBookTypeI' +
      'D, TotalAmount, PresentNum, AbbreviatedName, FullName from UV_Pr' +
      'essAndBookCatalogQuery'
    Parameters = <>
    Left = 168
    Top = 48
  end
end
