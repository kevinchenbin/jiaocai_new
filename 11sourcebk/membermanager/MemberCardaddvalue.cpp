//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberCardaddvalue.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmaddvalue *frmaddvalue;
//---------------------------------------------------------------------------
__fastcall Tfrmaddvalue::Tfrmaddvalue(TComponent* Owner,AnsiString MemcardID,TADOConnection *cn)
	: TForm(Owner)
{
	cardID =  MemcardID;
	MemberCardQuery->Connection = cn;
	quMemberRecord->Connection = cn;
	fcon = cn;
}
//---------------------------------------------------------------------------
//�ֿ���
void __fastcall Tfrmaddvalue::edtcardnameChange(TObject *Sender)
{
	name =  edtcardname->Text;
}

//---------------------------------------------------------------------------
//����
void __fastcall Tfrmaddvalue::edtcardnumChange(TObject *Sender)
{
	cardnum = edtcardnum->Text;
}
//---------------------------------------------------------------------------
//�������
void __fastcall Tfrmaddvalue::edtvalueChange(TObject *Sender)
{
	value = edtvalue->Text;
}
//---------------------------------------------------------------------------
//��ֵ���
void __fastcall Tfrmaddvalue::edtaddvalueChange(TObject *Sender)
{
	addvalue = edtaddvalue->Text;
}
//---------------------------------------------------------------------------
//ȷ��
void __fastcall Tfrmaddvalue::btComfirmClick(TObject *Sender)
{
	AnsiString sqlMemberCard,sqlMemberInfo,sqlMemberRecord,sql,Type,sdf;
	float old_cash = 0.00,new_cash = 0.00,VAmount;
	int  ID;

	try {
		StrToFloat(edtaddvalue->Text);
	} catch (...) {
		MessageBox(0,"��������ȷ�ĳ�ֵ���","��ʾ" ,MB_OK);
		return;
	}
	sqlMemberCard = "update CUST_MemberCard set BalanceAmount=BalanceAmount+"+edtaddvalue->Text +"  where CardID = '"+cardID + "'";
	sqlMemberInfo = "update CUST_MemberInfo set Balance=Balance+"+edtaddvalue->Text +" where CUST_MemberInfo.cardID = '"+cardID + "'";
	sqlMemberRecord = "select * from CUST_MemberToprecord where CardID = '" + cardID + "' order by Tid desc ";
	sql = "select CUST_MemberInfo.id as ID,CUST_MemberType.Type as T from CUST_MemberInfo inner join CUST_MemberType on CUST_MemberInfo.MemberType = CUST_MemberType.IDType where CUST_MemberInfo.cardID = '"+cardID + "'";
	quMemberRecord->Close();
	quMemberRecord->SQL->Clear();
	quMemberRecord->SQL->Add(sql);
	quMemberRecord->Open();
	ID = quMemberRecord->FieldByName("ID")->AsInteger;
    Type = quMemberRecord->FieldByName("T")->AsString;
	quMemberRecord->Close();
	quMemberRecord->SQL->Clear();
	quMemberRecord->SQL->Add(sqlMemberRecord);
	quMemberRecord->Open();
	if (quMemberRecord->IsEmpty() ) {
		VAmount = 0;
	}
	else
	{
		quMemberRecord->First();
		VAmount = quMemberRecord->FieldByName("VoucherAmount")->AsFloat ;
	}
	VAmount =  VAmount + StrToFloat(edtaddvalue->Text);
	old_cash = StrToFloat(edtvalue->Text);
	new_cash = old_cash + StrToFloat(edtaddvalue->Text);
	sdf =  "��ȷ�϶Ի�Ա��"+edtcardname->Text+"��ֵ"+edtaddvalue->Text+"Ԫ��";
	if(MessageBox(0,sdf.c_str() ,"ȷ�ϳ�ֵ" ,MB_ICONQUESTION|MB_OKCANCEL)==1)
	{
		try {
			MemberCardQuery->Close();
			MemberCardQuery->SQL->Clear();
			MemberCardQuery->SQL->Add(sqlMemberCard);
			MemberCardQuery->ExecSQL();
			MemberCardQuery->Close();
			MemberCardQuery->SQL->Clear();
			MemberCardQuery->SQL->Add(sqlMemberInfo);
			MemberCardQuery->ExecSQL();
			if (quMemberRecord->State != dsInsert) {
				quMemberRecord->Append();
			}
			if (quMemberRecord->State == dsInsert) {
				quMemberRecord->FieldByName("date")->AsDateTime =Date();
				quMemberRecord->FieldByName("BeforeVoucherAmount")->AsFloat  = old_cash;
				quMemberRecord->FieldByName("VoucherAmount")->AsFloat  = VAmount;
				quMemberRecord->FieldByName("AfterVoucherAmount")->AsFloat =  new_cash;
				quMemberRecord->FieldByName("CorrentVoucher")->AsFloat = StrToFloat(edtaddvalue->Text);
				quMemberRecord->FieldByName("CardID")->AsString =  cardID;
				quMemberRecord->FieldByName("MIid")->AsInteger = ID;
				quMemberRecord->FieldByName("MIName")->AsString =  edtcardname->Text;
				quMemberRecord->FieldByName("MIType")->AsString = Type;
				quMemberRecord->FieldByName("stgid")->AsInteger  = fstgid;
				quMemberRecord->FieldByName("userid")->AsInteger = userid;
				quMemberRecord->Post() ;
				//�����б�ĸ��¶��ɹ�
				sdf =  "��Ա��"+edtcardname->Text+"��ֵ�ɹ�����ֵ���Ϊ"+edtaddvalue->Text+"Ԫ����ʣ����Ϊ"+new_cash+"Ԫ��" ;
				MessageBox(0,sdf.c_str(),"��ֵȷ��    " ,MB_ICONINFORMATION);
				logmessage = "�Ի�Ա��" +  edtcardnum->Text + "��ֵ" + edtaddvalue->Text + "Ԫ";
				AddEvent(1,"��Ա����ֵ����",userid,fstgid,logmessage,fcon);
				this->Close();
			}
		}
		catch (Exception &E) {
			sdf =  "��Ա��"+edtcardname->Text+"��ֵʧ�ܣ�" ;
			MessageBox(0,sdf.c_str(),"ʧ��ȷ��    " ,MB_ICONINFORMATION);
		}
	}
}
//---------------------------------------------------------------------------

//ȡ��
void __fastcall Tfrmaddvalue::btConselClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

//�����ʼ��ʾ
void __fastcall Tfrmaddvalue::FormShow(TObject *Sender)
{
	AnsiString sql ;
	cardID = Trim(cardID);
	sql = "select Name,CardID,Balance from CUST_MemberInfo where CardID = '";
	sql = sql + cardID + "'";
	MemberCardQuery->Close();
	MemberCardQuery->SQL->Clear();
	MemberCardQuery->SQL->Add(sql);
	MemberCardQuery->Open();
	edtcardname->Text =  MemberCardQuery->FieldByName("Name")->AsString;
	edtcardnum->Text = MemberCardQuery->FieldByName("CardID")->AsAnsiString;
	edtvalue->Text = MemberCardQuery->FieldByName("Balance")->AsFloat;
	edtcardname->Enabled = false;
	edtcardnum->Enabled = false;
	edtvalue->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmaddvalue::edtaddvalueKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
    	btComfirm->Click();
	}
}
//---------------------------------------------------------------------------

