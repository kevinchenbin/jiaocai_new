//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ClearingProvidForm11.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzGrids"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TfrmClearingProvid11 *frmClearingProvid11;
//---------------------------------------------------------------------------
__fastcall TfrmClearingProvid11::TfrmClearingProvid11(TComponent* Owner)
	: TfrmMDIChild(Owner)
{        m_module = MTData;
	dtp1->Date=dtp1->Date .CurrentDate();
	dtp2->Date=dtp2->Date .CurrentDate();
	this->WindowState = wsMaximized ;
}
//---------------------------------------------------------------------------

void TfrmClearingProvid11::Init(TApplication* app, TADOConnection* con)
{          TfrmMDIChild::Init(app, con);

	query->Connection = con;
	fcon = con;
	AnsiString sql;
	TADOQuery * aq;
	aq = new TADOQuery(this);
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add("select * from sys_bsset where name ='xiaoshudian'");
	aq->Open();
	storageformat =  "￥" + aq->FieldByName("bk")->AsAnsiString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add("select * from sys_bsset where name ='retailxiaoshudian'");
	aq->Open();
	retaiformat =  "￥" + aq->FieldByName("bk")->AsAnsiString ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
	aq->Open();
	saleformat =  "￥" + aq->FieldByName("bk")->AsAnsiString ;

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

	sql = "select ID,Name from CUST_CustomerInfo where type = 1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbsupplier->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	aq->First();
	cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)stgid);

	sql = "select ID,Name from BS_BookType ";
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
	cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)stgid);

	sql = "select ID,AbbreviatedName from BS_PressInfo ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	aq->First();
	cpress->ItemIndex = cpress->Items->IndexOfObject((TObject*)stgid);
	delete aq;
	DBGridEh1->Columns->Items[2]->DisplayFormat =  storageformat;
	DBGridEh1->Columns->Items[3]->DisplayFormat =  storageformat;
	DBGridEh1->Columns->Items[5]->DisplayFormat =  storageformat;
	DBGridEh1->Columns->Items[6]->DisplayFormat =  storageformat;
	DBGridEh1->Columns->Items[8]->DisplayFormat =  retaiformat;
	DBGridEh1->Columns->Items[9]->DisplayFormat =  retaiformat;
	DBGridEh1->Columns->Items[11]->DisplayFormat =  saleformat;
	DBGridEh1->Columns->Items[12]->DisplayFormat =  saleformat;
	DBGridEh1->Columns->Items[13]->DisplayFormat =  storageformat;
	DBGridEh1->Columns->Items[14]->DisplayFormat =  storageformat;
	DBGridEh1->Columns->Items[2]->Footer->DisplayFormat =  storageformat;
	DBGridEh1->Columns->Items[3]->Footer->DisplayFormat =  storageformat;
	DBGridEh1->Columns->Items[5]->Footer->DisplayFormat =  storageformat;
	DBGridEh1->Columns->Items[6]->Footer->DisplayFormat =  storageformat;
	DBGridEh1->Columns->Items[8]->Footer->DisplayFormat =  retaiformat;
	DBGridEh1->Columns->Items[9]->Footer->DisplayFormat =  retaiformat;
	DBGridEh1->Columns->Items[11]->Footer->DisplayFormat =  saleformat;
	DBGridEh1->Columns->Items[12]->Footer->DisplayFormat =  saleformat;
	DBGridEh1->Columns->Items[13]->Footer->DisplayFormat =  storageformat;
	DBGridEh1->Columns->Items[14]->Footer->DisplayFormat =  storageformat;
}
//---------------------------------------------------------------------------

void __fastcall TfrmClearingProvid11::RzToolButton1Click(TObject *Sender)
{
	 if (cbsupplier->Text == "") {
		MessageBox(0,"请选供应商!","提示",MB_ICONEXCLAMATION);
		return;
	 }
	 Query();
}
//---------------------------------------------------------------------------

void __fastcall TfrmClearingProvid11::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmClearingProvid11::RzToolButton3Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmClearingProvid11::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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
	if (Shift.Contains(ssCtrl)&& Key ==90 ) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmClearingProvid11::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void TfrmClearingProvid11::Query()

{
	AnsiString sql,sqlwhere;
	if (cbsupplier->Text  == "") {
    	return;
	}
	int supplierid;
	try {
		supplierid = (int)cbsupplier->Items->Objects[cbsupplier->ItemIndex];
		sqlwhere = sqlwhere + " and bs_storagenoteheader.supplierid = " + IntToStr(supplierid) ;
	} catch (...) {
    	MessageBox(0,"请选择正确的供应商!","提示",MB_ICONEXCLAMATION);
		return;
	}
	if (chisbn->Checked && edisbn->Text != "") {
		sqlwhere = sqlwhere + " and bs_bookcatalog.ISBN = '" + edisbn->Text.Trim() + "'";
	}
	if (chname->Checked && edname->Text != "") {
		sqlwhere = sqlwhere + " and bs_bookcatalog.name like '%" + edname->Text.Trim() + "%'";
	}
	if (chtype->Checked && cbtype->Text != "") {
		sqlwhere = sqlwhere + " and bs_booktype.name = '" + cbtype->Text.Trim() + "'";
	}
	if (chpress->Checked && cpress->Text != "") {
		sqlwhere = sqlwhere + " and bs_pressinfo.AbbreviatedName = '" + cpress->Text.Trim() + "'";
	}
	if (cbstart->Checked ) {
		sqlwhere = sqlwhere + " and datadiff(day,'" + DateToStr(dtp1->Date) + "',bs_storagenoteheader.HdTime) >= 0";
	}
	if (cbend->Checked ) {
		sqlwhere = sqlwhere + " and datadiff(day,'" + DateToStr(dtp2->Date) + "',bs_storagenoteheader.HdTime) <= 0";
	}
	if (chstorage->Checked) {
    	int fstgid;
		try {
			fstgid = (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
			sqlwhere = sqlwhere + " and bs_storagenoteheader.stgid = " + IntToStr(fstgid);
		} catch (...) {
			MessageBox(0,"请选择正确的店号!","提示",MB_ICONEXCLAMATION);
			return;
		}
	}
	switch (rg->ItemIndex ) {
		case 0:
		break;
		case 1:
		break;
		case 2:
		break;
	default:
		;
	}

	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	try {
		query->Open();
	} catch (Exception &E) {
		//ShowMessage(E.Message);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmClearingProvid11::DBGridEh1TitleClick(TColumnEh *Column)
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


