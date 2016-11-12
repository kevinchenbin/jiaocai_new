//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitfinduser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmfinduser *frmfinduser;
//---------------------------------------------------------------------------
__fastcall Tfrmfinduser::Tfrmfinduser(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
fcon = cn;
fstgid = stgid;
}
void Tfrmfinduser::finduser(AnsiString descript,AnsiString Username)
{
  String sql;
  TListItem *item;
  if (descript == "" && Username != "") {
   sql = "select ID,Name,bk from sys_user where name like '%"+ Username +"%' and stgid = " + IntToStr(fstgid);
  }else if (Username == "" && descript != "") {
	 sql = "select ID,Name,bk from sys_user where bk like '%"+ descript +"%' and stgid = " + IntToStr(fstgid);
  }else if (Username != "" && descript != "") {
	 sql = "select ID,Name,bk from sys_user where bk like '%"+ descript +"%' and name like '%" + Username + "%' and stgid = " + IntToStr(fstgid);
  }else if (Username == "" && descript == "") {
		sql = "select ID,Name,bk from sys_user where stgid = " + IntToStr(fstgid);
		}

  aq->Connection = fcon;
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();
  lvuserlist->Items->Clear();
  lvuserlist->Items->BeginUpdate();
  while(!aq->Eof)
  {
	 item = lvuserlist->Items->Add();
	 item->SubItems->Add(aq->FieldByName("bk")->AsAnsiString)  ;
	 item->Caption  = aq->FieldByName("Name")->AsAnsiString ;
	 aq->Next();
  }
  lvuserlist->Items->EndUpdate();

}
//---------------------------------------------------------------------------

void __fastcall Tfrmfinduser::sbfinduserClick(TObject *Sender)
{
	finduser(editdescrip->Text,editname->Text);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfinduser::editnameKeyPress(TObject *Sender, wchar_t &Key)
{
  if (Key == VK_RETURN) {
     sbfinduser->Click();

  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfinduser::lvuserlistDblClick(TObject *Sender)
{

	 if (lvuserlist->Selected == NULL) {
		 return;
	 }else
	 {

	  SelectUser = lvuserlist->Selected->Caption;
	  UserDescript = lvuserlist->Selected->SubItems->Text ;
      Close();
	 }
}
//---------------------------------------------------------------------------
void __fastcall Tfrmfinduser::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfinduser::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfinduser::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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

