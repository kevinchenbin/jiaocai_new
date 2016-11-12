//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unitpsinorder.h"
#include "UnitSelectClient.h"
#include "NoteCode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
Tfrmpsinorder *frmpsinorder;
//---------------------------------------------------------------------------
__fastcall Tfrmpsinorder::Tfrmpsinorder(TComponent* Owner,TADOConnection *cn,int stgid,int userid,int headid)
	: TForm(Owner)
{
	con = cn;
	fstgid = stgid;
	fuserid = userid;
	ClientID = -1;
	query->Connection = cn;
	dtpstart->Date = Date();
	dtpend->Date = Date();
	fheadid = headid;
	dtedtDate->Date = Date();
	chordercode->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpsinorder::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TfrmselectClient * frm = new TfrmselectClient(Application,con,edclient->Text,fstgid);
		if (mrOk == frm->ShowModal())
		{
			ClientID = frm->GetSelectID();
			ClientView();
			edtclient->SetFocus();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------
void Tfrmpsinorder::ClientView()
{
	if (ClientID == -1) {
		return;
	}
	String sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = con;
	sql = "exec USP_BS_Client_View 0," + IntToStr(ClientID)  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edtclient->Text = aq->FieldByName("Name")->AsAnsiString ;
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpsinorder::spselectClientClick(TObject *Sender)
{

	TfrmselectClient * frm = new TfrmselectClient(Application,con,"",fstgid);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		edtclient->SetFocus();
		ClientView();
	}
	delete frm;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpsinorder::RzButton1Click(TObject *Sender)
{
	AnsiString sql;
	sql = "select distinct stk_bookinfo.id as stkid,CUST_CustomerInfo.name as suppliername,stk_bookinfo.amount as stkamount,BS_OrderNote.id as noteid,bs_bookcatalog.id,BS_OrderNoteHeader.OrderNtCode,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as ClientName,BS_OrderNoteHeader.id,convert(nvarchar(10),BS_OrderNoteHeader.HdTime,120) as HdTime,BS_OrderNote.UnsendAmount,case when order_lock.usableamount + BS_OrderNote.localnum > BS_OrderNote.UnsendAmount then BS_OrderNote.UnsendAmount else order_lock.usableamount + BS_OrderNote.localnum end as fenamount,order_lock.usableamount, "
			" BS_OrderNoteHeader.Remarks,bs_bookcatalog.isbn,bs_bookcatalog.name,bs_bookcatalog.price,bs_bookcatalog.author,bs_bookcatalog.presscount,bs_bookcatalog.pressdate,BS_PressInfo.AbbreviatedName,BS_OrderNote.amount,BS_OrderNote.discount"
			" from stk_bookinfo left join bs_bookcatalog on bs_bookcatalog.id = stk_bookinfo.bkcatalogid "
			" left join BS_OrderNote on bs_bookcatalog.id = BS_OrderNote.BkcatalogID"
			" left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" left join order_lock on bs_bookcatalog.id = order_lock.bkcatalogid "
			" left join BS_PressInfo on bs_bookcatalog.pressid = BS_PressInfo.id "
			" left join CUST_CustomerInfo on stk_bookinfo.supplierid = CUST_CustomerInfo.id";

	sqlwhere = " where BS_OrderNote.UnsendAmount > 0 and BS_OrderNote.state = 0 and BS_OrderNoteHeader.state in (0,1) and BS_OrderNoteHeader.type = 1 and BS_OrderNoteHeader.stgid = " + IntToStr(fstgid)  ;
	if (chordercode->Checked && edordercode->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNoteHeader.OrderNtCode = " + edordercode->Text ;
	}
	if (chstart->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',BS_OrderNoteHeader.HdTime) >= 0 ";
	}
	if (chend->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',BS_OrderNoteHeader.HdTime) <= 0 ";
	}
	if (chclient->Checked && edtclient->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNoteHeader.VendorID in (select id from dbo.GetChild(" + IntToStr(ClientID) + ")) ";
	}
	
	sql = sql + sqlwhere;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpsinorder::dtpstartChange(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpsinorder::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpsinorder::edtclientChange(TObject *Sender)
{
	if (edtclient->Text != "") {
		chclient->Checked = true;
	}
	else
	{
    	chclient->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpsinorder::dtedtDateChange(TObject *Sender)
{
	NoteCode nc(dtedtDate->Date, spstgid->IntValue, spedtID->IntValue);
	edordercode->Text = nc.AsString();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpsinorder::spedtIDChange(TObject *Sender)
{
	if (spedtID->IntValue < 0 || spedtID->IntValue > 99999)
	{
		ShowMessage("µ¥ºÅ´íÎó!");
		return;
	}
	NoteCode nc(dtedtDate->Date, spstgid->IntValue, spedtID->IntValue);
	edordercode->Text = nc.AsString();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpsinorder::edordercodeChange(TObject *Sender)
{
	if (edordercode->Text != "") {
		chordercode->Checked = true;
	}
	else
	{
    	chordercode->Checked = false;
	}
}

//---------------------------------------------------------------------------

void __fastcall Tfrmpsinorder::DBGrid1DblClick(TObject *Sender)
{
	Diaobo->AddNote(query->FieldByName("stkid")->AsInteger);
	Diaobo->aquery->Edit();

	if (query->FieldByName("fenamount")->AsInteger > query->FieldByName("stkamount")->AsInteger) {
		Diaobo->aquery->FieldByName("Amount")->AsInteger = query->FieldByName("stkamount")->AsInteger ;
		Diaobo->aquery->FieldByName("amountbk")->AsInteger = query->FieldByName("stkamount")->AsInteger ;
	}
	else
	{
    	Diaobo->aquery->FieldByName("Amount")->AsInteger = query->FieldByName("fenamount")->AsInteger ;
		Diaobo->aquery->FieldByName("amountbk")->AsInteger = query->FieldByName("fenamount")->AsInteger ;
	}
	Diaobo->aquery->FieldByName("orderid")->AsInteger = query->FieldByName("noteid")->AsInteger ;
	try {
		Diaobo->aquery->UpdateBatch(arCurrent);
	} catch (...) {
	}
}
//---------------------------------------------------------------------------

