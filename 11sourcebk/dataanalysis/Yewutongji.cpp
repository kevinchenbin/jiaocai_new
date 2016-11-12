//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Yewutongji.h"
#include "..\bsadmin\UnitSelectClient.h"
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
Tfrmywtongji *frmywtongji;
//---------------------------------------------------------------------------
__fastcall Tfrmywtongji::Tfrmywtongji(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	m_module = MTData;
	dtp1->Date=dtp1->Date .CurrentDate();
	dtp2->Date=dtp2->Date .CurrentDate();
	this->WindowState = wsMaximized ;
}
//---------------------------------------------------------------------------

void Tfrmywtongji::Init(TApplication* app, TADOConnection* con)
{
	TfrmMDIChild::Init(app, con);
	query->Connection = con;
	fcon = con;
	TADOQuery * aq;
	AnsiString sql;
	aq = new TADOQuery(this);
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add("select * from sys_bsset where name ='xiaoshudian'");
	aq->Open();
	storageformat =  "��###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add("select * from sys_bsset where name ='retailxiaoshudian'");
	aq->Open();
	retaiformat =  "��###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
	aq->Open();
	saleformat =  "��###,###,##" + aq->FieldByName("bk")->AsAnsiString ;
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
}
//---------------------------------------------------------------------------
void __fastcall Tfrmywtongji::FormClose(TObject *Sender, TCloseAction &Action)
{
	query->Active=false;
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::RzToolButton3Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		RzToolButton3->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
	if (Key == VK_F4) {   //�ָ�����
		BtnExport->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::DBGridEh1TitleClick(TColumnEh *Column)
{
	if (query->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (query->Sort == "") {
		query->Sort =  Column->FieldName + " ASC";
	}
	else if (query->Sort == qusort) {
		query->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		query->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::BtnExportClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	DbgridToExcel(DBGridEh1);
}
//---------------------------------------------------------------------------
//Excel��������
bool Tfrmywtongji::DbgridToExcel(TDBGridEh* dbg)
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

	MessageBox(0,"������ϣ�","��ʾ" ,MB_OK);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::edsupplierKeyPress(TObject *Sender, wchar_t &Key)
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

void __fastcall Tfrmywtongji::edtypeKeyPress(TObject *Sender, wchar_t &Key)
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

void __fastcall Tfrmywtongji::edpressKeyPress(TObject *Sender, wchar_t &Key)
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

void __fastcall Tfrmywtongji::dtp1Change(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::dtp1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        dtp2->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::dtp2Change(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::RzEdit5KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edsupplier->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::cbsupplierChange(TObject *Sender)
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

void __fastcall Tfrmywtongji::cbsupplierKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::cbtypeChange(TObject *Sender)
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

void __fastcall Tfrmywtongji::cbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::cbpressChange(TObject *Sender)
{
	if (cbpress->Text != "") {
		chpress->Checked = true;
	}
	else
	{
		chpress->Checked =- false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edclient->Text);
		if (mrOk == frm->ShowModal())
		{
			ClientID = frm->GetSelectID();
			ClientView();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"");
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		ClientView();
	}
	delete frm;
}
//---------------------------------------------------------------------------
void Tfrmywtongji::ClientView()
{
	if (ClientID == -1) {
		return;
	}
	String sql;
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

void Tfrmywtongji::Query(int modle)
{
	AnsiString sql,sqltime = "",sqlwhere = " where 1 = 1 ",sqlgroup = "",sqlhaving = "",sqltmp = "",sqladd = "";
	int type,pressid,supplierid;
	if (chstart->Checked) {
		sqltime = " and datediff(day,'" + DateToStr(dtp1->Date) + "',HdTime) >= 0";
	}
	if (chend->Checked ) {
		sqltime = sqltime + " and datediff(day,'" + DateToStr(dtp2->Date) + "',HdTime) <= 0";
	}

	if (chtype->Checked && cbtype->Text != "") {
    	try {
			type = (int)cbtype->Items->Objects[cbtype->ItemIndex];
			sqladd = sqladd + " and BS_BookCatalog.smallBookTypeID = " + IntToStr(type) ;
		} catch (...) {
			MessageBox(0,"��ѡ����ȷ�����","��ʾ" ,MB_OK);
		}
	}
	if (chpress->Checked && cbpress->Text != "") {
    	try {
			pressid = (int)cbpress->Items->Objects[cbpress->ItemIndex];
			sqladd = sqladd + " and BS_BookCatalog.PressID = " + IntToStr(pressid) ;
		} catch (...) {
			MessageBox(0,"��ѡ����ȷ�İ��","��ʾ" ,MB_OK);
		}
	}
	switch (rg1->ItemIndex ) {
		case 0:   //����
			if (chclient->Checked && edtclient->Text != "") {
				sqlwhere = sqlwhere + " and BS_OrderNoteHeader.VendorID in (select id from dbo.getchild(" + IntToStr(ClientID) + "))";
			}
			if (modle == 0) {   //�������
				sql = "select BkcatalogID,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,sum(BS_OrderNote.Amount) as ����,sum(BS_OrderNote.FixedPrice) as ����,SUM(BS_OrderNote.DiscountedPrice) as ʵ�� from BS_OrderNote "
						" left join BS_BookCatalog on BS_OrderNote.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id ";
				sqlgroup = " group by BkcatalogID,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName ";
				if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_OrderNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sql = sql + sqlwhere + sqladd + sqlgroup ;
							if (edminamount->Text != "") {
								sqlhaving = " having sum(BS_OrderNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (sqlhaving != "") {
									sqlhaving = sqlhaving + " and sum(BS_OrderNote.Amount) <= " + edmaxamount->Text;
								}
								else
								{
									sqlhaving = " having sum(BS_OrderNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sql = sql + sqlhaving;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_OrderNoteHeader.VendorID in(select VendorID from BS_OrderNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by VendorID having sum(BS_OrderNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_OrderNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by VendorID having sum(BS_OrderNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 2:        //���鵥λ����
							sqlwhere = sqlwhere + " and BS_OrderNote.BkcatalogID in(select BkcatalogID from BS_OrderNote left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,VendorID having sum(BS_OrderNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_OrderNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,VendorID having sum(BS_OrderNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_OrderNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_OrderNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd + sqlgroup;
				}
			}
			else if (modle == 1) {  //���鰴��λ����
				sql = "select BkcatalogID,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as �ͻ�����,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,sum(BS_OrderNote.Amount) as ����,sum(BS_OrderNote.FixedPrice) as ����,SUM(BS_OrderNote.DiscountedPrice) as ʵ�� from BS_OrderNote "
						" left join BS_BookCatalog on BS_OrderNote.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id ";
				sqlgroup = " group by BkcatalogID,BS_OrderNoteHeader.VendorID,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName ";
				if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_OrderNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sqlwhere = sqlwhere + " and BS_OrderNote.BkcatalogID in(select BkcatalogID from BS_OrderNote left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_OrderNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_OrderNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_OrderNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_OrderNoteHeader.VendorID in(select VendorID from BS_OrderNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by VendorID having sum(BS_OrderNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_OrderNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by VendorID having sum(BS_OrderNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 2:        //���鵥λ����
							sql = sql + sqlwhere + sqladd + sqlgroup ;
							if (edminamount->Text != "") {
								sqlhaving = " having sum(BS_OrderNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (sqlhaving != "") {
									sqlhaving = sqlhaving + " and sum(BS_OrderNote.Amount) <= " + edmaxamount->Text;
								}
								else
								{
									sqlhaving = " having sum(BS_OrderNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sql = sql + sqlhaving;
						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_OrderNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_OrderNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd + sqlgroup;
				}
			}
			else      //����ϸ����
			{
				sql = "select BkcatalogID,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as �ͻ�����,BS_OrderNoteHeader.OrderNtCode as ����,BS_OrderNoteHeader.HdTime as ����,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,BS_OrderNote.Amount as ����,BS_OrderNote.FixedPrice as ����,BS_OrderNote.DiscountedPrice as ʵ�� from BS_OrderNote "
						" left join BS_BookCatalog on BS_OrderNote.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id ";
                if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_OrderNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
                        	sqlwhere = sqlwhere + " and BS_OrderNote.BkcatalogID in(select BkcatalogID from BS_OrderNote left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_OrderNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_OrderNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_OrderNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd ;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_OrderNoteHeader.VendorID in(select VendorID from BS_OrderNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by VendorID having sum(BS_OrderNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_OrderNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by VendorID having sum(BS_OrderNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd ;
						break;
						case 2:        //���鵥λ����

							sqltmp = sqlwhere;
							sqlwhere = sqlwhere + " and BS_OrderNote.BkcatalogID in(select BkcatalogID from BS_OrderNote left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,VendorID having sum(BS_OrderNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_OrderNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,VendorID having sum(BS_OrderNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sqlwhere = sqlwhere + " and BS_OrderNoteHeader.VendorID in(select VendorID from BS_OrderNote left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id " + sqltmp;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,VendorID having sum(BS_OrderNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_OrderNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,VendorID having sum(BS_OrderNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;

						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_OrderNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_OrderNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere + sqladd ;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd ;
				}
			}
		break;
		case 1:   //�ɹ�
			if (chsupplier->Checked && cbsupplier->Text != "") {
				try {
					supplierid = (int)cbsupplier->Items->Objects[cbsupplier->ItemIndex];
					sqlwhere = sqlwhere + " and BS_ProcureNoteHeader.SupplierID = " + IntToStr(supplierid) ;
				} catch (...) {
					MessageBox(0,"��ѡ����ȷ�Ĺ�Ӧ�̣�","��ʾ" ,MB_OK);
				}
			}
			if (modle == 0) {   //�������
				sql = "select BkcatalogID,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,sum(BS_ProcureNote.Amount) as ����,sum(BS_ProcureNote.FixedPrice) as ����,SUM(BS_ProcureNote.DiscountedPrice) as ʵ�� from BS_ProcureNote "
						" left join BS_BookCatalog on BS_ProcureNote.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_ProcureNoteHeader on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id ";
				sqlgroup = " group by BkcatalogID,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName ";
                if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_ProcureNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sql = sql + sqlwhere + sqladd +sqlgroup ;
							if (edminamount->Text != "") {
								sqlhaving = " having sum(BS_ProcureNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (sqlhaving != "") {
									sqlhaving = sqlhaving + " and sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text;
								}
								else
								{
									sqlhaving = " having sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sql = sql + sqlhaving;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_ProcureNoteHeader.SupplierID in(select SupplierID from BS_ProcureNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by SupplierID having sum(BS_ProcureNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_ProcureNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by SupplierID having sum(BS_ProcureNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 2:        //���鵥λ����
							sqlwhere = sqlwhere + " and BS_ProcureNote.BkcatalogID in(select BkcatalogID from BS_ProcureNote left join BS_ProcureNoteHeader on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,SupplierID having sum(BS_ProcureNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,SupplierID having sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_ProcureNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_ProcureNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
					default:
						;
					}
				}
				else
				{
                	sql = sql + sqlwhere + sqladd + sqlgroup;
				}
			}
			else if (modle == 1) {  //���鰴��λ����
				sql = "select BkcatalogID,CUST_CustomerInfo.Name as ��Ӧ������,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,sum(BS_ProcureNote.Amount) as ����,sum(BS_ProcureNote.FixedPrice) as ����,SUM(BS_ProcureNote.DiscountedPrice) as ʵ�� from BS_ProcureNote "
						" left join BS_BookCatalog on BS_ProcureNote.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_ProcureNoteHeader on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id "
						" left join CUST_CustomerInfo on BS_ProcureNoteHeader.SupplierID = CUST_CustomerInfo.id";
				sqlgroup = " group by BkcatalogID,CUST_CustomerInfo.Name,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName ";
                if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_ProcureNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sqlwhere = sqlwhere + " and BS_ProcureNote.BkcatalogID in(select BkcatalogID from BS_ProcureNote left join BS_ProcureNoteHeader on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_ProcureNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_ProcureNoteHeader.SupplierID in(select SupplierID from BS_ProcureNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by SupplierID having sum(BS_ProcureNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_ProcureNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by SupplierID having sum(BS_ProcureNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 2:        //���鵥λ����
							sql = sql + sqlwhere + sqladd + sqlgroup ;
							if (edminamount->Text != "") {
								sqlhaving = " having sum(BS_ProcureNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (sqlhaving != "") {
									sqlhaving = sqlhaving + " and sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text;
								}
								else
								{
									sqlhaving = " having sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sql = sql + sqlhaving;
						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_ProcureNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_ProcureNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd + sqlgroup;
				}
			}
			else      //����ϸ����
			{
				sql = "select BkcatalogID,CUST_CustomerInfo.Name as ��Ӧ������,BS_ProcureNoteHeader.ProcureNtCode as ����,BS_ProcureNoteHeader.HdTime as ����,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,BS_ProcureNote.Amount as ����,BS_ProcureNote.FixedPrice as ����,BS_ProcureNote.DiscountedPrice as ʵ�� from BS_ProcureNote "
						" left join BS_BookCatalog on BS_ProcureNote.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_ProcureNoteHeader on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id "
						" left join CUST_CustomerInfo on BS_ProcureNoteHeader.SupplierID = CUST_CustomerInfo.id";
				if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_ProcureNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sqlwhere = sqlwhere + " and BS_ProcureNote.BkcatalogID in(select BkcatalogID from BS_ProcureNote left join BS_ProcureNoteHeader on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_ProcureNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd ;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_ProcureNoteHeader.SupplierID in(select SupplierID from BS_ProcureNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by SupplierID having sum(BS_ProcureNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_ProcureNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by SupplierID having sum(BS_ProcureNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd ;
						break;
						case 2:        //���鵥λ����

							sqltmp = sqlwhere;
							sqlwhere = sqlwhere + " and BS_ProcureNote.BkcatalogID in(select BkcatalogID from BS_ProcureNote left join BS_ProcureNoteHeader on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,SupplierID having sum(BS_ProcureNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,SupplierID having sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sqlwhere = sqlwhere + " and BS_ProcureNoteHeader.SupplierID in(select SupplierID from BS_ProcureNote left join BS_ProcureNoteHeader on BS_ProcureNote.ProcureNtHeaderID = BS_ProcureNoteHeader.id " + sqltmp;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,SupplierID having sum(BS_ProcureNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,SupplierID having sum(BS_ProcureNote.Amount) <= " + edmaxamount->Text;
								}
							}
                            sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;

						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_ProcureNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_ProcureNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere + sqladd ;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd ;
				}
			}
		break;
		case 2:   //���
			if (chsupplier->Checked && cbsupplier->Text != "") {
				try {
					supplierid = (int)cbsupplier->Items->Objects[cbsupplier->ItemIndex];
					sqlwhere = sqlwhere + " and BS_StorageNoteHeader.SupplierID = " + IntToStr(supplierid) ;
				} catch (...) {
					MessageBox(0,"��ѡ����ȷ�Ĺ�Ӧ�̣�","��ʾ" ,MB_OK);
				}
			}
			if (modle == 0) {   //�������
				sql = "select BkcatalogID,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,sum(BS_StorageNote.Amount) as ����,sum(BS_StorageNote.FixedPrice) as ����,SUM(BS_StorageNote.DiscountedPrice) as ʵ�� from BS_StorageNote "
						" left join stk_bookinfo on BS_StorageNote.bkinfoid = stk_bookinfo.id "
						" left join BS_BookCatalog on stk_bookinfo.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.id ";
				sqlgroup = " group by BkcatalogID,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName ";
                if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_StorageNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sql = sql + sqlwhere + sqladd + sqlgroup ;
							if (edminamount->Text != "") {
								sqlhaving = " having sum(BS_StorageNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (sqlhaving != "") {
									sqlhaving = sqlhaving + " and sum(BS_StorageNote.Amount) <= " + edmaxamount->Text;
								}
								else
								{
									sqlhaving = " having sum(BS_StorageNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sql = sql + sqlhaving;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_StorageNoteHeader.SupplierID in(select SupplierID from BS_StorageNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by SupplierID having sum(BS_StorageNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_StorageNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by SupplierID having sum(BS_StorageNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 2:        //���鵥λ����
							sqlwhere = sqlwhere + " and stk_bookinfo.BkcatalogID in(select BkcatalogID from BS_StorageNote left join stk_bookinfo on BS_StorageNote.bkinfoid = stk_bookinfo.id left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,BS_StorageNoteHeader.SupplierID having sum(BS_StorageNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_StorageNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,BS_StorageNoteHeader.SupplierID having sum(BS_StorageNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_StorageNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_StorageNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd + sqlgroup;
				}
			}
			else if (modle == 1) {  //���鰴��λ����
				sql = "select BkcatalogID,CUST_CustomerInfo.Name as ��Ӧ������,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,sum(BS_StorageNote.Amount) as ����,sum(BS_StorageNote.FixedPrice) as ����,SUM(BS_StorageNote.DiscountedPrice) as ʵ�� from BS_StorageNote "
						" left join stk_bookinfo on BS_StorageNote.bkinfoid = stk_bookinfo.id "
						" left join BS_BookCatalog on stk_bookinfo.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.id "
						" left join CUST_CustomerInfo on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.id";
				sqlgroup = " group by BkcatalogID,CUST_CustomerInfo.Name,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName ";
				if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_StorageNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sqlwhere = sqlwhere + " and stk_bookinfo.BkcatalogID in(select BkcatalogID from BS_StorageNote left join stk_bookinfo on BS_StorageNote.bkinfoid = stk_bookinfo.id left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_StorageNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_StorageNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_StorageNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_StorageNoteHeader.SupplierID in(select SupplierID from BS_StorageNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by SupplierID having sum(BS_StorageNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_StorageNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by SupplierID having sum(BS_StorageNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 2:        //���鵥λ����
							sql = sql + sqlwhere + sqladd + sqlgroup ;
							if (edminamount->Text != "") {
								sqlhaving = " having sum(BS_StorageNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (sqlhaving != "") {
									sqlhaving = sqlhaving + " and sum(BS_StorageNote.Amount) <= " + edmaxamount->Text;
								}
								else
								{
									sqlhaving = " having sum(BS_StorageNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sql = sql + sqlhaving;
						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_StorageNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_StorageNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd + sqlgroup;
				}
			}
			else      //����ϸ����
			{
				sql = "select BkcatalogID,CUST_CustomerInfo.Name as ��Ӧ������,BS_StorageNoteHeader.StgNtCode as ����,BS_StorageNoteHeader.HdTime as ����,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,BS_StorageNote.Amount as ����,BS_StorageNote.FixedPrice as ����,BS_StorageNote.DiscountedPrice as ʵ�� from BS_StorageNote "
						" left join stk_bookinfo on BS_StorageNote.bkinfoid = stk_bookinfo.id "
						" left join BS_BookCatalog on stk_bookinfo.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.id "
						" left join CUST_CustomerInfo on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.id";
				if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_StorageNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sqlwhere = sqlwhere + " and stk_bookinfo.BkcatalogID in(select BkcatalogID from BS_StorageNote left join stk_bookinfo on BS_StorageNote.bkinfoid = stk_bookinfo.id left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_StorageNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_StorageNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_StorageNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd ;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_StorageNoteHeader.SupplierID in(select SupplierID from BS_StorageNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by SupplierID having sum(BS_StorageNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_StorageNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by SupplierID having sum(BS_StorageNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd ;
						break;
						case 2:        //���鵥λ����

							sqltmp = sqlwhere;
							sqlwhere = sqlwhere + " and stk_bookinfo.BkcatalogID in(select BkcatalogID from BS_StorageNote left join stk_bookinfo on BS_StorageNote.bkinfoid = stk_bookinfo.id left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,BS_StorageNoteHeader.SupplierID having sum(BS_StorageNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_StorageNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,BS_StorageNoteHeader.SupplierID having sum(BS_StorageNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sqlwhere = sqlwhere + " and BS_StorageNoteHeader.SupplierID in(select BS_StorageNoteHeader.SupplierID from BS_StorageNote left join stk_bookinfo on BS_StorageNote.bkinfoid = stk_bookinfo.id left join BS_StorageNoteHeader on BS_StorageNote.StgNtHeaderID = BS_StorageNoteHeader.id " + sqltmp;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,BS_StorageNoteHeader.SupplierID having sum(BS_StorageNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_StorageNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,BS_StorageNoteHeader.SupplierID having sum(BS_StorageNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;

						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_StorageNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_StorageNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere + sqladd ;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd ;
				}
			}
		break;
		case 3:   //����
			if (chclient->Checked && edtclient->Text != "") {
				sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.VendorID in (select id from dbo.getchild(" + IntToStr(ClientID) + "))";
			}
			if (modle == 0) {   //�������
				sql = "select BkcatalogID,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,sum(BS_WsaleNote.Amount) as ����,sum(BS_WsaleNote.FixedPrice) as ����,SUM(BS_WsaleNote.DiscountedPrice) as ʵ�� from BS_WsaleNote "
						" left join stk_bookinfo on BS_WsaleNote.bkinfoid = stk_bookinfo.id "
						" left join BS_BookCatalog on stk_bookinfo.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_WsaleNoteHeader on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id ";
				sqlgroup = " group by BkcatalogID,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName ";
				if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sql = sql + sqlwhere + sqladd + sqlgroup ;
							if (edminamount->Text != "") {
								sqlhaving = " having sum(BS_WsaleNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (sqlhaving != "") {
									sqlhaving = sqlhaving + " and sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text;
								}
								else
								{
									sqlhaving = " having sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sql = sql + sqlhaving;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.VendorID in(select VendorID from BS_WsaleNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by VendorID having sum(BS_WsaleNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_WsaleNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by VendorID having sum(BS_WsaleNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 2:        //���鵥λ����
							sqlwhere = sqlwhere + " and stk_bookinfo.BkcatalogID in(select BkcatalogID from BS_WsaleNote left join stk_bookinfo on BS_WsaleNote.bkinfoid = stk_bookinfo.id left join BS_WsaleNoteHeader on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,VendorID having sum(BS_WsaleNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,VendorID having sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_WsaleNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_WsaleNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd + sqlgroup;
				}
			}
			else if (modle == 1) {  //���鰴��λ����
				sql = "select BkcatalogID,dbo.UF_BS_GetClientName(BS_WsaleNoteHeader.VendorID) as �ͻ�����,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,sum(BS_WsaleNote.Amount) as ����,sum(BS_WsaleNote.FixedPrice) as ����,SUM(BS_WsaleNote.DiscountedPrice) as ʵ�� from BS_WsaleNote "
						" left join stk_bookinfo on BS_WsaleNote.bkinfoid = stk_bookinfo.id "
						" left join BS_BookCatalog on stk_bookinfo.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_WsaleNoteHeader on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id ";
				sqlgroup = " group by BkcatalogID,BS_WsaleNoteHeader.VendorID,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName ";
				if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sqlwhere = sqlwhere + " and stk_bookinfo.BkcatalogID in(select BkcatalogID from BS_WsaleNote left join stk_bookinfo on BS_WsaleNote.bkinfoid = stk_bookinfo.id left join BS_WsaleNoteHeader on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_WsaleNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.VendorID in(select VendorID from BS_WsaleNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by VendorID having sum(BS_WsaleNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_WsaleNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by VendorID having sum(BS_WsaleNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 2:        //���鵥λ����
							sql = sql + sqlwhere + sqladd + sqlgroup ;
							if (edminamount->Text != "") {
								sqlhaving = " having sum(BS_WsaleNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (sqlhaving != "") {
									sqlhaving = sqlhaving + " and sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text;
								}
								else
								{
									sqlhaving = " having sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sql = sql + sqlhaving;
						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_WsaleNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_WsaleNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd + sqlgroup;
				}
			}
			else      //����ϸ����
			{
				sql = "select BkcatalogID,dbo.UF_BS_GetClientName(BS_WsaleNoteHeader.VendorID) as �ͻ�����,BS_WsaleNoteHeader.WsaleNtCode as ����,BS_WsaleNoteHeader.HdTime as ����,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,BS_WsaleNote.Amount as ����,BS_WsaleNote.FixedPrice as ����,BS_WsaleNote.DiscountedPrice as ʵ�� from BS_WsaleNote "
						" left join stk_bookinfo on BS_WsaleNote.bkinfoid = stk_bookinfo.id "
						" left join BS_BookCatalog on stk_bookinfo.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_WsaleNoteHeader on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id ";
                if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sqlwhere = sqlwhere + " and stk_bookinfo.BkcatalogID in(select BkcatalogID from BS_WsaleNote left join stk_bookinfo on BS_WsaleNote.bkinfoid = stk_bookinfo.id left join BS_WsaleNoteHeader on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_WsaleNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd ;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.VendorID in(select VendorID from BS_WsaleNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by VendorID having sum(BS_WsaleNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_WsaleNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by VendorID having sum(BS_WsaleNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd ;
						break;
						case 2:        //���鵥λ����

							sqltmp = sqlwhere;
							sqlwhere = sqlwhere + " and stk_bookinfo.BkcatalogID in(select BkcatalogID from BS_WsaleNote left join stk_bookinfo on BS_WsaleNote.bkinfoid = stk_bookinfo.id left join BS_WsaleNoteHeader on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,VendorID having sum(BS_WsaleNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,VendorID having sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.VendorID in(select VendorID from BS_WsaleNote left join stk_bookinfo on BS_WsaleNote.bkinfoid = stk_bookinfo.id left join BS_WsaleNoteHeader on BS_WsaleNote.WsaleNtHeaderID = BS_WsaleNoteHeader.id " + sqltmp;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,VendorID having sum(BS_WsaleNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,VendorID having sum(BS_WsaleNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;

						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_WsaleNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_WsaleNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqladd + sqlwhere ;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd ;
				}
			}
		break;
		case 4:   //����
			if (modle == 0) {   //�������
				sql = "select BkcatalogID,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,sum(BS_RetailNote.Amount) as ����,sum(BS_RetailNote.FixedPrice) as ����,SUM(BS_RetailNote.DiscountedPrice) as ʵ�� from BS_RetailNote "
						" left join stk_bookinfo on BS_RetailNote.bkinfoid = stk_bookinfo.id "
						" left join BS_BookCatalog on stk_bookinfo.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_RetailNoteHeader on BS_RetailNote.RetailNtHeaderID = BS_RetailNoteHeader.id ";
				sqlgroup = " group by BkcatalogID,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName ";
                if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_RetailNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sql = sql + sqlwhere + sqladd + sqlgroup ;
							if (edminamount->Text != "") {
								sqlhaving = " having sum(BS_RetailNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (sqlhaving != "") {
									sqlhaving = sqlhaving + " and sum(BS_RetailNote.Amount) <= " + edmaxamount->Text;
								}
								else
								{
									sqlhaving = " having sum(BS_RetailNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sql = sql + sqlhaving;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_RetailNoteHeader.MemberID in(select MemberID from BS_RetailNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by MemberID having sum(BS_RetailNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_RetailNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by MemberID having sum(BS_RetailNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 2:        //���鵥λ����
							sqlwhere = sqlwhere + " and stk_bookinfo.BkcatalogID in(select BkcatalogID from BS_RetailNote left join stk_bookinfo on BS_RetailNote.bkinfoid = stk_bookinfo.id left join BS_RetailNoteHeader on BS_RetailNote.RetailNtHeaderID = BS_RetailNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,MemberID having sum(BS_RetailNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_RetailNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,MemberID having sum(BS_RetailNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_RetailNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_RetailNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd + sqlgroup;
				}
			}
			else if (modle == 1) {  //���鰴��λ����
				sql = "select BkcatalogID,CUST_MemberInfo.Name as ��Ա����,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,sum(BS_RetailNote.Amount) as ����,sum(BS_RetailNote.FixedPrice) as ����,SUM(BS_RetailNote.DiscountedPrice) as ʵ�� from BS_RetailNote "
						" left join stk_bookinfo on BS_RetailNote.bkinfoid = stk_bookinfo.id "
						" left join BS_BookCatalog on stk_bookinfo.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_RetailNoteHeader on BS_RetailNote.RetailNtHeaderID = BS_RetailNoteHeader.id "
						" left join CUST_MemberInfo on BS_RetailNoteHeader.MemberID = CUST_MemberInfo.id";
				sqlgroup = " group by BkcatalogID,CUST_MemberInfo.Name,BS_BookCatalog.ISBN,BS_BookCatalog.Name,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookCatalog.PressCount,BS_PressInfo.AbbreviatedName ";
				if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_RetailNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sqlwhere = sqlwhere + " and stk_bookinfo.BkcatalogID in(select BkcatalogID from BS_RetailNote left join stk_bookinfo on BS_RetailNote.bkinfoid = stk_bookinfo.id left join BS_RetailNoteHeader on BS_RetailNote.RetailNtHeaderID = BS_RetailNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_RetailNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_RetailNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_RetailNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_RetailNoteHeader.MemberID in(select MemberID from BS_RetailNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by MemberID having sum(BS_RetailNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_RetailNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by MemberID having sum(BS_RetailNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
						case 2:        //���鵥λ����
							sql = sql + sqlwhere + sqladd + sqlgroup ;
							if (edminamount->Text != "") {
								sqlhaving = " having sum(BS_RetailNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (sqlhaving != "") {
									sqlhaving = sqlhaving + " and sum(BS_RetailNote.Amount) <= " + edmaxamount->Text;
								}
								else
								{
									sqlhaving = " having sum(BS_RetailNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sql = sql + sqlhaving;
						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_RetailNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_RetailNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere + sqladd + sqlgroup;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd + sqlgroup;
				}
			}
			else      //����ϸ����
			{
				sql = "select BkcatalogID,CUST_MemberInfo.Name as ��Ӧ������,BS_RetailNoteHeader.RetailNtCode as ����,BS_RetailNoteHeader.HdTime as ����,BS_BookCatalog.ISBN,BS_BookCatalog.Name as ����,BS_BookCatalog.Price as ����,BS_BookCatalog.Author as ����,BS_PressInfo.AbbreviatedName as ������,BS_BookCatalog.PressCount as ���,BS_RetailNote.Amount as ����,BS_RetailNote.FixedPrice as ����,BS_RetailNote.DiscountedPrice as ʵ�� from BS_RetailNote "
						" left join stk_bookinfo on BS_RetailNote.bkinfoid = stk_bookinfo.id "
						" left join BS_BookCatalog on stk_bookinfo.BkcatalogID = BS_BookCatalog.id "
						" left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id "
						" left join BS_RetailNoteHeader on BS_RetailNote.RetailNtHeaderID = BS_RetailNoteHeader.id "
						" left join CUST_MemberInfo on BS_RetailNoteHeader.MemberID = CUST_MemberInfo.id";
				if (chstorage->Checked) {
					try {
						stgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
					} catch (...) {
						MessageBox(0,"��ѡ����ȷ�ĵ�ţ�","��ʾ" ,MB_OK);
					}
					sqlwhere = sqlwhere + " and BS_RetailNoteHeader.stgid = " + IntToStr(stgid);
				}
				sqlwhere = sqlwhere + sqltime;
				if (chamount->Checked && (edminamount->Text != "" || edmaxamount->Text != "")) {
					switch (rg3->ItemIndex ) {
						case 0:        //�������
							sqlwhere = sqlwhere + " and stk_bookinfo.BkcatalogID in(select BkcatalogID from BS_RetailNote left join stk_bookinfo on BS_RetailNote.bkinfoid = stk_bookinfo.id left join BS_RetailNoteHeader on BS_RetailNote.RetailNtHeaderID = BS_RetailNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_RetailNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_RetailNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID having sum(BS_RetailNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqladd + sqlwhere ;
						break;
						case 1:        //����λ����
							sqlwhere = sqlwhere + " and BS_RetailNoteHeader.MemberID in(select MemberID from BS_RetailNoteHeader " +  sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by MemberID having sum(BS_RetailNoteHeader.TotalAmount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_RetailNoteHeader.TotalAmount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by MemberID having sum(BS_RetailNoteHeader.TotalAmount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd ;
						break;
						case 2:        //���鵥λ����

							sqltmp = sqlwhere;
							sqlwhere = sqlwhere + " and stk_bookinfo.BkcatalogID in(select BkcatalogID from BS_RetailNote left join stk_bookinfo on BS_RetailNote.bkinfoid = stk_bookinfo.id left join BS_RetailNoteHeader on BS_RetailNote.RetailNtHeaderID = BS_RetailNoteHeader.id " + sqlwhere;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,MemberID having sum(BS_RetailNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_RetailNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,MemberID having sum(BS_RetailNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sqlwhere = sqlwhere + " and BS_RetailNoteHeader.MemberID in(select MemberID from BS_RetailNote left join stk_bookinfo on BS_RetailNote.bkinfoid = stk_bookinfo.id left join BS_RetailNoteHeader on BS_RetailNote.RetailNtHeaderID = BS_RetailNoteHeader.id " + sqltmp;
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " group by BkcatalogID,MemberID having sum(BS_RetailNote.Amount) >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								if (edminamount->Text != "") {
									sqlwhere = sqlwhere + " and sum(BS_RetailNote.Amount) <= " + edmaxamount->Text ;
								}
								else
								{
									sqlwhere = sqlwhere + " group by BkcatalogID,MemberID having sum(BS_RetailNote.Amount) <= " + edmaxamount->Text;
								}
							}
							sqlwhere = sqlwhere + ")";
							sql = sql + sqlwhere + sqladd + sqlgroup;

						break;
						case 3:        //����ϸ
							if (edminamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_RetailNote.amount >= " + edminamount->Text;
							}
							if (edmaxamount->Text != "") {
								sqlwhere = sqlwhere + " and BS_RetailNote.amount <= " + edmaxamount->Text;
							}
							sql = sql + sqlwhere +sqladd ;
						break;
					default:
						;
					}
				}
				else
				{
					sql = sql + sqlwhere + sqladd ;
				}
			}
		break;
	default:
		;
	}
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	DBGridEh1->Columns->Clear();
	for (int i = 1; i < query->FieldCount ; i++) {
		TColumnEh * col ;
		col = DBGridEh1->Columns->Add();
		col->Field = query->Fields->Fields[i];
		if (query->Fields->Fields[i]->FieldName == "�ͻ�����") {
			col->Width = 120;
		}
		if (query->Fields->Fields[i]->FieldName == "��Ӧ������") {
			col->Width = 120;
		}
		if (query->Fields->Fields[i]->FieldName == "����") {
			col->Width = 120;
		}
		if (query->Fields->Fields[i]->FieldName == "����") {
			col->Width = 60;
		}
		if (query->Fields->Fields[i]->FieldName == "����") {
			col->Width = 70;
		}
		if (query->Fields->Fields[i]->FieldName == "������") {
			col->Width = 80;
		}
		if (query->Fields->Fields[i]->FieldName == "���") {
			col->Width = 50;
		}
		if (query->Fields->Fields[i]->FieldName == "����") {
			col->Footer->FieldName = "����";
			col->Footer->ValueType = fvtSum ;
			col->Width = 60;
		}
		if (query->Fields->Fields[i]->FieldName == "����") {
			col->Footer->FieldName = "����";
			col->Footer->ValueType = fvtSum ;
			col->DisplayFormat = "###0.00";
			col->Footer->DisplayFormat = "###0.00";
			col->Width = 80;
		}
		if (query->Fields->Fields[i]->FieldName == "ʵ��") {
			col->Footer->FieldName = "ʵ��";
			col->Footer->ValueType = fvtSum ;
			col->DisplayFormat = "###0.00";
			col->Footer->DisplayFormat = "###0.00";
			col->Width = 80;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::edminamountChange(TObject *Sender)
{
	if (edminamount->Text != "") {
		chamount->Checked = true;
	}
	else if (edmaxamount->Text != "") {
		chamount->Checked = true;
	}
	else
	{
    	chamount->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::edtclientChange(TObject *Sender)
{
	if (edtclient->Text == "") {
		chclient->Checked = false;
	}
	else
	{
    	chclient->Checked = true;
	}
}
//---------------------------------------------------------------------------



void __fastcall Tfrmywtongji::RzButton1Click(TObject *Sender)
{
	Query(0);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::RzButton2Click(TObject *Sender)
{
	Query(1);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmywtongji::RzButton3Click(TObject *Sender)
{
	Query(3);
}
//---------------------------------------------------------------------------

