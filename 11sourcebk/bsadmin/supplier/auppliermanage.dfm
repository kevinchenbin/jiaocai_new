object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 247
  ClientWidth = 480
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 40
    Top = 48
    Width = 75
    Height = 25
    Caption = #20379#24212#21830
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 40
    Top = 136
    Width = 75
    Height = 25
    Caption = #23458#25143
    TabOrder = 1
    OnClick = Button2Click
  end
  object cnn: TADOConnection
    ConnectionString = 
      'Provider=SQLOLEDB.1;Password=123456;Persist Security Info=True;U' +
      'ser ID=sa;Initial Catalog=book;Data Source=PDDATA'
    LoginPrompt = False
    Provider = 'SQLOLEDB.1'
    Left = 336
    Top = 80
  end
end
