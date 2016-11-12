//---------------------------------------------------------------------------

#ifndef ExcelImportH
#define ExcelImportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include "RzRadChk.hpp"
#include "RzRadGrp.hpp"
#include "RzShellDialogs.hpp"
#include "RzPrgres.hpp"
#include "ModalDialog.h"
#include "SelectBookTypeForm.h"
#include <Buttons.hpp>
#include <ImgList.hpp>
#include "RzCmboBx.hpp"
//---------------------------------------------------------------------------
class TfrmExcelImport : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TLabel *lbl3;
	TRzEdit *edtExcelPath;
	TRzOpenDialog *opndlgExcelPath;
	TRzRadioGroup *rdgrp1;
	TRzCheckBox *chckbxBarcode;
	TRzCheckBox *chckbxName;
	TRzCheckBox *chckbxUserDefCode;
	TRzCheckBox *chckbxPress;
	TRzCheckBox *chckbxISBN;
	TRzCheckBox *chckbxAuthor;
	TRzCheckBox *chckbxPrice;
	TRzCheckBox *chckbxDate;
	TRzCheckBox *chckbxTotalAmount;
	TLabel *lblExcel;
	TADODataSet *dset1;
	TDataSource *ds1;
	TADOQuery *qry1;
	TRzProgressBar *prgrsbrExcelImport;
	TLabel *lblRecordCount;
	TLabel *lbl4;
	TLabel *lblImportCount;
	TRzCheckBox *chckbxTypeName;
	TADOConnection *con1;
	TRzButton *btn2;
	TSpeedButton *spselectpath;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExit;
	TLabel *lbsum;
	TLabel *lbnow;
	TADODataSet *dspress;
	TRzCheckBox *checkbsupplier;
	TRzComboBox *cbsupplier;
	TLabel *Label1;
	TLabel *Label2;
	TADOQuery *query1;
	TRzToolButton *BtnAlignBottom;
	void __fastcall btn2Click(TObject *Sender);
	void __fastcall spselectpathClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall chckbxTotalAmountClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
private:	// User declarations
	bool Import;
	TADOQuery * dsdg;             //
public:		// User declarations
	__fastcall TfrmExcelImport(TComponent* Owner,TADOQuery * query);
	void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmExcelImport *frmExcelImport;
//---------------------------------------------------------------------------
#endif
