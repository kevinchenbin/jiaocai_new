//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SpecialPasswordForm.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmSpecialPassword *frmSpecialPassword;
//---------------------------------------------------------------------------
__fastcall TfrmSpecialPassword::TfrmSpecialPassword(TComponent* Owner)
	: TfrmMDIChild(Owner)
{

}

void TfrmSpecialPassword::Init(LandInfo* li)
{
	 TfrmMDIChild::Init(li);
	 cmd->Connection=li->con;
	 stgid = li->storageID ;
	 userid = li->userID ;
	 con = li->con;
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
		if (edmember->Text != "") {
			sql = sql + ",Member = '" + edmember->Text + "' ";
	  }
	  if (edsupshenpwd->Text != "") {
		sql = sql + ",supshenheipwd = '" + edsupshenpwd->Text + "' ";
	  }
	  if (edsupfanshenpwd->Text != "") {
		sql = sql + ",supfanshenpwd = '" + edsupfanshenpwd->Text + "' ";
	  }
	  if (edclishenpwd->Text != "") {
		sql = sql + ",clishenheipwd = '" + edclishenpwd->Text + "' ";
	  }
	  if (edclifanshenpwd->Text != "") {
		sql = sql + ",clifanshenpwd = '" + edclifanshenpwd->Text + "' ";
	  }
	  sql = sql + " where id = " + IntToStr(stgid);

	 cmd->CommandText=sql;
	 cmd->Execute();
	 AddEvent(1,"特殊口令窗口",userid,stgid,"特殊口令设置",con);
	 ShowMessage("修改成功！");
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

void __fastcall TfrmSpecialPassword::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSpecialPassword::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

