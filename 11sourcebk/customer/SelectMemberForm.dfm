inherited frmSelectMember: TfrmSelectMember
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'frmSelectMember'
  ClientHeight = 681
  ClientWidth = 857
  FormStyle = fsNormal
  Position = poDesktopCenter
  Visible = False
  OnShow = FormShow
  ExplicitWidth = 863
  ExplicitHeight = 707
  PixelsPerInch = 96
  TextHeight = 13
  inherited rztlbr1: TRzToolbar
    Width = 857
    ExplicitWidth = 857
    ToolbarControls = (
      RzSpacer1
      RzToolButton3
      RzToolButton4
      RzToolButton5
      RzToolButton9
      RzToolButton1
      RzToolButton2
      RzToolButton8
      RzToolButton7
      RzToolButton6)
    inherited RzToolButton3: TRzToolButton
      Enabled = False
    end
    inherited RzToolButton4: TRzToolButton
      Enabled = False
    end
    inherited RzToolButton5: TRzToolButton
      Enabled = False
    end
    inherited RzToolButton1: TRzToolButton
      Left = 308
      ExplicitLeft = 308
    end
    inherited RzToolButton2: TRzToolButton
      Left = 382
      ExplicitLeft = 382
    end
    inherited RzToolButton7: TRzToolButton
      Left = 531
      ExplicitLeft = 531
    end
    inherited RzToolButton6: TRzToolButton
      Left = 591
      ExplicitLeft = 591
    end
    inherited RzToolButton8: TRzToolButton
      Left = 456
      ExplicitLeft = 456
    end
    inherited RzToolButton9: TRzToolButton
      Enabled = False
    end
  end
  inherited RzGroupBox2: TRzGroupBox
    inherited RzEditInfor: TRzEdit
      DoubleBuffered = True
      Enabled = False
      ParentDoubleBuffered = False
    end
    inherited cbbType: TComboBox
      DoubleBuffered = True
      Enabled = False
      ParentDoubleBuffered = False
    end
  end
  inherited RzDBGrid: TRzDBGrid
    Width = 857
    Height = 459
  end
  inherited ds1: TDataSource
    Left = 16
    Top = 120
  end
  inherited dsetMemberLevel: TADODataSet
    Left = 632
  end
end
