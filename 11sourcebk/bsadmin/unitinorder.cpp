//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unitinorder.h"
#include "UnitSelectClient.h"
#include "NoteCode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
Tfrminorder *frminorder;
//---------------------------------------------------------------------------
__fastcall Tfrminorder::Tfrminorder(TComponent* Owner,TADOConnection *cn,int stgid,int userid,int headid)
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
void __fastcall Tfrminorder::edclientKeyPress(TObject *Sender, wchar_t &Key)
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
void Tfrminorder::ClientView()
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
void __fastcall Tfrminorder::spselectClientClick(TObject *Sender)
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
void __fastcall Tfrminorder::RzButton1Click(TObject *Sender)
{
	AnsiString sql;
	sql = "select distinct BS_OrderNote.id as noteid,bs_bookcatalog.id,BS_OrderNoteHeader.OrderNtCode,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as ClientName,BS_OrderNoteHeader.id,convert(nvarchar(10),BS_OrderNoteHeader.HdTime,120) as HdTime,order_lock.usableamount,order_lock.stkamount,BS_OrderNote.UnsendAmount, "
			" BS_OrderNoteHeader.Remarks,bs_bookcatalog.isbn,bs_bookcatalog.name,bs_bookcatalog.price,bs_bookcatalog.author,bs_bookcatalog.presscount,bs_bookcatalog.pressdate,BS_PressInfo.AbbreviatedName,BS_OrderNote.amount,BS_OrderNote.discount"
			" from BS_OrderNoteHeader left join BS_OrderNote on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" left join bs_bookcatalog on  bs_bookcatalog.id = BS_OrderNote.BkcatalogID "
			" left join order_lock on bs_bookcatalog.id = order_lock.bkcatalogid "
			" left join BS_PressInfo on bs_bookcatalog.pressid = BS_PressInfo.id";

	sqlwhere = " where BS_OrderNote.needprocurenum <> 10 and BS_OrderNote.UnsendAmount > 0 and BS_OrderNote.state = 0 and BS_OrderNoteHeader.state in (0,1) and BS_OrderNoteHeader.type = 1 and BS_OrderNoteHeader.shenheistate = 1 " ;
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

void __fastcall Tfrminorder::dtpstartChange(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::edtclientChange(TObject *Sender)
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

void __fastcall Tfrminorder::dtedtDateChange(TObject *Sender)
{
	NoteCode nc(dtedtDate->Date, fstgid, spedtID->IntValue);
	edordercode->Text = nc.AsString();
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::spedtIDChange(TObject *Sender)
{
	if (spedtID->IntValue < 0 || spedtID->IntValue > 99999)
	{
		ShowMessage("���Ŵ���!");
		return;
	}
	NoteCode nc(dtedtDate->Date, fstgid, spedtID->IntValue);
	edordercode->Text = nc.AsString();
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::edordercodeChange(TObject *Sender)
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

void __fastcall Tfrminorder::RzButton3Click(TObject *Sender)
{
	//ת��ɹ�
	if (query->IsEmpty() ) {
		return;
	}
	if (DBGrid1->SelectedRows->Count > 0) {
		for (int i =0; i < DBGrid1->SelectedRows->Count ; i++) {
			query->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
			int ret = pro->AddNote(supplierid,query->FieldByName("id")->AsInteger);
			if (ret == 1) {
				pro->dsetNote->Edit();
				pro->dsetNote->FieldByName("Amount")->AsInteger = query->FieldByName("amount")->AsInteger;
				pro->dsetNote->FieldByName("Discount")->AsFloat = query->FieldByName("discount")->AsFloat ;
				pro->dsetNote->FieldByName("orderid")->AsString = query->FieldByName("noteid")->AsString ;
				pro->dsetNote->FieldByName("ordercode")->AsString = query->FieldByName("OrderNtCode")->AsString  ;
				pro->dsetNote->FieldByName("clientname")->AsString = query->FieldByName("ClientName")->AsString ;
				pro->dsetNote->UpdateBatch(arCurrent);

			}
			else if (ret == 2) {
            	pro->dsetNote->Edit();
				pro->dsetNote->FieldByName("Amount")->AsInteger = pro->dsetNote->FieldByName("Amount")->AsInteger + query->FieldByName("amount")->AsInteger;
				pro->dsetNote->FieldByName("orderid")->AsString = pro->dsetNote->FieldByName("orderid")->AsString + "," + query->FieldByName("noteid")->AsInteger ;
				if (pro->dsetNote->FieldByName("ordercode")->AsString == "") {
					pro->dsetNote->FieldByName("ordercode")->AsString = query->FieldByName("OrderNtCode")->AsString  ;
				}
				else
				{
					pro->dsetNote->FieldByName("ordercode")->AsString = pro->dsetNote->FieldByName("ordercode")->AsString + "," + query->FieldByName("OrderNtCode")->AsString  ;
				}

				if (pro->dsetNote->FieldByName("clientname")->AsString == "") {
					pro->dsetNote->FieldByName("clientname")->AsString = query->FieldByName("ClientName")->AsString ;
				}
				else
				{
					pro->dsetNote->FieldByName("clientname")->AsString = pro->dsetNote->FieldByName("clientname")->AsString + "," + query->FieldByName("ClientName")->AsString ;
				}

				pro->dsetNote->UpdateBatch(arCurrent);
			}
            updaterecord();
	   }
	}
	else
	{
        int ret = pro->AddNote(supplierid,query->FieldByName("id")->AsInteger);
		if (ret == 1) {
			pro->dsetNote->Edit();
			pro->dsetNote->FieldByName("Amount")->AsInteger = query->FieldByName("amount")->AsInteger;
			pro->dsetNote->FieldByName("Discount")->AsFloat = query->FieldByName("discount")->AsFloat ;
			pro->dsetNote->FieldByName("orderid")->AsString = query->FieldByName("noteid")->AsString ;
			pro->dsetNote->FieldByName("ordercode")->AsString = query->FieldByName("OrderNtCode")->AsString  ;
			pro->dsetNote->FieldByName("clientname")->AsString = query->FieldByName("ClientName")->AsString ;
			pro->dsetNote->UpdateBatch(arCurrent);

		}
		else if (ret == 2) {
			pro->dsetNote->Edit();
			pro->dsetNote->FieldByName("Amount")->AsInteger = pro->dsetNote->FieldByName("Amount")->AsInteger + query->FieldByName("amount")->AsInteger;
				pro->dsetNote->FieldByName("orderid")->AsString = pro->dsetNote->FieldByName("orderid")->AsString + "," + query->FieldByName("noteid")->AsInteger ;
				if (pro->dsetNote->FieldByName("ordercode")->AsString == "") {
					pro->dsetNote->FieldByName("ordercode")->AsString = query->FieldByName("OrderNtCode")->AsString  ;
				}
				else
				{
					pro->dsetNote->FieldByName("ordercode")->AsString = pro->dsetNote->FieldByName("ordercode")->AsString + "," + query->FieldByName("OrderNtCode")->AsString  ;
				}

				if (pro->dsetNote->FieldByName("clientname")->AsString == "") {
					pro->dsetNote->FieldByName("clientname")->AsString = query->FieldByName("ClientName")->AsString ;
				}
				else
				{
					pro->dsetNote->FieldByName("clientname")->AsString = pro->dsetNote->FieldByName("clientname")->AsString + "," + query->FieldByName("ClientName")->AsString ;
				}
			pro->dsetNote->UpdateBatch(arCurrent);
		}
		updaterecord();
	}
	pro->dsetNtHeader->Edit();
	pro->dsetNtHeader->FieldByName("inorder")->AsInteger = 1;
	pro->dsetNtHeader->UpdateBatch(arCurrent);

}
//---------------------------------------------------------------------------
void Tfrminorder::updaterecord()
{
	AnsiString sql;
	sql  = "update bs_ordernote set needprocurenum = 10 where id = " + query->FieldByName("noteid")->AsAnsiString ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::N1Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= query->RecordCount; i++) {
		DBGrid1->DataSource->DataSet->RecNo = i;
		DBGrid1->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::DBGrid1TitleClick(TColumn *Column)
{
	if (query->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (query->Sort == "") {
		query->Sort =  Column->FieldName + " ASC";
	}
	else if (query->Sort == qusort) {
		query->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		query->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

