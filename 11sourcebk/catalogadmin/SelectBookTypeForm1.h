//---------------------------------------------------------------------------

#ifndef SelectBookTypeForm1H
#define SelectBookTypeForm1H
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
#include "SelectBookTypeForm.h"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include "RzShellDialogs.hpp"
#include "RzRadChk.hpp"
#include "RzRadGrp.hpp"
#include "RzPrgres.hpp"
#include <ComCtrls.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmSelectBookType1 : public TfrmSelectBookType
{
__published:	// IDE-managed Components
	TButton *btn2;
	TRzOpenDialog *opndlgExcelPath;
	TRzEdit *edtExcelPath;
	TLabel *lbl4;
	TRzRadioGroup *rdgrp1;
	TRzCheckBox *chckbxBarcode;
	TRzCheckBox *chckbxName;
	TRzCheckBox *chckbxUserDefCode;
	TRzCheckBox *chckbxPress;
	TRzCheckBox *chckbxISBN;
	TRzCheckBox *chckbxAuthor;
	TRzCheckBox *chckbxPrice;
	TRzCheckBox *chckbxDate;
	TLabel *lbl3;
	TADOConnection *con1;
	TADOQuery *qry1;
	TDataSource *ds1;
	TADODataSet *dset1;
	TRzCheckBox *chckbxTotalAmount;
	TLabel *lblExcel;
	void __fastcall btn2Click(TObject *Sender);
	void __fastcall btnExit1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmSelectBookType1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSelectBookType1 *frmSelectBookType1;
//---------------------------------------------------------------------------
#endif
