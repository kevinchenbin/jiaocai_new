inherited frmSelectCustomer: TfrmSelectCustomer
  Caption = #36873#25321#20379#24212#21830
  ClientHeight = 286
  ClientWidth = 451
  OnClose = FormClose
  OnShow = FormShow
  ExplicitWidth = 457
  ExplicitHeight = 318
  PixelsPerInch = 96
  TextHeight = 13
  object RzLabel1: TRzLabel [0]
    Left = 8
    Top = 16
    Width = 48
    Height = 13
    Caption = #23458#25143#21517#31216
    BlinkIntervalOff = 600
    BlinkIntervalOn = 600
  end
  inherited Panel2: TPanel
    Width = 451
    Height = 286
    ExplicitWidth = 194
    ExplicitHeight = 206
    inherited btnOk: TRzButton
      Left = 287
      Top = 253
      ExplicitLeft = 30
      ExplicitTop = 173
    end
    inherited btnCancel: TRzButton
      Left = 368
      Top = 253
      ExplicitLeft = 111
      ExplicitTop = 173
    end
  end
  object edtName: TRzEdit
    Left = 62
    Top = 13
    Width = 124
    Height = 21
    TabOrder = 2
    OnKeyPress = edtNameKeyPress
  end
  object dbgrdCustomer: TRzDBGrid
    Left = 8
    Top = 56
    Width = 178
    DataSource = dsrcCustomer
    DefaultDrawing = True
    Options = [dgTitles, dgIndicator, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnCellClick = dbgrdCustomerCellClick
    OnDblClick = dbgrdCustomerDblClick
    Columns = <
      item
        Expanded = False
        FieldName = 'Name'
        Title.Caption = #23458#25143#21517#31216
        Width = 159
        Visible = True
      end>
  end
  object qryCustomer: TADOQuery
    Parameters = <>
    Left = 8
    Top = 168
  end
  object dsrcCustomer: TDataSource
    DataSet = qryCustomer
    Left = 72
    Top = 112
  end
end
