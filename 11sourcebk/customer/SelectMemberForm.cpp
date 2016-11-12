//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectMemberForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MemberForm"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzDBDTP"
#pragma link "RzDTP"
#pragma resource "*.dfm"
TfrmSelectMember *frmSelectMember;
//---------------------------------------------------------------------------
__fastcall TfrmSelectMember::TfrmSelectMember(TComponent* Owner)
	: TfrmMember(Owner)
{
}

void __fastcall TfrmSelectMember::FormClose(TObject *Sender, TCloseAction &Action)

{
	TfrmMember::FormClose(Sender, Action);
	ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectMember::RzDBEdit8KeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key==VK_RETURN)
	{
		TfrmMember::RzDBEdit8KeyPress(Sender, Key);
		Close();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectMember::FormShow(TObject *Sender)
{
	//
	RzToolButton4Click(RzToolButton4);
}
//---------------------------------------------------------------------------

