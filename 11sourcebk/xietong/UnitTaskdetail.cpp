//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitTaskdetail.h"
#include "UnitreceiverSelect.h"
#include   <StrUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzShellDialogs"
#pragma resource "*.dfm"
Tfrmnewtask *frmnewtask;
//---------------------------------------------------------------------------
__fastcall Tfrmnewtask::Tfrmnewtask(TComponent* Owner)
	: TForm(Owner)
{
}
void Tfrmnewtask::init(TADOConnection *cn,int userid)
{
	fcn = cn;
	AnsiString sql;
	sql = "select name from sys_user where id = "+ IntToStr(userid);
	aq->Connection = fcn;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

   edituser->Text = aq->FieldByName("name")->AsAnsiString ;
   newtask->Connection = fcn;
   SendMsgReceiver->Connection = fcn;
   intuserid = userid;
}

//---------------------------------------------------------------------------
void __fastcall Tfrmnewtask::SpeedButton4Click(TObject *Sender)
{
   tempstr = new TStringList();
   Tfrmuserselect *frm = new Tfrmuserselect(Application);
   frm->init(fcn,tempstr);

   if (mrOk == frm->ShowModal() ) {
	 for (int i =0 ; i < tempstr->Count ; i++) {
		  editreceiver->Text = editreceiver->Text + tempstr->Strings[i]  +";";
	 }
   }
   delete frm;

}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewtask::SpeedButton1Click(TObject *Sender)
{
  if (((TSpeedButton*)Sender)->Caption == "����") {
	if (editattchment->Text == "") {
		MessageBoxA(0,"û�и����ɹ�����!","��ʾ",MB_ICONASTERISK);
		return;
	}
	savefile->DefaultExt =   ExtractFileExt(editattchment->Text);
	savefile->FileName =  editattchment->Text;
	if (savefile->Execute()) {
		AnsiString SavePath1 = savefile->FileName ;

		//���ظ���
		AnsiString sql = "select attachment from bs_task where TaskId ='" + TaskID+"'";
		TADOQuery *aaq = new TADOQuery(NULL);
		aaq->Connection = fcn ;
		aaq->Close();
		aaq->SQL->Clear();
		aaq->SQL->Add(sql);
		aaq->Open();
	   try
	   {
	   TBlobField *Field = (TBlobField*)aaq->FieldByName("attachment");
	   Field->SaveToFile(SavePath1);
	   delete aaq;

	   }catch(...)
	   {
		 MessageBoxA(0,"�ļ������з�������!","��ʾ",MB_ICONASTERISK);
		  return;
	   }

	   try
	   {
		   if (1==MessageBoxA(0,"�ļ����سɹ�,�Ƿ�򿪣�","��ʾ",MB_YESNO||MB_ICONQUESTION))
		   {
			 ShellExecute(NULL,"open",SavePath1.c_str() ,"","",SW_SHOW);
		   }
	   }catch(...)
	   {
		  MessageBoxA(0,"�ļ���ʧ��!","��ʾ",MB_ICONASTERISK);
		  return;
	   }
	}
  }else
  {
	  if (openfile->Execute()) {
		 editattchment->Text  = openfile->FileName ;
	  }
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewtask::SpeedButton2Click(TObject *Sender)
{
  //save


  if (Model >= 0) {      //�޸�
        AnsiString TaskStr;
    if (checkUserID != intuserid) {
     	 MessageBoxA(0,"���������������������޸ģ�","����",MB_ICONINFORMATION);
	 return;
  }

  newtask->Parameters->ParamByName("@creater")->Value = intuserid;
  newtask->Parameters->ParamByName("@contenta")->Value = memcontent->Text ;
  newtask->Parameters->ParamByName("@title")->Value =edittitle->Text  ;
  newtask->Parameters->ParamByName("@taskbegin")->Value = DateTimePicker1->Date ;
  newtask->Parameters->ParamByName("@taskend")->Value = DateTimePicker2->Date;
  newtask->Parameters->ParamByName("@state")->Value = cbstate->Text;

  if (FileExists(editattchment->Text.Trim()) ) {
	 newtask->Parameters->ParamByName("@attachmentname")->Value = ExtractFileName(editattchment->Text.Trim());
	 newtask->Parameters->ParamByName("@attachment")->LoadFromFile(editattchment->Text.Trim(),ftBlob)  ;
  }else
  {
	newtask->Parameters->ParamByName("@attachmentname")->Value =  "";
	// newtask->Parameters->ParamByName("@attachment")->Value = NULL)  ;
  }

  try
  {     newtask->Parameters->ParamByName("@Modal")->Value = Model;   //����0Ϊ�������ID��
		newtask->Parameters->ParamByName("@TaskIDStr")->Value = TaskID;
		Screen->Cursor = crHandPoint ;
		newtask->ExecProc();
		TaskStr = TaskID ; // newtask->Parameters->ParamByName("@TaskIDStr")->Value;
		AnsiString Receiver;

		for (int i =0 ; i < tempstr->Count ; i++) {
			 Receiver = Receiver + IntToStr(int(tempstr->Objects[i]))  +",";
		}

		Receiver = LeftStr(Receiver,Receiver.Length()-1);
		SendMsgReceiver->Parameters->ParamByName("@string")->Value = Receiver;
		SendMsgReceiver->Parameters->ParamByName("@Model")->Value = 1;
		SendMsgReceiver->Parameters->ParamByName("@TaskID")->Value = TaskStr;
		SendMsgReceiver->ExecProc();
		Screen->Cursor = crDefault ;
	 }
	 catch(...)
	 {}

     ModalResult = mbOK ;

  }else
  {
  AnsiString TaskStr;


  newtask->Parameters->ParamByName("@creater")->Value = intuserid;
  newtask->Parameters->ParamByName("@contenta")->Value = memcontent->Text ;
  newtask->Parameters->ParamByName("@title")->Value =edittitle->Text  ;
  newtask->Parameters->ParamByName("@taskbegin")->Value = DateTimePicker1->Date ;
  newtask->Parameters->ParamByName("@taskend")->Value = DateTimePicker2->Date;
  newtask->Parameters->ParamByName("@state")->Value = "ִ����";

  if (FileExists(editattchment->Text.Trim()) ) {
	newtask->Parameters->ParamByName("@attachmentname")->Value = ExtractFileName(editattchment->Text.Trim());
  }else
  {
	newtask->Parameters->ParamByName("@attachmentname")->Value =  ExtractFileName(editattchment->Text.Trim());
  }
  newtask->Parameters->ParamByName("@attachment")->LoadFromFile(editattchment->Text.Trim(),ftBlob)  ;
  try
  {     newtask->Parameters->ParamByName("@Modal")->Value =-1;
		newtask->Parameters->ParamByName("@TaskIDStr")->Value = "00000000000000000000";
		Screen->Cursor = crHandPoint ;
		newtask->ExecProc();
		TaskStr =  newtask->Parameters->ParamByName("@TaskIDStr")->Value;
		AnsiString Receiver;

		for (int i =0 ; i < tempstr->Count ; i++) {
			 Receiver = Receiver + IntToStr(int(tempstr->Objects[i]))  +",";
		}

		Receiver = LeftStr(Receiver,Receiver.Length()-1);
		SendMsgReceiver->Parameters->ParamByName("@string")->Value = Receiver;
		SendMsgReceiver->Parameters->ParamByName("@Model")->Value = 0;
		SendMsgReceiver->Parameters->ParamByName("@TaskID")->Value = TaskStr;
		SendMsgReceiver->ExecProc();
		Screen->Cursor = crDefault ;
	 }
	 catch(...)
	 {}
}
  }


void Tfrmnewtask::RefreshData()
{


}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewtask::SpeedButton3Click(TObject *Sender)
{
	Close();
    ModalResult = mbCancel ;
}
//---------------------------------------------------------------------------

