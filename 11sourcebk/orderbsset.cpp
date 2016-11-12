//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "orderbsset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmorderbsset *frmorderbsset;
//---------------------------------------------------------------------------
__fastcall Tfrmorderbsset::Tfrmorderbsset(TComponent* Owner,TADOConnection* con)
	: TForm(Owner)
{
   aquery->Connection = con;
   qryretairange->Connection = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderbsset::sbokClick(TObject *Sender)
{
   AnsiString sql;
   //自动锁定库存量
   if (cbautolocalstockbyOrder->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'autolocalstockbyOrder'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'autolocalstockbyOrder'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //预计天数
   if (edday->Text == "" ) {
		edday->Text = "0";
   }
   sql = "update sys_bsset set bk = " + edday->Text + " where name = 'orderyujiday'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //跟踪上次折扣
   if (chlastorderdiscount->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lastorderdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lastorderdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //重复记录提示
   if (edmonth->Text == "") {
	   edmonth->Text = "0";
   }
   if (chchongfuordertishi->Checked ) {
	   sql = "update sys_bsset set value = 1,bk = '" + edmonth->Text + "' where name = 'chongfuordertishi'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,bk = '" + edmonth->Text + "' where name = 'chongfuordertishi'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //订单查单密码启用
   if (chorderfind->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'orderfind'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'orderfind'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //订单修改单头密码启用
   if (chorderchange->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'orderchange'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'orderchange'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //打印抬头
   /*sql = "update sys_bsset set bk = '" + edorprinttitle->Text.Trim() + "' where name = 'orprinttitle'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //联系人
   sql = "update sys_bsset set bk = '" + edorcontact->Text.Trim() + "' where name = 'orcontact'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //电话
   sql = "update sys_bsset set bk = '" + edortel->Text.Trim() + "' where name = 'ortel'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //地址
   sql = "update sys_bsset set bk = '" + edoraddress->Text.Trim() + "' where name = 'oraddress'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库打印备注
   sql = "update sys_bsset set bk = '" + edorprintbk->Text + "' where name = 'orprintbk'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL(); */
   MessageBox(0,"业务设置成功！","",MB_OK);
   Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderbsset::FormShow(TObject *Sender)
{
	Readydata();

}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderbsset::sbcancelClick(TObject *Sender)
{
   Close();
}
void Tfrmorderbsset::Readydata()
{
  String sql= "select * from sys_bsset";
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  while (!aquery->Eof)
  {
	if (aquery->FieldByName("name")->AsAnsiString == "autolocalstockbyOrder") {
		cbautolocalstockbyOrder->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "orderyujiday")
	{
		edday->Text = aquery->FieldByName("bk")->AsString ;
	}
	//跟踪上次折扣
	if (aquery->FieldByName("name")->AsAnsiString == "lastorderdiscount") {
		chlastorderdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//重复记录提示
	if (aquery->FieldByName("name")->AsAnsiString == "chongfuordertishi") {
		chchongfuordertishi->Checked = aquery->FieldByName("value")->AsBoolean ;
		edmonth->Text = aquery->FieldByName("bk")->AsString ;
	}
	//订单密码启用
	if (aquery->FieldByName("name")->AsAnsiString == "orderfind") {
		chorderfind->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//订单修改单头密码启用
	if (aquery->FieldByName("name")->AsAnsiString == "orderchange") {
		chorderchange->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//地址
	/*if (aquery->FieldByName("name")->AsAnsiString == "oraddress")
	{
		edoraddress->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//抬头
	if (aquery->FieldByName("name")->AsAnsiString == "orprinttitle")
	{
		edorprinttitle->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//联系人
	if (aquery->FieldByName("name")->AsAnsiString == "orcontact")
	{
		edorcontact->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//电话
	if (aquery->FieldByName("name")->AsAnsiString == "ortel")
	{
		edortel->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//打印备注
	if (aquery->FieldByName("name")->AsAnsiString == "orprintbk" ) {
		edorprintbk->Text = aquery->FieldByName("bk")->AsString ;
	}   */
	aquery->Next();
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderbsset::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

