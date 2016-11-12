//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unitfapiao.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmunitfapiao *frmunitfapiao;
//---------------------------------------------------------------------------
__fastcall Tfrmunitfapiao::Tfrmunitfapiao(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmunitfapiao::edKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (ed->Text == "") {
			return;
		}
        ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------
