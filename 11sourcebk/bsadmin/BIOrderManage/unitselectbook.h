//---------------------------------------------------------------------------

#ifndef unitselectbookH
#define unitselectbookH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmcomfigbook : public TForm
{
__published:	// IDE-managed Components
	TPanel *frmselectbook;
	TDBGrid *DBGrid1;
	TCheckBox *chisbn;
	TEdit *edisbn;
	TCheckBox *chname;
	TEdit *edname;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TRzButton *RzButton3;
	TDataSource *ds;
	TADOQuery *query;
	TADOConnection *fcon;
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall RzButton3Click(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmcomfigbook(TComponent* Owner,TADOConnection *con);
	AnsiString ISBN,Name,Press,Author;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmcomfigbook *frmcomfigbook;
//---------------------------------------------------------------------------
#endif
