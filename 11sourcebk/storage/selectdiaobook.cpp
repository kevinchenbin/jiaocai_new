//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "selectdiaobook.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma link "RzLabel"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma resource "*.dfm"

Tfrmfinddiaobook *frmfinddiaobook;
//---------------------------------------------------------------------------
__fastcall Tfrmfinddiaobook::Tfrmfinddiaobook(TComponent* Owner,TADOQuery *aq)
	: TfrmModalDialog(Owner)
{
	aquery = aq;
	dsrcQry->DataSet = aquery;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfinddiaobook::dbgrdQryKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		ModalResult = mrOk;
	}
}

//---------------------------------------------------------------------------

void __fastcall Tfrmfinddiaobook::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (aquery->Active == true && aquery->RecordCount == 1) {
		ModalResult = mrOk;
	}

}
//---------------------------------------------------------------------------

void __fastcall Tfrmfinddiaobook::FormShow(TObject *Sender)
{
	SelectAll = false;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmfinddiaobook::BtnExitClick(TObject *Sender)
{
	 Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfinddiaobook::BtnselectallClick(TObject *Sender)
{
  SelectAll = true;
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfinddiaobook::BtnPropertiesClick(TObject *Sender)
{
		 if (MutilSelectModal) {
		   ModalResult = mrCancel ;
		 }else
		 {
			ModalResult = mrOk ;
		 }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfinddiaobook::dbgrdQryDblClick(TObject *Sender)
{
	 if (MutilSelectModal) {
			switch (DoModalType) {
				case 1:    //µ÷²¦
					frmdiaobo->AddNote(aquery->FieldByName("bkinfoid")->AsInteger);
				break;
				default:
				;
			}
	 }
	 else
	 {
        ModalResult = mrOk ;
	 }
}
//---------------------------------------------------------------------------



void __fastcall Tfrmfinddiaobook::BtnWeekViewClick(TObject *Sender)
{
   MutilSelectModal = true;
}
//---------------------------------------------------------------------------



void __fastcall Tfrmfinddiaobook::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F4)
	{
	  BtnProperties->Click();
	}
	if (Key == VK_F6) {
		 BtnWeekView->Click();
	}
		if (Key == VK_F7) {
		Btnselectall->Click();
	}
			if (Shift.Contains(ssCtrl)&& Key ==81  ) {
	   BtnExit->Click();
	}
}
//---------------------------------------------------------------------------



