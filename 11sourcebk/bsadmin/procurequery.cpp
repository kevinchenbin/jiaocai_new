//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "procurequery.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "DBCtrlsEh"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
Tfrmprocurequery *frmprocurequery;
//---------------------------------------------------------------------------
__fastcall Tfrmprocurequery::Tfrmprocurequery(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	dtstart->Value = Date();
	dtend->Value = Date();
    this->WindowState = wsMaximized ;
}
//---------------------------------------------------------------------------

void Tfrmprocurequery::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	aq->Connection = m_con ;
	aq1->Connection = m_con ;
	aq2->Connection = m_con ;
	AnsiString sql;
	sql = "select ID,Name from CUST_CustomerInfo where type = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject *)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocurequery::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type = 1 and Name like '%" + edquery->Text + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbsupplier->Clear();
		while (!aq->Eof )
		{
			cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject *)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbsupplier->SetFocus();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject *)aq->FieldByName("ID")->AsInteger );
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprocurequery::SpeedButton1Click(TObject *Sender)
{
	AnsiString sql,sqlwhere;
	sql = "select ProcureNtCode,HdTime,Name from BS_ProcureNoteHeader left join CUST_CustomerInfo on BS_ProcureNoteHeader.SupplierID = CUST_CustomerInfo.id ";
	if (chprocure->Checked ) {
		sqlwhere = " where ProcureNtCode = " + edprocurecode->Text ;
	}
	if (chsupplier->Checked ) {
		if (sqlwhere == "") {
			sqlwhere = " where CUST_CustomerInfo.Name like '%" + cbsupplier->Text + "%'";
		}
		else
		{
			sqlwhere = sqlwhere + " and CUST_CustomerInfo.Name like '%" + cbsupplier->Text + "%'";
		}
	}
	if (chstart->Checked) {
		if (sqlwhere == "") {
			sqlwhere = " where BS_ProcureNoteHeader.HdTime >= '" + DateToStr(dtstart->Value) + "'";
		}
		else
		{
			sqlwhere = sqlwhere + " and BS_ProcureNoteHeader.HdTime >= '" + DateToStr(dtstart->Value) + "'";
		}
	}
	if (chend->Checked ) {
		if (sqlwhere == "") {
			sqlwhere = " where BS_ProcureNoteHeader.HdTime <= '" + DateToStr(dtend->Value) + "'";
		}
		else
		{
			sqlwhere = sqlwhere + " and BS_ProcureNoteHeader.HdTime <= '" + DateToStr(dtend->Value) + "'";
		}
	}
	sql = sql + sqlwhere;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprocurequery::DBGridEh1CellClick(TColumnEh *Column)
{
	if (aq1->IsEmpty() ) {
        return;
	}
	AnsiString sql;
	sql = "select BS_ProcureNote.id,BS_ProcureNote.Amount,BS_ProcureNote.FixedPrice,BS_ProcureNote.Discount,BS_ProcureNote.DiscountedPrice,BS_ProcureNoteHeader.SupplierID,"
			"BS_ProcureNote.BkcatalogID,BS_BookCatalog.ISBN,BS_BookCatalog.Price,BS_BookCatalog.Name,BS_PressInfo.AbbreviatedName "
			" from BS_ProcureNoteHeader left join BS_ProcureNote on  BS_ProcureNoteHeader.id =  BS_ProcureNote.ProcureNtHeaderID "
			" left join BS_BookCatalog on BS_ProcureNote.BkcatalogID = BS_BookCatalog.id "
			" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id where BS_ProcureNoteHeader.ProcureNtCode = " + aq1->FieldByName("ProcureNtCode")->AsString ;
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprocurequery::SpeedButton2Click(TObject *Sender)
{
	//转入入库
	if (aq2->IsEmpty() ) {
        return;
	}
	int supplierid;
	if (ZNStorage->dsetNote->IsEmpty() )
	{
		supplierid =  aq2->FieldByName("SupplierID")->AsInteger;
	}
	else
	{
		supplierid =  ZNStorage->dsetNtHeader->FieldByName("SupplierID")->AsInteger;
	}
	if (DBGrid1->SelectedRows->Count > 0) {
    	for (int i =0; i < DBGrid1->SelectedRows->Count ; i++) {
			aq2->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
			if (ZNStorage->dsetNote->RecordCount > 0 && supplierid != aq2->FieldByName("SupplierID")->AsInteger) {
				MessageBox(0,"入库供应商不一致！","智能入库" ,MB_OK);
				return;
			}
			ZNStorage->AddNote(supplierid,aq2->FieldByName("BkcatalogID")->AsInteger);

			ZNStorage->dsetNote->Edit();
			ZNStorage->dsetNote->FieldByName("Amount")->AsInteger =  aq2->FieldByName("Amount")->AsInteger ;
			ZNStorage->dsetNote->FieldByName("Discount")->AsFloat  =  aq2->FieldByName("Discount")->AsFloat ;
			ZNStorage->UpdateNote();
			supplierid =  aq2->FieldByName("SupplierID")->AsInteger;
		}
	}
	else
	{
		if (ZNStorage->dsetNote->RecordCount > 0 && supplierid != aq2->FieldByName("SupplierID")->AsInteger) {
			MessageBox(0,"入库供应商不一致！","智能入库" ,MB_OK);
			return;
		}
		ZNStorage->AddNote(supplierid,aq2->FieldByName("BkcatalogID")->AsInteger);

		ZNStorage->dsetNote->Edit();
		ZNStorage->dsetNote->FieldByName("Amount")->AsInteger =  aq2->FieldByName("Amount")->AsInteger ;
		ZNStorage->dsetNote->FieldByName("Discount")->AsFloat  =  aq2->FieldByName("Discount")->AsFloat ;
		ZNStorage->UpdateNote();
	}

	if (ZNStorage->dsetNote->IsEmpty() ) {
    	ZNStorage->dsetNtHeader->Edit();
		ZNStorage->dsetNtHeader->FieldByName("SupplierID")->AsInteger = supplierid;
		ZNStorage->UpdateNtHeader();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprocurequery::N1Click(TObject *Sender)
{
	for (int i = 1; i <= aq2->RecordCount; i++) {
		DBGrid1->DataSource->DataSet->RecNo = i;
		DBGrid1->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------
