//---------------------------------------------------------------------------

#ifndef Unitorder_stkH
#define Unitorder_stkH
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
class Tfrmorder_stk : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edisbn;
	TLabel *Label2;
	TEdit *edname;
	TLabel *lable3;
	TEdit *edamount;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *query;
	TLabel *Label3;
	TEdit *edauthor;
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmorder_stk(TComponent* Owner,TADOQuery *aquery);
	AnsiString amount,name,isbn,author;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmorder_stk *frmorder_stk;
//---------------------------------------------------------------------------
#endif
