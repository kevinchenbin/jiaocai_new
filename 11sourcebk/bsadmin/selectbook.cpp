//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "selectbook.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma link "RzLabel"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma resource "*.dfm"

Tfrmfindbook *frmfindbook;
//---------------------------------------------------------------------------
__fastcall Tfrmfindbook::Tfrmfindbook(TComponent* Owner,TADOQuery *aq,int findagain)
	: TfrmModalDialog(Owner)
{
	aquery = aq;
	dsrcQry->DataSet = aq;
	findbook = findagain;
	if (findagain == 0) {
    	dbgrdQry->Columns->Items[6]->Visible = true;
		dbgrdQry->Columns->Items[6]->Field = aquery->FieldByName("SupplierName");
		dbgrdQry->Columns->Items[9]->Visible = true;
		dbgrdQry->Columns->Items[9]->Field = aquery->FieldByName("BKStName");
		dbgrdQry->Columns->Items[5]->Visible = true;
		dbgrdQry->Columns->Items[5]->Field = aquery->FieldByName("Amount");
	}
	else
	{
    	dbgrdQry->Columns->Items[6]->Visible = false;
		dbgrdQry->Columns->Items[9]->Visible = false;
		dbgrdQry->Columns->Items[5]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfindbook::dbgrdQryKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		ModalResult = mrOk;
	}
}

//---------------------------------------------------------------------------

void __fastcall Tfrmfindbook::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (aquery->Active == true && aquery->RecordCount == 1) {
		ModalResult = mrOk;
	}

}
//---------------------------------------------------------------------------

void __fastcall Tfrmfindbook::FormShow(TObject *Sender)
{
	SelectAll = false;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmfindbook::BtnExitClick(TObject *Sender)
{
	 Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfindbook::BtnselectallClick(TObject *Sender)
{
  SelectAll = true;
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfindbook::BtnPropertiesClick(TObject *Sender)
{
		 if (MutilSelectModal) {
		   ModalResult = mrCancel ;
		 }else
		 {
			ModalResult = mrOk ;
		 }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfindbook::dbgrdQryDblClick(TObject *Sender)
{
	  //	 ModalResult = mrOk;
}
//---------------------------------------------------------------------------



void __fastcall Tfrmfindbook::BtnWeekViewClick(TObject *Sender)
{
   MutilSelectModal = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfindbook::dbgrdQryCellClick(TColumn *Column)
{
	 if (MutilSelectModal) {
			switch (DoModalType) {
				case 1:    //ÖÇÄÜ²É¹º
					if (findbook == 0) {
						ZNProcurefrm->AddNote(aquery->FieldByName("SupplierID")->AsInteger,aquery->FieldByName("ID")->AsInteger);
					}
					else
					{
						ZNProcurefrm->AddNote(-1,aquery->FieldByName("ID")->AsInteger);
					}
				break;
				default:
				;
			}
	 }
}
//---------------------------------------------------------------------------


void __fastcall Tfrmfindbook::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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
	   //	if (Key == VK_ESC) {
	  // BtnExit->Click();
	//}
}
//---------------------------------------------------------------------------

