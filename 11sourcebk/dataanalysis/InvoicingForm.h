//---------------------------------------------------------------------------

#ifndef InvoicingFormH
#define InvoicingFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ImgList.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmInvoicing : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton3;
	TRzToolButton *RzToolButton1;
	TADODataSet *dsquery;
	TDataSource *ds1;
	TPanel *Panel3;
	TADOCommand *querycom;
	TADOStoredProc *storcquery;
	TImageList *ImageList1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExport;
	TSaveDialog *savedlg;
	TDBGridEh *DBGridEh1;
	TADOConnection *fcon;
	TGroupBox *GroupBox1;
	TRzEdit *RzEdit5;
	TCheckBox *chk2;
	TCheckBox *chk6;
	TRzEdit *RzEdtInfor;
	TCheckBox *chk1;
	TRzEdit *RzEdit2;
	TCheckBox *chk4;
	TCheckBox *chk5;
	TDateTimePicker *dtp1;
	TDateTimePicker *dtp2;
	TComboBox *cbsupplier;
	TCheckBox *chtype;
	TComboBox *cbtype;
	TCheckBox *cbstart;
	TCheckBox *cbend;
	TComboBox *cbpress;
	TCheckBox *chstorage;
	TComboBox *cbstorage;
	TCheckBox *ch1;
	TCheckBox *ch2;
	TCheckBox *ch3;
	TEdit *edsupplier;
	TEdit *edtype;
	TEdit *edpress;
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall cbbTypeSelect(TObject *Sender);
	void __fastcall RzEdtInforKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DBGridEh1TitleClick(TColumnEh *Column);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall ch1Click(TObject *Sender);
	void __fastcall ch2Click(TObject *Sender);
	void __fastcall ch3Click(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall edsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtp1Change(TObject *Sender);
	void __fastcall dtp1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtp2Change(TObject *Sender);
	void __fastcall dtp2KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzEdit2Change(TObject *Sender);
	void __fastcall RzEdtInforChange(TObject *Sender);
	void __fastcall RzEdit5Change(TObject *Sender);
	void __fastcall RzEdit5KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbsupplierChange(TObject *Sender);
	void __fastcall cbsupplierKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbtypeChange(TObject *Sender);
	void __fastcall cbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpressChange(TObject *Sender);
	void __fastcall cbpressKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
		TObject *Sender1;
		String storageformat,retaiformat,saleformat;
public:		// User declarations
	__fastcall TfrmInvoicing(TComponent* Owner);
	int stgid;
	void  Init(TApplication* app, TADOConnection* con);
	bool DbgridToExcel(TDBGridEh* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmInvoicing *frmInvoicing;
//---------------------------------------------------------------------------
#endif
