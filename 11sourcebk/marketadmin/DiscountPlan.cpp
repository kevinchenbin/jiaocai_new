//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DiscountPlan.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzRadChk"
#pragma link "RzEdit"
#pragma link "RzDTP"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TFormDiscount *FormDiscount;
//---------------------------------------------------------------------------
__fastcall TFormDiscount::TFormDiscount(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TFormDiscount::Init(TApplication* app, TADOConnection* con,int stgid)
{
    fstgid = stgid;
	query->Connection = con;
	querydetail->Connection = con;
	cn = con;
	//���������ʾ
	AnsiString sql;
	dtpstart->Date = Date();
	dtpend->Date = Date();
	type = 1;
	//����׷��
	//cbstgid->Enabled = false;
	sql = "select ID,Name from SYS_StorageInfo";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof)
	{
		cbstgid->AddItem(query->FieldByName("Name")->AsString,(TObject *)query->FieldByName("ID")->AsInteger );
		query->Next();
	}
	cbstgid->ItemIndex = cbstgid->Items->IndexOfObject((TObject*)stgid) ;

	sql = "select Master from SYS_StorageInfo where id = " + IntToStr(stgid);
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("Master")->AsBoolean ) {
		cbstgid->Enabled = true;
	}
	else
	{
		cbstgid->Enabled = false;
	}
	//���׷��
	sql = "select ID,Name from BS_BookType";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof )
	{
		cbtype->AddItem(query->FieldByName("Name")->AsString,(TObject *)query->FieldByName("ID")->AsInteger );
		query->Next();
	}
	cbtype->ItemIndex = 0;
	//��Ա���׷��
	sql = "select IDType,Type from CUST_MemberType";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof)
	{
		cbmembertype->AddItem(query->FieldByName("Type")->AsString ,(TObject*)query->FieldByName("IDType")->AsInteger );
		query->Next();
	}
    cbmembertype->ItemIndex = 0;
	//���۷���׷��
	//rzdiscounttype->Add("������");
	type = 1;
	Labelname->Caption = "��Ŀ���";
	sql = "select A.*,C.Name as storagename, B.Name,CUST_MemberType.Type as memtype,convert(varchar(20),A.Endtime,23) as endtime1,case when A.Membereffect = 'True' then '��' when Membereffect = 'False' then '��' end as effectname from BS_DiscountInfo_tmp A left join BS_BookType B on A.BookTypeID = B.ID left join CUST_MemberType on A.MemberType = CUST_MemberType.IDType left join SYS_StorageInfo C ON A.StgID = C.id where A.type = " + IntToStr(type) + " and A.StgID = " + IntToStr(stgid) ;
	querydetail->Close();
	querydetail->SQL->Clear();
	querydetail->SQL->Add(sql);
	querydetail->Open();

	disable();
}
void __fastcall TFormDiscount::cbstgidSelect(TObject *Sender)
{
	AnsiString sql;
	try {
		fstgid =  (int)cbstgid->Items->Objects[cbstgid->ItemIndex];
	} catch (...) {
		MessageBox(0,"��ѡ����ȷ�ĵ�����","����" ,MB_OK);
		return;
	}
	sql = "select A.*,C.Name as storagename, B.Name,CUST_MemberType.Type as memtype,convert(varchar(20),A.Endtime,23) as endtime1,case when A.Membereffect = 'True' then '��' when Membereffect = 'False' then '��' end as effectname from BS_DiscountInfo_tmp A left join BS_BookType B on A.BookTypeID = B.ID left join CUST_MemberType on A.MemberType = CUST_MemberType.IDType left join SYS_StorageInfo C ON A.StgID = C.id where A.type = " + IntToStr(type) + " and A.StgID = " + IntToStr(fstgid) ;
	querydetail->Close();
	querydetail->SQL->Clear();
	querydetail->SQL->Add(sql);
	querydetail->Open();

	disable();
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::dbgdiscountCellClick(TColumn *Column)
{
	disable();
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::NdeleteClick(TObject *Sender)
{
	if (querydetail->RecordCount > 0) {
		AnsiString sql;
		sql = "delete from BS_DiscountInfo_tmp where id = " + querydetail->FieldByName("ID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		querydetail->Active = false;
		querydetail->Active = true;
		((TFloatField *)querydetail->FieldByName("Discount"))->DisplayFormat = "##0.00%";
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::disable()
{
	if (!querydetail->IsEmpty()) {
		cbtype->ItemIndex = cbtype->Items->IndexOf(querydetail->FieldByName("Name")->AsString);
		//cbtype->Text = querydetail->FieldByName("Name")->AsString ;
		cbmembertype->ItemIndex = cbmembertype->Items->IndexOfObject((TObject*)querydetail->FieldByName("MemberType")->AsInteger );
		eddiscount->Text = querydetail->FieldByName("Discount")->AsString ;
		cbMonday->Checked =  querydetail->FieldByName("Monday")->Value;
		cbTuesday->Checked = querydetail->FieldByName("Tuesday")->Value;
		cbWednesday->Checked = querydetail->FieldByName("Wednesday")->Value;
		cbThursday->Checked = querydetail->FieldByName("Thursday")->Value;
		cbFriday->Checked = querydetail->FieldByName("Friday")->Value;
		cbSaturday->Checked = querydetail->FieldByName("Saturday")->Value;
		cbSunday->Checked = querydetail->FieldByName("Sunday")->Value;
		rcbMember->Checked = querydetail->FieldByName("Membereffect")->Value;
		dtpstart->Date = querydetail->FieldByName("Starttime")->AsDateTime ;
		dtpend->Date = querydetail->FieldByName("Endtime")->AsDateTime ;
		cball->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::cbtypeChange(TObject *Sender)
{
	AnsiString sql;
	if (cbtype->Text != "") {
		sql = "select A.*, B.Name from BS_DiscountInfo_tmp A left join BS_BookType B on A.BookTypeID = B.ID where B.Name = '" + cbtype->Text.Trim()  + "' and A.StgID = " + IntToStr(fstgid) + " and MemberType = " + IntToStr((int)cbmembertype->Items->Objects[cbmembertype->ItemIndex]) ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->RecordCount > 0) {
			eddiscount->Text = query->FieldByName("Discount")->AsString ;
			cbMonday->Checked =  query->FieldByName("Monday")->Value;
			cbTuesday->Checked = query->FieldByName("Tuesday")->Value;
			cbWednesday->Checked = query->FieldByName("Wednesday")->Value;
			cbThursday->Checked = query->FieldByName("Thursday")->Value;
			cbFriday->Checked = query->FieldByName("Friday")->Value;
			cbSaturday->Checked = query->FieldByName("Saturday")->Value;
			cbSunday->Checked = query->FieldByName("Sunday")->Value;
			rcbMember->Checked = query->FieldByName("Membereffect")->Value;
			dtpstart->Date = querydetail->FieldByName("Starttime")->AsDateTime ;
			dtpend->Date = querydetail->FieldByName("Endtime")->AsDateTime ;
			cball->Checked = true;
		}
		else
		{
			eddiscount->Text = "" ;
			cbMonday->Checked =  false;
			cbTuesday->Checked = false;
			cbWednesday->Checked = false;
			cbThursday->Checked = false;
			cbFriday->Checked = false;
			cbSaturday->Checked = false;
			cbSunday->Checked = false;
			rcbMember->Checked = true;
			dtpstart->Date = Date();
			dtpend->Date = Date();
			cball->Checked = false;
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TFormDiscount::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::eddiscountKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::BtnAlignBottomClick(TObject *Sender)
{
	WindowState  = wsMinimized;
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
	if (Key == VK_F4) {   //����
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::BtnSaveClick(TObject *Sender)
{
	AnsiString sql;
	if (cbtype->Visible ) {
		if (cbtype->Text == "") {
			MessageBox(0,"��ѡ����۵����ͣ�","������ʾ" ,MB_OK);
			return;
		}
	}
	if (eddiscount->Text == "") {
		MessageBox(0,"�ۿ۲���Ϊ�գ�","������ʾ" ,MB_OK);
		return;
	}
	int discount =  StrToInt(eddiscount->Text);
	if (discount < 0) {
		MessageBox(0,"�ۿ۲���С��0��","������ʾ" ,MB_OK);
		return;
	}
	if (discount > 100) {
		MessageBox(0,"�ۿ۲��ܴ���100��","������ʾ" ,MB_OK);
		return;
	}
	int start,end;
	if (dtpstart->Date > dtpend->Date ) {
		MessageBox(0,"�������ڱ�����ڿ�ʼ���ڣ�","������ʾ" ,MB_OK);
		return;
	}
	int booktype,memtype;
	try {
		booktype = int(cbtype->Items->Objects[cbtype->ItemIndex]);
	} catch (...) {
		MessageBox(0,"��ѡ����ȷ����Ŀ���","����" ,MB_OK);
		return;
	}
	try {
		memtype =  (int)cbmembertype->Items->Objects[cbmembertype->ItemIndex];
	} catch (...) {
		MessageBox(0,"��ѡ����ȷ�Ļ�Ա���","����" ,MB_OK);
		return;
	}
	try {
		fstgid =  (int)cbstgid->Items->Objects[cbstgid->ItemIndex];
	} catch (...) {
		MessageBox(0,"��ѡ����ȷ�ĵ�����","����" ,MB_OK);
		return;
	}
	type = 1;
	sql = "select * from BS_DiscountInfo_tmp where Type = " + IntToStr(type) + " and StgID = " + IntToStr(fstgid) + " and MemberType = " + IntToStr(memtype) + " and BookTypeID = " + IntToStr(booktype) ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {    //�޸�
		sql = "update BS_DiscountInfo_tmp set Discount = " + eddiscount->Text +",Starttime = '" + DateToStr(dtpstart->Date) + "',Endtime = '" + DateToStr(dtpend->Date) + " 23:59:59'";
		if (cbMonday->Checked ) {
			sql = sql + ",Monday = 1";
		}
		else
		{
			sql = sql + ",Monday = 0";
		}
		if (cbTuesday->Checked ) {
			sql = sql + ",Tuesday = 1";
		}
		else
		{
			sql = sql + ",Tuesday = 0";
		}
		if (cbWednesday->Checked ) {
			sql = sql + ",Wednesday = 1";
		}
		else
		{
			sql = sql + ",Wednesday = 0";
		}
		if (cbThursday->Checked ) {
			sql = sql + ",Thursday = 1";
		}
		else
		{
        	sql = sql + ",Thursday = 0";
		}
		if (cbFriday->Checked) {
			sql = sql + ",Friday = 1";
		}
		else
		{
			sql = sql + ",Friday = 0";
		}
		if (cbSaturday->Checked ) {
			sql = sql + ",Saturday = 1";
		}
		else
		{
			sql = sql + ",Saturday = 0";
		}
		if (cbSunday->Checked ) {
			sql = sql + ",Sunday = 1";
		}
		else
		{
			sql = sql + ",Sunday = 0";
		}
		if (rcbMember->Checked ) {
			sql = sql + ",Membereffect = 1";
		}
		else
		{
			sql = sql + ",Membereffect = 0";
		}
		sql = sql + " where ID = " + query->FieldByName("ID")->AsString;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		querydetail->UpdateBatch(arAll);
		querydetail->Active = false;
		querydetail->Active = true;
		((TFloatField *)querydetail->FieldByName("Discount"))->DisplayFormat = "##0.00%";
		//querydetail->Refresh();
	}
	else  //���
	{
    	if (querydetail->State != dsInsert) {
			querydetail->Append();
		}
		querydetail->FieldByName("StgID")->AsInteger = fstgid;
		querydetail->FieldByName("Type")->AsInteger = type;
		if (cbtype->Visible ) {
			int booktypeid = int(cbtype->Items->Objects[cbtype->ItemIndex]);
			querydetail->FieldByName("BookTypeID")->AsInteger = booktypeid;
		}
		querydetail->FieldByName("Discount")->AsFloat =  StrToFloat(eddiscount->Text);
		querydetail->FieldByName("MemberType")->AsInteger = (int)cbmembertype->Items->Objects[cbmembertype->ItemIndex];
		querydetail->FieldByName("Monday")->Value  = cbMonday->Checked;
		querydetail->FieldByName("Tuesday")->Value  = cbTuesday->Checked;
		querydetail->FieldByName("Wednesday")->Value  = cbWednesday->Checked;
		querydetail->FieldByName("Thursday")->Value  = cbThursday->Checked;
		querydetail->FieldByName("Friday")->Value  = cbFriday->Checked;
		querydetail->FieldByName("Saturday")->Value  = cbSaturday->Checked;
		querydetail->FieldByName("Sunday")->Value  = cbSunday->Checked;
		querydetail->FieldByName("Membereffect")->Value  = rcbMember->Checked;
		querydetail->FieldByName("Starttime")->AsString = DateToStr(dtpstart->Date);
		querydetail->FieldByName("Endtime")->AsString = DateToStr(dtpend->Date) + " 23:59:59";
		querydetail->UpdateBatch(arAll);
		querydetail->Active = false;
		querydetail->Active = true;
		((TFloatField *)querydetail->FieldByName("Discount"))->DisplayFormat = "##0.00%";
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::cballClick(TObject *Sender)
{
	if (cball->Checked ) {
		cbMonday->Checked = true;
		cbTuesday->Checked = true;
		cbWednesday->Checked = true;
		cbThursday->Checked = true;
		cbFriday->Checked = true;
		cbSaturday->Checked = true;
		cbSunday->Checked = true;
	}
	else
	{
		cbMonday->Checked = false;
		cbTuesday->Checked = false;
		cbWednesday->Checked = false;
		cbThursday->Checked = false;
		cbFriday->Checked = false;
		cbSaturday->Checked = false;
		cbSunday->Checked = false;
	}
}
//---------------------------------------------------------------------------

