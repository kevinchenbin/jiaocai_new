//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "procuredetail.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "ModalDialog"
#pragma link "DBCtrlsEh"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmprocuredetail *frmprocuredetail;
//---------------------------------------------------------------------------
__fastcall Tfrmprocuredetail::Tfrmprocuredetail(TComponent* Owner)
	: TfrmModalDialog(Owner)
{

}
//---------------------------------------------------------------------------

void Tfrmprocuredetail::Init(LandInfo* li)
{
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	aq->Connection = li->con ;
	aq1->Connection = li->con ;
	aq2->Connection = li->con ;
	aq3->Connection = li->con ;
	AnsiString sql;
	sql = "select * from BS_Tmpheader where groupid = " + IntToStr(groupid);
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();

	sql = "select * from BS_Tmpdetail where BS_Tmpdetail.groupid = " + IntToStr(groupid) + " order by supplierid ";
	aq3->Close();
	aq3->SQL->Clear();
	aq3->SQL->Add(sql);
	aq3->Open();
	check = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocuredetail::SpeedButton3Click(TObject *Sender)
{
	if (aq3->IsEmpty() ) {
		MessageBoxA(0,"请添加明细！","提示",MB_ICONASTERISK);
		return;
	}
	aq3->First();
	while (!aq3->Eof)
	{
		if (aq3->FieldByName("checked")->AsBoolean ) {
			check = true;
			ModalResult = mrOk ;
			break;
		}
		aq3->Next();
	}
	if (!check) {
		MessageBoxA(0,"请勾选明细！","提示",MB_ICONASTERISK);
	}

}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocuredetail::SpeedButton1Click(TObject *Sender)
{
	if (aq1->FieldByName("state")->AsInteger != 0 ) {
		return;
	}
	AnsiString sql;
	if (aq1->FieldByName("type")->AsInteger == 1) {
		sql = "select 1 as type,BS_ProcureNote.id,BS_ProcureNote.BkcatalogID,BS_ProcureNote.UnrecAmount as Amount,BS_ProcureNote.FixedPrice,BS_ProcureNote.Discount,BS_ProcureNote.DiscountedPrice,BS_ProcureNoteHeader.SupplierID,"
			" BS_BookCatalog.ISBN,BS_BookCatalog.Price,BS_BookCatalog.Name,BS_PressInfo.AbbreviatedName,CUST_CustomerInfo.name as suppliername"
			" from BS_ProcureNoteHeader left join BS_ProcureNote on  BS_ProcureNoteHeader.id =  BS_ProcureNote.ProcureNtHeaderID "
			" left join BS_BookCatalog on BS_ProcureNote.BkcatalogID = BS_BookCatalog.id "
			" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
			" left join CUST_CustomerInfo on BS_ProcureNoteHeader.SupplierID = CUST_CustomerInfo.id "
			" where BS_ProcureNoteHeader.ProcureNtCode = " + aq1->FieldByName("code")->AsString ;
	}
	else  if (aq1->FieldByName("type")->AsInteger == 2) {
		sql = "select 2 as type,BS_ZN_ProcureNote.id,BS_ZN_ProcureNote.BkcatalogID,BS_ZN_ProcureNote.UnrecAmount as Amount,BS_ZN_ProcureNote.FixedPrice,BS_ZN_ProcureNote.Discount,BS_ZN_ProcureNote.DiscountedPrice,BS_ZN_ProcureNote.SupplierID,"
			" BS_BookCatalog.ISBN,BS_BookCatalog.Price,BS_BookCatalog.Name,BS_PressInfo.AbbreviatedName,CUST_CustomerInfo.name as suppliername"
			" from BS_ZN_ProcureNoteHeader left join BS_ZN_ProcureNote on  BS_ZN_ProcureNoteHeader.id =  BS_ZN_ProcureNote.ZNProcureNtHeaderID "
			" left join BS_BookCatalog on BS_ZN_ProcureNote.BkcatalogID = BS_BookCatalog.id "
			" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
			" left join CUST_CustomerInfo on BS_ZN_ProcureNote.SupplierID = CUST_CustomerInfo.id "
			" where BS_ZN_ProcureNoteHeader.ZNProcureNtCode = " + aq1->FieldByName("code")->AsString ;
	}
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();

	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	Variant   locvalues[2];
	aq2->DisableControls();
	while (!aq2->Eof)
	{
		if (aq2->FieldByName("Amount")->AsInteger > 0) {
        	locvalues[0]   =   Variant(aq2->FieldByName("BkcatalogID")->AsString);
			locvalues[1]   =   Variant(aq2->FieldByName("SupplierID")->AsString);
			if ( !aq3->Locate("bkcatalogid;supplierid",VarArrayOf(locvalues,1),Opts))
			{
				if (aq3->State != dsInsert ) {
					aq3->Append();
				}
				aq3->FieldByName("bkcatalogid")->AsInteger = aq2->FieldByName("BkcatalogID")->AsInteger ;
				aq3->FieldByName("groupid")->AsInteger = groupid ;
				aq3->FieldByName("type")->AsInteger = aq2->FieldByName("type")->AsInteger ;
				aq3->FieldByName("amount")->AsInteger = aq2->FieldByName("Amount")->AsInteger ;
				aq3->FieldByName("discount")->AsFloat = aq2->FieldByName("Discount")->AsFloat ;
				aq3->FieldByName("fixedprice")->AsFloat = aq2->FieldByName("FixedPrice")->AsFloat ;
				aq3->FieldByName("discountprice")->AsInteger = aq2->FieldByName("DiscountedPrice")->AsFloat ;
				aq3->FieldByName("supplierid")->AsInteger = aq2->FieldByName("SupplierID")->AsInteger ;
				aq3->FieldByName("ISBN")->AsString  = aq2->FieldByName("ISBN")->AsString ;
				aq3->FieldByName("Price")->AsFloat = aq2->FieldByName("Price")->AsFloat ;
				aq3->FieldByName("Name")->AsString = aq2->FieldByName("Name")->AsString ;
				aq3->FieldByName("AbbreviatedName")->AsString = aq2->FieldByName("AbbreviatedName")->AsString ;
				aq3->FieldByName("suppliername")->AsString = aq2->FieldByName("suppliername")->AsString ;
				aq3->FieldByName("procureid")->AsString = aq2->FieldByName("id")->AsString ;
				aq3->UpdateBatch(arAll);
			}
			else
			{
				/*DBGridEh1->SelectedRows->CurrentRowSelected = true;
				DBGridEh1->SetFocus();
				aq3->Edit();
				aq3->FieldByName("amount")->AsInteger = aq2->FieldByName("Amount")->AsInteger + aq3->FieldByName("amount")->AsInteger;
				aq3->UpdateBatch(arAll);    */
			}
		}
		aq2->Next();
	}
	aq2->EnableControls();
	aq3->Active = false;
	aq3->Active = true;
	aq1->Edit();
	aq1->FieldByName("state")->AsInteger = 1;
	aq1->UpdateBatch(arAll);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocuredetail::aq3AfterPost(TDataSet *DataSet)
{
	aq3->Active = false;
	aq3->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocuredetail::BtnAlignBottomClick(TObject *Sender)
{
     WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocuredetail::BtnExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocuredetail::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{   	if (Shift.Contains(ssCtrl)&& Key == 78 ) {
	   BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {
	   BtnExit->Click();
	}
			if (Shift.Contains(ssCtrl)&& Key ==90) {
				WindowState = wsNormal  ;
		}

}
//---------------------------------------------------------------------------

