//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Database.h"
#include "backdatabase.h"
#include "ResStore.h"
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
void __fastcall TForm1::btBakDatabaseClick(TObject *Sender)
{
	TBakDatabase *frm = new TBakDatabase(Application);
	if (frm->ShowModal() == mrOk)
	{

	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btResDatabaseClick(TObject *Sender)
{
	TResDatabase *frm = new TResDatabase(Application);
	if (frm->ShowModal() == mrOk)
	{

	}
	delete frm;
}
//---------------------------------------------------------------------------

