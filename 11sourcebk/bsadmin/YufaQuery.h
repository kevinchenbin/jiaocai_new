//---------------------------------------------------------------------------

#ifndef YufaQueryH
#define YufaQueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmYufaQuery : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TDateTimePicker *dtpstart;
	TDateTimePicker *dtpend;
	TSpeedButton *spselectClient;
	TCheckBox *chclient;
	TEdit *edclient;
	TEdit *edtclient;
	TDBGrid *DBGrid1;
	TRzButton *RzButton1;
	TCheckBox *chstart;
	TCheckBox *chend;
	TADOConnection *fcon;
	TDataSource *ds;
	TADOQuery *query;
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmYufaQuery(TComponent* Owner,TADOConnection *con,int stgid);
	int ClientID,fstgid;
	void ClientView();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmYufaQuery *frmYufaQuery;
//---------------------------------------------------------------------------
#endif
