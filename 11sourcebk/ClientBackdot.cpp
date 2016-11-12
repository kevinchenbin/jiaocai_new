//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ClientBackdot.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmClientBackdot *frmClientBackdot;
//---------------------------------------------------------------------------
__fastcall TfrmClientBackdot::TfrmClientBackdot(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
    fstgid = stgid;
	aq->Connection = con;
	query1->Connection = con;
	query2->Connection = con;
	fcon = con;
	String sql ;
	sql = "select ID,Name from CUST_CustomerInfo where Type in(2,3)";
	query1->Close();
	query1->SQL->Clear();
	query1->SQL->Add(sql);
	query1->Open();
	sql = "select ID,Name from SYS_StorageInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
    	cbstorage->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger);
		aq->Next();
	}
	cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)stgid);
	sql = "select Master from SYS_StorageInfo where id = " + IntToStr(stgid);
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->FieldByName("Master")->AsBoolean) {
		cbstorage->Enabled = true;
	}
	else
	{
    	cbstorage->Enabled = false;
	}

	sql = "select BS_ClientBackdot.*,CUST_CustomerInfo.Name,convert(nvarchar(10),BS_ClientBackdot.DiscountLow)+'% - '+convert(nvarchar(10),BS_ClientBackdot.DiscountHight)+'%' as qujian from BS_ClientBackdot left join CUST_CustomerInfo on  BS_ClientBackdot.ClientID = CUST_CustomerInfo.id where StgID = " + IntToStr(fstgid) ;
	query2->Close();
	query2->SQL->Clear();
	query2->SQL->Add(sql);
	query2->Open();
}
//---------------------------------------------------------------------------
void __fastcall TfrmClientBackdot::btqueryClick(TObject *Sender)
{
	String sql ;
	sql = "select * from CUST_CustomerInfo where Type in(2,3)";
	if (edname->Text != "") {
    	sql = sql + " and Name like '%" + edname->Text.Trim() + "%'";
	}
	query1->Close();
	query1->SQL->Clear();
	query1->SQL->Add(sql);
	query1->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientBackdot::SpeedButton1Click(TObject *Sender)
{
	String sql;
	float low,hight,backdot;
	try {
		low = StrToFloat(edlow->Text);
		hight = StrToFloat(edhight->Text);
		backdot = StrToFloat(edbackdot->Text);
	} catch (...) {
		MessageBoxA(0,"请输入正确的折扣!","警告",MB_ICONASTERISK);
	}
	if (low < 0 || hight < 0 || backdot < 0 ) {
		MessageBoxA(0,"折扣不能小于0!","警告",MB_ICONASTERISK);
		return;
	}
	if (hight > 100 || low > 100 || backdot > 100 ) {
		MessageBoxA(0,"折扣不能大于100!","警告",MB_ICONASTERISK);
		return;
	}
	if (low > hight) {
		MessageBoxA(0,"请输入正确的折扣范围!","警告",MB_ICONASTERISK);
		return;
	}

	if (query1->RecordCount > 0) {
		sql = "select * from BS_ClientBackdot where ClientID = " + query1->FieldByName("id")->AsString + " and StgID = " + IntToStr(fstgid) ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount > 0) {
			sql = "update BS_ClientBackdot set BackDot = " + edbackdot->Text.Trim() +",DiscountLow = " + edlow->Text.Trim() + ",DiscountHight = " + edhight->Text.Trim() + " where ID = " + aq->FieldByName("ID")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
		else
		{
			sql = "insert into BS_ClientBackdot(ClientID,DiscountLow,DiscountHight,BackDot,StgID) values (" + query1->FieldByName("id")->AsString + "," + edlow->Text.Trim() + "," + edhight->Text.Trim() + "," + edbackdot->Text.Trim() + ","+ IntToStr(fstgid) + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
		query2->Active = false;
		query2->Active = true;
	}
}

//---------------------------------------------------------------------------
void __fastcall TfrmClientBackdot::SpeedButton2Click(TObject *Sender)
{
	String sql;
	if (!query2->IsEmpty()) {
		sql = "delete from BS_ClientBackdot where id = " + query2->FieldByName("id")->AsString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		query2->Active = false;
		query2->Active = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientBackdot::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientBackdot::edlowKeyPress(TObject *Sender, wchar_t &Key)
{
    if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
	if (Key == '\r') {
        edhight->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientBackdot::edhightKeyPress(TObject *Sender, wchar_t &Key)

{
    if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
	if (Key == '\r') {
        edbackdot->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientBackdot::DBGrid2CellClick(TColumn *Column)
{
	if (query2->RecordCount > 0) {
		edlow->Text = query2->FieldByName("DiscountLow")->AsString ;
		edhight->Text = query2->FieldByName("DiscountHight")->AsString ;
		edbackdot->Text = query2->FieldByName("BackDot")->AsString ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientBackdot::ednameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        btquery->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientBackdot::DBGrid1CellClick(TColumn *Column)
{
	if (query1->Active && query1->RecordCount > 0) {
		AnsiString sql;
		sql = "select * from BS_ClientBackdot where ClientID = " + query1->FieldByName("ID")->AsString + " and StgID = " + IntToStr(fstgid) ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount > 0) {
			edlow->Text = aq->FieldByName("DiscountLow")->AsString ;
			edhight->Text = aq->FieldByName("DiscountHight")->AsString ;
			edbackdot->Text = aq->FieldByName("BackDot")->AsString ;
		}
		else
		{
			edlow->Text = "0";
			edhight->Text = "100";
			edbackdot->Text = "0";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientBackdot::edbackdotKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientBackdot::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized;
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientBackdot::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientBackdot::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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
}
//---------------------------------------------------------------------------

void __fastcall TfrmClientBackdot::cbstorageSelect(TObject *Sender)
{
	AnsiString sql;
	try {
		fstgid =  (int)cbstorage->Items->Objects[cbstorage->ItemIndex];
	} catch (...) {
		MessageBox(0,"请选择正确的店名！","错误" ,MB_OK);
		return;
	}
	sql = "select BS_ClientBackdot.*,CUST_CustomerInfo.Name,convert(nvarchar(10),BS_ClientBackdot.DiscountLow)+'% - '+convert(nvarchar(10),BS_ClientBackdot.DiscountHight)+'%' as qujian from BS_ClientBackdot left join CUST_CustomerInfo on  BS_ClientBackdot.ClientID = CUST_CustomerInfo.id where StgID = " + IntToStr(fstgid) ;
	query2->Close();
	query2->SQL->Clear();
	query2->SQL->Add(sql);
	query2->Open();
}
//---------------------------------------------------------------------------

