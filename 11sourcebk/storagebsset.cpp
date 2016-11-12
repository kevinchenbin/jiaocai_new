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

   //�Ƿ������ظ�¼��
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
   //�Ƿ��Զ�ע���ɹ���¼
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
   //�ж�����¼��ʾ
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
   //�����ϴ�����ۿ�
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
   //����/�˻���ϸ
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
   //Ԥ�������ۿ��Ƿ����ø��ӵ�����
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
   //�����ϴ�Ԥ�������ۿ�
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
   //Ԥ�������ۿ��Ժ�������
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
   //�����ϸ��ʾ���й�Ӧ�̵���ʷ��¼
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
   //���鵥����
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
   //���ɾ������
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
   //����˻�����
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
   //����ӡ��ע
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
   //�Ƿ����ö��Դ
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
   //�п�����ÿ�ɾ����λ
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
   //����˻��ʼ���ʱ��
   if (edmonth->Text == "" ) {
		edmonth->Text == "0";
   }
   sql = "update sys_bsset set bk = " + edmonth->Text + " where name = 'rkbenqituihuolv'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //����޸ĵ�ͷ����
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
   //�����ϴ�Ԥ�������ۿ�
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
   //�ظ�¼����ʾ
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
   /*//����ӡ̧ͷ
   sql = "update sys_bsset set bk = '" + edrkprinttitle->Text.Trim() + "' where name = 'rkprinttitle'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //��ϵ��
   sql = "update sys_bsset set bk = '" + edrkcontact->Text.Trim() + "' where name = 'rkcontact'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�绰
   sql = "update sys_bsset set bk = '" + edrktel->Text.Trim() + "' where name = 'rktel'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //��ַ
   sql = "update sys_bsset set bk = '" + edrkaddress->Text.Trim() + "' where name = 'rkaddress'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL(); */
   //�˻����
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
   MessageBox(0,"ҵ�����óɹ���   ","��ʾ",MB_ICONASTERISK);
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
	//�鵥
	if (aquery->FieldByName("name")->AsAnsiString == "rkusefind")
	{
		cbrkusefind->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//ɾ��
	if (aquery->FieldByName("name")->AsAnsiString == "rkusedelete")
	{
		cbrkusedelete->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//�˻�
	if (aquery->FieldByName("name")->AsAnsiString == "rkusetuihuo")
	{
		cbrkusetuihuo->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//����ӡ��ע
	/*if (aquery->FieldByName("name")->AsAnsiString == "rkprintbk" ) {
		cbrkprintbk->Checked = aquery->FieldByName("value")->AsBoolean ;
		edrkprintbk->Text = aquery->FieldByName("bk")->AsString ;
	} */
	//�Ƿ����ö��Դ
	if (aquery->FieldByName("name")->AsAnsiString == "mutisupplier")
	{
		chmutisupplier->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//�п�����ÿ�ɾ����λ
	if (aquery->FieldByName("name")->AsAnsiString == "deletestack")
	{
		chdeletestack->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//�˻��ʼ���ʱ��
	if (aquery->FieldByName("name")->AsAnsiString == "rkbenqituihuolv")
	{
		edmonth->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//�޸ĵ�ͷ
	if (aquery->FieldByName("name")->AsAnsiString == "rkusechange")
	{
		cbrkusechange->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//�ϴ�Ԥ�������ۿ�
	if (aquery->FieldByName("name")->AsAnsiString == "lastyjlsdiscount")
	{
		cblastyjlsdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//�ظ�¼����ʾ
	if (aquery->FieldByName("name")->AsAnsiString == "storagesametishi")
	{
		chstoragesametishi->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//��ַ
	/*if (aquery->FieldByName("name")->AsAnsiString == "rkaddress")
	{
		edrkaddress->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//̧ͷ
	if (aquery->FieldByName("name")->AsAnsiString == "rkprinttitle")
	{
		edrkprinttitle->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//��ϵ��
	if (aquery->FieldByName("name")->AsAnsiString == "rkcontact")
	{
		edrkcontact->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}
	//�绰
	if (aquery->FieldByName("name")->AsAnsiString == "rktel")
	{
		edrktel->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}  */
	//�˻����
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


