//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectCustomerForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma link "RzLabel"
#pragma link "RzEdit"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TfrmSelectCustomer *frmSelectCustomer;
//---------------------------------------------------------------------------
__fastcall TfrmSelectCustomer::TfrmSelectCustomer(TComponent* Owner)
	: TfrmModalDialog(Owner)
	, m_type(0)
	, m_id(0)
{
}
//---------------------------------------------------------------------------

void TfrmSelectCustomer::Init(LandInfo* li)
{
	TfrmModalDialog::Init(li);
	qryCustomer->Active = false;
	qryCustomer->Connection = m_con;
}

void TfrmSelectCustomer::SetCustomerType(int type)
{
	m_type = type;
}
void __fastcall TfrmSelectCustomer::edtNameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		QryCustomer();
		if(qryCustomer->Active && qryCustomer->RecordCount >= 1)
		{
			m_id = qryCustomer->FieldByName("ID")->AsInteger;
			ModalResult = mrOk;
		}
	}
}
//---------------------------------------------------------------------------

void TfrmSelectCustomer::QryCustomer()
{
	qryCustomer->Active = false;
	qryCustomer->SQL->Clear();
	String sql;
	sql = Format("select ID,Name from CUST_CustomerInfo where ID=0 or (ID>0"
		" and Name like '%%%s%%' and Type=%d)", ARRAYOFCONST((edtName->Text.c_str(), m_type)));
	qryCustomer->SQL->Add(sql);
	qryCustomer->Active = true;
	dsrcCustomer->DataSet = NULL;
	dsrcCustomer->DataSet = qryCustomer;
}

int TfrmSelectCustomer::GetCustomerID()
{
	return m_id;
}

void __fastcall TfrmSelectCustomer::dbgrdCustomerCellClick(TColumn *Column)
{
	if(qryCustomer->Active && qryCustomer->RecordCount >= 1)
	{
		m_id = qryCustomer->FieldByName("ID")->AsInteger;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCustomer::dbgrdCustomerDblClick(TObject *Sender)
{
	if(qryCustomer->Active && qryCustomer->RecordCount >= 1)
	{
		ModalResult = mrOk;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmSelectCustomer::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(qryCustomer->Active && qryCustomer->RecordCount >= 1)
	{
		m_id = qryCustomer->FieldByName("ID")->AsInteger;
	}
	qryCustomer->Active = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectCustomer::FormShow(TObject *Sender)
{
	wchar_t key = '\r';
	edtNameKeyPress(edtName, key);
}
//---------------------------------------------------------------------------

