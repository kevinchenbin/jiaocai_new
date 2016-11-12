//---------------------------------------------------------------------------

#ifndef procuresetH
#define procuresetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <Buttons.hpp>
#include <DB.hpp>
#include "pdtypes.h"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzCmboBx.hpp"
//---------------------------------------------------------------------------
class Tfrmprocureset : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSpeedButton *sbok;
	TSpeedButton *sbcancel;
	TADOQuery *aquery;
	TADOQuery *qryretairange;
	TDataSource *dsrcretairange;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TCheckBox *chprocurefindpwd;
	TCheckBox *chprocuredeletepwd;
	TCheckBox *chznprocurefindpwd;
	TCheckBox *chznprocuredeletepwd;
	TEdit *edday;
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmprocureset(TComponent* Owner,TADOConnection* con);
	void Readydata();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmprocureset *frmprocureset;
//---------------------------------------------------------------------------
#endif
