//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "QryNoteCodeForm.h"
#include "NoteCode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzCmboBx"
#pragma link "RzSpnEdt"
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmQryNoteCode *frmQryNoteCode;
//---------------------------------------------------------------------------
__fastcall TfrmQryNoteCode::TfrmQryNoteCode(TComponent* Owner,int modle)
	: TfrmModalDialog(Owner)
{
	/*if (modle == 0) {
		spedtID->IntValue = 0;
		spedtID->Min = 0;
		spedtID->Max = 9999;
	}
	else
	{
		spedtID->IntValue = 10000;
		spedtID->Min = 10000;
		spedtID->Max = 99999;
	}  */
}
//---------------------------------------------------------------------------
void __fastcall TfrmQryNoteCode::dtedtDateChange(TObject *Sender)
{
	//
	//m_storageID =0;
	NoteCode nc(dtedtDate->Date, m_storageID, spedtID->IntValue);
    edtCode->Text = nc.AsString();
	m_stgNtCode = edtCode->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfrmQryNoteCode::spedtIDChange(TObject *Sender)
{
	//
	if (spedtID->IntValue < 0 || spedtID->IntValue > 99999)
	{
		ShowMessage("µ¥ºÅ´íÎó!");
		return;
	}
    NoteCode nc(dtedtDate->Date, m_storageID, spedtID->IntValue);
    edtCode->Text = nc.AsString();
	m_stgNtCode = edtCode->Text;
}
//---------------------------------------------------------------------------

String TfrmQryNoteCode::GetNoteCode()
{
	return m_stgNtCode;
}
void __fastcall TfrmQryNoteCode::FormShow(TObject *Sender)
{
	dtedtDate->Date = TDateTime::CurrentDate();
	NoteCode nc(dtedtDate->Date, m_storageID, spedtID->IntValue);
	edtCode->Text = nc.AsString();
	m_stgNtCode = edtCode->Text;
	cbb1->Text = IntToStr(m_storageID);
}
void TfrmQryNoteCode::SetstgID(int stgid)
{
   m_storageID = stgid;
}
//---------------------------------------------------------------------------





