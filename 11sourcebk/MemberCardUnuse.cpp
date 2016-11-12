//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberCardUnuse.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMemberCardUnuse *frmMemberCardUnuse;
//---------------------------------------------------------------------------
__fastcall TfrmMemberCardUnuse::TfrmMemberCardUnuse(TComponent* Owner,TADOConnection *cn,int memberid)
	: TForm(Owner)
{
	id = memberid;
	aq->Connection = cn;
	fcon = cn;
	String sql ;
	sql = "select CardID,Name from CUST_MemberInfo where id = " + IntToStr(id);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edcard->Text = aq->FieldByName("CardID")->AsString ;
	edname->Text = aq->FieldByName("Name")->AsString ;
	edcard->Enabled = false;
    edname->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemberCardUnuse::btokClick(TObject *Sender)
{
	String sql ;
	sql = "select PassWord,CardID from CUST_MemberInfo where id = " + IntToStr(id);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	logmessage = aq->FieldByName("CardID")->AsString ;
	if (aq->FieldByName("PassWord") == "" ) {
		sql = "update CUST_MemberInfo set Available = 0 where id = " + IntToStr(id);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		logmessage = "�Ի�Ա��" +  logmessage + "�������˿�";
		AddEvent(1,"��Ա���˿�����",userid,fstgid,logmessage,fcon);
		Close();
	}
	else
	{
		if (aq->FieldByName("PassWord")->AsString != edpassword->Text.Trim()) {
			MessageBox(0,"���������֤�벻��ȷ����ȷ�ϣ�","����" ,MB_ICONWARNING);
			return;
		}
		sql = "update CUST_MemberInfo set Available = 0 where id = " + IntToStr(id);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		logmessage = "�Ի�Ա��" +  logmessage + "�������˿�";
		AddEvent(1,"��Ա���˿�����",userid,fstgid,logmessage,fcon);
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemberCardUnuse::btconcelClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemberCardUnuse::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
