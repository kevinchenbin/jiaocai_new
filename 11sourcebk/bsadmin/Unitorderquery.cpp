//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitorderquery.h"
#include "UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmorderquery *frmorderquery;
//---------------------------------------------------------------------------
__fastcall Tfrmorderquery::Tfrmorderquery(TComponent* Owner,TADOConnection *con,int stgid,int modle,int tuihuo,boolean aisprint)
	: TForm(Owner)
{
	fstgid = stgid;
	fcon = con;
	fmodle = modle;
	ftuihuo = tuihuo;
	query->Connection = con;
	dtpstart->Date = Date();
	dtpend->Date = Date();
    TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	AnsiString sql;
	sql = "select * from SYS_BSSET where name = 'changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	ChangeDisplay  = aq->FieldByName("value")->AsBoolean ;

	sql = "select ID,Name from sys_user where stgid = " + IntToStr(fstgid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbuser->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	aq->First();
	cbuser->ItemIndex = cbuser->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );

	delete aq;

	if (!aisprint) {
       DBGrid1->PopupMenu=NULL; 
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery::spselectClientClick(TObject *Sender)
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

void Tfrmorderquery::ClientView()
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
void __fastcall Tfrmorderquery::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edclient->Text,fstgid);
	   if (mrOk == frm->ShowModal())
	   {
			ClientID = frm->GetSelectID();
			ClientView();
	   }
	   delete frm;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery::Button2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery::Button1Click(TObject *Sender)
{
	AnsiString sql;
	if (fmodle == 1) {
		sql = "select BS_OrderNoteHeader.OrderNtCode as NtCode,convert(nvarchar(10),HdTime,120) as HdTime,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_OrderNoteHeader.TotalAmount,BS_OrderNoteHeader.FixedPrice,BS_OrderNoteHeader.DiscountedPrice from BS_OrderNoteHeader ";
		if (chinorder->Checked ) {
			sqlwhere = " where BS_OrderNoteHeader.type = 1 ";
		}
		else
		{
			sqlwhere = " where BS_OrderNoteHeader.StgID = " + IntToStr(fstgid);
		}
		if (sqladd != "" && chshenhei->Checked ) {
			sqlwhere = sqlwhere + " and shenheistate = 1 ";
		}
		if (sqladd != "" && !chshenhei->Checked) {
			sqlwhere = sqlwhere + sqladd;
		}
	}else if (fmodle == 100) {
			sql = "select BS_OrderNoteHeader.OrderNtCode as NtCode,convert(nvarchar(10),HdTime,120) as HdTime,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_OrderNoteHeader.TotalAmount,BS_OrderNoteHeader.FixedPrice,BS_OrderNoteHeader.DiscountedPrice from BS_OrderNoteHeader where type = 1 ";
			sqlwhere = "";
			if (chstart->Checked ) {
				sqlwhere = sqlwhere + "  and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
			}
			if (chend->Checked ) {
				sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
			}
			if (chclient->Checked && edtclient->Text != "") {
				sqlwhere = sqlwhere + " and VendorID in (select id from dbo.GetChild("  + IntToStr(ClientID) + ")) ";
			}
			if (chcode->Checked && edcode->Text != "") {
				sqlwhere = sqlwhere +" and OrderNtCode = " + edcode->Text ;
			}
			sql  = sql + sqlwhere + " order by OrderNtCode";
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			return;
	}
	else if (fmodle==101) {  //  C网订单

			sql = "select OrderNtCode as NtCode,convert(nvarchar(10),HdTime,120) as HdTime,OrderUser as clientname,TotalAmount,FixedPrice,DiscountedPrice from C_BS_OrderNoteHeader where 1 = 1 ";
			sqlwhere = " ";
			if (chstart->Checked ) {
				sqlwhere = sqlwhere + "  and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
			}
			if (chend->Checked ) {
				sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
			}
			if (chclient->Checked && edtclient->Text != "") {
				sqlwhere = sqlwhere + " and OrderUser like '%"  + edtclient->Text + "%'";
			}
			if (chcode->Checked && edcode->Text != "") {
				sqlwhere = sqlwhere +" and OrderNtCode = " + edcode->Text ;
			}
			sql  = sql + sqlwhere + " order by OrderNtCode";
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			return;

	}
	else{
		if (ChangeDisplay) {
			sql = "select id,BS_WsaleNoteHeader.WsaleNtCodeStr as NtCode,BS_WsaleNoteHeader.WsaleNtCode,convert(nvarchar(10),HdTime,120) as HdTime,dbo.UF_BS_GetClientName(BS_WsaleNoteHeader.VendorID) as clientname,BS_WsaleNoteHeader.TotalAmount,BS_WsaleNoteHeader.FixedPrice,BS_WsaleNoteHeader.DiscountedPrice from BS_WsaleNoteHeader " ;
		}
		else
		{
			sql = "select id,kBS_WsaleNoteHeader.WsaleNtCode as NtCode,convert(nvarchar(10),HdTime,120) as HdTime,dbo.UF_BS_GetClientName(BS_WsaleNoteHeader.VendorID) as clientname,BS_WsaleNoteHeader.TotalAmount,BS_WsaleNoteHeader.FixedPrice,BS_WsaleNoteHeader.DiscountedPrice from BS_WsaleNoteHeader " ;
		}
		sqlwhere = " where BS_WsaleNoteHeader.StgID = " + IntToStr(fstgid);
		if (ftuihuo == 0) {
			sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.WsaleNtCodeInt > 0 ";
		}
		else if (ftuihuo == 2) {
			sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.state = 2 and BS_WsaleNoteHeader.WsaleNtCode <> 0 ";
		}
		else
		{
			sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.TWsaleNtCodeInt > 0 ";
		}
	}
	if (chstart->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
	}
	if (chuser->Checked && cbuser->Text != "") {
        int userid;
		try {
			userid = int(cbuser->Items->Objects[cbuser->ItemIndex]);
		} catch (...) {
			MessageBoxA(0,"请选择正确的操作员！","提示",MB_ICONERROR);
			return;
		}
		sqlwhere = sqlwhere + " and OperatorID = "  + IntToStr(userid);
	}
	if (chend->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
	}
	if (chclient->Checked && edtclient->Text != "") {
		sqlwhere = sqlwhere + " and VendorID in (select id from dbo.GetChild("  + IntToStr(ClientID) + ")) ";
	}
	if (chcode->Checked && edcode->Text != "") {
    	if (fmodle == 1) {
			sqlwhere = sqlwhere + " and OrderNtCode = " + edcode->Text ;
		}
		else
		{
			if (ChangeDisplay) {
				sqlwhere = sqlwhere + " and (WsaleNtCodeInt = " + edcode->Text + " or TWsaleNtCodeInt = " + edcode->Text + ") ";
			}
			else
			{
				sqlwhere = sqlwhere + " and WsaleNtCode = " + edcode->Text ;
			}
		}
	}
	sql = sql + sqlwhere;
	if (fmodle == 1) {
		sql = sql + " order by OrderNtCode";
	}
	else {
		sql = sql + " order by WsaleNtCodeStr";
	}
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------
AnsiString Tfrmorderquery::GetNoteCode()
{
	AnsiString recode;
	if (!query->IsEmpty() ) {
		if (fmodle == 2 && ChangeDisplay ) {
			recode = query->FieldByName("WsaleNtCode")->AsString ;
		}
		else if (fmodle == 101) {
            recode = query->FieldByName("NtCode")->AsString ;
		}
	   else{
			recode = query->FieldByName("NtCode")->AsString ;
		}
	}
	return recode;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery::DBGrid1DblClick(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery::DBGrid1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------

AnsiString Tfrmorderquery::GetWhere()
{
	return sqlwhere;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery::dtpstartChange(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderquery::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderquery::edtclientChange(TObject *Sender)
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

void __fastcall Tfrmorderquery::edcodeChange(TObject *Sender)
{
	if (edcode->Text != "") {
		chcode->Checked = true;
	}
	else
	{
    	chcode->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderquery::N2Click(TObject *Sender)
{
  if (query->IsEmpty()) {
			return;
		}
  AnsiString  clientname="";


   DBGrid1->DataSource->DataSet->DisableControls();
  	for (int i = 0 ; i < DBGrid1->SelectedRows->Count ; i++) {

	       	 DBGrid1->DataSource->DataSet->Bookmark = DBGrid1->SelectedRows->Items[i];
			 bm = DBGrid1->DataSource->DataSet->GetBookmark();
			 DBGrid1->DataSource->DataSet->GotoBookmark(bm);
			 clientname=clientname+ query->FieldByName("clientname")->AsAnsiString+",";
			 headerid= headerid+query->FieldByName("id")->AsAnsiString+",";

        }
        	DBGrid1->DataSource->DataSet->EnableControls();
     if (headerid=="") {
        MessageBox(Handle ,"提示","请选择单据！",MB_ICONWARNING|MB_SYSTEMMODAL);
	 }else
	 {
		 printnow=true;
		 ModalResult = mrOk ;
	 }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderquery::N1Click(TObject *Sender)
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

void __fastcall Tfrmorderquery::FormShow(TObject *Sender)
{
//

}
//---------------------------------------------------------------------------

