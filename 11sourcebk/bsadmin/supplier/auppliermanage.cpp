//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "auppliermanage.h"
#include "suppmanage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	TSuppMana * frm = new TSuppMana(Application,1,cnn);
	frm->ShowModal();
	delete frm;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	TSuppMana * frm = new TSuppMana(Application,2,cnn);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

