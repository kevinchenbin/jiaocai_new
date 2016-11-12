//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Membertypeadddot.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmmemberadddot *frmmemberadddot;
//---------------------------------------------------------------------------
__fastcall Tfrmmemberadddot::Tfrmmemberadddot(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
	fcon = con;
	fstgid = stgid;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq1->Connection = fcon;
	aq2->Connection = fcon;
	AnsiString sql;
	sql = "select IDType,Type from CUST_MemberType where IDType > 0";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while(!aq->Eof )
	{
		cbmembertype->AddItem(aq->FieldByName("Type")->AsString ,(TObject*)aq->FieldByName("IDType")->AsInteger );
		aq->Next();
	}
	aq->First();
	cbmembertype->ItemIndex = cbmembertype->Items->IndexOfObject((TObject*)aq->FieldByName("IDType")->AsInteger);
	delete aq;
	sql = "select BS_Membertypedot.*,CUST_MemberType.Type as name,case BS_Membertypedot.active when 1 then '√' else '无效' end as active1 from BS_Membertypedot left join "
			" CUST_MemberType on BS_Membertypedot.membertype = CUST_MemberType.IDType where BS_Membertypedot.type = 0 and BS_Membertypedot.stgid = " + IntToStr(fstgid) ;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	sql = "select BS_Membertypedot.*,convert(nvarchar(10),BS_Membertypedot.mindiscount) + '% - ' + convert(nvarchar(10),BS_Membertypedot.maxdiscount) + '%' as fanwei, CUST_MemberType.Type as name,case BS_Membertypedot.active when 1 then '√' else '无效' end as active1 from BS_Membertypedot left join "
			" CUST_MemberType on BS_Membertypedot.membertype = CUST_MemberType.IDType where BS_Membertypedot.type = 1 and BS_Membertypedot.stgid = " + IntToStr(fstgid) + " order by name";
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmmemberadddot::eddot1KeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r')&& (Key != '-')) {
		Key = NULL;
	}
	if (Key == '\r') {
    	BtnSave->Click();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmmemberadddot::BtnSaveClick(TObject *Sender)
{
	if (MessageBox(0,"确认会员类型调整点设置？","确认" ,MB_OKCANCEL)!=1) {
		return;
	}
	float dot;
	int type;
	AnsiString sql;
	float mindiscount,maxdiscount;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	TADOQuery *query = new TADOQuery(this);
	query->Connection = fcon;
	try {
		type = (int)cbmembertype->Items->Objects[cbmembertype->ItemIndex];
	} catch (...) {
		MessageBox(0,"请输入正确的会员类型！","提示" ,MB_OK);
		return;
	}
	if (rg->ItemIndex == 0) {
    	try {
			dot = StrToFloat(eddot->Text);
		} catch (...) {
			MessageBox(0,"请输入正确的加点折扣！","提示" ,MB_OK);
			return;
		}


		sql = "select * from BS_Membertypedot where membertype = " + IntToStr(type) + " and stgid = " + IntToStr(fstgid) + " and type = 0";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount == 0) {
			sql = "insert into BS_Membertypedot(membertype,dot,stgid,type) values(" + IntToStr(type) + "," + eddot->Text + "," + IntToStr(fstgid) + ",0)" ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
		else
		{
			sql = "update BS_Membertypedot set dot = " + eddot->Text + " where id = " + aq->FieldByName("id")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
		}
		aq1->Active = false;
		aq1->Active = true;
	}
	else
	{
    	try {
			dot = StrToFloat(eddot1->Text);
		} catch (...) {
			MessageBox(0,"请输入正确的加点折扣！","提示" ,MB_OK);
			return;
		}
		try {
			mindiscount = StrToFloat(edminedit->Text);
			maxdiscount = StrToFloat(edmaxdiscount->Text);
		} catch (...) {
			MessageBox(0,"请输入正确的预计折扣范围！","提示" ,MB_OK);
			return;
		}
		if (mindiscount < 0 && maxdiscount > 100) {
        	MessageBox(0,"折扣范围超出界限！","提示" ,MB_OK);
			return;
		}
		sql = "select * from BS_Membertypedot where membertype = " + IntToStr(type) + " and stgid = " + IntToStr(fstgid) + " and ((mindiscount <= " + FloatToStr(mindiscount) + " and maxdiscount >= " + FloatToStr(mindiscount) + ") or (mindiscount <= " + FloatToStr(maxdiscount) + " and maxdiscount >= " + FloatToStr(maxdiscount) + ")) and type = 1";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		float ymindiscount,ymaxdiscount,ydot;

		while (!query->Eof ) {
			sql = "select id,mindiscount,maxdiscount,dot from BS_Membertypedot where id = " + query->FieldByName("id")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			ymindiscount = aq->FieldByName("mindiscount")->AsFloat ;
			ymaxdiscount = aq->FieldByName("maxdiscount")->AsFloat ;
			ydot = aq->FieldByName("dot")->AsFloat ;
			sql = "delete from  BS_Membertypedot where id = " + aq->FieldByName("id")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			if (ymindiscount < mindiscount) {
				sql = "insert into BS_Membertypedot(membertype,dot,stgid,type,mindiscount,maxdiscount) values(" + IntToStr(type) + "," + FloatToStr(ydot)  + "," + IntToStr(fstgid) + ",1," + FloatToStr(ymindiscount) + "," + FloatToStr(mindiscount) + ")" ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
			}
			if (ymaxdiscount > maxdiscount) {
				sql = "insert into BS_Membertypedot(membertype,dot,stgid,type,mindiscount,maxdiscount) values(" + IntToStr(type) + "," + FloatToStr(ydot)  + "," + IntToStr(fstgid) + ",1," + FloatToStr(maxdiscount) + "," + FloatToStr(ymaxdiscount) + ")" ;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
			}
			query->Next();
		}
		sql = "delete from BS_Membertypedot where mindiscount > " + FloatToStr(mindiscount) + " and maxdiscount < " + FloatToStr(maxdiscount) ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();

		sql = "insert into BS_Membertypedot(membertype,dot,stgid,type,mindiscount,maxdiscount) values(" + IntToStr(type) + "," + eddot1->Text + "," + IntToStr(fstgid) + ",1," + FloatToStr(mindiscount) + "," + FloatToStr(maxdiscount) + ")" ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();

		aq2->Active = false;
		aq2->Active = true;
	}
	delete aq;
	delete query;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmmemberadddot::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmmemberadddot::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmmemberadddot::edmineditKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r')&& (Key != '-')) {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberadddot::edmaxdiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r')&& (Key != '-')) {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberadddot::rgClick(TObject *Sender)
{
	if (rg->ItemIndex == 0) {
		gb1->Visible = true;
		gb2->Visible = false;
		dg1->Visible = true;
		dg2->Visible = false;
	}
	else
	{
		gb1->Visible = false;
		gb2->Visible = true;
		dg1->Visible = false;
		dg2->Visible = true;
	}
	int type;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	try {
		type = (int)cbmembertype->Items->Objects[cbmembertype->ItemIndex];
	} catch (...) {
		return;
	}
	AnsiString sql;
	sql = "select active from BS_Membertypedot where type = " + IntToStr(rg->ItemIndex) + " and membertype = " + IntToStr(type) + " and stgid = " + IntToStr(fstgid);
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	chactive->Checked = aq->FieldByName("active")->AsBoolean ;
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberadddot::chactiveClick(TObject *Sender)
{
	int type;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	try {
		type = (int)cbmembertype->Items->Objects[cbmembertype->ItemIndex];
	} catch (...) {
		MessageBox(0,"请输入正确的会员类型！","提示" ,MB_OK);
		return;
	}
	AnsiString sql;
	if (chactive->Checked ) {
		sql = "update BS_Membertypedot set active = 1 where type = " + IntToStr(rg->ItemIndex) + " and membertype = " + IntToStr(type) + " and stgid = " + IntToStr(fstgid);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		sql = "update BS_Membertypedot set active = 0 where type <> " + IntToStr(rg->ItemIndex) + " and membertype = " + IntToStr(type) + " and stgid = " + IntToStr(fstgid);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
	}
	delete aq;
	aq1->Active = false;
	aq1->Active = true;
	aq2->Active = false;
	aq2->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberadddot::cbmembertypeClick(TObject *Sender)
{
	int type;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	try {
		type = (int)cbmembertype->Items->Objects[cbmembertype->ItemIndex];
	} catch (...) {
		MessageBox(0,"请输入正确的会员类型！","提示" ,MB_OK);
		return;
	}
	AnsiString sql;
	sql = "select * from  BS_Membertypedot where type = " + IntToStr(rg->ItemIndex) + " and membertype = " + IntToStr(type) + " and stgid = " + IntToStr(fstgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	eddot->Text = aq->FieldByName("dot")->AsString ;
	eddot1->Text = aq->FieldByName("dot")->AsString ;
	edname1->Text = cbmembertype->Text ;
	edname->Text = cbmembertype->Text ;
	edminedit->Text = aq->FieldByName("mindiscount")->AsAnsiString ;
	edmaxdiscount->Text = aq->FieldByName("maxdiscount")->AsAnsiString ;
	chactive->Checked = aq->FieldByName("active")->AsBoolean ;
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberadddot::dg2CellClick(TColumn *Column)
{
	if (aq2->IsEmpty() ) {
		return;
	}
	edname1->Text = aq2->FieldByName("name")->AsAnsiString ;
	edminedit->Text = aq2->FieldByName("mindiscount")->AsAnsiString ;
	edmaxdiscount->Text = aq2->FieldByName("maxdiscount")->AsAnsiString ;
	eddot1->Text = aq2->FieldByName("dot")->AsAnsiString ;
	cbmembertype->ItemIndex = cbmembertype->Items->IndexOfObject((TObject*)aq2->FieldByName("membertype")->AsInteger );
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemberadddot::dg1CellClick(TColumn *Column)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	edname->Text = aq1->FieldByName("name")->AsAnsiString ;
	eddot->Text = aq1->FieldByName("dot")->AsAnsiString ;
	cbmembertype->ItemIndex = cbmembertype->Items->IndexOfObject((TObject*)aq1->FieldByName("membertype")->AsInteger );
}
//---------------------------------------------------------------------------

