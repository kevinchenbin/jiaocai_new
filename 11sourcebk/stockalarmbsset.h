//---------------------------------------------------------------------------

#ifndef stockalarmbssetH
#define stockalarmbssetH
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
//---------------------------------------------------------------------------
class Tfrmstockalarmbsset : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSpeedButton *sbok;
	TSpeedButton *sbcancel;
	TADOQuery *aquery;
	TADOQuery *qryretairange;
	TDataSource *dsrcretairange;
	TGroupBox *GroupBox3;
	TCheckBox *chloginstockalarm;
	TCheckBox *chkucunstockalarm;
	TLabel *Label2;
	TEdit *edtime;
	TLabel *Label3;
	TCheckBox *chtimestockalarm;
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edtimeKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmstockalarmbsset(TComponent* Owner,TADOConnection* con);
	void Readydata();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmstockalarmbsset *frmstockalarmbsset;
//---------------------------------------------------------------------------
#endif
