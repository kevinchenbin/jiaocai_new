//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Syspwdchange.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmsyspwdchange *frmsyspwdchange;
//---------------------------------------------------------------------------
__fastcall Tfrmsyspwdchange::Tfrmsyspwdchange(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	aq->Connection = con;
	fcon = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsyspwdchange::btOKClick(TObject *Sender)
{
	AnsiString sql,pwd;
	sql = "select bk from sys_bsset where name ='changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	pwd = aq->FieldByName("bk")->AsString ;
	if (pwd != edoldpwd->Text ) {
		AddEvent(3,"单号显示规则密码修改窗口",userid,storageid,"密码输入错误",fcon);
		MessageBoxA(0,"密码输入错误！","错误",MB_ICONERROR);
		return;
	}
	if (ednewpwd->Text != edpwdagain->Text ) {
		AddEvent(2,"单号显示规则密码修改窗口",userid,storageid,"两次输入密码不一致",fcon);
		MessageBoxA(0,"两次输入密码不一致！","错误",MB_ICONERROR);
		return;
	}
	sql = "update sys_bsset set bk = '" + ednewpwd->Text.Trim() + "' where name = 'changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	try {
		aq->ExecSQL();
		AddEvent(1,"单号显示规则密码修改窗口",userid,storageid,"密码更改成功",fcon);
		MessageBox(0,"密码更改成功！","提示",MB_ICONEXCLAMATION );
		Close();
	} catch (...) {
		AddEvent(3,"单号显示规则密码修改窗口",userid,storageid,"密码更改出错",fcon);
		MessageBoxA(0,"密码修改失败！","提示",MB_ICONERROR);
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsyspwdchange::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsyspwdchange::btConcelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
