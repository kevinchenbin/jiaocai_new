//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unithuancard.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
Tfrmhuancard *frmhuancard;
//---------------------------------------------------------------------------
__fastcall Tfrmhuancard::Tfrmhuancard(TComponent* Owner,TADOConnection *con,int cardid)
	: TForm(Owner)
{
	password = 0;
	fcon = con;
	AnsiString sql;
	ycardid = cardid;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = con;

	sql = "select IDType,Type from CUST_MemberType";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbtype->AddItem(aq->FieldByName("Type")->AsString ,(TObject*)aq->FieldByName("IDType")->AsInteger );
		aq->Next();
	}
	sql = "select CUST_MemberInfo.*,case sex when 0 then '男' else '女' end as sex1,CUST_MemberType.Type,CUST_MemberType.Discount "
			" from CUST_MemberInfo left join CUST_MemberType on CUST_MemberInfo.MemberType = CUST_MemberType.IDType where CUST_MemberInfo.id = " + IntToStr(cardid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edcard->Text = aq->FieldByName("CardID")->AsAnsiString.Trim();
	edname->Text = aq->FieldByName("Name")->AsAnsiString.Trim();
	edsex->Text = aq->FieldByName("sex1")->AsAnsiString.Trim();
	edtype->Text = aq->FieldByName("Type")->AsAnsiString.Trim();
	eddiscount->Text = FormatFloat("0.00%",aq->FieldByName("Discount")->AsFloat);
	edconsumption->Text = FormatFloat("###,###,##0.00",aq->FieldByName("TotalConsumption")->AsFloat);
	edjifen->Text = IntToStr(aq->FieldByName("Memberdot")->AsInteger);
	edyue->Text = FormatFloat("###,###,##0.00",aq->FieldByName("Balance")->AsFloat);
	Pwd = aq->FieldByName("PassWord")->AsAnsiString.Trim();
	if (aq->FieldByName("PassWord")->AsAnsiString != "" ) {
		//edpassword->SetFocus();
		password = 1;
		Label8->Visible = true;
		edpassword->Visible = true;
		//PageControl1->Enabled = false;
	}
	edtname->Text = aq->FieldByName("Name")->AsAnsiString.Trim();
	cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)aq->FieldByName("MemberType")->AsInteger);
	cbsex->ItemIndex =  aq->FieldByName("sex")->AsInteger ;
	edtdiscount->Text = FormatFloat("0.00%",aq->FieldByName("Discount")->AsFloat);
	edCardCast->Text =  FormatFloat("0.00",aq->FieldByName("CardCast")->AsFloat);
	tdtbirthday->Date =  aq->FieldByName("Birthday")->AsDateTime ;
	edttelephone->Text =  aq->FieldByName("Tel")->AsAnsiString.Trim();
	edtmobile->Text =  aq->FieldByName("Mobile")->AsAnsiString.Trim();
	edtaddress->Text =  aq->FieldByName("Address")->AsAnsiString.Trim();
	edtpostalcode->Text = aq->FieldByName("PostalCode")->AsAnsiString.Trim();
	edbircard->Text = aq->FieldByName("bircard")->AsAnsiString.Trim();
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmhuancard::edtcardIDKeyPress(TObject *Sender, wchar_t &Key)
{
	if (password == 1) {
		MessageBox(0,"请输入原卡号的验证码！","提示" ,MB_ICONWARNING);
		return;
	}
	if (Key == '\r') {
		edtpwd->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmhuancard::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmhuancard::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key ==81  ) {
		BtnExit->Click();
	}
	if (Key == VK_F8) {
		BtnSendtoBack->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmhuancard::BtnSendtoBackClick(TObject *Sender)
{
	if (password == 1) {
		MessageBox(0,"请输入原卡号的验证码！","提示" ,MB_ICONWARNING);
		return;
	}
	if (edtcardID->Text == "") {
		MessageBox(0,"请输入新会员卡的卡号！","提示" ,MB_ICONWARNING);
		return;
	}
	if (edtcardID->Text.Length() != 13 ) {
		MessageBox(0,"请输入13位的会员卡号！","提示" ,MB_ICONWARNING);
		return;
	}
	if(MessageBox(0,"确认换卡！","确认" ,MB_ICONQUESTION|MB_OKCANCEL)!=1)
	{
		return;
	}
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	sql = "select * from CUST_MemberInfo where CardID = " + edtcardID->Text ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount > 0) {
		MessageBox(0,"该会员卡号已存在，请重新输入会员卡卡号！","提示" ,MB_ICONWARNING);
		return;
	}
	if (edCardCast->Text == "") {
        edCardCast->Text == "0";
	}
	sql = "insert into CUST_MemberInfo(Name,Birthday,Sex,Tel,Mobile,Address,PostalCode,CardID,Balance,TotalConsumption,MemberType,CardSN,Memberdot,CardType,PassWord,CardCast,bk,bircard) values ('" +
			edtname->Text + "','" + DateToStr(tdtbirthday->Date) + "'," + IntToStr(cbsex->ItemIndex) + ",'" + edttelephone->Text + "','" + edtmobile->Text + "','" + edtaddress->Text + "','" + edtpostalcode->Text + "','" +
			edtcardID->Text + "'," + edyue->Text + "," + edconsumption->Text + "," + IntToStr((int)cbtype->Items->Objects[cbtype->ItemIndex]) + ",'" + edtcardID->Text + "'," +
			edjifen->Text + "," + IntToStr(rg->ItemIndex) + ",'" + edtpwd->Text + "'," + edCardCast->Text + ",'补新卡，旧卡卡号" + edcard->Text + "','" + edbircard->Text + "')";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	try {
		aq->ExecSQL();
	} catch (...) {
        MessageBox(0,"添加新会员失败，请检查输入信息是否正确！","提示" ,MB_ICONWARNING);
		return;
	}
	sql = "select max(id) as id from CUST_MemberInfo ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	newcardid = aq->FieldByName("id")->AsInteger ;
	sql = "update BS_RetailNoteHeader set MemberID = " + IntToStr(newcardid) + " where MemberID = " + IntToStr(ycardid) ;
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = "update CUST_MemberToprecord set MIid = " + IntToStr(newcardid) + ",CardID = '" + edtcardID->Text + "' where MIid = " + IntToStr(ycardid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = "update CUST_MemberInfo set Available = 0,bk = '换新卡，新卡卡号" + edtcardID->Text + "' where id = " + IntToStr(ycardid) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();

	delete aq;

	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmhuancard::edtpwdKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		edCardCast->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmhuancard::edpasswordKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edpassword->Text == Pwd) {
			Pwd = 0;
			edtcardID->SetFocus();
		}
		else
		{
			MessageBox(0,"原卡验证码输入错误！","提示" ,MB_ICONWARNING);
			return;
		}
	}
}
//---------------------------------------------------------------------------
