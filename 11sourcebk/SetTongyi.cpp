//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SetTongyi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma resource "*.dfm"
TfrmSetTongyi *frmSetTongyi;
//---------------------------------------------------------------------------
__fastcall TfrmSetTongyi::TfrmSetTongyi(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSetTongyi::RzButton1Click(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSetTongyi::RzButton2Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
bool TfrmSetTongyi::Getpxdiscount(float& pxdiscount)
{
	bool ret = false;
	if (chyjpxdiscount->Checked)
	{
		pxdiscount = edyjpx->Value ;
		ret = true;
	}
	return ret;
}

//---------------------------------------------------------------------------
bool TfrmSetTongyi::Getlsdiscount(float& lsdiscount)
{
	bool ret = false;
	if (chyilsdiscount->Checked)
	{
		lsdiscount = edyjls->Value ;
		ret = true;
	}
	return ret;
}
//---------------------------------------------------------------------------
