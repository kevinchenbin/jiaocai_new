//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ModalDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmModalDialog *frmModalDialog;
//---------------------------------------------------------------------------
__fastcall TfrmModalDialog::TfrmModalDialog(TComponent* Owner)
	: TForm(Owner)
	, m_app(NULL)
	, m_con(NULL)
	, m_userID(-1)
	, m_storageID(-1)
{

}
//---------------------------------------------------------------------------
void TfrmModalDialog::Init(TApplication* app, TADOConnection* con)
{
	m_app = app;
	m_con = con;
	m_userID = 0;
	m_storageID = 0;
}

void TfrmModalDialog::Init(LandInfo* li)
{
	m_app = li->app;
	m_con = li->con;
	m_userID = li->userID;
	m_storageID = li->storageID;
}

void __fastcall TfrmModalDialog::OnHotKey(TMessage& Msg)
{
    if (Msg.WParam==GlobalAddAtom("Cancel")) //Ctrl+A
    {
        ModalResult = mrCancel;
    }
}

void __fastcall TfrmModalDialog::FormDestroy(TObject *Sender)
{
	if (GlobalAddAtom("Cancel") != 0)
	{
    	UnregisterHotKey(Handle,GlobalAddAtom("Cancel"));
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmModalDialog::FormCreate(TObject *Sender)
{
	if (GlobalAddAtom("Cancel") != 0)
	{
    	RegisterHotKey(Handle,GlobalAddAtom("Cancel"),NULL, VK_ESCAPE);
	}
}
//---------------------------------------------------------------------------

