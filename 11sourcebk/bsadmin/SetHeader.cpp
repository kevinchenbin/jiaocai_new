//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SetHeader.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSetHeader *frmSetHeader;
//---------------------------------------------------------------------------
__fastcall TfrmSetHeader::TfrmSetHeader(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetHeader::btconcelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetHeader::BtokClick(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetHeader::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
