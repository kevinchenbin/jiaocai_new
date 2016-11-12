//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unitfahuoclient.h"
#include "UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmfahuoclient *frmfahuoclient;
//---------------------------------------------------------------------------
__fastcall Tfrmfahuoclient::Tfrmfahuoclient(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	fcon = con;
	ClientID = -1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfahuoclient::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edclient->Text,1);
		if (mrOk == frm->ShowModal())
		{
			ClientID = frm->GetSelectID();
			edtclient->SetFocus();
			ClientView();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------
void Tfrmfahuoclient::ClientView()
{
	if (ClientID == -1) {
		return;
	}
	String sql;
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
void __fastcall Tfrmfahuoclient::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",1);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		edtclient->SetFocus();
		ClientView();
	}
	delete frm;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfahuoclient::RzButton2Click(TObject *Sender)
{
	if (ClientID == -1) {
		return;
	}
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfahuoclient::RzButton1Click(TObject *Sender)
{
	AnsiString sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;

	switch (mode) {
		case 1:
			sql = "insert into CUST_CustomerInfo(name,type,PrentID) values('" + xiaoqu + "',3," + IntToStr(prentid) + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			sql = "select max(id) as id from CUST_CustomerInfo" ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			ClientID = aq->FieldByName("id")->AsInteger ;
			sql = "insert into CUST_CustomerStartMoney(CustomerID) values(" + IntToStr(ClientID) + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			break;
		case 2:
			sql = "insert into CUST_CustomerInfo(name,type,PrentID) values('" + xiaoqu + "',3," + IntToStr(prentid) + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			sql = "select max(id) as id from CUST_CustomerInfo" ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			ClientID = aq->FieldByName("id")->AsInteger ;
			sql = "insert into CUST_CustomerStartMoney(CustomerID) values(" + IntToStr(ClientID) + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();

			sql = "insert into CUST_CustomerInfo(name,type,PrentID) values('" + xueyuan + "',3," + IntToStr(prentid) + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			sql = "select max(id) as id from CUST_CustomerInfo" ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			ClientID = aq->FieldByName("id")->AsInteger ;
			sql = "insert into CUST_CustomerStartMoney(CustomerID) values(" + IntToStr(ClientID) + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			break;
		case 3:
			sql = "insert into CUST_CustomerInfo(name,type,PrentID) values('" + xiaoqu + "',3," + IntToStr(prentid) + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			sql = "select max(id) as id from CUST_CustomerInfo" ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			ClientID = aq->FieldByName("id")->AsInteger ;
			sql = "insert into CUST_CustomerStartMoney(CustomerID) values(" + IntToStr(ClientID) + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();

			sql = "insert into CUST_CustomerInfo(name,type,PrentID) values('" + xueyuan + "',3," + IntToStr(prentid) + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			sql = "select max(id) as id from CUST_CustomerInfo" ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			ClientID = aq->FieldByName("id")->AsInteger ;
			sql = "insert into CUST_CustomerStartMoney(CustomerID) values(" + IntToStr(ClientID) + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();

			sql = "insert into CUST_CustomerInfo(name,type,PrentID) values('" + classname + "',3," + IntToStr(prentid) + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			sql = "select max(id) as id from CUST_CustomerInfo" ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			ClientID = aq->FieldByName("id")->AsInteger ;
			sql = "insert into CUST_CustomerStartMoney(CustomerID) values(" + IntToStr(ClientID) + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			break;
    default:
		;
	}
	delete aq;
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
