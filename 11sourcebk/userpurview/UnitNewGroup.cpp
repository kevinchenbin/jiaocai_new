//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitNewGroup.h"
#include "Unitfinduser.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzListVw"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmnewgroup *frmnewgroup;
//---------------------------------------------------------------------------
__fastcall Tfrmnewgroup::Tfrmnewgroup(TComponent* Owner,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
   fcon = cn;
   Type = 1;
   fstgid = stgid;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewgroup::sbaddgroupClick(TObject *Sender)
{
   TListItem *item ;

   Tfrmfinduser * frm = new Tfrmfinduser(Application,fcon,fstgid);
   frm->sbfinduser->Click();
   frm->ShowModal();
   if (frm->SelectUser != "") {
       
 
   for (int i = 0; i < listviewuser->Items->Count ; i++) {
	   if (listviewuser->Items->Item[i]->Caption == frm->SelectUser) {
		 MessageBoxA(0,"ͬһ����ɫ���������ͬ���û�����","����",MB_ICONINFORMATION);
		 return;
	   }
   }

   item = listviewuser->Items->Add();
   item->Caption = frm->SelectUser ;
   item->SubItems->Add(frm->UserDescript);
	}
   delete frm;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewgroup::sbdelgroupClick(TObject *Sender)
{
  if (listviewuser->Selected == NULL) {
	  return;
  }else
  {
	  if (MessageBoxA(0,"ȷ��Ҫ�Ӹý�ɫ���Ƴ���","ѯ��",MB_OKCANCEL||MB_ICONQUESTION)==1 ) {
		  listviewuser->Selected->Delete();
	  }


  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewgroup::sbcreategroupClick(TObject *Sender)
{
   Screen->Cursor = crHourGlass ;
   AnsiString sql;
   AnsiString GroupName,bk;
   if (Type == 1) {
   		sql = "select * from SYS_group where groupname = '" + editgroupname->Text.Trim() + "' and stgid = " + IntToStr(fstgid);
		TADOQuery *aq = new TADOQuery(Application);
		aq->Connection  = fcon ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount > 0) {
			if (MessageBoxA(0,"�ý�ɫ�Ѵ��ڣ��Ƿ���û���ӵ��ý�ɫ�У�","ѯ��",MB_OKCANCEL||MB_ICONQUESTION)!=1 )
			{
				delete aq;
				return;
			}
		}
		delete aq;
   }

   GroupName = editgroupname->Text.Trim();
   bk = editdescript->Text.Trim();
   if (Type == 2) {
	 sql = "delete sys_usergroup where GroupID= " +  IntToStr(GroupID);
	 ExcSQL(sql);
   }
   if (listviewuser->Items->Count == 0) {
		sql = "exec AddUserIntoGroup '','" + GroupName + "','" +bk+"'," + IntToStr(fstgid);
		ExcSQL(sql);
		Sleep(100);
		Application->ProcessMessages();
   }
   for (int i = 0; i < listviewuser->Items->Count ; i++) {
	 sql = "exec AddUserIntoGroup '"+ listviewuser->Items->Item[i]->Caption + "','" + GroupName + "','" +bk+"'," + IntToStr(fstgid);
	 ExcSQL(sql);
	 Sleep(100);
	 Application->ProcessMessages();
   }
   Screen->Cursor = crDefault ;
   logmessage = "�½���ɫ" + editgroupname->Text ;
   AddEvent(1,"�½���ɫ����",userid,fstgid,logmessage,fcon);
   MessageBoxA(0,"����ɹ�!","��ʾ",MB_ICONWARNING);
   Close();
}
void Tfrmnewgroup::ExcSQL(AnsiString SQL)
{
   TADOQuery *aq = new TADOQuery(Application);
   aq->Connection = fcon ;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(SQL);
   aq->ExecSQL();
   delete aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewgroup::spcloseClick(TObject *Sender)
{
   ModalResult = mbOK ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewgroup::FormShow(TObject *Sender)
{
	if (Type == 2) {
		this->Caption = "����";
	   this->sbcreategroup->Caption = "����";

	}

}
void Tfrmnewgroup::ReadyGroupData(int groupID)
{
  String sql;
  TListItem *item;
  sql= "select name,bk from sys_usergroup A inner join sys_user B on A.UserID = B.ID ";
  sql = sql + " where A.GroupID = " + IntToStr(groupID);
  TADOQuery *aq = new TADOQuery(Application);
  aq->Connection  = fcon ;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();
  while(!aq->Eof )
  {
	 item = listviewuser->Items->Add();
	 item->Caption = aq->FieldByName("name")->AsAnsiString ;
	 item->SubItems->Text = aq->FieldByName("bk")->AsAnsiString ;
     aq->Next();
  }

  delete aq;


}
//---------------------------------------------------------------------------


void __fastcall Tfrmnewgroup::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewgroup::BtnExitClick(TObject *Sender)
{
	ModalResult = mbOK ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewgroup::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

