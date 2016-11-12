//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "diaoboset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzCmboBx"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmdiaoboset *frmdiaoboset;
//---------------------------------------------------------------------------
__fastcall Tfrmdiaoboset::Tfrmdiaoboset(TComponent* Owner,TADOConnection* con)
	: TForm(Owner)
{
   aquery->Connection = con;
   qryretairange->Connection = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdiaoboset::FormShow(TObject *Sender)
{
	Readydata();
}
//---------------------------------------------------------------------------
void Tfrmdiaoboset::Readydata()
{
  String sql= "select * from sys_bsset";
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  while (!aquery->Eof)
  {
	if (aquery->FieldByName("name")->AsAnsiString == "diaoboadddiscount")
	{
		edadddiscount->Text  = aquery->FieldByName("bk")->AsString ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "diaodefaultdiscount")
	{
		eddefaultdiscount->Text = aquery->FieldByName("bk")->AsString ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "diaodiscounttype" ) {
		RadioGroup1->ItemIndex = aquery->FieldByName("bk")->AsInteger ;
	}
	//重复录入提示
	if (aquery->FieldByName("name")->AsAnsiString == "peisongsametishi" ) {
		chpeisongsametishi->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	aquery->Next();
  }
}
//---------------------------------------------------------------------------


void __fastcall Tfrmdiaoboset::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmdiaoboset::edadddiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdiaoboset::RzButton1Click(TObject *Sender)
{
	AnsiString sql,bk;
   float adddiscount,defaultdiscount;
   //默认调拨折扣
   try {
		defaultdiscount = StrToFloat(eddefaultdiscount->Text);
   } catch (...) {
		MessageBox(0,"请输入正确的默认调拨折扣！","警告",MB_ICONWARNING);
		return;
   }
   if (defaultdiscount > 100) {
		MessageBox(0,"默认调拨折扣不能大于100！","警告",MB_ICONWARNING);
		return;
   }
   if (defaultdiscount < 0) {
		MessageBox(0,"默认调拨折扣不能小于0！","警告",MB_ICONWARNING);
		return;
   }
   //加扣折扣
   try {
		adddiscount = StrToFloat(edadddiscount->Text);
   } catch (...) {
		MessageBox(0,"请输入正确的加扣折扣！","警告",MB_ICONWARNING);
		return;
   }
   if (adddiscount > 100) {
		MessageBox(0,"加扣折扣不能大于100！","警告",MB_ICONWARNING);
		return;
   }
   if (adddiscount < 0) {
		MessageBox(0,"加扣折扣不能小于0！","警告",MB_ICONWARNING);
		return;
   }
   //默认调拨折扣
   sql = "update sys_bsset set bk = '" + eddefaultdiscount->Text + "' where name = 'diaodefaultdiscount'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //加扣折扣
   sql = "update sys_bsset set bk = '" + edadddiscount->Text + "' where name = 'diaoboadddiscount'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //调拨折扣方式
   sql = "update sys_bsset set bk = '" + IntToStr(RadioGroup1->ItemIndex) + "' where name = 'diaodiscounttype'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //重复录入提示
   if (chpeisongsametishi->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'peisongsametishi'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'peisongsametishi'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   MessageBox(0,"业务设置成功！     ","提示",MB_ICONINFORMATION);
   Close();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmdiaoboset::RzButton2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

