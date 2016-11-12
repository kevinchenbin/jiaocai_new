//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectBookTypeForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BookTypeAdminForm"
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmSelectBookType *frmSelectBookType;
//---------------------------------------------------------------------------
__fastcall TfrmSelectBookType::TfrmSelectBookType(TComponent* Owner)
	: TfrmBookTypeAdmin(Owner)
	, m_id(0)
{
}
//---------------------------------------------------------------
int TfrmSelectBookType::GetSelectID()
{
	return m_id;
}
//-----------
void __fastcall TfrmSelectBookType::RzDBGrid1DblClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectBookType::FormClose(TObject *Sender, TCloseAction &Action)

{
	if (dsetBookType->Active)
	{
		m_id = dsetBookType->FieldByName("Code")->AsInteger;
	}
	this->ModalResult = mrOk;
	TfrmBookTypeAdmin::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectBookType::RzDBGrid1CellClick(TColumn *Column)
{
	if (dsetBookType->Active)
	{
		m_id = dsetBookType->FieldByName("Code")->AsInteger;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectBookType::dsetBookTypeMoveComplete(TCustomADODataSet *DataSet,
          const TEventReason Reason, const Error *Error, TEventStatus &EventStatus)

{
	if (DataSet->Active)
	{
		m_id = DataSet->FieldByName("Code")->AsInteger;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectBookType::btnExit3Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------




