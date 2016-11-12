//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectCustomerForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CustomerForm"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzLine"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmSelectCustomer *frmSelectCustomer;
//---------------------------------------------------------------------------
__fastcall TfrmSelectCustomer::TfrmSelectCustomer(TComponent* Owner)
	: TfrmCustomer(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSelectCustomer::RzDBEdit10KeyPress(TObject *Sender, wchar_t &Key)

{
	TfrmCustomer::RzDBEdit10KeyPress(Sender,Key);
	if (Key == '\r')
	{
        Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSelectCustomer::FormShow(TObject *Sender)
{
	//
   //	RzToolButton2->Click();
}
//---------------------------------------------------------------------------
