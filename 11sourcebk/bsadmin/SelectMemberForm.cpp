//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelectMemberForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ModalDialog"
#pragma link "RzButton"
#pragma link "RzLabel"
#pragma link "RzEdit"
#pragma link "RzLine"
#pragma link "RzDBEdit"
#pragma resource "*.dfm"
TfrmSelectMember *frmSelectMember;
//---------------------------------------------------------------------------
__fastcall TfrmSelectMember::TfrmSelectMember(TComponent* Owner)
	: TfrmModalDialog(Owner)
	, m_memberID(-1)
{
	enterflag = 0;
}
//---------------------------------------------------------------------------
void TfrmSelectMember::Init(LandInfo* li)
{
	TfrmModalDialog::Init(li);
	m_memberID = 0;
	dsetMember->Connection = m_con;
	aq->Connection = m_con;
}

int TfrmSelectMember::GetMemberID()
{
	return m_memberID;
}

void __fastcall TfrmSelectMember::edtMemberKeyPress(TObject *Sender, wchar_t &Key)
{
	//
	if (Key == '\r')
	{
		if (edtMember->Text == "") {
			if (lbl1->Caption == "会员卡号") {
				lbl1->Caption = "身份证号";
			}
			else
			{
				lbl1->Caption = "会员卡号";
			}
			return;
		}
		if (lbl1->Caption == "会员卡号"){
			String sql = "select PassWord,Available from CUST_MemberInfo where CardID = '" + edtMember->Text .Trim() + "'";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->IsEmpty() ) {
				MessageBox(0,"无此会员，请核实！","提示" ,MB_OK);
				return;
			}
			if (!aq->FieldByName("Available")->AsBoolean ) {
				MessageBox(0,"该会员卡已退卡，不能再继续使用！","提示" ,MB_OK);
				return;
			}
			if (aq->FieldByName("PassWord")->AsString == "" ) {
				Label1->Visible = false;
				edpassword->Visible = false;
				if (enterflag == 0) {
					enterflag = 1;
					dsetMember->Active = false;
					dsetMember->CommandText = "select ID,Name,CardSN,Balance,Discount"
						" from CUST_MemberInfo left join CUST_MemberType"
						" on CUST_MemberInfo.MemberType=CUST_MemberType.IDType"
						" where CardID='" + edtMember->Text + "'";
					dsetMember->Active = true;
					if (dsetMember->RecordCount >= 1)
					{
						m_memberID = dsetMember->FieldByName("ID")->AsInteger;
						Key = 0;
						Perform(WM_NEXTDLGCTL, 0, 0);
					}
					else
						m_memberID = 0;
				}
				else
				{
					btnOk->Click();
				}
			}
			else
			{
				Label1->Visible = true;
				edpassword->Visible = true;
				edpassword->SetFocus();
			}
		}
		else
		{
			String sql = "select Available from CUST_MemberInfo where bircard = '" + edtMember->Text .Trim() + "'";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->IsEmpty() ) {
				MessageBox(0,"无此会员，请核实！","提示" ,MB_OK);
				return;
			}
			if (!aq->FieldByName("Available")->AsBoolean ) {
				MessageBox(0,"该会员卡已退卡，不能再继续使用！","提示" ,MB_OK);
				return;
			}
			if (enterflag == 0) {
				enterflag = 1;
				dsetMember->Active = false;
				dsetMember->CommandText = "select ID,Name,CardSN,Balance,Discount"
					" from CUST_MemberInfo left join CUST_MemberType"
					" on CUST_MemberInfo.MemberType=CUST_MemberType.IDType"
					" where bircard='" + edtMember->Text + "'";
				dsetMember->Active = true;
				if (dsetMember->RecordCount >= 1)
				{
					m_memberID = dsetMember->FieldByName("ID")->AsInteger;
					Key = 0;
					Perform(WM_NEXTDLGCTL, 0, 0);
				}
				else
					m_memberID = 0;
			}
			else
			{
				btnOk->Click();
			}
		}
	}
}
//---------------------------------------------------------------------------




void __fastcall TfrmSelectMember::btnCancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSelectMember::dbedtCardSNKeyPress(TObject *Sender, wchar_t &Key)

{
  if (Key = VK_RETURN) {
      btnOk->SetFocus();
  }
}
//---------------------------------------------------------------------------


void __fastcall TfrmSelectMember::edpasswordKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (enterflag == 0) {
			if (aq->FieldByName("PassWord")->AsString != edpassword->Text) {
            	MessageBox(0,"验证码输入错误，请确认！","错误" ,MB_OK);
				return;
			}
			enterflag = 1;
			dsetMember->Active = false;
			dsetMember->CommandText = "select ID,Name,CardSN,Balance,Discount"
				" from CUST_MemberInfo left join CUST_MemberType"
				" on CUST_MemberInfo.MemberType=CUST_MemberType.IDType"
				" where CardID='" + edtMember->Text + "'";
			dsetMember->Active = true;
			if (dsetMember->RecordCount >= 1)
			{
				m_memberID = dsetMember->FieldByName("ID")->AsInteger;
				Key = 0;
				Perform(WM_NEXTDLGCTL, 0, 0);
			}
			else
				m_memberID = 0;
		}
		else
		{
			btnOk->Click();
		}
	}
}
//---------------------------------------------------------------------------




