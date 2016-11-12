object frmprinttitle: Tfrmprinttitle
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #25171#21360#20449#24687#35774#32622
  ClientHeight = 246
  ClientWidth = 565
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poMainFormCenter
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 565
    Height = 246
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    object PageControl1: TPageControl
      Left = 2
      Top = 8
      Width = 561
      Height = 236
      ActivePage = taborder
      Align = alBottom
      TabOrder = 0
      object taborder: TTabSheet
        Caption = #35746#21333
        object GroupBox2: TGroupBox
          Left = 1
          Top = 5
          Width = 537
          Height = 120
          Caption = #35746#21333#20449#24687
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 0
          object Label6: TLabel
            Left = 8
            Top = 16
            Width = 48
            Height = 13
            Caption = #21333#25454#25260#22836
          end
          object Label7: TLabel
            Left = 32
            Top = 70
            Width = 24
            Height = 13
            Caption = #22320#22336
          end
          object Label8: TLabel
            Left = 20
            Top = 43
            Width = 36
            Height = 13
            Caption = #32852#31995#20154
          end
          object Label9: TLabel
            Left = 306
            Top = 43
            Width = 24
            Height = 13
            Caption = #30005#35805
          end
          object Label4: TLabel
            Left = 8
            Top = 97
            Width = 72
            Height = 13
            Caption = #35746#21333#25171#21360#22791#27880
          end
          object edorprintbk: TEdit
            Left = 86
            Top = 94
            Width = 434
            Height = 21
            TabOrder = 0
          end
          object edorprinttitle: TEdit
            Left = 62
            Top = 13
            Width = 458
            Height = 21
            TabOrder = 1
          end
          object edoraddress: TEdit
            Left = 62
            Top = 67
            Width = 458
            Height = 21
            TabOrder = 2
          end
          object edorcontact: TEdit
            Left = 62
            Top = 40
            Width = 91
            Height = 21
            TabOrder = 3
          end
          object edortel: TEdit
            Left = 336
            Top = 40
            Width = 184
            Height = 21
            TabOrder = 4
          end
        end
        object RzButton1: TRzButton
          Left = 463
          Top = 131
          Caption = #30830#23450
          TabOrder = 1
          OnClick = RzButton1Click
        end
      end
      object tabcaigou: TTabSheet
        Caption = #37319#36141
        ImageIndex = 1
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object GroupBox1: TGroupBox
          Left = 1
          Top = 5
          Width = 537
          Height = 169
          Caption = #37319#36141#20449#24687
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 0
          object Label1: TLabel
            Left = 18
            Top = 16
            Width = 48
            Height = 13
            Caption = #21333#25454#25260#22836
          end
          object Label2: TLabel
            Left = 42
            Top = 70
            Width = 24
            Height = 13
            Caption = #22320#22336
          end
          object Label3: TLabel
            Left = 30
            Top = 43
            Width = 36
            Height = 13
            Caption = #32852#31995#20154
          end
          object Label5: TLabel
            Left = 306
            Top = 43
            Width = 24
            Height = 13
            Caption = #30005#35805
          end
          object Label10: TLabel
            Left = 8
            Top = 148
            Width = 72
            Height = 13
            Caption = #37319#36141#25171#21360#22791#27880
          end
          object Label21: TLabel
            Left = 18
            Top = 123
            Width = 48
            Height = 13
            Caption = #25910#36135#22320#22336
          end
          object Label22: TLabel
            Left = 6
            Top = 96
            Width = 60
            Height = 13
            Caption = #25910#36135#32852#31995#20154
          end
          object Label23: TLabel
            Left = 282
            Top = 96
            Width = 48
            Height = 13
            Caption = #25910#36135#30005#35805
          end
          object edcgprintbk: TEdit
            Left = 86
            Top = 145
            Width = 434
            Height = 21
            TabOrder = 0
          end
          object edcgprinttitle: TEdit
            Left = 69
            Top = 13
            Width = 451
            Height = 21
            TabOrder = 1
          end
          object edcgaddress: TEdit
            Left = 69
            Top = 67
            Width = 451
            Height = 21
            TabOrder = 2
          end
          object edcgcontact: TEdit
            Left = 69
            Top = 40
            Width = 84
            Height = 21
            TabOrder = 3
          end
          object edcgtel: TEdit
            Left = 336
            Top = 40
            Width = 184
            Height = 21
            TabOrder = 4
          end
          object edshaddress: TEdit
            Left = 69
            Top = 120
            Width = 451
            Height = 21
            TabOrder = 5
          end
          object edshcontact: TEdit
            Left = 69
            Top = 93
            Width = 91
            Height = 21
            TabOrder = 6
          end
          object edshtel: TEdit
            Left = 336
            Top = 93
            Width = 184
            Height = 21
            TabOrder = 7
          end
        end
        object RzButton2: TRzButton
          Left = 475
          Top = 180
          Caption = #30830#23450
          TabOrder = 1
          OnClick = RzButton2Click
        end
      end
      object rabrk: TTabSheet
        Caption = #20837#24211
        ImageIndex = 2
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object GroupBox3: TGroupBox
          Left = 1
          Top = 5
          Width = 537
          Height = 120
          Caption = #20837#24211#20449#24687
          Ctl3D = True
          ParentCtl3D = False
          TabOrder = 0
          object Label11: TLabel
            Left = 8
            Top = 16
            Width = 48
            Height = 13
            Caption = #21333#25454#25260#22836
          end
          object Label12: TLabel
            Left = 32
            Top = 70
            Width = 24
            Height = 13
            Caption = #22320#22336
          end
          object Label13: TLabel
            Left = 20
            Top = 43
            Width = 36
            Height = 13
            Caption = #32852#31995#20154
          end
          object Label14: TLabel
            Left = 306
            Top = 43
            Width = 24
            Height = 13
            Caption = #30005#35805
          end
          object Label15: TLabel
            Left = 8
            Top = 97
            Width = 72
            Height = 13
            Caption = #20837#24211#25171#21360#22791#27880
          end
          object edrkprintbk: TEdit
            Left = 86
            Top = 94
            Width = 434
            Height = 21
            TabOrder = 0
          end
          object edrkprinttitle: TEdit
            Left = 62
            Top = 13
            Width = 458
            Height = 21
            TabOrder = 1
          end
          object edrkaddress: TEdit
            Left = 62
            Top = 67
            Width = 458
            Height = 21
            TabOrder = 2
          end
          object edrkcontact: TEdit
            Left = 62
            Top = 40
            Width = 91
            Height = 21
            TabOrder = 3
          end
          object edrktel: TEdit
            Left = 336
            Top = 40
            Width = 184
            Height = 21
            TabOrder = 4
          end
        end
        object RzButton3: TRzButton
          Left = 463
          Top = 131
          Caption = #30830#23450
          TabOrder = 1
          OnClick = RzButton3Click
        end
      end
      object tabws: TTabSheet
        Caption = #21457#36135
        ImageIndex = 3
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object GroupBox4: TGroupBox
          Left = 1
          Top = 6
          Width = 537
          Height = 122
          Caption = #21457#36135#20449#24687
          TabOrder = 0
          object Label16: TLabel
            Left = 8
            Top = 17
            Width = 48
            Height = 13
            Caption = #21333#25454#25260#22836
          end
          object Label17: TLabel
            Left = 32
            Top = 70
            Width = 24
            Height = 13
            Caption = #22320#22336
          end
          object Label18: TLabel
            Left = 20
            Top = 42
            Width = 36
            Height = 13
            Caption = #32852#31995#20154
          end
          object Label19: TLabel
            Left = 306
            Top = 42
            Width = 24
            Height = 13
            Caption = #30005#35805
          end
          object Label20: TLabel
            Left = 8
            Top = 97
            Width = 72
            Height = 13
            Caption = #21457#36135#25171#21360#22791#27880
          end
          object edwsprinttitle: TEdit
            Left = 62
            Top = 14
            Width = 458
            Height = 21
            TabOrder = 0
          end
          object edwsaddress: TEdit
            Left = 62
            Top = 67
            Width = 458
            Height = 21
            TabOrder = 1
          end
          object edwscontact: TEdit
            Left = 62
            Top = 39
            Width = 91
            Height = 21
            TabOrder = 2
          end
          object edwstel: TEdit
            Left = 336
            Top = 39
            Width = 184
            Height = 21
            TabOrder = 3
          end
          object edpxprintbk: TEdit
            Left = 86
            Top = 94
            Width = 434
            Height = 21
            TabOrder = 4
          end
        end
        object RzButton4: TRzButton
          Left = 463
          Top = 131
          Caption = #30830#23450
          TabOrder = 1
          OnClick = RzButton4Click
        end
      end
    end
  end
  object fcon: TADOConnection
    Left = 352
    Top = 8
  end
  object aq: TADOQuery
    Parameters = <>
    Left = 480
  end
end
