//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "settypress.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmsettyperss *frmsettyperss;
//---------------------------------------------------------------------------
__fastcall Tfrmsettyperss::Tfrmsettyperss(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
	con = cn;
	aq->Connection = cn;
	AnsiString sql;
	sql = "select id,AbbreviatedName from BS_PressInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsAnsiString,(TObject*)aq->FieldByName("id")->AsInteger);
		aq->Next();
	}
	pressid = -1;
	price = 0.00;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsettyperss::edpriceKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsettyperss::edpriceChange(TObject *Sender)
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
void __fastcall Tfrmsettyperss::edpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        AnsiString sql;
		sql = "select id,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + edpress->Text + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbpress->Clear();
		while (!aq->Eof )
		{
			cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsAnsiString,(TObject*)aq->FieldByName("id")->AsInteger);
			aq->Next();
		}
		aq->First();
		cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aq->FieldByName("id")->AsInteger);
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsettyperss::cbpressChange(TObject *Sender)
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
void __fastcall Tfrmsettyperss::RzButton1Click(TObject *Sender)
{
	if (chprice->Checked ) {
		try {
			price = StrToFloat(edprice->Text);
		} catch (...) {
			MessageBoxA(0,"请输入正确的定价","提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	if (chpress->Checked ) {
		try {
			pressid = (int)cbpress->Items->Objects[cbpress->ItemIndex];
			PressName = cbpress->Text.Trim();
		} catch (...) {
        	MessageBoxA(0,"请选择正确的出版社","提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	ISBN = edisbn->Text .Trim();
	Name = edname->Text .Trim();
	Author = edauthor->Text .Trim();
	PressCount = edpresscount->Text .Trim();
    ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsettyperss::RzButton2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsettyperss::edisbnChange(TObject *Sender)
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

void __fastcall Tfrmsettyperss::ednameChange(TObject *Sender)
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

void __fastcall Tfrmsettyperss::edauthorChange(TObject *Sender)
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

void __fastcall Tfrmsettyperss::edpresscountChange(TObject *Sender)
{
	if (edpresscount->Text != "") {
		chpresscount->Checked = true;
	}
	else
	{
    	chpresscount->Checked = false;
	}
}
//---------------------------------------------------------------------------

