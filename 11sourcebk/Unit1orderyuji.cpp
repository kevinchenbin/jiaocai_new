//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1orderyuji.h"
#include "UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzEdit"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmorderyuji *frmorderyuji;
//---------------------------------------------------------------------------
__fastcall Tfrmorderyuji::Tfrmorderyuji(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
	con = cn;
	fstgid = stgid;
	ClientID = -1;
	dtporderstart->Date = Date();
	dtporderend->Date = Date();
	dtpyjstart->Date = Date();
	dtpyjend->Date = Date();
	Query();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderyuji::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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

void __fastcall Tfrmorderyuji::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderyuji::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderyuji::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderyuji::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,con,"",fstgid);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		ClientView();
	}
    delete frm;
}
//---------------------------------------------------------------------------
void Tfrmorderyuji::ClientView()
{
		if (ClientID == -1) {
			return;
		}
		String sql;
		TADOQuery * aq = new TADOQuery(NULL);
		aq->Connection = con;
	    sql = "exec USP_BS_Client_View 0," + IntToStr(ClientID)  ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		edtclient->Text = aq->FieldByName("Name")->AsAnsiString ;
		delete aq;
}
//---------------------------------------------------------------------------
void Tfrmorderyuji::Query()
{
	AnsiString sql;
	sql = "select distinct BS_OrderNoteHeader.OrderNtCode,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as ClientName, convert(char(10),BS_OrderNoteHeader.arravaldate,120) as arravaldate,convert(char(10),BS_OrderNoteHeader.HdTime,120) as HdTime,BS_OrderNote.*,"
			" BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.ISBN,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName "
			" from BS_OrderNoteHeader left join BS_OrderNote on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" left join BS_BookCatalog on BS_OrderNote.BkcatalogID = BS_BookCatalog.id "
			" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
			" where StgID = " + IntToStr(fstgid) + " and BS_OrderNoteHeader.state in (0,1) and BS_OrderNoteHeader.shenheistate = 1 "
			" and BS_OrderNote.UnsendAmount > 0 and  datediff(day,BS_OrderNoteHeader.arravaldate,getdate()) > 0 ";
	if (chclient->Checked && edtclient->Text != "") {
		sql = sql + " and BS_OrderNoteHeader.VendorID in (select id from dbo.GetChild(" + IntToStr(ClientID) + ")) ";
	}
	if (chday->Checked) {
		if (edminday->Text != "" && StrToInt(edminday->Text)  != 0) {
			sql = sql + " and datediff(day,BS_OrderNoteHeader.arravaldate,getdate()) >= " + edminday->Text;
		}
		if (edmaxday->Text != "" && StrToInt(edmaxday->Text)  != 0) {
			sql = sql + " and datediff(day,BS_OrderNoteHeader.arravaldate,getdate()) <= " + edmaxday->Text;
		}
	}
	if (chorderstart->Checked ) {
		sql = sql + " and datediff(day,'" + DateToStr(dtporderstart->Date) + "',BS_OrderNoteHeader.HdTime) >= 0 ";
	}
	if (chorderend->Checked ) {
		sql = sql + " and datediff(day,'" + DateToStr(dtporderend->Date) + "',BS_OrderNoteHeader.HdTime) <= 0 ";
	}
	if (chyujistart->Checked ) {
		sql = sql + " and datediff(day,'" + DateToStr(dtpyjstart->Date) + "',BS_OrderNoteHeader.arravaldate) >= 0 ";
	}
	if (chyjend->Checked ) {
		sql = sql + " and datediff(day,'" + DateToStr(dtpyjend->Date) + "',BS_OrderNoteHeader.arravaldate) <= 0 ";
	}
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderyuji::BtnViewClick(TObject *Sender)
{
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderyuji::edtQryVendorKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		TfrmselectClient * frm = new TfrmselectClient(Application,con,edtQryVendor->Text,fstgid);
		if (mrOk == frm->ShowModal())
		{
			ClientID = frm->GetSelectID();
			ClientView();
		}
	   delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderyuji::BtnExportClick(TObject *Sender)
{
	if (aq->IsEmpty() ) {
		return;
	}
	DbgridToExcel(DBGrid1);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//Excel导出函数
bool  Tfrmorderyuji::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString temptext,path  ;

	savedlg->FileName = "订单超期未发货(" + DateToStr(Date()) + ")";
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


	temptext = "客户,订单号,ISBN,书名,定价,出版社,版次,订货数量,未发货数,锁定数量,订货日期,预计发货日期";
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
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN" || dbg->Columns ->Items [j-1]->FieldName == "OrderNtCode") {
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

void __fastcall Tfrmorderyuji::DBGrid1TitleClick(TColumn *Column)
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

