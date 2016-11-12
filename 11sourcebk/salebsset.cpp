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
   //���ȼ����ж�
   if ((cb1->ItemIndex == cb2->ItemIndex ) || (cb1->ItemIndex == cb3->ItemIndex) ||
	   (cb1->ItemIndex == cb4->ItemIndex ) || (cb2->ItemIndex == cb3->ItemIndex) ||
	   (cb2->ItemIndex == cb4->ItemIndex ) || (cb3->ItemIndex == cb4->ItemIndex )) {
		MessageBox(0,"ͬһ���۷�ʽ����ͬʱΪ��������","����",MB_ICONWARNING);
		return;
   }
   //С����λ��
   if (etdot->Text == "") {
		bit = 0;
   }
   else
   {
		bit = StrToInt(etdot->Text.Trim() );
   }
   if (bit > 4) {
	   MessageBox(0,"С��λ�����ֻ������4λ��","����",MB_ICONWARNING);
	   return;
   }
   //Ĭ�������ۿ�
   try {
		defaultdiscount = StrToFloat(eddefaultdiscount->Text);
   } catch (...) {
		MessageBox(0,"��������ȷ���ۿۣ�","����",MB_ICONWARNING);
		return;
   }
   if (defaultdiscount > 100) {
		MessageBox(0,"�ۿ۲��ܴ���100��","����",MB_ICONWARNING);
		return;
   }
   if (defaultdiscount < 0) {
		MessageBox(0,"�ۿ۲���С��0��","����",MB_ICONWARNING);
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
   //ͼ����Ϊ0ʱ�Ƿ��г�
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
   //�Ƿ������������
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
   //������ʷ��ϸ
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
   //��ǰ�ͻ���/Ƿ�������ʾ
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
   //�Ƿ������������˻�
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
   //���������ϴ��ۿ�
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
   //���ڳɱ��ۿ�����
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
   //���ڳɱ��ۿ��Ƿ񷢻�
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
   //���������ۿ�����
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
   //���������ۿ��Ƿ񷢻�
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
   //�����޸��ۿ۵�����
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
   //�����˻����
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
   //�ֳ��տ��Ƿ����
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
   //������ϸ��ʾ���Կͻ���ʷ��¼
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
   //����ɾ�������Ƿ�����
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
   //�����鵥�����Ƿ�����
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
   //�����˻������Ƿ�����
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
   //�޿������
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
   //�޿�������˻�
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
   //����Ĭ���ۿ�
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
   //�޿�������˻�
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
   //�˻��ʼ���ʱ��
   if (edmonth->Text == "" ) {
		edmonth->Text == "0" ;
   }
   sql = "update sys_bsset set bk = " + edmonth->Text + "where name = 'pxbenqituihuolv'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�����޸ĵ�ͷ�����Ƿ�����
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
   //�ظ�¼����ʾ
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
   //�ͻ��ӵ��ۿ�����
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
   //�����˻�����
   if (edpxtuihuoqixian->Text == "") {
	   edpxtuihuoqixian->Text = "0";
   }
   sql = "update sys_bsset set bk = '" + edpxtuihuoqixian->Text + "' where name = 'pxtuihuoqixian'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //������ӡ̧ͷ
   /*sql = "update sys_bsset set bk = '" + edwsprinttitle->Text.Trim() + "' where name = 'wsprinttitle'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //��ϵ��
   sql = "update sys_bsset set bk = '" + edwscontact->Text.Trim() + "' where name = 'wscontact'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�绰
   sql = "update sys_bsset set bk = '" + edwstel->Text.Trim() + "' where name = 'wstel'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //��ַ
   sql = "update sys_bsset set bk = '" + edwsaddress->Text.Trim() + "' where name = 'wsaddress'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();   */
   //���۷�ʽ
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
   //���ȼ���
   //һ��
   if (cb1->Text == "Ӫ������������������") {
		sql = "update sys_bsset set bk = '1' where name = 'pxsinglebook'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb1->Text == "���Ԥ�������ۿ�") {
   		sql = "update sys_bsset set bk = '1' where name = 'pxrkyjdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb1->Text == "�����ϴ��ۿ�") {
		sql = "update sys_bsset set bk = '1' where name = 'pxlastdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb1->Text == "����Ĭ���ۿ�") {
		sql = "update sys_bsset set bk = '1' where name = 'pxmorendiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   //����
   if (cb2->Text == "Ӫ������������������") {
		sql = "update sys_bsset set bk = '2' where name = 'pxsinglebook'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb2->Text == "���Ԥ�������ۿ�") {
		sql = "update sys_bsset set bk = '2' where name = 'pxrkyjdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb2->Text == "�����ϴ��ۿ�") {
		sql = "update sys_bsset set bk = '2' where name = 'pxlastdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb2->Text == "����Ĭ���ۿ�") {
		sql = "update sys_bsset set bk = '2' where name = 'pxmorendiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   //����
   if (cb3->Text == "Ӫ������������������") {
		sql = "update sys_bsset set bk = '3' where name = 'pxsinglebook'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb3->Text == "���Ԥ�������ۿ�") {
		sql = "update sys_bsset set bk = '3' where name = 'pxrkyjdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb3->Text == "�����ϴ��ۿ�") {
		sql = "update sys_bsset set bk = '3' where name = 'pxlastdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb3->Text == "����Ĭ���ۿ�") {
		sql = "update sys_bsset set bk = '3' where name = 'pxmorendiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   //�ļ�
   if (cb4->Text == "Ӫ������������������") {
		sql = "update sys_bsset set bk = '4' where name = 'pxsinglebook'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb4->Text == "���Ԥ�������ۿ�") {
		sql = "update sys_bsset set bk = '4' where name = 'pxrkyjdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb4->Text == "�����ϴ��ۿ�") {
		sql = "update sys_bsset set bk = '4' where name = 'pxlastdiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else if (cb4->Text == "����Ĭ���ۿ�") {
		sql = "update sys_bsset set bk = '4' where name = 'pxmorendiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   MessageBox(0,"ҵ�����óɹ���       ","��ʾ",MB_ICONASTERISK);
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
	//������ӡ��ע
	/*if (aquery->FieldByName("name")->AsAnsiString == "pxprintbk" ) {
		cbpxprintbk->Checked = aquery->FieldByName("value")->AsBoolean ;
		edpxprintbk->Text = aquery->FieldByName("bk")->AsString ;
	}   */
	//����Ĭ���ۿ�
	if (aquery->FieldByName("name")->AsAnsiString == "pxdefaultdiscount" ) {
		cbpxdefaultdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
		eddefaultdiscount->Text = aquery->FieldByName("bk")->AsString ;
	}
	//�������۷�ʽ
	if (aquery->FieldByName("name")->AsAnsiString == "pxpriordiscount" ) {
		if (aquery->FieldByName("value")->AsBoolean) {
			RadioGroup1->ItemIndex = 0;
		}
		else
		{
        	RadioGroup1->ItemIndex = 1;
		}
	}
	//�޿�������˻�
	if (aquery->FieldByName("name")->AsAnsiString == "nokucunpxth" ) {
		chnokucunpxth->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//�ظ�¼����ʾ
	if (aquery->FieldByName("name")->AsAnsiString == "wsalesametishi" ) {
		chwsalesametishi->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//�˻��ʼ���ʱ��
	if (aquery->FieldByName("name")->AsAnsiString == "pxbenqituihuolv")
	{
		edmonth->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//�ͻ��ӵ��ۿ�����
	if (aquery->FieldByName("name")->AsAnsiString == "clientaddyx" ) {
		chclientaddyx->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//�����˻�����
	if (aquery->FieldByName("name")->AsAnsiString == "pxtuihuoqixian")
	{
		edpxtuihuoqixian->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//��ַ
	/*if (aquery->FieldByName("name")->AsAnsiString == "wsaddress")
	{
		edwsaddress->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//̧ͷ
	if (aquery->FieldByName("name")->AsAnsiString == "wsprinttitle")
	{
		edwsprinttitle->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//��ϵ��
	if (aquery->FieldByName("name")->AsAnsiString == "wscontact")
	{
		edwscontact->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//�绰
	if (aquery->FieldByName("name")->AsAnsiString == "wstel")
	{
		edwstel->Text = aquery->FieldByName("bk")->AsAnsiString ;
	} */
	//���ȼ���
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

