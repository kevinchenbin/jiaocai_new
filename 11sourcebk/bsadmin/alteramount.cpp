//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "alteramount.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmalteramount *frmalteramount;
//---------------------------------------------------------------------------
__fastcall Tfrmalteramount::Tfrmalteramount(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmalteramount::ednumKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
    	if (ednum->Text == "") {
			return;
		}
		try {
			StrToInt(ednum->Text);
		} catch (...) {
			return;
		}
		ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------
