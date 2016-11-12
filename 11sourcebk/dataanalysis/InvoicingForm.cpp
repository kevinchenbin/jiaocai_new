//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "InvoicingForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TfrmInvoicing *frmInvoicing;
//---------------------------------------------------------------------------
__fastcall TfrmInvoicing::TfrmInvoicing(TComponent* Owner)
	: TfrmMDIChild(Owner)
{             m_module = MTData;
	dtp1->Date=dtp1->Date .CurrentDate();
	dtp2->Date=dtp2->Date .CurrentDate();
	this->WindowState = wsMaximized ;
}
//---------------------------------------------------------------------------

void TfrmInvoicing::Init(TApplication* app, TADOConnection* con)
{         TfrmMDIChild::Init(app, con);
		dsquery->Connection=con;
		storcquery->Connection = con;
		fcon = con;
		TADOQuery * aq;
		String sql;
		aq = new TADOQuery(this);
		aq->Connection = con;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add("select * from sys_bsset where name ='xiaoshudian'");
		aq->Open();
		storageformat =  "￥###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add("select * from sys_bsset where name ='retailxiaoshudian'");
		aq->Open();
		retaiformat =  "￥###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
		aq->Open();
		saleformat =  "￥###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
		sql = "select ID,Name from CUST_CustomerInfo where Type = 1 order by name";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while (!aq->Eof )
		{
			cbsupplier->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		sql = "select ID,PresentNum,AbbreviatedName from BS_PressInfo";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while (!aq->Eof )
		{
			cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		sql = "select ID,Name from BS_BookType";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while (!aq->Eof )
		{
			cbtype->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}

        sql = "select ID,Name from SYS_StorageInfo ";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while (!aq->Eof )
		{
			cbstorage->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)stgid);
		sql = "select Master from SYS_StorageInfo where id = " + IntToStr(stgid);
        aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->FieldByName("Master")->AsBoolean ) {
			chstorage->Enabled = true;
			cbstorage->Enabled = true;
		}
		else
		{
			chstorage->Enabled = false;
			cbstorage->Enabled = false;
		}

		delete aq;
		DBGridEh1->Columns->Items[3]->DisplayFormat = storageformat;
		DBGridEh1->Columns->Items[6]->DisplayFormat = storageformat;
		DBGridEh1->Columns->Items[7]->DisplayFormat = storageformat;

		DBGridEh1->Columns->Items[9]->DisplayFormat = retaiformat;
		DBGridEh1->Columns->Items[10]->DisplayFormat = retaiformat;
		DBGridEh1->Columns->Items[12]->DisplayFormat = retaiformat;
		DBGridEh1->Columns->Items[13]->DisplayFormat = retaiformat;

		DBGridEh1->Columns->Items[14]->DisplayFormat = saleformat;
		DBGridEh1->Columns->Items[15]->DisplayFormat = saleformat;
		DBGridEh1->Columns->Items[17]->DisplayFormat = saleformat;
		DBGridEh1->Columns->Items[18]->DisplayFormat = saleformat;

		DBGridEh1->Columns->Items[6]->Footer->DisplayFormat = storageformat;
		DBGridEh1->Columns->Items[7]->Footer->DisplayFormat = storageformat;

		DBGridEh1->Columns->Items[9]->Footer->DisplayFormat = retaiformat;
		DBGridEh1->Columns->Items[10]->Footer->DisplayFormat = retaiformat;
		DBGridEh1->Columns->Items[12]->Footer->DisplayFormat = retaiformat;
		DBGridEh1->Columns->Items[13]->Footer->DisplayFormat = retaiformat;

		DBGridEh1->Columns->Items[14]->Footer->DisplayFormat = saleformat;
		DBGridEh1->Columns->Items[15]->Footer->DisplayFormat = saleformat;
		DBGridEh1->Columns->Items[17]->Footer->DisplayFormat = saleformat;
		DBGridEh1->Columns->Items[18]->Footer->DisplayFormat = saleformat;
}

void __fastcall TfrmInvoicing::RzToolButton1Click(TObject *Sender)
{
				Sender1=Sender;
				storcquery->Close();

				//storcquery->Active = false;
					OleVariant value;
				value  = NULL;

				storcquery->Parameters->Clear();
				storcquery->Parameters->CreateParameter("@starttime",ftDateTime,pdInput,20,NULL);
				storcquery->Parameters->CreateParameter("@endtime",ftDateTime,pdInput,20,NULL);
				storcquery->Parameters->CreateParameter("@ISBN",ftString,pdInput,20,NULL);
				storcquery->Parameters->CreateParameter("@BookName",ftString,pdInput,50,NULL);
				storcquery->Parameters->CreateParameter("@SupplyName",ftString,pdInput,50,NULL);
				storcquery->Parameters->CreateParameter("@PressName",ftString,pdInput,20,NULL);
				storcquery->Parameters->CreateParameter("@UserDefCode",ftString,pdInput,50,NULL);
				storcquery->Parameters->CreateParameter("@Type",ftString,pdInput,50,NULL);
				storcquery->Parameters->CreateParameter("@stgid",ftInteger,pdInput,50,-1);


				storcquery->Parameters->ParamByName("@starttime")->Value = "1901-1-1 0:00:00";
				storcquery->Parameters->ParamByName("@endtime")->Value = "2200-1-1 23:59:59" ;
			   if (cbstart->Checked && !cbend->Checked ) {
				   storcquery->Parameters->ParamByName("@starttime")->Value = DateToStr(dtp1->Date).Trim() + " 0:00:00";
			   }
			   if (!cbstart->Checked && cbend->Checked ) {
				   storcquery->Parameters->ParamByName("@endtime")->Value = DateToStr(dtp2->Date).Trim() + " 23:59:59";
			   }
			   if (cbstart->Checked && cbend->Checked ) {
					storcquery->Parameters->ParamByName("@starttime")->Value = dtp1->Date ;
					storcquery->Parameters->ParamByName("@endtime")->Value = dtp2->Date;
				}
				 if (chk1->Checked==true&&RzEdtInfor->Text!="") {
					storcquery->Parameters->ParamByName("@ISBN")->Value = "%" + RzEdtInfor->Text.Trim()  + "%";
				 }

				else
				 {
					storcquery->Parameters->ParamByName("@ISBN")->Value = "";
				 }


				 if (chk6->Checked==true&&RzEdit5->Text!="") {  //书名
					storcquery->Parameters->ParamByName("@BookName")->Value =  "%" + RzEdit5->Text.Trim()  + "%";
				 }
				else
				 {
					storcquery->Parameters->ParamByName("@BookName")->Value =  "";
				 }


				 if (chk4->Checked==true&&cbsupplier->Text!="") {   //供应商
					storcquery->Parameters->ParamByName("@SupplyName")->Value = "%" +cbsupplier->Text.Trim()  + "%";
				 }
				 else
				 {
					storcquery->Parameters->ParamByName("@SupplyName")->Value ="";
				 }

				 if (chk5->Checked==true&&cbpress->Text!="") {  //出版社
					storcquery->Parameters->ParamByName("@PressName")->Value = cbpress->Text.Trim()   ;
				 }
				else
				 {
					storcquery->Parameters->ParamByName("@PressName")->Value = "";

				 }

				 if (chk2->Checked==true&&RzEdit2->Text!="") {  //自编码
					storcquery->Parameters->ParamByName("@UserDefCode")->Value = "%" + RzEdit2->Text.Trim()  + "%";
				 }
				else
				 {
					storcquery->Parameters->ParamByName("@UserDefCode")->Value = "";
				 }

				 if (chtype->Checked==true&&cbtype->Text!="") { //类别
					storcquery->Parameters->ParamByName("@Type")->Value =  cbtype->Text.Trim()  ;
				 }
				 else
				 {
					storcquery->Parameters->ParamByName("@Type")->Value = "";
				 }

				if (chstorage->Checked) {
					int fstgid;
					try {
						fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"请选择正确的店号!","提示",MB_ICONEXCLAMATION);
						return;
					}
					storcquery->Parameters->ParamByName("@stgid")->Value = fstgid ;
				}
				 ds1->DataSet = NULL;
				 dsquery->AfterScroll = NULL;
				 //storcquery->Parameters->ParamByName("@Type")->
			   //	storcquery->ExecProc();
				 //storcquery->Active = true;
				storcquery->Open();
				 dsquery->Recordset = storcquery->Recordset ;
				 ds1->DataSet = dsquery;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::cbbTypeSelect(TObject *Sender)
{
	  RzEdtInfor->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::RzEdtInforKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        RzEdit5->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::FormClose(TObject *Sender, TCloseAction &Action)
{
 	dsquery->Active=false;
	 Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::RzToolButton3Click(TObject *Sender)
{
	      Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		RzToolButton1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		RzToolButton3->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
	if (Key == VK_F4) {   //恢复窗口
		BtnExport->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::DBGridEh1TitleClick(TColumnEh *Column)
{
	if (dsquery->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsquery->Sort == "") {
		dsquery->Sort =  Column->FieldName + " ASC";
	}
	else if (dsquery->Sort == qusort) {
		dsquery->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsquery->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::ch1Click(TObject *Sender)
{
	if (ch1->Checked ) {
		DBGridEh1->Columns->Items[6]->Visible = true;
		DBGridEh1->Columns->Items[7]->Visible = true;
		DBGridEh1->Columns->Items[8]->Visible = true;
	}
	else
	{
		DBGridEh1->Columns->Items[6]->Visible = false;
		DBGridEh1->Columns->Items[7]->Visible = false;
		DBGridEh1->Columns->Items[8]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::ch2Click(TObject *Sender)
{
	if (ch2->Checked ) {
		DBGridEh1->Columns->Items[9]->Visible = true;
		DBGridEh1->Columns->Items[10]->Visible = true;
		DBGridEh1->Columns->Items[11]->Visible = true;
		DBGridEh1->Columns->Items[12]->Visible = true;
		DBGridEh1->Columns->Items[13]->Visible = true;
	}
	else
	{
		DBGridEh1->Columns->Items[9]->Visible = false;
		DBGridEh1->Columns->Items[10]->Visible = false;
		DBGridEh1->Columns->Items[11]->Visible = false;
		DBGridEh1->Columns->Items[12]->Visible = false;
		DBGridEh1->Columns->Items[13]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::ch3Click(TObject *Sender)
{
	if (ch3->Checked ) {
		DBGridEh1->Columns->Items[14]->Visible = true;
		DBGridEh1->Columns->Items[15]->Visible = true;
		DBGridEh1->Columns->Items[16]->Visible = true;
		DBGridEh1->Columns->Items[17]->Visible = true;
		DBGridEh1->Columns->Items[18]->Visible = true;
	}
	else
	{
		DBGridEh1->Columns->Items[14]->Visible = false;
		DBGridEh1->Columns->Items[15]->Visible = false;
		DBGridEh1->Columns->Items[16]->Visible = false;
		DBGridEh1->Columns->Items[17]->Visible = false;
		DBGridEh1->Columns->Items[18]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::BtnExportClick(TObject *Sender)
{
	if (dsquery->IsEmpty() ) {
		return;
	}
	DbgridToExcel(DBGridEh1);
}
//---------------------------------------------------------------------------
//Excel导出函数
bool TfrmInvoicing::DbgridToExcel(TDBGridEh* dbg)
{
	if (dbg->DataSource ->DataSet->IsEmpty() ) {
        return false;
	}
	AnsiString temptext,path;

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
	int  iFileLength;
	if(FileExists(path))
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
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
				else if (dbg->Columns ->Items [j-1]->FieldName == "BookName") {
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
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();

	temptext = "\n";
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			temptext = temptext + dbg->Columns ->Items[q]->Footer->Value + ",";
		}
	}
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::edsupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edsupplier->Text == "") {
            return;
		}
		TADOQuery * aq = new TADOQuery(this);
		String sql;
		aq->Connection =fcon;

		sql = "select ID,Name from CUST_CustomerInfo where Type = 1 and Name like '%" + edsupplier->Text.Trim() + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbsupplier->Items->Clear();
		while (!aq->Eof )
		{
			cbsupplier->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
		cbsupplier->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::edtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edtype->Text == "") {
            return;
		}
		TADOQuery * aq = new TADOQuery(this);
		String sql;
		aq->Connection =fcon;

		sql = "select ID,Name from BS_BookType where Name like '%" + edtype->Text.Trim() + "%'" ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while (!aq->Eof )
		{
			cbtype->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
        aq->First();
		cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
		cbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::edpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edpress->Text == "") {
            return;
		}
		TADOQuery * aq = new TADOQuery(this);
		String sql;
		aq->Connection =fcon;

		sql = "select ID,PresentNum,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + edpress->Text.Trim() + "%'" ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while (!aq->Eof )
		{
			cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
        aq->First();
		cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
		cbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::dtp1Change(TObject *Sender)
{
	cbstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::dtp1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        dtp2->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::dtp2Change(TObject *Sender)
{
	cbend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::dtp2KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        RzEdit2->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::RzEdit2Change(TObject *Sender)
{
	if (RzEdit2->Text != "") {
		chk2->Checked = true;
	}
	else
	{
    	chk2->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::RzEdtInforChange(TObject *Sender)
{
	if (RzEdtInfor->Text != "") {
		chk1->Checked = true;
	}
	else
	{
    	chk1->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::RzEdit5Change(TObject *Sender)
{
	if (RzEdit5->Text != "") {
		chk6->Checked = true;
	}
	else
	{
    	chk6->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::RzEdit5KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edsupplier->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::cbsupplierChange(TObject *Sender)
{
	if (cbsupplier->Text != "") {
		chk4->Checked = true;
	}
	else
	{
    	chk4->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::cbsupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::cbtypeChange(TObject *Sender)
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

void __fastcall TfrmInvoicing::cbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::cbpressChange(TObject *Sender)
{
	if (cbpress->Text != "") {
		chk5->Checked = true;
	}
	else
	{
    	chk5->Checked =- false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmInvoicing::cbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        RzToolButton1->Click();
	}
}
//---------------------------------------------------------------------------

