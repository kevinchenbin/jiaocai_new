//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "adduserForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmadduser *frmadduser;
//---------------------------------------------------------------------------
__fastcall Tfrmadduser::Tfrmadduser(TComponent* Owner)
	: TfrmModalDialog(Owner)
{
}
//---------------------------------------------------------------------------
void Tfrmadduser::Init(LandInfo* li)
{
	TfrmModalDialog::Init(li);
	cmd->Connection=li->con;
	dsUser->Connection=li->con;
	dsGroupID->Connection=li->con;


}
void __fastcall Tfrmadduser::btnOkClick(TObject *Sender)
{
	  String s1=edt1->Text;
	  String s2=edt2->Text;
	  String s3=edt3->Text;
	  String s4=edt4->Text;

if (s1=="") {
	 // ShowMessage("用户名不能为空");
	  MessageBox(0,"用户名不能为空!","员工管理",MB_ICONASTERISK|MB_OK);
}
 else
 {
	 if (s2=="") {
		 // ShowMessage("密码不能为空");
	  MessageBox(0,"密码不能为空!","员工管理",MB_ICONASTERISK|MB_OK);
	}
	 else  {

		 if (s2!=s3) {
	  //	  ShowMessage("失败，两次输入的密码不一致！");
		 MessageBox(0,"两次输入的密码不一致！","员工管理",MB_ICONASTERISK|MB_OK);
		}
		 else  {

			if (s2.Length()>6||s3.Length()>6) {

			 MessageBox(0,"密码最多是6位！","员工管理",MB_ICONASTERISK|MB_OK);
			}
			else
			{

							///

						if (Type1==1) {  ///  修改密码
							   if (s4!=""&&s4.Length()<7) {
									 if (dsUser->Active) {
										 dsUser->Active=false;
								 }
								 dsUser->CommandText="select * from SYS_UserInfo where Name='"+str1+"' and Password='"+s4+"'";
								  dsUser->Active=true;
								 if (dsUser->IsEmpty()) {
									 ShowMessage("旧密码错误");
								 }
								 else
									 {
										cmd->CommandText="update SYS_UserInfo set Password='"+s2+"' where Name='"+str1+"'";
										cmd->Execute();
                                         ShowMessage("修改成功");
									 }




							   }
							   else{ShowMessage("旧密码不能为空且最多6位");}


						 }
						  else  //添加用户
							{

								 if (dsUser->Active) {
										 dsUser->Active=false;
								 }
								 dsUser->CommandText="select * from SYS_UserInfo where Name='"+s1+"'";
								  dsUser->Active=true;

								if (dsUser->IsEmpty()) {

										if (dsGroupID->Active) {
												 dsGroupID->Active=false;
										 }
										 dsGroupID->CommandText="select id from SYS_UserGroupInfo where Name='"+str1+"'";
										  dsGroupID->Active=true;
										 cmd->CommandText="insert into SYS_UserInfo (Name,Password,UserGroupID) values('"+s1+"','"+s2+"',"+dsGroupID->FieldByName("id")->AsString+")";
										 cmd->Execute();
									   //	 ShowMessage("添加成功");
											 MessageBox(0,"添加用户成功！","员工管理",MB_ICONASTERISK|MB_OK);
										 edt1->Text=="" ;
									}
								else
								  {MessageBox(0,"此用户已存在!不能再添加！","员工管理",MB_ICONWARNING|MB_OK);}

						}

				  ///
			}

	 }


	 }
 }

/////


 


}
//---------------------------------------------------------------------------
void Tfrmadduser::deal(String str,int Type)
{
	 str1=str;
	 Type1=Type;
	 if (Type==1) {    //type=1时为修改密码
	   lbl4->Visible=true;
	   edt4->Visible=true;
	   edt1->Text=str;
       edt1->ReadOnly=true;
	 }
	 else
	 {
	 	lbl4->Visible=false;
	   edt4->Visible=false;
	 }
}
void __fastcall Tfrmadduser::FormClose(TObject *Sender, TCloseAction &Action)
{
	 dsUser->Active=false;
	 dsGroupID->Active=false;
}
//---------------------------------------------------------------------------

