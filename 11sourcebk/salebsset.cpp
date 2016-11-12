//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "salebsset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
Tfrmsalebsset *frmsalebsset;
//---------------------------------------------------------------------------
__fastcall Tfrmsalebsset::Tfrmsalebsset(TComponent* Owner,TADOConnection* con)
	: TForm(Owner)
{
   aquery->Connection = con;
   qryretairange->Connection = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsalebsset::sbokClick(TObject *Sender)
{
   AnsiString sql,bk;
   int bit,defaultdiscount;
   //优先级别判断
   if ((cb1->ItemIndex == cb2->ItemIndex ) || (cb1->ItemIndex == cb3->ItemIndex) ||
	   (cb1->ItemIndex == cb4->ItemIndex ) || (cb2->ItemIndex == cb3->ItemIndex) ||
	   (cb2->ItemIndex == cb4->ItemIndex ) || (cb3->ItemIndex == cb4->ItemIndex )) {
		MessageBox(0,"同一打折方式不能同时为两个级别！","警告",MB_ICONWARNING);
		return;
   }
   //小数点位数
   if (etdot->Text == "") {
		bit = 0;
   }
   else
   {
		bit = StrToInt(etdot->Text.Trim() );
   }
   if (bit > 4) {
	   MessageBox(0,"小数位数最高只能设置4位！","警告",MB_ICONWARNING);
	   return;
   }
   //默认批销折扣
   try {
		defaultdiscount = StrToFloat(eddefaultdiscount->Text);
   } catch (...) {
		MessageBox(0,"请输入正确的折扣！","警告",MB_ICONWARNING);
		return;
   }
   if (defaultdiscount > 100) {
		MessageBox(0,"折扣不能大于100！","警告",MB_ICONWARNING);
		return;
   }
   if (defaultdiscount < 0) {
		MessageBox(0,"折扣不能小于0！","警告",MB_ICONWARNING);
		return;
   }
   bk = "0";
   if (bit > 0) {
		bk = bk + ".";
		for (int i = 0; i < bit; i++) {
			bk = bk + "0";
		}
   }
   sql = "update sys_bsset set bk = '" + bk + "' where name = 'salexiaoshudian'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //图书库存为0时是否列出
   if (cbstorezero->Checked) {
		sql = "update sys_bsset set value = 1 where name ='storagezero'";
   } else
   {
		sql = "update sys_bsset set value = 0 where name ='storagezero'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //是否允许负库存输入
   if (cbbear->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'bear'";
   }
   else
   {
       sql = "update sys_bsset set value = 0 where name = 'bear'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销历史明细
   if (cbwosalehistory->Checked ) {
		sql = "update sys_bsset set value = 1,bk = '" + edwosaleday->Text + "' where name = 'wosaleday'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,bk = '" + edwosaleday->Text + "' where name = 'wosaleday'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //当前客户结/欠款情况显示
   if (cbcheckedview->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'checkedview'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'checkedview'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //是否允许无销售退货
   if (cbwosalereturn->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'wosalereturn'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'wosalereturn'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销跟踪上次折扣
   if (cbpxdiscount->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //低于成本折扣提醒
   if (cblowcostalter->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lowcostalter'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lowcostalter'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //低于成本折扣是否发货
   if (cblowcostenable->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lowcostenable'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lowcostenable'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //低于正常折扣提醒
   if (cblownormalalter->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lownormalalter'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lownormalalter'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //低于正常折扣是否发货
   if (cblownormalenable->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lownormalenable'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lownormalenable'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //允许修改折扣的设置
   if (cbwsaledisscountchange->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'WsalelDiscountChange'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'WsalelDiscountChange'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销退货监管
   if (cbpxtuihuocatch->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxtuihuocatch'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxtuihuocatch'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //现场收款是否可用
   if (chxianchangrecive->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'xianchangrecive'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'xianchangrecive'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销明细显示所以客户历史记录
   if (cbpxallclientdetail->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxallclientdetail'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxallclientdetail'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销删行密码是否启用
   if (cbpxdeleteusepassword->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxdeleteusepassword'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxdeleteusepassword'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销查单密码是否启用
   if (cbpxfindusepassword->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxfindusepassword'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxfindusepassword'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销退货密码是否启用
   if (cbpxtuihuousepassword->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxtuihuousepassword'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxtuihuousepassword'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //无库存销售
   if (cbpxnobkinfosale->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxnobkinfosale'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxnobkinfosale'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //无库存批销退货
   if (cbpxnobkinfotuihuo->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxnobkinfotuihuo'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxnobkinfotuihuo'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销默认折扣
   if (cbpxdefaultdiscount->Checked ) {
		sql = "update sys_bsset set value = 1,bk = '" + eddefaultdiscount->Text + "' where name = 'pxdefaultdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,bk = '" + eddefaultdiscount->Text + "' where name = 'pxdefaultdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //无库存批销退货
   if (chnokucunpxth->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'nokucunpxth'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'nokucunpxth'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //退货率计算时间
   if (edmonth->Text == "" ) {
		edmonth->Text == "0" ;
   }
   sql = "update sys_bsset set bk = " + edmonth->Text + "where name = 'pxbenqituihuolv'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销修改单头密码是否启用
   if (chpxusechange->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxusechange'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxusechange'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //重复录入提示
   if (chwsalesametishi->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'wsalesametishi'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'wsalesametishi'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //客户加点折扣优先
   if (chclientaddyx->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'clientaddyx'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'clientaddyx'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //批销退货期限
   if (edpxtuihuoqixian->Text == "") {
	   edpxtuihuoqixian->Text = "0";
   }
   sql = "update sys_bsset set bk = '" + edpxtuihuoqixian->Text + "' where name = 'pxtuihuoqixian'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //发货打印抬头
   /*sql = "update sys_bsset set bk = '" + edwsprinttitle->Text.Trim() + "' where name = 'wsprinttitle'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //联系人
   sql = "update sys_bsset set bk = '" + edwscontact->Text.Trim() + "' where name = 'wscontact'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //电话
   sql = "update sys_bsset set bk = '" + edwstel->Text.Trim() + "' where name = 'wstel'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //地址
   sql = "update sys_bsset set bk = '" + edwsaddress->Text.Trim() + "' where name = 'wsaddress'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();   */
   //打折方式
   if (RadioGroup1->ItemIndex == 0 ) {
		sql = "update sys_bsset set value = 1 where name = 'pxpriordiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
		sql = "update sys_bsset set value = 0 where name = 'pxmindiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxpriordiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
		sql = "update sys_bsset set value = 1 where name = 'pxmindiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   //优先级别
   //一级
   if (cb1->Text == "营销管理批销打折设置") {
		sql = "update sys_bsset set bk = '1' where name = 'pxsinglebook'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb1->Text == "入库预计批销折扣") {
   		sql = "update sys_bsset set bk = '1' where name = 'pxrkyjdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb1->Text == "跟踪上次折扣") {
		sql = "update sys_bsset set bk = '1' where name = 'pxlastdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb1->Text == "批销默认折扣") {
		sql = "update sys_bsset set bk = '1' where name = 'pxmorendiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   //二级
   if (cb2->Text == "营销管理批销打折设置") {
		sql = "update sys_bsset set bk = '2' where name = 'pxsinglebook'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb2->Text == "入库预计批销折扣") {
		sql = "update sys_bsset set bk = '2' where name = 'pxrkyjdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb2->Text == "跟踪上次折扣") {
		sql = "update sys_bsset set bk = '2' where name = 'pxlastdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb2->Text == "批销默认折扣") {
		sql = "update sys_bsset set bk = '2' where name = 'pxmorendiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   //三级
   if (cb3->Text == "营销管理批销打折设置") {
		sql = "update sys_bsset set bk = '3' where name = 'pxsinglebook'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb3->Text == "入库预计批销折扣") {
		sql = "update sys_bsset set bk = '3' where name = 'pxrkyjdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb3->Text == "跟踪上次折扣") {
		sql = "update sys_bsset set bk = '3' where name = 'pxlastdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb3->Text == "批销默认折扣") {
		sql = "update sys_bsset set bk = '3' where name = 'pxmorendiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   //四级
   if (cb4->Text == "营销管理批销打折设置") {
		sql = "update sys_bsset set bk = '4' where name = 'pxsinglebook'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb4->Text == "入库预计批销折扣") {
		sql = "update sys_bsset set bk = '4' where name = 'pxrkyjdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb4->Text == "跟踪上次折扣") {
		sql = "update sys_bsset set bk = '4' where name = 'pxlastdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb4->Text == "批销默认折扣") {
		sql = "update sys_bsset set bk = '4' where name = 'pxmorendiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   MessageBox(0,"业务设置成功！       ","提示",MB_ICONASTERISK);
   Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsalebsset::FormShow(TObject *Sender)
{
	Readydata();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsalebsset::sbcancelClick(TObject *Sender)
{
   Close();
}
void Tfrmsalebsset::Readydata()
{
  String sql= "select * from sys_bsset",bk;
  int bit;
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  while (!aquery->Eof)
  {
	if (aquery->FieldByName("name")->AsAnsiString == "storagezero")
	{
		cbstorezero->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "bear")
	{
		cbbear->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "wosaleday" ) {
		cbwosalehistory->Checked = aquery->FieldByName("value")->AsBoolean ;
		edwosaleday->Text = aquery->FieldByName("bk")->AsString ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "checkedview" ) {
		cbcheckedview->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "wosalereturn" ) {
		cbwosalereturn->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lowcostalter" ) {
		cblowcostalter->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lowcostenable" ) {
		cblowcostenable->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lownormalalter" ) {
		cblownormalalter->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lownormalenable" ) {
    	cblownormalenable->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxdiscount" ) {
		cbpxdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "WsalelDiscountChange" ) {
		cbwsaledisscountchange->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxtuihuocatch" ) {
		cbpxtuihuocatch->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "salexiaoshudian" ) {
		bk = aquery->FieldByName("bk")->AsString;
		if (bk.Pos(".") == 0 ) {
			bit = 0;
		}
		else
		{
			bit = bk.Length() - bk.Pos(".");
		}
        etdot->Text = IntToStr(bit);
	}
	if (aquery->FieldByName("name")->AsAnsiString == "xianchangrecive" ) {
		chxianchangrecive->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxallclientdetail" ) {
		cbpxallclientdetail->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxdeleteusepassword" ) {
		cbpxdeleteusepassword->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxfindusepassword" ) {
		cbpxfindusepassword->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxtuihuousepassword" ) {
		cbpxtuihuousepassword->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxnobkinfosale" ) {
		cbpxnobkinfosale->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxnobkinfotuihuo" ) {
		cbpxnobkinfotuihuo->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxusechange" ) {
		chpxusechange->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//批销打印备注
	/*if (aquery->FieldByName("name")->AsAnsiString == "pxprintbk" ) {
		cbpxprintbk->Checked = aquery->FieldByName("value")->AsBoolean ;
		edpxprintbk->Text = aquery->FieldByName("bk")->AsString ;
	}   */
	//批销默认折扣
	if (aquery->FieldByName("name")->AsAnsiString == "pxdefaultdiscount" ) {
		cbpxdefaultdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
		eddefaultdiscount->Text = aquery->FieldByName("bk")->AsString ;
	}
	//批销打折方式
	if (aquery->FieldByName("name")->AsAnsiString == "pxpriordiscount" ) {
		if (aquery->FieldByName("value")->AsBoolean) {
			RadioGroup1->ItemIndex = 0;
		}
		else
		{
        	RadioGroup1->ItemIndex = 1;
		}
	}
	//无库存批销退货
	if (aquery->FieldByName("name")->AsAnsiString == "nokucunpxth" ) {
		chnokucunpxth->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//重复录入提示
	if (aquery->FieldByName("name")->AsAnsiString == "wsalesametishi" ) {
		chwsalesametishi->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//退货率计算时间
	if (aquery->FieldByName("name")->AsAnsiString == "pxbenqituihuolv")
	{
		edmonth->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//客户加点折扣优先
	if (aquery->FieldByName("name")->AsAnsiString == "clientaddyx" ) {
		chclientaddyx->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//批销退货期限
	if (aquery->FieldByName("name")->AsAnsiString == "pxtuihuoqixian")
	{
		edpxtuihuoqixian->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//地址
	/*if (aquery->FieldByName("name")->AsAnsiString == "wsaddress")
	{
		edwsaddress->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//抬头
	if (aquery->FieldByName("name")->AsAnsiString == "wsprinttitle")
	{
		edwsprinttitle->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//联系人
	if (aquery->FieldByName("name")->AsAnsiString == "wscontact")
	{
		edwscontact->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//电话
	if (aquery->FieldByName("name")->AsAnsiString == "wstel")
	{
		edwstel->Text = aquery->FieldByName("bk")->AsAnsiString ;
	} */
	//优先级别
	if (aquery->FieldByName("name")->AsAnsiString == "pxsinglebook" ) {
		int prior = aquery->FieldByName("bk")->AsInteger  ;
		switch (prior) {
			case 1:
				cb1->ItemIndex = 0;
			break;
			case 2:
				cb2->ItemIndex = 0;
			break;
			case 3:
				cb3->ItemIndex = 0;
			break;
			case 4:
				cb4->ItemIndex = 0;
			break;
		default:
			;
		}
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxrkyjdiscount" ) {
		int prior = aquery->FieldByName("bk")->AsInteger ;
		switch (prior) {
			case 1:
				cb1->ItemIndex = 1;
			break;
			case 2:
				cb2->ItemIndex = 1;
			break;
			case 3:
				cb3->ItemIndex = 1;
			break;
			case 4:
				cb4->ItemIndex = 1;
			break;
		default:
			;
		}
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxlastdiscount" ) {
		int prior = aquery->FieldByName("bk")->AsInteger ;
		switch (prior) {
			case 1:
				cb1->ItemIndex = 2;
			break;
			case 2:
				cb2->ItemIndex = 2;
			break;
			case 3:
				cb3->ItemIndex = 2;
			break;
			case 4:
				cb4->ItemIndex = 2;
			break;
		default:
			;
		}
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxmorendiscount" ) {
		int prior = aquery->FieldByName("bk")->AsInteger ;
		switch (prior) {
			case 1:
				cb1->ItemIndex = 3;
			break;
			case 2:
				cb2->ItemIndex = 3;
			break;
			case 3:
				cb3->ItemIndex = 3;
			break;
			case 4:
				cb4->ItemIndex = 3;
			break;
		default:
			;
		}
	}
	aquery->Next();
  }
}
//---------------------------------------------------------------------------


void __fastcall Tfrmsalebsset::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmsalebsset::eddefaultdiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------

