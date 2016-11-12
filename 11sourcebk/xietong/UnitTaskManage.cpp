//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitTaskManage.h"
#include "UnitTaskdetail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
Tfrmtaskmanagea *frmtaskmanagea;
//---------------------------------------------------------------------------
__fastcall Tfrmtaskmanagea::Tfrmtaskmanagea(TComponent* Owner)
	: TForm(Owner)
{
}
void Tfrmtaskmanagea::init(TADOConnection *con,int userid,int stgid)
{
	fcon = con;
	fuserid = userid;
	fstgid = stgid;
	aq->Connection = fcon;
	readdata(1);
}
void Tfrmtaskmanagea::readdata(int type)
{
	 AnsiString sql;
	 if (type == 0) {         //布置的任务
		 sql = "select A.creater as UserID,A.ID,taskid,U.name as creater,P.name as receiver,content,title,taskbegin,taskend,state, attachmentname ";
		 sql = sql + " from bs_task A join sys_user U on A.creater = U.ID join sys_user P on A.receiver = P.ID where A.creater = "+IntToStr(fuserid);
	 }else
	 {                              //收到的任务
		 sql = "select UP.name as receiver,A.creater as UserID,P.name as creater,A.ID,A.taskid,content,title,taskbegin,taskend,state, attachmentname from bs_task A join BS_TaskReceiver U ";
		 sql = sql + " on A.taskid = U.TaskID join sys_user P on A.creater = P.ID  join sys_user UP on UP.ID = U.ReceiveUserID where  U.ReceiveUserID= "+IntToStr(fuserid);

	 }

	 aq->Close();
	 aq->SQL->Clear();
	 aq->SQL->Add(sql);
	 aq->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmtaskmanagea::BtnClick(TObject *Sender)
{     //新建任务

	  Tfrmnewtask *frm = new Tfrmnewtask(Application);
	  frm->Caption = "新建任务";
      frm->Model = -1;
	  frm->init(fcon,fuserid);
	  frm->checkUserID = fuserid;
	  frm->ShowModal();
	  delete frm;

}
//---------------------------------------------------------------------------
void __fastcall Tfrmtaskmanagea::Btn1Click(TObject *Sender)
{
readdata(0);  //
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtaskmanagea::Btn2Click(TObject *Sender)
{
readdata(1);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtaskmanagea::N1Click(TObject *Sender)
{
	  AnsiString UserStr,sql;
	  Tfrmnewtask *frm = new Tfrmnewtask(Application);
	  frm->Caption = "任务详细";
	  //fuserid
	   sql = "select Name from BS_TaskReceiver T join sys_user U ON T.ReceiveUserID  = U.ID where T.TaskID ='";
	   sql = sql + aq->FieldByName("taskid")->AsAnsiString +"'";
	   frm->TaskID = aq->FieldByName("taskid")->AsAnsiString ;
	  frm->init(fcon,aq->FieldByName("UserID")->AsInteger);
	  TADOQuery *aaq = new TADOQuery(NULL);
	  aaq->Connection = fcon ;
	  aaq->Close();
	  aaq->SQL->Clear();
	  aaq->SQL->Add(sql);
	  aaq->Open();
	  while(!aaq->Eof)
	  {
		UserStr = UserStr + aaq->FieldByName("Name")->AsAnsiString +";" ;
		aaq->Next();
	  }
	  delete aaq;

	  frm->editreceiver->Text = UserStr;
	  frm->DateTimePicker1->Date = aq->FieldByName("taskbegin")->AsDateTime ;
	  frm->DateTimePicker2->Date = aq->FieldByName("taskend")->AsDateTime ;
	  frm->cbstate->Text = aq->FieldByName("state")->AsAnsiString ;
	  frm->edittitle->Text = aq->FieldByName("title")->AsAnsiString ;
	  frm->memcontent->Text = aq->FieldByName("content")->AsAnsiString ;
	  frm->editattchment->Text = aq->FieldByName("attachmentname")->AsAnsiString;
	  frm->SpeedButton1->Caption = "下载";
	  frm->SpeedButton2->Enabled = false;
	  frm->SpeedButton3->Caption = "退出";
	  frm->ShowModal();
	  delete frm;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmtaskmanagea::N3Click(TObject *Sender)
{
//
  AnsiString UserStr,sql;
	  Tfrmnewtask *frm = new Tfrmnewtask(Application);
	  frm->Caption = "任务修改";
	  //fuserid
	   sql = "select Name from BS_TaskReceiver T join sys_user U ON T.ReceiveUserID  = U.ID where T.TaskID ='";
	   sql = sql + aq->FieldByName("taskid")->AsAnsiString +"'";
	   frm->TaskID = aq->FieldByName("taskid")->AsAnsiString ;
	  frm->init(fcon,aq->FieldByName("UserID")->AsInteger); //用户不同就不能修改
	  frm->checkUserID  = fuserid ;
	  TADOQuery *aaq = new TADOQuery(NULL);
	  aaq->Connection = fcon ;
	  aaq->Close();
	  aaq->SQL->Clear();
	  aaq->SQL->Add(sql);
	  aaq->Open();
	  while(!aaq->Eof)
	  {
		UserStr = UserStr + aaq->FieldByName("Name")->AsAnsiString +";" ;
		aaq->Next();
	  }
	  delete aaq;
	  frm->Model = aq->FieldByName("ID")->AsInteger  ;
	  frm->editreceiver->Text = UserStr;
	  frm->DateTimePicker1->Date = aq->FieldByName("taskbegin")->AsDateTime ;
	  frm->DateTimePicker2->Date = aq->FieldByName("taskend")->AsDateTime ;
	  frm->cbstate->Text = aq->FieldByName("state")->AsAnsiString ;
	  frm->edittitle->Text = aq->FieldByName("title")->AsAnsiString ;
	  frm->memcontent->Text = aq->FieldByName("content")->AsAnsiString ;
	  frm->editattchment->Text = aq->FieldByName("attachmentname")->AsAnsiString;
   //	  frm->SpeedButton1->Caption = "";
	 // frm->SpeedButton2->Enabled = false;
	//  frm->SpeedButton3->Caption = "退出";
	  if (mbOK == frm->ShowModal())
	  {
		Btn->Click();
	  }
	  delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtaskmanagea::rzdbDblClick(TObject *Sender)
{
  N1->Click();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmtaskmanagea::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtaskmanagea::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

