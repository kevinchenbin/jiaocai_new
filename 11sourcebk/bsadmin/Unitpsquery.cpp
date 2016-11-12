//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitpsquery.h"
#include "NoteCode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
Tfrmpsquery *frmpsquery;
//---------------------------------------------------------------------------
__fastcall Tfrmpsquery::Tfrmpsquery(TComponent* Owner,TADOConnection *con,int stgid,int type)
	: TForm(Owner)
{
	fstgid  = stgid;
	ftype = type;
	query->Connection = con;
	spstorage->Text = stgid;
	dtpstart->Date = Date();
	dtpend->Date = Date();
	dtedtDate->Date = Date();
	chcode->Checked = false;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	AnsiString sql;
	sql = "select id,name from SYS_StorageInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cboutstorage->AddItem(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
        cbinstorage->AddItem(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
		aq->Next();
	}
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpsquery::dtedtDateChange(TObject *Sender)
{
	NoteCode nc(dtedtDate->Date, spstorage->IntValue, spedtID->IntValue);
	edcode->Text = nc.AsString();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpsquery::edcodeChange(TObject *Sender)
{
	if (edcode->Text == "") {
		chcode->Checked = false;
	}
	else
	{
    	chcode->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpsquery::dtpstartChange(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpsquery::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmpsquery::cboutstorageChange(TObject *Sender)
{
	if (cboutstorage->Text != "") {
		choutstorage->Checked = true;
	}
	else
	{
    	choutstorage->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpsquery::cbinstorageChange(TObject *Sender)
{
	if (cbinstorage->Text != "") {
		chinstorage->Checked = true;
	}
	else
	{
		chinstorage->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpsquery::Button1Click(TObject *Sender)
{
	AnsiString sql;
	sql = "select BS_ZN_DiaoNoteHeader.ZNDiaoNtCode,BS_ZN_DiaoNoteHeader.HdTime,"
		" SYS_StorageInfo.name as stgnameout,SYS_StorageInfo1.name as stgnamein "
		" from BS_ZN_DiaoNoteHeader left join SYS_StorageInfo on BS_ZN_DiaoNoteHeader.outstorage = SYS_StorageInfo.id "
		" left join SYS_StorageInfo as SYS_StorageInfo1 on BS_ZN_DiaoNoteHeader.instorage = SYS_StorageInfo1.id ";
	sqlwhere = " where BS_ZN_DiaoNoteHeader.type = " + IntToStr(ftype) + " and (instorage = " + IntToStr(fstgid) + " or outstorage = " +  IntToStr(fstgid) + ")";
	if (chstart->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
	}
	if (chend->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
	}
	if (choutstorage->Checked && cboutstorage->Text != "" ) {
		sqlwhere = sqlwhere + " and SYS_StorageInfo.name = '" + cboutstorage->Text.Trim() + "'";
	}
	if (chinstorage->Checked && cbinstorage->Text != "") {
		sqlwhere = sqlwhere + " and SYS_StorageInfo1.name = '" + cbinstorage->Text.Trim() + "'";
	}
	if (chcode->Checked && edcode->Text != "") {
		sqlwhere = sqlwhere + " and BS_ZN_DiaoNoteHeader.ZNDiaoNtCode = " + edcode->Text;
	}
	sql = sql + sqlwhere ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpsquery::Button2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpsquery::DBGrid1DblClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
        return;
	}
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
AnsiString Tfrmpsquery::GetNoteCode()
{
	AnsiString recode;
	recode = query->FieldByName("ZNDiaoNtCode")->AsString ;
	return recode;
}
//---------------------------------------------------------------------------
AnsiString Tfrmpsquery::Getsqlwhere()
{
	return sqlwhere;
}
//---------------------------------------------------------------------------
