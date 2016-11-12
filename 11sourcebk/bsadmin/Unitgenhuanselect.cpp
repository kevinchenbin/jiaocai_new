//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitgenhuanselect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmchangeselect *frmchangeselect;
//---------------------------------------------------------------------------
__fastcall Tfrmchangeselect::Tfrmchangeselect(TComponent* Owner,TADOQuery *qu)
	: TForm(Owner)
{
	continuechange = 0;
	ds->DataSet = qu;
	query = qu;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmchangeselect::DBGrid1DblClick(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmchangeselect::DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == '\r') {
		ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmchangeselect::btgenhuanClick(TObject *Sender)
{
	continuechange = 1;
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
