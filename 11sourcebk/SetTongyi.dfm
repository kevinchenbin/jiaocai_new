object frmSetTongyi: TfrmSetTongyi
  Left = 0
  Top = 0
  Caption = #32479#19968
  ClientHeight = 144
  ClientWidth = 202
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
    Width = 202
    Height = 144
    Align = alClient
    BevelInner = bvLowered
    Color = 16180174
    ParentBackground = False
    TabOrder = 0
    ExplicitLeft = 16
    ExplicitTop = 32
    ExplicitWidth = 185
    ExplicitHeight = 41
    object RzButton1: TRzButton
      Left = 16
      Top = 98
      Caption = #30830#23450
      TabOrder = 0
      OnClick = RzButton1Click
    end
    object RzButton2: TRzButton
      Left = 112
      Top = 98
      Caption = #21462#28040
      TabOrder = 1
      OnClick = RzButton2Click
    end
    object chyjpxdiscount: TCheckBox
      Left = 16
      Top = 30
      Width = 97
      Height = 17
      Caption = #39044#35745#25209#38144#25240#25187
      TabOrder = 2
    end
    object chyilsdiscount: TCheckBox
      Left = 16
      Top = 64
      Width = 97
      Height = 17
      Caption = #39044#35745#38646#21806#25240#25187
      TabOrder = 3
    end
    object edyjpx: TRzNumericEdit
      Left = 119
      Top = 28
      Width = 68
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 4
      IntegersOnly = False
      DisplayFormat = '##0.00'
    end
    object edyjls: TRzNumericEdit
      Left = 119
      Top = 62
      Width = 68
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 5
      IntegersOnly = False
      DisplayFormat = '##0.00'
    end
  end
end
