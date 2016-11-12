//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Setunite.h"
#include "PressAdminForm.h"
#include "BooKTypeAdminForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
TfrmSetunite *frmSetunite;
//---------------------------------------------------------------------------
__fastcall TfrmSetunite::TfrmSetunite(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
   String sql ;
   fcon = con;
   sql = "select ID,Name from BS_BookType ";
   query->Connection = con;
   query->Close();
   query->SQL->Clear();
   query->SQL->Add(sql);
   query->Open();
   while(!query->Eof)
   {
	 rcbtype->AddItem(query->FieldByName("ID")->AsAnsiString + query->FieldByName("name")->AsAnsiString, (TObject*)query->FieldByName("ID")->AsInteger );
	 query->Next();
   }
	sql = "select ID,abbreviatedname,PresentNum from BS_PressInfo ";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while(!query->Eof)
	{
		rcbpress->AddItem(query->FieldByName("PresentNum")->AsAnsiString.Trim() + query->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)query->FieldByName("ID")->AsInteger );
		query->Next();
	}
	datapressday->Date = Date();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetunite::cbpriceKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        editprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetunite::editpriceKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        cbbook->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetunite::cbbookKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edbook->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetunite::edbookKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        cbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetunite::cbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        rcbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetunite::rcbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        cbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetunite::cbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        rcbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetunite::rcbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        cbpressday->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetunite::cbpressdayKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        datapressday->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetunite::datapressdayKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
        cbpresscount->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetunite::cbpresscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
        sedpresscount->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetunite::sedpresscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
        btok->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetunite::btokClick(TObject *Sender)
{
    String price = editprice->Text ;
	price = price.SubString(price.Pos("гд")+1,price.Length()-price.Pos("гд") );
	editprice->Text = price;
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetunite::btcancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetunite::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetunite::btaddtypeClick(TObject *Sender)
{
	TfrmBookTypeAdmin* frm = new TfrmBookTypeAdmin(Application);
	frm->Init(Application,fcon);
    frm->Visible = false;
	frm->ShowModal();
	delete frm;
	String sql ;
	sql = "select ID,Name from BS_BookType ";
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	rcbtype->Clear();
	while(!aq->Eof)
	{
		rcbtype->AddItem(aq->FieldByName("ID")->AsAnsiString + aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetunite::btaddpressClick(TObject *Sender)
{
	TfrmPressAdmin* frm = new TfrmPressAdmin(Application);
	frm->Init(Application, fcon);
	frm->FormStyle = fsNormal ;
    frm->Visible = false;
	frm->Position = poMainFormCenter ;
	frm->ShowModal();
	delete frm;
	String sql;
	sql = "select ID,abbreviatedname,PresentNum from BS_PressInfo ";
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	rcbpress->Clear();
	while(!aq->Eof)
	{
		rcbpress->AddItem(aq->FieldByName("PresentNum")->AsAnsiString.Trim() + aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
   	}
	delete aq;
}
//---------------------------------------------------------------------------
int TfrmSetunite::Gettypeid()
{
	int booktypeid = (int)rcbtype->Items->Objects[rcbtype->ItemIndex];
	return  booktypeid;

}
//---------------------------------------------------------------------------

int TfrmSetunite::Getpressid()
{
	int pressid = (int)rcbpress->Items->Objects[rcbpress->ItemIndex];
	return  pressid;

}
//---------------------------------------------------------------------------
