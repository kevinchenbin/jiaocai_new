//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1caigouyuji.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma resource "*.dfm"
Tfrmcaigouyuji *frmcaigouyuji;
//---------------------------------------------------------------------------
__fastcall Tfrmcaigouyuji::Tfrmcaigouyuji(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
	con = cn;
	fstgid = stgid;
	TADOQuery *qu = new TADOQuery(this);
	qu->Connection = con;
	AnsiString sql;
	sql = "select ID,Name from CUST_CustomerInfo where Type = 1";
	qu->Close();
	qu->SQL->Clear();
	qu->SQL->Add(sql);
	qu->Open();
	while(!qu->Eof)
	{
		cbsupplier->AddItem(qu->FieldByName("Name")->AsAnsiString,(TObject*)qu->FieldByName("ID")->AsInteger );
		qu->Next();
	}
	delete qu;
	dtporderstart->Date = Date();
	dtporderend->Date = Date();
	dtpyjstart->Date = Date();
	dtpyjend->Date = Date();
	Query();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcaigouyuji::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key ==70) {
		BtnView->Click();
	}
	if (Key == VK_F4) {
		BtnExport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {
		WindowState = wsNormal;
	}
	if (Shift.Contains(ssCtrl)&& Key ==81) {
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78) {
		BtnAlignBottom->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouyuji::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouyuji::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouyuji::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------
void Tfrmcaigouyuji::Query()
{
	AnsiString sql;
	sql = "select distinct BS_ProcureNoteHeader.ProcureNtCode,dbo.UF_BS_GetClientName(BS_ProcureNoteHeader.SupplierID) as ClientName, convert(char(10),BS_ProcureNoteHeader.yujidate,120) as yujidate,convert(char(10),BS_ProcureNoteHeader.HdTime,120) as HdTime,BS_ProcureNote.*,"
			" BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.ISBN,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName "
			" from BS_ProcureNoteHeader left join BS_ProcureNote on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id "
			" left join BS_BookCatalog on BS_ProcureNote.BkcatalogID = BS_BookCatalog.id "
			" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
			" where BS_ProcureNoteHeader.StgID = " + IntToStr(fstgid) + " and BS_ProcureNoteHeader.state in (0,1) "
			" and BS_ProcureNote.UnrecAmount > 0 and datediff(day,BS_ProcureNoteHeader.yujidate,getdate()) > 0 ";
	if (chsupplier->Checked && cbsupplier->Text != "") {
		int supplierid;
		try {
			supplierid = (int)cbsupplier->Items->Objects[cbsupplier->ItemIndex];
		} catch (...) {
			return;
		}
		sql = sql + " and BS_ProcureNoteHeader.SupplierID = " + IntToStr(supplierid);
	}
	if (chday->Checked) {
		if (edminday->Text != "" && StrToInt(edminday->Text)  != 0) {
			sql = sql + " and datediff(day,BS_ProcureNoteHeader.yujidate,getdate()) >= " + edminday->Text;
		}
		if (edmaxday->Text != "" && StrToInt(edmaxday->Text)  != 0) {
			sql = sql + " and datediff(day,BS_ProcureNoteHeader.yujidate,getdate()) <= " + edmaxday->Text;
		}
	}
	if (chorderstart->Checked ) {
		sql = sql + " and datediff(day,'" + DateToStr(dtporderstart->Date) + "',BS_ProcureNoteHeader.HdTime) >= 0 ";
	}
	if (chorderend->Checked ) {
		sql = sql + " and datediff(day,'" + DateToStr(dtporderend->Date) + "',BS_ProcureNoteHeader.HdTime) <= 0 ";
	}
	if (chyujistart->Checked ) {
		sql = sql + " and datediff(day,'" + DateToStr(dtpyjstart->Date) + "',BS_ProcureNoteHeader.yujidate) >= 0 ";
	}
	if (chyjend->Checked ) {
		sql = sql + " and datediff(day,'" + DateToStr(dtpyjend->Date) + "',BS_ProcureNoteHeader.yujidate) <= 0 ";
	}
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouyuji::BtnViewClick(TObject *Sender)
{
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouyuji::edsupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        TADOQuery *qu = new TADOQuery(this);
		qu->Connection = con;
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where Type = 1 and Name like '%" + edsupplier->Text.Trim() + "%'" ;
		qu->Close();
		qu->SQL->Clear();
		qu->SQL->Add(sql);
		qu->Open();
		cbsupplier->Clear();
		while(!qu->Eof)
		{
			cbsupplier->AddItem(qu->FieldByName("Name")->AsAnsiString,(TObject*)qu->FieldByName("ID")->AsInteger );
			qu->Next();
		}
		qu->First();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)qu->FieldByName("ID")->AsInteger );
		delete qu;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouyuji::BtnExportClick(TObject *Sender)
{
	if (aq->IsEmpty() ) {
		return;
	}
	DbgridToExcel(DBGrid1);
}
//---------------------------------------------------------------------------
//Excel导出函数
bool  Tfrmcaigouyuji::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString temptext,path  ;

	savedlg->FileName = "采购超期未到货(" + DateToStr(Date()) + ")";
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
	int  iFileLength;
	if(FileExists(path))
	   //iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());


	temptext = "供应商,采购单号,ISBN,书名,定价,出版社,版次,采购数量,未到货数,采购日期,预计到货日期";
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	temptext = "\n";

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	while(!dbg->DataSource ->DataSet->Eof)
	{
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1 ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN" || dbg->Columns ->Items [j-1]->FieldName == "ProcureNtCode") {
					temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "Name") {
					AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					temptext = temptext + bookname + ",";
				}
				else
				{
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}

	dbg->DataSource ->DataSet->EnableControls();

	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouyuji::DBGrid1TitleClick(TColumn *Column)
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

