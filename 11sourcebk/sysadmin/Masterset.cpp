//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Masterset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmMasterset *frmMasterset;
//---------------------------------------------------------------------------
__fastcall TfrmMasterset::TfrmMasterset(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	aq->Connection = con;
	query->Connection = con;
	AnsiString sql ;
	sql = "select ID,Name,Master from SYS_StorageInfo ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMasterset::btokClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMasterset::FormClose(TObject *Sender, TCloseAction &Action)
{
    AnsiString sql;
	sql = "select count(*) as count from SYS_StorageInfo where Master = 1";
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("count")->AsInteger == 0 ) {
		MessageBoxA(0,"没有设置总店","提示",MB_ICONASTERISK);
		Action = caNone ;
		return;
	}
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMasterset::aqAfterPost(TDataSet *DataSet)
{
	aq->Active = false;
	aq->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMasterset::btconcelClick(TObject *Sender)
{
	AnsiString sql;
	sql = "update SYS_StorageInfo set Master = 1 where id = " + IntToStr(stgid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
    Close();
}
//---------------------------------------------------------------------------




