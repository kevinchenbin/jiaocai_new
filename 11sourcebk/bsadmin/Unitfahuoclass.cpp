//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitfahuoclass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmfahuoclass *frmfahuoclass;
//---------------------------------------------------------------------------
__fastcall Tfrmfahuoclass::Tfrmfahuoclass(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfahuoclass::RzButton2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfahuoclass::RzButton1Click(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfahuoclass::ed6Change(TObject *Sender)
{
	if (ed6->Text != "") {
		ch6->Checked = true;
	}
	else
	{
		ch6->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfahuoclass::ed2Change(TObject *Sender)
{
	if (ed2->Text != "") {
		ch2->Checked = true;
	}
	else
	{
		ch2->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfahuoclass::ed3Change(TObject *Sender)
{
	if (ed3->Text != "") {
		ch3->Checked = true;
	}
	else
	{
		ch3->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfahuoclass::ed5Change(TObject *Sender)
{
	if (ed5->Text != "") {
		ch5->Checked = true;
	}
	else
	{
		ch5->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfahuoclass::edclassChange(TObject *Sender)
{
	if (edclass->Text != "") {
		chclass->Checked = true;
	}
	else
	{
    	chclass->Checked = false;
	}
}
//---------------------------------------------------------------------------

