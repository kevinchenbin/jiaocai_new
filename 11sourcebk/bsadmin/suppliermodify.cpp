//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "suppliermodify.h"
#include "unitsupplier.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzLabel"
#pragma resource "*.dfm"
Tfrmsuppliermodify *frmsuppliermodify;
//---------------------------------------------------------------------------
__fastcall Tfrmsuppliermodify::Tfrmsuppliermodify(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
    con = cn;
	aq->Connection = cn;
	query->Connection = cn;
	String sql = "select * from CUST_CustomerInfo where Type = 1";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof )
	{
		cbsupplier->AddItem(query->FieldByName("ID")->AsString + query->FieldByName("Name")->AsString,(TObject*)query->FieldByName("ID")->AsInteger);
		query->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsuppliermodify::cbQueryTypeClick(TObject *Sender)
{
	if (cbQueryType->Text == "条码") {
		edtQuery->MaxLength = 13;
		edtQuery->NumbersOnly = true;
	}
	if (cbQueryType->Text == "书号") {
		edtQuery->MaxLength = 13;
		edtQuery->NumbersOnly = false;
	}
	if (cbQueryType->Text == "自编码") {
		edtQuery->MaxLength = 0;
		edtQuery->NumbersOnly = false;
	}
	if (cbQueryType->Text == "书名") {
		edtQuery->MaxLength = 0;
		edtQuery->NumbersOnly = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsuppliermodify::edtQueryKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		String condition = edtQuery->Text ;
		if(cbQueryType->Value == 1)
		{
			if(condition.Length() != 13 )
			{
				MessageBox(0,"位数不正确！","输入错误" ,MB_OK);
				return;
			}
			for(int i=1;i<condition.Length();i++ )
			if(condition.SubString(i,1)>='0'&&condition.SubString(i,1)<='9'  )
			continue;
			else
			{
				MessageBox(0,"请输入数字！","输入错误" ,MB_OK);
				return;
			}
		}
		else if(cbQueryType->Value == 2)
		{
			int i = condition.Length();
			if(i!=13)
			if(i!=10 )
			{
				MessageBox(0,"查询位数不正确！","输入错误" ,MB_OK);
				return;
			}
			for(int i=1;i<condition.Length();i++ )
			if(condition.SubString(i,1)>='0'&&condition.SubString(i,1)<='9'  )
			continue;
			else
			{
				MessageBox(0,"请输入数字！","输入错误" ,MB_OK);
				return;
			}
		}
		else if(cbQueryType->Value == 3)
		{
			for(int i=1;i<condition.Length();i++ )
			if(condition.SubString(i,1)>='a'&&condition.SubString(i,1)<='z'||condition.SubString(i,1)>='A'&&condition.SubString(i,1)<='Z'    )
			continue;
			else
			{
				MessageBox(0,"请输入正确的自编码！","输入错误" ,MB_OK);
				return;
			}
		}
		//Query();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsuppliermodify::Query(String condition)
{
	String sql ;
	/*if (cbdetail->Checked ) {
		sql  = sql = " select BS_BookCatalog.ID,STK_BookInfo.ID as bkid,STK_BookInfo.BkstackID,BS_BookCatalog.Author,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.fullname "
			  " from BS_BookCatalog  join STK_BookInfo on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			  " left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			  " left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			  " left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			  " where BS_BookCatalog.Unavailable=1 ";
		if (cbQueryType->Value == 1) {
			sql = sql + " and BS_BookCatalog.Barcode='" + edtQuery->Text + "'";
		}
		if (cbQueryType->Value == 2) {
			sql = sql + " and BS_BookCatalog.ISBN='" + edtQuery->Text + "'";
		}
		if (cbQueryType->Value == 3) {
			sql = sql + " and BS_BookCatalog.UserDefCode like '%" + edtQuery->Text + "%'";
		}
		if (cbQueryType->Value == 4) {
			sql = sql + " and BS_BookCatalog.Name like '%" + edtQuery->Text + "%'";
		}
	}  */
	if (cbheader->Checked ) {
		sql  = sql = " select BS_BookCatalog.ID,BS_StorageNote.id as bsnoteid,STK_BookInfo.BkstackID,STK_BookInfo.ID as bkid,BS_StorageNote.Amount as samount,BS_BookCatalog.Author,STK_BookInfo.SupplierID,BS_BookCatalog.Name,BS_BookCatalog.Barcode,BS_BookCatalog.UserDefCode,BS_BookCatalog.ISBN,CUST_CustomerInfo.Name as SupplierName,STK_BookInfo.Amount,STK_BookstackInfo.Name as BkstackName,BS_BookCatalog.Price ,BS_PressInfo.fullname "
			  " from BS_BookCatalog  join STK_BookInfo on STK_BookInfo.BkcatalogID=BS_BookCatalog.ID "
			  " left join STK_BookstackInfo on STK_BookInfo.BkstackID=STK_BookstackInfo.ID "
			  " left join BS_PressInfo ON BS_BookCatalog.PressID = BS_PressInfo.ID "
			  " left join BS_StorageNote on BS_StorageNote.BkInfoID = STK_BookInfo.ID "
			  " left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.ID "
			  " left join CUST_CustomerInfo on STK_BookInfo.SupplierID=CUST_CustomerInfo.ID "
			  " where BS_BookCatalog.Unavailable=1 and BS_StorageNoteHeader.StgNtCode = " + condition ;
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsuppliermodify::BtnChangeOptionsClick(TObject *Sender)
{
	String sql;
	if (aq->IsEmpty() ) {
		return;
	}
	int supplierid = (int)cbsupplier->Items->Objects[cbsupplier->ItemIndex];
	int bkid;
	if (cbheader->Checked ) {
		sql = "update BS_StorageNoteHeader set SupplierID = " +  IntToStr(supplierid) + " where StgNtCode = " + edntheader->Text ;
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
			query->ExecSQL();  */
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
		aq->Active = false;
		aq->Active = true;
	}
	/*else
	{
		float nochecked = 0.0,fixedprice = 0.0,discountprice = 0.0,discount = 0.0,totalfixedprice = 0.0, totaldiscountprice = 0.0;
		int totalamount = 0;
		sql = "select max(StgNtCode) as StgNtCode from BS_StorageNoteHeader";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		long  StgNtCode =  query->FieldByName("StgNtCode")->AsFloat + 1;
		sql = "insert into BS_StorageNoteHeader(StgNtCode,HdTime,StgID,SupplierID,State,OperatorID) values(" + StgNtCode +",getdate()," + IntToStr(stgid) + "," + IntToStr(supplierid) + ",0," + IntToStr(userid) +")"
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
        sql = "select max(id) as id from BS_StorageNoteHeader";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		int sntheadid = query->FieldByName("id")->AsInteger ;
		for (int i = 0; i < dgdetail->SelectedRows->Count ; i++) {
			aq->GotoBookmark(dgdetail->SelectedRows->Items[i]);
			totalamount = totalamount + aq->FieldByName("Amount")->AsInteger;
			fixedprice =  aq->FieldByName("Price")->AsFloat * aq->FieldByName("Amount")->AsInteger;
			totalfixedprice = totalfixedprice + fixedprice;
			sql = "select discount from BS_StorageNote where BkInfoID = " + aq->FieldByName("bkid")->AsString ;
            query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount > 0) {
				discount = query->FieldByName("discount")->AsFloat ;
			}
			else
			{
            	discount = 100;
			}
			discountprice =  fixedprice * discount;
			totaldiscountprice = totaldiscountprice + discountprice;
			sql = "select * from STK_BookInfo where BkcatalogID = " + aq->FieldByName("ID")->AsString + " and SupplierID = " + IntToStr(supplierid) + " and BkstackID = " + aq->FieldByName("BkstackID")->AsString;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			if (query->RecordCount > 0) {
				bkid = query->FieldByName("ID")->AsInteger ;
				sql = "update STK_BookInfo set Amount = Amount + " + aq->FieldByName("Amount")->AsString + " where id = " + query->FieldByName("ID")->AsString ;
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
			}
			else
			{
				sql = "insert into STK_BookInfo(Amount,BkcatalogID,BkstackID,SupplierID,State) values (" +aq->FieldByName("Amount")->AsString + "," + aq->FieldByName("ID")->AsString + "," + aq->FieldByName("BkstackID")->AsString + "," + IntToStr(supplierid) + ",0)";
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
			sql = "update STK_BookInfo set Amount = Amount - " + aq->FieldByName("Amount")->AsString + " where id = " + aq->FieldByName("bkid")->AsString ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
			sql = "insert into BS_StorageNote(Amount,Discount,StgNtHeaderID,BkInfoID,FixedPrice,DiscountedPrice) values (" + aq->FieldByName("Amount")->AsString + "," + FloatToStr(discount) + "," + IntToStr(sntheadid) + "," + IntToStr(bkid) + "," + FloatToStr(FixedPrice) + "," + FloatToStr("discountprice") + ")" ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
			sql = "delete from BS_StorageNote where BkInfoID = " + aq->FieldByName("bkid")->AsString ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
		}
		sql = "update BS_StorageNoteHeader set NoChecked = " + FloatToStr("totaldiscountprice") + ",TotalFixedPrice = " + FloatToStr(totalfixedprice) + ",TotalDiscountedPrice = " + FloatToStr("totaldiscountprice") + ",TotalAmount = " + IntToStr(totalamount);
        query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}*/
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsuppliermodify::edntheaderKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
    	Query(edntheader->Text);
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsuppliermodify::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsuppliermodify::cbdetailClick(TObject *Sender)
{
	if (cbdetail->Checked ) {
		cbheader->Checked = false;
	}
	else
	{
		cbheader->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsuppliermodify::cbheaderClick(TObject *Sender)
{
	if (cbheader->Checked ) {
		cbdetail->Checked = false;
	}
	else
	{
		cbdetail->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsuppliermodify::BtnVerticalTileClick(TObject *Sender)
{
	Tfrmsupplierunit *frm = new Tfrmsupplierunit(Application,con);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsuppliermodify::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

