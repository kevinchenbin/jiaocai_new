//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CustomerForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzDBEdit"
#pragma link "RzLine"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RzDBNav"
#pragma resource "*.dfm"
TfrmCustomer *frmCustomer;
//---------------------------------------------------------------------------
__fastcall TfrmCustomer::TfrmCustomer(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCustomer::SetCustomerType(int type)
{
	m_type = type;
	Query("", m_type);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCustomer::FormClose(TObject *Sender, TCloseAction &Action)
{
	dsetCustomer->Active = false;
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCustomer::rtbaddClick(TObject *Sender)
{
	//Ìí¼Ó¼ÇÂ¼
   if (dsetCustomer->State == dsInsert&&dbedtName->Text!= "")
	{
		dbcbbType->ReadOnly = false;
		if (m_type == CT_Supplier)
		{
			dbcbbType->Value = "1";
		}
		else
		{
			dbcbbType->Value = "2";
		}
		dsetCustomer->Post();
		dbcbbType->ReadOnly = true;
		dsetCustomer->Refresh();
	}
	dsetCustomer->Append();
	if (m_type == CT_Supplier)
	{
		dbcbbType->ItemIndex = 0;
	}
	else
	{
		dbcbbType->ItemIndex = 1;
	}
}



//---------------------------------------------------------------------------

void __fastcall TfrmCustomer::rtbexitClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------

void __fastcall TfrmCustomer::FormShow(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------

void __fastcall TfrmCustomer::rtbmodifyClick(TObject *Sender)
{
	//
   //	Query(edtQuery->Text, m_type);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCustomer::rtbdelClick(TObject *Sender)
{
	//É¾³ý¼ÇÂ¼
//
	if(!dsetCustomer->IsEmpty())
	{
		dsetCustomer->Delete();
	}
}
 //---------------------------------------------------------------------------

void TfrmCustomer::Query(String condition, CustomerType type)
{
	if (dsetCustomer->Active)
	{
		dsetCustomer->Active = false;
	}
	String sql;
	if (condition == "")
	{
		if (m_type == CT_Supplier)
		{
			sql = "select * from CUST_CustomerInfo where Type = '1'";
		}
		else if (m_type == CT_Vendor)
		{
			sql = "select * from CUST_CustomerInfo where Type = '2'";
		}
		else
		{
			sql = "select * from CUST_CustomerInfo";
        }
	}
	else
	{
		if (m_type == CT_Supplier)
		{
			sql = "select * from CUST_CustomerInfo where Type = '1' and Name like '%" + condition + "%'";
		}
		else if (m_type == CT_Vendor)
		{
			sql = "select * from CUST_CustomerInfo where Type = '2' and Name like '%" + condition + "%'";
		}
		else
		{
			sql = "select * from CUST_CustomerInfo where Name like '%" + condition + "%'";
        }
	}
	dsetCustomer->CommandText = sql;
	dsetCustomer->Active = true;	
}
//---------------------------------------------------------------------------





