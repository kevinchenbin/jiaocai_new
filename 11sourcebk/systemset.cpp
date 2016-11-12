//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "systemset.h"
#include "Syspwdchange.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmsystemset *frmsystemset;
//---------------------------------------------------------------------------
__fastcall Tfrmsystemset::Tfrmsystemset(TComponent* Owner,TADOConnection* con)
	: TForm(Owner)
{
   aquery->Connection = con;
   qryretairange->Connection = con;
   fcon = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsystemset::sbokClick(TObject *Sender)
{

   //顺延单号模式
   AnsiString sql;
   if (cbchangeDanHaoDisplay->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'changeDanHaoDisplay'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'changeDanHaoDisplay'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   if (cbchangeDanHaoDisplay->Checked) {
	logmessage = "启用顺延单号模式";
   }
   else
   {
	logmessage = "取消顺延单号模式";
   }
   AddEvent(1,"单号显示规则窗口",userid,storageid,logmessage,fcon);
   MessageBox(0,"业务设置成功！","",MB_OK);
   Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsystemset::FormShow(TObject *Sender)
{
	Readydata();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsystemset::sbcancelClick(TObject *Sender)
{
   Close();
}

//---------------------------------------------------------------------------
void Tfrmsystemset::Readydata()
{
  String sql= "select * from sys_bsset where name = 'changeDanHaoDisplay'";
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  while (!aquery->Eof)
  {
	if (aquery->FieldByName("name")->AsAnsiString == "changeDanHaoDisplay" ) {
		cbchangeDanHaoDisplay->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	aquery->Next();
  }
}
//---------------------------------------------------------------------------


void __fastcall Tfrmsystemset::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsystemset::Button1Click(TObject *Sender)
{
	Tfrmsyspwdchange *frm = new Tfrmsyspwdchange(Application,fcon);
	frm->userid = userid;
	frm->storageid = storageid;
	frm->Show();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsystemset::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsystemset::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

