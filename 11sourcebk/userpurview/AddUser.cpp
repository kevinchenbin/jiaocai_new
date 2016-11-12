//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AddUser.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
TfrmAddUser *frmAddUser;
//---------------------------------------------------------------------------
__fastcall TfrmAddUser::TfrmAddUser(TComponent* Owner,TADOConnection *cn,int modle,TADOQuery *aquery,String user,int stgid)
	: TForm(Owner)
{
	Modle = modle;
	if (Modle == 2) {
		this->Caption =  "修改操作员";
	}
	query = aquery;
	User = user;
	fstgid = stgid;
	String sql;
	con = cn;
	querygroup->Connection = cn;
	aq->Connection = cn;
	if (user == "Admin") {
		cbstorge->Enabled = false;
	}
	else
	{
		cbstorge->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmAddUser::FormShow(TObject *Sender)
{
	AnsiString sql;
	/*sql = "select ID,groupname from SYS_group where stgid = " + IntToStr(fstgid) ;
	querygroup->Close();
	querygroup->SQL->Clear();
	querygroup->SQL->Add(sql);
	querygroup->Open();
	while (!querygroup->Eof )
	{
		cbusergroup->AddObject(querygroup->FieldByName("ID")->AsString + querygroup->FieldByName("groupname")->AsString , (TObject*)querygroup->FieldByName("ID")->AsInteger);
		querygroup->Next();
	}*/
	sql = "select ID,Name from SYS_StorageInfo";
	querygroup->Close();
	querygroup->SQL->Clear();
	querygroup->SQL->Add(sql);
	querygroup->Open();
	while (!querygroup->Eof)
	{
		cbstorge->AddObject(querygroup->FieldByName("ID")->AsString + querygroup->FieldByName("Name")->AsString ,(TObject*)querygroup->FieldByName("ID")->AsInteger);
		querygroup->Next();
	}

	if (Modle == 1) {
		//cbusergroup->ItemIndex = cbusergroup->Items->IndexOfObject((TObject*)1);
		cbstorge->ItemIndex = cbstorge->Items->IndexOfObject((TObject*)fstgid);
		/*if (User == "Admin") {
			cbstorge->ItemIndex = cbstorge->Items->IndexOfObject((TObject*)fstgid); }
		else
		{
			sql = "select stgID from SYS_User where Name = '" + User + "'";
			querygroup->Close();
			querygroup->SQL->Clear();
			querygroup->SQL->Add(sql);
			querygroup->Open();
			cbstorge->ItemIndex = cbstorge->Items->IndexOfObject((TObject*)querygroup->FieldByName("stgID")->AsInteger);
		} */
	}
	if (Modle == 2) {     //修改用户
		edname->Text = query->FieldByName("Name")->AsString.Trim();
		edtel->Text = query->FieldByName("tel")->AsString.Trim();
		edmob->Text = query->FieldByName("Mob")->AsString.Trim();
		edjob->Text = query->FieldByName("job")->AsString.Trim();
		edaddress->Text = query->FieldByName("address")->AsString.Trim();
		edbk->Text = query->FieldByName("bk")->AsString.Trim();
		//cbusergroup->ItemIndex = cbusergroup->Items->IndexOfObject((TObject*)query->FieldByName("groupid")->AsInteger);
		cbstorge->ItemIndex = cbstorge->Items->IndexOfObject((TObject*)query->FieldByName("stgID")->AsInteger);
	}
	edname->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAddUser::ednameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		if (edname->Text == "") {
			MessageBox(0,"姓名不能为空！","系统提示" ,MB_OK);
			edname->SetFocus();
		}
		else
			edjob->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmAddUser::edjobKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edtel->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddUser::edtelKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edmob->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmAddUser::edmobKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edaddress->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmAddUser::edaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edbk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddUser::BtnSaveClick(TObject *Sender)
{
	AnsiString sql;
	if (edname->Text == "") {
		MessageBox(0,"请输入姓名！","系统提示" ,MB_ICONWARNING );
		return;
	}
	sql = "select * from SYS_User where name = '" + edname->Text.Trim() + "' and stgID = " + IntToStr(fstgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount > 0 && Modle == 1) {
		MessageBox(0,"该操作员已存在，请重新输入姓名！","系统提示" ,MB_ICONWARNING );
		edname->SetFocus();
		return;
	}
	/*if (cbusergroup->Text == "") {
		MessageBox(0,"请选择用户组！","系统提示" ,MB_OK);
		return;
	} */
	if (Modle == 1) {
		if (query->State != dsInsert) {
			query->Append();
		}
		query->FieldByName("Name")->AsString = edname->Text.Trim();
		query->FieldByName("job")->AsString = edjob->Text.Trim();
		query->FieldByName("tel")->AsString = edtel->Text.Trim();
		query->FieldByName("PassWord")->AsString = "123456";
		query->FieldByName("Mob")->AsString = edmob->Text.Trim();
		//query->FieldByName("groupid")->AsInteger  = (int)(cbusergroup->Items->Objects[cbusergroup->ItemIndex]);
		query->FieldByName("address")->AsString = edaddress->Text.Trim();
		query->FieldByName("bk")->AsString = edbk->Text.Trim();
		query->FieldByName("stgID")->AsInteger = (int)(cbstorge->Items->Objects[cbstorge->ItemIndex]);
		query->UpdateBatch(arAll);
		logmessage = "添加新操作员" + edname->Text ;
		AddEvent(1,"添加新操作员窗口",userid,fstgid,logmessage,con);
		/*sql = "select max(id) as id from SYS_User";
		querygroup->Close();
		querygroup->SQL->Clear();
		querygroup->SQL->Add(sql);
		querygroup->Open();
		int maxid = querygroup->FieldByName("id")->AsInteger ;
		sql = "insert into SYS_UserGroup values(" + IntToStr(maxid) + "," + IntToStr((int)(cbusergroup->Items->Objects[cbusergroup->ItemIndex])) + ",'')";
		querygroup->Close();
		querygroup->SQL->Clear();
		querygroup->SQL->Add(sql);
		querygroup->ExecSQL();*/
		this->Close();
	}
	if (Modle == 2) {
		sql = "update SYS_User set name = '" + edname->Text.Trim() + "',job = '" + edjob->Text.Trim()  + "',tel = '" + edtel->Text.Trim();
		sql = sql + "',Mob = '" + edmob->Text.Trim() ;
		sql = sql + "',address = '" + edaddress->Text.Trim() + "',bk = '" + edbk->Text.Trim() ;
		sql = sql + "',stgID = " + IntToStr((int)(cbstorge->Items->Objects[cbstorge->ItemIndex]));
		sql = sql + " where ID = " + query->FieldByName("ID")->AsString ;
		querygroup->Close();
		querygroup->SQL->Clear();
		querygroup->SQL->Add(sql);
		try {
			querygroup->ExecSQL();
			query->Active = false;
			query->Active = true;
			this->Close();
		} catch (Exception &E) {
			logmessage = E.Message ;
			AddEvent(3,"修改操作员窗口",userid,fstgid,logmessage,con);
			MessageBox(0,"该数据跟系统其他数据有关联，不能修改！","系统提示" ,MB_ICONWARNING);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmAddUser::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddUser::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAddUser::edbkKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddUser::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddUser::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F4) {     //保存
		BtnSave->Click();
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

