//---------------------------------------------------------------------------

#ifndef SupplyInitFormH
#define SupplyInitFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzDBEdit.hpp"
//---------------------------------------------------------------------------
class TfrmSupplyInit : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzDBGrid *rzdbgrd2;
	TComboBox *cbbType;
	TRzLabel *lbl4;
	TRzLabel *lbl1;
	TRzLabel *lbl3;
	TRzLabel *lbl2;
	TRzToolbar *RzToolbar1;
	TRzToolButton *RzToolButton3;
	TRzLabel *lbl5;
	TADODataSet *dsSupplyInit;
	TADOQuery *qrySupply;
	TDataSource *ds1;
	TDataSource *ds2;
	TRzDBEdit *edt1;
	TRzLabel *lbl6;
	TADOCommand *cmdaddMoney;
	TEdit *edtnum1;
	void __fastcall cbbTypeSelect(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall edtnum1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmSupplyInit(TComponent* Owner);
	void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSupplyInit *frmSupplyInit;
//---------------------------------------------------------------------------
#endif
