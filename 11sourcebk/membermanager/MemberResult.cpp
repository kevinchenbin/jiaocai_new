//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberResult.h"
#include "PwdForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzDBGrid"
#pragma link "RzLine"
#pragma resource "*.dfm"
TfrmMemberResult *frmMemberResult;
//---------------------------------------------------------------------------
__fastcall TfrmMemberResult::TfrmMemberResult(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
  quType->Connection = cn;
  quMemberCard->Connection = cn;
  quMemberInfo->Connection = cn;
  quMemberRecord->Connection = cn;
  fcon = cn;
  AnsiString sql;
  int maxid;
  sql = "select max(ID) as id from CUST_MemberInfo";
  quMemberCard->Close();
  quMemberCard->SQL->Clear();
  quMemberCard->SQL->Add(sql);
  quMemberCard->Open();
  maxid = quMemberCard->FieldByName("id")->AsInteger ;
  sql = "select CUST_MemberInfo.ID,CUST_MemberInfo.CardSN,CUST_MemberInfo.CardID,CUST_MemberInfo.Name,CUST_MemberType.Type,"
		"CUST_MemberInfo.Balance,CUST_MemberInfo.Birthday,CUST_MemberInfo.Sex,case CUST_MemberInfo.Sex when 0 then '男' when 1 then '女' end as Sexname,CUST_MemberInfo.Tel,"
		"CUST_MemberInfo.Mobile,CUST_MemberInfo.Address,CUST_MemberInfo.PostalCode,CUST_MemberInfo.TotalConsumption,"
		"CUST_MemberInfo.MemberType from CUST_MemberInfo inner join CUST_MemberType on CUST_MemberInfo.MemberType = CUST_MemberType.IDType "
		"where CUST_MemberInfo.ID > " + IntToStr(maxid);
  quMemberInfo->Close();
  quMemberInfo->SQL->Clear();
  quMemberInfo->SQL->Add(sql);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemberResult::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberResult::FormShow(TObject *Sender)
{
	//向会员下拉列表添加类型值
	AnsiString sql;
	TTreeNode * Node,* Root;
	AnsiString Value;
    AnsiString membertype;
	sql = "select IDType,Type as T,Discount from cust_membertype order by discount desc ";
	quType->Close();
	quType->SQL->Clear();
	quType->SQL->Add(sql);
	quType->Open();
	while(!quType->Eof )
	{
		membertype =  quType->FieldByName("T")->AsAnsiString.Trim()+"(" + quType->FieldByName("Discount")->AsAnsiString.Trim() + "%)";
		cbMemberType->AddItem(membertype ,(TObject*)quType->FieldByName("IDType")->AsInteger);
		quType->Next();
	}
	cbMemberType->ItemIndex = 0;
}
//----------------------------------------------------------------------------


void __fastcall TfrmMemberResult::btEscClick(TObject *Sender)
{
	   Close();
}

//------------------------会员类型查询---------------------------------------

void __fastcall TfrmMemberResult::cbMemberTypeSelect(TObject *Sender)
{
	  int memtype;
	  memtype = int(cbMemberType->Items->Objects[cbMemberType->ItemIndex]);
	  AnsiString sql = "select CUST_MemberInfo.ID,CUST_MemberInfo.CardSN,CUST_MemberInfo.CardID,CUST_MemberInfo.Name,CUST_MemberType.Type,CUST_MemberInfo.Balance,CUST_MemberInfo.Birthday,CUST_MemberInfo.CardType,CUST_MemberInfo.PassWord,CUST_MemberInfo.Sex,case CUST_MemberInfo.Sex when 0 then '男' when 1 then '女' end as Sexname,case CUST_MemberInfo.Available when 0 then '无效'  else  '有效' end as aviable,CUST_MemberInfo.Tel,CUST_MemberInfo.Mobile,CUST_MemberInfo.Address,CUST_MemberInfo.PostalCode,CUST_MemberInfo.TotalConsumption,CUST_MemberInfo.MemberType,CUST_MemberInfo.Memberdot,CUST_MemberInfo.CardCast from CUST_MemberInfo inner join CUST_MemberType on CUST_MemberInfo.MemberType = CUST_MemberType.IDType where MemberType = ";
	  sql = sql + memtype;
	  quMemberInfo->Close();
	  quMemberInfo->SQL->Clear();
	  quMemberInfo->SQL->Add(sql);
	  quMemberInfo->Open();
}

//----------------------------------------------------------------------------
void __fastcall TfrmMemberResult::dgmemlistTitleClick(TColumn *Column)
{
	AnsiString qusort;
	if (quMemberInfo->IsEmpty() ) {
        return;
	}
	qusort =  Column->FieldName + " ASC";
	if (quMemberInfo->Sort == "") {
		quMemberInfo->Sort =  Column->FieldName + " ASC";
	}
	else if (quMemberInfo->Sort == qusort) {
		quMemberInfo->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		quMemberInfo->Sort =  Column->FieldName + " ASC";
	}

}
//---------------------------------------------------------------------------
void __fastcall TfrmMemberResult::edtcardnumKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberResult::edtnameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmMemberResult::BtnViewClick(TObject *Sender)
{
	AnsiString  card = "",name = "",sql = "select CUST_MemberInfo.ID,CUST_MemberInfo.CardSN,CUST_MemberInfo.CardID,CUST_MemberInfo.Name,CUST_MemberType.Type,CUST_MemberInfo.Balance, CUST_MemberInfo.Birthday,CUST_MemberInfo.Sex,CUST_MemberInfo.CardType,CUST_MemberInfo.PassWord,case CUST_MemberInfo.Sex when 0 then '男' when 1 then '女' end as Sexname,CUST_MemberInfo.Tel,CUST_MemberInfo.Mobile,CUST_MemberInfo.Address,CUST_MemberInfo.PostalCode,CUST_MemberInfo.TotalConsumption,CUST_MemberInfo.MemberType,CUST_MemberInfo.Memberdot,case CUST_MemberInfo.Available when 0 then '无效'  else '有效' end as aviable,CUST_MemberInfo.CardCast from CUST_MemberInfo inner join CUST_MemberType on CUST_MemberInfo.MemberType = CUST_MemberType.IDType ";
	  card = edtcardnum->Text;
	  name = edtname->Text;
	  card = Trim(card);
	  name = Trim(name);
	  if (card != "") {
			if (name != "") {
				  sql = sql + "where CardID like '%" + card + "%' and Name like '%" + name + "%'";
			}
			else {
				  sql = sql + "where CardID like '%" + card + "%'" ;
			}
	  }
	  else
	  {
          if (name != "") {
				  sql = sql + "where name like '%"  + name + "%'";
			}
	  }
	  quMemberInfo->Close();
	  quMemberInfo->SQL->Clear();
	  quMemberInfo->SQL->Add(sql);
	  quMemberInfo->Open();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberResult::BtnNoteClick(TObject *Sender)
{
	if (quMemberInfo->Active == true &&quMemberInfo->RecordCount > 0) {
        if (quMemberInfo->FieldByName("Name")->AsString == "普通会员") {
			MessageBox(0,"普通会员不能充值！","系统提示" ,MB_OK);
			return;
		}
        if (quMemberInfo->FieldByName("aviable")->AsString == "无效") {
			MessageBox(0,"该会员卡已退卡，不能充值！","系统提示" ,MB_OK);
			return;
		}
		String sql = "select Member from SYS_StorageInfo";
		quType->Close();
		quType->SQL->Clear();
		quType->SQL->Add(sql);
		quType->Open();
		String password = quType->FieldByName("Member")->AsString ;
		TfrmPwd* frm = new TfrmPwd(this);
		if (mrOk == frm->ShowModal())
		{
			if (frm->GetPassword() != password)
			{
				MessageBoxA(0,"密码错误！","警告",MB_ICONASTERISK);
				return;
			}
		}
		else
		{
        	return;
		}
		delete frm;
		Tfrmaddvalue * frm1 = new Tfrmaddvalue(Application,quMemberInfo->FieldByName("CardID")->AsString,fcon);
		frm1->userid = userid;
		frm1->fstgid = stgid;
		frm1->ShowModal();
		delete frm1;
		quMemberInfo->Active = false;
		quMemberInfo->Active = true;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMemberResult::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
       	if (Key == VK_F1) {
		 BtnView->Click();
	   }
		if (Key == VK_F2) {
		 BtnNote->Click();
	   }
		if (Shift.Contains(ssCtrl)&& Key ==90) {
			WindowState = wsNormal  ;
		}
		if (Shift.Contains(ssCtrl)&& Key ==81  ) {
			btEsc->Click();
		}
		if (Shift.Contains(ssCtrl)&& Key == 78 ) {
		  BtnAlignBottom->Click();
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberResult::BtnAlignBottomClick(TObject *Sender)
{
WindowState = wsMinimized   ;
}
//---------------------------------------------------------------------------

