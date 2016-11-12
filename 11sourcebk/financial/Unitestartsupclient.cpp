//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitestartsupclient.h"
#include "..\bsadmin\UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmsupplierandclient *frmsupplierandclient;
//---------------------------------------------------------------------------
__fastcall Tfrmsupplierandclient::Tfrmsupplierandclient(TComponent* Owner,TADOConnection *cn,int type)
	: TForm(Owner)
{
   	fcon = cn;
	TMenuItem *item1,*item2;
	Type = type;
	if (type==1) {
	   this->Caption = "供应商往来期初";
	   Label4->Caption = "供应商";
	   labeltitle->Caption = "供应商欠书店";
	   PopupMenu1->Items->Items[0]->Caption = "供应商欠书店";
	   PopupMenu1->Items->Items[1]->Caption = "书店欠供应商";
	   edtclient->Visible = false;
	   spselectClient->Visible = false;
	   dg->Columns->Items[1]->Title->Caption = "供应商名称";
	   dg->Columns->Items[2]->Title->Caption = "书店欠供应商";
	   dg->Columns->Items[3]->Title->Caption = "供应商欠书店";
	}else
	{
	   this->Caption = "客户往来期初";
	   Label4->Caption = "客户";
	   labeltitle->Caption = "客户欠书店";
	   PopupMenu1->Items->Items[0]->Caption = "客户欠书店";
	   PopupMenu1->Items->Items[1]->Caption = "书店欠客户";
	   cbselect->Visible = false;
	   dg->Columns->Items[1]->Title->Caption = "客户名称";
	   dg->Columns->Items[2]->Title->Caption = "书店欠客户";
	   dg->Columns->Items[3]->Title->Caption = "客户欠书店";
	}
	aquery->Connection = cn;
	ReadyData(type);
	TADOQuery * aq;
		String sql;
		aq = new TADOQuery(this);
		aq->Connection = cn;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add("select * from sys_bsset where name ='xiaoshudian'");
		aq->Open();
		storageformat =  "###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
		aq->Open();
		saleformat =  "###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
		delete aq;
}
void Tfrmsupplierandclient::ReadyData(int type)
{
	String sqlstr ;
	TColumn *Col;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	if (type == 1) {
		sqlstr = "select ID,Name from CUST_CustomerInfo where type = 1 and name <> '' order by name";
	}
	else
	{
		sqlstr = "select ID,Name from CUST_CustomerInfo where type in(2,3) order by name";
	}

	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sqlstr);
	aq->Open();
	while(!aq->Eof)
	{
		cbselect->AddObject(aq->FieldByName("name")->AsAnsiString , (TObject*)aq->FieldByName("ID")->AsInteger);
		aq->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsupplierandclient::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsupplierandclient::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsupplierandclient::editmoneyKeyPress(TObject *Sender, wchar_t &Key)
{
	float blance=0.00;
	float mon=0.00;
	String sqlstr;
	String sqlupdate;
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key==VK_RETURN) {
		if (aquery->IsEmpty() || aquery->FieldByName("ID")->AsAnsiString == "" || editmoney->Text == "" ) {
			return;
		}

		if (labeltitle->Tag == 0 ) {   //书店欠供应商
			if (aquery->FieldByName("BookstoreLessBusiness")->AsFloat > 0.00 ) {
				if (!MessageBoxA(0,"确定重新录入期初值？","提示",MB_ICONQUESTION||MB_YESNO) == 1)
				{
					return;
				}
			}
		}
		else if (labeltitle->Tag == 1) {      //供应商欠书店
			if (aquery->FieldByName("BusinessLessBookstore")->AsFloat > 0.00 ) {
				if (!MessageBoxA(0,"确定重新录入期初值？","提示",MB_ICONQUESTION||MB_YESNO) == 1)
				{
					return;
				}
			}
		}

		if (MessageBoxA(0,"确认修改期初值吗？","往来管理",MB_ICONQUESTION||MB_YESNO) == 1) {
			try {
				mon =  StrToFloat(editmoney->Text) ;
			} catch (...) {
				MessageBox(0,"请输入正确的期初金额！","提示" ,MB_OK);
				return;
			}
			if (labeltitle->Tag == 0 ) {   //书店欠供应商
				if (Type == 1) {
					sqlupdate = "update CUST_CustomerStartMoney set BookstoreLessBusiness = " + editmoney->Text +",Balance = BusinessLessBookstore - " + editmoney->Text + " where id = " + aquery->FieldByName("ID")->AsAnsiString;
				}
				else
				{
					sqlupdate = "update CUST_CustomerStartMoney set BookstoreLessBusiness = " + editmoney->Text +",Balance = " + editmoney->Text + " - BusinessLessBookstore where id = " + aquery->FieldByName("ID")->AsAnsiString;
				}
			}
			else if (labeltitle->Tag == 1) {      //供应商欠书店
				if (Type == 1) {
					sqlupdate = "update CUST_CustomerStartMoney set BusinessLessBookstore = " + editmoney->Text +",Balance = " + editmoney->Text + " - BookstoreLessBusiness where id = " + aquery->FieldByName("ID")->AsAnsiString;
				}
				else
				{
					sqlupdate = "update CUST_CustomerStartMoney set BusinessLessBookstore = " + editmoney->Text +",Balance = BookstoreLessBusiness - " + editmoney->Text + " where id = " + aquery->FieldByName("ID")->AsAnsiString;
				}
			}
			TADOQuery *aq = new TADOQuery(this);
			aq->Connection = fcon;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sqlupdate);
			aq->ExecSQL();
			delete aq;
			TLocateOptions Opts;
			Opts.Clear();
			Opts   <<   loPartialKey;
			String   str   = aquery->FieldByName("ID")->AsAnsiString;
			aquery->Active = false;
			aquery->Active = true;
			aquery->Locate("ID",str,Opts);
			edqichuyue->Text = FormatFloat("#,##0.00",aquery->FieldByName("Balance")->AsFloat );
			edityu->Text = FormatFloat("#,##0.00",aquery->FieldByName("totalyue")->AsFloat);
			((TFloatField *)aquery->FieldByName("Balance"))->DisplayFormat = "0.00";
			((TFloatField *)aquery->FieldByName("totalyue"))->DisplayFormat = "0.00";
			((TFloatField *)aquery->FieldByName("BusinessLessBookstore"))->DisplayFormat = "0.00";
			((TFloatField *)aquery->FieldByName("BookstoreLessBusiness"))->DisplayFormat = "0.00";
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsupplierandclient::labeltitleMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		PopupMenu1->Popup(pt.x,pt.y);
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsupplierandclient::N1Click(TObject *Sender)
{
	labeltitle->Caption = ((TMenuItem*)Sender)->Caption ;
	labeltitle->Tag = ((TMenuItem*)Sender)->Tag ;
	editmoney->Text = "0.00";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsupplierandclient::cbselectSelect(TObject *Sender)
{
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsupplierandclient::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
	if (Key ==VK_F4) {   //导出
		BtnExport->Click() ;
	}
	if (Shift.Contains(ssCtrl)&& Key ==70) {   //查询
		BtnView->Click() ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsupplierandclient::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsupplierandclient::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",0);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		cbselect->ItemIndex = cbselect->Items->IndexOfObject((TObject*)ClientID);
		ClientView();
		Query();
	}
	delete frm;
}
//---------------------------------------------------------------------------

void Tfrmsupplierandclient::ClientView()
{
	if (ClientID == -1) {
		return;
	}
	AnsiString sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	sql = "exec USP_BS_Client_View 0," + IntToStr(ClientID)  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edtclient->Text = aq->FieldByName("Name")->AsAnsiString ;
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsupplierandclient::edqueryKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		AnsiString sql;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection  = fcon ;
		if (Type == 1) {
			sql = "select ID,Name from CUST_CustomerInfo where type = 1 and Name like '%" + edquery->Text + "%' and name <> '' ";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			cbselect->Clear();
			while (!aq->Eof )
			{
				cbselect->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger );
				aq->Next();
			}
			aq->First();
			cbselect->ItemIndex = cbselect->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		}
		else
		{
			TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edquery->Text,0);
			if (mrOk == frm->ShowModal())
			{
				ClientID = frm->GetSelectID();
				cbselect->ItemIndex = cbselect->Items->IndexOfObject((TObject*)ClientID);
				ClientView();
				Query();
			}
			delete frm;
		}
		delete aq;
	}
}
//---------------------------------------------------------------------------

void Tfrmsupplierandclient::Query()
{
	AnsiString sql,sqlwhere;
	if (Type==1) {
		sql = " select distinct cast (rank() over(order by B.id) as nvarchar(10)) as xuhao, B.id,A.Name ,A.Telephone ,A.Contact ,A.Address ,B.BookstoreLessBusiness ,B.BusinessLessBookstore ,B.Balance,B.totalyue ";
		sqlwhere = " from  CUST_CustomerInfo A join CUST_CustomerStartMoney B on A.ID = B.customerID where A.Type=1  and A.Name <> '' ";
		if (cbselect->Text != "") {
			sqlwhere = sqlwhere + " and A.Name = '" + cbselect->Text.Trim() + "'";
		}
	}else if (Type == 2) {
		sql = " select distinct cast (rank() over(order by B.id) as nvarchar(10)) as xuhao, B.id,dbo.UF_BS_GetClientName(A.id) as Name ,A.Telephone  ,A.Contact ,A.Address ,B.BookstoreLessBusiness ,B.BusinessLessBookstore ,B.Balance,B.totalyue ";
		sqlwhere = " from  CUST_CustomerInfo A join CUST_CustomerStartMoney B on A.ID = B.customerID where A.Name <> '' and Type in(2,3) ";
		if (edtclient->Text != "") {
			sqlwhere = sqlwhere + " and A.id in (select id from dbo.GetChild(" + IntToStr(ClientID) + "))";
		}
	}
	sql = sql + sqlwhere + " union select '合计',999999999,null,null,null,null,sum(B.BookstoreLessBusiness),sum(B.BusinessLessBookstore),sum(B.Balance),sum(B.totalyue) " + sqlwhere + " order BY ID asc ";
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (Type == 1) {
		((TFloatField *)aquery->FieldByName("Balance"))->DisplayFormat = storageformat;
		((TFloatField *)aquery->FieldByName("totalyue"))->DisplayFormat = storageformat;
		((TFloatField *)aquery->FieldByName("BusinessLessBookstore"))->DisplayFormat = storageformat;
		((TFloatField *)aquery->FieldByName("BookstoreLessBusiness"))->DisplayFormat = storageformat;
	}
	else
	{
		((TFloatField *)aquery->FieldByName("Balance"))->DisplayFormat = saleformat;
		((TFloatField *)aquery->FieldByName("totalyue"))->DisplayFormat = saleformat;
		((TFloatField *)aquery->FieldByName("BusinessLessBookstore"))->DisplayFormat = saleformat;
		((TFloatField *)aquery->FieldByName("BookstoreLessBusiness"))->DisplayFormat = saleformat;
	}
	if (aquery->IsEmpty() ) {
		return;
	}
	edqichuyue->Text = FormatFloat("#,##0.00",aquery->FieldByName("Balance")->AsFloat );
	edityu->Text = FormatFloat("#,##0.00",aquery->FieldByName("totalyue")->AsFloat);
	editmoney->Text = "0.00";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsupplierandclient::BtnViewClick(TObject *Sender)
{
	Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsupplierandclient::dgCellClick(TColumn *Column)
{
	if (aquery->IsEmpty() ) {
		return;
	}
	edqichuyue->Text = FormatFloat("#,##0.00",aquery->FieldByName("Balance")->AsFloat );
	edityu->Text = FormatFloat("#,##0.00",aquery->FieldByName("totalyue")->AsFloat);
	editmoney->Text = "0.00";
}
//---------------------------------------------------------------------------
//Excel导出函数
bool Tfrmsupplierandclient::DbgridToExcel(TDBGrid* dbg)
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

	aquery->DisableControls();
	dbg->DataSource ->DataSet ->First();
	while(!dbg->DataSource ->DataSet->Eof)
	{
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "Telephone") {
					if (dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString != "") {
						temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
					else
					{
                    	temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "Address") {
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
	aquery->EnableControls();

	FileClose(iFileHandle);
	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmsupplierandclient::BtnExportClick(TObject *Sender)
{
	DbgridToExcel(dg);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsupplierandclient::dgDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
	if (dg->DataSource->DataSet->IsEmpty() ) {
    	return;
	}
	if (dg->DataSource->DataSet->FieldByName("xuhao")->AsAnsiString  == "合计" ) {
		dg->Canvas->FillRect(Rect);
		dg->Canvas->Font->Color  = clRed;
		dg->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}
//---------------------------------------------------------------------------

