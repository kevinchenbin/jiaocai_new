//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "orderpipeiresurt.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
Tfrmorderresurt *frmorderresurt;
//---------------------------------------------------------------------------
__fastcall Tfrmorderresurt::Tfrmorderresurt(TComponent* Owner,TADOQuery *query)
	: TForm(Owner)
{
	ds->DataSet = query;
	aq = query;
	aquery->Connection = query->Connection ;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmorderresurt::SpeedButton1Click(TObject *Sender)
{
    firstcreate();
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderresurt::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderresurt::SpeedButton2Click(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void Tfrmorderresurt::firstcreate()
{
	AnsiString sql;
	sql = "select * from BS_Tmporder where 1 = 2";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	aq->First();
	while (!aq->Eof)
	{
		if (aq->FieldByName("amount")->AsInteger > 0 && aq->FieldByName("UnsendAmount")->AsInteger > 0 ) {
        	if (aquery->State != dsInsert ) {
				aquery->Append();
			}
			aquery->FieldByName("groupid")->AsInteger = groupid;
			aquery->FieldByName("orderheaderid")->AsInteger = aq->FieldByName("id")->AsInteger ;
			aquery->FieldByName("ISBN")->AsString = aq->FieldByName("ISBN")->AsString ;
			aquery->FieldByName("bookname")->AsString = aq->FieldByName("Name")->AsString ;
			aquery->FieldByName("Price")->AsFloat = aq->FieldByName("Price")->AsFloat ;
			aquery->FieldByName("Author")->AsString = aq->FieldByName("Author")->AsString ;
			if (aq->FieldByName("UnsendAmount")->AsInteger > aq->FieldByName("amount")->AsInteger ) {
				aquery->FieldByName("Amount")->AsInteger = aq->FieldByName("amount")->AsInteger ;
			}
			else
			{
				aquery->FieldByName("Amount")->AsInteger = aq->FieldByName("UnsendAmount")->AsInteger ;
			}
			aquery->FieldByName("OrderNtCode")->AsString = aq->FieldByName("OrderNtCode")->AsString ;
			aquery->FieldByName("bkcatalogid")->AsInteger = aq->FieldByName("BkcatalogID")->AsInteger ;
			aquery->FieldByName("bkamount")->AsInteger = aq->FieldByName("amount")->AsInteger ;
			aquery->FieldByName("Pressname")->AsString = aq->FieldByName("AbbreviatedName")->AsString ;
			aquery->FieldByName("ClientName")->AsString = aq->FieldByName("clientname")->AsString ;
			aquery->FieldByName("Clientid")->AsInteger = aq->FieldByName("VendorID")->AsInteger ;
			aquery->FieldByName("Discount")->AsFloat = aq->FieldByName("Discount")->AsFloat ;
			aquery->FieldByName("ordernoteid")->AsInteger = aq->FieldByName("ordernoteid")->AsInteger ;
			aquery->UpdateBatch(arAll);
		}
		aq->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderresurt::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderresurt::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderresurt::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {
	   BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {
	   BtnExit->Click();
	}
			if (Shift.Contains(ssCtrl)&& Key ==90) {
				WindowState = wsNormal  ;
		}
}
//---------------------------------------------------------------------------

