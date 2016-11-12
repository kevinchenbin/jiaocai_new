//---------------------------------------------------------------------------

#ifndef BookstackMngFormH
#define BookstackMngFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzDBCmbo.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzLine.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <DB.hpp>
#include <MDIChild.h>
//---------------------------------------------------------------------------
class TfrmBookstackMng : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzDBEdit *edtStgName;
	TRzLabel *lbl1;
	TRzLabel *lbl2;
	TRzDBEdit *edtNum;
	TRzLabel *lbl3;
	TRzToolbar *rztlbr1;
	TRzToolButton *RzToolButton2;
	TRzToolButton *RzToolButton4;
	TRzToolButton *RzToolButton5;
	TRzToolButton *RzToolButton1;
	TRzDBGrid *rzdbgrdGridCust;
	TRzDBEdit *edtID;
	TRzToolButton *RzToolButton3;
	TADODataSet *dsetBookStackMng;
	TDataSource *ds1;
	TRzDBEdit *edtName;
	TDataSource *ds2;
	TADODataSet *dsStore;

	void __fastcall RzToolButton2Click(TObject *Sender);
	void __fastcall edtStgNameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtNumKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall RzToolButton4Click(TObject *Sender);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton5Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	TObject *Sender1;
public:		// User declarations
	__fastcall TfrmBookstackMng(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBookstackMng *frmBookstackMng;
//---------------------------------------------------------------------------
#endif
