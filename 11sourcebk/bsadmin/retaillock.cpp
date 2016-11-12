//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "retaillock.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmretaillock *frmretaillock;
//---------------------------------------------------------------------------
__fastcall Tfrmretaillock::Tfrmretaillock(TComponent* Owner,TADOConnection *con,int userid)
	: TForm(Owner)
{
	Userid = userid;
	aq->Connection = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmretaillock::edpasswordKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        btok->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretaillock::btokClick(TObject *Sender)
{
	String sql ;
	sql = "select * from SYS_User where id = " + IntToStr(Userid) + " and PassWord = '" + edpassword->Text.Trim() + "'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount == 0) {
		MessageBox(0,"ÃÜÂë´íÎó£¡","ÃÜÂë´íÎó" ,MB_OK);
		return;
	}
	else
	{
        Close();
	}
}
//---------------------------------------------------------------------------
