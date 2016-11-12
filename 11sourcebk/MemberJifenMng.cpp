//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberJifenMng.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmMemberjifen *frmMemberjifen;
//---------------------------------------------------------------------------
__fastcall TfrmMemberjifen::TfrmMemberjifen(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	aq->Connection = con;
	query->Connection = con;
	query1->Connection = con;
	aq1->Connection = con;
	fcon = con;
	currentmax = 0;
	String sql ;
	sql = "select IDType,Type from CUST_MemberType";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbmembertype->AddItem(aq->FieldByName("IDType")->AsString + aq->FieldByName("Type")->AsString,(TObject*)aq->FieldByName("IDType")->AsInteger );
		aq->Next();
	}
	sql = "select Money,jifen from SYS_Member_Jifen where stgid = " + IntToStr(stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edmoney->Text = aq->FieldByName("Money")->AsString ;
	eddot->Text = aq->FieldByName("jifen")->AsString ;
	sql = "select jifenmin,Membertype from SYS_Member_jifen_type where stgid = " + IntToStr(stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	eddotset->Text = aq->FieldByName("jifenmin")->AsString ;
	cbmembertype->ItemIndex = cbmembertype->Items->IndexOfObject((TObject*)aq->FieldByName("Membertype")->AsInteger );
	sql = "select SYS_Member_jifen_type.*,CUST_MemberType.Type from SYS_Member_jifen_type left join CUST_MemberType on SYS_Member_jifen_type.Membertype = CUST_MemberType.IDType  where SYS_Member_jifen_type.Membertype >= 0 order by jifenmin";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	sql = "select jifenmin,jifenmax from SYS_Member_jifen_type where Membertype = -1 order by jifenmin";
	query1->Close();
	query1->SQL->Clear();
	query1->SQL->Add(sql);
	query1->Open();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemberjifen::btsaveClick(TObject *Sender)
{
	if (eddotset->Text == "") {
		eddotset->Text = "1";
	}
	int membertype = (int)cbmembertype->Items->Objects[cbmembertype->ItemIndex];
	if (membertype == 0) {
		MessageBoxA(0,"默认会员不需升级!","提示",MB_ICONASTERISK);
		return;
	}
	AnsiString sql;
	sql = "select * from SYS_Member_jifen_type where Membertype = " + IntToStr(membertype) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount > 0) {
    	currentmax = aq->FieldByName("jifenmax")->AsInteger ;
		sql = "update SYS_Member_jifen_type set jifenmin = " + eddotset->Text + " where Membertype = " + IntToStr(membertype) ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		MaxMin();
	}
	else
	{
		sql  = "insert into SYS_Member_jifen_type(jifenmin,Membertype,stgid) values(" + eddotset->Text + "," + IntToStr(membertype) + "," + IntToStr(stgid) + ")";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		MaxMin();
	}
	query->Active = false;
	query->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemberjifen::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberjifen::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemberjifen::DBGrid1CellClick(TColumn *Column)
{
	if (query->RecordCount > 0) {
		eddotset->Text = query->FieldByName("jifenmin")->AsString;
		cbmembertype->ItemIndex = cbmembertype->Items->IndexOfObject((TObject*)query->FieldByName("Membertype")->AsInteger );
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemberjifen::N1Click(TObject *Sender)
{
	String sql ;
	if (query->FieldByName("Membertype")->AsInteger == 0 ) {
        MessageBoxA(0,"默认会员不能删除!","警告",MB_ICONASTERISK);
		return;
	}
	if (query->RecordCount > 1) {
		sql = "select * from SYS_Member_jifen_type where jifenmin < "  + query->FieldByName("jifenmin")->AsString + " order by jifenmin";
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->Open();
		aq1->Last();
		sql = "update SYS_Member_jifen_type set jifenmax = " + query->FieldByName("jifenmax")->AsString + " where id = " + aq1->FieldByName("id")->AsString ;
        aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->ExecSQL();
		sql = "delete from SYS_Member_jifen_type where id = " + query->FieldByName("id")->AsString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		query->Active = false;
		query->Active = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberjifen::MaxMin()
{
	String sql ;
	sql = "select * from SYS_Member_jifen_type where jifenmin < " + eddotset->Text + " order by jifenmin";
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	if (aq1->RecordCount > 0) {
		aq1->Last();
		sql = "update SYS_Member_jifen_type set jifenmax = " + eddotset->Text + "where id = " + aq1->FieldByName("id")->AsString ;
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->ExecSQL();
	}
	sql =  "select * from SYS_Member_jifen_type where jifenmin > " + eddotset->Text + " order by jifenmin";
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	if (aq1->RecordCount > 0) {
		aq1->First();
		int id = aq1->FieldByName("id")->AsInteger ;
		int min = aq1->FieldByName("jifenmin")->AsInteger;
		sql = "update SYS_Member_jifen_type set jifenmax = " + aq1->FieldByName("jifenmin")->AsString + " where jifenmin = " + eddotset->Text;
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->ExecSQL();
		sql = "update SYS_Member_jifen_type set jifenmin = " + IntToStr(min) + "where id = " + IntToStr(id) ;
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->ExecSQL();
		sql = "select * from SYS_Member_jifen_type where jifenmin > " + IntToStr(min) + " order by jifenmin";
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->Open();
		if (aq1->RecordCount > 0) {
        	sql = "update SYS_Member_jifen_type set jifenmax = " + aq1->FieldByName("jifenmin")->AsString + " where jifenmin = " + IntToStr(min);
			aq1->Close();
			aq1->SQL->Clear();
			aq1->SQL->Add(sql);
			aq1->ExecSQL();
		}
		sql = "select * from SYS_Member_jifen_type where jifenmin < " + IntToStr(currentmax) + " order by jifenmin";
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->Open();
		if (aq1->RecordCount > 0) {
			aq1->Last();
			sql = "update SYS_Member_jifen_type set jifenmax = " + IntToStr(currentmax) + " where id = " + aq1->FieldByName("id")->AsString ;
			aq1->Close();
			aq1->SQL->Clear();
			aq1->SQL->Add(sql);
			aq1->ExecSQL();
		}
	}
	else
	{
		sql = "update SYS_Member_jifen_type set jifenmax = 999999999 where jifenmin = " +eddotset->Text;
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->ExecSQL();
	}
	sql = "select max(jifenmin) as jifenmin from SYS_Member_jifen_type";
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	int jifenmin =  aq1->FieldByName("jifenmin")->AsInteger ;
	sql = "select jifenmax from SYS_Member_jifen_type where jifenmin = " + aq1->FieldByName("jifenmin")->AsString ;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	if (aq1->FieldByName("jifenmax")->AsInteger != 999999999 ) {
		sql = "update SYS_Member_jifen_type set jifenmax = 999999999 where jifenmin = " + IntToStr(jifenmin) ;
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add(sql);
		aq1->ExecSQL();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMemberjifen::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberjifen::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmMemberjifen::Button2Click(TObject *Sender)
{
	float money;
	try {
		money = StrToFloat(edmoney->Text);
	} catch (...) {
		MessageBoxA(0,"请输入正确的金额!","警告",MB_ICONASTERISK);
	}
	if (eddot->Text == "") {
		eddot->Text = "1";
	}
	int dot = StrToInt(eddot->Text);
	String sql = "select * from SYS_Member_Jifen ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount > 0) {
		sql = "update SYS_Member_Jifen set Money = " + edmoney->Text + ",jifen = " + eddot->Text + " where stgid = " + IntToStr(stgid);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
	}
	else
	{
		sql = "insert into SYS_Member_Jifen(Money,jifen,stgid) values(" + edmoney->Text + "," +  eddot->Text + "," + IntToStr(stgid) + ")";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberjifen::Button1Click(TObject *Sender)
{
	if (edjifen->Text == "") {
		return;
	}
	if (edyouhui->Text == "") {
        return;
	}
	AnsiString sql;
	sql = "select * from SYS_Member_jifen_type where jifenmax = " + edjifen->Text + " and Membertype = -1" ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount > 0) {
		sql = "update SYS_Member_jifen_type set jifenmin = " + edyouhui->Text + " where Membertype = -1 and jifenmax = " + edjifen->Text;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
	}
	else
	{
		sql  = "insert into SYS_Member_jifen_type(jifenmin,jifenmax,Membertype) values(" + edyouhui->Text + "," + edjifen->Text + "," + -1 + ")";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
	}
	query1->Active = false;
	query1->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberjifen::DBGrid2CellClick(TColumn *Column)
{
	if (query1->IsEmpty() ) {
		return;
	}
	edjifen->Text = query1->FieldByName("jifenmax")->AsAnsiString ;
	edyouhui->Text = query1->FieldByName("jifenmin")->AsAnsiString ;
}
//---------------------------------------------------------------------------

