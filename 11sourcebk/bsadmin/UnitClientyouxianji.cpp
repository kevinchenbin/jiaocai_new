//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitClientyouxianji.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmClientyouxianji *frmClientyouxianji;
//---------------------------------------------------------------------------
__fastcall TfrmClientyouxianji::TfrmClientyouxianji(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
	aq1->Connection = cn;
	aq2->Connection = cn;
	con = cn;
	fstgid = stgid;
	AnsiString sql;
	sql = "exec USP_BS_Set_Clientyouxianji 0,0," + IntToStr(stgid);
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	dbg2->Visible = false;
	type = 0;
}
//---------------------------------------------------------------------------


void __fastcall TfrmClientyouxianji::RzButton1Click(TObject *Sender)
{
	AnsiString sql;
	sql = "exec USP_BS_Set_Clientyouxianji 1,0," + IntToStr(fstgid);
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	dbg2->Visible = false;
	dbg1->Visible = true;
	type = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmClientyouxianji::RzButton2Click(TObject *Sender)
{
	AnsiString sql;
	sql = "exec USP_BS_Set_Clientyouxianji 1,1," + IntToStr(fstgid);
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();
	dbg1->Visible = false;
	dbg2->Visible = true;
	type = 1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmClientyouxianji::RzButton3Click(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

