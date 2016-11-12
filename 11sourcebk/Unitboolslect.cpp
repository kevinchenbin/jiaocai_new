//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitboolslect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmselectbook *frmselectbook;
//---------------------------------------------------------------------------
__fastcall Tfrmselectbook::Tfrmselectbook(TComponent* Owner,TADOQuery *query)
	: TForm(Owner)
{
	ds->DataSet = query;
	aq = query;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselectbook::BtnClick(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselectbook::DBGrid1DblClick(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmselectbook::DBGrid1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselectbook::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselectbook::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //ÍË³ö
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==70) {   //Ñ¡ÖÐ
		Btn->Click();
	}
}
//---------------------------------------------------------------------------

