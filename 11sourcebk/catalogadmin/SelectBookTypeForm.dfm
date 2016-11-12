inherited frmSelectBookType: TfrmSelectBookType
  BorderStyle = bsDialog
  Caption = #31867#21035#35774#32622
  ClientHeight = 692
  ClientWidth = 604
  Position = poOwnerFormCenter
  Visible = False
  ExplicitWidth = 610
  ExplicitHeight = 724
  PixelsPerInch = 96
  TextHeight = 13
  inherited rztlbr2: TRzToolbar
    Width = 604
    ExplicitWidth = 604
    ToolbarControls = (
      btnExit1
      btnExit2
      btnExit3
      RzToolButton1
      rtbmodify
      BtnSave)
    inherited btnExit2: TRzToolButton
      Left = 64
      ExplicitLeft = 64
    end
    inherited btnExit3: TRzToolButton
      Left = 124
      ExplicitLeft = 124
    end
    inherited RzToolButton1: TRzToolButton
      Left = 201
      ExplicitLeft = 201
    end
    inherited rtbmodify: TRzToolButton
      Left = 261
      ExplicitLeft = 261
    end
    inherited BtnSave: TRzToolButton
      Left = 321
      ExplicitLeft = 321
    end
  end
  object Panel1: TPanel [1]
    Left = 291
    Top = 264
    Width = 185
    Height = 41
    Caption = 'Panel1'
    TabOrder = 1
  end
  inherited Panel2: TPanel
    Width = 604
    Height = 663
    TabOrder = 3
    ExplicitWidth = 604
    ExplicitHeight = 371
    inherited Splitter1: TSplitter
      Height = 659
      ExplicitLeft = 161
      ExplicitTop = 2
      ExplicitHeight = 370
    end
    inherited tvbookclass: TTreeView
      Height = 659
      ExplicitHeight = 367
    end
    inherited Panel3: TPanel
      Width = 438
      Height = 659
      ExplicitWidth = 438
      ExplicitHeight = 367
    end
  end
end
