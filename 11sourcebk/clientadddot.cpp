//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "clientadddot.h"
#include "..\bsadmin\UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
Tfrmclientadddot *frmclientadddot;
//---------------------------------------------------------------------------
__fastcall Tfrmclientadddot::Tfrmclientadddot(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
	fcon = con;
	query->Connection = con;
	AnsiString sql;
	sql = "select rank() over(order by clientid) as xuhao,clientid,dbo.UF_BS_GetClientName(clientid) as clientname,adddot from BS_ClientAddDot";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	ClientID = -1;
	fstgid = stgid;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientadddot::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",fstgid);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		ClientView();
	}
	delete frm;
}
//---------------------------------------------------------------------------
void Tfrmclientadddot::ClientView()
{
	if (ClientID == -1) {
		return;
	}
	AnsiString sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	sql = "exec USP_BS_Client_View 0," + IntToStr(ClientID)  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edtclient->Text = aq->FieldByName("Name")->AsAnsiString ;
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientadddot::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString sql;
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edquery->Text,fstgid);
		if (mrOk == frm->ShowModal())
		{
			ClientID = frm->GetSelectID();
			ClientView();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientadddot::Button1Click(TObject *Sender)
{
	if (ClientID == -1 || edtclient->Text == "" || eddot->Text == "")  {
		return;
	}
	try {
		StrToFloat(eddot->Text) ;
	} catch (...) {
		MessageBoxA(0,"请输入正确的折扣!","警告",MB_ICONASTERISK);
		return;
	}
	AnsiString sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	sql = "select * from BS_ClientAddDot where Clientid = " + IntToStr(ClientID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount > 0) {
		sql = "update BS_ClientAddDot set Adddot = " + eddot->Text + " where Clientid = " + IntToStr(ClientID);
	}
	else
	{
		sql = "insert into BS_ClientAddDot(Clientid,Adddot) values(" + IntToStr(ClientID) + "," + eddot->Text + ")";
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	query->Close();
	query->Open();
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientadddot::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientadddot::N1Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
    AnsiString sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	sql = "delete from BS_ClientAddDot where Clientid = " + query->FieldByName("clientid")->AsAnsiString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	query->Close();
	query->Open();
	delete aq;
}
//---------------------------------------------------------------------------

