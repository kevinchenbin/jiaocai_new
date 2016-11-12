//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PurchaseQuery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzDBDTP"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzDTP"
#pragma link "RzEdit"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TfrmPurchaseQuery *frmPurchaseQuery;
//---------------------------------------------------------------------------
__fastcall TfrmPurchaseQuery::TfrmPurchaseQuery(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_sql("")
{
}
//---------------------------------------------------------------------------
void TfrmPurchaseQuery::Init(TApplication* app, TADOConnection* con)
{
	 TfrmMDIChild::Init(app,con);
	 //Formstrngrid();
}
void __fastcall TfrmPurchaseQuery::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPurchaseQuery::btnExit4Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------



