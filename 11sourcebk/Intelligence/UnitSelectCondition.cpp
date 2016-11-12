//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitSelectCondition.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmselectcondition *frmselectcondition;
//---------------------------------------------------------------------------
__fastcall Tfrmselectcondition::Tfrmselectcondition(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselectcondition::sbokClick(TObject *Sender)
{
  ModalResult = mbOK ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmselectcondition::cbsaleClick(TObject *Sender)
{
  if (cbsale->Checked ) {
	 cbtime->Enabled = true;

  } else
  {
    cbtime->Enabled  = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmselectcondition::sbcancelClick(TObject *Sender)
{
  ModalResult = mbCancel ;
  Close();
}
//---------------------------------------------------------------------------

