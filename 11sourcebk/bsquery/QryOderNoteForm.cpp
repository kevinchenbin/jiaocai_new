//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "QryOderNoteForm.h"
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
TfrmQryOderNote *frmQryOderNote;
//---------------------------------------------------------------------------
__fastcall TfrmQryOderNote::TfrmQryOderNote(TComponent* Owner)
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
String TfrmQryOderNote::QueryDesic()
{
	TADOQuery * aq;
   aq = new TADOQuery(this);
   aq->Connection = m_con ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add("select bk from sys_bsset where name ='xiaoshudian'");
   aq->Open();
   Desic1 = aq->FieldByName("bk")->AsAnsiString;
   return "￥###,###,##"+ aq->FieldByName("bk")->AsAnsiString ;
   delete aq;
}

void __fastcall TfrmQryOderNote::tlbtnQryClick(TObject *Sender)
{
	//查询
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
		case 4:
			((TFloatField *)dbgrdByBktype->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByBktype->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			break;
		case 5:
			((TFloatField *)dbgrdByPress->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = Desic;
			((TFloatField *)dbgrdByPress->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = Desic;
			break;
    default:
        ;
	}
}

void TfrmQryOderNote::Query()
{
	long double   TotalMan=0.0000,TotalShi=0.0000;
	int TotalNum=0,totalunrec = 0;
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

	if (chckbxStartTime->Checked && dtedtStart->Text != "") //开始时间
		spQryNote->Parameters->ParamByName("@Start")->Value = dtedtStart->Date;

	if (chckbxEndTime->Checked && dtedtEnd->Text != "") //结束时间
		spQryNote->Parameters->ParamByName("@End")->Value = dtedtEnd->Date;

    if (chckbxBookName->Checked && edtBookName->Text != "") //书名
		spQryNote->Parameters->ParamByName("@Name")->Value = "%" + edtBookName->Text + "%";

	if (chckbxUserDefNum->Checked && edtUserDefNum->Text != "") //自编码
		spQryNote->Parameters->ParamByName("@UserDefCode")->Value = "%" + edtUserDefNum->Text + "%";

	if (chckbxPress->Checked && dblkpcbbPress->Text != "") //出版社
		spQryNote->Parameters->ParamByName("@PressID")->Value = dsetPress->FieldByName("ID")->AsInteger;

	if (chckbxISBN->Checked && edtISBN->Text != "") //ISBN
		spQryNote->Parameters->ParamByName("@ISBN")->Value = "%" + isbn + "%";

	if (chckbxPrice->Checked && numedtMinPrice->Text != "") //定价
		spQryNote->Parameters->ParamByName("@MinPrice")->Value = numedtMinPrice->Value;

	if (chckbxPrice->Checked && numedtMaxPrice->Text != "") //定价
		spQryNote->Parameters->ParamByName("@MaxPrice")->Value = numedtMaxPrice->Value;

	if (chckbxType->Checked && dblkpcbbBookType->Text != "") //书目类型
		spQryNote->Parameters->ParamByName("@BktypeID")->Value = dsetBookType->FieldByName("ID")->AsInteger;

	if (chckbxCustomer->Checked && edtclient->Text != "") //客户
		spQryNote->Parameters->ParamByName("@CustomerID")->Value = ClientID;

	if (chckbxAuthor->Checked && edtAuthor->Text != "") //作者
		spQryNote->Parameters->ParamByName("@Author")->Value = "%" + edtAuthor->Text + "%";

	if (chckbxRemarks->Checked && edtRemarks->Text != "") //备注
		spQryNote->Parameters->ParamByName("@Remarks")->Value = "%" + edtRemarks->Text + "%";

	if (chckbxBkstack->Checked) //库位
		spQryNote->Parameters->ParamByName("@BkstackID")->Value = dsetBookstack->FieldByName("ID")->AsInteger;

	if (chckbxAmount->Checked && numedtMinAmount->Text != "") //库存
		spQryNote->Parameters->ParamByName("@MinAmount")->Value = numedtMinAmount->IntValue;

	if (chckbxAmount->Checked && numedtMaxAmount->Text != "") //库存
		spQryNote->Parameters->ParamByName("@MaxAmount")->Value = numedtMaxAmount->IntValue;

	if (chckbxStorage->Checked) //店
		//spQryNote->Parameters->ParamByName("@StgID")->Value = dsetInit->FieldByName("StorageID")->AsInteger;
		spQryNote->Parameters->ParamByName("@StgID")->Value = dsetStorage->FieldByName("ID")->AsInteger;
    if (chstaff->Checked ) {    //操作员
		spQryNote->Parameters->ParamByName("@staff")->Value = int(cbstaff->Items->Objects[cbstaff->ItemIndex]);
	}
	if (chdiscount->Checked && edmindiscount->Text != "") {   //最小折扣
		spQryNote->Parameters->ParamByName("@mindiscount")->Value = StrToFloat(edmindiscount->Text);
	}
	if (chdiscount->Checked && edmaxdiscount->Text != "") {   //最大折扣
		spQryNote->Parameters->ParamByName("@maxdiscount")->Value =  StrToFloat(edmaxdiscount->Text);
	}

	spQryNote->Parameters->ParamByName("@Bsmode")->Value = 5;
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
	if (chsupplier->Checked && cbsupplier->Text != "") {   //采购供应商
		int supplier;
		try {
			supplier = (int)cbsupplier->Items->Objects[cbsupplier->ItemIndex];
		} catch (...) {
			supplier = -1;
		}
		spQryNote->Parameters->ParamByName("@instorage")->Value = supplier;
	}
	if (chstate->Checked ) {
    	spQryNote->Parameters->ParamByName("@Maxyk")->Value = cbstate->ItemIndex ;
	}

	try
	{
		spQryNote->Active = true;
		((TFloatField *)spQryNote->FieldByName("FixedPrice"))->DisplayFormat = Desic;
		((TFloatField *)spQryNote->FieldByName("DiscountedPrice"))->DisplayFormat = Desic ;

		switch (pgcntrlResult->ActivePage->Tag)
		{
		case 1:
			dsrcByNtHeader->DataSet = NULL;
			dsetByNtHeader->Recordset = spQryNote->Recordset;
			dsetByNtHeader->First();
			dsrcByNtHeader->DataSet = dsetByNtHeader;
			break;
		case 2:
			dsrcByNote->DataSet = NULL;
			dsetByNote->Recordset = spQryNote->Recordset;
            dsetByNote->First();
			dsrcByNote->DataSet = dsetByNote;
        	break;
		case 3:
			dsrcByCustomer->DataSet = NULL;
			dsetByCustomer->Recordset = spQryNote->Recordset;

            dsetByCustomer->First();
			dsrcByCustomer->DataSet = dsetByCustomer;
			break;
		case 4:
			dsrcByBktype->DataSet = NULL;
			dsetByBktype->Recordset = spQryNote->Recordset;

			dsetByBktype->First();

			dsrcByBktype->DataSet = dsetByBktype;
        	break;
		case 5:
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

void TfrmQryOderNote::Init(LandInfo* li)
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

   	delete aq;
	Desic = QueryDesic();
}
//---------------------------------------------------------------------------
void __fastcall TfrmQryOderNote::chckbxBkstackClick(TObject *Sender)
{
	//
	if (chckbxBkstack->Checked)
	{
    	chckbxStorage->Checked = chckbxBkstack->Checked;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::tlbtnExportClick(TObject *Sender)
{
	//Excel导出
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
		if (dsetByCustomer->Active && dsetByCustomer->RecordCount > 0) {
				DbgridToExcel(dbgrdByCustomer);
			}
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
bool __fastcall TfrmQryOderNote::DbgridToExcel(TDBGridEh* dbg)
{
	AnsiString temptext,path;

   //	savedlg->FileName = "订单查询";

	 savedlg->FileName = "B订单查询"+FormatDateTime("yyyy-mm-ddHHMM",Now())+".csv";

	  if (savedlg->Execute())
	{

		  savedlg->FileName=savedlg->FileName;// + "." + Ext;
		  SaveDBGridEhToExportFile(__classid(TDBGridEhExportAsCSV),dbg,savedlg->FileName,true);
		  st = new TStringList();
		  st->LoadFromFile(savedlg->FileName);
		  st->Text = StringReplace(st->Text,";",",",TReplaceFlags()<<rfReplaceAll);
		  st->SaveToFile(savedlg->FileName);
		  String sMsg="文件导出成功！\r\n\r\n"+savedlg->FileName;
		  MessageBox(0,"导出完毕！","提示" ,MB_OK);
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

	temptext = "\n合计,";
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
	MessageBox(0,"导出完毕！","提示" ,MB_OK);
	return false;

}
//---------------------------------------------------------------------------


void __fastcall TfrmQryOderNote::tlbtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::edtPressKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		TCustomEdit* edt = dynamic_cast<TCustomEdit*>(Sender);
		if (edt != NULL)
		{
			if (edt->Tag == 1)//版别
			{
				//查询版别
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
			/*else if (edt->Tag == 2)//供应商
			{
				//查询供应商
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
void __fastcall TfrmQryOderNote::FormClose(TObject *Sender, TCloseAction &Action)
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



void __fastcall TfrmQryOderNote::edtBookNameChange(TObject *Sender)
{
	if (edtBookName->Text != "") {
		chckbxBookName->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::edtUserDefNumChange(TObject *Sender)
{
	if (edtUserDefNum->Text != "") {
        chckbxUserDefNum->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::edtISBNChange(TObject *Sender)
{
	if (edtISBN->Text != "") {
        chckbxISBN->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::numedtMinPriceChange(TObject *Sender)
{
	if (numedtMinPrice->Text != "") {
		chckbxPrice->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::numedtMaxPriceChange(TObject *Sender)
{
	if (numedtMaxPrice->Text != "") {
        chckbxPrice->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::numedtMinAmountChange(TObject *Sender)
{
	if (numedtMinAmount->Text != "") {
		chckbxAmount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::numedtMaxAmountChange(TObject *Sender)
{
	if (numedtMaxAmount->Text != "") {
        chckbxAmount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::edtAuthorChange(TObject *Sender)
{
	if (edtAuthor->Text != "") {
        chckbxAuthor->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::edtRemarksChange(TObject *Sender)
{
	if (edtRemarks->Text != "") {
        chckbxRemarks->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::dblkpcbbPressClick(TObject *Sender)
{
	if (dblkpcbbPress->Text != "") {
		chckbxPress->Checked = true;
		edtPress->Text = dsetPress->FieldByName("PresentNum")->AsString ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::dblkpcbbBookstackClick(TObject *Sender)
{
	if (dblkpcbbBookstack->Text != "") {
        chckbxBkstack->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::dblkpcbbBookTypeClick(TObject *Sender)
{
	if (dblkpcbbBookType->Text != "" ) {
        chckbxType->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::dblkpcbbStorageClick(TObject *Sender)
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



void __fastcall TfrmQryOderNote::cbstaffClick(TObject *Sender)
{
	if (cbstaff->Text != "") {
		chstaff->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::edmindiscountChange(TObject *Sender)
{
	if (edmindiscount->Text != "") {
		chdiscount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::edmaxdiscountChange(TObject *Sender)
{
	if (edmaxdiscount->Text != "") {
    	chdiscount->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F6) {      //导出
		tlbtnExport->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 70 ) {    //查询
		tlbtnQry->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 81 ) {    //退出
		tlbtnExit->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::spselectClientClick(TObject *Sender)
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

void TfrmQryOderNote::ClientView()
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

void __fastcall TfrmQryOderNote::edtclientChange(TObject *Sender)
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

void __fastcall TfrmQryOderNote::edtCustomerKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edtCustomer->Text,m_storageID);
		if (mrOk == frm->ShowModal())
		{
			ClientID = frm->GetSelectID();
			ClientView();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::SpeedButton1Click(TObject *Sender)
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

void __fastcall TfrmQryOderNote::ch1Click(TObject *Sender)
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

void __fastcall TfrmQryOderNote::ch2Click(TObject *Sender)
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

void __fastcall TfrmQryOderNote::ch3Click(TObject *Sender)
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

void __fastcall TfrmQryOderNote::ch4Click(TObject *Sender)
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

void __fastcall TfrmQryOderNote::ch5Click(TObject *Sender)
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

void __fastcall TfrmQryOderNote::ch6Click(TObject *Sender)
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

void __fastcall TfrmQryOderNote::ch7Click(TObject *Sender)
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

void __fastcall TfrmQryOderNote::ch8Click(TObject *Sender)
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

void __fastcall TfrmQryOderNote::dbgrdByNtHeaderDblClick(TObject *Sender)
{
	if (dsetByNtHeader->IsEmpty() ) {
		return;
	}
	if (dsetByNtHeader->RecordCount > 0) {
		TfrmNotedetail *frm = new TfrmNotedetail(Application,dsetByNtHeader->FieldByName("Code")->AsString,4,fcon,0,m_userID);
		frm->ShowModal();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::dbgrdByNtHeaderTitleClick(TColumnEh *Column)
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

void __fastcall TfrmQryOderNote::dbgrdByNoteTitleClick(TColumnEh *Column)
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


void __fastcall TfrmQryOderNote::dbgrdByCustomerTitleClick(TColumnEh *Column)
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

void __fastcall TfrmQryOderNote::dbgrdByBktypeTitleClick(TColumnEh *Column)
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

void __fastcall TfrmQryOderNote::dbgrdByPressTitleClick(TColumnEh *Column)
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

void __fastcall TfrmQryOderNote::N1Click(TObject *Sender)
{
	if (dsetByNote->IsEmpty() ) {
        return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,m_con ,m_storageID ,dsetByNote->FieldByName("Catalogid")->AsInteger,m_userID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQryOderNote::edsupplierKeyPress(TObject *Sender, wchar_t &Key)

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

