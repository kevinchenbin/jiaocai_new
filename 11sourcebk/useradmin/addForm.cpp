//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "addForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmadd *frmadd;
//---------------------------------------------------------------------------
__fastcall Tfrmadd::Tfrmadd(TComponent* Owner)
	: TfrmModalDialog(Owner)
{
}
//---------------------------------------------------------------------------
void Tfrmadd::Init(LandInfo* li)
{
	TfrmModalDialog::Init(li);
	 cmd->Connection=li->con;
	 dsUserGroup->Connection=li->con;

}
void __fastcall Tfrmadd::btnOkClick(TObject *Sender)
{  

 if (edt1->Text!="") {
		 if (dsUserGroup->Active) {
				 dsUserGroup->Active=false;
		 }
		 dsUserGroup->CommandText="select * from SYS_UserGroupInfo where Name='"+edt1->Text+"'";
		  dsUserGroup->Active=true;
		  
		if (dsUserGroup->IsEmpty()) {
	

		 
		 cmd->CommandText="insert into SYS_UserGroupInfo (Name) values('"+edt1->Text+"')";
		  cmd->Execute();
		  //ShowMessage("添加成功");
		   MessageBox(0,"添加用户组成功！","用户组管理",MB_ICONASTERISK|MB_OK);
		 edt1->Text=="" ;
		}
		else
		  {  MessageBox(0,"此用户组已存在,不能再添加!","用户组管理",MB_ICONWARNING|MB_OK);}

	 }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmadd::FormClose(TObject *Sender, TCloseAction &Action)
{
	 dsUserGroup->Active=false;
}
//---------------------------------------------------------------------------

