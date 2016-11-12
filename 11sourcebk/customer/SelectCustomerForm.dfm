inherited frmSelectCustomer: TfrmSelectCustomer
  BorderStyle = bsDialog
  Caption = 'frmSelectCustomer'
  ClientHeight = 421
  ClientWidth = 636
  FormStyle = fsNormal
  Position = poDesktopCenter
  Visible = False
  OnShow = FormShow
  ExplicitWidth = 642
  ExplicitHeight = 447
  PixelsPerInch = 96
  TextHeight = 13
  inherited rztlbr1: TRzToolbar
    Width = 636
    ExplicitWidth = 636
    ToolbarControls = (
      RzToolButton1
      RzToolButton2
      RzToolButton4
      RzToolButton5)
    inherited RzToolButton1: TRzToolButton
      Enabled = False
    end
    inherited RzToolButton2: TRzToolButton
      Enabled = False
    end
    inherited RzToolButton4: TRzToolButton
      Enabled = False
    end
  end
  inherited RzGroupBox1: TRzGroupBox
    inherited edtQuery: TRzEdit
      Enabled = False
    end
  end
  inherited dbGridCust: TRzDBGrid
    Width = 636
    Height = 197
  end
end
