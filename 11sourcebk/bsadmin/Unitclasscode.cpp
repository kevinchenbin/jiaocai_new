//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitclasscode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmclasscode *frmclasscode;
//---------------------------------------------------------------------------
__fastcall Tfrmclasscode::Tfrmclasscode(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclasscode::RzButton2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclasscode::RzButton1Click(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclasscode::ed1Change(TObject *Sender)
{
	if (ed1->Text != "") {
		ch1->Checked = true;
	}
	else
	{
    	ch1->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclasscode::ed6Change(TObject *Sender)
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
void __fastcall Tfrmclasscode::ed2Change(TObject *Sender)
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
void __fastcall Tfrmclasscode::ed3Change(TObject *Sender)
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
void __fastcall Tfrmclasscode::ed4Change(TObject *Sender)
{
	if (ed4->Text != "") {
		ch4->Checked = true;
	}
	else
	{
		ch4->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclasscode::ed5Change(TObject *Sender)
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
void __fastcall Tfrmclasscode::ed7Change(TObject *Sender)
{
	if (ed7->Text != "") {
		ch7->Checked = true;
	}
	else
	{
		ch7->Checked = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclasscode::ed8Change(TObject *Sender)
{
	if (ed8->Text != "") {
		ch8->Checked = true;
	}
	else
	{
		ch8->Checked = false;
	}
}
//---------------------------------------------------------------------------
