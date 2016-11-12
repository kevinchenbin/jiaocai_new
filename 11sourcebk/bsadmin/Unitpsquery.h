//---------------------------------------------------------------------------

#ifndef UnitpsqueryH
#define UnitpsqueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class Tfrmpsquery : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDateTimePicker *dtpstart;
	TCheckBox *chstart;
	TDateTimePicker *dtpend;
	TCheckBox *chend;
	TCheckBox *choutstorage;
	TCheckBox *chcode;
	TEdit *edcode;
	TDBGrid *DBGrid1;
	TButton *Button1;
	TButton *Button2;
	TComboBox *cboutstorage;
	TDataSource *ds;
	TADOQuery *query;
	TADOConnection *fcon;
	TCheckBox *chinstorage;
	TComboBox *cbinstorage;
	TRzDateTimeEdit *dtedtDate;
	TRzSpinEdit *spedtID;
	TLabel *Label1;
	TRzSpinEdit *spstorage;
	void __fastcall dtedtDateChange(TObject *Sender);
	void __fastcall edcodeChange(TObject *Sender);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall cboutstorageChange(TObject *Sender);
	void __fastcall cbinstorageChange(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmpsquery(TComponent* Owner,TADOConnection *con,int stgid,int type);
	int fstgid,ftype;
	AnsiString GetNoteCode();
	AnsiString Getsqlwhere();
	AnsiString sqlwhere;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmpsquery *frmpsquery;
//---------------------------------------------------------------------------
#endif
