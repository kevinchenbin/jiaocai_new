//---------------------------------------------------------------------------

#ifndef UnitgenhuanselectH
#define UnitgenhuanselectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DB.hpp>
#include <ADODB.hpp>
//---------------------------------------------------------------------------
class Tfrmchangeselect : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TButton *btgenhuan;
	TDataSource *ds;
	TADOQuery *query;
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btgenhuanClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmchangeselect(TComponent* Owner,TADOQuery *qu);
	int continuechange;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmchangeselect *frmchangeselect;
//---------------------------------------------------------------------------
#endif
