object frmModalDialog: TfrmModalDialog
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'frmModalDialog'
  ClientHeight = 172
  ClientWidth = 326
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 326
    Height = 175
    BevelInner = bvLowered
    TabOrder = 0
    DesignSize = (
      326
      175)
    object btnOk: TRzButton
      Left = 138
      Top = 131
      ModalResult = 1
      Anchors = [akRight, akBottom]
      Caption = #30830#35748
      TabOrder = 0
    end
    object btnCancel: TRzButton
      Left = 229
      Top = 131
      ModalResult = 2
      Anchors = [akRight, akBottom]
      Caption = #21462#28040
      TabOrder = 1
    end
  end
end
