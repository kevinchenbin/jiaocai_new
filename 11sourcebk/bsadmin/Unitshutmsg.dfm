object frmshortmessage: Tfrmshortmessage
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #30701#20449#36890#30693#27169#26495
  ClientHeight = 270
  ClientWidth = 373
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
    Width = 373
    Height = 270
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    ExplicitLeft = 88
    ExplicitTop = 112
    ExplicitWidth = 185
    ExplicitHeight = 41
    object PageControl1: TPageControl
      Left = 8
      Top = 16
      Width = 353
      Height = 209
      ActivePage = TabSheet1
      TabOrder = 0
      object TabSheet1: TTabSheet
        Caption = 'C'#32593#23458#25143
        ExplicitWidth = 281
        ExplicitHeight = 165
        object memo1: TMemo
          Left = 0
          Top = 3
          Width = 329
          Height = 166
          Lines.Strings = (
            '')
          ScrollBars = ssVertical
          TabOrder = 0
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'B'#32593#23458#25143
        ImageIndex = 1
        ExplicitLeft = -44
        ExplicitTop = -8
        ExplicitWidth = 281
        ExplicitHeight = 165
        object Memo2: TMemo
          Left = 3
          Top = 3
          Width = 329
          Height = 166
          TabOrder = 0
        end
      end
    end
    object bsave: TButton
      Left = 184
      Top = 231
      Width = 75
      Height = 25
      Caption = #20445#23384
      ModalResult = 1
      TabOrder = 1
    end
    object Button2: TButton
      Left = 282
      Top = 231
      Width = 75
      Height = 25
      Caption = #21462#28040
      ModalResult = 2
      TabOrder = 2
    end
  end
end