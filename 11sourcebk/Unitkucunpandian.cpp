//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitkucunpandian.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmkucunpandian *frmkucunpandian;
//---------------------------------------------------------------------------
__fastcall Tfrmkucunpandian::Tfrmkucunpandian(TComponent* Owner,TADOQuery *aq)
	: TForm(Owner)
{
	query = aq;
	ds->DataSet = query;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmkucunpandian::DBGrid1DblClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmkucunpandian::DBGrid1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
    	if (query->IsEmpty() ) {
			return;
		}
		ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmkucunpandian::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
