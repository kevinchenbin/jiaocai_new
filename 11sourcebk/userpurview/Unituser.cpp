//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unituser.h"
#include "AddUser.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmuser *frmuser;
//---------------------------------------------------------------------------
__fastcall Tfrmuser::Tfrmuser(TComponent* Owner,TADOConnection *cn,String user,int stgid,int sid)
	: TForm(Owner)
{
	aquery->Connection = cn;
	query->Connection = cn;
	cnn = cn;
	User = user;
	AnsiString sql;
	fstgid = stgid;
	userid = sid;
	/*sql = "select stgID from SYS_User where Name = '" + user + "'";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	int stgID = aquery->FieldByName("stgID")->AsInteger ;
	sql = "select A.*,B.groupname,C.Name as storgename from SYS_User A inner join SYS_group B on A.groupid = B.ID left join SYS_StorageInfo C on A.stgID = C.ID";
	if (user != "Admin") {
    	sql = sql + " where A.stgID = " + IntToStr(stgID);
	} */
	sql = "select A.*,C.Name as storgename from SYS_User A left join SYS_StorageInfo C on A.stgID = C.ID where A.stgid = " + IntToStr(stgid) ;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmuser::BtnNewClick(TObject *Sender)
{
	TfrmAddUser * frm = new TfrmAddUser(Application,cnn,1,aquery,User,fstgid);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmuser::BtnChangeOptionsClick(TObject *Sender)
{
	if (aquery->Active && aquery->RecordCount > 0) {
		if (aquery->FieldByName("Name")->AsAnsiString == "Admin" ) {
			MessageBox(0,"默认系统管理员不能修改！","系统提示" ,MB_OK);
			return;
		}
		TfrmAddUser * frm = new TfrmAddUser(Application,cnn,2,aquery,User,fstgid);
		frm->ShowModal();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmuser::BtnDeleteClick(TObject *Sender)
{
	String sql;
	if (aquery->Active && aquery->RecordCount > 0) {
    	if (aquery->FieldByName("Name")->AsAnsiString == "Admin" ) {
			MessageBox(0,"默认系统管理员不能删除！","系统提示" ,MB_OK);
			return;
		}
		if (MessageBox(0,"确认删除该操作员？","删除操作员" ,MB_OKCANCEL)==1) {
			try {
				sql = "delete from SYS_UserGroup where UserID = " + aquery->FieldByName("ID")->AsString;
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->ExecSQL();
				sql = "delete from SYS_User where ID = " + aquery->FieldByName("ID")->AsString;
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				logmessage = "删除操作员" + aquery->FieldByName("Name")->AsString;
				AddEvent(1,"操作员管理窗口",userid,fstgid,logmessage,cnn);
				query->ExecSQL();
				aquery->Active = false;
				aquery->Active = true;
			} catch (Exception &E) {
            	logmessage = E.Message ;
				AddEvent(3,"操作员管理窗口",userid,fstgid,logmessage,cnn);
				MessageBox(0,"该数据跟系统其他数据有关联，不能删除！","系统提示" ,MB_OK);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmuser::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmuser::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmuser::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmuser::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {     //添单
		BtnNew->Click();
	}
	if (Key == VK_F5) {     //删除
		BtnDelete->Click();
	}
	if (Key == VK_F3) {     //修改
		BtnChangeOptions->Click();
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

