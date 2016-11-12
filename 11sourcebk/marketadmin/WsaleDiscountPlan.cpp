//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WsaleDiscountPlan.h"
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
TfrmWsaleDiscount *frmWsaleDiscount;
//---------------------------------------------------------------------------
__fastcall TfrmWsaleDiscount::TfrmWsaleDiscount(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TfrmWsaleDiscount::Init(TApplication* app, TADOConnection* con,int stgid)
{
    fstgid = stgid;
	query->Connection = con;
	aq->Connection = con;
	cn = con;
	//���������ʾ
	AnsiString sql;
	//����׷��
	sql = "select ID,Name from SYS_StorageInfo";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof)
	{
		cbstgid->AddItem(aq->FieldByName("Name")->AsString,(TObject *)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	cbstgid->ItemIndex = cbstgid->Items->IndexOfObject((TObject*)stgid) ;

	sql = "select Master from SYS_StorageInfo where id = " + IntToStr(stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->FieldByName("Master")->AsBoolean ) {
		cbstgid->Enabled = true;
	}
	else
	{
    	cbstgid->Enabled = false;
	}

	sql = "select wsaletype from BS_WsaleDiscount where active = 1 and stgid = " + IntToStr(stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount == 0) {
		rbtotal->Checked = true;
		Labelname->Visible = false;
		cbtype->Visible = false;
		type = 1;
	}
	else
	{
		correntdiscount =  aq->FieldByName("wsaletype")->AsInteger;
		type = correntdiscount;
		View(correntdiscount);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWsaleDiscount::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree ;
}
//---------------------------------------------------------------------------

void TfrmWsaleDiscount::View(int tag)
{
	AnsiString sql;
	int stgid;
	try {
		stgid = (int)cbstgid->Items->Objects[cbstgid->ItemIndex];
	} catch (...) {
    	MessageBox(0,"��ѡ����ȷ�ĵ�����","��ʾ" ,MB_ICONWARNING );
		return;
	}

	switch (tag ) {
			case 1:        //ȫ��
				rbtotal->Checked = true;
				Labelname->Visible = false;
				cbtype->Visible = false;
				sql = "select * from BS_WsaletypeDiscountInfo where type = 1 and stgid = " + IntToStr(stgid);
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				eddiscount->Text = aq->FieldByName("alldot")->AsString ;
				if (correntdiscount == 1) {
					cbcorrent->Checked = true;
				}
				else
				{
					cbcorrent->Checked = false;
				}
			break;
			case 2:        //���
				rbpress->Checked = true;
				cbtype->Visible = true;
				Labelname->Visible = true;
				Labelname->Caption = "������";
				sql = "select ID,PresentNum,AbbreviatedName from BS_PressInfo";
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				cbtype->Clear();
				while (!aq->Eof)
				{
					cbtype->AddItem(aq->FieldByName("PresentNum")->AsString + aq->FieldByName("AbbreviatedName")->AsString,(TObject *)aq->FieldByName("ID")->AsInteger );
					aq->Next();
				}
				sql = "select A.*,A.pressdot as dot,BS_PressInfo.AbbreviatedName as name,SYS_StorageInfo.Name as storagename from BS_WsaletypeDiscountInfo as A left join BS_PressInfo on A.pressid = BS_PressInfo.ID left join SYS_StorageInfo on A.stgid = SYS_StorageInfo.ID where type = 2 and SYS_StorageInfo.ID = " + IntToStr(stgid) ;
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->Open();
				if (correntdiscount == 2) {
					cbcorrent->Checked = true;
				}
				else
				{
					cbcorrent->Checked = false;
				}
				eddiscount->Text = query->FieldByName("dot")->AsString ;
				cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)query->FieldByName("pressid")->AsInteger);
			break;
			case 3:        //���
				rbtype->Checked = true;
				cbtype->Visible = true;
				Labelname->Visible = true;
				Labelname->Caption = "���";
				sql = "select ID,Name from BS_BookType";
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				cbtype->Clear();
				while (!aq->Eof)
				{
					cbtype->AddItem(aq->FieldByName("Name")->AsString,(TObject *)aq->FieldByName("ID")->AsInteger );
					aq->Next();
				}
				sql = "select A.*,A.typedot as dot,BS_BookType.Name as name,SYS_StorageInfo.Name as storagename from BS_WsaletypeDiscountInfo as A left join BS_BookType on A.typeid = BS_BookType.ID left join SYS_StorageInfo on A.stgid = SYS_StorageInfo.ID where type = 3 and SYS_StorageInfo.ID = " + IntToStr(stgid) ;
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->Open();
				if (correntdiscount == 3) {
					cbcorrent->Checked = true;
				}
				else
				{
					cbcorrent->Checked = false;
				}
				eddiscount->Text = query->FieldByName("dot")->AsString ;
				cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)query->FieldByName("typeid")->AsInteger);
			break;
			case 4:        //��Ӧ��
				rbsupplier->Checked = true;
				cbtype->Visible = true;
				Labelname->Visible = true;
				Labelname->Caption = "��Ӧ��";
				sql = "select ID,Name from CUST_CustomerInfo where Type = 1 order by name";
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				cbtype->Clear();
				while (!aq->Eof)
				{
					cbtype->AddItem(aq->FieldByName("Name")->AsString,(TObject *)aq->FieldByName("ID")->AsInteger );
					aq->Next();
				}
				sql = "select A.*,A.supplierdot as dot,CUST_CustomerInfo.Name as name,SYS_StorageInfo.Name as storagename from BS_WsaletypeDiscountInfo as A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.ID left join SYS_StorageInfo on A.stgid = SYS_StorageInfo.ID where A.type = 4 and SYS_StorageInfo.ID = " + IntToStr(stgid) ;
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->Open();
				if (correntdiscount == 4) {
					cbcorrent->Checked = true;
				}
				else
				{
					cbcorrent->Checked = false;
				}
				eddiscount->Text = query->FieldByName("dot")->AsString ;
				cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)query->FieldByName("supplierid")->AsInteger);
			break;
        default:
			;
	}
}

void __fastcall TfrmWsaleDiscount::rbtotalClick(TObject *Sender)
{
	if (rbtotal->Checked ) {
		type = 1;
		View(type);
		rbpress->Checked = false;
		rbtype->Checked = false;
		rbsupplier->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWsaleDiscount::rbpressClick(TObject *Sender)
{
	if (rbpress->Checked ) {
		type = 2;
		View(type);
		rbtotal->Checked = false;
		rbtype->Checked = false;
		rbsupplier->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWsaleDiscount::rbtypeClick(TObject *Sender)
{
	if (rbtype->Checked ) {
		type = 3;
		View(type);
		rbtotal->Checked = false;
		rbpress->Checked = false;
		rbsupplier->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWsaleDiscount::rbsupplierClick(TObject *Sender)
{
	if (rbsupplier->Checked ) {
		type = 4;
		View(type);
		rbtotal->Checked = false;
		rbpress->Checked = false;
		rbtype->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWsaleDiscount::cbtypeSelect(TObject *Sender)
{
	AnsiString sql;
	int stgid = (int)cbstgid->Items->Objects[cbstgid->ItemIndex],id;
	try {
		id = (int)cbtype->Items->Objects[cbtype->ItemIndex];
	} catch (...) {
		switch (type) {
			case 2:
				MessageBox(0,"��ѡ����ȷ���","��ʾ" ,MB_ICONWARNING );
			break;
			case 3:
				MessageBox(0,"��ѡ����ȷ���","��ʾ" ,MB_ICONWARNING );
			break;
			case 4:
				MessageBox(0,"��ѡ����ȷ��Ӧ�̣�","��ʾ" ,MB_ICONWARNING );
			break;
        default:
			;
		}
	}
	switch (type) {
		case 2:
			sql = "select * from BS_WsaletypeDiscountInfo where type = 2 and pressid = " + IntToStr(id) + " and stgid = " + IntToStr(stgid);
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				eddiscount->Text = aq->FieldByName("pressdot")->AsString ;
			}
			else
			{
				eddiscount->Text = "";
			}
		break;
		case 3:
			sql = "select * from BS_WsaletypeDiscountInfo where type = 3 and typeid = " + IntToStr(id) + " and stgid = " + IntToStr(stgid);
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				eddiscount->Text = aq->FieldByName("typedot")->AsString ;
			}
			else
			{
				eddiscount->Text = "";
			}
		break;
		case 4:
			sql = "select * from BS_WsaletypeDiscountInfo where type = 4 and supplierid = " + IntToStr(id) + " and stgid = " + IntToStr(stgid);
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				eddiscount->Text = aq->FieldByName("supplierdot")->AsString ;
			}
			else
			{
				eddiscount->Text = "";
			}
		break;
    default:
        ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWsaleDiscount::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmWsaleDiscount::cbcorrentClick(TObject *Sender)
{
	int stgid = (int)cbstgid->Items->Objects[cbstgid->ItemIndex];
	AnsiString sql;
	if (cbcorrent->Checked ) {
		switch (type) {
			case 1:
				sql = "select * from BS_WsaleDiscount where wsaletype = " + IntToStr(type) + " and stgid = " + IntToStr(stgid);
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				if (aq->RecordCount == 0) {
					sql = "insert into BS_WsaleDiscount(stgid,wsaletype,typename,active) values (" + IntToStr(stgid) + ",1,'ȫ��',0)";
					aq->Close();
					aq->SQL->Clear();
					aq->SQL->Add(sql);
					aq->ExecSQL();
				}
				correntdiscount = 1;
			break;
			case 2:
            	sql = "select * from BS_WsaleDiscount where wsaletype = " + IntToStr(type) + " and stgid = " + IntToStr(stgid);
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				if (aq->RecordCount == 0) {
					sql = "insert into BS_WsaleDiscount(stgid,wsaletype,typename,active) values (" + IntToStr(stgid) + ",2,'���',0)";
					aq->Close();
					aq->SQL->Clear();
					aq->SQL->Add(sql);
					aq->ExecSQL();
				}
				correntdiscount = 2;
			break;
			case 3:
				sql = "select * from BS_WsaleDiscount where wsaletype = " + IntToStr(type) + " and stgid = " + IntToStr(stgid);
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				if (aq->RecordCount == 0) {
					sql = "insert into BS_WsaleDiscount(stgid,wsaletype,typename,active) values (" + IntToStr(stgid) + ",3,'���',0)";
					aq->Close();
					aq->SQL->Clear();
					aq->SQL->Add(sql);
					aq->ExecSQL();
				}
				correntdiscount = 3;
			break;
			case 4:
				sql = "select * from BS_WsaleDiscount where wsaletype = " + IntToStr(type) + " and stgid = " + IntToStr(stgid);
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				if (aq->RecordCount == 0) {
					sql = "insert into BS_WsaleDiscount(stgid,wsaletype,typename,active) values (" + IntToStr(stgid) + ",4,'��Ӧ��',0)";
					aq->Close();
					aq->SQL->Clear();
					aq->SQL->Add(sql);
					aq->ExecSQL();
				}
            	correntdiscount = 4;
			break;
		default:
			;
		}
		sql = "update BS_WsaleDiscount set active = 0 where stgid = " + IntToStr(stgid);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		sql = "update BS_WsaleDiscount set active = 1 where stgid = " + IntToStr(stgid) + " and wsaletype = " + IntToStr(type) ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWsaleDiscount::eddiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWsaleDiscount::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmWsaleDiscount::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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
	if ( Key == VK_F4) {   //����
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWsaleDiscount::cbstgidSelect(TObject *Sender)
{
	AnsiString sql;
	try {
		fstgid =  (int)cbstgid->Items->Objects[cbstgid->ItemIndex];
	} catch (...) {
		MessageBox(0,"��ѡ����ȷ�ĵ�����","����" ,MB_OK);
		return;
	}
	sql = "select wsaletype from BS_WsaleDiscount where active = 1 and stgid = " + IntToStr(fstgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount == 0) {
		rbtotal->Checked = true;
		Labelname->Visible = false;
		cbtype->Visible = false;
		type = 1;
	}
	else
	{
		correntdiscount =  aq->FieldByName("wsaletype")->AsInteger;
		type = correntdiscount;
		View(correntdiscount);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmWsaleDiscount::BtnSaveClick(TObject *Sender)
{
	AnsiString sql;
	if (cbtype->Text == "" && type != 1) {
		MessageBox(0,"��ѡ����۵����ͣ�","��ʾ" ,MB_ICONWARNING );
		return;
	}
	if (eddiscount->Text == "") {
		MessageBox(0,"�ۿ۲���Ϊ�գ�","��ʾ" ,MB_ICONWARNING );
		return;
	}
	float discount;
	try {
		discount =  StrToInt(eddiscount->Text);
	} catch (...) {
		MessageBox(0,"��������ȷ�ĸ����ۿۣ�","��ʾ" ,MB_ICONWARNING );
		return;
	}


	if (discount < 0) {
		MessageBox(0,"�����ۿ۲���С��0��","��ʾ" ,MB_ICONWARNING );
		return;
	}
	if (discount > 100) {
		MessageBox(0,"�����ۿ۲��ܴ���100��","��ʾ" ,MB_ICONWARNING );
		return;
	}
	int stgid;
	try {
		stgid = (int)cbstgid->Items->Objects[cbstgid->ItemIndex];
	} catch (...) {
    	MessageBox(0,"��ѡ����ȷ�ĵ�����","��ʾ" ,MB_ICONWARNING );
		return;
	}
	int id = 0;
	if (type != 1) {
		try {
			id = (int)cbtype->Items->Objects[cbtype->ItemIndex];
		} catch (...) {
			switch (type) {
				case 2:
					MessageBox(0,"��ѡ����ȷ���","��ʾ" ,MB_ICONWARNING );
				break;
				case 3:
					MessageBox(0,"��ѡ����ȷ���","��ʾ" ,MB_ICONWARNING );
				break;
				case 4:
					MessageBox(0,"��ѡ����ȷ��Ӧ�̣�","��ʾ" ,MB_ICONWARNING );
				break;
			default:
				;
			}
		}
	}

	switch (type) {
		case 1:
			sql = "select * from BS_WsaletypeDiscountInfo where type = 1 and stgid = " + IntToStr(stgid);
			aq->Close();
            aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				sql = "update BS_WsaletypeDiscountInfo set alldot = " + FloatToStr(discount) + " where id = " + aq->FieldByName("ID")->AsString ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
			}
			else
			{
				sql = "insert into BS_WsaletypeDiscountInfo(type,stgid,alldot) values(1," + IntToStr(stgid) + "," + FloatToStr(discount) + ")";
                aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
			}
			break;
		case 2:
			if (cbtype->Text == "") {
				MessageBox(0,"��ѡ���� ","��ʾ" ,MB_ICONWARNING );
				return;
			}
			sql = "select * from BS_WsaletypeDiscountInfo where type = 2 and pressid = " + IntToStr(id) + " and stgid = " + IntToStr(stgid);
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				sql = "update BS_WsaletypeDiscountInfo set pressdot = " + FloatToStr(discount) + " where id = " + aq->FieldByName("ID")->AsString ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
				query->Active = false;
				query->Active = true;
			}
			else
			{
				if (query->State != dsInsert) {
					query->Append();
				}
				query->FieldByName("type")->AsInteger = 2;
				query->FieldByName("stgid")->AsInteger = stgid;
				query->FieldByName("pressid")->AsInteger = id;
				query->FieldByName("pressdot")->AsFloat = discount;
				query->UpdateBatch(arAll);
				query->Active = false;
				query->Active = true;
			}
		break;
		case 3:
			if (cbtype->Text == "") {
				MessageBox(0,"��ѡ�����","��ʾ" ,MB_ICONWARNING );
				return;
			}
			sql = "select * from BS_WsaletypeDiscountInfo where type = 3 and typeid = " + IntToStr(id) + " and stgid = " + IntToStr(stgid);
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				sql = "update BS_WsaletypeDiscountInfo set typedot = " + FloatToStr(discount) + " where id = " + aq->FieldByName("ID")->AsString ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
				query->Active = false;
				query->Active = true;
			}
			else
			{
				if (query->State != dsInsert) {
					query->Append();
				}
				query->FieldByName("type")->AsInteger = 3;
				query->FieldByName("stgid")->AsInteger = stgid;
				query->FieldByName("typeid")->AsInteger = id;
				query->FieldByName("typedot")->AsFloat = discount;
				query->UpdateBatch(arAll);
				query->Active = false;
				query->Active = true;
			}
		break;
		case 4:
			if (cbtype->Text == "") {
				MessageBox(0,"��ѡ��Ӧ�̣�  ","��ʾ" ,MB_ICONWARNING );
				return;
			}
			sql = "select * from BS_WsaletypeDiscountInfo where type = 4 and supplierid = " + IntToStr(id) + " and stgid = " + IntToStr(stgid);
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				sql = "update BS_WsaletypeDiscountInfo set supplierdot = " + FloatToStr(discount) + " where id = " + aq->FieldByName("ID")->AsString ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
				query->Active = false;
				query->Active = true;
			}
			else
			{
				if (query->State != dsInsert) {
					query->Append();
				}
				query->FieldByName("type")->AsInteger = 4;
				query->FieldByName("stgid")->AsInteger = stgid;
				query->FieldByName("supplierid")->AsInteger = id;
				query->FieldByName("supplierdot")->AsFloat = discount;
				query->UpdateBatch(arAll);
				query->Active = false;
				query->Active = true;
			}
		break;
    default:
        ;
	}
}
//---------------------------------------------------------------------------

