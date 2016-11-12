//---------------------------------------------------------------------------

#ifndef QryNoteCodeForm1H
#define QryNoteCodeForm1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include "RzCmboBx.hpp"
#include "RzSpnEdt.hpp"
#include "RzButton.hpp"
#include "ModalDialog.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ComCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmQryNoteCode1 : public TfrmModalDialog
{
__published:	// IDE-managed Components
	TRzDateTimeEdit *dtedtDate;
	TRzSpinEdit *spedtID;
	TRzEdit *edtCode;
	TSpeedButton *spselectClient;
	TEdit *edtclient;
	TRzComboBox *cbselect;
	TRzEdit *edtQryVendor;
	TCheckBox *ch1;
	TCheckBox *chstart;
	TDateTimePicker *dtpstart;
	TCheckBox *chend;
	TDateTimePicker *dtpend;
	TCheckBox *chcode;
	TDBGrid *DBGrid1;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TDataSource *ds;
	TADOQuery *query;
	TADOConnection *fcon;
	void __fastcall dtedtDateChange(TObject *Sender);
	void __fastcall spedtIDChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall DBGrid1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall edtCodeChange(TObject *Sender);
	void __fastcall cbselectChange(TObject *Sender);
	void __fastcall edtclientChange(TObject *Sender);
	void __fastcall edtQryVendorKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
	String m_stgNtCode;
public:		// User declarations
	__fastcall TfrmQryNoteCode1(TComponent* Owner,int modle,TADOConnection *con);
	String GetNoteCode();
	void SetstgID(int stgid);
	int type;
	int ClientID;
	AnsiString sqlwhere;
	String GetSqlWhere();
	void ClientView();
    bool weishenhei,master;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmQryNoteCode1 *frmQryNoteCode1;
//---------------------------------------------------------------------------
#endif
