//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "storagebsset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmstoragebsset *frmstoragebsset;
//---------------------------------------------------------------------------
__fastcall Tfrmstoragebsset::Tfrmstoragebsset(TComponent* Owner,TADOConnection* con)
	: TForm(Owner)
{
   aquery->Connection = con;
   qryretairange->Connection = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmstoragebsset::sbokClick(TObject *Sender)
{
   AnsiString sql,bk;
   int bit;
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
   bk = "0";
   if (bit > 0) {
		bk = bk + ".";
		for (int i = 0; i < bit; i++) {
			bk = bk + "0";
		}
   }
   sql = "update sys_bsset set bk = '" + bk + "' where name = 'xiaoshudian'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();

   //是否允许重复录入
   if (cbsameid->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'sameid'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'sameid'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //是否自动注销采购记录
   if (cbauto->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'autologout'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'autologout'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //有订货记录提示
   if (cborder->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'ordernote'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'ordernote'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //跟踪上次入库折扣
   if (cbtrace->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'tracediscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'tracediscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库进/退货明细
   if (cbstoragehistory->Checked ) {
		sql = "update sys_bsset set value = 1,bk = '" + edstorageday->Text + "' where name = 'storageday'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,bk = '" + edstorageday->Text + "' where name = 'storageday'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //预计批销折扣是否启用附加点设置
   if (cbadddotenable->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'adddotenable'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'adddotenable'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //跟踪上次预计批销折扣
   if (cblastyjpxdiscount->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'lastyjpxdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lastyjpxdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //预计批销折扣以何种优先
   if (cblastyjpx->Checked ) {
		sql = "update sys_bsset set bk = 'lastyjpxdiscount' where name = 'yjpxfirstkind'";
   }
   else
   {
		sql = "update sys_bsset set bk = 'adddotenable' where name = 'yjpxfirstkind'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库明细显示所有供应商的历史记录
   if (cbrkallsupplier->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'rkallsupplier'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'rkallsupplier'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库查单密码
   if (cbrkusefind->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'rkusefind'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'rkusefind'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库删单密码
   if (cbrkusedelete->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'rkusedelete'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'rkusedelete'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库退货密码
   if (cbrkusetuihuo->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'rkusetuihuo'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'rkusetuihuo'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库打印备注
   /*if (cbrkprintbk->Checked ) {
		sql = "update sys_bsset set value = 1,bk = '" + edrkprintbk->Text + "' where name = 'rkprintbk'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,bk = '" + edrkprintbk->Text + "' where name = 'rkprintbk'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();   */
   //是否启用多货源
   if (chmutisupplier->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'mutisupplier'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'mutisupplier'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //有库存引用可删除库位
   if (chdeletestack->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'deletestack'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'deletestack'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库退货率计算时间
   if (edmonth->Text == "" ) {
		edmonth->Text == "0";
   }
   sql = "update sys_bsset set bk = " + edmonth->Text + " where name = 'rkbenqituihuolv'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库修改单头密码
   if (cbrkusechange->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'rkusechange'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'rkusechange'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //跟踪上次预计零售折扣
   if (cblastyjlsdiscount->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'lastyjlsdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lastyjlsdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //重复录入提示
   if (chstoragesametishi->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'storagesametishi'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'storagesametishi'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   /*//入库打印抬头
   sql = "update sys_bsset set bk = '" + edrkprinttitle->Text.Trim() + "' where name = 'rkprinttitle'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //联系人
   sql = "update sys_bsset set bk = '" + edrkcontact->Text.Trim() + "' where name = 'rkcontact'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //电话
   sql = "update sys_bsset set bk = '" + edrktel->Text.Trim() + "' where name = 'rktel'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //地址
   sql = "update sys_bsset set bk = '" + edrkaddress->Text.Trim() + "' where name = 'rkaddress'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL(); */
   //退货监管
   if (chrktuihuoguanli->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'rktuihuoguanli'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'rktuihuoguanli'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   MessageBox(0,"业务设置成功！   ","提示",MB_ICONASTERISK);
   Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmstoragebsset::FormShow(TObject *Sender)
{
	Readydata();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstoragebsset::sbcancelClick(TObject *Sender)
{
   Close();
}
void Tfrmstoragebsset::Readydata()
{
  String sql= "select * from sys_bsset",bk;
  int bit;
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  while (!aquery->Eof)
  {
	if (aquery->FieldByName("name")->AsAnsiString == "sameid")
	{
		cbsameid->Checked = aquery->FieldByName("value")->AsBoolean ;

	}
	if (aquery->FieldByName("name")->AsAnsiString == "tracediscount")
	{
		cbtrace->Checked = aquery->FieldByName("value")->AsBoolean ;

	}
	if (aquery->FieldByName("name")->AsAnsiString == "autologout")
	{
		cbauto->Checked = aquery->FieldByName("value")->AsBoolean ;

	}
	if (aquery->FieldByName("name")->AsAnsiString == "ordernote")
	{
		cborder->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "adddotenable")
	{
		cbadddotenable->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lastyjpxdiscount")
	{
		cblastyjpxdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;

	}
	if (aquery->FieldByName("name")->AsAnsiString == "yjpxfirstkind")
	{
		if (aquery->FieldByName("bk")->AsString == "lastyjpxdiscount" ) {
			cblastyjpx ->Checked = true;
			cbadddot->Checked = false;
		}
		else
		{
			cblastyjpx ->Checked = false;
			cbadddot->Checked = true;
		}

	}
	if (aquery->FieldByName("name")->AsAnsiString == "xiaoshudian" ) {
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
	if (aquery->FieldByName("name")->AsAnsiString == "storageday" ) {
		cbstoragehistory->Checked = aquery->FieldByName("value")->AsBoolean ;
		edstorageday->Text = aquery->FieldByName("bk")->AsString ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "rkallsupplier")
	{
		cbrkallsupplier->Checked = aquery->FieldByName("value")->AsBoolean ;

	}
	//查单
	if (aquery->FieldByName("name")->AsAnsiString == "rkusefind")
	{
		cbrkusefind->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//删单
	if (aquery->FieldByName("name")->AsAnsiString == "rkusedelete")
	{
		cbrkusedelete->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//退货
	if (aquery->FieldByName("name")->AsAnsiString == "rkusetuihuo")
	{
		cbrkusetuihuo->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//入库打印备注
	/*if (aquery->FieldByName("name")->AsAnsiString == "rkprintbk" ) {
		cbrkprintbk->Checked = aquery->FieldByName("value")->AsBoolean ;
		edrkprintbk->Text = aquery->FieldByName("bk")->AsString ;
	} */
	//是否启用多货源
	if (aquery->FieldByName("name")->AsAnsiString == "mutisupplier")
	{
		chmutisupplier->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//有库存引用可删除库位
	if (aquery->FieldByName("name")->AsAnsiString == "deletestack")
	{
		chdeletestack->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//退货率计算时间
	if (aquery->FieldByName("name")->AsAnsiString == "rkbenqituihuolv")
	{
		edmonth->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//修改单头
	if (aquery->FieldByName("name")->AsAnsiString == "rkusechange")
	{
		cbrkusechange->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//上次预计零售折扣
	if (aquery->FieldByName("name")->AsAnsiString == "lastyjlsdiscount")
	{
		cblastyjlsdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//重复录入提示
	if (aquery->FieldByName("name")->AsAnsiString == "storagesametishi")
	{
		chstoragesametishi->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//地址
	/*if (aquery->FieldByName("name")->AsAnsiString == "rkaddress")
	{
		edrkaddress->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//抬头
	if (aquery->FieldByName("name")->AsAnsiString == "rkprinttitle")
	{
		edrkprinttitle->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//联系人
	if (aquery->FieldByName("name")->AsAnsiString == "rkcontact")
	{
		edrkcontact->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//电话
	if (aquery->FieldByName("name")->AsAnsiString == "rktel")
	{
		edrktel->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}  */
	//退货监管
	if (aquery->FieldByName("name")->AsAnsiString == "rktuihuoguanli")
	{
		chrktuihuoguanli->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	aquery->Next();
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstoragebsset::cblastyjpxClick(TObject *Sender)
{
	if (cblastyjpx->Checked) {
		cbadddot->Checked = false;
	}
	else
	{
		cbadddot->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstoragebsset::cbadddotClick(TObject *Sender)
{
	if (cbadddot->Checked) {
		cblastyjpx->Checked = false;
	}
	else
	{
    	cblastyjpx->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmstoragebsset::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------


