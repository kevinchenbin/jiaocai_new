//---------------------------------------------------------------------------

#ifndef unitpsinorderH
#define unitpsinorderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "RzButton.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include "UnitDiaobo.h"
//---------------------------------------------------------------------------
class Tfrmpsinorder : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TSpeedButton *spselectClient;
	TCheckBox *chordercode;
	TEdit *edordercode;
	TCheckBox *chclient;
	TEdit *edclient;
	TEdit *edtclient;
	TRzButton *RzButton1;
	TDBGrid *DBGrid1;
	TDataSource *ds;
	TADOQuery *query;
	TADOConnection *con;
	TDataSource *ds2;
	TADOQuery *query2;
	TCheckBox *chstart;
	TDateTimePicker *dtpstart;
	TCheckBox *chend;
	TDateTimePicker *dtpend;
	TRzDateTimeEdit *dtedtDate;
	TRzSpinEdit *spedtID;
	TRzSpinEdit *spstgid;
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall edtclientChange(TObject *Sender);
	void __fastcall dtedtDateChange(TObject *Sender);
	void __fastcall spedtIDChange(TObject *Sender);
	void __fastcall edordercodeChange(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmpsinorder(TComponent* Owner,TADOConnection *cn,int stgid,int userid,int headid);
	int fstgid,fuserid,fheadid;
	int ClientID;
	int supplierid;
	void ClientView();
	AnsiString sqlwhere;
	Tfrmdiaobo *Diaobo;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmpsinorder *frmpsinorder;
//---------------------------------------------------------------------------
#endif
