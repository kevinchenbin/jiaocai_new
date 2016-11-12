//---------------------------------------------------------------------------

#ifndef procurequeryH
#define procurequeryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "DBCtrlsEh.hpp"
#include <Mask.hpp>
#include <Buttons.hpp>
#include "DBGridEh.hpp"
#include "MDIChild.h"
#include "GridsEh.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
#include "ZNStorageMngForm.h"
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class Tfrmprocurequery : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TCheckBox *chprocure;
	TEdit *edprocurecode;
	TCheckBox *chsupplier;
	TEdit *edquery;
	TComboBox *cbsupplier;
	TCheckBox *chstart;
	TDBDateTimeEditEh *dtstart;
	TCheckBox *chend;
	TDBDateTimeEditEh *dtend;
	TSpeedButton *SpeedButton1;
	TDBGridEh *DBGridEh1;
	TSpeedButton *SpeedButton2;
	TDataSource *ds1;
	TDataSource *ds2;
	TADOQuery *aq1;
	TADOQuery *aq2;
	TADOQuery *aq;
	TPopupMenu *pqpm;
	TMenuItem *N1;
	TDBGrid *DBGrid1;
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall DBGridEh1CellClick(TColumnEh *Column);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmprocurequery(TComponent* Owner);
	LandInfo linfo;
	void Init(LandInfo* li);
	TfrmZNStorageMng *ZNStorage;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmprocurequery *frmprocurequery;
//---------------------------------------------------------------------------
#endif
