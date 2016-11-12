object frmnewtask: Tfrmnewtask
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'frmnewtask'
  ClientHeight = 365
  ClientWidth = 406
  Color = 16180174
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 32
    Top = 24
    Width = 36
    Height = 13
    Caption = #24067#32622#20154
  end
  object Label2: TLabel
    Left = 32
    Top = 56
    Width = 36
    Height = 13
    Caption = #25191#34892#20154
  end
  object Label3: TLabel
    Left = 20
    Top = 88
    Width = 48
    Height = 13
    Caption = #24320#22987#26085#26399
  end
  object Label4: TLabel
    Left = 227
    Top = 88
    Width = 48
    Height = 13
    Caption = #32467#26463#26085#26399
  end
  object Label5: TLabel
    Left = 20
    Top = 185
    Width = 48
    Height = 13
    Caption = #20219#21153#20869#23481
  end
  object Label6: TLabel
    Left = 44
    Top = 305
    Width = 24
    Height = 13
    Caption = #38468#20214
  end
  object SpeedButton1: TSpeedButton
    Left = 352
    Top = 302
    Width = 33
    Height = 22
    Caption = #19978#20256
    Flat = True
    OnClick = SpeedButton1Click
  end
  object Label7: TLabel
    Left = 44
    Top = 146
    Width = 24
    Height = 13
    Caption = #20027#39064
  end
  object SpeedButton2: TSpeedButton
    Left = 247
    Top = 332
    Width = 66
    Height = 25
    Caption = #20445#23384
    OnClick = SpeedButton2Click
  end
  object SpeedButton3: TSpeedButton
    Left = 327
    Top = 332
    Width = 58
    Height = 25
    Caption = #25918#24323
    OnClick = SpeedButton3Click
  end
  object SpeedButton4: TSpeedButton
    Left = 360
    Top = 54
    Width = 25
    Height = 21
    Caption = #36873#25321
    Flat = True
    OnClick = SpeedButton4Click
  end
  object Label8: TLabel
    Left = 44
    Top = 119
    Width = 24
    Height = 13
    Caption = #29366#24577
  end
  object edituser: TEdit
    Left = 74
    Top = 21
    Width = 311
    Height = 21
    ReadOnly = True
    TabOrder = 0
  end
  object editreceiver: TEdit
    Left = 74
    Top = 53
    Width = 286
    Height = 21
    ReadOnly = True
    TabOrder = 1
  end
  object memcontent: TMemo
    Left = 74
    Top = 175
    Width = 314
    Height = 113
    TabOrder = 2
  end
  object editattchment: TEdit
    Left = 74
    Top = 302
    Width = 280
    Height = 21
    ReadOnly = True
    TabOrder = 3
  end
  object edittitle: TEdit
    Left = 74
    Top = 141
    Width = 313
    Height = 21
    TabOrder = 4
  end
  object DateTimePicker1: TDateTimePicker
    Left = 74
    Top = 84
    Width = 103
    Height = 21
    Date = 40296.782309560190000000
    Time = 40296.782309560190000000
    TabOrder = 5
  end
  object DateTimePicker2: TDateTimePicker
    Left = 282
    Top = 84
    Width = 103
    Height = 21
    Date = 40296.782550995370000000
    Time = 40296.782550995370000000
    TabOrder = 6
  end
  object cbstate: TComboBox
    Left = 74
    Top = 114
    Width = 311
    Height = 21
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 7
    Text = #25191#34892#20013
    Items.Strings = (
      #25191#34892#20013
      #23436#25104#20219#21153
      #26410#23436#25104#20219#21153)
  end
  object openfile: TRzOpenDialog
    Options = [osoFileMustExist, osoHideReadOnly, osoPathMustExist, osoAllowTree, osoShowHints, osoOleDrag, osoOleDrop, osoShowHidden]
    Left = 120
    Top = 312
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 8
    Top = 296
  end
  object newtask: TADOStoredProc
    ProcedureName = 'CreateTask'
    Parameters = <
      item
        Name = '@creater'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@contenta'
        DataType = ftString
        Size = -1
        Value = Null
      end
      item
        Name = '@title'
        DataType = ftString
        Size = -1
        Value = Null
      end
      item
        Name = '@taskbegin'
        DataType = ftDateTime
        Value = Null
      end
      item
        Name = '@taskend'
        DataType = ftDateTime
        Value = Null
      end
      item
        Name = '@state'
        DataType = ftString
        Size = 50
        Value = Null
      end
      item
        Name = '@attachmentname'
        DataType = ftString
        Size = -1
        Value = Null
      end
      item
        Name = '@attachment'
        Attributes = [paNullable]
        DataType = ftBlob
        Size = 16
        Value = Null
      end
      item
        Name = '@Modal'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@TaskIDStr'
        DataType = ftString
        Direction = pdOutput
        Size = -1
        Value = Null
      end>
    Prepared = True
    Left = 40
    Top = 240
  end
  object SendMsgReceiver: TADOStoredProc
    ProcedureName = 'SendMsgToReceiver'
    Parameters = <
      item
        Name = '@string'
        DataType = ftString
        Size = -1
        Value = Null
      end
      item
        Name = '@Model'
        DataType = ftInteger
        Value = Null
      end
      item
        Name = '@TaskID'
        DataType = ftString
        Size = -1
        Value = Null
      end>
    Left = 56
    Top = 304
  end
  object savefile: TSaveDialog
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Left = 200
    Top = 312
  end
end
