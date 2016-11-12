//---------------------------------------------------------------------------

#ifndef UnitfahuocodeH
#define UnitfahuocodeH
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
class Tfrmfahuocode : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDBGrid *DBGrid1;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TDataSource *ds;
	TADOQuery *aquery;
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmfahuocode(TComponent* Owner,TADOQuery *query);
	int newid,clientid,wsheadid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmfahuocode *frmfahuocode;
//---------------------------------------------------------------------------
#endif
