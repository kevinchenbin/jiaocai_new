//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "retailbsset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmretailbsset *frmretailbsset;
//---------------------------------------------------------------------------
__fastcall Tfrmretailbsset::Tfrmretailbsset(TComponent* Owner,TADOConnection* con)
	: TForm(Owner)
{
   aquery->Connection = con;
   qryretairange->Connection = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmretailbsset::sbokClick(TObject *Sender)
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
   if (bit > 2) {
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
   sql = "update sys_bsset set bk = '" + bk + "' where name = 'retailxiaoshudian'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   float ertairange,discount;
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
		MessageBox(0,"请输入正确的收款范围！","警告",MB_ICONWARNING);
		return;
   }
   try {
		discount = StrToFloat(edlsdiscount->Text);
   } catch (...) {
		MessageBox(0,"请输入正确的最低零售折扣！","警告",MB_ICONWARNING);
		return;
   }
   if (discount > 100 || discount < 0) {
		MessageBox(0,"请输入正确范围内输入零售折扣！","警告",MB_ICONWARNING);
		return;
   }

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
   //小票默认打印
   if (cbxiaopiaoprint->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'xiaopiaoprint'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'xiaopiaoprint'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //零售查单密码是否启用
   if (cblsusefind->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'lsusefind'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lsusefind'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //零售删单密码是否启用
   if (cblsusedelete->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'lsusedelete'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lsusedelete'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //零售退货密码是否启用
   if (cblsusetuihuo->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'lsusetuihuo'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lsusetuihuo'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //零售打印备注
   if (cblsprintbk->Checked ) {
		sql = "update sys_bsset set value = 1,bk = '" + edlsprintbk->Text + "' where name = 'lsprintbk'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,bk = '" + edlsprintbk->Text + "' where name = 'lsprintbk'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //入库零售折扣是否启用
   if (chlsdiscount->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lsdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lsdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //交接版是否打印小票
   if (chjiaojieprint->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'jiaojieprint'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'jiaojieprint'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //允许负库存销售
   if (chretailbear->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'retailbear'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'retailbear'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //会员时会员折扣优先
   if (chMemberdiscountyouxian->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'Memberdiscountyouxian'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'Memberdiscountyouxian'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //单品打折启用
   if (chRetailsingle->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'Retailsingle'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'Retailsingle'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //书目类别打折启用
   if (chRetaitype->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'Retaitype'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'Retaitype'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //零售界面现在打折方案
   if (chRetaiview->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'Retaiview'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'Retaiview'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //前台允许挂单
   if (chguadan->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'guadan'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'guadan'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //前台允许退换
   if (chretailtuihuan->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'retailtuihuan'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'retailtuihuan'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //前台允许输入售价
   if (chretailprice->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'retailprice'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'retailprice'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //退出时提示挂单
   if (chguadantishi->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'guadantishi'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'guadantishi'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //零售换扣密码是否启用
   if (chhuankoupwd->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'huankoupwd'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'huankoupwd'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //零售换价密码是否启用
   if (chhuanjiapwd->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'huanjiapwd'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'huanjiapwd'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //最低零售折扣
   if (chminlsdiscount->Checked ) {
	   sql = "update sys_bsset set value = 1,boundmix = " + edlsdiscount->Text ;
   }
   else
   {
		sql = "update sys_bsset set value = 0,boundmix = " + edlsdiscount->Text ;
   }

   if (chstorage->Checked) {
		sql = sql + ",bk = 1 ";
   }
   else
   {
		sql = sql + ",bk = 0 ";
   }
   sql = sql + " where name = 'minlsdiscount'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   MessageBox(0,"业务设置成功！","提示",MB_ICONASTERISK);
   Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmretailbsset::FormShow(TObject *Sender)
{
	Readydata();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbsset::sbcancelClick(TObject *Sender)
{
   Close();
}
void Tfrmretailbsset::Readydata()
{
  String sql= "select * from sys_bsset",bk;
  int bit;
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  while (!aquery->Eof)
  {
	if (aquery->FieldByName("name")->AsAnsiString == "nosalereturn" ) {
		cbnosalereturn->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "RetailDiscountChange" ) {
		cbRetailDiscountChange->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//小票打印
	if (aquery->FieldByName("name")->AsAnsiString == "xiaopiaoprint" ) {
		cbxiaopiaoprint->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//查单密码
	if (aquery->FieldByName("name")->AsAnsiString == "lsusefind" ) {
		cblsusefind->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//删单密码
	if (aquery->FieldByName("name")->AsAnsiString == "lsusedelete" ) {
		cblsusedelete->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//退货密码
	if (aquery->FieldByName("name")->AsAnsiString == "lsusetuihuo" ) {
		cblsusetuihuo->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//入库零售折扣是否启用
	if (aquery->FieldByName("name")->AsAnsiString == "lsdiscount" ) {
		chlsdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//允许负库存销售
	if (aquery->FieldByName("name")->AsAnsiString == "retailbear" ) {
		chretailbear->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//交接班是否打印小票
	if (aquery->FieldByName("name")->AsAnsiString == "jiaojieprint" ) {
		chjiaojieprint->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//会员时会员折扣优先
	if (aquery->FieldByName("name")->AsAnsiString == "Memberdiscountyouxian" ) {
		chMemberdiscountyouxian->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//单品打折启用
	if (aquery->FieldByName("name")->AsAnsiString == "Retailsingle" ) {
		chRetailsingle->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//书目类别打折启用
	if (aquery->FieldByName("name")->AsAnsiString == "Retaitype" ) {
		chRetaitype->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//零售界面显示打折方案
	if (aquery->FieldByName("name")->AsAnsiString == "Retaiview" ) {
		chRetaiview->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//零售打印备注
	if (aquery->FieldByName("name")->AsAnsiString == "lsprintbk" ) {
		cblsprintbk->Checked = aquery->FieldByName("value")->AsBoolean ;
		edlsprintbk->Text = aquery->FieldByName("bk")->AsString ;
	}

	//前台允许挂单
	if (aquery->FieldByName("name")->AsAnsiString == "guadan" ) {
		chguadan->Checked = aquery->FieldByName("value")->AsBoolean ;
		if (chguadan->Checked ) {
            chguadantishi->Enabled = true;
		}
	}
	//前台允许退换
	if (aquery->FieldByName("name")->AsAnsiString == "retailtuihuan" ) {
		chretailtuihuan->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//前台允许输入售价
	if (aquery->FieldByName("name")->AsAnsiString == "retailprice" ) {
		chretailprice->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//退出时提示挂单
	if (aquery->FieldByName("name")->AsAnsiString == "guadantishi" ) {
		chguadantishi->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//换扣密码
	if (aquery->FieldByName("name")->AsAnsiString == "huankoupwd" ) {
		chhuankoupwd->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//换价密码
	if (aquery->FieldByName("name")->AsAnsiString == "huanjiapwd" ) {
		chhuanjiapwd->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "retailxiaoshudian" ) {
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
	//最低零售折扣
	if (aquery->FieldByName("name")->AsAnsiString == "minlsdiscount" ) {
		chminlsdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
		edlsdiscount->Text = aquery->FieldByName("boundmix")->AsAnsiString ;
		if (aquery->FieldByName("bk")->AsAnsiString == "1") {
			chstorage->Checked = true;
		}
		else
		{
			chstorage->Checked = false;
		}
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

void __fastcall Tfrmretailbsset::cbeffect1Click(TObject *Sender)
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
			MessageBox(0,"最大范围必须大于最小范围！","设置错误" ,MB_ICONWARNING);
			cbeffect1->Checked = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbsset::cbeffect2Click(TObject *Sender)
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
			MessageBox(0,"最大范围必须大于最小范围！","设置错误" ,MB_ICONWARNING);
			cbeffect2->Checked = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbsset::cbeffect3Click(TObject *Sender)
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
			MessageBox(0,"最大范围必须大于最小范围！","设置错误" ,MB_ICONWARNING);
			cbeffect3->Checked = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbsset::cbeffect4Click(TObject *Sender)
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
			MessageBox(0,"最大范围必须大于最小范围！","设置错误" ,MB_ICONWARNING);
			cbeffect4->Checked = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbsset::cbeffect5Click(TObject *Sender)
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
			MessageBox(0,"最大范围必须大于最小范围！","设置错误" ,MB_ICONWARNING);
			cbeffect5->Checked = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbsset::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------

void Tfrmretailbsset::StyleView()

{
	AnsiString labelcaption;
	if (chMemberdiscountyouxian->Checked ) {
		labelcaption = "会员卡折扣";
	}
	if (chlsdiscount->Checked) {
		if (labelcaption == "") {
			labelcaption = "预计零售折扣";
		}
		else
		{
			labelcaption = labelcaption + "->预计零售折扣";
		}
	}
	if (chRetailsingle->Checked) {
		if (labelcaption == "") {
			labelcaption = "单品设置折扣";
		}
		else
		{
			labelcaption = labelcaption + "->单品设置折扣";
		}
	}
	if (chRetaitype->Checked) {
		if (labelcaption == "") {
			labelcaption = "书目类别打折";
		}
		else
		{
			labelcaption = labelcaption + "->书目类别打折";
		}
	}
	if (!chMemberdiscountyouxian->Checked) {
		if (labelcaption == "") {
			labelcaption = "会员类型折扣";
		}
		else
		{
			labelcaption = labelcaption + "->会员类型折扣";
		}
	}
	Label23->Caption = "当前打折方案：" + labelcaption;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmretailbsset::chlsdiscountClick(TObject *Sender)
{
	StyleView();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmretailbsset::chguadanClick(TObject *Sender)
{
	if (chguadan->Checked ) {
		chguadantishi->Enabled = true;
	}
	else
	{
    	chguadantishi->Checked = false;
		chguadantishi->Enabled = false;
	}
}
//---------------------------------------------------------------------------

