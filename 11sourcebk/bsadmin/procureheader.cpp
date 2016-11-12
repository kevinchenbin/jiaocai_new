//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "procureheader.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBCtrlsEh"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmprocureheader *frmprocureheader;
//---------------------------------------------------------------------------
__fastcall Tfrmprocureheader::Tfrmprocureheader(TComponent* Owner)
	: TForm(Owner)
{
	dtstart->Value = Date();
	dtend->Value = Date();
}
//---------------------------------------------------------------------------

void Tfrmprocureheader::Init(LandInfo* li)
{
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	aq->Connection = li->con ;
	aq1->Connection = li->con ;
	aq2->Connection = li->con ;
	AnsiString sql;
	sql = "select ID,Name from CUST_CustomerInfo where type = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject *)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}

	if (groupid == -1) {
    	sql = "select max(groupid) as groupid from BS_Tmpheader ";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->IsEmpty() ) {
			groupid = 0;
		}
		else
		{
			groupid = aq->FieldByName("groupid")->AsInteger + 1;
		}
	}
	sql = "select * from BS_Tmpheader where groupid = " + IntToStr(groupid);
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocureheader::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type = 1 and Name like '%" + edquery->Text + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbsupplier->Clear();
		while (!aq->Eof )
		{
			cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject *)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbsupplier->SetFocus();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject *)aq->FieldByName("ID")->AsInteger );
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprocureheader::SpeedButton1Click(TObject *Sender)
{
	AnsiString sql,sqlwhere;
	if (chznprocure->Checked) {
		sql = "select BS_ZN_ProcureNoteHeader.ID,ZNProcureNtCode as ProcureNtCode,HdTime,'智能采购单' as Name,2 as type from BS_ZN_ProcureNoteHeader where BS_ZN_ProcureNoteHeader.state <> 3 and BS_ZN_ProcureNoteHeader.StgID = " + IntToStr(linfo.storageID) ;   //智能采购
	}
	else
	{
		sql = "select BS_ProcureNoteHeader.ID,ProcureNtCode,HdTime,Name,1 as type from BS_ProcureNoteHeader left join CUST_CustomerInfo on BS_ProcureNoteHeader.SupplierID = CUST_CustomerInfo.id where BS_ProcureNoteHeader.state <> 3 and BS_ProcureNoteHeader.StgID = " + IntToStr(linfo.storageID) ;   //一般采购
	}
	if (chprocure->Checked ) {
		if (chznprocure->Checked) {
			sqlwhere = " and ZNProcureNtCode = " + edprocurecode->Text ;
		}
		else
		{
			sqlwhere = " and ProcureNtCode = " + edprocurecode->Text ;
		}
	}
	if (chsupplier->Checked && !chznprocure->Checked) {
		sqlwhere = sqlwhere + " and CUST_CustomerInfo.Name like '%" + cbsupplier->Text + "%'";
	}
	if (chstart->Checked) {
		sqlwhere = sqlwhere + " and HdTime >= '" + DateToStr(dtstart->Value) + " 0:00:00'";
	}
	if (chend->Checked ) {
		sqlwhere = sqlwhere + " and HdTime <= '" + DateToStr(dtend->Value) + " 23:59:59'";
	}
	sql = sql + sqlwhere;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprocureheader::SpeedButton3Click(TObject *Sender)
{
	if (aq2->IsEmpty() ) {
		MessageBoxA(0,"请添加采购单！","提示",MB_ICONASTERISK);
		return;
	}
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocureheader::N1Click(TObject *Sender)
{
	AnsiString sql;
	sql = "delete from BS_Tmpheader where id = " + aq2->FieldByName("id")->AsString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	aq2->Active = false;
	aq2->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocureheader::N2Click(TObject *Sender)
{
	for (int i = 1; i <= aq1->RecordCount; i++) {
		DBGrid1->DataSource->DataSet->RecNo = i;
		DBGrid1->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocureheader::SpeedButton2Click(TObject *Sender)
{
	//追加
	if (aq1->IsEmpty() ) {
		return;
	}
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	Variant   locvalues[2];
	if (DBGrid1->SelectedRows->Count > 0) {
		for (int i =0; i < DBGrid1->SelectedRows->Count ; i++) {
			aq1->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
			locvalues[0]   =   Variant(aq1->FieldByName("ProcureNtCode")->AsString);
			locvalues[1]   =   Variant(aq1->FieldByName("type")->AsString);
			if ( !aq2->Locate("code;type",VarArrayOf(locvalues,1),Opts))
			{
				if (aq2->State != dsInsert ) {
					aq2->Append();
				}
				aq2->FieldByName("groupid")->AsInteger = groupid;
				aq2->FieldByName("headerid")->AsInteger = aq1->FieldByName("ID")->AsInteger ;
				aq2->FieldByName("code")->AsString = aq1->FieldByName("ProcureNtCode")->AsString ;
				aq2->FieldByName("name")->AsString = aq1->FieldByName("Name")->AsString ;
				aq2->FieldByName("headtime")->AsDateTime  = aq1->FieldByName("HdTime")->AsDateTime ;
				aq2->FieldByName("type")->AsInteger = aq1->FieldByName("type")->AsInteger;  //智能入库采购单头
				aq2->UpdateBatch(arAll);
			}
		}
	}
	else
	{
		locvalues[0]   =   Variant(aq1->FieldByName("ProcureNtCode")->AsString);
		locvalues[1]   =   Variant(aq1->FieldByName("type")->AsString);
		if ( !aq2->Locate("code;type",VarArrayOf(locvalues,1),Opts))
		{
        	if (aq2->State != dsInsert ) {
				aq2->Append();
			}
			aq2->FieldByName("groupid")->AsInteger = groupid;
			aq2->FieldByName("headerid")->AsInteger = aq1->FieldByName("ID")->AsInteger ;
			aq2->FieldByName("code")->AsString = aq1->FieldByName("ProcureNtCode")->AsString ;
			aq2->FieldByName("name")->AsString = aq1->FieldByName("Name")->AsString ;
			aq2->FieldByName("headtime")->AsDateTime  = aq1->FieldByName("HdTime")->AsDateTime ;
			aq2->FieldByName("type")->AsInteger = aq1->FieldByName("type")->AsInteger;  //智能入库采购单头
			aq2->UpdateBatch(arAll);
		}
		else
		{
			DBGrid2->SelectedRows->CurrentRowSelected = true;
			DBGrid2->SetFocus();
		}
	}
	aq2->Active = false;
	aq2->Active = true;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmprocureheader::BtnAlignBottomClick(TObject *Sender)
{
   WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocureheader::BtnExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocureheader::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {
	   BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {
	   BtnExit->Click();
	}
			if (Shift.Contains(ssCtrl)&& Key ==90) {
            	WindowState = wsNormal  ;
		}
}
//---------------------------------------------------------------------------

