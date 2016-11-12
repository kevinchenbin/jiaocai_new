//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PwdForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma link "RzLabel"
#pragma link "RzEdit"
#pragma resource "*.dfm"
TfrmPwd *frmPwd;
//---------------------------------------------------------------------------
__fastcall TfrmPwd::TfrmPwd(TComponent* Owner)
	: TfrmModalDialog(Owner)
	, m_password("")
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPwd::FormShow(TObject *Sender)
{
	//
    edtPwd->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPwd::edtPwdKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
        m_password = edtPwd->Text;
		btnOk->SetFocus();
	}
}
//---------------------------------------------------------------------------
String TfrmPwd::GetPassword()
{
 	return m_password;
}
void __fastcall TfrmPwd::edtPwdChange(TObject *Sender)
{
	m_password = edtPwd->Text;
}
//---------------------------------------------------------------------------

