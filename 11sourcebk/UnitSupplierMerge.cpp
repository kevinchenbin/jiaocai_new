//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitSupplierMerge.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmSupplierMerge *frmSupplierMerge;
//---------------------------------------------------------------------------
__fastcall TfrmSupplierMerge::TfrmSupplierMerge(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	query->Connection = con;
	fcon = con;
	ysupplierid = -1;
	msupplierid = -1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSupplierMerge::RzButton1Click(TObject *Sender)
{
	AnsiString sql;
	sql = "select rank() over(order by id) as xuhao,CUST_CustomerInfo.* from CUST_CustomerInfo where type = 1 and name like '%" + edquery->Text .Trim() + "%'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSupplierMerge::BtnOKClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	msupplierid = query->FieldByName("ID")->AsInteger ;
	edbaoliu->Text = query->FieldByName("Name")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSupplierMerge::BtnCancelClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	ysupplierid = query->FieldByName("ID")->AsInteger ;
	edzuofei->Text = query->FieldByName("Name")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSupplierMerge::BtnClick(TObject *Sender)
{
	if (msupplierid == -1) {
		MessageBox(0,"请设置保留供应商！","提示" ,MB_OK|MB_ICONASTERISK);
		return;
	}
	if (ysupplierid == -1) {
		MessageBox(0,"请设置作废供应商！","提示" ,MB_OK|MB_ICONASTERISK);
		return;
	}
	if (msupplierid == ysupplierid) {
		MessageBox(0,"保留供应商和作废供应商为同一家供应商！","提示" ,MB_OK|MB_ICONASTERISK);
		return;
	}
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "exec Supplier_Merge " + IntToStr(ysupplierid) + "," + IntToStr(msupplierid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
}
//---------------------------------------------------------------------------

