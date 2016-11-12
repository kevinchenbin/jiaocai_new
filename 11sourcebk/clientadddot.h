//---------------------------------------------------------------------------

#ifndef clientadddotH
#define clientadddotH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzCmboBx.hpp"
#include <Buttons.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class Tfrmclientadddot : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TLabel *Label1;
	TSpeedButton *spselectClient;
	TEdit *edquery;
	TEdit *edtclient;
	TLabel *Label2;
	TEdit *eddot;
	TLabel *Label3;
	TADOConnection *fcon;
	TDataSource *ds;
	TADOQuery *query;
	TButton *Button1;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall N1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmclientadddot(TComponent* Owner,TADOConnection *con,int stgid);
	int ClientID;
	int fstgid;
	void ClientView();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmclientadddot *frmclientadddot;
//---------------------------------------------------------------------------
#endif
