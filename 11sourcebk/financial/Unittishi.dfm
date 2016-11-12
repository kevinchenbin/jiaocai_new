object frmtishi: Tfrmtishi
  Left = 0
  Top = 0
  ClientHeight = 199
  ClientWidth = 447
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
    Width = 447
    Height = 199
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    ExplicitHeight = 202
    object btok: TRzButton
      Left = 360
      Top = 159
      Caption = #30830#23450
      TabOrder = 0
      OnClick = btokClick
    end
    object rg: TRadioGroup
      Left = 16
      Top = 144
      Width = 185
      Height = 40
      Columns = 2
      ItemIndex = 0
      Items.Strings = (
        #19981#32418#20914
        #32418#20914)
      TabOrder = 1
    end
    object cbts: TCheckBox
      Left = 224
      Top = 164
      Width = 97
      Height = 17
      Caption = #20197#21518#19981#20877#25552#31034
      TabOrder = 2
    end
    object GroupBox1: TGroupBox
      Left = 16
      Top = 11
      Width = 419
      Height = 127
      TabOrder = 3
      object Label1: TLabel
        Left = 9
        Top = 16
        Width = 24
        Height = 13
        Caption = #21333#21495
      end
      object Label2: TLabel
        Left = 157
        Top = 16
        Width = 24
        Height = 13
        Caption = #30721#27915
      end
      object Label3: TLabel
        Left = 288
        Top = 16
        Width = 24
        Height = 13
        Caption = #23454#27915
      end
      object Label4: TLabel
        Left = 157
        Top = 45
        Width = 24
        Height = 13
        Caption = #26410#32467
      end
      object Label5: TLabel
        Left = 288
        Top = 45
        Width = 24
        Height = 13
        Caption = #32418#20914
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label6: TLabel
        Left = 9
        Top = 45
        Width = 24
        Height = 13
        Caption = #24050#32467
      end
      object Label7: TLabel
        Left = 9
        Top = 72
        Width = 24
        Height = 13
        Caption = #22791#27880
      end
      object edcode: TEdit
        Left = 39
        Top = 13
        Width = 106
        Height = 21
        Enabled = False
        TabOrder = 0
      end
      object edmy: TEdit
        Left = 187
        Top = 13
        Width = 95
        Height = 21
        Enabled = False
        TabOrder = 1
      end
      object edsy: TEdit
        Left = 318
        Top = 13
        Width = 95
        Height = 21
        Enabled = False
        TabOrder = 2
      end
      object edwj: TEdit
        Left = 187
        Top = 42
        Width = 95
        Height = 21
        Enabled = False
        TabOrder = 3
      end
      object edhc: TEdit
        Left = 318
        Top = 42
        Width = 95
        Height = 21
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
      end
      object edyj: TEdit
        Left = 39
        Top = 42
        Width = 106
        Height = 21
        Enabled = False
        TabOrder = 5
      end
      object membk: TMemo
        Left = 39
        Top = 69
        Width = 374
        Height = 50
        Enabled = False
        TabOrder = 6
      end
    end
  end
end
