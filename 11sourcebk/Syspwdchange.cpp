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
		AddEvent(3,"������ʾ���������޸Ĵ���",userid,storageid,"�����������",fcon);
		MessageBoxA(0,"�����������","����",MB_ICONERROR);
		return;
	}
	if (ednewpwd->Text != edpwdagain->Text ) {
		AddEvent(2,"������ʾ���������޸Ĵ���",userid,storageid,"�����������벻һ��",fcon);
		MessageBoxA(0,"�����������벻һ�£�","����",MB_ICONERROR);
		return;
	}
	sql = "update sys_bsset set bk = '" + ednewpwd->Text.Trim() + "' where name = 'changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	try {
		aq->ExecSQL();
		AddEvent(1,"������ʾ���������޸Ĵ���",userid,storageid,"������ĳɹ�",fcon);
		MessageBox(0,"������ĳɹ���","��ʾ",MB_ICONEXCLAMATION );
		Close();
	} catch (...) {
		AddEvent(3,"������ʾ���������޸Ĵ���",userid,storageid,"������ĳ���",fcon);
		MessageBoxA(0,"�����޸�ʧ�ܣ�","��ʾ",MB_ICONERROR);
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
