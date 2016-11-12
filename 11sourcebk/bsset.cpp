//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bsset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmbsset *frmbsset;
//---------------------------------------------------------------------------
__fastcall Tfrmbsset::Tfrmbsset(TComponent* Owner,TADOConnection* con)
	: TForm(Owner)
{
   aquery->Connection = con;
   qryretairange->Connection = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbsset::sbokClick(TObject *Sender)
{
   AnsiString sql,bk;
   int bit;
   float ertairange;
   // 零售收款范围
   if (edmin1->Text == "") {
		edmin1->Text = "0";
   }
   if (edmax1->Text == "") {
	   edmax1->Text = "0";
   }
   if (edlost1->Text == "") {
	   edlost1->Text = "0";
   }
   if (edmin2->Text == "") {
		edmin2->Text = "0";
   }
   if (edmax2->Text == "") {
	   edmax2->Text = "0";
   }
   if (edlost2->Text == "") {
	   edlost2->Text = "0";
   }
   if (edmin3->Text == "") {
		edmin3->Text = "0";
   }
   if (edmax3->Text == "") {
	   edmax3->Text = "0";
   }
   if (edlost3->Text == "") {
	   edlost3->Text = "0";
   }
   if (edmin4->Text == "") {
		edmin4->Text = "0";
   }
   if (edmax4->Text == "") {
	   edmax4->Text = "0";
   }
   if (edlost4->Text == "") {
	   edlost4->Text = "0";
   }
   if (edmin5->Text == "") {
		edmin5->Text = "0";
   }
   if (edmax5->Text == "") {
	   edmax5->Text = "0";
   }
   if (edlost5->Text == "") {
	   edlost5->Text = "0";
   }
   try {
		ertairange = StrToFloat(edmin1->Text);
		ertairange = StrToFloat(edmin2->Text);
		ertairange = StrToFloat(edmin3->Text);
		ertairange = StrToFloat(edmin4->Text);
		ertairange = StrToFloat(edmin5->Text);
		ertairange = StrToFloat(edmax1->Text);
		ertairange = StrToFloat(edmax2->Text);
		ertairange = StrToFloat(edmax3->Text);
		ertairange = StrToFloat(edmax4->Text);
		ertairange = StrToFloat(edmax5->Text);
		ertairange = StrToFloat(edlost1->Text);
		ertairange = StrToFloat(edlost2->Text);
		ertairange = StrToFloat(edlost3->Text);
		ertairange = StrToFloat(edlost4->Text);
		ertairange = StrToFloat(edlost5->Text);
   } catch (...) {
		MessageBox(0,"请输入正确的收款范围！","",MB_OK);
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
	   MessageBox(0,"小数位数最高只能设置4位！","",MB_OK);
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
   //允许无销售退货
   if (cbnosalereturn->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'nosalereturn'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'nosalereturn'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //零售范围设置
   qryretairange->First();
   sql = "update sys_bsset set boundmix = " + edmin1->Text + ",boundmax = " + edmax1->Text + ",bk = '" + edlost1->Text ;
   if (cbeffect1->Checked ) {
	   sql = sql + "',value = 1 ";
   }
   else
   {
		sql = sql + "',value = 0 ";
   }
   sql = sql + "where ID = " + qryretairange->FieldByName("ID")->AsString ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   qryretairange->Next();
   sql = "update sys_bsset set boundmix = " + edmin2->Text + ",boundmax = " + edmax2->Text + ",bk = '" + edlost2->Text ;
   if (cbeffect2->Checked ) {
	   sql = sql + "',value = 1 ";
   }
   else
   {
		sql = sql + "',value = 0 ";
   }
   sql = sql + "where ID = " + qryretairange->FieldByName("ID")->AsString ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   qryretairange->Next();
   sql = "update sys_bsset set boundmix = " + edmin3->Text + ",boundmax = " + edmax3->Text + ",bk = '" + edlost3->Text ;
   if (cbeffect3->Checked ) {
	   sql = sql + "',value = 1 ";
   }
   else
   {
		sql = sql + "',value = 0 ";
   }
   sql = sql + "where ID = " + qryretairange->FieldByName("ID")->AsString ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   qryretairange->Next();
   sql = "update sys_bsset set boundmix = " + edmin4->Text + ",boundmax = " + edmax4->Text + ",bk = '" + edlost4->Text ;
   if (cbeffect4->Checked ) {
	   sql = sql + "',value = 1 ";
   }
   else
   {
		sql = sql + "',value = 0 ";
   }
   sql = sql + "where ID = " + qryretairange->FieldByName("ID")->AsString ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   qryretairange->Next();
   sql = "update sys_bsset set boundmix = " + edmin5->Text + ",boundmax = " + edmax5->Text + ",bk = '" + edlost5->Text ;
   if (cbeffect5->Checked ) {
	   sql = sql + "',value = 1 ";
   }
   else
   {
		sql = sql + "',value = 0 ";
   }
   sql = sql + "where ID = " + qryretairange->FieldByName("ID")->AsString ;
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
   //是否可更改零售折扣
   if (cbRetailDiscountChange->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'RetailDiscountChange'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'RetailDiscountChange'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
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
   //警告信用额度
   if (cbalarmcredit->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'alarmcredit'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'alarmcredit'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //禁止信用额度
   if (cbforbidcredit->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'forbidcredit'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'forbidcredit'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //警告退货率
   if (cbalarmbackrate->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'alarmbackrate'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'alarmbackrate'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //禁用退货率
   if (cbforbidbackrate->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'forbidbackrate'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'forbidbackrate'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   MessageBox(0,"业务设置成功！","",MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbsset::FormShow(TObject *Sender)
{
	Readydata();

}
//---------------------------------------------------------------------------

void __fastcall Tfrmbsset::sbcancelClick(TObject *Sender)
{
   Close();
}
void Tfrmbsset::Readydata()
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
	if (aquery->FieldByName("name")->AsAnsiString == "bear")
	{
		cbbear->Checked = aquery->FieldByName("value")->AsBoolean ;

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
	if (aquery->FieldByName("name")->AsAnsiString == "nosalereturn" ) {
		cbnosalereturn->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "storageday" ) {
		cbstoragehistory->Checked = aquery->FieldByName("value")->AsBoolean ;
		edstorageday->Text = aquery->FieldByName("bk")->AsString ;
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
	if (aquery->FieldByName("name")->AsAnsiString == "autolocalstockbyOrder") {
		cbautolocalstockbyOrder->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "RetailDiscountChange" ) {
		cbRetailDiscountChange->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "alarmcredit" ) {
		cbalarmcredit->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "forbidcredit" ) {
		cbforbidcredit->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "alarmbackrate" ) {
		cbalarmbackrate->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "forbidbackrate" ) {
    	cbforbidbackrate->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxdiscount" ) {
    	cbpxdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	aquery->Next();
  }
  sql = "select * from SYS_BSSET where name = 'retairangge' order by ID";
  qryretairange->Close();
  qryretairange->SQL->Clear();
  qryretairange->SQL->Add(sql);
  qryretairange->Open();
  qryretairange->First();
  edmin1->Text = qryretairange->FieldByName("boundmix")->AsString ;
  edmax1->Text = qryretairange->FieldByName("boundmax")->AsString ;
  edlost1->Text = qryretairange->FieldByName("bk")->AsString ;
  cbeffect1->Checked = qryretairange->FieldByName("value")->AsBoolean;
  qryretairange->Next();
  edmin2->Text = qryretairange->FieldByName("boundmix")->AsString ;
  edmax2->Text = qryretairange->FieldByName("boundmax")->AsString ;
  edlost2->Text = qryretairange->FieldByName("bk")->AsString ;
  cbeffect2->Checked = qryretairange->FieldByName("value")->AsBoolean;
  qryretairange->Next();
  edmin3->Text = qryretairange->FieldByName("boundmix")->AsString ;
  edmax3->Text = qryretairange->FieldByName("boundmax")->AsString ;
  edlost3->Text = qryretairange->FieldByName("bk")->AsString ;
  cbeffect3->Checked = qryretairange->FieldByName("value")->AsBoolean;
  qryretairange->Next();
  edmin4->Text = qryretairange->FieldByName("boundmix")->AsString ;
  edmax4->Text = qryretairange->FieldByName("boundmax")->AsString ;
  edlost4->Text = qryretairange->FieldByName("bk")->AsString ;
  cbeffect4->Checked = qryretairange->FieldByName("value")->AsBoolean;
  qryretairange->Next();
  edmin5->Text = qryretairange->FieldByName("boundmix")->AsString ;
  edmax5->Text = qryretairange->FieldByName("boundmax")->AsString ;
  edlost5->Text = qryretairange->FieldByName("bk")->AsString ;
  cbeffect5->Checked = qryretairange->FieldByName("value")->AsBoolean;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbsset::cbeffect1Click(TObject *Sender)
{
	if (cbeffect1->Checked ) {
		if (edmin1->Text == "") {
			edmin1->Text = "0";
		}
		if (edmax1->Text == "") {
			edmax1->Text = "0";
		}
		float min,max;
		min = StrToFloat(edmin1->Text);
		max = StrToFloat(edmax1->Text);
		if (min >= max) {
			MessageBox(0,"最大范围必须大于最小范围！","设置错误" ,MB_OK);
			cbeffect1->Checked = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbsset::cbeffect2Click(TObject *Sender)
{
	if (cbeffect2->Checked ) {
		if (edmin2->Text == "") {
			edmin2->Text = "0";
		}
		if (edmax2->Text == "") {
			edmax2->Text = "0";
		}
		float min,max;
		min = StrToFloat(edmin2->Text);
		max = StrToFloat(edmax2->Text);
		if (min >= max) {
			MessageBox(0,"最大范围必须大于最小范围！","设置错误" ,MB_OK);
			cbeffect2->Checked = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbsset::cbeffect3Click(TObject *Sender)
{
	if (cbeffect3->Checked ) {
		if (edmin3->Text == "") {
			edmin3->Text = "0";
		}
		if (edmax3->Text == "") {
			edmax3->Text = "0";
		}
		float min,max;
		min = StrToFloat(edmin3->Text);
		max = StrToFloat(edmax3->Text);
		if (min >= max) {
			MessageBox(0,"最大范围必须大于最小范围！","设置错误" ,MB_OK);
			cbeffect3->Checked = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbsset::cbeffect4Click(TObject *Sender)
{
	if (cbeffect4->Checked ) {
		if (edmin4->Text == "") {
			edmin4->Text = "0";
		}
		if (edmax4->Text == "") {
			edmax4->Text = "0";
		}
		float min,max;
		min = StrToFloat(edmin4->Text);
		max = StrToFloat(edmax4->Text);
		if (min >= max) {
			MessageBox(0,"最大范围必须大于最小范围！","设置错误" ,MB_OK);
			cbeffect4->Checked = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbsset::cbeffect5Click(TObject *Sender)
{
	if (cbeffect5->Checked ) {
		if (edmin5->Text == "") {
			edmin5->Text = "0";
		}
		if (edmax5->Text == "") {
			edmax5->Text = "0";
		}
		float min,max;
		min = StrToFloat(edmin5->Text);
		max = StrToFloat(edmax5->Text);
		if (min >= max) {
			MessageBox(0,"最大范围必须大于最小范围！","设置错误" ,MB_OK);
			cbeffect5->Checked = false;
		}
	}
}
//---------------------------------------------------------------------------

