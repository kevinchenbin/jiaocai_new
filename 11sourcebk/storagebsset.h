//---------------------------------------------------------------------------

#ifndef storagebssetH
#define storagebssetH
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
class Tfrmstoragebsset : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSpeedButton *sbok;
	TSpeedButton *sbcancel;
	TADOQuery *aquery;
	TGroupBox *GroupBox1;
	TCheckBox *cbsameid;
	TCheckBox *cborder;
	TCheckBox *cbauto;
	TCheckBox *cbtrace;
	TLabel *Label1;
	TEdit *etdot;
	TLabel *Label2;
	TADOQuery *qryretairange;
	TDataSource *dsrcretairange;
	TCheckBox *cbstoragehistory;
	TLabel *½øÍË»õÃ÷Ï¸;
	TEdit *edstorageday;
	TCheckBox *cbadddotenable;
	TCheckBox *cblastyjpxdiscount;
	TLabel *Label3;
	TCheckBox *cblastyjpx;
	TCheckBox *cbadddot;
	TCheckBox *cbrkallsupplier;
	TCheckBox *cbrkusefind;
	TCheckBox *cbrkusedelete;
	TCheckBox *cbrkusetuihuo;
	TCheckBox *chmutisupplier;
	TCheckBox *chdeletestack;
	TLabel *Label4;
	TEdit *edmonth;
	TLabel *Label5;
	TGroupBox *GroupBox4;
	TGroupBox *GroupBox5;
	TCheckBox *cbrkusechange;
	TGroupBox *GroupBox3;
	TCheckBox *cblastyjlsdiscount;
	TCheckBox *chstoragesametishi;
	TCheckBox *chrktuihuoguanli;
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
	void __fastcall cblastyjpxClick(TObject *Sender);
	void __fastcall cbadddotClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmstoragebsset(TComponent* Owner,TADOConnection* con);
	void Readydata();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmstoragebsset *frmstoragebsset;
//---------------------------------------------------------------------------
#endif
