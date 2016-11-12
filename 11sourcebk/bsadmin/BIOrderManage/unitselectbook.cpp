//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unitselectbook.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmcomfigbook *frmcomfigbook;
//---------------------------------------------------------------------------
__fastcall Tfrmcomfigbook::Tfrmcomfigbook(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	fcon = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcomfigbook::RzButton2Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
    ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcomfigbook::FormShow(TObject *Sender)
{
	query->Connection = fcon;
	AnsiString sql;
	sql = "select BS_BookCatalog.id,ISBN,Name,Price,Author,BS_PressInfo.AbbreviatedName,Presscount from BS_BookCatalog left join BS_PressInfo on BS_BookCatalog.pressid = BS_PressInfo.id "
			" where Name like '%" + Name + "%'";
	if (ISBN != "") {
		if (ISBN.Length() == 10 || ISBN.Length() == 13) {
			ISBN = ISBN.Delete(ISBN.Length(),1);
		}
		sql = sql + " and(ISBN like '%" + ISBN + "%' or barcode like '%" + ISBN + "%')";
	}
	if (Author != "") {
		sql = sql + " and Author like '%" + Author + "%'";
	}
	if (Press != "") {
		sql = sql + " and (AbbreviatedName like '%" + Press + "%' or FullName like '%" + Press + "%')";
	}
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcomfigbook::RzButton3Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcomfigbook::RzButton1Click(TObject *Sender)
{
	AnsiString sql;
	sql = "select BS_BookCatalog.id,ISBN,Name,Price,Author,BS_PressInfo.AbbreviatedName,Presscount from BS_BookCatalog left join BS_PressInfo on BS_BookCatalog.pressid = BS_PressInfo.id where 1=1 ";
	if (chisbn->Checked && edisbn->Text != "") {
		sql = sql + " and (ISBN like '%" + edisbn->Text + "%' or barcode like '%" + edisbn->Text + "%')";
	}
	if (chname->Checked && edname->Text != "") {
    	sql = sql + " and name like '%" + edname->Text + "%'";
	}
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------

