//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitorder_stk.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmorder_stk *frmorder_stk;
//---------------------------------------------------------------------------
__fastcall Tfrmorder_stk::Tfrmorder_stk(TComponent* Owner,TADOQuery *aquery)
	: TForm(Owner)
{
	query = aquery;
	ds->DataSet = query;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorder_stk::DBGrid1DblClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
    ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorder_stk::FormShow(TObject *Sender)
{
	edisbn->Text = isbn;
	edname->Text = name;
	edamount->Text = amount;
	edauthor->Text = author;
}
//---------------------------------------------------------------------------

