object frmInform: TfrmInform
  Left = 618
  Top = 0
  BorderIcons = []
  Caption = 'frmInform'
  ClientHeight = 340
  ClientWidth = 418
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDesigned
  Visible = True
  OnCanResize = FormCanResize
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object dg: TRzDBGrid
    Left = 8
    Top = 8
    Width = 401
    Height = 321
    Cursor = crHandPoint
    BorderStyle = bsNone
    Ctl3D = False
    DataSource = ds
    DefaultDrawing = False
    FixedColor = clSilver
    Font.Charset = ANSI_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Options = [dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentCtl3D = False
    ParentFont = False
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnCellClick = dgCellClick
    OnDrawColumnCell = dgDrawColumnCell
    FrameColor = clBlue
    FrameControllerNotifications = [fcpColor, fcpFocusColor, fcpDisabledColor, fcpReadOnlyColor, fcpReadOnlyColorOnFocus, fcpParentColor, fcpFlatButtonColor, fcpFlatButtons, fcpFrameColor, fcpFrameHotColor, fcpFrameHotTrack, fcpFrameHotStyle, fcpFrameSides, fcpFrameVisible, fcpFramingPreference]
    FixedLineColor = clBlue
    Columns = <
      item
        Expanded = False
        FieldName = 'state'
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Message'
        Width = 350
        Visible = True
      end>
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 8
    Top = 72
  end
  object Timer2: TTimer
    Interval = 100
    OnTimer = Timer2Timer
    Left = 16
    Top = 152
  end
  object RzBalloonHints1: TRzBalloonHints
    Bitmaps.TransparentColor = clOlive
    CenterThreshold = 0
    FrameColor = cl3DDkShadow
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clInfoText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Left = 16
    Top = 192
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 272
    Top = 280
  end
  object ds: TDataSource
    DataSet = aq
    Left = 184
    Top = 360
  end
  object ImageList1: TImageList
    Left = 344
    Top = 240
    Bitmap = {
      494C010101000500040010001000FFFFFFFFFF00FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF003333FF00FFFFFF00FFFFFF006666FF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF009999
      FF009999FF009999FF000000FF003333FF003333FF000000FF006666FF009999
      FF006666FF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF006666
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF003333FF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF009999FF009999FF006666
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF003333FF009999FF009999FF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF006666FF000000FF000000
      FF006666FF006666FF000000FF006666FF003333FF000000FF006666FF006666
      FF000000FF000000FF006666FF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00CCCCFF000000FF000000
      FF00FFFFFF00FFFFFF000000FF00FFFFFF006666FF003333FF00CCCCFF00FFFF
      FF000000FF000000FF00CCCCFF00CCCCFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000006666FF000000FF000000FF000000
      FF00FFFFFF00FFFFFF000000FF00FFFFFF006666FF003333FF00FFFFFF00FFFF
      FF000000FF000000FF000000FF003333FF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF006666FF000000FF000000
      FF00FFFFFF00FFFFFF000000FF00FFFFFF009999FF003333FF00CCCCFF00CCCC
      FF003333FF000000FF006666FF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF006666FF000000FF000000
      FF00FFFFFF00FFFFFF000000FF00FFFFFF009999FF003333FF00CCCCFF00CCCC
      FF003333FF000000FF006666FF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF006666FF000000FF000000
      FF00CCCCFF00CCCCFF000000FF00FFFFFF003333FF003333FF009999FF006666
      FF009999FF000000FF003333FF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009999FF003333FF003333FF000000
      FF009999FF006666FF003333FF00FFFFFF00CCCCFF003333FF009999FF006666
      FF00FFFFFF000000FF003333FF009999FF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CCCCFF00FFFFFF009999FF000000
      FF003333FF000000FF000000FF006666FF006666FF000000FF003333FF000000
      FF006666FF006666FF00FFFFFF00CCCCFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF006666FF003333
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF003333
      FF000000FF003333FF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF009999FF00CCCC
      FF00CCCCFF000000FF003333FF000000FF000000FF000000FF000000FF00CCCC
      FF00CCCCFF009999FF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF006666FF00CCCCFF003333FF000000FF00CCCCFF006666FF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00CCCCFF009999FF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000}
  end
  object Timer3: TTimer
    Interval = 100000
    Left = 16
    Top = 280
  end
  object adosp: TADOStoredProc
    ProcedureName = 'UpdateMessageState'
    Parameters = <
      item
        Name = '@ID'
        DataType = ftInteger
        Value = Null
      end>
    Left = 416
    Top = 224
  end
end