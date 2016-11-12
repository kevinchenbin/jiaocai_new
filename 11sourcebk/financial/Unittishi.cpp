//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unittishi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmtishi *frmtishi;
//---------------------------------------------------------------------------
__fastcall Tfrmtishi::Tfrmtishi(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmtishi::btokClick(TObject *Sender)
{
	hc = rg->ItemIndex ;
	if (cbts->Checked ) {
		ts = 1;
	}
	else
	{
    	ts = 0;
	}
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------


