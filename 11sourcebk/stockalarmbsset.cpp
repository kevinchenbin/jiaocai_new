//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "stockalarmbsset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmstockalarmbsset *frmstockalarmbsset;
//---------------------------------------------------------------------------
__fastcall Tfrmstockalarmbsset::Tfrmstockalarmbsset(TComponent* Owner,TADOConnection* con)
	: TForm(Owner)
{
   aquery->Connection = con;
   qryretairange->Connection = con;
   StrToInt("11");
}
//---------------------------------------------------------------------------
void __fastcall Tfrmstockalarmbsset::sbokClick(TObject *Sender)
{
	AnsiString sql,setdate;
	if (edtime->Text.Trim().Pos(":") > 0   ) {
		setdate = "2010-12-30 " + edtime->Text.Trim() + ":000";
	}
	else
	{
		setdate = "2010-12-30 " + edtime->Text.Trim() + ":00:000";
	}
	try {
		setdate = DateTimeToStr(Now());
		StrToDateTime(setdate);
	} catch (...) {
		MessageBox(0,"请设置正确的时间！","",MB_OK);
		return;
	}

   //每次登陆时提示
   if (chloginstockalarm->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'loginstockalarm'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'loginstockalarm'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //按时间点提示
   if (edtime->Text == "") {
	   edtime->Text = "0";
   }
   if (chtimestockalarm->Checked ) {
	   sql = "update sys_bsset set value = 1,bk = '" + edtime->Text + "' where name = 'timestockalarm'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,bk = '" + edtime->Text + "' where name = 'timestockalarm'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //库存管理时提示
   if (chkucunstockalarm->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'kucunstockalarm'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'kucunstockalarm'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   MessageBox(0,"业务设置成功！","",MB_OK);
   Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmstockalarmbsset::FormShow(TObject *Sender)
{
	Readydata();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockalarmbsset::sbcancelClick(TObject *Sender)
{
   Close();
}
void Tfrmstockalarmbsset::Readydata()
{
	String sql= "select * from sys_bsset";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while (!aquery->Eof)
	{
		//按时间点提示
		if (aquery->FieldByName("name")->AsAnsiString == "timestockalarm") {
			chtimestockalarm->Checked = aquery->FieldByName("value")->AsBoolean ;
			edtime->Text = aquery->FieldByName("bk")->AsString ;
		}
		//登陆时提示
		if (aquery->FieldByName("name")->AsAnsiString == "loginstockalarm") {
			chloginstockalarm->Checked = aquery->FieldByName("value")->AsBoolean ;
		}
		//库存管理时提示
		if (aquery->FieldByName("name")->AsAnsiString == "kucunstockalarm") {
			chkucunstockalarm->Checked = aquery->FieldByName("value")->AsBoolean ;
		}
		aquery->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockalarmbsset::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstockalarmbsset::edtimeKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && Key != '\r' && Key != ':' && Key != '\b') {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------

