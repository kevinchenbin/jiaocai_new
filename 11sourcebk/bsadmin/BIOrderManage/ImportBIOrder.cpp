//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ImportBIOrder.h"
#include "UnitSelectClient.h"
#include "SelectCatalogForm.h"
#include "SetNotesForm.h"
#include "UnitClient.h"
#include "QryNoteCodeForm.h"
#include "..\..\supplier\detailemessage.h"
#include "Addsyslog.h"
#include "NewBookinput.h"
#include "bookQuery.h"
#include "UnitSelectClient.h"
#include "orderExcelImport.h"
#include "UnitClient.h"
#include "NewBookModify.h"
#include "Ordermodify.h"
#include "Unitchongfuorder.h"
#include "Unitorderquery.h"
#include "Unitfindbook.h"
#include "Unitgenhuanselect.h"
#include "NewBookinput1.h"
#include "retailbookup.h"
#include "bookhistory.h"
#include "settypress.h"
#include "Unitclasscode.h"
#include "unitselectbook.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzLabel"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TfrmimptBIorder *frmimptBIorder;
//---------------------------------------------------------------------------
__fastcall TfrmimptBIorder::TfrmimptBIorder(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	m_module = MTOrder;
	ClientID = -1;
	m_catalogSearchMode = 1;
	edtCatalog->MaxLength = 13;
	dtpdate->Date = Date();
	dtpfahuo->Date = Date();
	WindowState = wsMaximized ;
	dgdetail->OnDrawColumnCell=dgdetail1DrawColumnCell;
}
void TfrmimptBIorder::init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	UserID = li->userID ;
	UserName =  li->UserName ;
	StgID = li->storageID ;
	fcon = li->con ;
	query->Connection = li->con;
	querypress->Connection = fcon;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select ID,Name,Master from SYS_StorageInfo where id = " + IntToStr(StgID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	Edit2->Text = aq->FieldByName("ID")->AsString;
	Edit3->Text = aq->FieldByName("Name")->AsString ;
	Master = aq->FieldByName("Master")->AsBoolean ;
	sql = "select orprinttitle,orcontact,ortel,oraddress,orprintbk from sys_printtitle where stgid = " + IntToStr(m_storageID);
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	printbk = query->FieldByName("orprintbk")->AsAnsiString ;
	printtitle = query->FieldByName("orprinttitle")->AsAnsiString ;
	contact = query->FieldByName("orcontact")->AsAnsiString ;
	tel = query->FieldByName("ortel")->AsAnsiString ;
	address = query->FieldByName("oraddress")->AsAnsiString ;

	delete aq;
	aqupdatehead->Connection = fcon;
	try
	{
		aqhd->Connection = fcon;
		aqhd->Active = false;
		aqhd->Parameters->ParamByName("stgid")->Value = StgID;
		aqhd->Parameters->ParamByName("type")->Value = type;
		aqhd->Active = true;
	}
	catch(Exception &E)
	{
	  	ShowMessage(E.Message);
	}

	//SAddHead->Connection = fcon;
	ReadyDate();
	//RefreshHead();
	if (type == 0) {
		//cbtype->ItemIndex = 0;
		BtnNew->Click();
		/*if (!Master) {
			cbtype->ItemIndex = 1;
            BtnImport->Enabled = false;
		}   */
	}
	else if (type == 2) {
		//dbn->BtnClick(3);
		aqhd->Last();
		RefreshHead(aqhd->FieldByName("ID")->AsInteger );
		BtnNew->Visible = false;
		Label1->Caption = "网 上 订 单";
		cbtype->ItemIndex = 1;
	}
	edclient->SetFocus();
}
void TfrmimptBIorder::init(LandInfo*li,AnsiString Danhao)
{
    TfrmMDIChild::Init(li);
	type = 2;
	UserID = li->userID ;
	UserName =  li->UserName ;
	StgID = li->storageID ;
	fcon = li->con ;
	querypress->Connection = fcon;
	query->Connection =fcon;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select ID,Name,Master from SYS_StorageInfo where id = " + IntToStr(StgID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	Edit2->Text = aq->FieldByName("ID")->AsString;
	Edit3->Text = aq->FieldByName("Name")->AsString ;
	Master = aq->FieldByName("Master")->AsBoolean ;

	sql = "select orprinttitle,orcontact,ortel,oraddress,orprintbk from sys_printtitle where stgid = " + IntToStr(m_storageID);
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	printbk = query->FieldByName("orprintbk")->AsAnsiString ;
	printtitle = query->FieldByName("orprinttitle")->AsAnsiString ;
	contact = query->FieldByName("orcontact")->AsAnsiString ;
	tel = query->FieldByName("ortel")->AsAnsiString ;
	address = query->FieldByName("oraddress")->AsAnsiString ;


	aqupdatehead->Connection = fcon;
	if (StgID == 0) {
		cbtype->ItemIndex = 1;
		cbtype->Enabled = false;
	}
	try
	{
		sql = " select A.*,S.ID as Sid,C.Name as Clientname,S.Name as StgName,U.ID,U.name as OpName from BS_OrderNoteHeader A "
			   " left join SYS_StorageInfo S ON A.stgID = S.ID "
			   " left join SYS_User U ON A.operatorID = U.ID left join CUST_customerinfo C ON C.ID = A.vendorID ";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
	}
	catch(Exception &E)
	{
		ShowMessage(E.Message);
	}
	//SAddHead->Connection = fcon;
	ReadyDate();
   //	RefreshHead();
	if (Danhao == "") {
		return;
	}
	TLocateOptions Opts;
	Opts.Clear();
	Opts << loPartialKey;

	if(aq->Locate("OrderNtCode", Variant(Danhao), Opts))
	{
		RefreshHead(aq->FieldByName("ID")->AsInteger );
	}
  //	Label1->Caption = "网 上 订 单";
	BtnNew->Visible = false;
	//edclient->SetFocus();
		delete aq;
}
void TfrmimptBIorder::ReadyDate()
{
	AnsiString sql = "select * from SYS_StaffInfo ";// where ID = " + IntToStr((int)(ccbclient->Items->Objects[ccbclient->ItemIndex])) ;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbvendor->Items->Clear();
	while(!aq->Eof)
	{
	   cbvendor->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger);
	   aq->Next();
	}
	sql = "select ID,Name from CUST_CustomerInfo where type in(2,3) order by name";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbclient->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}

	sql = "select value from sys_bsset where name = 'lastorderdiscount'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
    lastdiscount = aq->FieldByName("value")->AsBoolean ;

	sql = "select value,bk from sys_bsset where name = 'chongfuordertishi'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	ordertishi = aq->FieldByName("value")->AsBoolean ;
	month = aq->FieldByName("bk")->AsString ;

	sql = "select value from sys_bsset where name = 'orderfind'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	orderfind = aq->FieldByName("value")->AsBoolean ;

	sql = "select value from sys_bsset where name = 'orderchange'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	orderchange = aq->FieldByName("value")->AsBoolean ;

	delete aq;
	ClientID = 1;

	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)1);

}
void TfrmimptBIorder::AddNewHead()
{
	int ret;
	adospaddhead->Connection = fcon;
	adospaddhead->Parameters->ParamByName("@CustomerID")->Value  = 1;
	adospaddhead->Parameters->ParamByName("@type")->Value  = 0;
	adospaddhead->Parameters->ParamByName("@Bsmode")->Value  = 4;
	adospaddhead->Parameters->ParamByName("@OperatorID")->Value  = UserID ;
	adospaddhead->Parameters->ParamByName("@StgID")->Value  = StgID ;
	adospaddhead->ExecProc();
	ret =   adospaddhead->Parameters->ParamByName("@RETURN_VALUE")->Value;
	if (ret < 0 ) {
		MessageBox(0,"添加订单错误！","提示",MB_ICONASTERISK);
	}else
	{
	   headid = ret;
	   RefreshHead(headid);
	   aqorderdetail->Active = false;
	   aqorderdetail->Parameters->ParamByName("ID")->Value = ret ;
	   aqorderdetail->Connection = fcon;
	   aqorderdetail->Active = true;
	   cbclient->Enabled = true;
	   SpeedButton2->Enabled = true;
	   aqhd->Active = false;
	   aqhd->Active = true;
	   logmessage = "添加一般订单" + aqupdatehead->FieldByName("OrderNtCode")->AsString ;
	   AddEvent(1,"一般订单窗口",UserID,StgID,logmessage,fcon);
	}
   // adospaddhead->Last();
}
AnsiString TfrmimptBIorder::GetField(AnsiString sql,AnsiString Field)
{
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	return	aq->FieldByName(Field)->AsAnsiString ;
	delete aq;
}
//---------------------------------------------------------------------------
void TfrmimptBIorder::ExecSQL(AnsiString sql)
{  	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}
//---------------------------------------------------------------------------
BOOL TfrmimptBIorder::UpdateHead()
{
	if (!aqupdatehead->Active) {
		  return false;
	}
	if (edtclient->Text == "" ) {
		MessageBoxA(0,"请选择客户","提示",MB_ICONEXCLAMATION);
		return false;
	}

	aqupdatehead->Edit();
	aqupdatehead->FieldByName("state")->AsInteger = cbstate->ItemIndex;
	aqupdatehead ->FieldByName("type")->AsInteger = 	cbtype->ItemIndex ;
	aqupdatehead->FieldByName("hdtime")->AsDateTime = dtpdate->Date ;
	aqupdatehead->FieldByName("arravaldate")->AsDateTime = dtpfahuo->Date ;
	aqupdatehead->FieldByName("Remarks")->AsAnsiString  = membk->Text ;

	if (cbvendor->ItemIndex == -1) {
	   aqupdatehead->FieldByName("staffid")->AsInteger = 0;
	} else
	{
	  aqupdatehead->FieldByName("staffid")->AsInteger = (int)(cbvendor->Items->Objects[cbvendor->ItemIndex]);
	}
	if (ClientID != -1 )
	{
	   aqupdatehead->FieldByName("vendorID")->AsInteger =  ClientID;
	}
	aqupdatehead->UpdateBatch(arCurrent);

	if (dbeditdanhao->Text == "0") {
    	AnsiString sql;
		sql = "update BS_OrderNoteHeader set OrderNtCode = dbo.UF_BS_BuildNtCode(" + IntToStr(m_storageID) + ", getdate(), 4,0) where id = " + aqupdatehead->FieldByName("id")->AsAnsiString ;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
	}
	RefreshHead(aqupdatehead->FieldByName("id")->AsInteger);
	return true;
	//dbeditdanhao->Text = aqupdatehead->FieldByName("OrderNtCode")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::BtnNewClick(TObject *Sender)
{
	DelInvalidNtHeader();
	edclientview();
	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)1);
	ClientID = 1;
	dbn->Enabled = false;
	if (!Master) {
		cbtype->ItemIndex = 1;
        BtnImport->Enabled = false;
	}
	AddNewHead();
	if (!Master) {
		cbtype->ItemIndex = 1;
        BtnImport->Enabled = false;
	}
	//dbn->BtnClick(3);   //最后一个
	edtCatalog->Text = "";
	editamount->Text = "0";
	editdiscount->Text = "100";
	editdetailbk->Text = "";
	cbtype->Enabled = true;
}
//---------------------------------------------------------------------------
void TfrmimptBIorder::RefreshHead()
{
	int vendor;
	AnsiString sql;
	sql = "select A.*,S.ID,C.Name as Clientname,S.Name as StgName,U.ID,U.name as OpName from BS_OrderNoteHeader A "
			"left join SYS_StorageInfo S ON A.stgID = S.ID "
			"left join SYS_User U ON A.operatorID = U.ID "
			"left join CUST_customerinfo C ON C.ID = A.vendorID where A.StgID = " + IntToStr(StgID) + " and A.type = " + IntToStr(type) ;
	aqupdatehead->Close();
	aqupdatehead->SQL->Clear();
	aqupdatehead->SQL->Add(sql);
	aqupdatehead->Open();
	((TFloatField *)dshead->DataSet->FieldByName("addcosts"))->DisplayFormat = "￥0.00";
	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aqupdatehead->FieldByName("vendorID")->AsInteger );
	ClientID = aqupdatehead->FieldByName("vendorID")->AsInteger;
	cbstate->ItemIndex = aqupdatehead->FieldByName("state")->AsInteger ;
	cbtype->ItemIndex = aqupdatehead ->FieldByName("type")->AsInteger ;
	dtpdate->Date = aqupdatehead->FieldByName("hdtime")->AsDateTime ;
	dtpfahuo->Date  = aqupdatehead->FieldByName("arravaldate")->AsDateTime ;
	vendor = aqupdatehead->FieldByName("staffid")->AsInteger;
	lblOpName->Caption =  aqupdatehead->FieldByName("OpName")->AsString;
	membk->Text =  aqupdatehead->FieldByName("Remarks")->AsString;
	for (int i =0; i < cbvendor->Items->Count ; i++) {
	  if ((int)(cbvendor->Items->Objects[i])== vendor) {
		  cbvendor->ItemIndex = i;
		  break;
	  }
	}         //更新明细
	ClientView();
	RefreshDetail();

	if (aqupdatehead->FieldByName("shenheistate")->AsInteger == 1) {
		BtnOK1->Enabled = false;
		BtnCancel->Enabled = true;
		BtnOK->Enabled = false;
		BtnProperties->Enabled = false;
		BtnDelete->Enabled = false;
		BtnChangeOptions->Enabled = false;
		SpeedButton1->Visible = true;
		edtCatalog->Enabled = false;
		editamount->Enabled = false;
		editdiscount->Enabled = false;
		edqikan->Enabled = false;
		//GroupBox2->Enabled = false;
	}
	else
	{
		BtnOK1->Enabled = true;
		BtnCancel->Enabled = false;
		BtnOK->Enabled = true;
		BtnProperties->Enabled = true;
		BtnDelete->Enabled = true;
		BtnChangeOptions->Enabled = true;
		SpeedButton1->Visible = false;
		edtCatalog->Enabled = true;
		editamount->Enabled = true;
		editdiscount->Enabled = true;
		edqikan->Enabled = true;
		//GroupBox2->Enabled = true;
	}
	if (cbtype->Text == "内部订单") {
		if (Master) {
			BtnLastRecord->Enabled = true;
		}
		else
		{
			BtnLastRecord->Enabled = false;
		}
		dgdetail->Columns->Items[21]->Field = aqorderdetail->FieldByName("prostate");
	}
	else
	{
		BtnLastRecord->Enabled = false;
		dgdetail->Columns->Items[21]->Field = aqorderdetail->FieldByName("needprocurenum");
	}
}
//---------------------------------------------------------------------------
void TfrmimptBIorder::RefreshHead(AnsiString headerCode)
{
    int vendor;
	edclientview();
	AnsiString sql;
	sql = "select A.*,S.ID,C.Name as Clientname,S.Name as StgName,U.ID,U.name as OpName from BS_OrderNoteHeader A "
			"left join SYS_StorageInfo S ON A.stgID = S.ID "
			"left join SYS_User U ON A.operatorID = U.ID "
			"left join CUST_customerinfo C ON C.ID = A.vendorID where A.orderNtCode = " + headerCode + " and A.type =1 ";
	aqupdatehead->Close();
	aqupdatehead->SQL->Clear();
	aqupdatehead->SQL->Add(sql);
	aqupdatehead->Open();
	((TFloatField *)dshead->DataSet->FieldByName("addcosts"))->DisplayFormat = "￥0.00";
	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aqupdatehead->FieldByName("vendorID")->AsInteger );
    ClientID = aqupdatehead->FieldByName("vendorID")->AsInteger;
	cbstate->ItemIndex = aqupdatehead->FieldByName("state")->AsInteger ;
	cbtype->ItemIndex = aqupdatehead ->FieldByName("type")->AsInteger ;
	dtpdate->Date = aqupdatehead->FieldByName("hdtime")->AsDateTime ;
	dtpfahuo->Date  = aqupdatehead->FieldByName("arravaldate")->AsDateTime ;
	vendor = aqupdatehead->FieldByName("staffid")->AsInteger;
	lblOpName->Caption =  aqupdatehead->FieldByName("OpName")->AsString;
	membk->Text =  aqupdatehead->FieldByName("Remarks")->AsString;
	for (int i =0; i < cbvendor->Items->Count ; i++) {
	  if ((int)(cbvendor->Items->Objects[i])== vendor) {
		  cbvendor->ItemIndex = i;
		  break;
	  }
	}         //更新明细

	ClientView();
	RefreshDetail();
	if (aqupdatehead->FieldByName("shenheistate")->AsInteger == 1) {
		BtnOK1->Enabled = false;
		BtnCancel->Enabled = true;
		BtnOK->Enabled = false;
		BtnProperties->Enabled = false;
		BtnDelete->Enabled = false;
		BtnChangeOptions->Enabled = false;
		SpeedButton1->Visible = true;
		edtCatalog->Enabled = false;
		editamount->Enabled = false;
		editdiscount->Enabled = false;
		edqikan->Enabled = false;
	   //	GroupBox2->Enabled = false;
	  //	cbtype->Enabled = false;
	}
	else
	{
		BtnOK1->Enabled = true;
		BtnCancel->Enabled = false;
		BtnOK->Enabled = true;
		BtnProperties->Enabled = true;
		BtnDelete->Enabled = true;
		BtnChangeOptions->Enabled = true;
		SpeedButton1->Visible = false;
		edtCatalog->Enabled = true;
		editamount->Enabled = true;
		editdiscount->Enabled = true;
		edqikan->Enabled = true;
	  //	GroupBox2->Enabled = true;
	  //	cbtype->Enabled = false;
	}
	if (cbtype->Text == "内部订单") {
		if (Master) {
			BtnLastRecord->Enabled = true;
		}
		else
		{
			BtnLastRecord->Enabled = false;
		}
		dgdetail->Columns->Items[21]->Field = aqorderdetail->FieldByName("prostate");
	}
	else
	{
		BtnLastRecord->Enabled = false;
		dgdetail->Columns->Items[21]->Field = aqorderdetail->FieldByName("needprocurenum");
	}
}
void TfrmimptBIorder::RefreshHead(int headerid)
{
	int vendor;
	edclientview();
	AnsiString sql;
	sql = "select A.*,S.ID,C.Name as Clientname,S.Name as StgName,U.ID,U.name as OpName from BS_OrderNoteHeader A "
			"left join SYS_StorageInfo S ON A.stgID = S.ID "
			"left join SYS_User U ON A.operatorID = U.ID "
			"left join CUST_customerinfo C ON C.ID = A.vendorID where A.id = " + IntToStr(headerid) ;
	aqupdatehead->Close();
	aqupdatehead->SQL->Clear();
	aqupdatehead->SQL->Add(sql);
	aqupdatehead->Open();
	((TFloatField *)dshead->DataSet->FieldByName("addcosts"))->DisplayFormat = "￥0.00";
	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aqupdatehead->FieldByName("vendorID")->AsInteger );
    ClientID = aqupdatehead->FieldByName("vendorID")->AsInteger;
	cbstate->ItemIndex = aqupdatehead->FieldByName("state")->AsInteger ;
	cbtype->ItemIndex = aqupdatehead ->FieldByName("type")->AsInteger ;
	dtpdate->Date = aqupdatehead->FieldByName("hdtime")->AsDateTime ;
	dtpfahuo->Date  = aqupdatehead->FieldByName("arravaldate")->AsDateTime ;
	vendor = aqupdatehead->FieldByName("staffid")->AsInteger;
	lblOpName->Caption =  aqupdatehead->FieldByName("OpName")->AsString;
	membk->Text =  aqupdatehead->FieldByName("Remarks")->AsString;
	for (int i =0; i < cbvendor->Items->Count ; i++) {
	  if ((int)(cbvendor->Items->Objects[i])== vendor) {
		  cbvendor->ItemIndex = i;
		  break;
	  }
	}         //更新明细

	ClientView();
	RefreshDetail();
	if (aqupdatehead->FieldByName("shenheistate")->AsInteger == 1) {
		BtnOK1->Enabled = false;
		BtnCancel->Enabled = true;
		BtnOK->Enabled = false;
		BtnProperties->Enabled = false;
		BtnDelete->Enabled = false;
		BtnChangeOptions->Enabled = false;
		SpeedButton1->Visible = true;
		edtCatalog->Enabled = false;
		editamount->Enabled = false;
		editdiscount->Enabled = false;
		edqikan->Enabled = false;
	  //	GroupBox2->Enabled = false;
	   //	cbtype->Enabled = false; //订单类型不能改
	}
	else
	{
		BtnOK1->Enabled = true;
		BtnCancel->Enabled = false;
		BtnOK->Enabled = true;
		BtnProperties->Enabled = true;
		BtnDelete->Enabled = true;
		BtnChangeOptions->Enabled = true;
		SpeedButton1->Visible = false;
		edtCatalog->Enabled = true;
		editamount->Enabled = true;
		editdiscount->Enabled = true;
		edqikan->Enabled = true;
	  //	GroupBox2->Enabled = true;
	   //	cbtype->Enabled = false;
	}
	if (cbtype->Text == "内部订单") {
		if (Master) {
			BtnLastRecord->Enabled = true;
		}
		else
		{
			BtnLastRecord->Enabled = false;
		}
		dgdetail->Columns->Items[21]->Field = aqorderdetail->FieldByName("prostate");
	}
	else
	{
		BtnLastRecord->Enabled = false;
		dgdetail->Columns->Items[21]->Field = aqorderdetail->FieldByName("needprocurenum");
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::BtnOKClick(TObject *Sender)
{
	if (!GroupBox1->Enabled) {
		return;
	}
	try
	{
		HeaderRec = aqupdatehead->RecNo;
		if (!UpdateHead())
		{
			return ;
	   	}
	}
	catch(...)
	{
	   MessageBoxA(0,"保存失败，请重试!","警告",MB_ICONEXCLAMATION);
       return;
	}
	//MessageBoxA(0,"保存成功!","提示",MB_ICONWARNING);
	//GroupBox1->Enabled = false;

	edclient->Enabled = false;
	edtclient->Enabled = false;
	spselectClient->Enabled = false;
	SpeedButton2->Enabled = false;
	//dbeditaddcost->Enabled = false;
	dtpdate->Enabled = false;
	dtpfahuo->Enabled = false;
	//membk->Enabled = false;

	cbtype->Enabled = false;
	GroupBox2->Enabled = true;
	edtCatalog->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::dbnClick(TObject *Sender, TNavigateBtn Button)
{
	DelInvalidNtHeader();
	edclientview();
	int  vendor;

	RefreshHead(aqhd->FieldByName("ID")->AsInteger );
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N1Click(TObject *Sender)
{
		lblCatalog->Caption = "书号";
		m_catalogSearchMode=1;
		if (chqikan->Checked ) {
			edtCatalog->MaxLength = 15;
		}
		else
		{
			edtCatalog->MaxLength = 13;
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码";
	m_catalogSearchMode=2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名";
	m_catalogSearchMode=3;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode=6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	/*if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}

	if (Key == '\r')
	{
			if (edtCatalog->Text == "") {
            	ChangeCatalogSearchMode();
			}
			else
			{
				float price;
				if (m_catalogSearchMode == 6) {
				try {
						price = StrToFloat(edtCatalog->Text.Trim());
					} catch (...) {
						MessageBox(0,"请输入正确的定价！","提示" ,MB_ICONEXCLAMATION);
						return;
					}
				}
				if (chqikan->Checked && m_catalogSearchMode != 1) {
					edqikan->SetFocus();
					return;
				}
				if (m_catalogSearchMode == 1 && chqikan->Checked) {
					if (edtCatalog->Text.Length() == 15 ) {
						edqikan->Text = edtCatalog->Text.SubString(14,2);
						edtCatalog->Text = edtCatalog->Text.SubString(0,13);
					}
					else
					{
                    	edqikan->SetFocus();
						return;
					}
				}

				TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,fcon);
					LandInfo li;
					li.app = Application;
					li.con = fcon;
					li.userID = UserID ;
					li.storageID = StgID ;
					frm->Init(&li);
					frm->DoModalType = 4;
					//frm->order  = this;
					frm->qikan = chqikan->Checked ;
					frm->qikanhao = edqikan->Text ;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					if (mrOk == frm->ShowModal())
					{
						int supplierID = -1,catalogID = -1;
						if (frm->SelectAll) {

							 for (int i = 0; i < frm->lengthint  ; i++) {
								 if (chongfutishi(frm->BkcatalogiD[i])) {
									AddNote(supplierID,frm->BkcatalogiD[i]);
								 }
							 }

						}else
						{
							frm->GetSelectResult(supplierID, catalogID);

							if (catalogID >= 0)
							{
								TLocateOptions   Opts;
								Opts.Clear();
								Opts   <<   loPartialKey;
								String   str   = AnsiString(catalogID);
								if ( !aqorderdetail->Locate("bkcatalogid",str,Opts))
								{
									if (chongfutishi(catalogID)) {
										AddNote(-1, catalogID);
										editamount->Enabled = true;
										editdiscount->Enabled = true;
										edtCatalog->Text  = "";
										edqikan->Text = "";

										if (chfoceset->Checked) {
											if (chfsamount->Checked ) {
												Perform(WM_NEXTDLGCTL, 0, 0);
											}
											else if (chfsdiscount->Checked ) {
												editdiscount->SetFocus();
											}
											else if (chfsluru->Checked) {
												edtCatalog->SetFocus();
											}
										}
										else
										{
											Perform(WM_NEXTDLGCTL, 0, 0);
										}
									}
									else
									{
										edtCatalog->Text  = "";
										edqikan->Text = "";
										edtCatalog->SetFocus();
									}
								}
								else
								{
									MessageBox(0,"有相同记录请核实！","提示" ,MB_ICONEXCLAMATION);
									dgdetail->SetFocus();
									dgdetail->SelectedRows->CurrentRowSelected = true;
									edtCatalog->Text  = "";
									edqikan->Text = "";
									editamount->SetFocus();
								}
							}
						}
					}
					else
					{
						if (!frm->findbook) {     //产生新书
										//新书目
									if (aqupdatehead->Active && aqupdatehead->RecordCount >= 1)
									{
									   Tfrmnewbook1 *frma = new Tfrmnewbook1(Application,fcon);
									   //frma->BIorder = this;
									   frma->modle = 4;
									   //frma->qikan = chqikan->Checked ;
									   if (chqikan->Checked) {
											frma->cbsaletype->Text = "期刊";
											frma->cbsaletypeChange(this);
											frma->editqikanmao->Text =edtCatalog->Text + edqikan->Text;
											PostMessage(frma->editqikanmao->Handle, WM_KEYDOWN,VK_RETURN,0);
									   }
									   else
									   {
											frma->editcode->Text = edtCatalog->Text ;
											PostMessage(frma->editcode->Handle, WM_KEYDOWN,VK_RETURN,0);
									   }
									   if (mbOK == frma->ShowModal())
									   {

									   }
									   delete frma;
									   editamount->SetFocus();
									}

						}
					}
					delete frm;
			}
	}   */
}



void TfrmimptBIorder::ChangeCatalogSearchMode()
{
if (m_catalogSearchMode==3) {
		m_catalogSearchMode=5;
	}else
	{
	m_catalogSearchMode++;  }
	if (m_catalogSearchMode >= 7)
	{
		m_catalogSearchMode = 1;
	}

	switch (m_catalogSearchMode)
	{
	case 1:
		if (chqikan->Checked ) {
			edtCatalog->MaxLength = 15;
		}
		else
		{
			edtCatalog->MaxLength = 13;
		}

		lblCatalog->Caption = "书号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "自编码";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "书名";
		break;
	case 5:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "作者";
		break;
	case 6:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "定价";
		break;
    default:
        break;
	}
}


void TfrmimptBIorder::AddNote(int SupplierID,int CatalogID)
{
   if (!aqupdatehead->Active) {
	   return;
   }
   TLocateOptions   Opts;
   Opts.Clear();
   Opts   <<   loPartialKey;
   String   str   = AnsiString(CatalogID);
   if ( !aqorderdetail->Locate("bkcatalogid",str,Opts))
   {
    editamount->Text = "0";
	editdiscount->Text = "100";
	editdetailbk->Text = "";
	aqorderdetail->Append();
	AnsiString sql;
	if (lastdiscount) {

		sql = "select top 1 BS_OrderNote.discount from BS_OrderNote left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id where BS_OrderNote.BkcatalogID = " + IntToStr(CatalogID) + " and BS_OrderNoteHeader.VendorID = " + IntToStr(ClientID) + " and BS_OrderNote.state = 0 order by BS_OrderNote.id desc";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->RecordCount > 0) {
			aqorderdetail->FieldByName("Discount")->AsFloat = query->FieldByName("discount")->AsFloat ;
			editdiscount->Text = query->FieldByName("discount")->AsAnsiString ;
		}
	}

	aqorderdetail->FieldByName("OrderNtHeaderID")->AsInteger = aqupdatehead->FieldByName("ID")->AsInteger ;
	aqorderdetail->FieldByName("bkcatalogid")->AsInteger = CatalogID;
	aqorderdetail->UpdateBatch(arCurrent);
	RefreshDetail();
	//aqorderdetail->Last();

	sql = " select sum(amount) as stockamount from STK_BookInfo where BkcatalogID ="+IntToStr(CatalogID)+" and amount > 0";
	if ( GetField(sql,"stockamount")=="")
	{
		editstockamount->Text = "0";
	}else
	{
		editstockamount->Text = GetField(sql,"stockamount");
	}
   }
   else
   {

   }
}

//---------------------------------------------------------------------------

void TfrmimptBIorder::RefreshDetail()
{
	/*querypress->Active = false;
	querypress->Parameters->ParamByName("ID")->Value = aqupdatehead->FieldByName("ID")->AsInteger ;
   	querypress->Active = true;
	edpress->Text = querypress->FieldByName("presscount")->AsAnsiString ;  */
	TLocateOptions Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str;
	if (!aqorderdetail->IsEmpty() ) {
		str = aqorderdetail->FieldByName("id")->AsAnsiString ;
	}

	aqorderdetail->Active = false;
	aqorderdetail->Parameters->ParamByName("ID")->Value = aqupdatehead->FieldByName("ID")->AsInteger ;
	aqorderdetail->Connection = fcon;
	aqorderdetail->Active = true;
	if (str != "" && str != NULL) {
    	try {
			aqorderdetail->Locate("id",str,Opts);
		} catch (...) {
		}
	}

   if (aqorderdetail->RecordCount > 0) {
		GroupBox2->Enabled = true;
		//GroupBox1->Enabled = false;
		edclient->Enabled = false;
		edtclient->Enabled = false;
		spselectClient->Enabled = false;
		SpeedButton2->Enabled = false;
		//dbeditaddcost->Enabled = false;
		dtpdate->Enabled = false;
		dtpfahuo->Enabled = false;
		//membk->Enabled = false;

		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "0.00%";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "￥0.00";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("fixedPrice"))->DisplayFormat = "￥###,###,##0.00";
		((TFloatField *)dgdetail->DataSource->DataSet->FieldByName("Discountedprice"))->DisplayFormat = "￥###,###,##0.00";
	}
	else
	{
		GroupBox2->Enabled = false;
		GroupBox1->Enabled = true;

		edclient->Enabled = true;
		edtclient->Enabled = true;
		spselectClient->Enabled = true;
		SpeedButton2->Enabled = true;
		dbeditaddcost->Enabled = true;
		dtpdate->Enabled = true;
		dtpfahuo->Enabled = true;
		membk->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::editamountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
	 if (!aqupdatehead->Active) {
	   return;
   }
	    AnsiString sql;
		TLocateOptions   Opts;
		Opts.Clear();
		Opts   <<   loPartialKey;
		AnsiString id;
		id = aqorderdetail->FieldByName("id")->AsString;
		//aqorderdetail->Locate("bkcatalogid",bkcatalogid,Opts);


	   aqorderdetail->Edit() ;
	   aqorderdetail->FieldByName("amount")->AsInteger = StrToInt(editamount->Text.Trim()) ;
	   aqorderdetail->UpdateBatch(arCurrent);
	   //aqupdatehead->Active = false;
	   //aqupdatehead->Active = true;
	   RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );

	   aqorderdetail->Locate("id",id,Opts);

	   if (chfoceset->Checked) {
			if (chfsdiscount->Checked) {
				Perform(WM_NEXTDLGCTL, 0, 0);
			}
			else if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!aqorderdetail->Eof) {
					dgdetail->SetFocus();
					aqorderdetail->Next();
					dgdetail->SelectedRows->CurrentRowSelected = true;
					editamount->SetFocus();
				}
			}
		}
		else
		{
			Perform(WM_NEXTDLGCTL, 0, 0);
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::editdiscountKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
	if (Key == VK_RETURN) {
	 if (!aqupdatehead->Active) {
	   return;
   }
       AnsiString sql;
		TLocateOptions   Opts;
		Opts.Clear();
		Opts   <<   loPartialKey;
		AnsiString bkcatalogid;
		bkcatalogid = aqorderdetail->FieldByName("bkcatalogid")->AsString;
		//aqorderdetail->Locate("bkcatalogid",bkcatalogid,Opts);
	   aqorderdetail->Edit() ;
	   try {
			aqorderdetail->FieldByName("Discount")->AsFloat =  StrToFloat(editdiscount->Text);
	   } catch (...) {
			MessageBoxA(0,"请输入正确的折扣！","提示",MB_ICONERROR);
			return;
	   }
	   aqorderdetail->UpdateBatch(arCurrent);
	   //aqupdatehead->Active = false;
	   //aqupdatehead->Active = true;
	   RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );

	   aqorderdetail->Locate("bkcatalogid",bkcatalogid,Opts);

	   if (chfoceset->Checked) {
			if (chfsluru->Checked) {
				edtCatalog->SetFocus();
			}
			else if (chfsamount->Checked) {
				if (!aqorderdetail->Eof) {
					dgdetail->SetFocus();
					aqorderdetail->Next();
					dgdetail->SelectedRows->CurrentRowSelected = true;
					editamount->SetFocus();
				}
			}
			else if (chfsdiscount->Checked) {
				if (!aqorderdetail->Eof) {
					dgdetail->SetFocus();
					aqorderdetail->Next();
					dgdetail->SelectedRows->CurrentRowSelected = true;
					editdiscount->SetFocus();
				}
			}
		}
		else
		{
			edtCatalog->SetFocus();
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::editdetailbkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		if (aqupdatehead->IsEmpty() ) {
			return;
		}
		if (aqorderdetail->IsEmpty() ) {
			return;
		}
		aqorderdetail->Edit() ;
		aqorderdetail->FieldByName("bk")->AsAnsiString  = editdetailbk->Text ;
		aqorderdetail->UpdateBatch(arCurrent);
		if (edtCatalog->Enabled ) {
			edtCatalog->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmimptBIorder::BtnDeleteClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
	 return;
   }
  if (MessageBoxA(0,"确认要删除吗？","提示",MB_ICONQUESTION)==1)
  {
	//aqorderdetail->Edit();
	//aqorderdetail->Delete();
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
        aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
		logmessage = "删除订单" + aqupdatehead->FieldByName("OrderNtCode")->AsString + "的书目《" + aqorderdetail->FieldByName("bookname")->AsString + "》";
		AddEvent(1,"一般订单窗口",UserID,StgID,logmessage,fcon);
		AnsiString sql = "delete from BS_OrderNote where id = " + aqorderdetail->FieldByName("id")->AsString ;

		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
	}

	delete aq;
	aqorderdetail->Active = false;
	aqorderdetail->Active = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::BtnChangeOptionsClick(TObject *Sender)
{
			if (aqorderdetail->IsEmpty() ) {
            	return;
			}
			if (dgdetail->SelectedRows->Count == 0 || dgdetail->SelectedRows->Count == 1) {
				for (int i = 1; i <= aqorderdetail->RecordCount ; i++) {
					dgdetail->DataSource->DataSet->RecNo = i;
					dgdetail->SelectedRows->CurrentRowSelected = true;
				}
			}
			TfrmSetNotes* frm = new TfrmSetNotes(this);
			frm->ChangeBsmode(1);
			if (frm->ShowModal() == mrOk)
			{
				int amount = 0;
				float discount = 0;
				bool bsetAmount = frm->GetAmount(amount);
				bool bsetDiscount = frm->GetDiscount(discount);
				if (bsetAmount && bsetDiscount)
				{
					BatchSetNotes(amount, discount, 1);
				}
				else if (bsetAmount && !bsetDiscount)
				{
					BatchSetNotes(amount, discount, 2);
				}
				else if (!bsetAmount && bsetDiscount)
				{
                	BatchSetNotes(amount, discount, 3);
				}
				//RefreshDetail();
				RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );
			}
}
void TfrmimptBIorder::BatchSetNotes(int amount, float discount, int mode)
{
		 if (aqorderdetail->IsEmpty() ) {
			 return;
		   }

		switch(mode)
		{
		case 1://两者均更新

			 for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
				aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
				aqorderdetail->Edit();
				aqorderdetail->FieldByName("amount")->AsInteger = amount;
				aqorderdetail->FieldByName("Discount")->AsFloat  = discount;
                aqorderdetail->UpdateBatch(arCurrent);
			 }

			break;
		case 2://只更新Amount

			try
			{
				 for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
				aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
				aqorderdetail->Edit();
				aqorderdetail->FieldByName("amount")->AsInteger = amount;
				aqorderdetail->UpdateBatch(arCurrent);
			 }
			}
			__finally
			{
				LockWindowUpdate(NULL);
			}
			break;
		case 3://只更新Discount

			try
			{
               	 for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
				aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
				aqorderdetail->Edit();
				aqorderdetail->FieldByName("Discount")->AsFloat  = discount;
                aqorderdetail->UpdateBatch(arCurrent);
			 }
			}
			__finally
			{
				LockWindowUpdate(NULL);
			}
			break;
		default:
			break;
		}


}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::SpeedButton2Click(TObject *Sender)
{
	   AnsiString sql;
	   TADOQuery * aq = new TADOQuery(NULL);
	   aq->Connection = fcon;
	   sql = "select * from cust_customerinfo";
	   aq->Close();
	   aq->SQL->Clear();
	   aq->SQL->Add(sql);
	   aq->Open();
	   int count1 = aq->RecordCount ;
	   /*TDetaileForm * frm = new TDetaileForm(Application,2,1,0 ,fcon);
		frm->ParentID = -1;
		frm->ShowModal();
	   delete frm; */

	   Tfrmclient * frm = new Tfrmclient(Application,fcon,StgID);

	   frm->FormStyle = fsNormal ;
	   frm->Visible = false;
	   frm->WindowState = wsNormal ;
	   frm->Position = poMainFormCenter ;
		frm->ShowModal();
	   delete frm;
	   sql = "select * from cust_customerinfo";
	   aq->Close();
	   aq->SQL->Clear();
	   aq->SQL->Add(sql);
	   aq->Open();
	   int count2 = aq->RecordCount ;
	   if (count2 > count1) {
			sql = "select top 1 ID,Name from cust_customerinfo order by ID desc ";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			ClientID =	aq->FieldByName("ID")->AsInteger  ;
			cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)ClientID );
			edtclient->SetFocus();
			ClientView();
	   }
		delete aq;
}
//---------------------------------------------------------------------------

void TfrmimptBIorder::ClientView()
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

	sql = "select Salesman from CUST_CustomerInfo where id = " + IntToStr(ClientID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	sql = "select * from SYS_StaffInfo where Name = '" + aq->FieldByName("Salesman")->AsString + "' and stgID = " + IntToStr(StgID) + " and Career = 2";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	cbvendor->ItemIndex = cbvendor->Items->IndexOfObject((TObject*)aq->FieldByName("id")->AsInteger);

	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::BtnViewClick(TObject *Sender)
{
	if (orderfind) {
		if (!CheckOperateAuthority())
					return;
	}
		DelInvalidNtHeader();
		edclientview();

		Tfrmorderquery *frm = new Tfrmorderquery(Application,fcon,StgID,1,0,false);
		if (Master) {
            frm->chinorder ->Visible = true;
		}
		if (frm->ShowModal()==mrOk ) {
        	dbn->Enabled = true;
		   AnsiString code = frm->GetNoteCode();
		   AnsiString sqlwhere = frm->GetWhere();
		   AnsiString sql;
		   if (sqlwhere != "") {
			   sql = " select * from BS_OrderNoteHeader " + sqlwhere;
			   aqhd->Close();
			   aqhd->SQL->Clear();
			   aqhd->SQL->Add(sql);
			   aqhd->Open();
		   }
		 AnsiString str =  LeftBStr(code,2);
		   if (str == "00") {
			code = AnsiRightStr(code,code.Length()-2) ;

		}else
		   {
			  str = LeftBStr(code,1);
			  if (str == "0") {
						code = AnsiRightStr(code,code.Length()-1) ;
			  }

		   }

			TLocateOptions Opts;
			Opts.Clear();
			Opts << loPartialKey;
		   if(aqhd->Locate("OrderNtCode", Variant(code), Opts))
		   {
			RefreshHead(aqhd->FieldByName("ID")->AsInteger );
		   }else
		   {

			 MessageBoxA(0,"查询结果为空！","提示",MB_ICONWARNING);
		   }
		}
}
//---------------------------------------------------------------------------
void __fastcall TfrmimptBIorder::BtnClearClick(TObject *Sender)
{
  if (aqupdatehead->Active) {
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,fcon);
		::ShowWindow(frm->Handle, SW_HIDE);
		frm->PrintType = 1;//订单
		frm->InputPara(aqupdatehead->FieldByName("ID")->AsAnsiString,0 );

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;

		frm->RvSystem1->DefaultDest  = rdPreview ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPreview;
		frm->ClientName = edtclient->Text ;
		frm->pxbk = printbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;

		frm->previewprint(1,3);
		frm->Close();
		delete frm;
		}

}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::FormClose(TObject *Sender, TCloseAction &Action)
{
    DelInvalidNtHeader();
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::BtnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::BtnExportClick(TObject *Sender)
{
	if (aqorderdetail->Active && aqorderdetail->RecordCount >= 1)
	{
		DbgridToExcel2(dgdetail);
	}
}
//---------------------------------------------------------------------------
//Excel导出函数
bool __fastcall TfrmimptBIorder::DbgridToExcel2(TDBGrid* dbg)
{
	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

    savedlg->FileName = StringReplace(edtclient->Text+dbeditdanhao->Text,"\\","-",TReplaceFlags()<<rfReplaceAll) + cbtype->Text;
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
		path =  DBPath;
	}
	else
	{
    	return false;
	}

	if(FileExists(path))
	try {
		DeleteFileA(path);
	} catch (...) {
		return false;
	}

	Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");

	int *Count;
	Count = new int[6];

	int t1= 0;
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			if (dbg->Columns ->Items [q]->Title ->Caption == "数量") {
				Count[0] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "码洋") {
				Count[1] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "实洋") {
				Count[2] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "已发数量") {
				Count[3] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "未发数量") {
				Count[4] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "锁定数量") {
				Count[5] = t1;
			}
		}
	}

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;
	aqorderdetail->DisableControls();
	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					//temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				/*else if (dbg->Columns ->Items [j-1]->FieldName == "bookname") {
					t1++;
					AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					//temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					//v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					temptext = temptext + bookname + ",";
				} */
				else if (dbg->Columns ->Items [j-1]->FieldName == "Discount") {
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					//temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + "%,";
				}
				else
				{
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
					//temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		//iFileLength   =   FileSeek(iFileHandle,0,2);
		//FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+2,t1)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","合计");
	temptext = RzDBNumericEdit1->Text ;
	v.OlePropertyGet("Cells",t2+2+n,Count[0]).OlePropertySet("Value",temptext .c_str() );
	temptext = RzDBNumericEdit2->Text ;
	v.OlePropertyGet("Cells",t2+2+n,Count[1]).OlePropertySet("Value",temptext .c_str() );
	temptext = RzDBNumericEdit3->Text ;
	v.OlePropertyGet("Cells",t2+2+n,Count[2]).OlePropertySet("Value",temptext .c_str() );

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select sum(BS_OrderNote.SendAmount) as SendAmount,sum(BS_OrderNote.UnsendAmount) as UnsendAmount,sum(BS_OrderNote.localnum) as localnum"
			" from BS_OrderNote left join  BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" where BS_OrderNoteHeader.OrderNtCode = " + dbeditdanhao->Text + " and BS_OrderNote.state = 0";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	temptext = aq->FieldByName("SendAmount")->AsString ;
	v.OlePropertyGet("Cells",t2+2+n,Count[3]).OlePropertySet("Value",temptext .c_str() );
	temptext = aq->FieldByName("UnsendAmount")->AsString ;
	v.OlePropertyGet("Cells",t2+2+n,Count[4]).OlePropertySet("Value",temptext .c_str() );
	temptext = aq->FieldByName("localnum")->AsString ;
	v.OlePropertyGet("Cells",t2+2+n,Count[5]).OlePropertySet("Value",temptext .c_str() );

	delete aq;

	aqorderdetail->EnableControls();

	try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (Exception &E) {
		//ShowMessage(E.Message);
	}

	/*temptext = "\n";
	AnsiString tamount,mayang,shiyang;
	mayang =  RzDBNumericEdit2->Text;
	shiyang = RzDBNumericEdit3->Text;
	tamount = RzDBNumericEdit1->Text;
	mayang = StringReplace(mayang , ",","",TReplaceFlags()<<rfReplaceAll);
	shiyang = StringReplace(shiyang , ",","",TReplaceFlags()<<rfReplaceAll);
	tamount = StringReplace(tamount , ",","",TReplaceFlags()<<rfReplaceAll);

	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = "select sum(BS_OrderNote.SendAmount) as SendAmount,sum(BS_OrderNote.UnsendAmount) as UnsendAmount,sum(BS_OrderNote.localnum) as localnum"
			" from BS_OrderNote left join  BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" where BS_OrderNoteHeader.OrderNtCode = " + tamount + " and BS_OrderNote.state = 0";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	temptext = temptext + "合计,,,,,,,,," + tamount + ",," + mayang + "," + shiyang + ",,"+ aq->FieldByName("SendAmount")->AsString + "," + aq->FieldByName("UnsendAmount")->AsString + "," + aq->FieldByName("localnum")->AsString;
	delete aq;

	//temptext = temptext + "合计,,,,,," + RzDBNumericEdit1->Text + ",," + mayang + "," + shiyang;
	//temptext = temptext + "合计,,,,,," + RzDBNumericEdit1->Text + ",," + RzDBNumericEdit2->Text + "," + RzDBNumericEdit3->Text;
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	FileClose(iFileHandle);

	MessageBox(0,"导出完毕！","提示" ,MB_OK);    */
	return false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edclient->Text,StgID);
	   if (mrOk == frm->ShowModal())
	   {
			ClientID = frm->GetSelectID();
			cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)ClientID);
			edclient->Text = "";
			ClientView();
			edtclient->SetFocus();
	   }
	   delete frm;
	}
}

//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::cbclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		try {
			ClientID = (int)(cbclient->Items->Objects[cbclient->ItemIndex]);
		} catch (...) {
			MessageBoxA(0,"请选择正确的客户！","提示",MB_ICONERROR);
			return;
		}
		dbeditaddcost->SetFocus();
	}
}
//---------------------------------------------------------------------------

void TfrmimptBIorder::edclientview()
{
        edclient->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::dgdetail1CellClick(TColumn *Column)
{
	if (aqorderdetail->IsEmpty() ) {
	 return;
   }
   if (aqorderdetail->FieldByName("state1")->AsAnsiString == "有效") {
		editamount->Enabled = true;
		editdiscount->Enabled = true;
   }
   else
   {
    	editamount->Enabled = false;
		editdiscount->Enabled = false;
   }
   //edtCatalog->Text = aqorderdetail->FieldByName("ISBN")->AsAnsiString ;
   editamount->Text = aqorderdetail->FieldByName("amount")->AsAnsiString ;
   editdiscount->Text = aqorderdetail->FieldByName("Discount")->AsAnsiString ;
   editdetailbk->Text = aqorderdetail->FieldByName("bk")->AsAnsiString ;
}
//---------------------------------------------------------------------------
 void __fastcall TfrmimptBIorder::BtnPrintClick(TObject *Sender)
{
	  if (aqupdatehead->Active) {
		Tfrmwsaleprinta* frm = new Tfrmwsaleprinta(this,fcon);
		::ShowWindow(frm->Handle, SW_HIDE);
		frm->PrintType = 1;//订单
		frm->InputPara(aqupdatehead->FieldByName("ID")->AsAnsiString ,0);

		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;
		frm->RvSystem1->DefaultDest  = rdPrinter ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPreview;
		frm->ClientName = edtclient->Text ;
		frm->pxbk = printbk;
		frm->printtitle = printtitle;
		frm->contact = contact;
		frm->tel = tel;
		frm->address = address;

		frm->previewprint(0,3);

		frm->Close();
		delete frm;

		int count = aqupdatehead->FieldByName("printcount")->AsInteger + 1;
		aqupdatehead->Edit();
		aqupdatehead->FieldByName("printcount")->AsInteger = count;
		aqupdatehead->UpdateBatch(arCurrent);
		RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N5Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= aqorderdetail->RecordCount; i++) {
		dgdetail->DataSource->DataSet->RecNo = i;
		dgdetail->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	//ShowMessage(Key);
	if (Key == VK_F1) {   //查单
		if (!BtnView->Enabled ) {
			return;
		}
		BtnView->Click();
	}
	if (Key == VK_F2) {   //添单
		if (!BtnNew->Enabled ) {
			return;
		}
		BtnNew->Click();
	}
	if (Key == VK_F3) {   //保存
		if (!BtnOK->Enabled ) {
			return;
		}
		BtnOK->Click();
	}
	if (Key == VK_F4) {   //修改单头
		if (!BtnProperties->Enabled ) {
			return;
		}
		BtnProperties->Click();
	}
	if (Key == VK_F5) {   //删除
		if (!BtnDelete->Enabled ) {
			return;
		}
		BtnDelete->Click();
	}
	if (Key == VK_F6) {   //统一
		if (!BtnChangeOptions->Enabled ) {
			return;
		}
		BtnChangeOptions->Click();
	}
	if (Key == VK_F7) {   //导入
		if (!BtnImport->Enabled ) {
			return;
		}
		BtnImport->Click();
	}
	if (Key == VK_F8) {   //导出
		if (!BtnExport->Enabled ) {
			return;
		}
		BtnExport->Click();
	}
	if (Key == VK_F10) {  //打印
		if (!BtnPrint->Enabled ) {
			return;
		}
		BtnPrint->Click();
	}
	if (Key == VK_F11) {   //预览
		if (!BtnClear->Enabled ) {
			return;
		}
		BtnClear->Click();
	}
	if (Key == VK_F12) {   //审核本单
		if (!BtnOK1->Enabled ) {
			return;
		}
		BtnOK1->Click();
	}
	if (Key == VK_F9) {   //反审核
		if (!BtnCancel->Enabled ) {
			return;
		}
		BtnCancel->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 88) {    //期刊
		if (chqikan->Checked ) {
			chqikan->Checked = false;
		}
		else
		{
			chqikan->Checked = true;
		}
		chqikan->OnClick ;
	}
	if (Shift.Contains(ssAlt)&& Key == 67) {    //定位
		SpeedButton3->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 68) {    //浏览区设置
		SpeedButton4->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
   //	if (Shift.Contains(ssCtrl)&& Key == 70 ) {   //查书
  //	   BtnView1->Click();
  //	}
	if (Shift.Contains(ssAlt)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal;
	}
	if (Shift.Contains(ssCtrl)&&Key==70 ) {    //Ctrl + f 查书
		Tfrmfindorderbook *frm = new Tfrmfindorderbook(Application);
		frm->aq =aqorderdetail;

		if (mrOk == frm->ShowModal()){  ;    //查询条件
			AnsiString type,value;
			type = frm->type ;
			value = frm->value ;

				TLocateOptions   Opts;
				Opts.Clear();
				Opts   <<   loPartialKey;

				if ( !aqorderdetail->Locate(type,value,Opts))
				{
				   MessageBoxA(0,"没有找到查询的数据!","订单查询",MB_ICONINFORMATION);

				}else
				{
					dgdetail->SelectedRows->Clear();
					dgdetail->SelectedRows->CurrentRowSelected = true;
				}
		   }
		 delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::cbclientClick(TObject *Sender)
{
	try {
		ClientID = (int)(cbclient->Items->Objects[cbclient->ItemIndex]);
	} catch (...) {
		MessageBoxA(0,"请选择正确的客户！","提示",MB_ICONERROR);
		return;
	}
	dbeditaddcost->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TfrmimptBIorder::BtnView1Click(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,fcon,StgID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------
void TfrmimptBIorder::DelInvalidNtHeader()
{
	if (aqupdatehead->Active && aqupdatehead->RecordCount >= 1
		&& aqorderdetail->Active && aqorderdetail->RecordCount < 1 && aqupdatehead->FieldByName("OrderNtCode")->AsAnsiString == "0" )
	{
		DelNtHeader();
	}
}
//---------------------------------------------------------------------------
void TfrmimptBIorder::DelNtHeader()
{
	if (aqupdatehead->IsEmpty() ) {
        return;
	}
	AnsiString sql;
	sql = "delete from BS_OrderNoteHeader where id = " + aqupdatehead->FieldByName("ID")->AsAnsiString ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
	aqhd->Active = false;
	aqhd->Active = true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmimptBIorder::dbeditaddcostKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		membk->SetFocus();
	}
}
//---------------------------------------------------------------------------




void __fastcall TfrmimptBIorder::spnewbookClick(TObject *Sender)
{
	//新书目
	if (aqupdatehead->Active && aqupdatehead->RecordCount >= 1)
	{
	   Tfrmnewbook1 *frm = new Tfrmnewbook1(Application,fcon);
	   //frm->BIorder = this;
	   frm->modle = 4;//订单
	   if (chqikan->Checked) {
			frm->cbsaletype->Text = "期刊";
			frm->cbsaletypeChange(this);
	   }
	   if (mbOK == frm->ShowModal())
	   {
			edtCatalog->Text  = "";
			editamount->Text = "0";
			editdiscount->Text = "100";
			editdetailbk->Text = "";
		 	editamount->SetFocus();
	   }else
	   {
		 	edtCatalog->SetFocus();
	   }
	   delete frm;
	   return;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmimptBIorder::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",StgID);
	   if (mrOk == frm->ShowModal())
	   {
			ClientID = frm->GetSelectID();
			cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)ClientID);
			edtclient->SetFocus();
			ClientView();
	   }
	   delete frm;
	   dbeditaddcost->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::BtnImportClick(TObject *Sender)
{
	if (edtclient->Enabled ) {
		MessageBoxA(0,"请先保存单头信息，再进行导入！","提示",MB_ICONERROR);
		return;
	}
	TfrmExcelImport *frm = new TfrmExcelImport(Application,fcon,aqupdatehead->FieldByName("ID")->AsInteger);
	//frm ->ShowModal();
	frm->fuserid = UserID;
	frm->fstgid = StgID;
	if (frm->ShowModal() == mrOk  ) {
		RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::edtclientKeyPress(TObject *Sender, wchar_t &Key)
{
	dbeditaddcost->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::dgdetail1DblClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
		TfrmNewBookModify * frm = new TfrmNewBookModify(Application,fcon,aqorderdetail->FieldByName("bkcatalogid")->AsInteger,m_storageID,m_userID);
		frm->ShowModal();
		delete frm;
		RefreshDetail();
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N6Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	else
	{
		AnsiString sql;
		int newcatalogid = -1;
		sql = "select BS_BookCatalog.ID,ISBN,Name,UserDefCode,Price,PressCount,Author,AbbreviatedName from BS_BookCatalog left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id where BS_BookCatalog.Name like '%" + aqorderdetail->FieldByName("bookname")->AsString + "%' and AbbreviatedName = '" + aqorderdetail->FieldByName("AbbreviatedName")->AsString + "'";
		aquery->Connection = fcon;
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->RecordCount > 1) {
			Tfrmchangeselect *frm = new Tfrmchangeselect(Application,aquery);
			if (frm->ShowModal() == mrOk  ) {
				if (frm->continuechange == 1) {
					delete frm;
					TfrmNewBookModify * frm1 = new TfrmNewBookModify(Application,fcon,aqorderdetail->FieldByName("bkcatalogid")->AsInteger,m_storageID,m_userID);
					frm1->newbook = 1;
					if (frm1->ShowModal() == mrOk) {
						newcatalogid = frm1->newcatalogid ;
					}
					delete frm1;
				}
				else
				{
					newcatalogid = aquery->FieldByName("ID")->AsInteger ;
					delete frm;
				}
			}
			else
			{
				delete frm;
			}
		}

		else
		{
			TfrmNewBookModify * frm2 = new TfrmNewBookModify(Application,fcon,aqorderdetail->FieldByName("bkcatalogid")->AsInteger,m_storageID,m_userID);
			frm2->newbook = 1;
			if (frm2->ShowModal() == mrOk) {
				newcatalogid = frm2->newcatalogid ;
			}
			delete frm2;
		}

		if (newcatalogid > -1) {
        	sql = "update BS_OrderNote set state = 1,bk = '该书被更换' where id = " + aqorderdetail->FieldByName("id")->AsString ;
			TADOQuery *aq = new TADOQuery(this);
			aq->Connection = fcon;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL() ;

			sql = "insert into BS_OrderNote(OrderNtHeaderID,Amount,Discount,FixedPrice,DiscountedPrice,UnsendAmount,BkcatalogID,bk) select OrderNtHeaderID,Amount,Discount,FixedPrice,DiscountedPrice,UnsendAmount," + IntToStr(newcatalogid) + ",'由《" + aqorderdetail->FieldByName("bookname")->AsString + "》换书而来' from BS_OrderNote where id = " + aqorderdetail->FieldByName("id")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL() ;
			delete aq;
			//RefreshDetail();
			RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N7Click(TObject *Sender)
{
	if (aqorderdetail->	IsEmpty() ) {
		return;
	}
	AnsiString sql;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	AnsiString bkcatalogid;
	bkcatalogid = aqorderdetail->FieldByName("bkcatalogid")->AsString;

	sql = "update BS_OrderNote set state = 0 where id = " + aqorderdetail->FieldByName("id")->AsString ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL() ;
	delete aq;
	RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );

	aqorderdetail->Locate("bkcatalogid",bkcatalogid,Opts);
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N8Click(TObject *Sender)
{
	if (aqorderdetail->	IsEmpty() ) {
		return;
	}
	AnsiString sql;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	AnsiString bkcatalogid;
	bkcatalogid = aqorderdetail->FieldByName("bkcatalogid")->AsString;

	sql = "update BS_OrderNote set state = 1,localnum = 0 where id = " + aqorderdetail->FieldByName("id")->AsString ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL() ;
	delete aq;
	RefreshHead(aqupdatehead->FieldByName("ID")->AsInteger );

	aqorderdetail->Locate("bkcatalogid",bkcatalogid,Opts);
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::BtnOK1Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}

	AnsiString sql = "exec USP_BS_Order_shenhei 0," + aqupdatehead->FieldByName("ID")->AsString  ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;

	RefreshDetail();
	BtnOK1->Enabled = false;
	BtnCancel->Enabled = true;
	SpeedButton1->Visible = true;
	GroupBox2->Enabled = false;

	BtnOK->Enabled = false;
	BtnProperties->Enabled = false;
	BtnDelete->Enabled = false;
	BtnChangeOptions->Enabled = false;

}
//---------------------------------------------------------------------------
bool TfrmimptBIorder::chongfutishi(int catalogid)
{
	if (ordertishi) {
    	AnsiString sql;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		sql = "select BS_OrderNote.Amount,BS_OrderNote.SendAmount,BS_OrderNote.UnsendAmount,BS_OrderNote.BkcatalogID,BS_BookCatalog.ISBN,BS_BookCatalog.Name,"
				" BS_OrderNoteHeader.OrderNtCode,convert (char(10),BS_OrderNoteHeader.HdTime,120) as HdTime,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname "
				" from BS_OrderNote left join  BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
				" left join BS_BookCatalog on BS_OrderNote.BkcatalogID = BS_BookCatalog.id "
				" where BS_OrderNoteHeader.StgID = " + IntToStr(StgID) + " and BS_OrderNote.BkcatalogID = " + IntToStr(catalogid) + " and BS_OrderNoteHeader.VendorID = " + IntToStr(ClientID) + " and BS_OrderNoteHeader.state in (0,1) and BS_OrderNote.state = 0 and BS_OrderNoteHeader.HdTime > dateadd(month,-" + month + ",getdate())";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount >= 1) {
			Tfrmchongfuorder * frm = new Tfrmchongfuorder(Application,aq);
			if (frm->ShowModal()== mrOk ) {
				delete aq;
				return true;
			}
			else
			{
            	delete aq;
				return false;
			}
		}
		else
		{
			delete aq;
			return true;
		}
	}
	else
	{
    	return true;
	}
}
//---------------------------------------------------------------------------


 /*
void __fastcall TfrmimptBIorder::dgdetail1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (dgdetail->DataSource->DataSet->FieldByName("state1")->AsString  == "无效" ) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
		dgdetail->Canvas->FillRect(Rect);
		dgdetail->Canvas->Font->Color  = clRed;
	   //	DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;  //>>fsBold ;
		dgdetail->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}  */
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::dgdetailCellClick(TColumn *Column)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
   	}
   if (aqorderdetail->FieldByName("state1")->AsAnsiString == "有效") {
		editamount->Enabled = true;
		editdiscount->Enabled = true;
   }
   else
   {
    	editamount->Enabled = false;
		editdiscount->Enabled = false;
   }
   //edtCatalog->Text = aqorderdetail->FieldByName("ISBN")->AsAnsiString ;
   editamount->Text = aqorderdetail->FieldByName("amount")->AsAnsiString ;
   editdiscount->Text = aqorderdetail->FieldByName("Discount")->AsAnsiString ;
   editdetailbk->Text = aqorderdetail->FieldByName("bk")->AsAnsiString ;
   editstockamount->Text = aqorderdetail->FieldByName("bookamount")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::dgdetailDblClick(TObject *Sender)
{
	/*if (aqorderdetail->IsEmpty() ) {
		return;
	}
		TfrmNewBookModify * frm = new TfrmNewBookModify(Application,fcon,aqorderdetail->FieldByName("bkcatalogid")->AsInteger,m_storageID,m_userID);
		frm->ShowModal();
		delete frm;
		RefreshDetail();   */
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::dgdetail1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (dgdetail->DataSource->DataSet->FieldByName("state1")->AsString  == "无效" ) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
		dgdetail->Canvas->FillRect(Rect);
		dgdetail->Canvas->Font->Color  = clRed;
	   //	DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;  //>>fsBold ;
		dgdetail->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
	if (dgdetail->DataSource->DataSet->FieldByName("newbook")->AsBoolean  == true ) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
		dgdetail->Canvas->FillRect(Rect);
		dgdetail->Canvas->Font->Color  = clPurple ;
	   //	DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;  //>>fsBold ;
		dgdetail->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::BtnPropertiesClick(TObject *Sender)
{
	if (orderchange) {
		if (!CheckOperateAuthority())
			return;
	}
	GroupBox1->Enabled = true;
	edclient->Enabled = true;
	edtclient->Enabled = true;
	spselectClient->Enabled = true;
	SpeedButton2->Enabled = true;
	dbeditaddcost->Enabled = true;
	dtpdate->Enabled = true;
	dtpfahuo->Enabled = true;
	membk->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::dgdetailTitleClick(TColumn *Column)
{
	if (aqorderdetail->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqorderdetail->Sort == "") {
		aqorderdetail->Sort =  Column->FieldName + " ASC";
	}
	else if (aqorderdetail->Sort == qusort) {
		aqorderdetail->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqorderdetail->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmimptBIorder::membkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		BtnOK->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::SpeedButton3Click(TObject *Sender)
{
	if (GroupBox3->Visible) {
		GroupBox3->Visible = false;
	}
	else
	{
    	GroupBox3->Visible = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::chqikanClick(TObject *Sender)
{
	if (chqikan->Checked ) {
		edqikan->Visible = true;
		if (m_catalogSearchMode == 1) {
			edtCatalog->MaxLength = 15;
		}
		else
		{
			edtCatalog->MaxLength = 0;
		}
	}
	else
	{
		edqikan->Visible = false;
		if (m_catalogSearchMode == 1) {
			edtCatalog->MaxLength = 13;
		}
		else
		{
			edtCatalog->MaxLength = 0;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::edqikanKeyPress(TObject *Sender, wchar_t &Key)
{
	/*if (Key == '\r')
	{
				float price;
				if (m_catalogSearchMode == 6) {
				try {
						price = StrToFloat(edtCatalog->Text.Trim());
					} catch (...) {
						MessageBox(0,"请输入正确的定价！","订单" ,MB_ICONEXCLAMATION);
						return;
					}
				}

				TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,fcon);
					LandInfo li;
					li.app = Application;
					li.con = fcon;
					li.userID = UserID ;
					li.storageID = StgID ;
					frm->Init(&li);
					frm->DoModalType = 4;
					//frm->order  = this;
					frm->qikan = chqikan->Checked ;
					frm->qikanhao = edqikan->Text ;
					frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
					if (mrOk == frm->ShowModal())
					{
						int supplierID = -1,catalogID = -1;
						if (frm->SelectAll) {

							 for (int i = 0; i < frm->lengthint  ; i++) {
								 if (chongfutishi(frm->BkcatalogiD[i])) {
									AddNote(supplierID,frm->BkcatalogiD[i]);
								 }
							 }

						}else
						{
							frm->GetSelectResult(supplierID, catalogID);

							if (catalogID >= 0)
							{
								TLocateOptions   Opts;
								Opts.Clear();
								Opts   <<   loPartialKey;
								String   str   = AnsiString(catalogID);
								if ( !aqorderdetail->Locate("bkcatalogid",str,Opts))
								{
									if (chongfutishi(catalogID)) {
										AddNote(-1, catalogID);
										editamount->Enabled = true;
										editdiscount->Enabled = true;
										edtCatalog->Text  = "";

										if (chfoceset->Checked) {
											if (chfsamount->Checked ) {
												Perform(WM_NEXTDLGCTL, 0, 0);
											}
											else if (chfsdiscount->Checked ) {
												editdiscount->SetFocus();
											}
											else if (chfsluru->Checked) {
												edtCatalog->SetFocus();
											}
										}
										else
										{
											Perform(WM_NEXTDLGCTL, 0, 0);
										}
									}
									else
									{
										edtCatalog->Text  = "";
										edtCatalog->SetFocus();
									}
								}
								else
								{
									dgdetail->SetFocus();
									dgdetail->SelectedRows->CurrentRowSelected = true;
									edtCatalog->Text  = "";
									editamount->SetFocus();
								}
							}
						}
					}
					else
					{
						if (!frm->findbook) {     //产生新书
										//新书目
									if (aqupdatehead->Active && aqupdatehead->RecordCount >= 1)
									{
									   Tfrmnewbook1 *frma = new Tfrmnewbook1(Application,fcon);
									   //frma->BIorder = this;
									   frma->modle = 4;
										//frma->editcode->Text = edtCatalog->Text ;
										if (chqikan->Checked) {
											frma->cbsaletype->Text = "期刊";
											frma->cbsaletypeChange(this);
											frma->editqikanmao->Text =edtCatalog->Text + edqikan->Text;
											PostMessage(frma->editqikanmao->Handle, WM_KEYDOWN,VK_RETURN,0);
									   }
									   else
									   {
											frma->editcode->Text = edtCatalog->Text ;
											PostMessage(frma->editcode->Handle, WM_KEYDOWN,VK_RETURN,0);
									   }
										//PostMessage(frma->editcode->Handle, WM_KEYDOWN,VK_RETURN,0);
									   if (mbOK == frma->ShowModal())
									   {

									   }
									   delete frma;
									   editamount->SetFocus();
									}

						}
					}
					delete frm;

	}  */
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N13Click(TObject *Sender)
{
	lblCatalog->Caption = "作者";
	m_catalogSearchMode=5;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::chfsluruClick(TObject *Sender)
{
	if (chfsluru->Checked ) {
		chfoceset->Checked = true;
	}
	else if (chfsamount->Checked ) {
		chfoceset->Checked = true;
	}
	else if (chfsdiscount->Checked ) {
		chfoceset->Checked = true;
	}
	else
	{
		chfoceset->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::BtnCancelClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
		return;
	}
	AnsiString sql = "exec USP_BS_Order_shenhei 1," + aqupdatehead->FieldByName("ID")->AsString  ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;

	RefreshDetail();
	BtnOK1->Enabled = true;
	BtnCancel->Enabled = false;
	SpeedButton1->Visible = false;
	GroupBox2->Enabled = true;
	edtCatalog->Enabled = true;
	edqikan->Enabled = true;

	BtnOK->Enabled = true;
	BtnProperties->Enabled = true;
	BtnDelete->Enabled = true;
	BtnChangeOptions->Enabled = true;


}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::cbtypeChange(TObject *Sender)
{
	if (cbtype->ItemIndex == 1) {
		BtnImport->Enabled = false;
	}else
	{
		BtnImport->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::SpeedButton4Click(TObject *Sender)
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

void __fastcall TfrmimptBIorder::ch1Click(TObject *Sender)
{
	if (ch1->Checked ) {
		dgdetail->Columns->Items[1]->Visible = true;
		dgdetail->Columns->Items[1]->Width = 52;
	}
	else
	{
		dgdetail->Columns->Items[1]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::ch2Click(TObject *Sender)
{
	if (ch2->Checked ) {
		dgdetail->Columns->Items[2]->Visible = true;
		dgdetail->Columns->Items[2]->Width = 57;
	}
	else
	{
		dgdetail->Columns->Items[2]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::ch3Click(TObject *Sender)
{
	if (ch3->Checked ) {
		dgdetail->Columns->Items[3]->Visible = true;
		dgdetail->Columns->Items[3]->Width = 56;
	}
	else
	{
		dgdetail->Columns->Items[3]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::ch4Click(TObject *Sender)
{
	if (ch4->Checked ) {
		dgdetail->Columns->Items[4]->Visible = true;
		dgdetail->Columns->Items[4]->Width = 55;
	}
	else
	{
		dgdetail->Columns->Items[4]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::ch5Click(TObject *Sender)
{
	if (ch5->Checked ) {
		dgdetail->Columns->Items[5]->Visible = true;
		dgdetail->Columns->Items[5]->Width = 57;
	}
	else
	{
		dgdetail->Columns->Items[5]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::ch6Click(TObject *Sender)
{
	if (ch6->Checked ) {
		dgdetail->Columns->Items[6]->Visible = true;
		dgdetail->Columns->Items[6]->Width = 59;
	}
	else
	{
		dgdetail->Columns->Items[6]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::ch7Click(TObject *Sender)
{
	if (ch7->Checked ) {
		dgdetail->Columns->Items[7]->Visible = true;
		dgdetail->Columns->Items[7]->Width = 55;
	}
	else
	{
		dgdetail->Columns->Items[7]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::ch8Click(TObject *Sender)
{
	if (ch8->Checked ) {
		dgdetail->Columns->Items[8]->Visible = true;
		dgdetail->Columns->Items[8]->Width = 56;
	}
	else
	{
		dgdetail->Columns->Items[8]->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::BtnFinishClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() || aqorderdetail->RecordCount == 0) {
		return;
	}
	AnsiString temptext,path,sql;
	sql = "select distinct press from BS_OrderNote where OrderNtHeaderID = " + aqupdatehead->FieldByName("ID")->AsString;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon ;
	aq->Close() ;
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	savedlg->FileName = aq->FieldByName("press")->AsAnsiString.Trim() ;
	if (savedlg->Execute())
	{
		/*String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str());
        while (!aq->Eof )
		{
			path = DBPath + aq->FieldByName("press")->AsAnsiString.Trim() + ".xls" ;
			if (FileExists(path)) {
				try {
					DeleteFileA(path);
				} catch (...) {
					return;
				}
			}
			sql = "select ISBN,Name,Price,Author,Press,Presscount,sum(needprocurenum) as Amount "
				" from BS_OrderNote  where OrderNtHeaderID = "  + aqupdatehead->FieldByName("ID")->AsString + " and press = '" + aq->FieldByName("press")->AsAnsiString +
				"' group by ISBN,Name,Price,Author,Press,Presscount";
			query->Close() ;
			query->SQL->Clear() ;
			query->SQL->Add(sql);
			query->Open();

            Variant  v,vSheet,R,xWorkbook;
			v   =Variant::CreateObject("Excel.Application");
			v.OlePropertySet("Visible",true);
			v.OlePropertyGet("WorkBooks").OleFunction("Add");
			xWorkbook = v.OlePropertyGet("ActiveWorkBook");
			vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");
			int t2 = query->RecordCount ,n=0;
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",1,1),vSheet.OlePropertyGet("Cells",t2+11,14)); //取得合并的区域
			R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
			R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

			v.OlePropertyGet("Cells",1,1).OlePropertySet("Value",printtitle .c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",1,1),vSheet.OlePropertyGet("Cells",2,14)); //取得合并的区域
			R.OleProcedure("Merge");
			R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Bold",true);
			R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("Name","宋体");   //字体
			R.OlePropertyGet("Cells").OlePropertyGet("Font").OlePropertySet("size",16);
			R.OlePropertySet("HorizontalAlignment",3);

			temptext = "联系人：" + lblOpName->Caption ;
			v.OlePropertyGet("Cells",3,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,1),vSheet.OlePropertyGet("Cells",3,4)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "电话：" + usertel ;
			v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",3,5),vSheet.OlePropertyGet("Cells",3,14)); //取得合并的区域
			R.OleProcedure("Merge");

            temptext = "地址：" + address ;
			v.OlePropertyGet("Cells",4,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",4,1),vSheet.OlePropertyGet("Cells",4,14)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "收订单号：" + dbeditdanhao->Text ;
			v.OlePropertyGet("Cells",5,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",5,1),vSheet.OlePropertyGet("Cells",5,4)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "供应商名称：" + dblkpcbbVendorID->Text ;
			v.OlePropertyGet("Cells",5,5).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",5,5),vSheet.OlePropertyGet("Cells",5,8)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "联系人："+ dsetVendor->FieldByName("Contact")->AsString ;
			v.OlePropertyGet("Cells",5,9).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",5,9),vSheet.OlePropertyGet("Cells",5,14)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "采购日期：" +  DateToStr(dbdtedtHdTime->Date ) ;
			v.OlePropertyGet("Cells",6,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",6,1),vSheet.OlePropertyGet("Cells",6,4)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "供应商电话：" + dsetVendor->FieldByName("Telephone")->AsString ;
			v.OlePropertyGet("Cells",6,5).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",6,5),vSheet.OlePropertyGet("Cells",6,8)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "传真："+ dsetVendor->FieldByName("Fax")->AsString ;
			v.OlePropertyGet("Cells",6,9).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",6,9),vSheet.OlePropertyGet("Cells",6,14)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "备注：" + membk->Text;
			v.OlePropertyGet("Cells",7,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",7,1),vSheet.OlePropertyGet("Cells",7,14)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "供应商地址："+ dsetVendor->FieldByName("Address")->AsString ;
			v.OlePropertyGet("Cells",8,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",8,1),vSheet.OlePropertyGet("Cells",8,14)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "总品种：" +  IntToStr(t2) ;
			v.OlePropertyGet("Cells",9,1).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",9,1),vSheet.OlePropertyGet("Cells",9,4)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "总数量：" + dbnbedt2->Text ;
			v.OlePropertyGet("Cells",9,5).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",9,5),vSheet.OlePropertyGet("Cells",9,8)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "总码洋："+ dbnbedt3->Text ;
			v.OlePropertyGet("Cells",9,9).OlePropertySet("Value",temptext.c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",9,10),vSheet.OlePropertyGet("Cells",9,14)); //取得合并的区域
			R.OleProcedure("Merge");

			n = 9;
			int t1= 0;
			for(int q=0;q<dbg->FieldCount-1 ;++q)
			{
				if (dbg->Columns->Items[q]->Visible == true) {
					t1++;
					temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
					v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
					temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
				}
			}

			for(int i=2+n;i<=t2+1+n ;i++)
			{
				t1=0;
				temptext = "\n";
				for(int j=1;j<dbg->Columns ->Count  ;j++)
				{
					if (dbg->Columns->Items[j-1]->Visible == true) {
						if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
							t1++;
							temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
							v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
							//temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
						}

						else if (dbg->Columns ->Items [j-1]->FieldName == "Discount") {
							t1++;
							temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
							v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
							//temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + "%,";
						}
						else
						{
							t1++;
							temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
							v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
							//temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
						}
					}
				}
				dbg->DataSource ->DataSet ->Next() ;
			}
            R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,3),vSheet.OlePropertyGet("Cells",t2+10,3)); //取得合并的区域  、
			R.OlePropertySet("WrapText", true);//设置指定区域中所有的单元格中的文本自动换行

			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,14),vSheet.OlePropertyGet("Cells",t2+10,14)); //取得合并的区域  、
			R.OlePropertySet("WrapText", true);//设置指定区域中所有的单元格中的文本自动换行

			v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","合计");
			temptext = dbnbedt2->Text ;
			v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );
			temptext = dbnbedt3->Text ;
			v.OlePropertyGet("Cells",t2+2+n,11).OlePropertySet("Value",temptext .c_str() );
			temptext = dbnbedt4->Text ;
			v.OlePropertyGet("Cells",t2+2+n,12).OlePropertySet("Value",temptext .c_str() );

			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,11),vSheet.OlePropertyGet("Cells",t2+11,12)); //取得合并的区域  、
			R.OlePropertySet("NumberFormatLocal", "0.00");//设置指定区域中的所有单元格格式为小数百分比

			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",10,7),vSheet.OlePropertyGet("Cells",t2+11,7)); //取得合并的区域  、
			R.OlePropertySet("NumberFormatLocal", "0.00");//设置指定区域中的所有单元格格式为小数百分比

			temptext = "制单员：" + lblOpName->Caption ;
			v.OlePropertyGet("Cells",t2+3+n,1).OlePropertySet("Value",temptext .c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+3+n,1),vSheet.OlePropertyGet("Cells",t2+3+n,14)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "收货联系人：" + shcontact ;
			v.OlePropertyGet("Cells",t2+4+n,1).OlePropertySet("Value",temptext .c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+4+n,1),vSheet.OlePropertyGet("Cells",t2+4+n,14)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "收货联系电话：" + shtel ;
			v.OlePropertyGet("Cells",t2+5+n,1).OlePropertySet("Value",temptext .c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+5+n,1),vSheet.OlePropertyGet("Cells",t2+5+n,14)); //取得合并的区域
			R.OleProcedure("Merge");

			temptext = "收货地址：" + shaddress ;
			v.OlePropertyGet("Cells",t2+6+n,1).OlePropertySet("Value",temptext .c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+6+n,1),vSheet.OlePropertyGet("Cells",t2+6+n,14)); //取得合并的区域
			R.OleProcedure("Merge");

			v.OlePropertyGet("Cells",t2+7+n,1).OlePropertySet("Value",printbk .c_str() );
			R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",t2+7+n,1),vSheet.OlePropertyGet("Cells",t2+7+n,14)); //取得合并的区域
			R.OleProcedure("Merge");

            try {
				xWorkbook.OleFunction("SaveAs",path.c_str());
			} catch (Exception &E) {
				//ShowMessage(E.Message);
			}
			aq->Next();
		}*/
	}

	delete aq;
	MessageBox(0,"导出完毕！","提示" ,MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N14Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
        return;
	}
	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,fcon,StgID,aqorderdetail->FieldByName("bkcatalogid")->AsInteger,m_userID );
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::BtnLastRecordClick(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
    	return;
	}
	AnsiString sql;
	sql = "insert into SYS_InforMessage(state,Message,Type,Datetime,value,stgid,userid) values (1,'" + Edit3->Text + "已回告内部订单"+ dbeditdanhao->Text +"',1,getdate(),'" + aqupdatehead->FieldByName("OrderNtCode")->AsString + "'," + aqupdatehead->FieldByName("StgID")->AsString + "," + IntToStr(UserID) + ")";
	ExecSQL(sql);
    MessageBox(0,"回告通知已发出！","订单" ,MB_ICONEXCLAMATION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N15Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
    	return;
	}
	Tfrmsettyperss *frm = new Tfrmsettyperss(Application,fcon);
	if (frm->ShowModal() == mrOk ) {
		AnsiString ids = "-1",sql;
		bool up = false;

		sql = "update BS_OrderNote set ";
		if (frm->chisbn ->Checked && frm->ISBN != "") {
			sql = sql + "ISBN = '" + frm->ISBN + "'";
			up = true;
		}
		if (frm->chname ->Checked && frm->Name != "") {
			if (up) {
				sql = sql + ",";
			}
			sql = sql + "Name = '" + frm->Name + "'";
			up = true;
		}
		if (frm->chprice ->Checked && frm->price > 0) {
			if (up) {
				sql = sql + ",";
			}
			sql = sql + "Price = " + FloatToStr(frm->price);
			up = true;
		}
		if (frm->chpress ->Checked && frm->PressName != "" ) {
			if (up) {
				sql = sql + ",";
			}
			sql = sql + "Press = '" + frm->PressName + "'";
			up = true;
		}
		if (frm->chauthor ->Checked && frm->Author != "") {
			if (up) {
				sql = sql + ",";
			}
			sql = sql + "Author = '" + frm->Author + "'";
			up = true;
		}
		if (frm->chpresscount ->Checked && frm->PressCount != "") {
			if (up) {
				sql = sql + ",";
			}
			sql = sql + "Presscount = '" + frm->PressCount + "'";
			up = true;
		}

		if (up) {
        	for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
				aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
				ids = ids + "," + aqorderdetail->FieldByName("id")->AsAnsiString ;
			}
			sql = sql + " where id in(" + ids + ")";
            ExecSQL(sql);
			RefreshDetail();
		}
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N16Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() ) {
    	return;
	}
	Tfrmclasscode *frm = new Tfrmclasscode(Application);
	if (frm->ShowModal() == mrOk ) {
		int pressid = -1;
		float price = 0.00;
		AnsiString ids = "-1",sql;

		for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
			aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
			ids = ids + "," + aqorderdetail->FieldByName("id")->AsAnsiString ;
		}
		bool mut = false;
		sql = " update BS_OrderNote set ";
		if (frm->ch1->Checked ) {
			sql = sql + " xuxiao = '" + frm->ed1->Text.Trim()  + "' ";
			mut = true;
		}
		if (frm->ch2->Checked ) {
			if (mut) {
                sql = sql + ",";
			}
			sql = sql + " xiaoqu = '" + frm->ed2->Text.Trim() + "' ";
			mut = true;
		}
		if (frm->ch3->Checked ) {
			if (mut) {
                sql = sql + ",";
			}
			sql = sql + " xueyuan = '" + frm->ed3->Text.Trim() + "' ";
			mut = true;
		}
		if (frm->ch4->Checked ) {
			if (mut) {
                sql = sql + ",";
			}
			sql = sql + " class = '" + frm->ed4->Text.Trim() + "' ";
			mut = true;
		}
		if (frm->ch5->Checked ) {
			if (mut) {
                sql = sql + ",";
			}
			sql = sql + " course = '" + frm->ed5->Text.Trim() + "' ";
			mut = true;
		}
		if (frm->ch6->Checked ) {
			if (mut) {
                sql = sql + ",";
			}
			sql = sql + " incode = '" + frm->ed6->Text.Trim() + "' ";
			mut = true;
		}
		if (frm->ch7->Checked ) {
			if (mut) {
                sql = sql + ",";
			}
			sql = sql + " teacher = '" + frm->ed7->Text.Trim() + "' ";
			mut = true;
		}
		if (frm->ch8->Checked ) {
			if (mut) {
                sql = sql + ",";
			}
			sql = sql + " telphone = '" + frm->ed8->Text.Trim() + "' ";
			mut = true;
		}
		if (mut) {
        	sql = sql + " where id in(" + ids + ")";
			ExecSQL(sql);
			RefreshDetail();
		}
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N17Click(TObject *Sender)
{
	if (aqorderdetail->Active && aqorderdetail->RecordCount >= 1)
	{
		DbgridToExcel2(dgdetail);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N18Click(TObject *Sender)
{
	if (aqorderdetail->Active && aqorderdetail->RecordCount >= 1)
	{
		DbgridToExcel(dgdetail);
	}
}
//---------------------------------------------------------------------------
//Excel导出函数
bool TfrmimptBIorder::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString temptext,path;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;

    savedlg->FileName = StringReplace(edtclient->Text+dbeditdanhao->Text,"\\","-",TReplaceFlags()<<rfReplaceAll) + cbtype->Text;
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + "锁定.xls";
		path =  DBPath;
	}
	else
	{
    	return false;
	}

	if(FileExists(path))
	try {
		DeleteFileA(path);
	} catch (...) {
		return false;
	}

	Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");

	int *Count;
	Count = new int[6];

	int t1= 0;
	for(int q=0;q<dbg->FieldCount-1 ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			if (dbg->Columns ->Items [q]->Title ->Caption == "数量") {
				Count[0] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "码洋") {
				Count[1] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "实洋") {
				Count[2] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "已发数量") {
				Count[3] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "未发数量") {
				Count[4] = t1;
			}
			else if (dbg->Columns ->Items [q]->Title ->Caption == "锁定数量") {
				Count[5] = t1;
			}
		}
	}

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;
	aqorderdetail->DisableControls();
	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true && aqorderdetail->FieldByName("localnum")->AsInteger > 0 ) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "Discount") {
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
				else
				{
                	t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+1,t1)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	aqorderdetail->EnableControls();

	try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (Exception &E) {

	}
	return false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::SpeedButton5Click(TObject *Sender)
{
	if(aqorderdetail->IsEmpty())
	{
		return;
	}
	else
	{
		if (SpeedButton5->Caption == "显示有效") {
			aqorderdetail->Active = false;
			aqorderdetail->Filtered = true;
            aqorderdetail->Filter = "state1 = '有效'";
			aqorderdetail->Active = true;
			SpeedButton5->Caption = "显示全部";
		}
		else
		{
			aqorderdetail->Active = false;
			aqorderdetail->Filtered = false;
			aqorderdetail->Active = true;
			SpeedButton5->Caption = "显示有效";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmimptBIorder::N12Click(TObject *Sender)
{
	if (aqorderdetail->IsEmpty() && aqorderdetail->RecordCount == 0 ) {
    	return;
	}

	Tfrmcomfigbook *frm = new Tfrmcomfigbook(Application,fcon);

	frm->ISBN = aqorderdetail->FieldByName("ISBN")->AsAnsiString;
	frm->Name = aqorderdetail->FieldByName("bookname")->AsAnsiString;
	frm->Press = aqorderdetail->FieldByName("press")->AsAnsiString;
	frm->Author = aqorderdetail->FieldByName("Author")->AsAnsiString;
	if (frm->ShowModal() == mrOk ) {
		AnsiString ids = "-1",sql;

		sql = "update BS_OrderNote set BkcatalogID = " + frm->query->FieldByName("id")->AsAnsiString;

		for (int i =0; i < dgdetail->SelectedRows->Count ; i++) {
			aqorderdetail->GotoBookmark(dgdetail->SelectedRows->Items[i]);
			ids = ids + "," + aqorderdetail->FieldByName("id")->AsAnsiString ;
		}
		sql = sql + " where id in(" + ids + ")";

		ExecSQL(sql);
		//RefreshDetail();
	}
}
//---------------------------------------------------------------------------

