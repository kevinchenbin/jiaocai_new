//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitjifendh.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmjifendh *frmjifendh;
//---------------------------------------------------------------------------
__fastcall Tfrmjifendh::Tfrmjifendh(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	fcon = con;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "select jifenmin,jifenmax from SYS_Member_jifen_type where Membertype = -1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbtype->AddItem(aq->FieldByName("jifenmax")->AsAnsiString ,(TObject*)aq->FieldByName("jifenmin")->AsInteger );
		aq->Next();
	}
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmjifendh::cbtypeClick(TObject *Sender)
{
	try {
		int jifenmin = (int)cbtype->Items->Objects[cbtype->ItemIndex];
		edyouhui->Text = IntToStr(jifenmin);
    } catch (...) {
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmjifendh::RzButton1Click(TObject *Sender)
{
	if (cbtype->Text == "") {
		return;
	}
	try {
		if (StrToFloat(cbtype->Text) > StrToFloat(edjifen->Text)) {
			MessageBox(0,"���ֲ��������ܶһ���","��ʾ" ,MB_OK);
			return;
		}
	} catch (...) {
    	return;
	}

    TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	sql = "update CUST_MemberInfo set Memberdot = Memberdot - " + cbtype->Text + " where id = " + IntToStr(memberid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	AnsiString logmessage;
	logmessage = "��Ա��" +  edcard->Text + "�û���" + cbtype->Text + "�һ�" + edyouhui->Text + "Ԫ�Ż�ȯһ��";
	AddEvent(1,"���ֶһ�",userid,stgid,logmessage,fcon);
	delete aq;
	edjifen->Text = FloatToStr(StrToFloat(edjifen->Text) - StrToFloat(cbtype->Text));
	MessageBox(0,"�һ��ɹ���","��ʾ" ,MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmjifendh::RzButton2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
