//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SpecialPasswordForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmSpecialPassword *frmSpecialPassword;
//---------------------------------------------------------------------------
__fastcall TfrmSpecialPassword::TfrmSpecialPassword(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	m_module = MTUser;
}

void TfrmSpecialPassword::Init(LandInfo* li)
{
	 TfrmMDIChild::Init(li);
	 if (!CheckOperateAuthority())
	 {
         Close();
	 }
	 cmd->Connection=li->con;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpecialPassword::FormClose(TObject *Sender, TCloseAction &Action)

{
	    Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpecialPassword::btn2Click(TObject *Sender)
{
	      Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpecialPassword::btn1Click(TObject *Sender)
{
	 String sql ;
	 sql= "update SYS_StorageInfo set Name=Name" ;
	  if (edt1->Text!="") {
		   sql= sql+",Retail='"+edt1->Text+"' ";
	  }
		if (edt2->Text!="") {
		   sql= sql+",Wholesale='"+edt2->Text+"' ";
	  }
		if (edt3->Text!="") {
		   sql= sql+",Orders='"+edt3->Text+"' ";
	  }
		if (edt4->Text!="") {
		   sql= sql+",Accounts='"+edt4->Text+"' ";
	  }
		if (edt5->Text!="") {
		   sql= sql+",Storage='"+edt5->Text+"' ";
	  }
		if (edt6->Text!="") {
		   sql= sql+",Specialpassword='"+edt6->Text+"' ";
	  }
		if (edt7->Text!="") {
		   sql= sql+",Procurement='"+edt7->Text+"' ";
	  }

	 cmd->CommandText=sql;
	 cmd->Execute();
	 ShowMessage("ÐÞ¸Ä³É¹¦£¡");
	 Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpecialPassword::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{

				if (Key==0x1B) {   //esc
			this->btn2->Click();

		}
		if (Shift.Contains(ssCtrl)&&Key==83) {     //s

		   this->btn1->Click();
	}
}
//---------------------------------------------------------------------------

