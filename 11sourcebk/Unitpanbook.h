//---------------------------------------------------------------------------

#ifndef UnitpanbookH
#define UnitpanbookH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmpanbook : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *query;
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmpanbook(TComponent* Owner,TADOQuery *aq);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmpanbook *frmpanbook;
//---------------------------------------------------------------------------
#endif
