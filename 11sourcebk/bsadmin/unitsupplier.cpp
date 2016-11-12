//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unitsupplier.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmsupplierunit *frmsupplierunit;
//---------------------------------------------------------------------------
__fastcall Tfrmsupplierunit::Tfrmsupplierunit(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
	aq->Connection = cn;
	query->Connection = cn;
	String sql = "select * from CUST_CustomerInfo where Type = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbsupplierbefore->AddItem(aq->FieldByName("ID")->AsString + aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger);
		cbsupplierafter->AddItem(aq->FieldByName("ID")->AsString + aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger);
		aq->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsupplierunit::BtnTileClick(TObject *Sender)
{
	String sql;
	if (cbsupplierbefore->Text == "" || cbsupplierafter->Text == "") {
    	return;
	}
	int supplier = (int)cbsupplierbefore->Items->Objects[cbsupplierbefore->ItemIndex];
	sql = " select BS_BookCatalog.ID,BS_StorageNote.id as bsnoteid,STK_BookInfo.BkstackID,STK_BookInfo.ID as bkid,BS_StorageNote.Amount as samount,BS_BookCatalog.Author,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.fullname "
		" from BS_BookCatalog  join STK_BookInfo on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
		" left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
		" left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
		" left join BS_StorageNote on BS_StorageNote.BkInfoID = STK_BookInfo.ID "
		" left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.ID "
		" left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
		" where BS_BookCatalog.Unavailable=1 and STK_BookInfo.SupplierID = " + IntToStr(supplier) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	int supplierid = (int)cbsupplierafter->Items->Objects[cbsupplierafter->ItemIndex];
	BtnChange(aq,supplierid);
	sql = "delete from STK_BookInfo where supplierID = " + IntToStr(supplier);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
	sql = "delete from CUST_CustomerInfo where id = " + IntToStr(supplier);
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
	MessageBox(0,"供应商合并完毕!","提示",MB_ICONEXCLAMATION);
}
//---------------------------------------------------------------------------

void Tfrmsupplierunit::BtnChange(TADOQuery *aq,int supplier)
{
	String sql;
	if (aq->IsEmpty() ) {
		return;
	}
	int supplierbefore = (int)cbsupplierbefore->Items->Objects[cbsupplierbefore->ItemIndex];
	int supplierid = supplier;
	int bkid;
		sql = "update BS_StorageNoteHeader set SupplierID = " +  IntToStr(supplierid) + " where SupplierID = " + IntToStr(supplierbefore) ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		aq->First();
		while (!aq->Eof )
		{
			sql = "select * from STK_BookInfo where BkcatalogID = " + aq->FieldByName("ID")->AsString + " and SupplierID = " + IntToStr(supplierid) + " and BkstackID = " + aq->FieldByName("BkstackID")->AsString;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount > 0) {
				bkid = query->FieldByName("ID")->AsInteger ;
				sql = "update STK_BookInfo set Amount = Amount + " + aq->FieldByName("samount")->AsString + " where id = " + query->FieldByName("ID")->AsString ;
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
			}
			else
			{
				sql = "insert into STK_BookInfo(Amount,BkcatalogID,BkstackID,SupplierID,State) values (" +aq->FieldByName("samount")->AsString + "," + aq->FieldByName("ID")->AsString + "," + aq->FieldByName("BkstackID")->AsString + "," + IntToStr(supplierid) + ",0)";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
				sql = "select max(id) as id from STK_BookInfo";
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->Open();
				bkid = query->FieldByName("id")->AsInteger ;
			}
			/*sql = "update STK_BookInfo set Amount = Amount - " + aq->FieldByName("samount")->AsString + " where id = " + aq->FieldByName("bkid")->AsString ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL(); */
			sql = "update BS_StorageNote set BkInfoID = " + IntToStr(bkid) + " where id = " + aq->FieldByName("bsnoteid")->AsString ;
            query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
            	sql = "update STK_BookInfo set Amount = Amount - " + aq->FieldByName("samount")->AsString + " where id = " + IntToStr(bkid);
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();

			aq->Next();
		}
}

void __fastcall Tfrmsupplierunit::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
