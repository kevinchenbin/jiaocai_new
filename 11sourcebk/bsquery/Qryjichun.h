//---------------------------------------------------------------------------

#ifndef QryjichunH
#define QryjichunH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBCmbo.hpp"
#include "RzEdit.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include <Buttons.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "RzTabs.hpp"
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "MDIChild.h"
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrmjichun : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzGroupBox *grpbx1;
	TRzCheckBox *chckbxStartTime;
	TRzDateTimeEdit *dtedtStart;
	TRzCheckBox *chckbxEndTime;
	TRzDateTimeEdit *dtedtEnd;
	TRzCheckBox *chckbxBookName;
	TRzCheckBox *chckbxISBN;
	TRzCheckBox *chckbxUserDefNum;
	TRzCheckBox *chckbxPress;
	TRzCheckBox *chckbxRemarks;
	TRzCheckBox *chckbxStorage;
	TRzEdit *edtBookName;
	TRzEdit *edtISBN;
	TRzEdit *edtUserDefNum;
	TRzEdit *edtPress;
	TRzEdit *edtRemarks;
	TRzCheckBox *chckbx1;
	TCheckBox *chstaff;
	TComboBox *cbstaff;
	TEdit *edsuplier;
	TRzToolbar *rztlbr1;
	TRzToolButton *tlbtnQry;
	TRzToolButton *tlbtnExport;
	TRzToolButton *tlbtnExit;
	TRzToolButton *BtnAlignBottom;
	TRzPageControl *pagecontrol;
	TRzTabSheet *tabandan;
	TRzTabSheet *tabdetail;
	TDBGridEh *dbgrid2;
	TComboBox *cbstg;
	TComboBox *cbsupplier;
	TComboBox *cbpress;
	TADOQuery *aqandan;
	TDataSource *ds1;
	TDBGridEh *dbgrid1;
	TRzCheckBox *ckdanhao;
	TEdit *editdanhao;
	TDataSource *ds2;
	TADOQuery *aqdetail;
	TSaveDialog *savedialog;
	void __fastcall tlbtnQryClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall tlbtnExitClick(TObject *Sender);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall cbsupplierChange(TObject *Sender);
	void __fastcall cbstaffChange(TObject *Sender);
	void __fastcall edsuplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtPressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtISBNChange(TObject *Sender);
	void __fastcall edtBookNameChange(TObject *Sender);
	void __fastcall edtUserDefNumChange(TObject *Sender);
	void __fastcall editdanhaoChange(TObject *Sender);
	void __fastcall tlbtnExportClick(TObject *Sender);
	void __fastcall dbgrid2TitleClick(TColumnEh *Column);


private:	// User declarations
public:		// User declarations
	__fastcall Tfrmjichun(TComponent* Owner);
        void Init(LandInfo* li);
        void Query();
        void Query1();
        void readyDate();
        TADOConnection *fcon;
        int fstgid;
        void DbgridToExcel(TDBGridEh* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmjichun *frmjichun;
//---------------------------------------------------------------------------
#endif