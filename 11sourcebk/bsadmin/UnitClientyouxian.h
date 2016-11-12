//---------------------------------------------------------------------------

#ifndef UnitClientyouxianH
#define UnitClientyouxianH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmclientyouxian : public TForm
{
__published:	// IDE-managed Components
	TRzDBGrid *RzDBGrid1;
	TADOQuery *aq;
	TDataSource *ds;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
   TADOConnection *fcn;
public:		// User declarations
	__fastcall Tfrmclientyouxian(TComponent* Owner);
	void init(TADOConnection *cn);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmclientyouxian *frmclientyouxian;
//---------------------------------------------------------------------------
#endif
