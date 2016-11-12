//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "QryNoteCodeForm1.h"
#include "NoteCode.h"
#include "..\bsadmin\UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzCmboBx"
#pragma link "RzSpnEdt"
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmQryNoteCode1 *frmQryNoteCode1;
//---------------------------------------------------------------------------
__fastcall TfrmQryNoteCode1::TfrmQryNoteCode1(TComponent* Owner,int modle,TADOConnection *con)
	: TfrmModalDialog(Owner)
{
	if (modle == 1) {
		ch1->Caption = "供应商";
		spselectClient->Visible = false;
		edtclient->Visible = false;
	}
	else
	{
		ch1->Caption = "客户";
		cbselect->Visible = false;
		DBGrid1->Columns->Items[0]->Title->Caption = "客户名称";
	}
	type = modle;
	fcon = con;
	query->Connection = con;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	String sql;
	if (modle == 1) {
		sql = "select * from CUST_CustomerInfo where Type = 1 order by Name";
	}
	else
	{
		sql = " select * from CUST_CustomerInfo where Type in (2,3) order by Name ";
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbselect->Clear();
	while(!aq->Eof)
	{
		cbselect->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
		aq->Next();
	}
	dtpstart->Date = Date();
	dtpend->Date = Date();
	ClientID = -1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmQryNoteCode1::dtedtDateChange(TObject *Sender)
{
	//
	//m_storageID =0;
	NoteCode nc(dtedtDate->Date, m_storageID, spedtID->IntValue);
    edtCode->Text = nc.AsString();
	m_stgNtCode = edtCode->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfrmQryNoteCode1::spedtIDChange(TObject *Sender)
{
	//
	if (spedtID->IntValue < 0 || spedtID->IntValue > 99999)
	{
		ShowMessage("单号错误!");
		return;
	}
    NoteCode nc(dtedtDate->Date, m_storageID, spedtID->IntValue);
    edtCode->Text = nc.AsString();
	m_stgNtCode = edtCode->Text;
}
//---------------------------------------------------------------------------

String TfrmQryNoteCode1::GetNoteCode()
{
	if (query->IsEmpty() ) {
		return "";
	}
	return query->FieldByName("MoneyCode")->AsAnsiString ;
}

//---------------------------------------------------------------------------
void __fastcall TfrmQryNoteCode1::FormShow(TObject *Sender)
{
	dtedtDate->Date = TDateTime::CurrentDate();
	NoteCode nc(dtedtDate->Date, m_storageID, spedtID->IntValue);
	edtCode->Text = nc.AsString();
	m_stgNtCode = edtCode->Text;
	chcode->Checked = false;
}
//---------------------------------------------------------------------------
void TfrmQryNoteCode1::SetstgID(int stgid)
{
	m_storageID = stgid;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryNoteCode1::RzButton2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryNoteCode1::RzButton1Click(TObject *Sender)
{
	sqlwhere = "select custmername,payment,MoneyCode,clearingtype,clearingstyle,Convert(varchar(20),date,111) as date,case state when 0 then '未审核' when 1 then '已审核' end as state,remarks from FN_CUSEndMoneyDocuments ";
	sqlwhere = sqlwhere + " where type = " + IntToStr(type) ;
	if (chstart->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',date) >= 0";
	}
	if (chend->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',date) <= 0";
	}
	if (chcode->Checked ) {
		sqlwhere = sqlwhere + " and MoneyCode = " + edtCode->Text ;
	}
	if (ch1->Checked ) {
		if (type == 1) {
			sqlwhere = sqlwhere + " and CustmerName = '" + cbselect->Text + "'";
		}
		else
		{
			sqlwhere = sqlwhere + " and cusid = " + IntToStr(ClientID);
		}
	}
	if (weishenhei) {
    	sqlwhere = sqlwhere + " and state = 0 ";
	}
	if (!master) {
		sqlwhere = sqlwhere + " and stgid = " + IntToStr(m_storageID);
	}
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sqlwhere);
	query->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryNoteCode1::DBGrid1DblClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
    ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryNoteCode1::DBGrid1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
    	if (query->IsEmpty() ) {
			return;
		}
		ModalResult = mrOk ;
	}

}
//---------------------------------------------------------------------------

String TfrmQryNoteCode1::GetSqlWhere()
{
	return sqlwhere;
}

//---------------------------------------------------------------------------
void __fastcall TfrmQryNoteCode1::dtpstartChange(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryNoteCode1::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryNoteCode1::edtCodeChange(TObject *Sender)
{
	if (edtCode->Text != "") {
		chcode->Checked = true;
	}
	else
	{
    	chcode->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryNoteCode1::cbselectChange(TObject *Sender)
{
	if (cbselect->Text != "") {
		ch1->Checked = true;
	}
	else
	{
    	ch1->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryNoteCode1::edtclientChange(TObject *Sender)
{
	if (edtclient->Text != "") {
		ch1->Checked = true;
	}
	else
	{
    	ch1->Checked = false;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmQryNoteCode1::edtQryVendorKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r')
	{
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		String sql;
		if (type == 1) {
			sql = " select * from CUST_CustomerInfo where Type = 1 and Name like '%"+ edtQryVendor->Text.Trim() + "%' and name <> '' ";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			cbselect->Clear();
			while(!aq->Eof)
			{
				cbselect->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
				aq->Next();
			}
			aq->First();
			cbselect->ItemIndex = cbselect->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
			cbselect->SetFocus();
		}
		else
		{
			TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edtQryVendor->Text,m_storageID);
			if (mrOk == frm->ShowModal())
			{
				ClientID = frm->GetSelectID();
				ClientView();
			}
			delete frm;
		}
		delete aq;
	}
}
//---------------------------------------------------------------------------
void TfrmQryNoteCode1::ClientView()
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


