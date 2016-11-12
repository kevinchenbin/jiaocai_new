//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitrate.h"
#include "UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmrate *frmrate;
//---------------------------------------------------------------------------
__fastcall Tfrmrate::Tfrmrate(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
	con = cn;
	fstgid = stgid;
	aq1->Connection = cn;
	aq2->Connection = cn;
	aq3->Connection = cn;
	dtpstart->Date = Date();
	dtpend->Date = Date();
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = cn;
	AnsiString sql;
	sql = "select ID,AbbreviatedName from BS_PressInfo ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
	Clientid == -1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmrate::edpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
    	TADOQuery *aq = new TADOQuery(this);
		aq->Connection = con;
		AnsiString sql;
		sql = "select ID,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + edpress->Text + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbpress->Clear();
		while (!aq->Eof)
		{
			cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmrate::spselectClientClick(TObject *Sender)
{
		TfrmselectClient * frm = new TfrmselectClient(Application,con,"",fstgid);
	   if (mrOk == frm->ShowModal())
	   {
			Clientid = frm->GetSelectID();
			ClientView();
	   }
	   delete frm;
}
//---------------------------------------------------------------------------

void Tfrmrate::ClientView()
{
		if (Clientid == -1) {
			return;
		}
	   String sql;
	   TADOQuery * aq = new TADOQuery(NULL);
	   aq->Connection = con;
	   sql = "exec USP_BS_Client_View 0," + IntToStr(Clientid) ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		edtclient->Text = aq->FieldByName("Name")->AsAnsiString ;
		delete aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmrate::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TfrmselectClient * frm = new TfrmselectClient(Application,con,edclient->Text,fstgid);
	   if (mrOk == frm->ShowModal())
	   {
			Clientid = frm->GetSelectID();
			ClientView();
			edclient->Text = "";
	   }
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmrate::dbg3TitleClick(TColumn *Column)
{
	if (aq3->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aq3->Sort == "") {
		aq3->Sort =  Column->FieldName + " ASC";
	}
	else if (aq3->Sort == qusort) {
		aq3->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aq3->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmrate::dbg2TitleClick(TColumn *Column)
{
	if (aq2->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aq2->Sort == "") {
		aq2->Sort =  Column->FieldName + " ASC";
	}
	else if (aq2->Sort == qusort) {
		aq2->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aq2->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmrate::dbg1TitleClick(TColumn *Column)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aq1->Sort == "") {
		aq1->Sort =  Column->FieldName + " ASC";
	}
	else if (aq1->Sort == qusort) {
		aq1->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aq1->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmrate::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1 ) {    //按明细
		BtnView->Click();
	}
	if (Key == VK_F2 ) {    //按单
		BtnView1->Click();
	}
	if (Key == VK_F3 ) {    //按客户
		BtnView2->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmrate::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmrate::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmrate::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmrate::BtnViewClick(TObject *Sender)
{
	AnsiString sql,sqlwhere;
	if (chstart->Checked ) {
	   sqlwhere = sqlwhere + " and BS_OrderNoteHeader.HdTime > '" + DateToStr(dtpstart->Date) + "'" ;
	}
	if (chend->Checked) {
		sqlwhere = sqlwhere + " and BS_OrderNoteHeader.HdTime < '" + DateToStr(dtpend->Date) + " 23:59:59'" ;
	}
	if (chisbn->Checked ) {
		sqlwhere = sqlwhere + " and BS_BookCatalog.ISBN = '" + edisbn->Text + "'" ;
	}
	if (chname->Checked ) {
		sqlwhere = sqlwhere + " and BS_BookCatalog.Name like '%" + edname->Text + "%'" ;
	}
	if (chpress->Checked ) {
		sqlwhere = sqlwhere + " and BS_PressInfo.AbbreviatedName like '%" + cbpress->Text + "%'";
	}
	if (chclient->Checked ) {
		sqlwhere = sqlwhere + " and BS_OrderNoteHeader.VendorID in (select id from dbo.GetChild(" + IntToStr(Clientid) + "))";
	}
	sql = "select  BS_OrderNote.BkcatalogID,BS_OrderNote.Amount,BS_OrderNote.SendAmount, cast (case when BS_OrderNote.Amount <> 0 then BS_OrderNote.SendAmount*100/BS_OrderNote.Amount else 0 end as nvarchar(5))+'%' as fahuorate,A.fahuorate as totalrate ,"
			" dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price, "
			" BS_BookCatalog.Author,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName "
			" from BS_OrderNote left join BS_OrderNoteHeader "
			" on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id left join BS_BookCatalog "
			" on BS_OrderNote.BkcatalogID = BS_BookCatalog.id left join BS_PressInfo "
			" on BS_BookCatalog.PressID = BS_PressInfo.id "
			" left join "
			" (select  BS_OrderNote.BkcatalogID,cast (case when sum(BS_OrderNote.Amount) <> 0 then sum(BS_OrderNote.SendAmount)*100/sum(BS_OrderNote.Amount) else 0 end as nvarchar(5))+'%' as fahuorate "
			" from BS_OrderNote left join BS_OrderNoteHeader "
			" on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id left join BS_BookCatalog "
			" on BS_OrderNote.BkcatalogID = BS_BookCatalog.id left join BS_PressInfo "
			" on BS_BookCatalog.PressID = BS_PressInfo.id where BS_OrderNoteHeader.StgID = " + IntToStr(fstgid) + sqlwhere +
			" group by BS_OrderNote.BkcatalogID ) as A "
			" on  BS_OrderNote.BkcatalogID = A.BkcatalogID where BS_OrderNoteHeader.StgID = " + IntToStr(fstgid) + sqlwhere;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	dbg2->Visible = false;
	dbg3->Visible = false;
	dbg1->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmrate::BtnView1Click(TObject *Sender)
{
	AnsiString sql;
	sql = "select  BS_OrderNoteHeader.id,BS_OrderNoteHeader.OrderNtCode,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,sum(BS_OrderNote.Amount) as Amount,sum(BS_OrderNote.SendAmount) as SendAmount,cast (case when sum(BS_OrderNote.Amount) <> 0 then sum(BS_OrderNote.SendAmount)*100/sum(BS_OrderNote.Amount) else 0 end as nvarchar(5))+'%' as fahuorate "
			" from BS_OrderNote left join BS_OrderNoteHeader "
			" on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id left join BS_BookCatalog "
			" on BS_OrderNote.BkcatalogID = BS_BookCatalog.id left join BS_PressInfo "
			" on BS_BookCatalog.PressID = BS_PressInfo.id "
			" where BS_OrderNoteHeader.StgID = " + IntToStr(fstgid) ;
	if (chstart->Checked ) {
		sql = sql + " and BS_OrderNoteHeader.HdTime > '" + DateToStr(dtpstart->Date) + "'" ;
	}
	if (chend->Checked) {
		sql = sql + " and BS_OrderNoteHeader.HdTime < '" + DateToStr(dtpend->Date) + " 23:59:59'" ;
	}
	if (chclient->Checked ) {
		sql = sql + " and BS_OrderNoteHeader.VendorID in (select id from dbo.GetChild(" + IntToStr(Clientid) + "))";
	}
	sql = sql + " group by BS_OrderNoteHeader.id,BS_OrderNoteHeader.OrderNtCode,BS_OrderNoteHeader.VendorID ";
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();
	dbg1->Visible = false;
	dbg3->Visible = false;
	dbg2->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmrate::BtnView2Click(TObject *Sender)
{
	AnsiString sql;
	sql = "select  dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,sum(BS_OrderNote.Amount) as Amount,sum(BS_OrderNote.SendAmount) as SendAmount,cast (case when sum(BS_OrderNote.Amount) <> 0 then sum(BS_OrderNote.SendAmount)*100/sum(BS_OrderNote.Amount) else 0 end as nvarchar(5))+'%' as fahuorate "
			" from BS_OrderNote left join BS_OrderNoteHeader "
			" on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id left join BS_BookCatalog "
			" on BS_OrderNote.BkcatalogID = BS_BookCatalog.id left join BS_PressInfo "
			" on BS_BookCatalog.PressID = BS_PressInfo.id "
			" where BS_OrderNoteHeader.StgID = " + IntToStr(fstgid) ;
	if (chstart->Checked ) {
		sql = sql + " and BS_OrderNoteHeader.HdTime > '" + DateToStr(dtpstart->Date) + "'" ;
	}
	if (chend->Checked) {
		sql = sql + " and BS_OrderNoteHeader.HdTime < '" + DateToStr(dtpend->Date) + " 23:59:59'" ;
	}
	if (chclient->Checked ) {
		sql = sql + " and BS_OrderNoteHeader.VendorID in (select id from dbo.GetChild(" + IntToStr(Clientid) + "))";
	}
	sql = sql + " group by BS_OrderNoteHeader.VendorID";
	aq3->Close();
	aq3->SQL->Clear();
	aq3->SQL->Add(sql);
	aq3->Open();
	dbg1->Visible = false;
	dbg2->Visible = false;
	dbg3->Visible = true;
}
//---------------------------------------------------------------------------

