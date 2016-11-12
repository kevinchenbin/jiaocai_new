//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitfindbook.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmfindorderbook *frmfindorderbook;
//---------------------------------------------------------------------------
__fastcall Tfrmfindorderbook::Tfrmfindorderbook(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfindorderbook::sbfindClick(TObject *Sender)
{
	 switch (cbfindname->ItemIndex) {
		 case 0:
			type = "bookname";
			break;
		 case 1:
			type = "ISBN";
			break;
		 case 2:
			type = "userDefCode";
			break;
		 case 3:
			type = "AbbreviatedName";
			break;
  default:
	  ;
  }
  value = editname->Text.Trim();
  ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfindorderbook::SpeedButton2Click(TObject *Sender)
{
 // SendMessageA(hand,WM_FINDNEXTMESSAGE,0,0);
  //           aq->FindNext();
			  // aq->SelectedRows->CurrentRowSelected = true;

}
//---------------------------------------------------------------------------
void __fastcall Tfrmfindorderbook::editnameKeyPress(TObject *Sender, wchar_t &Key)

{
  if (Key == '\r') {
    sbfind->Click();
  }
}
//---------------------------------------------------------------------------
