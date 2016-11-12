//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Stockanalysis.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
Tfrmstockanalysis *frmstockanalysis;
//---------------------------------------------------------------------------
__fastcall Tfrmstockanalysis::Tfrmstockanalysis(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
  fcon = cn;
  aq->Connection = cn;
  dtpstart->Date = Date();
  dtpend->Date = Date();
  fstgid = stgid;
  ReadyData();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmstockanalysis::FormClose(TObject *Sender, TCloseAction &Action)

{
  Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::BtnExitClick(TObject *Sender)
{
  Close();
}
void Tfrmstockanalysis::ReadyData()
{
	TADOQuery * query = new TADOQuery(this);
	query->Connection = fcon;
	String sql ;
	sql = "select ID,Name from CUST_CustomerInfo where type = 1";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof )
	{
		cbsupplier->AddItem(query->FieldByName("ID")->AsString + query->FieldByName("Name")->AsString ,(TObject*)query->FieldByName("ID")->AsInteger );
		query->Next();
	}
	sql = "select ID,Name from BS_BookType";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof )
	{
		cbtype->AddItem(query->FieldByName("ID")->AsString + query->FieldByName("Name")->AsString ,(TObject*)query->FieldByName("ID")->AsInteger );
		query->Next();
	}
	sql = "select ID,Name from STK_BookstackInfo where StgID = " + IntToStr(fstgid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof )
	{
		cbstact->AddItem(query->FieldByName("ID")->AsString + query->FieldByName("Name")->AsString ,(TObject*)query->FieldByName("ID")->AsInteger );
		query->Next();
  	}

	sql = "select ID,Name  from SYS_StorageInfo";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof)
	{
		cbstorage->AddItem(query->FieldByName("Name")->AsString,(TObject*)query->FieldByName("ID")->AsInteger);
		query->Next();
	}
	cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)fstgid);
	sql = "select Master from SYS_StorageInfo where id = " + IntToStr(fstgid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("Master")->AsBoolean ) {
		cbstorage->Enabled = true;
		chstorage->Enabled = true;
	}
	else
	{
		cbstorage->Enabled = false;
		chstorage->Enabled = false;
	}

	delete query;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmstockanalysis::BtnPrintPreviewClick(TObject *Sender)
{
	String  wherestr;
	wherestr = " where 1 = 1";

	if (cbstart->Checked) {
		wherestr = wherestr + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',B.Hdtime ) >= 0 " ;
	}
	if (cbend->Checked) {
		wherestr = wherestr + " and datediff(day,'" + DateToStr(dtpend->Date) + "',B.Hdtime ) >= 0 " ;
	}


	if (chstorage->Checked ) {
		int ffstgid;
		try {
			ffstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
		} catch (...) {
			MessageBox(0,"请选择正确的店号!","提示",MB_ICONEXCLAMATION);
			return;
		}
		wherestr = wherestr + " and B.StgID = " + IntToStr(ffstgid);
   	}

	TypeQuery(wherestr);
}
//---------------------------------------------------------------------------
void Tfrmstockanalysis::TypeQuery(String wherestr)
{
   String sql;
   String sqlsum;
   sqlsum = "select sum(A.amount) as d from stk_bookinfo A left join STK_BookstackInfo F ON A.BkstackID = F.id "
			" where A.ID not in(  select distinct(bkinfoid) "
			" as bkinfoid from bs_retailnote A  inner join bs_retailnoteheader B on A.retailntheaderid = B.ID " ;
   sqlsum = sqlsum + wherestr;
   sqlsum = sqlsum + " union ";
   sqlsum = sqlsum + " select distinct(bkinfoid) as bkinfoid from bs_wsalenote A inner join bs_wsalenoteheader B  on A.WsaleNtHeaderID = B.ID " ;
   sqlsum  = sqlsum + wherestr + ")" ;

   if (chstorage->Checked ) {
		int ffstgid;
		try {
			ffstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
		} catch (...) {
			MessageBox(0,"请选择正确的店号!","提示",MB_ICONEXCLAMATION);
			return;
		}
		sqlsum = sqlsum + " and F.StgID = " + IntToStr(ffstgid);
   }


   sqlsum = "select sum(A.amount) as d,sum(A.amount*A.Cbprice) as s,sum(A.amount*B.price) as m from stk_bookinfo A "
		 " inner join bs_bookcatalog B On A.bkcatalogID = B.ID "
		 " left join bs_pressinfo C On B.PressID = C.ID "
		 " left join cust_customerinfo D on A.supplierid = D.ID "
		 " left join BS_booktype E on B.smallBooktypeid = E.id "
		 " left join STK_BookstackInfo F ON A.BkstackID = F.id "
		 " left join SYS_StorageInfo G ON F.StgID = G.id "
		 " where A.ID not in( "
		 " select distinct(bkinfoid) as bkinfoid from bs_retailnote A "
		 " inner join bs_retailnoteheader B on A.retailntheaderid = B.ID " ;
   sqlsum = sqlsum + wherestr ;
   sqlsum = sqlsum + "  union "
		 "  select distinct(bkinfoid) as bkinfoid from bs_wsalenote A inner join bs_wsalenoteheader B "
		 "  on A.WsaleNtHeaderID = B.ID ";
   sqlsum = sqlsum + wherestr + ")" ;
   if (chisbn->Checked && edbook->Text != "") {
		sqlsum = sqlsum + " and B.Barcode like '%" + edbook->Text.Trim() + "%'";
   }
   if (chname->Checked && edname->Text != "") {
		sqlsum = sqlsum + " and B.Name like '%" + edname->Text.Trim() + "%'";
   }
   if (chsupplier->Checked && cbsupplier->Text != "") {
		try {
			sqlsum = sqlsum + " and A.supplierid = " + IntToStr((int)cbsupplier->Items->Objects[cbsupplier->ItemIndex]);
		} catch (...) {
        	return;
		}
   }
   if (chtype->Checked && cbtype->Text != "") {
		try {
			sqlsum = sqlsum + " and B.smallBookTypeID = " + IntToStr((int)cbtype->Items->Objects[cbtype->ItemIndex]);
		} catch (...) {
			return;
		}
   }
   if (chstack->Checked && cbstact->Text != "") {
		try {
			sqlsum = sqlsum + " and A.BkstackID = " + IntToStr((int)cbstact->Items->Objects[cbstact->ItemIndex]);
		} catch (...) {
			return;
		}
   }
   if (chstorage->Checked ) {
		int ffstgid;
		try {
			ffstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
		} catch (...) {
			MessageBox(0,"请选择正确的店号!","提示",MB_ICONEXCLAMATION);
			return;
		}
		sqlsum = sqlsum + " and F.StgID = " + IntToStr(ffstgid);
   }

   TADOQuery *aquery = new TADOQuery(Application);
   aquery->Connection = fcon ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sqlsum);
   aquery->Open();

   sql = "select rank() over(order by A.id asc ) as xuhao,A.ID,D.Name Name1 ,B.ISBN ,B.Name Name2 ,B.presscount,B.price bookprice ,E.name Name3,C.Abbreviatedname ,A.amount,G.Name as storagename from stk_bookinfo A "
		 " inner join bs_bookcatalog B On A.bkcatalogID = B.ID "
		 " left join bs_pressinfo C On B.PressID = C.ID "
		 " left join cust_customerinfo D on A.supplierid = D.ID "
		 " left join BS_booktype E on B.smallBooktypeid = E.id "
		 " left join STK_BookstackInfo F ON A.BkstackID = F.id "
		 " left join SYS_StorageInfo G ON F.StgID = G.id "
		 " where A.ID not in( "
		 " select distinct(bkinfoid) as bkinfoid from bs_retailnote A "
		 " inner join bs_retailnoteheader B on A.retailntheaderid = B.ID " ;
   sql = sql + wherestr ;
   sql = sql + "  union "
		 "  select distinct(bkinfoid) as bkinfoid from bs_wsalenote A inner join bs_wsalenoteheader B "
		 "  on A.WsaleNtHeaderID = B.ID ";
   sql = sql + wherestr + ")" ;
   if (chisbn->Checked && edbook->Text != "") {
		sql = sql + " and B.Barcode like '%" + edbook->Text.Trim() + "%'";
   }
   if (chname->Checked && edname->Text != "") {
		sql = sql + " and B.Name like '%" + edname->Text.Trim() + "%'";
   }
   if (chsupplier->Checked && cbsupplier->Text != "") {
		try {
			sql = sql + " and A.supplierid = " + IntToStr((int)cbsupplier->Items->Objects[cbsupplier->ItemIndex]);
		} catch (...) {
        	return;
		}
   }
   if (chtype->Checked && cbtype->Text != "") {
		try {
			sql = sql + " and B.smallBookTypeID = " + IntToStr((int)cbtype->Items->Objects[cbtype->ItemIndex]);
		} catch (...) {
			return;
		}
   }
   if (chstack->Checked && cbstact->Text != "") {
		try {
			sql = sql + " and A.BkstackID = " + IntToStr((int)cbstact->Items->Objects[cbstact->ItemIndex]);
		} catch (...) {
			return;
		}
   }
   if (chstorage->Checked ) {
		int ffstgid;
		try {
			ffstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
		} catch (...) {
			MessageBox(0,"请选择正确的店号!","提示",MB_ICONEXCLAMATION);
			return;
		}
		sql = sql + " and F.StgID = " + IntToStr(ffstgid);
   }

   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   ((TFloatField *)aq->FieldByName("bookprice"))->DisplayFormat = "0.00";
   edittotal->Text  = FormatFloat("###,###,##0",aquery->FieldByName("d")->AsInteger);
   edtotalmayang->Text  = FormatFloat("###,###,##0.00",aquery->FieldByName("m")->AsFloat);
   edtotalshiyang->Text  = FormatFloat("###,###,##0.00",aquery->FieldByName("s")->AsFloat);
   delete aquery;
}
//---------------------------------------------------------------------------
void Tfrmstockanalysis::dgcolumn(TADOQuery *aq,TRzDBGrid * dg)
{
	TColumn *Col;
	dg->Columns->Clear();

	for (int i = 1; i < aq->Fields->Count ; i++) { //去悼ID
		Col =  dg->Columns->Add();
		Col->FieldName  = aq->Fields->Fields[i]->FieldName  ;
		Col->Width = 80;
		aq->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::BtnExportClick(TObject *Sender)
{
	if (aq->IsEmpty() ) {
		return;
	}
	DbgridToExcel(dg);
}
//---------------------------------------------------------------------------

//Excel导出函数
bool Tfrmstockanalysis::DbgridToExcel(TRzDBGrid* dbg)
{
	if (dbg->DataSource ->DataSet->IsEmpty() ) {
        return false;
	}
	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	savedlg->FileName = this->Caption;
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(savedlg->FileName .c_str()  );
		Name = ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
	else
	{
		return false;
	}
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	dbg->DataSource ->DataSet->DisableControls();
	dbg->DataSource ->DataSet ->First();
	while(!dbg->DataSource ->DataSet->Eof)
	{
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					if (dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString != "") {
						temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
					else
					{
                    	temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "Name2") {
					AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					temptext = temptext + bookname + ",";
				}
				else
				{
                	t1++;
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::dgTitleClick(TColumn *Column)
{
	if (aq->IsEmpty() ) {
        return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aq->Sort == "") {
		aq->Sort =  Column->FieldName + " ASC";
	}
	else if (aq->Sort == qusort) {
		aq->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aq->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmstockanalysis::cbsupplierKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
        cbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::cbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        cbstart->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::cbstartKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
        dtpstart->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::dtpstartKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
        cbend->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::cbendKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        dtpend->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::dtpendKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        cbstorage->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::cbstactKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
    	BtnPrintPreview->Click();
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmstockanalysis::BtnAlignBottomClick(TObject *Sender)
{
WindowState = wsMinimized   ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
		if (Key == VK_F1) {
		 BtnPrintPreview->Click();
	   }
			if (Key == VK_F10) {
		 BtnPrint->Click();
	   }

		if (Shift.Contains(ssCtrl)&& Key ==90) {
			WindowState = wsNormal  ;
		}
		if (Shift.Contains(ssCtrl)&& Key ==81  ) {
			BtnExit->Click();
		}
		if (Shift.Contains(ssCtrl)&& Key == 78 ) {
		  BtnAlignBottom->Click();
		}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::cbstorageSelect(TObject *Sender)
{
	TADOQuery * query = new TADOQuery(this);
	query->Connection = fcon;
	String sql ;
	int ffstgid;
	try {
		ffstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	} catch (...) {
		MessageBox(0,"请选择正确的店号!","提示",MB_ICONEXCLAMATION);
		return;
	}
	sql = "select ID,Name from STK_BookstackInfo where StgID = " + IntToStr(ffstgid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	cbstact->Items->Clear();
	while (!query->Eof )
	{
		cbstact->AddItem(query->FieldByName("ID")->AsString + query->FieldByName("Name")->AsString ,(TObject*)query->FieldByName("ID")->AsInteger );
		query->Next();
	}
	delete query;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::ednameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        cbsupplier->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmstockanalysis::edbookKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::edbookChange(TObject *Sender)
{
	if (edbook->Text != "") {
		chisbn->Checked = true;
	}
	else
	{
		chisbn->Checked = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::ednameChange(TObject *Sender)
{
	if (edname->Text != "") {
		chname->Checked = true;
	}
	else
	{
    	chname->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::cbsupplierChange(TObject *Sender)
{
	if (cbsupplier->Text != "") {
		chsupplier->Checked = true;
	}
	else
	{
    	chsupplier->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::cbtypeChange(TObject *Sender)
{
	if (cbtype->Text != "") {
		chtype->Checked = true;
	}
	else
	{
    	chtype->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::dtpstartChange(TObject *Sender)
{
	cbstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::dtpendChange(TObject *Sender)
{
	cbend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::cbstactChange(TObject *Sender)
{
	if (cbstact->Text != "") {
		chstack->Checked = true;
	}
	else
	{
    	chstack->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockanalysis::FormShow(TObject *Sender)
{
	edbook->SetFocus();
}
//---------------------------------------------------------------------------

