//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserGroupPermissionsForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzTreeVw"
#pragma link "RzDBChk"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TfrmUserGroupPermissions *frmUserGroupPermissions;
//---------------------------------------------------------------------------
__fastcall TfrmUserGroupPermissions::TfrmUserGroupPermissions(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
       m_module =MTUser;
}
//---------------------------------------------------------------------------
void TfrmUserGroupPermissions::Init(LandInfo* li)
{
	 TfrmMDIChild::Init(li);
	dsUserGroup->Connection=li->con;
	dsuser->Connection=li->con;
	cmd->Connection=li->con;
	this->deal();

}
void __fastcall TfrmUserGroupPermissions::FormClose(TObject *Sender, TCloseAction &Action)

{      dsUserGroup->Active=false;
		dsuser->Active=false;
		cmd->Destroying();
		Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserGroupPermissions::RzToolButton5Click(TObject *Sender)
{
	 Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmUserGroupPermissions::tvUserGroupClick(TObject *Sender)
{
   if (tvUserGroup->Selected!=NULL)
   {

		   if (tvUserGroup->Selected->Level==0)

		   {
			 dsUserGroup->RecNo=tvUserGroup->Selected->Index+1;
		   }
		   else
		   {
			 dsUserGroup->RecNo=tvUserGroup->Selected->Parent->Index+1;
		   }
   }
}
//---------------------------------------------------------------------------


void __fastcall TfrmUserGroupPermissions::btn1Click(TObject *Sender)
{
		if (dsUserGroup->State == dsEdit || dsUserGroup->State == dsInsert)
	{
		dsUserGroup->Post();
		ShowMessage("保存成功！");
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmUserGroupPermissions::RzToolButton1Click(TObject *Sender)
{
		Tfrmadd* frm = new Tfrmadd(Application);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm->Init(&li);

		if (mrOk == frm->ShowModal())
		{
			  tvUserGroup->Items->Clear();
			  this->deal();
		}
		delete frm;

}
//---------------------------------------------------------------------------
void TfrmUserGroupPermissions::deal()
	{
       		if (dsUserGroup->Active) {
		  dsUserGroup->Active=false;
	}
	String sql="select * from SYS_UserGroupInfo";
	dsUserGroup->CommandText=sql;
	 dsUserGroup->Active=true;
	   dsUserGroup->First();

	   while (!dsUserGroup->Eof)
		   {
		Node1 = this->tvUserGroup->Items->AddChild(NULL,dsUserGroup->FieldByName("Name")->AsString);
		   if (dsuser->Active) {
			  dsuser->Active=false;
		   }
		   dsuser->CommandText="select * from  SYS_UserInfo where UserGroupID="+dsUserGroup->FieldByName("id")->AsString;
			dsuser->Active=true;
			  dsuser->First();
			while (!dsuser->Eof)
				  {
				   this->tvUserGroup->Items->AddChild(Node1,dsuser->FieldByName("Name")->AsString);
					dsuser->Next();
				  }

		dsUserGroup->Next();
	 }
	 dsUserGroup->First();


	}
void __fastcall TfrmUserGroupPermissions::RzToolButton3Click(TObject *Sender)
{
   if (tvUserGroup->Selected!=NULL&&tvUserGroup->Selected->Level==0) {
	 if (tvUserGroup->Selected->Text=="系统管理员"||tvUserGroup->Selected->Text=="业务员"){
            ShowMessage("系统管理员组和业务员组不能删除！");
	 }
	 else{
			  if(MessageDlg(" 确认删除“"+tvUserGroup->Selected->Text+"”吗？", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
				 {
					 try{
					 cmd->CommandText="delete from SYS_UserGroupInfo where Name='"+tvUserGroup->Selected->Text+"'";
					 cmd->Execute();
					 tvUserGroup->Selected->Delete();
					 }
				   catch(Exception &E)
					 {
					   ShowMessage("此数据更系统其他地方有关联，不能删除！");
					 }

				}
	 }
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserGroupPermissions::RzToolButton4Click(TObject *Sender)
{     if (tvUserGroup->Selected->Level==1&&tvUserGroup->Selected!=NULL) {



	  if(MessageDlg(" 确认删除“"+tvUserGroup->Selected->Text+"”吗？", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
	 {
		 try{

		 cmd->CommandText="delete from SYS_UserInfo where Name='"+tvUserGroup->Selected->Text+"'";
		 cmd->Execute();
		 tvUserGroup->Selected->Delete();
		 }
	   catch(Exception &E)
				 {
					  ShowMessage("此数据更系统其他地方有关联，不能删除！");
				 }

	}
	   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserGroupPermissions::RzToolButton2Click(TObject *Sender)
{

if (!dsUserGroup->IsEmpty()) {

	if(MessageDlg(" 确认添加员工到 “"+dsUserGroup->FieldByName("Name")->AsString+" ”组吗？", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
	 {
		Tfrmadduser* frm1 = new Tfrmadduser(Application);
		LandInfo li;
		li.app = m_app;
		li.con = m_con;
		li.userID = m_userID;
		li.storageID = m_storageID;
		frm1->Init(&li);
		frm1->deal(dsUserGroup->FieldByName("Name")->AsString,0);

		if (mrOk == frm1->ShowModal())
		{
			  tvUserGroup->Items->Clear();
			  this->deal();
		}
		delete frm1;
  }
 }
}
//---------------------------------------------------------------------------



void __fastcall TfrmUserGroupPermissions::RzToolButton6Click(TObject *Sender)
{

		   if (tvUserGroup->Selected!=NULL&&tvUserGroup->Selected->Level==1) {


								Tfrmadduser* frm1 = new Tfrmadduser(Application);
								LandInfo li;
								li.app = m_app;
								li.con = m_con;
								li.userID = m_userID;
								li.storageID = m_storageID;
								frm1->Init(&li);
								frm1->deal(tvUserGroup->Selected->Text,1);

								if (mrOk == frm1->ShowModal())
								{
									  tvUserGroup->Items->Clear();
									  this->deal();
								}
								delete frm1;
						  }


}
//---------------------------------------------------------------------------



void __fastcall TfrmUserGroupPermissions::FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
			if (Key==0x1B) {   //esc
			 this->RzToolButton5->Click();

		}
				if (Key==0x70) {   //F1
			 this->RzToolButton2->Click();

		}
				if (Key==0x71) {   //F2
		 this->RzToolButton4->Click();

		}
				if (Key==0x72) {   //F3
		 this->RzToolButton6->Click();

		}

		if (Shift.Contains(ssCtrl)&&Key==65) {     //A

		   this->RzToolButton1->Click();
	}
			if (Shift.Contains(ssCtrl)&&Key==68) {     //D

		   this->RzToolButton3->Click();
	}
}
//---------------------------------------------------------------------------

