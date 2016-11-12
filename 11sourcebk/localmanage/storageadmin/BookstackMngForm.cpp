//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BookstackMngForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzLine"
#pragma link "RzPanel"
#pragma link "MDIChild"
#pragma resource "*.dfm"
TfrmBookstackMng *frmBookstackMng;
//---------------------------------------------------------------------------
__fastcall TfrmBookstackMng::TfrmBookstackMng(TComponent* Owner)
	: TfrmMDIChild(Owner)
{     m_module = MTStore;
}
//---------------------------------------------------------------------------
void TfrmBookstackMng::Init(TApplication* app, TADOConnection* con)
{        TfrmMDIChild::Init(app, con);
	   this->Caption="��λ����";

	if (dsetBookStackMng->Active)
	{
		dsetBookStackMng->Active = false;
	}
		String   sql;
		dsetBookStackMng->Connection = con;
	   sql = "select Name as Name1,StgID  from STK_BookstackInfo";
		dsetBookStackMng->CommandText = sql;
		dsetBookStackMng->Active = true;

			if (dsStore->Active)
	{
		dsStore->Active = false;
	}
		String   sql1;
		dsStore->Connection = con;
	   sql1 = "select top 1 id,name from SYS_StorageInfo";
		dsStore->CommandText = sql1;
		dsStore->Active = true;

}



void __fastcall TfrmBookstackMng::RzToolButton2Click(TObject *Sender)
{         this->Sender1=Sender;
	   edtStgName->SetFocus();
	   edtStgName->ReadOnly=false;
	   edtNum->ReadOnly=false;
	 dsetBookStackMng->Append();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookstackMng::edtStgNameKeyPress(TObject *Sender, wchar_t &Key)

{
		if (Key==VK_RETURN)
	{
		 edtNum->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookstackMng::edtNumKeyPress(TObject *Sender, wchar_t &Key)
{
         if (Key==VK_RETURN) //
	{

			  this->RzToolButton5Click(Sender1) ;

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookstackMng::RzToolButton1Click(TObject *Sender)
{
			edtStgName->ReadOnly=false;
			edtNum->ReadOnly=false;
			edtStgName->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookstackMng::RzToolButton4Click(TObject *Sender)
{       if(MessageDlg("��ȷ��ɾ����", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
		  {
		   	 try{
						if(!dsetBookStackMng->IsEmpty())
						{
						dsetBookStackMng->Delete();
						dsetBookStackMng->UpdateBatch();
						ShowMessage("�����ɹ�����Ϣ��ɾ����");
						}
				}
			    catch(Exception &E)
				 {
						ShowMessage("�����ݸ�ϵͳ�����ط��й���������ɾ����");
				 }
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookstackMng::RzToolButton3Click(TObject *Sender)
{
	      Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookstackMng::FormClose(TObject *Sender, TCloseAction &Action)

{        dsStore->Active=false;
	   dsetBookStackMng->Active = false;
		Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookstackMng::RzToolButton5Click(TObject *Sender)
{          if(MessageDlg("��ȷ�ϱ�����", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
			  {
				   dsetBookStackMng->UpdateBatch();
				   ShowMessage("�����ɹ�����Ϣ�ѱ��棡");
					edtStgName->ReadOnly=true;
					edtNum->ReadOnly=true;
			   }

}
//---------------------------------------------------------------------------

void __fastcall TfrmBookstackMng::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	  		if (Key==0x1B) {   //esc
			this->RzToolButton3->Click();

		}

			if (Shift.Contains(ssCtrl)&&Key==65) {   //A
			this->RzToolButton2->Click();

		}
				if (Shift.Contains(ssCtrl)&&Key==68) {   //D
			this->RzToolButton4->Click();

		}
				if (Key==0x70) {   //F1
			this->RzToolButton1->Click();

		}
		if (Shift.Contains(ssCtrl)&&Key==83) {  //S
			  this->RzToolButton5->Click();

		}
}
//---------------------------------------------------------------------------

