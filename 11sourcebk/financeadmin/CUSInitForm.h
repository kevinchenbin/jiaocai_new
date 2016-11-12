//---------------------------------------------------------------------------

#ifndef CUSInitFormH
#define CUSInitFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzDBGrid.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TfrmCUSInit : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TRzToolButton *RzToolButton3;
	TADODataSet *dsSupplyInit;
	TDataSource *ds1;
	TADOQuery *qrySupply;
	TDataSource *ds2;
	TRzLabel *lbl3;
	TRzDBEdit *edtBalance;
	TRzLabel *lbl5;
	TRzLabel *lbl4;
	TComboBox *cbbType;
	TRzLabel *lbl6;
	TRzLabel *lbl1;
	TEdit *edtnum1;
	TADOCommand *cmdaddMoney;
	TRzDBGrid *rzdbgrd2;
	void __fastcall cbbTypeSelect(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edtnum1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzToolButton3Click(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
   		void OnHotKeyPress(DWORD vkCode);
public:		// User declarations
	__fastcall TfrmCUSInit(TComponent* Owner);
		void Init(TApplication* app, TADOConnection* con);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCUSInit *frmCUSInit;
//---------------------------------------------------------------------------
#endif
