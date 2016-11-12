//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "QryCOderNoteForm.h"
#include "pdutil.h"
#include "Notedetail.h"
#include "..\bsadmin\UnitSelectClient.h"
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
TfrmCQryOderNote *frmCQryOderNote;
//---------------------------------------------------------------------------
__fastcall TfrmCQryOderNote::TfrmCQryOderNote(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
   this->WindowState = wsMaximized ;
   dtedtEnd->Date = Now();
   dtedtStart->Date = Now();
   chckbxBkstack->Enabled = false;
   dblkpcbbBookstack->Enabled = false;
   totalsend = 0;
   totalunsend = 0;
   ClientID = -1;
}
//---------------------------------------------------------------------------
String TfrmCQryOderNote::QueryDesic()
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

void __fastcall TfrmCQryOderNote::tlbtnQryClick(TObject *Sender)
{
	//��ѯ
	Query();
	switch (pgcntrlResult->ActivePage->Tag) {
		case 1:
			((TFloatField *)dbgrdByNtHeader->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByNtHeader->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			break;
		case 2:
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0%";
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByNote->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			break;
		case 3:
			((TFloatField *)dbgrdByCustomer->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByCustomer->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			break;
	
		case 5:
			((TFloatField *)dbgrdByPress->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByPress->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			break;
    default:
        ;
	}
}

void TfrmCQryOderNote::Query()
{
	long double   TotalMan=0.0000,TotalShi=0.0000;
	int TotalNum=0,totalunrec = 0;
	AnsiString isbn;
	int stateaa ;
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
		spQryNote->Parameters->ParamByName("@MinPrice")->Value = numedtMinPrice->Value;

	if (chckbxPrice->Checked && numedtMaxPrice->Text != "") //����
		spQryNote->Parameters->ParamByName("@MaxPrice")->Value = numedtMaxPrice->Value;

	if (chckbxType->Checked && dblkpcbbBookType->Text != "") //��Ŀ����
		spQryNote->Parameters->ParamByName("@BktypeID")->Value = dsetBookType->FieldByName("ID")->AsInteger;

	if (chckbxCustomer->Checked && cbusername->Text != "") //�ͻ�
		spQryNote->Parameters->ParamByName("@CustomerID")->Value =int(cbusername->Items->Objects[cbusername->ItemIndex]);

	if (chckbxAuthor->Checked && edtAuthor->Text != "") //����
		spQryNote->Parameters->ParamByName("@Author")->Value = "%" + edtAuthor->Text + "%";

	if (chckbxRemarks->Checked && edtRemarks->Text != "") //��ע
		spQryNote->Parameters->ParamByName("@Remarks")->Value = "%" + edtRemarks->Text + "%";

	if (chckbxBkstack->Checked) //��λ
		spQryNote->Parameters->ParamByName("@BkstackID")->Value = dsetBookstack->FieldByName("ID")->AsInteger;

	if (chckbxAmount->Checked && numedtMinAmount->Text != "") //���
		spQryNote->Parameters->ParamByName("@MinAmount")->Value = numedtMinAmount->IntValue;

	if (chckbxAmount->Checked && numedtMaxAmount->Text != "") //���
		spQryNote->Parameters->ParamByName("@MaxAmount")->Value = numedtMaxAmount->IntValue;

	if (chckbxStorage->Checked) //��
		//spQryNote->Parameters->ParamByName("@StgID")->Value = dsetInit->FieldByName("StorageID")->AsInteger;
		spQryNote->Parameters->ParamByName("@StgID")->Value = dsetStorage->FieldByName("ID")->AsInteger;
    if (chstaff->Checked ) {    //����Ա
		spQryNote->Parameters->ParamByName("@staff")->Value = int(cbstaff->Items->Objects[cbstaff->ItemIndex]);
	}
	if (chdiscount->Checked && edmindiscount->Text != "") {   //��С�ۿ�
		spQryNote->Parameters->ParamByName("@mindiscount")->Value = StrToFloat(edmindiscount->Text);
	}
	if (chdiscount->Checked && edmaxdiscount->Text != "") {   //����ۿ�
		spQryNote->Parameters->ParamByName("@maxdiscount")->Value =  StrToFloat(edmaxdiscount->Text);
	}

	spQryNote->Parameters->ParamByName("@Bsmode")->Value = 12;
	spQryNote->Parameters->ParamByName("@SearchMode")->Value = pgcntrlResult->ActivePage->Tag;
	if (chactive->Checked && !chnoactive->Checked ) {
		spQryNote->Parameters->ParamByName("@type")->Value = 1;
	}
	else if (chnoactive->Checked && !chactive->Checked) {
		spQryNote->Parameters->ParamByName("@type")->Value = 2;
	}
	else
	{
		spQryNote->Parameters->ParamByName("@type")->Value = 0;
	}

	if (chsendamount->Checked ) {
		spQryNote->Parameters->ParamByName("@check")->Value = 1;
	}

	if (chunsendamount->Checked ) {
		spQryNote->Parameters->ParamByName("@nocheck")->Value = 1;
	}
	if (chunarrive->Checked ) {
		spQryNote->Parameters->ParamByName("@checkpart")->Value = 1;
	}
	if (chbaoxiao->Checked ) {
		spQryNote->Parameters->ParamByName("@MaxDamage")->Value = 1;
	}
	if (chxiankuan->Checked ) {
		spQryNote->Parameters->ParamByName("@MinDamage")->Value = 1;
	}
	if (chconfrim->Checked ) {
		spQryNote->Parameters->ParamByName("@career")->Value = 1;
	}
	if (chlocal->Checked ) {
		spQryNote->Parameters->ParamByName("@andan")->Value = 1;
	}
	if (chunconfrim->Checked ) {
		spQryNote->Parameters->ParamByName("@outstorage")->Value = 1;
	}
	if (cbbackinfo->Checked&&editbackinfo->Text!="") {

	}
	if (chsupplier->Checked && cbsupplier->Text != "") {   //�ɹ���Ӧ��
		int supplier;
		try {
			supplier = (int)cbsupplier->Items->Objects[cbsupplier->ItemIndex];
		} catch (...) {
			supplier = -1;
		}
		spQryNote->Parameters->ParamByName("@instorage")->Value = supplier;
	}
	if (chstate->Checked ) {
		 stateaa=1;
		 stateaa = cbstate->ItemIndex ;
		spQryNote->Parameters->ParamByName("@Maxyk")->Value =stateaa+1; ;
	}

	try
	{
		spQryNote->Active = true;
		((TFloatField *)spQryNote->FieldByName("FixedPrice"))->DisplayFormat = Desic;
		((TFloatField *)spQryNote->FieldByName("DiscountedPrice"))->DisplayFormat = Desic ;

		switch (pgcntrlResult->ActivePage->Tag)
		{
		case 6:
			dsrcByNtHeader->DataSet = NULL;
			dsetByNtHeader->Recordset = spQryNote->Recordset;
			dsetByNtHeader->First();
			dsrcByNtHeader->DataSet = dsetByNtHeader;
			break;
		case 7:
			dsrcByNote->DataSet = NULL;
			dsetByNote->Recordset = spQryNote->Recordset;
            dsetByNote->First();
			dsrcByNote->DataSet = dsetByNote;
        	break;
		case 9:
			dsrcByCustomer->DataSet = NULL;
			dsetByCustomer->Recordset = spQryNote->Recordset;

            dsetByCustomer->First();
			dsrcByCustomer->DataSet = dsetByCustomer;
			break;

		case 8:
			dsrcByPress->DataSet = NULL;
			dsetByPress->Recordset = spQryNote->Recordset;

			dsetByPress->First();

			dsrcByPress->DataSet = dsetByPress;
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

void TfrmCQryOderNote::Init(LandInfo* li)
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
	aqclient->Connection=m_con;
	dsetBookstack->Active = true;
	qryItems->Connection = m_con;
	numedtMinPrice->Text = "";
	numedtMaxPrice->Text = "";
	numedtMinAmount->Text = "";
	numedtMaxAmount->Text = "";
	dblkpcbbStorage->KeyValue = m_storageID ;
	chckbxStorage->Checked = true;
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
	if (aq->FieldByName("Master")->AsBoolean)
	{
		dblkpcbbStorage->Enabled = true;
		chckbxStorage->Enabled = true;
	}
	else
	{
		chckbxStorage->Enabled = false;
		sql = "select * from BS_StoToSto where ystgid = " + IntToStr(m_storageID) + " and [order] = 1";
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
	sql = "select ID,Name from CUST_CustomerInfo where type = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger);
		aq->Next();
	}

	sql = "select orderuser,clientid from dbo.C_BS_OrderNoteHeader group by orderuser,clientid";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbusername->AddItem(aq->FieldByName("orderuser")->AsAnsiString ,(TObject*)aq->FieldByName("clientid")->AsInteger);
		aq->Next();
	}

   	delete aq;
	Desic = QueryDesic();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCQryOderNote::chckbxBkstackClick(TObject *Sender)
{
	//
	if (chckbxBkstack->Checked)
	{
    	chckbxStorage->Checked = chckbxBkstack->Checked;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::tlbtnExportClick(TObject *Sender)
{
	//Excel����
	switch (pgcntrlResult->ActivePage->Tag)
	{
	case 6:
		if (dsetByNtHeader->Active && dsetByNtHeader->RecordCount > 0) {
				DbgridToExcel(dbgrdByNtHeader);
			}
		break;
	case 7:
		if (dsetByNote->Active && dsetByNote->RecordCount > 0) {
				DbgridToExcel(dbgrdByNote);
			}
		break;
	case 9:
		if (dsetByCustomer->Active && dsetByCustomer->RecordCount > 0) {
				DbgridToExcel(dbgrdByCustomer);
			}
		break;

	case 8:
		if (dsetByPress->Active && dsetByPress->RecordCount > 0) {
				DbgridToExcel(dbgrdByPress);
			}
		break;
	default:
		break;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TfrmCQryOderNote::DbgridToExcel(TDBGridEh* dbg)
{
	AnsiString temptext,path;

  //	savedlg->FileName = "������ѯ";

	savedlg->FileName = "C������ѯ"+FormatDateTime("yyyy-mm-ddHHMM",Now())+".csv";

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
   Screen->Cursor=crHourGlass;
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
	dbg->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "FixedPrice" || dbg->Columns ->Items [j-1]->FieldName == "DiscountedPrice" ) {
					temptext = temptext + FormatFloat(Desic1,dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsFloat) + ",";
				}
				else
				{
					AnsiString bookname;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					bookname = StringReplace(bookname , '\n',"",TReplaceFlags()<<rfReplaceAll);
                    bookname = StringReplace(bookname , '\r',"",TReplaceFlags()<<rfReplaceAll);
					temptext = temptext + bookname + ",";
				}
			}
		}
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();

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
   Screen->Cursor=crDefault;
	MessageBox(0,"������ϣ�","��ʾ" ,MB_OK);
	return false;

}
//---------------------------------------------------------------------------


void __fastcall TfrmCQryOderNote::tlbtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::edtPressKeyPress(TObject *Sender, wchar_t &Key)
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
			/*else if (edt->Tag == 2)//��Ӧ��
			{
				//��ѯ��Ӧ��
				TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edtPress->Text);
				if (mrOk == frm->ShowModal())
				{
					ClientID = frm->GetSelectID();
					ClientView();
				}
				delete frm;
			}  */
			else
			{

			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCQryOderNote::FormClose(TObject *Sender, TCloseAction &Action)
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



void __fastcall TfrmCQryOderNote::edtBookNameChange(TObject *Sender)
{
	if (edtBookName->Text != "") {
		chckbxBookName->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::edtUserDefNumChange(TObject *Sender)
{
	if (edtUserDefNum->Text != "") {
        chckbxUserDefNum->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::edtISBNChange(TObject *Sender)
{
	if (edtISBN->Text != "") {
        chckbxISBN->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::numedtMinPriceChange(TObject *Sender)
{
	if (numedtMinPrice->Text != "") {
		chckbxPrice->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::numedtMaxPriceChange(TObject *Sender)
{
	if (numedtMaxPrice->Text != "") {
        chckbxPrice->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::numedtMinAmountChange(TObject *Sender)
{
	if (numedtMinAmount->Text != "") {
		chckbxAmount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::numedtMaxAmountChange(TObject *Sender)
{
	if (numedtMaxAmount->Text != "") {
        chckbxAmount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::edtAuthorChange(TObject *Sender)
{
	if (edtAuthor->Text != "") {
        chckbxAuthor->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::edtRemarksChange(TObject *Sender)
{
	if (edtRemarks->Text != "") {
        chckbxRemarks->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::dblkpcbbPressClick(TObject *Sender)
{
	if (dblkpcbbPress->Text != "") {
		chckbxPress->Checked = true;
		edtPress->Text = dsetPress->FieldByName("PresentNum")->AsString ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::dblkpcbbBookstackClick(TObject *Sender)
{
	if (dblkpcbbBookstack->Text != "") {
        chckbxBkstack->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::dblkpcbbBookTypeClick(TObject *Sender)
{
	if (dblkpcbbBookType->Text != "" ) {
        chckbxType->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::dblkpcbbStorageClick(TObject *Sender)
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



void __fastcall TfrmCQryOderNote::cbstaffClick(TObject *Sender)
{
	if (cbstaff->Text != "") {
		chstaff->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::edmindiscountChange(TObject *Sender)
{
	if (edmindiscount->Text != "") {
		chdiscount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::edmaxdiscountChange(TObject *Sender)
{
	if (edmaxdiscount->Text != "") {
    	chdiscount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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

void __fastcall TfrmCQryOderNote::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",m_storageID);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		ClientView();
	}
	delete frm;
}
//---------------------------------------------------------------------------

void TfrmCQryOderNote::ClientView()
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

void __fastcall TfrmCQryOderNote::edtclientChange(TObject *Sender)
{
	if (edtclient->Text != "") {
		chckbxCustomer->Checked = true;
	}
	else
	{
    	chckbxCustomer->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::edtCustomerKeyPress(TObject *Sender, wchar_t &Key)

{
AnsiString sql;
	if (Key == '\r') {
		sql = "select orderuser,clientid from dbo.C_BS_OrderNoteHeader where orderuser like '%"+Trim(edtCustomer->Text)+"%' group by orderuser,clientid  ";
	aqclient->Close();
	aqclient->SQL->Clear();
	aqclient->SQL->Add(sql);
	aqclient->Open();
	while (!aqclient->Eof)
	{
		cbusername->AddItem(aqclient->FieldByName("orderuser")->AsAnsiString ,(TObject*)aqclient->FieldByName("clientid")->AsInteger);
		aqclient->Next();
	}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::SpeedButton1Click(TObject *Sender)
{
	if (GroupBox4->Visible) {
		GroupBox4->Visible = false;
	}
	else
	{
    	GroupBox4->Visible = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::ch1Click(TObject *Sender)
{
	if (ch1->Checked ) {
		dbgrdByNote->Columns->Items[17]->Visible = true;
		dbgrdByNote->Columns->Items[17]->Width = 52;
	}
	else
	{
		dbgrdByNote->Columns->Items[17]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::ch2Click(TObject *Sender)
{
	if (ch2->Checked ) {
		dbgrdByNote->Columns->Items[18]->Visible = true;
		dbgrdByNote->Columns->Items[18]->Width = 57;
	}
	else
	{
		dbgrdByNote->Columns->Items[18]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::ch3Click(TObject *Sender)
{
	if (ch3->Checked ) {
		dbgrdByNote->Columns->Items[19]->Visible = true;
		dbgrdByNote->Columns->Items[19]->Width = 56;
	}
	else
	{
		dbgrdByNote->Columns->Items[19]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::ch4Click(TObject *Sender)
{
	if (ch4->Checked ) {
		dbgrdByNote->Columns->Items[20]->Visible = true;
		dbgrdByNote->Columns->Items[20]->Width = 55;
	}
	else
	{
		dbgrdByNote->Columns->Items[20]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::ch5Click(TObject *Sender)
{
	if (ch5->Checked ) {
		dbgrdByNote->Columns->Items[21]->Visible = true;
		dbgrdByNote->Columns->Items[21]->Width = 57;
	}
	else
	{
		dbgrdByNote->Columns->Items[21]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::ch6Click(TObject *Sender)
{
	if (ch6->Checked ) {
		dbgrdByNote->Columns->Items[22]->Visible = true;
		dbgrdByNote->Columns->Items[22]->Width = 59;
	}
	else
	{
		dbgrdByNote->Columns->Items[22]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::ch7Click(TObject *Sender)
{
	if (ch7->Checked ) {
		dbgrdByNote->Columns->Items[23]->Visible = true;
		dbgrdByNote->Columns->Items[23]->Width = 55;
	}
	else
	{
		dbgrdByNote->Columns->Items[23]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::ch8Click(TObject *Sender)
{
	if (ch8->Checked ) {
		dbgrdByNote->Columns->Items[24]->Visible = true;
		dbgrdByNote->Columns->Items[24]->Width = 56;
	}
	else
	{
		dbgrdByNote->Columns->Items[24]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::dbgrdByNtHeaderDblClick(TObject *Sender)
{
	if (dsetByNtHeader->IsEmpty() ) {
		return;
	}
	if (dsetByNtHeader->RecordCount > 0) {
		TfrmNotedetail *frm = new TfrmNotedetail(Application,dsetByNtHeader->FieldByName("Code")->AsString,7,fcon,0,m_userID);
		frm->ShowModal();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::dbgrdByNtHeaderTitleClick(TColumnEh *Column)
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

void __fastcall TfrmCQryOderNote::dbgrdByNoteTitleClick(TColumnEh *Column)
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


void __fastcall TfrmCQryOderNote::dbgrdByCustomerTitleClick(TColumnEh *Column)
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

void __fastcall TfrmCQryOderNote::dbgrdByBktypeTitleClick(TColumnEh *Column)
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

void __fastcall TfrmCQryOderNote::dbgrdByPressTitleClick(TColumnEh *Column)
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

void __fastcall TfrmCQryOderNote::N1Click(TObject *Sender)
{
	if (dsetByNote->IsEmpty() ) {
		return;                                                                                              //Catalogid
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con ,m_storageID ,dsetByNote->FieldByName("Catalogid")->AsInteger,m_userID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::edsupplierKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
    	TADOQuery *aq = new TADOQuery(this);
		aq->Connection = m_con;
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type = 1 and name like '%" + edsupplier->Text.Trim() + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbsupplier->Clear() ;
		while (!aq->Eof)
		{
			cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger);
			aq->Next();
		}
		aq->First();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCQryOderNote::cbusernameChange(TObject *Sender)
{
 if (cbusername->Text !="") {
  chckbxCustomer->Checked=true;

 }
}
//---------------------------------------------------------------------------
