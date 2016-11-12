//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "retailbookup.h"
#include "hoistoryview.h"
#include "bookhistory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
Tfrmretailbookup *frmretailbookup;
//---------------------------------------------------------------------------
__fastcall Tfrmretailbookup::Tfrmretailbookup(TComponent* Owner,TADOConnection *con,int stgid,int userid)
	: TForm(Owner)
{
	fcon = con;
	fstgid = stgid;
	fuserid = userid;
	qudetail->Connection = con;
	dtpbegin->Date = Date();
	dtpend->Date = Date();
	chbegin->Checked = true;
	chend->Checked = true;

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	AnsiString sql;
	sql = "select ID,Name from SYS_StorageInfo where id = " + IntToStr(stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	Edit1->Text = IntToStr(stgid);
	Edit2->Text = aq->FieldByName("Name")->AsAnsiString ;

	sql = "select ID,Name from SYS_StorageInfo " ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		if (sqlstorage == "") {
			sqlstorage = "[" + aq->FieldByName("ID")->AsAnsiString + "]";
		}
		else
		{
			sqlstorage = sqlstorage + ",[" + aq->FieldByName("ID")->AsAnsiString + "]";
		}

		aq->Next();
	}

	sql = "select id,AbbreviatedName from BS_PressInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
		aq->Next();
	}

	sql = "select id,name from CUST_CustomerInfo where type = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbsupplier->AddItem(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
		aq->Next();
	}
	delete aq;
	BtnView->Click();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmretailbookup::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (!qudetail->IsEmpty() ) {
    	AnsiString sql ;
		sql = sql = sql = "update stk_bookinfo set selected = 0 where stgid = " + IntToStr(fstgid);

		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
	}
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmretailbookup::BtnExportClick(TObject *Sender)
{
	if (qudetail->IsEmpty() ) {
		return;
	}
	if (qudetail->Active && qudetail->RecordCount > 0) {
		DbgridToExcel(dgdetail);
	}
}
//---------------------------------------------------------------------------
//Excel导出函数
bool __fastcall Tfrmretailbookup::DbgridToExcel(TDBGridEh* dbg)
{
	AnsiString sql,sql1;
	AnsiString temptext,path,DBPath;
	int  iFileHandle;
	int   iFileLength;

	sql = " select distinct F.name "
			" from  stk_bookinfo D left join BS_BookCatalog A on D.bkcatalogid = A.id "
			" left join BS_PressInfo B on A.pressid = B.id "
			" left join CUST_CustomerInfo F ON D.supplierid = F.ID "
			" left join (select  E.bkinfoid,sum(E.amount) as retailamount, "
			" sum(E.FixedPrice) AS RetailFixedPrice,sum(E.DiscountedPrice) as RetailDiscountedPrice "
			" from BS_RetailNoteHeader join BS_RetailNote E ON BS_RetailNoteHeader.ID = E.RetailNtHeaderID "
			" where BS_RetailNoteHeader.stgid = " + IntToStr(fstgid) + sqltime +
			" group by E.bkinfoid " + sqlls + ") H on D.id = H.bkinfoid "
			" left join (select  E.bkinfoid,sum(E.amount) as wsaleamount, "
			" sum(E.FixedPrice) AS WsaleFixedPrice,sum(E.DiscountedPrice) as WsaleDiscountedPrice "
			" from BS_WsaleNoteHeader join BS_WsaleNote E ON BS_WsaleNoteHeader.ID = E.WsaleNtHeaderID "
			" where BS_WsaleNoteHeader.stgid = " + IntToStr(fstgid) + sqltime +
			" group by E.bkinfoid " + sqlws + ") I on D.id = I.bkinfoid "
			" WHERE (I.wsaleamount > 0 or H.retailamount > 0) " + sqlwhere ;

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	TADOQuery *aq1 = new TADOQuery(this);
	aq1->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	savedlg->FileName = aq->FieldByName("name")->AsAnsiString ;
	if (savedlg->Execute())
	{
		String Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
	}
	else
	{
		return false;
	}

	aq->First();
	while (!aq->Eof )
	{
		path = DBPath + aq->FieldByName("name")->AsAnsiString + ".csv";
		if(FileExists(path))
			if (DeleteFileA(path))
				iFileHandle = FileCreate(path.c_str());
			else
				return false;
		else
		iFileHandle = FileCreate(path.c_str());
        temptext = "";
		for(int q=1;q<dbg->FieldCount ;++q)
		{
			if (dbg->Columns->Items[q]->Visible == true) {
				temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

		sql1 = " select rank() over (order by D.id) as xuhao,D.id as stkid,A.id,A.ISBN,A.name,A.Price,B.AbbreviatedName,C.Name as typename,G.Name as stackname,F.id as supplierid,F.name as suppliername,D.selected, "
			" H.retailamount,H.RetailFixedPrice,H.RetailDiscountedPrice,I.wsaleamount,I.WsaleFixedPrice,I.WsaleDiscountedPrice ," + sqlstorage +
			" from  stk_bookinfo D left join BS_BookCatalog A on D.bkcatalogid = A.id "
			" left join BS_PressInfo B on A.pressid = B.id "
			" left join BS_BookType C on A.smallBookTypeID = C.id "
			" left join STK_BookstackInfo G on D.BkstackID = G.id "
			" left join CUST_CustomerInfo F ON D.supplierid = F.ID "
			" left join (select  E.bkinfoid,sum(E.amount) as retailamount, "
			" sum(E.FixedPrice) AS RetailFixedPrice,sum(E.DiscountedPrice) as RetailDiscountedPrice "
			" from BS_RetailNoteHeader join BS_RetailNote E ON BS_RetailNoteHeader.ID = E.RetailNtHeaderID "
			" where BS_RetailNoteHeader.stgid = " + IntToStr(fstgid) + sqltime +
			" group by E.bkinfoid " + sqlls + ") H on D.id = H.bkinfoid "
			" left join (select  E.bkinfoid,sum(E.amount) as wsaleamount, "
			" sum(E.FixedPrice) AS WsaleFixedPrice,sum(E.DiscountedPrice) as WsaleDiscountedPrice "
			" from BS_WsaleNoteHeader join BS_WsaleNote E ON BS_WsaleNoteHeader.ID = E.WsaleNtHeaderID "
			" where BS_WsaleNoteHeader.stgid = " + IntToStr(fstgid) + sqltime +
			" group by E.bkinfoid " + sqlws + ") I on D.id = I.bkinfoid left join "
			" (select bkcatalogid ," + sqlstorage +
			" from (select bkcatalogid,amount,stgid from stk_bookinfo ) as SourceTable "
			" pivot(sum(amount) for stgid in(" + sqlstorage + ")) as PivotTable) J on D.BkcatalogID = J.bkcatalogid"
			" WHERE (I.wsaleamount > 0 or H.retailamount > 0) " + sqlwhere + " and F.Name = '" + aq->FieldByName("name")->AsString + "'";



		/*sql1 = "select rank() over (order by D.id) as xuhao,A.id,A.ISBN,A.name,A.Price,B.AbbreviatedName,C.Name as typename,G.Name as stackname,D.Amount,sum(E.amount) as retailamount, "
			" sum(E.FixedPrice) AS FixedPrice,sum(E.DiscountedPrice) as DiscountedPrice,F.name as suppliername "
			" from BS_RetailNoteHeader join BS_RetailNote E ON BS_RetailNoteHeader.ID = E.RetailNtHeaderID "
			" left join stk_bookinfo D on E.BkInfoID = D.id "
			" left join BS_BookCatalog A on D.bkcatalogid = A.id "
			" left join BS_PressInfo B on A.pressid = B.id "
			" left join BS_BookType C on A.smallBookTypeID = C.id "
			" left join STK_BookstackInfo G on D.BkstackID = G.id "
			" left join CUST_CustomerInfo F ON D.supplierid = F.ID " ;
		sql1 = sql1 + sqlwhere + " and F.Name = '" + aq->FieldByName("name")->AsString +
			"' group by A.ISBN,A.name,A.Price,B.AbbreviatedName,C.Name,D.Amount,F.name,A.id,D.id,G.Name" ;   */
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql1);
		aq1->Open();
		while (!aq1->Eof )
		{
            temptext = "\n";
			for(int j=2;j<dbg->Columns ->Count+1;j++)
			{
				if (dbg->Columns->Items[j-1]->Visible == true) {
					if (dbg->Columns ->Items [j-1]->FieldName == "Name") {
						AnsiString bookname;
						bookname = aq1->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
						bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
						temptext = temptext + bookname + ",";
					}
					else
					{
						temptext = temptext + aq1->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
				}
			}
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
			aq1->Next();
		}
		FileClose(iFileHandle);
		aq->Next();
	}
	delete aq;
	delete aq1;
	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}

//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::N4Click(TObject *Sender)
{
	if (qudetail->RecordCount > 0) {
    	Tfrmhistoryview *frm = new Tfrmhistoryview(Application,fcon,qudetail->FieldByName("id")->AsInteger );
		frm->ShowModal();
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmretailbookup::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F6) {
		BtnExport->Click();
	}
	if (Key == VK_F7) {
		BtnExport1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		BtnView->Click();
	}

	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::BtnViewClick(TObject *Sender)
{
	AnsiString sql ;
	sqlwhere = "";
	sqltime = "";
	sqlls = "";
	sqlws = "";
	if (chbegin->Checked ) {
		sqltime =  " and datediff(day,'" + DateToStr(dtpbegin->Date) + "',HdTime) >= 0 ";
	}
	if (chend->Checked ) {
		sqltime = sqltime + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0 ";
	}
	if (chbkinfo->Checked ) {
		if (edmin->Text != "") {
			sqlwhere = sqlwhere + " and D.amount >= " + edmin->Text ;
		}
		if (edmax->Text != "") {
            sqlwhere = sqlwhere + " and D.amount <= " + edmax->Text ;
		}
	}
	if (chpress->Checked && cbpress->Text != "") {
    	sqlwhere = sqlwhere + " and B.AbbreviatedName = '" + cbpress->Text.Trim() + "'";
	}

	if (chsupplier->Checked && cbsupplier->Text != "") {
		sqlwhere = sqlwhere + " and F.name = '" + cbsupplier->Text.Trim() + "'";
	}
	if (chbox2->Checked ) {
		sqlwhere = sqlwhere + " and D.id not in(select BkInfoID from BS_StorageNote join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.id "
			" where BS_StorageNoteHeader.stgid = " + IntToStr(fstgid) + sqltime + " and BS_StorageNote.amount < 0)";
	}
	if (chls->Checked) {
		if (edlsmin->Text != "") {
			sqlls = " having sum(amount) >= " + edlsmin->Text ;
		}
		if (edlsmax->Text != "") {
			if (sqlls == "") {
				sqlls = " having sum(amount) <= " + edlsmax->Text ;
			}
			else
			{
				sqlls = sqlls + " and sum(amount) <= " + edlsmax->Text ;
			}
		}
	}
	if (chws->Checked ) {
		if (edwsmin->Text != "") {
			sqlws = " having sum(amount) >= " + edwsmin->Text ;
		}
		if (edwsmax->Text != "") {
			if (sqlws == "") {
				sqlws = " having sum(amount) <= " + edwsmax->Text ;
			}
			else
			{
				sqlws = sqlws + " and sum(amount) <= " + edwsmax->Text ;
			}
		}
	}

	sql = " select rank() over (order by D.id) as xuhao,D.id as stkid,A.id,A.ISBN,A.name,A.Price,B.AbbreviatedName,C.Name as typename,G.Name as stackname,F.id as supplierid,F.name as suppliername,D.selected, "
			" H.retailamount,H.RetailFixedPrice,H.RetailDiscountedPrice,I.wsaleamount,I.WsaleFixedPrice,I.WsaleDiscountedPrice ," + sqlstorage +
			" from  stk_bookinfo D left join BS_BookCatalog A on D.bkcatalogid = A.id "
			" left join BS_PressInfo B on A.pressid = B.id "
			" left join BS_BookType C on A.smallBookTypeID = C.id "
			" left join STK_BookstackInfo G on D.BkstackID = G.id "
			" left join CUST_CustomerInfo F ON D.supplierid = F.ID "
			" left join (select  E.bkinfoid,sum(E.amount) as retailamount, "
			" sum(E.FixedPrice) AS RetailFixedPrice,sum(E.DiscountedPrice) as RetailDiscountedPrice "
			" from BS_RetailNoteHeader join BS_RetailNote E ON BS_RetailNoteHeader.ID = E.RetailNtHeaderID "
			" where BS_RetailNoteHeader.stgid = " + IntToStr(fstgid) + sqltime +
			" group by E.bkinfoid " + sqlls + ") H on D.id = H.bkinfoid "
			" left join (select  E.bkinfoid,sum(E.amount) as wsaleamount, "
			" sum(E.FixedPrice) AS WsaleFixedPrice,sum(E.DiscountedPrice) as WsaleDiscountedPrice "
			" from BS_WsaleNoteHeader join BS_WsaleNote E ON BS_WsaleNoteHeader.ID = E.WsaleNtHeaderID "
			" where BS_WsaleNoteHeader.stgid = " + IntToStr(fstgid) + sqltime +
			" group by E.bkinfoid " + sqlws + ") I on D.id = I.bkinfoid left join "
			" (select bkcatalogid ," + sqlstorage +
			" from (select bkcatalogid,amount,stgid from stk_bookinfo ) as SourceTable "
			" pivot(sum(amount) for stgid in(" + sqlstorage + ")) as PivotTable) J on D.BkcatalogID = J.bkcatalogid"
			" WHERE (I.wsaleamount > 0 or H.retailamount > 0) " + sqlwhere ;

	qudetail->Close();
	qudetail->SQL->Clear();
	qudetail->SQL->Add(sql);
	qudetail->Open();
    TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = "select ID,Name from SYS_StorageInfo where id <> " + IntToStr(fstgid)  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	AnsiString ss = IntToStr(fstgid);
	dgdetail->Columns->Items[13]->Field = qudetail->FieldByName(ss);
	int i = 1;
	while (!aq->Eof && i <= 10 )
	{
		ss = aq->FieldByName("ID")->AsAnsiString ;
		dgdetail->Columns->Items[13+i]->Field = qudetail->FieldByName(ss);
		dgdetail->Columns->Items[13+i]->Visible = true;
		dgdetail->Columns->Items[13+i]->Title->Caption = aq->FieldByName("Name")->AsString ;
		aq->Next();
		i++;
	}
	maxlen = 12 + i;
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::dtpbeginChange(TObject *Sender)
{
	chbegin->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::dgdetailTitleClick(TColumnEh *Column)
{
	if (qudetail->RecordCount > 0) {
    	AnsiString qusort;
		qusort =  Column->FieldName + " ASC";
		if (qudetail->Sort == "") {
			qudetail->Sort =  Column->FieldName + " ASC";
		}
		else if (qudetail->Sort == qusort) {
			qudetail->Sort =  Column->FieldName + " DESC";
		}
		else
		{
			qudetail->Sort =  Column->FieldName + " ASC";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::btallClick(TObject *Sender)
{
	if (qudetail->IsEmpty() ) {
        return;
	}
	AnsiString sql ;
	sql = "update stk_bookinfo set selected = 1 where stgid = " + IntToStr(fstgid);

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;

	qudetail->Active = false;
	qudetail->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::btconcelClick(TObject *Sender)
{
	if (qudetail->IsEmpty() ) {
        return;
	}
	AnsiString sql ;
	sql = sql = "update stk_bookinfo set selected = 0 where stgid = " + IntToStr(fstgid);

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;

	qudetail->Active = false;
	qudetail->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::BtnExport1Click(TObject *Sender)
{
	AnsiString sql,sql1;
	AnsiString temptext,path,DBPath;
	int  iFileHandle;
	int   iFileLength;

	sql = " select distinct F.name "
			" from  stk_bookinfo D left join BS_BookCatalog A on D.bkcatalogid = A.id "
			" left join BS_PressInfo B on A.pressid = B.id "
			" left join CUST_CustomerInfo F ON D.supplierid = F.ID "
			" left join (select  E.bkinfoid,sum(E.amount) as retailamount, "
			" sum(E.FixedPrice) AS RetailFixedPrice,sum(E.DiscountedPrice) as RetailDiscountedPrice "
			" from BS_RetailNoteHeader join BS_RetailNote E ON BS_RetailNoteHeader.ID = E.RetailNtHeaderID "
			" where BS_RetailNoteHeader.stgid = " + IntToStr(fstgid) + sqltime +
			" group by E.bkinfoid " + sqlls + ") H on D.id = H.bkinfoid "
			" left join (select  E.bkinfoid,sum(E.amount) as wsaleamount, "
			" sum(E.FixedPrice) AS WsaleFixedPrice,sum(E.DiscountedPrice) as WsaleDiscountedPrice "
			" from BS_WsaleNoteHeader join BS_WsaleNote E ON BS_WsaleNoteHeader.ID = E.WsaleNtHeaderID "
			" where BS_WsaleNoteHeader.stgid = " + IntToStr(fstgid) + sqltime +
			" group by E.bkinfoid " + sqlws + ") I on D.id = I.bkinfoid "
			" WHERE (I.wsaleamount > 0 or H.retailamount > 0) and D.selected = 1 " + sqlwhere ;

	/*sql = "select distinct F.name "
			" from BS_RetailNoteHeader join BS_RetailNote E ON BS_RetailNoteHeader.ID = E.RetailNtHeaderID "
			" left join stk_bookinfo D on E.BkInfoID = D.id "
			" left join CUST_CustomerInfo F ON D.supplierid = F.ID " ;
	sql = sql + sqlwhere + " and D.selected = 1 ";  */
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	TADOQuery *aq1 = new TADOQuery(this);
	aq1->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	savedlg->FileName = aq->FieldByName("name")->AsAnsiString ;
	if (savedlg->Execute())
	{
		String Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
	}
	else
	{
		return ;
	}

	aq->First();
	while (!aq->Eof )
	{
		path = DBPath + aq->FieldByName("name")->AsAnsiString + ".csv";
		if(FileExists(path))
			if (DeleteFileA(path))
				iFileHandle = FileCreate(path.c_str());
			else
				return ;
		else
		iFileHandle = FileCreate(path.c_str());
        temptext = "";
		for(int q=1;q<dgdetail->FieldCount ;++q)
		{
			if (dgdetail->Columns->Items[q]->Visible == true) {
				temptext = temptext + dgdetail->Columns ->Items [q]->Title ->Caption + ",";
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

		sql1 = " select rank() over (order by D.id) as xuhao,D.id as stkid,A.id,A.ISBN,A.name,A.Price,B.AbbreviatedName,C.Name as typename,G.Name as stackname,F.id as supplierid,F.name as suppliername,D.selected, "
			" H.retailamount,H.RetailFixedPrice,H.RetailDiscountedPrice,I.wsaleamount,I.WsaleFixedPrice,I.WsaleDiscountedPrice ," + sqlstorage +
			" from  stk_bookinfo D left join BS_BookCatalog A on D.bkcatalogid = A.id "
			" left join BS_PressInfo B on A.pressid = B.id "
			" left join BS_BookType C on A.smallBookTypeID = C.id "
			" left join STK_BookstackInfo G on D.BkstackID = G.id "
			" left join CUST_CustomerInfo F ON D.supplierid = F.ID "
			" left join (select  E.bkinfoid,sum(E.amount) as retailamount, "
			" sum(E.FixedPrice) AS RetailFixedPrice,sum(E.DiscountedPrice) as RetailDiscountedPrice "
			" from BS_RetailNoteHeader join BS_RetailNote E ON BS_RetailNoteHeader.ID = E.RetailNtHeaderID "
			" where BS_RetailNoteHeader.stgid = " + IntToStr(fstgid) + sqltime +
			" group by E.bkinfoid " + sqlls + ") H on D.id = H.bkinfoid "
			" left join (select  E.bkinfoid,sum(E.amount) as wsaleamount, "
			" sum(E.FixedPrice) AS WsaleFixedPrice,sum(E.DiscountedPrice) as WsaleDiscountedPrice "
			" from BS_WsaleNoteHeader join BS_WsaleNote E ON BS_WsaleNoteHeader.ID = E.WsaleNtHeaderID "
			" where BS_WsaleNoteHeader.stgid = " + IntToStr(fstgid) + sqltime +
			" group by E.bkinfoid " + sqlws + ") I on D.id = I.bkinfoid left join "
			" (select bkcatalogid ," + sqlstorage +
			" from (select bkcatalogid,amount,stgid from stk_bookinfo ) as SourceTable "
			" pivot(sum(amount) for stgid in(" + sqlstorage + ")) as PivotTable) J on D.BkcatalogID = J.bkcatalogid"
			" WHERE (I.wsaleamount > 0 or H.retailamount > 0) " + sqlwhere + " and F.Name = '" + aq->FieldByName("name")->AsString + "' and D.selected = 1";

		/*sql1 = "select rank() over (order by D.id) as xuhao,A.id,A.ISBN,A.name,A.Price,B.AbbreviatedName,C.Name as typename,G.Name as stackname,D.Amount,sum(E.amount) as retailamount, "
			" sum(E.FixedPrice) AS FixedPrice,sum(E.DiscountedPrice) as DiscountedPrice,F.name as suppliername "
			" from BS_RetailNoteHeader join BS_RetailNote E ON BS_RetailNoteHeader.ID = E.RetailNtHeaderID "
			" left join stk_bookinfo D on E.BkInfoID = D.id "
			" left join BS_BookCatalog A on D.bkcatalogid = A.id "
			" left join BS_PressInfo B on A.pressid = B.id "
			" left join BS_BookType C on A.smallBookTypeID = C.id "
			" left join STK_BookstackInfo G on D.BkstackID = G.id "
			" left join CUST_CustomerInfo F ON D.supplierid = F.ID " ;
		sql1 = sql1 + sqlwhere + " and F.Name = '" + aq->FieldByName("name")->AsString + "' and D.selected = 1 "
			" group by A.ISBN,A.name,A.Price,B.AbbreviatedName,C.Name,D.Amount,F.name,A.id,D.id,G.Name" ;  */
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql1);
		aq1->Open();
		while (!aq1->Eof )
		{
            temptext = "\n";
			for(int j=2;j<dgdetail->Columns ->Count+1;j++)
			{
				if (dgdetail->Columns->Items[j-1]->Visible == true) {
					if (dgdetail->Columns ->Items [j-1]->FieldName == "Name") {
						AnsiString bookname;
						bookname = aq1->FieldByName(dgdetail->Columns ->Items [j-1]->FieldName )->AsAnsiString;
						bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
						temptext = temptext + bookname + ",";
					}
					else
					{
						temptext = temptext + aq1->FieldByName(dgdetail->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
				}
			}
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
			aq1->Next();
		}
		FileClose(iFileHandle);
		aq->Next();
	}
	delete aq;
	delete aq1;
	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::dgdetailDblClick(TObject *Sender)
{
	if (qudetail->IsEmpty() ) {
    	return;
	}
	if (modle == 1) {
		Ord->AddNote(qudetail->FieldByName("supplierid")->AsInteger ,qudetail->FieldByName("id")->AsInteger );
	}
	if (modle == 2) {
		Diaobo->AddNote(qudetail->FieldByName("stkid")->AsInteger);
	}
	if (modle == 3) {
        Pro->AddNote(qudetail->FieldByName("supplierid")->AsInteger ,qudetail->FieldByName("id")->AsInteger );
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::edminChange(TObject *Sender)
{
	if (edmin->Text != "") {
		chbkinfo->Checked = true;
	}
	else if (edmax->Text != "") {
		chbkinfo->Checked = true;
	}
	else
	{
		chbkinfo->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::edlsminChange(TObject *Sender)
{
	if (edlsmin->Text != "") {
		chls->Checked = true;
	}
	else if (edlsmax->Text != "") {
		chls->Checked = true;
	}
	else
	{
		chls->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::edwsminChange(TObject *Sender)
{
	if (edwsmin->Text != "") {
		chws->Checked = true;
	}
	else if (edwsmax->Text != "") {
		chws->Checked = true;
	}
	else
	{
		chws->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::edpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r' && edpress->Text != "") {
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		AnsiString sql;
		sql = "select id,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + edpress->Text.Trim() + "%'" ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbpress->Clear();
		while (!aq->Eof )
		{
			cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aq->FieldByName("id")->AsInteger );
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::CheckBox1Click(TObject *Sender)
{
	if (CheckBox1->Checked ) {
		for (int i = 14; i <= maxlen; i++) {
			dgdetail->Columns->Items[i]->Visible = true;
		}
	}
	else
	{
		dgdetail->Columns->Items[14]->Visible = false;
		dgdetail->Columns->Items[15]->Visible = false;
		dgdetail->Columns->Items[16]->Visible = false;
		dgdetail->Columns->Items[17]->Visible = false;
		dgdetail->Columns->Items[18]->Visible = false;
		dgdetail->Columns->Items[19]->Visible = false;
		dgdetail->Columns->Items[20]->Visible = false;
		dgdetail->Columns->Items[21]->Visible = false;
		dgdetail->Columns->Items[22]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::N1Click(TObject *Sender)
{
	if (qudetail->IsEmpty() ) {
        return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,fcon,fstgid,qudetail->FieldByName("id")->AsInteger,fuserid);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbookup::edsupplierKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r' && edsupplier->Text != "") {
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		AnsiString sql;
		sql = "select id,name from CUST_CustomerInfo where name like '%" + edsupplier->Text.Trim() + "%' and type = 1 " ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbsupplier->Clear();
		while (!aq->Eof )
		{
			cbsupplier->AddItem(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq->FieldByName("id")->AsInteger );
		delete aq;
	}
}
//---------------------------------------------------------------------------

