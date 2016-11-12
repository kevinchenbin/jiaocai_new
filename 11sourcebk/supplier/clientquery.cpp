//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "clientquery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmclientquery *frmclientquery;
//---------------------------------------------------------------------------
__fastcall Tfrmclientquery::Tfrmclientquery(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientquery::SpeedButton2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientquery::SpeedButton1Click(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientquery::edclientnameKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------
