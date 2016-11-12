//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitfahuocode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmfahuocode *frmfahuocode;
//---------------------------------------------------------------------------
__fastcall Tfrmfahuocode::Tfrmfahuocode(TComponent* Owner,TADOQuery *query)
	: TForm(Owner)
{
	aquery = query;
	ds->DataSet = aquery;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfahuocode::RzButton2Click(TObject *Sender)
{
	newid = 1;
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfahuocode::RzButton1Click(TObject *Sender)
{
	if (MessageBoxA(0,"确认要追加到该单中吗？","提示",MB_ICONQUESTION|MB_OKCANCEL)==1)
	{
    	newid = 0;
		wsheadid = aquery->FieldByName("id")->AsInteger ;
		ModalResult = mrOk ;
	}

}
//---------------------------------------------------------------------------

