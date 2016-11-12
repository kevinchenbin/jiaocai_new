//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitLog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzListVw"
#pragma link "RzCmboBx"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmLog *frmLog;
//---------------------------------------------------------------------------
__fastcall TfrmLog::TfrmLog(TComponent* Owner,TADOConnection *cn,int userid,int stgid)
	: TForm(Owner)
{
	dtpstart->Date = Date();
	dtpend->Date = Date();
	con = cn;
	aq->Connection = cn;
	query->Connection = cn;
	fuserid = userid;
	fstgid = stgid;
    ReadData();
}
//---------------------------------------------------------------------------
void TfrmLog::ReadData()
{
	AnsiString sql;
	sql = "select ID,Name from SYS_StorageInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbstorage->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	cbstorage->ItemIndex = cbstorage->Items->IndexOfObject((TObject*)fstgid);
	sql = "select ID,Name from sys_user where StgID = " + IntToStr(fstgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbuser->AddItem(aq->FieldByName("Name")->AsString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	cbuser->ItemIndex = cbuser->Items->IndexOfObject((TObject*)fuserid);
	cbtype->Add("信息");
	cbtype->Add("警告");
	cbtype->Add("错误");
	cbtype->Text = "信息";
	sql = "select distinct SourceFrom from sys_log";
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbsuorefrom->Add(aq->FieldByName("SourceFrom")->AsAnsiString );
		aq->Next();
	}
	aq->First();
	cbsuorefrom->Text = aq->FieldByName("SourceFrom")->AsAnsiString;
}
//---------------------------------------------------------------------------
void __fastcall TfrmLog::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	AnsiString sql;
	sql = "select distinct SourceFrom from sys_log where SourceFrom like '%" + edquery->Text + "%'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbsuorefrom->Clear();
	while (!aq->Eof )
	{
		cbsuorefrom->Add(aq->FieldByName("SourceFrom")->AsAnsiString );
		aq->Next();
	}
	aq->First();
	cbsuorefrom->Text = aq->FieldByName("SourceFrom")->AsAnsiString;
}
//---------------------------------------------------------------------------

void __fastcall TfrmLog::BtnViewClick(TObject *Sender)
{
	AnsiString sql;
	sql = " select sys_log.*,sys_user.Name as username,sys_storageinfo.Name as storagename from sys_log left join sys_user on sys_log.EventUser = sys_user.id "
		" left join sys_storageinfo on sys_log.stgName = sys_storageinfo.id where 1 = 1 ";
	if (chstarttime->Checked ) {
		sql = sql + " and sys_log.EventDate >= '" + DateToStr(dtpstart->Date) + "'";
	}
	if (chendtime->Checked ) {
		sql = sql + " and sys_log.EventDate <= '" + DateToStr(dtpend->Date) + " 23:59:59'";
	}
	if (chsourcefrom->Checked ) {
		sql = sql + " and sys_log.SourceFrom = '" + cbsuorefrom->Text + "'";
	}
	if (chtype->Checked ) {
		sql = sql + " and sys_log.Eventtype = '" + cbtype->Text + "'";
	}
	if (chstorage->Checked ) {
		sql = sql + " and sys_storageinfo.Name = '" + cbstorage->Text + "'";
	}
	if (chuser->Checked ) {
		sql = sql + " and sys_user.Name = '" + cbuser->Text + "'";
	}
	if (chneirong->Checked ) {
		sql = sql + " and sys_log.EventMessage  like '%" + edneirong->Text + "%'";
	}
	sql = sql + " order by EventDate desc";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	lv->Items->Clear();
	lv->Items->Count = query->RecordCount ;

	/*while (!query->Eof )
	{
		TListItem *item = lv->Items->Add();
		item->SubItems->Add(query->FieldByName("Eventtype")->AsString);
		item->SubItems->Add(query->FieldByName("SourceFrom")->AsString);
		item->SubItems->Add(query->FieldByName("EventDate")->AsString);
		item->SubItems->Add(query->FieldByName("username")->AsString);
		item->SubItems->Add(query->FieldByName("storagename")->AsString);
		item->SubItems->Add(query->FieldByName("EventMessage")->AsString);
		query->Next();
	} */
}
//---------------------------------------------------------------------------

void __fastcall TfrmLog::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized;
}
//---------------------------------------------------------------------------

void __fastcall TfrmLog::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmLog::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		BtnView->Click();
	}
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

void __fastcall TfrmLog::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmLog::lvData(TObject *Sender, TListItem *Item)
{
	query->RecNo = Item->Index + 1;
	//Item->caption = Item->SubItems->Add(query->FieldByName("Eventtype")->AsString);
	Item->SubItems->Add(query->FieldByName("Eventtype")->AsString);
	Item->SubItems->Add(query->FieldByName("SourceFrom")->AsString);
	Item->SubItems->Add(query->FieldByName("EventDate")->AsString);
	Item->SubItems->Add(query->FieldByName("username")->AsString);
	Item->SubItems->Add(query->FieldByName("storagename")->AsString);
	Item->SubItems->Add(query->FieldByName("EventMessage")->AsString);

}
//---------------------------------------------------------------------------

void __fastcall TfrmLog::ListView1Data(TObject *Sender, TListItem *Item)
{
	query->RecNo = Item->Index + 1;
	//Item->caption = Item->SubItems->Add(query->FieldByName("Eventtype")->AsString);
	Item->SubItems->Add(query->FieldByName("Eventtype")->AsString);
	Item->SubItems->Add(query->FieldByName("SourceFrom")->AsString);
	Item->SubItems->Add(query->FieldByName("EventDate")->AsString);
	Item->SubItems->Add(query->FieldByName("username")->AsString);
	Item->SubItems->Add(query->FieldByName("storagename")->AsString);
	Item->SubItems->Add(query->FieldByName("EventMessage")->AsString);
}
//---------------------------------------------------------------------------

