//---------------------------------------------------------------------------

#ifndef unitfahuoclientH
#define unitfahuoclientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmfahuoclient : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TSpeedButton *spselectClient;
	TEdit *edclient;
	TEdit *edtclient;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TADOConnection *fcon;
	void __fastcall edclientKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spselectClientClick(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmfahuoclient(TComponent* Owner,TADOConnection *con);
	int ClientID;
	void ClientView();
	int prentid,mode;   //mode = 1 ,加校区   2/加校区学院    2加校区学院班级
	AnsiString xiaoqu,xueyuan,classname;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmfahuoclient *frmfahuoclient;
//---------------------------------------------------------------------------
#endif
