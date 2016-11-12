//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ordertocaigoupipei.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmordertocaigoupipei *frmordertocaigoupipei;
//---------------------------------------------------------------------------
__fastcall Tfrmordertocaigoupipei::Tfrmordertocaigoupipei(TComponent* Owner,TADOQuery *query)
	: TForm(Owner)
{
	ds->DataSet = query;
	aq = query;
	aquery->Connection = query->Connection ;
	aq1->Connection = query->Connection ;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmordertocaigoupipei::SpeedButton1Click(TObject *Sender)
{
	firstcreate();
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordertocaigoupipei::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordertocaigoupipei::SpeedButton2Click(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void Tfrmordertocaigoupipei::firstcreate()
{
	AnsiString sql;
    sql = "select * from BS_Tmporder where 1 = 2";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	aq->First();
	aq->DisableControls();
	while (!aq->Eof)
	{
		if (aq->FieldByName("usableamount")->AsInteger < (aq->FieldByName("UnsendAmount")->AsInteger - aq->FieldByName("localnum")->AsInteger) ) {
            TLocateOptions   Opts;
			Opts.Clear();
			Opts   <<   loPartialKey;
			AnsiString bkcatalogid;
			bkcatalogid = aq->FieldByName("BkcatalogID")->AsString;
			if ( !aquery->Locate("bkcatalogid",bkcatalogid,Opts))
			{
				if (aquery->State != dsInsert ) {
					aquery->Append();
				}
				aquery->FieldByName("groupid")->AsInteger = groupid;
				aquery->FieldByName("orderheaderid")->AsInteger = aq->FieldByName("id")->AsInteger ;
				aquery->FieldByName("ISBN")->AsString = aq->FieldByName("ISBN")->AsString ;
				aquery->FieldByName("bookname")->AsString = aq->FieldByName("Name")->AsString ;
				aquery->FieldByName("Price")->AsFloat = aq->FieldByName("Price")->AsFloat ;
				aquery->FieldByName("Author")->AsString = aq->FieldByName("Author")->AsString ;
				aquery->FieldByName("Amount")->AsInteger = aq->FieldByName("UnsendAmount")->AsInteger - aq->FieldByName("localnum")->AsInteger - aq->FieldByName("usableamount")->AsInteger;
				aquery->FieldByName("OrderNtCode")->AsString = aq->FieldByName("OrderNtCode")->AsString ;
				aquery->FieldByName("bkcatalogid")->AsInteger = aq->FieldByName("BkcatalogID")->AsInteger ;
				aquery->FieldByName("bkamount")->AsInteger = aq->FieldByName("usableamount")->AsInteger;
				aquery->FieldByName("Pressname")->AsString = aq->FieldByName("FullName")->AsString ;
				aquery->FieldByName("ClientName")->AsString = aq->FieldByName("clientname")->AsString ;
				aquery->FieldByName("Clientid")->AsInteger = aq->FieldByName("VendorID")->AsInteger ;
				aquery->FieldByName("Discount")->AsFloat = aq->FieldByName("Discount")->AsFloat ;
				aquery->FieldByName("ordernoteid")->AsInteger = aq->FieldByName("ordernoteid")->AsInteger ;
				aquery->UpdateBatch(arAll);
			}
			else
			{
				if (aquery->State != dsEdit) {
					aquery->Edit() ;
				}
				aquery->FieldByName("Amount")->AsInteger = aquery->FieldByName("Amount")->AsInteger + aq->FieldByName("UnsendAmount")->AsInteger - aq->FieldByName("localnum")->AsInteger - aq->FieldByName("usableamount")->AsInteger;
				aquery->UpdateBatch(arAll);
			}
		}
		aq->Next();
	}
	aq->EnableControls();
	sql = "exec USP_BS_SetSupplier " + IntToStr(groupid);
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->ExecSQL();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordertocaigoupipei::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordertocaigoupipei::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmordertocaigoupipei::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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

