//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BookQuery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzCmboBx"
#pragma link "RzEdit"
#pragma link "ModalDialog"
#pragma link "RzButton"

#pragma resource "*.dfm"
TfrmBookQuery *frmBookQuery;
//---------------------------------------------------------------------------
__fastcall TfrmBookQuery::TfrmBookQuery(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	fcon = con;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	AnsiString sql;
	sql = "select ID,AbbreviatedName FROM BS_PressInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	sql = "select ID,Name FROM BS_BookType";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbtype->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
}
//---------------------------------------------------------------------------



void __fastcall TfrmBookQuery::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------


void __fastcall TfrmBookQuery::btOKClick(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::RzButton1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmBookQuery::edpressKeyPress(TObject *Sender, wchar_t &Key)
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select ID,AbbreviatedName FROM BS_PressInfo where AbbreviatedName like '%" + edpress->Text.Trim() + "%'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbpress->Items->Clear();
	while (!aq->Eof )
	{
		cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	aq->First();
	cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
	delete aq;
	cbpress->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::edtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;

	sql = "select ID,Name FROM BS_BookType where Name like %'" + edtype->Text.Trim() + "%'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbtype->Items->Clear();
	while (!aq->Eof )
	{
		cbtype->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	aq->First();
	cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
	delete aq;
	cbtype->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::cbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        btOK->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::edpriceKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
		Key = NULL;
	}
}

//---------------------------------------------------------------------------
AnsiString TfrmBookQuery::getcontion()
{
	AnsiString contion;
	contion = " where 1 = 1";
	if (chisbn->Checked && edisbn->Text != "") {
		contion = contion + " and (A.isbn like '%" + edisbn->Text.Trim() + "%' or A.Barcode like '%" + edisbn->Text.Trim() + "%')";
	}
	if (chname->Checked && edname->Text != "") {
		contion = contion + " and A.name like '%" + edname->Text.Trim() + "%'";
	}
	if (chprice->Checked && edprice->Text != "") {
		try {
			StrToFloat(edprice->Text);
		} catch (...) {
			return contion;
		}
		contion = contion + " and A.price = " + edprice->Text;
	}
	if (chauthor->Checked && edauthor->Text != "") {
		contion = contion + " and A.author like '%" + edauthor->Text.Trim() + "%'";
	}
	if (chpress->Checked && cbpress->Text != "") {
		contion = contion + " and B.AbbreviatedName = '" + cbpress->Text + "'";
	}
	if (chtype->Checked && cbtype->Text != "") {
		contion = contion + " and C.Name = '" + cbtype->Text + "'";
	}
	return  contion;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::edisbnChange(TObject *Sender)
{
	if (edisbn->Text != "") {
		chisbn->Checked = true;
	}
	else
	{
    	chisbn->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::ednameChange(TObject *Sender)
{
	if (edname->Text != "") {
		chname->Checked = true;
	}
	else
	{
		chname->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::edpriceChange(TObject *Sender)
{
	if (edprice->Text != "") {
		chprice->Checked = true;
	}
	else
	{
    	chprice->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::edauthorChange(TObject *Sender)
{
	if (edauthor->Text != "") {
		chauthor->Checked = true;
	}
	else
	{
    	chauthor->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::cbpressChange(TObject *Sender)
{
	if (cbpress->Text != "") {
		chpress->Checked = true;
	}
	else
	{
    	chpress->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookQuery::cbtypeChange(TObject *Sender)
{
	if (cbtype->Text != "") {
		chtype->Checked = true;
	}
	else
	{
    	chtype->Checked = false;
	}
}
//---------------------------------------------------------------------------

