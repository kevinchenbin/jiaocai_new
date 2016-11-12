//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitdaohuorate.h"
#include "UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmdaohuorate *frmdaohuorate;
//---------------------------------------------------------------------------
__fastcall Tfrmdaohuorate::Tfrmdaohuorate(TComponent* Owner,TADOConnection *cn,int stgid)
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
	sql = "select ID,Name from CUST_CustomerInfo where type = 1";
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbsupplier->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
	supplierid == -1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaohuorate::edpressKeyPress(TObject *Sender, wchar_t &Key)
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



//---------------------------------------------------------------------------
void __fastcall Tfrmdaohuorate::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
    	AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type = 1 and Name like '%" + edclient->Text + "%'";
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = con;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbsupplier->Clear();
		while (!aq->Eof)
		{
			cbsupplier->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaohuorate::dbg3TitleClick(TColumn *Column)
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
void __fastcall Tfrmdaohuorate::dbg2TitleClick(TColumn *Column)
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
void __fastcall Tfrmdaohuorate::dbg1TitleClick(TColumn *Column)
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
void __fastcall Tfrmdaohuorate::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaohuorate::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaohuorate::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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
	if (Key == VK_F4 ) {    //导出
		BtnExport->Click();
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

void __fastcall Tfrmdaohuorate::BtnViewClick(TObject *Sender)
{
	AnsiString sql,sqlwhere;
	if (chstart->Checked ) {
	   sqlwhere = sqlwhere + " and BS_ProcureNoteHeader.HdTime > '" + DateToStr(dtpstart->Date) + "'" ;
	}
	if (chend->Checked) {
		sqlwhere = sqlwhere + " and BS_ProcureNoteHeader.HdTime < '" + DateToStr(dtpend->Date) + " 23:59:59'" ;
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
	if (chsupplie->Checked ) {
		try {
			supplierid = int(cbsupplier->Items->Objects[cbsupplier->ItemIndex]);
			sqlwhere = sqlwhere + " and BS_ProcureNoteHeader.SupplierID = " + IntToStr(supplierid) ;
		} catch (...) {
        	MessageBoxA(0,"请选择正确的供应商!","提示",MB_ICONASTERISK);
			return;
		}
	}
	sql = "select  BS_ProcureNote.BkcatalogID,BS_ProcureNote.Amount,BS_ProcureNote.RecAmount, cast (case when BS_ProcureNote.Amount <> 0 then BS_ProcureNote.RecAmount*100/BS_ProcureNote.Amount else 0 end as nvarchar(5))+'%' as fahuorate,A.fahuorate as totalrate ,"
			" dbo.UF_BS_GetClientName(BS_ProcureNoteHeader.SupplierID) as clientname,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price, "
			" BS_BookCatalog.Author,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName "
			" from BS_ProcureNote left join BS_ProcureNoteHeader "
			" on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id left join BS_BookCatalog "
			" on BS_ProcureNote.BkcatalogID = BS_BookCatalog.id left join BS_PressInfo "
			" on BS_BookCatalog.PressID = BS_PressInfo.id "
			" left join "
			" (select  BS_ProcureNote.BkcatalogID,cast (case when sum(BS_ProcureNote.Amount) <> 0 then sum(BS_ProcureNote.RecAmount)*100/sum(BS_ProcureNote.Amount) else 0 end as nvarchar(5))+'%' as fahuorate "
			" from BS_ProcureNote left join BS_ProcureNoteHeader "
			" on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id left join BS_BookCatalog "
			" on BS_ProcureNote.BkcatalogID = BS_BookCatalog.id left join BS_PressInfo "
			" on BS_BookCatalog.PressID = BS_PressInfo.id where BS_ProcureNoteHeader.StgID = " + IntToStr(fstgid) + sqlwhere +
			" group by BS_ProcureNote.BkcatalogID ) as A "
			" on  BS_ProcureNote.BkcatalogID = A.BkcatalogID where BS_ProcureNoteHeader.StgID = " + IntToStr(fstgid) + sqlwhere;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	dbg2->Visible = false;
	dbg3->Visible = false;
	dbg1->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaohuorate::BtnView1Click(TObject *Sender)
{
	AnsiString sql;
	sql = "select  BS_ProcureNoteHeader.id,BS_ProcureNoteHeader.ProcureNtCode,dbo.UF_BS_GetClientName(BS_ProcureNoteHeader.SupplierID) as clientname,sum(BS_ProcureNote.Amount) as Amount,sum(BS_ProcureNote.RecAmount) as RecAmount,cast (case when sum(BS_ProcureNote.Amount) <> 0 then sum(BS_ProcureNote.RecAmount)*100/sum(BS_ProcureNote.Amount) else 0 end as nvarchar(5))+'%' as fahuorate "
			" from BS_ProcureNote left join BS_ProcureNoteHeader "
			" on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id left join BS_BookCatalog "
			" on BS_ProcureNote.BkcatalogID = BS_BookCatalog.id left join BS_PressInfo "
			" on BS_BookCatalog.PressID = BS_PressInfo.id "
			" where BS_ProcureNoteHeader.StgID = " + IntToStr(fstgid) ;
	if (chstart->Checked ) {
		sql = sql + " and BS_ProcureNoteHeader.HdTime > '" + DateToStr(dtpstart->Date) + "'" ;
	}
	if (chend->Checked) {
		sql = sql + " and BS_ProcureNoteHeader.HdTime < '" + DateToStr(dtpend->Date) + " 23:59:59'" ;
	}
	if (chsupplie->Checked ) {
		try {
			supplierid = int(cbsupplier->Items->Objects[cbsupplier->ItemIndex]);
			sql = sql + " and BS_ProcureNoteHeader.SupplierID = " + IntToStr(supplierid) ;
		} catch (...) {
			MessageBoxA(0,"请选择正确的供应商!","提示",MB_ICONASTERISK);
			return;
		}
	}
	sql = sql + " group by BS_ProcureNoteHeader.id,BS_ProcureNoteHeader.ProcureNtCode,BS_ProcureNoteHeader.SupplierID ";
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();
	dbg1->Visible = false;
	dbg3->Visible = false;
	dbg2->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaohuorate::BtnView2Click(TObject *Sender)
{
	AnsiString sql;
	sql = "select  dbo.UF_BS_GetClientName(BS_ProcureNoteHeader.SupplierID) as clientname,sum(BS_ProcureNote.Amount) as Amount,sum(BS_ProcureNote.RecAmount) as RecAmount,cast (case when sum(BS_ProcureNote.Amount) <> 0 then sum(BS_ProcureNote.RecAmount)*100/sum(BS_ProcureNote.Amount) else 0 end as nvarchar(5))+'%' as fahuorate "
			" from BS_ProcureNote left join BS_ProcureNoteHeader "
			" on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id left join BS_BookCatalog "
			" on BS_ProcureNote.BkcatalogID = BS_BookCatalog.id left join BS_PressInfo "
			" on BS_BookCatalog.PressID = BS_PressInfo.id "
			" where BS_ProcureNoteHeader.StgID = " + IntToStr(fstgid) ;
	if (chstart->Checked ) {
		sql = sql + " and BS_ProcureNoteHeader.HdTime > '" + DateToStr(dtpstart->Date) + "'" ;
	}
	if (chend->Checked) {
		sql = sql + " and BS_ProcureNoteHeader.HdTime < '" + DateToStr(dtpend->Date) + " 23:59:59'" ;
	}
	if (chsupplie->Checked ) {
		try {
			supplierid = int(cbsupplier->Items->Objects[cbsupplier->ItemIndex]);
			sql = sql + " and BS_ProcureNoteHeader.SupplierID = " + IntToStr(supplierid) ;
		} catch (...) {
			MessageBoxA(0,"请选择正确的供应商!","提示",MB_ICONASTERISK);
			return;
		}
	}
	sql = sql + " group by BS_ProcureNoteHeader.SupplierID";
	aq3->Close();
	aq3->SQL->Clear();
	aq3->SQL->Add(sql);
	aq3->Open();
	dbg1->Visible = false;
	dbg2->Visible = false;
	dbg3->Visible = true;
}
//---------------------------------------------------------------------------





void __fastcall Tfrmdaohuorate::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

