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
	 // ShowMessage("�û�������Ϊ��");
	  MessageBox(0,"�û�������Ϊ��!","Ա������",MB_ICONASTERISK|MB_OK);
}
 else
 {
	 if (s2=="") {
		 // ShowMessage("���벻��Ϊ��");
	  MessageBox(0,"���벻��Ϊ��!","Ա������",MB_ICONASTERISK|MB_OK);
	}
	 else  {

		 if (s2!=s3) {
	  //	  ShowMessage("ʧ�ܣ�������������벻һ�£�");
		 MessageBox(0,"������������벻һ�£�","Ա������",MB_ICONASTERISK|MB_OK);
		}
		 else  {

			if (s2.Length()>6||s3.Length()>6) {

			 MessageBox(0,"���������6λ��","Ա������",MB_ICONASTERISK|MB_OK);
			}
			else
			{

							///

						if (Type1==1) {  ///  �޸�����
							   if (s4!=""&&s4.Length()<7) {
									 if (dsUser->Active) {
										 dsUser->Active=false;
								 }
								 dsUser->CommandText="select * from SYS_UserInfo where Name='"+str1+"' and Password='"+s4+"'";
								  dsUser->Active=true;
								 if (dsUser->IsEmpty()) {
									 ShowMessage("���������");
								 }
								 else
									 {
										cmd->CommandText="update SYS_UserInfo set Password='"+s2+"' where Name='"+str1+"'";
										cmd->Execute();
                                         ShowMessage("�޸ĳɹ�");
									 }




							   }
							   else{ShowMessage("�����벻��Ϊ�������6λ");}


						 }
						  else  //����û�
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
									   //	 ShowMessage("��ӳɹ�");
											 MessageBox(0,"����û��ɹ���","Ա������",MB_ICONASTERISK|MB_OK);
										 edt1->Text=="" ;
									}
								else
								  {MessageBox(0,"���û��Ѵ���!��������ӣ�","Ա������",MB_ICONWARNING|MB_OK);}

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
	 if (Type==1) {    //type=1ʱΪ�޸�����
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

