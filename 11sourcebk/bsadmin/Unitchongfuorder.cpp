//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitchongfuorder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmchongfuorder *frmchongfuorder;
//---------------------------------------------------------------------------
__fastcall Tfrmchongfuorder::Tfrmchongfuorder(TComponent* Owner,TADOQuery *aq)
	: TForm(Owner)
{
	ds->DataSet = aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmchongfuorder::quitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmchongfuorder::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == 81) {
    	quit->Click();
	}
	if (Key == 67) {
		RzButton1->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmchongfuorder::RzButton1Click(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

