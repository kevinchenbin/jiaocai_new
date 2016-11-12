//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "QryStockNoteForm.h"
#include "pdutil.h"
#include "Notedetail.h"
#include "Notedetail.h"
#include "bookhistory.h"
#include "DBGridEhImpExp.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzEdit"
#pragma link "RzRadChk"
#pragma link "RzDBCmbo"
#pragma link "RzLine"
#pragma link "RzTabs"
#pragma link "RzDBGrid"
#pragma link "RzCmboBx"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TfrmQryCheckNote *frmQryCheckNote;
//---------------------------------------------------------------------------
__fastcall TfrmQryCheckNote::TfrmQryCheckNote(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
   this->WindowState = wsMaximized ;
   dtedtEnd->Date = Now();
   dtedtStart->Date = Now();
}
//---------------------------------------------------------------------------
String TfrmQryCheckNote::QueryDesic()
{
	 TADOQuery * aq;
   aq = new TADOQuery(this);
   aq->Connection = m_con ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add("select bk from sys_bsset where name ='xiaoshudian'");
   aq->Open();
   Desic1 = aq->FieldByName("bk")->AsAnsiString;
   return "��###,###,##"+ aq->FieldByName("bk")->AsAnsiString ;
   delete aq;

}
//---------------------------------------------------------------------------
void __fastcall TfrmQryCheckNote::tlbtnQryClick(TObject *Sender)
{
	//��ѯ
	Query();

}
//---------------------------------------------------------------------------
void TfrmQryCheckNote::Query()
{

	AnsiString isbn;
	if (chckbxISBN->Checked && edtISBN->Text != "") {
		isbn = edtISBN->Text.Trim();
		if (isbn.Length() == 10 || isbn.Length() == 13  ) {
			isbn = isbn.Delete(isbn.Length(),1);
		}
	}
	spQryNote->Active = false;
	for (int i = 0; i < spQryNote->Parameters->Count; i++)
	{
        spQryNote->Parameters->operator [](i)->Value = System::Variant();
	}

	if (chckbxStartTime->Checked && dtedtStart->Text != "") //��ʼʱ��
		spQryNote->Parameters->ParamByName("@Start")->Value = dtedtStart->Date;

	if (chckbxEndTime->Checked && dtedtEnd->Text != "") //����ʱ��
		spQryNote->Parameters->ParamByName("@End")->Value = dtedtEnd->Date;

    if (chckbxBookName->Checked && edtBookName->Text != "") //����
		spQryNote->Parameters->ParamByName("@Name")->Value = "%" + edtBookName->Text + "%";

	if (chckbxUserDefNum->Checked && edtUserDefNum->Text != "") //�Ա���
		spQryNote->Parameters->ParamByName("@UserDefCode")->Value = "%" + edtUserDefNum->Text + "%";

	if (chckbxPress->Checked && dblkpcbbPress->Text != "") //������
		spQryNote->Parameters->ParamByName("@PressID")->Value = dsetPress->FieldByName("ID")->AsInteger;

	if (chckbxISBN->Checked && edtISBN->Text != "") //ISBN
		spQryNote->Parameters->ParamByName("@ISBN")->Value = "%" + isbn + "%";

	if (chckbxPrice->Checked && numedtMinPrice->Text != "") //����
	{
		try {
			StrToFloat(numedtMinPrice->Text);
		} catch (...) {
			return;
		}
		spQryNote->Parameters->ParamByName("@MinPrice")->Value = numedtMinPrice->Value;
	}
	if (chckbxPrice->Checked && numedtMaxPrice->Text != "") //����
	{
		try {
			StrToFloat(numedtMaxPrice->Text);
		} catch (...) {
			return;
		}
		spQryNote->Parameters->ParamByName("@MaxPrice")->Value = numedtMaxPrice->Value;
	}

	if (chckbxType->Checked && dblkpcbbBookType->Text != "") //��Ŀ����
		spQryNote->Parameters->ParamByName("@BktypeID")->Value = dsetBookType->FieldByName("ID")->AsInteger;

	if (chckbxCustomer->Checked) //�ͻ�
		spQryNote->Parameters->ParamByName("@CustomerID")->Value = dsetCustomer->FieldByName("ID")->AsInteger;

	if (chckbxAuthor->Checked && edtAuthor->Text != "") //����
		spQryNote->Parameters->ParamByName("@Author")->Value = "%" + edtAuthor->Text + "%";

	if (chckbxRemarks->Checked && edtRemarks->Text != "") //��ע
		spQryNote->Parameters->ParamByName("@Remarks")->Value = "%" + edtRemarks->Text + "%";

	if (chckbxBkstack->Checked) //��λ
		spQryNote->Parameters->ParamByName("@BkstackID")->Value = dsetBookstack->FieldByName("ID")->AsInteger;

	if (chckbxAmount->Checked && numedtMinAmount->Text != "") //���
	{
		try {
			StrToInt(numedtMinAmount->Text);
		} catch (...) {
			return;
		}
		spQryNote->Parameters->ParamByName("@MinAmount")->Value = numedtMinAmount->IntValue;
	}
	if (chckbxAmount->Checked && numedtMaxAmount->Text != "") //���
	{
    	try {
			StrToInt(numedtMaxAmount->Text);
		} catch (...) {
			return;
		}
		spQryNote->Parameters->ParamByName("@MaxAmount")->Value = numedtMaxAmount->IntValue;
	}
	if (cbdamage->Checked && maxnu->Text !="") {
		spQryNote->Parameters->ParamByName("@MaxDamage")->Value  = maxnu->IntValue ;
	}
	if (cbdamage->Checked && minnu->Text !="") {
	 spQryNote->Parameters->ParamByName("@MinDamage")->Value  = minnu->IntValue ;
	}

	if (chckbxStorage->Checked) //��
		//spQryNote->Parameters->ParamByName("@StgID")->Value = dsetInit->FieldByName("StorageID")->AsInteger;
		spQryNote->Parameters->ParamByName("@StgID")->Value = dsetStorage->FieldByName("ID")->AsInteger;
	if (chstaff->Checked ) {    //����Ա
		spQryNote->Parameters->ParamByName("@staff")->Value = int(cbstaff->Items->Objects[cbstaff->ItemIndex]);
	}
	if (chchayi->Checked ) {
		spQryNote->Parameters->ParamByName("@andan")->Value = 1;
	}
	if (chyingkui->Checked ) {
		if (numykmin->Text != "") {
			try {
				StrToInt(numykmin->Text);
			} catch (...) {
				return;
			}
			spQryNote->Parameters->ParamByName("@Minyk")->Value = numykmin->IntValue;
		}
		if (numykmax->Text != "") {
        	try {
				StrToInt(numykmax->Text);
			} catch (...) {
				return;
			}
			spQryNote->Parameters->ParamByName("@Maxyk")->Value = numykmax->IntValue;
		}
	}
	spQryNote->Parameters->ParamByName("@Bsmode")->Value = 4;
	spQryNote->Parameters->ParamByName("@SearchMode")->Value = pgcntrlResult->ActivePage->Tag;
	spQryNote->Parameters->ParamByName("@type")->Value = rgtype->ItemIndex;


	try
	{
		spQryNote->Active = true;
		switch (pgcntrlResult->ActivePage->Tag)
		{
		case 1:
			dsrcByNtHeader->DataSet = NULL;
			dsetByNtHeader->Recordset = spQryNote->Recordset;
			dsetByNtHeader->First();
			dsrcByNtHeader->DataSet = dsetByNtHeader;
			((TFloatField *)dbgrdByNtHeader->DataSource->DataSet->FieldByName("BFixedPrice"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdByNtHeader->DataSource->DataSet->FieldByName("BDiscountPrice"))->DisplayFormat = "0.00";
			break;
		case 2:
			dsrcByNote->DataSet = NULL;
			dsetByNote->Recordset = spQryNote->Recordset;
            dsetByNote->First();
			dsrcByNote->DataSet = dsetByNote;
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("BFixedPrice"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("BDiscountPrice"))->DisplayFormat = "0.00";
			break;
		case 4:
			dsrcByBktype->DataSet = NULL;
			dsetByBktype->Recordset = spQryNote->Recordset;
			dsetByBktype->First();
			dsrcByBktype->DataSet = dsetByBktype;
			((TFloatField *)dbgrdByBktype->DataSource->DataSet->FieldByName("BFixedPrice"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdByBktype->DataSource->DataSet->FieldByName("BDiscountPrice"))->DisplayFormat = "0.00";
        	break;
		case 5:
			dsrcByPress->DataSet = NULL;
			dsetByPress->Recordset = spQryNote->Recordset;
			dsetByPress->First();
			dsrcByPress->DataSet = dsetByPress;
			((TFloatField *)dbgrdByPress->DataSource->DataSet->FieldByName("BFixedPrice"))->DisplayFormat = "0.00";
			((TFloatField *)dbgrdByPress->DataSource->DataSet->FieldByName("BDiscountPrice"))->DisplayFormat = "0.00";
        	break;
		default:
			break;
		}
	}
	catch(...)
	{

    }
}

//---------------------------------------------------------------------------

void TfrmQryCheckNote::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	//
	fcon = m_con;
	spQryNote->Connection = m_con;
	dsetPress->Connection = m_con;
	dsetPress->Active = true;
	dsetBookType->Connection = m_con;
	dsetBookType->Active = true;
	dsetStorage->Connection = m_con;
	dsetStorage->Active = true;
	dsetCustomer->Connection = m_con;
	dsetCustomer->Active = true;
	dsetBookstack->Connection = m_con;
	dsetBookstack->Active = true;
	qryItems->Connection = m_con;
	numedtMinPrice->Text = "";
	numedtMaxPrice->Text = "";
	numedtMinAmount->Text = "";
	numedtMaxAmount->Text = "";
	chckbxStorage->Checked = true;
	dblkpcbbStorage->KeyValue = m_storageID ;
    TADOQuery * aq;
   aq = new TADOQuery(this);
   aq->Connection = m_con ;
   AnsiString sql;
   sql = "select id,Name from SYS_User where stgID = " + IntToStr(m_storageID) ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   while (!aq->Eof )
   {
		cbstaff->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
   }
   sql = "select Master from SYS_StorageInfo where id = " + IntToStr(m_storageID);
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   if (aq->FieldByName("Master")->AsBoolean) {
		chckbxStorage->Enabled = true;
		dblkpcbbStorage->Enabled = true;
   }
   else
   {
        chckbxStorage->Enabled = false;
		sql = "select * from BS_StoToSto where ystgid = " + IntToStr(m_storageID) + " and pandian = 1";
        aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount == 0) {
			dblkpcbbStorage->Enabled = false;
		}
		else
		{
			AnsiString ss ;
			ss = "ID = " + IntToStr(m_storageID);
			while (!aq->Eof )
			{
				ss = ss + " or ID = " + aq->FieldByName("mstgid")->AsString ;
				aq->Next();
			}
			dsetStorage->Filtered = false;
			dsetStorage->Filter = ss;
			dsetStorage->Filtered = true;
		}
   }

   delete aq;
	Desic = QueryDesic();
}


void __fastcall TfrmQryCheckNote::chckbxBkstackClick(TObject *Sender)
{
	//
	if (chckbxBkstack->Checked)
	{
    	chckbxStorage->Checked = chckbxBkstack->Checked;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::tlbtnExportClick(TObject *Sender)
{
	//Excel����
	switch (pgcntrlResult->ActivePage->Tag)
	{
	case 1:
		if (dsetByNtHeader->Active && dsetByNtHeader->RecordCount > 0) {
				DbgridToExcel(dbgrdByNtHeader);
			}
		break;
	case 2:
		if (dsetByNote->Active && dsetByNote->RecordCount > 0) {
				DbgridToExcel(dbgrdByNote);
			}
		break;
	case 3:
		break;
	case 4:
		if (dsetByBktype->Active && dsetByBktype->RecordCount > 0) {
				DbgridToExcel(dbgrdByBktype);
			}
		break;
	case 5:
		if (dsetByPress->Active && dsetByPress->RecordCount > 0) {
				DbgridToExcel(dbgrdByPress);
			}
		break;
	default:
		break;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TfrmQryCheckNote::DbgridToExcel(TDBGridEh* dbg)
{
	AnsiString temptext,path;
      TStringList *st;
	//savedlg->FileName = "�̵��ѯ";
	 savedlg->FileName = "�̵��ѯ"+FormatDateTime("yyyy-mm-ddHHMM",Now())+".csv";



	 if (savedlg->Execute())
	{

		  savedlg->FileName=savedlg->FileName;// + "." + Ext;
		  SaveDBGridEhToExportFile(__classid(TDBGridEhExportAsCSV),dbg,savedlg->FileName,true);
		  st = new TStringList();
		  st->LoadFromFile(savedlg->FileName);
		  st->Text = StringReplace(st->Text,";",",",TReplaceFlags()<<rfReplaceAll);
		  st->SaveToFile(savedlg->FileName);
		  String sMsg="�ļ������ɹ���\r\n\r\n"+savedlg->FileName;
		  MessageBox(0,"������ϣ�","��ʾ" ,MB_OK);
          return true;

	}
	else
	{
		return false;
	}














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

	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());


	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet ->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "BookName") {
					AnsiString bookname;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					bookname = StringReplace(bookname , '\n',"",TReplaceFlags()<<rfReplaceAll);
                    bookname = StringReplace(bookname , '\r',"",TReplaceFlags()<<rfReplaceAll);
					temptext = temptext + bookname + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "BFixedPrice" || dbg->Columns ->Items [j-1]->FieldName == "BDiscountPrice") {
					temptext = temptext + FormatFloat(Desic1,dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsFloat) + ",";
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
	dbg->DataSource ->DataSet ->EnableControls();

	temptext = "\n�ϼ�,";
	AnsiString text;
	for(int q=1;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			text = dbg->GetFooterValue(q,dbg->Columns->Items [q]);
			text = StringReplace(text , ",","",TReplaceFlags()<<rfReplaceAll);
			text = StringReplace(text , "-","'-",TReplaceFlags()<<rfReplaceAll);
			temptext = temptext + text + ",";
		}
	}

	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
	FileClose(iFileHandle);
    MessageBox(0,"������ϣ�","��ʾ" ,MB_OK);
	return false;

}
//---------------------------------------------------------------------------


void __fastcall TfrmQryCheckNote::tlbtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::edtPressKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		TCustomEdit* edt = dynamic_cast<TCustomEdit*>(Sender);
		if (edt != NULL)
		{
			if (edt->Tag == 1)//���
			{
				//��ѯ���
				String sql = "select * from BS_PressInfo where AbbreviatedName like '%";
				sql = sql + edt->Text + "%'";
				dsetPress->Active = false;
				dsetPress->CommandText = sql;
				dsetPress->Active = true;
				if (dsetPress->RecordCount >= 1)
				{
					dsetPress->First();
					dblkpcbbPress->KeyValue = dsetPress->FieldByName("ID")->AsInteger ;
				}
			}
			else if (edt->Tag == 2)//��Ӧ��
			{
				//��ѯ��Ӧ��
				String sql = "select ID,Name from CUST_CustomerInfo where (ID=0 or (ID>0 and Type=1)) and Name like '%";
				sql = sql + edtCustomer->Text + "%'";

                dsetCustomer->Active = false;
				dsetCustomer->CommandText = sql;
				dsetCustomer->Active = true;
				dsetCustomer->First();
				dblkpcbbCustomer->KeyValue = dsetCustomer->FieldByName("ID")->AsInteger;

				/*qryItems->Active = false;
				qryItems->SQL->Clear();
				qryItems->SQL->Add(sql);
				qryItems->Active = true;
				if (qryItems->RecordCount >= 1)
				{
					qryItems->First();
					dsetInit->Edit();
					dsetInit->FieldByName("CustomerID")->AsInteger = qryItems->FieldByName("ID")->AsInteger;
				}
				qryItems->Active = false;    */
			}
			else
			{

            }
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmQryCheckNote::FormClose(TObject *Sender, TCloseAction &Action)
{
	//
	spQryNote->Active = false;
	dsetPress->Active = false;
	dsetBookType->Active = false;
	dsetStorage->Active = false;
	dsetCustomer->Active = false;
	dsetBookstack->Active = false;
	qryItems->Active = false;
	dsetByNtHeader->Active = false;
	dsetByNote->Active = false;
	dsetByCustomer->Active = false;
	dsetByBktype->Active = false;
	dsetByPress->Active = false;
	TfrmMDIChild::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------



void __fastcall TfrmQryCheckNote::edtBookNameChange(TObject *Sender)
{
	if (edtBookName->Text != "") {
		chckbxBookName->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::edtUserDefNumChange(TObject *Sender)
{
	if (edtUserDefNum->Text != "") {
        chckbxUserDefNum->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::edtISBNChange(TObject *Sender)
{
	if (edtISBN->Text != "") {
        chckbxISBN->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::numedtMinPriceChange(TObject *Sender)
{
	if (numedtMinPrice->Text != "") {
		chckbxPrice->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::numedtMaxPriceChange(TObject *Sender)
{
	if (numedtMaxPrice->Text != "") {
        chckbxPrice->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::numedtMinAmountChange(TObject *Sender)
{
	if (numedtMinAmount->Text != "") {
		chckbxAmount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::numedtMaxAmountChange(TObject *Sender)
{
	if (numedtMaxAmount->Text != "") {
        chckbxAmount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::edtAuthorChange(TObject *Sender)
{
	if (edtAuthor->Text != "") {
        chckbxAuthor->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::edtRemarksChange(TObject *Sender)
{
	if (edtRemarks->Text != "") {
        chckbxRemarks->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::dblkpcbbPressClick(TObject *Sender)
{
	if (dblkpcbbPress->Text != "") {
		chckbxPress->Checked = true;
		edtPress->Text = dsetPress->FieldByName("PresentNum")->AsString ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::dblkpcbbBookstackClick(TObject *Sender)
{
	if (dblkpcbbBookstack->Text != "") {
        chckbxBkstack->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::dblkpcbbBookTypeClick(TObject *Sender)
{
	if (dblkpcbbBookType->Text != "" ) {
        chckbxType->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::dblkpcbbStorageClick(TObject *Sender)
{
	if (dblkpcbbStorage->Text != "") {
		chckbxStorage->Checked = true;
		dsetBookstack->Close();
		dsetBookstack->CommandText = "select ID, Name from STK_BookstackInfo where StgID = " + dsetStorage->FieldByName("ID")->AsString ;
		dsetBookstack->Active = false;
		dsetBookstack->Active = true;

		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = m_con ;
		AnsiString sql;
		sql = "select ID,Name from sys_user where stgid = " + dsetStorage->FieldByName("ID")->AsString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbstaff->Items ->Clear();
		while (!aq->Eof )
		{
			cbstaff->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::dblkpcbbCustomerClick(TObject *Sender)
{
	if (dblkpcbbCustomer->Text != "") {
		chckbxCustomer->Checked = true;
		edtCustomer->Text = dsetCustomer->FieldByName("ID")->AsString ;
	}
}
//---------------------------------------------------------------------------





void __fastcall TfrmQryCheckNote::dbgrdByNtHeader1TitleClick(TColumn *Column)
{
	if (dsetByNtHeader->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetByNtHeader->Sort == "") {
		dsetByNtHeader->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetByNtHeader->Sort == qusort) {
		dsetByNtHeader->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetByNtHeader->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmQryCheckNote::dbgrdByCustomerTitleClick(TColumn *Column)
{
	if (dsetByCustomer->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetByCustomer->Sort == "") {
		dsetByCustomer->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetByCustomer->Sort == qusort) {
		dsetByCustomer->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetByCustomer->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmQryCheckNote::cbstaffClick(TObject *Sender)
{
	if (cbstaff->Text != "") {
		chstaff->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F6) {      //����
		tlbtnExport->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 70 ) {    //��ѯ
		tlbtnQry->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 81 ) {    //�˳�
		tlbtnExit->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmQryCheckNote::dbgrdByNtHeaderDblClick(TObject *Sender)
{
	if (dsetByNtHeader->IsEmpty() ) {
        return;
	}
	if (dsetByNtHeader->RecordCount > 0) {
		TfrmNotedetail *frm = new TfrmNotedetail(Application,dsetByNtHeader->FieldByName("checkstockNum")->AsString,3,fcon,dsetByNtHeader->FieldByName("panstyle")->AsInteger,m_userID );

		frm->ShowModal();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::dbgrdByNtHeaderTitleClick(TColumnEh *Column)
{
	if (dsetByNtHeader->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetByNtHeader->Sort == "") {
		dsetByNtHeader->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetByNtHeader->Sort == qusort) {
		dsetByNtHeader->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetByNtHeader->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::dbgrdByNoteTitleClick(TColumnEh *Column)
{
	if (dsetByNote->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetByNote->Sort == "") {
		dsetByNote->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetByNote->Sort == qusort) {
		dsetByNote->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetByNote->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::dbgrdByBktypeTitleClick(TColumnEh *Column)
{
	if (dsetByBktype->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetByBktype->Sort == "") {
		dsetByBktype->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetByBktype->Sort == qusort) {
		dsetByBktype->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetByBktype->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::dbgrdByPressTitleClick(TColumnEh *Column)
{
	if (dsetByPress->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (dsetByPress->Sort == "") {
		dsetByPress->Sort =  Column->FieldName + " ASC";
	}
	else if (dsetByPress->Sort == qusort) {
		dsetByPress->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		dsetByPress->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryCheckNote::N1Click(TObject *Sender)
{
	if (dsetByNote->IsEmpty() ) {
        return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con ,m_storageID ,dsetByNote->FieldByName("Catalogid")->AsInteger,m_userID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------
