//---------------------------------------------------------------------------

#ifndef SalesAnalysisFormH
#define SalesAnalysisFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmSalesAnalysis : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TDataSource *ds1;
	TADODataSet *dsquery;
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton1;
	TImageList *ImageList1;
	TRzToolButton *BtnExport;
	TPanel *Panel1;
	TCheckBox *cbstart;
	TDateTimePicker *dtp1;
	TCheckBox *cbend;
	TDateTimePicker *dtp2;
	TGroupBox *GroupBox2;
	TRadioButton *rb1;
	TRadioButton *rb2;
	TRadioButton *rb4;
	TRadioButton *rb5;
	TRadioGroup *RadioGroup1;
	TDBGridEh *DBGridEh1;
	TRzToolButton *BtnAlignBottom;
	TCheckBox *chstorage;
	TComboBox *cbstorage;
	TSaveDialog *savedlg;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall DBGridEh1TitleClick(TColumnEh *Column);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
private:	// User declarations
	String storageformat,retaiformat;
public:		// User declarations
	__fastcall TfrmSalesAnalysis(TComponent* Owner);
	void  Init(TApplication* app, TADOConnection* con);
	bool __fastcall DbgridToExcel(TDBGridEh* dbg);
	int stgid;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSalesAnalysis *frmSalesAnalysis;
//---------------------------------------------------------------------------
#endif
