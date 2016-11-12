//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "procureset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
Tfrmprocureset *frmprocureset;
//---------------------------------------------------------------------------
__fastcall Tfrmprocureset::Tfrmprocureset(TComponent* Owner,TADOConnection* con)
	: TForm(Owner)
{
   aquery->Connection = con;
   qryretairange->Connection = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprocureset::sbokClick(TObject *Sender)
{
   AnsiString sql,bk;
   //采购单查单密码启用
   if (chprocurefindpwd->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'procurefindpwd'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'procurefindpwd'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //采购单删行密码启用
   if (chprocuredeletepwd->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'procuredeletepwd'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'procuredeletepwd'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //智能采购单查单密码启用
   if (chznprocurefindpwd->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'znprocurefindpwd'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'znprocurefindpwd'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //智能采购单删行密码启用
   if (chznprocuredeletepwd->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'znprocuredeletepwd'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'znprocuredeletepwd'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //预计天数
   if (edday->Text == "" ) {
		edday->Text = "0";
   }
   sql = "update sys_bsset set bk = " + edday->Text + " where name = 'caigouyujiday'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   /*//打印抬头
   sql = "update sys_bsset set bk = '" + edcgprinttitle->Text.Trim() + "' where name = 'cgprinttitle'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //联系人
   sql = "update sys_bsset set bk = '" + edcgcontact->Text.Trim() + "' where name = 'cgcontact'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //电话
   sql = "update sys_bsset set bk = '" + edcgtel->Text.Trim() + "' where name = 'cgtel'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //地址
   sql = "update sys_bsset set bk = '" + edcgaddress->Text.Trim() + "' where name = 'cgaddress'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库打印备注
   sql = "update sys_bsset set bk = '" + edcgprintbk->Text + "' where name = 'cgprintbk'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();   */
   MessageBox(0,"业务设置成功！     ","提示",MB_ICONINFORMATION);
   Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprocureset::FormShow(TObject *Sender)
{
	Readydata();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmprocureset::sbcancelClick(TObject *Sender)
{
   Close();
}
void Tfrmprocureset::Readydata()
{
  String sql= "select * from sys_bsset";
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  while (!aquery->Eof)
  {
	if (aquery->FieldByName("name")->AsAnsiString == "procurefindpwd")
	{
		chprocurefindpwd->Checked = aquery->FieldByName("Value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "procuredeletepwd")
	{
		chprocuredeletepwd->Checked = aquery->FieldByName("Value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "znprocurefindpwd")
	{
		chznprocurefindpwd->Checked = aquery->FieldByName("Value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "znprocuredeletepwd")
	{
		chznprocuredeletepwd->Checked = aquery->FieldByName("Value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "caigouyujiday")
	{
		edday->Text = aquery->FieldByName("bk")->AsString ;
	}
	/*//地址
	if (aquery->FieldByName("name")->AsAnsiString == "cgaddress")
	{
		edcgaddress->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//抬头
	if (aquery->FieldByName("name")->AsAnsiString == "cgprinttitle")
	{
		edcgprinttitle->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//联系人
	if (aquery->FieldByName("name")->AsAnsiString == "cgcontact")
	{
		edcgcontact->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//电话
	if (aquery->FieldByName("name")->AsAnsiString == "cgtel")
	{
		edcgtel->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//打印备注
	if (aquery->FieldByName("name")->AsAnsiString == "cgprintbk" ) {
		edcgprintbk->Text = aquery->FieldByName("bk")->AsString ;
	}  */
	aquery->Next();
  }
}
//---------------------------------------------------------------------------


void __fastcall Tfrmprocureset::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------



