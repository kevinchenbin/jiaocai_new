//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitpanbook.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmpanbook *frmpanbook;
//---------------------------------------------------------------------------
__fastcall Tfrmpanbook::Tfrmpanbook(TComponent* Owner,TADOQuery *aq)
	: TForm(Owner)
{
	ds->DataSet = aq;
	query = aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpanbook::DBGrid1CellClick(TColumn *Column)
{
	if (query->IsEmpty() ) {
		return;
	}
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmpanbook::DBGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == '\r') {
        if (query->IsEmpty() ) {
			return;
		}
		ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------
