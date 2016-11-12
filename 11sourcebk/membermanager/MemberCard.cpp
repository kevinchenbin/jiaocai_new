//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberCard.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
TfrmMemberCard *frmMemberCard;
//---------------------------------------------------------------------------
__fastcall TfrmMemberCard::TfrmMemberCard(TComponent* Owner,int mdole,String *ASMemberInfo,TADOConnection *cn)
	: TForm(Owner)
{
	m_modle = mdole;
	ASMemInfo = ASMemberInfo;
	quMemberCard->Connection  = cn;
	quMemberType->Connection = cn;
	ADOCommand1->Connection = cn;
	quMemberInfo->Connection = cn;
	tdtbirthday->Date = Date();
	tdtbirthday->Date = Date();
	if (mdole == 2) {
        edpassword->Enabled = false;
	}
}
//---------------------------------------------------------------------------
//��Ա��
void __fastcall TfrmMemberCard::edtnameChange(TObject *Sender)
{
	name =  edtname->Text;
}
//---------------------------------------------------------------------------
//��Ա����
void __fastcall TfrmMemberCard::edtcardIDChange(TObject *Sender)
{
	cardID =  edtcardID->Text;
}
//---------------------------------------------------------------------------
//��Ա�Ա�
void __fastcall TfrmMemberCard::edtsexChange(TObject *Sender)
{
	sex =  cbsex->Text ;
	if (sex == "��") {
		memsex = 0;     //0Ϊ����
	}
	else
	{
		memsex = 1;     //1ΪŮ��
	}
}
//---------------------------------------------------------------------------
//��Ա����
void __fastcall TfrmMemberCard::tdtbirthdayClick(TObject *Sender)
{
	birthday = DateToStr(tdtbirthday->Date);
}
//��Ա����
void __fastcall TfrmMemberCard::cbtypeSelect(TObject *Sender)
{
	type =  cbtype->Value ;
//-----�ۿ۵���ʾ
	memtype = int(cbtype->Items->Objects[cbtype->ItemIndex]);
	AnsiString sql = "select IDType,discount from cust_membertype where IDType = ";
	sql = sql + memtype;
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	edtdiscount->Text =  quMemberType->FieldByName("discount")->AsString + "%";
}
//---------------------------------------------------------------------------
//��Ա�绰
void __fastcall TfrmMemberCard::edttelephoneChange(TObject *Sender)
{
	telephone =  edttelephone->Text;
}
//---------------------------------------------------------------------------
//��Ա�ֻ�
void __fastcall TfrmMemberCard::edtmobileChange(TObject *Sender)
{
	mobile =  edtmobile->Text;
}
//---------------------------------------------------------------------------
//��Ա��ַ
void __fastcall TfrmMemberCard::edtaddressChange(TObject *Sender)
{
	address =  edtaddress->Text;
}
//---------------------------------------------------------------------------
//��Ա��ַ�ʱ�
void __fastcall TfrmMemberCard::edtpostalcodeChange(TObject *Sender)
{
	postalcode =  edtpostalcode->Text;
}
//---------------------------------------------------------------------------
//�ۿ�
void __fastcall TfrmMemberCard::edtdiscountChange(TObject *Sender)
{
	discount =  edtdiscount->Text;
}

//---------------------------------------------------------------------------

//����
void __fastcall TfrmMemberCard::BtnSaveClick(TObject *Sender)
{
	int cardsnlen = 0;
	AnsiString sql;
	sex =  cbsex->Text ;
	if (sex == "��") {
		memsex = 0;     //0Ϊ����
	}
	else
	{
		memsex = 1;     //1ΪŮ��
	}
	if (edCardCast->Text == "") {
		edCardCast->Text = "0";
	}
	try {
		float cardcast = StrToFloat(edCardCast->Text);
	} catch (...) {
		MessageBox(0,"��������ȷ�Ĺ�����","����" ,MB_ICONWARNING);
		return;
	}
	if (edtname->Text == "") {
		MessageBox(0,"��Ա���ֲ���Ϊ�գ�","����ȷ��" ,MB_ICONWARNING);
		return;
	}
	else
	{
		if (cardID == "") {
			MessageBox(0,"��Ա���Ų���Ϊ�գ�","����ȷ��" ,MB_ICONWARNING);
			return;
		}
		else
		{
			cardsnlen =  cardID.Length();
			if (cardsnlen!= 13) {
				MessageBox(0,"������13λ��Ա���ţ�","����λ��ȷ��" ,MB_ICONWARNING);
				return;
			}
			else
			{
				if (quMemberInfo->Active == true) {
                	quMemberInfo->Active = false;
				}
				if (m_modle == 1 ) {     //��ӻ�Ա��Ϣ
					AnsiString sql = "select * from CUST_MemberInfo where CardID = '" ;
					sql = sql +  cardID + "'";
					quMemberInfo->Close();
					quMemberInfo->SQL->Clear();
					quMemberInfo->SQL->Add(sql);
					quMemberInfo->Open();
					if (quMemberInfo->IsEmpty() ) {
                    	sql =  "select max(ID) as id from CUST_MemberInfo";
						quMemberCard->Close();
						quMemberCard->SQL->Clear();
						quMemberCard->SQL->Add(sql);
						quMemberCard->Open();
						int memberid = quMemberCard->FieldByName("id")->AsInteger + 1 ;
						AnsiString sqlMemberCard = "select * from CUST_MemberCard " ;
						quMemberCard->Close();
						quMemberCard->SQL->Clear();
						quMemberCard->SQL->Add(sqlMemberCard);
						quMemberCard->Open();
						if (quMemberInfo->State != dsInsert||quMemberCard->State != dsInsert ) {
							quMemberInfo->Append();
							quMemberCard->Append();
						}
						if (quMemberInfo->State == dsInsert && quMemberCard->State == dsInsert)
						{
							quMemberInfo->FieldByName("Name")->AsString = edtname->Text;
							quMemberInfo->FieldByName("Birthday")->AsDateTime = tdtbirthday->DateTime;
							quMemberInfo->FieldByName("CardID")->AsString = edtcardID->Text;
							quMemberInfo->FieldByName("MemberType")->AsInteger =  memtype;
							quMemberInfo->FieldByName("Sex")->AsInteger = memsex;
							quMemberInfo->FieldByName("Tel")->AsString = edttelephone->Text;
							quMemberInfo->FieldByName("Mobile")->AsString = edtmobile->Text;
							quMemberInfo->FieldByName("Address")->AsString = edtaddress->Text;
							quMemberInfo->FieldByName("PostalCode")->AsString = edtpostalcode->Text;
							quMemberInfo->FieldByName("CardSN")->AsString = edtcardID->Text;
							quMemberInfo->FieldByName("CardType")->AsInteger = rg->ItemIndex ;
							quMemberInfo->FieldByName("bircard")->AsString = edbircard->Text;
							quMemberInfo->FieldByName("CardCast")->AsString = edCardCast->Text ;
							quMemberInfo->FieldByName("PassWord")->AsString = edpassword->Text.Trim();

							quMemberCard->FieldByName("CardID")->AsString = edtcardID->Text;
							quMemberCard->FieldByName("Type")->AsInteger =  memtype;
							quMemberCard->FieldByName("MIfID")->AsInteger =  memberid;
							if(MessageBox(0,"��ȷ����Ӹû�Ա��","���ȷ��" ,MB_ICONQUESTION|MB_OKCANCEL)==1)
							{
								quMemberInfo->Post();
								quMemberCard->Post();
								this->Close();
							}
						}
					}
					else
					{
						MessageBox(0,"�û�Ա�����Ѿ����ڣ�","����ȷ��" ,MB_ICONWARNING);
					}

				}
				else {    //�޸Ļ�Ա��Ϣ
					AnsiString sql = "select * from CUST_MemberInfo where ID = " ;
					sql = sql +  ASMemInfo[0];
					quMemberInfo->Close();
					quMemberInfo->SQL->Clear();
					quMemberInfo->SQL->Add(sql);
					quMemberInfo->Open();
					if (!quMemberInfo->IsEmpty() ) {
						sql = "update CUST_MemberInfo set CardType = " + IntToStr(rg->ItemIndex) ;
						sql = sql + ", Name = '"+name+"',Birthday = " + DateToStr(tdtbirthday->Date)  + ",MemberType = " +memtype +",Sex = "
						+memsex +",CardID = '" +cardID +"',Tel = '" + telephone +"',Mobile ='" +mobile + "',CardCast = " + edCardCast->Text + ",bircard = '" + edbircard->Text ;
						sql = sql + "',Address = '" + address +"',PostalCode = '" + postalcode + "' where id = " + ASMemInfo[0];
							try{
								if(MessageBox(0,"��ȷ���޸ĸû�Ա��","�޸�ȷ��" ,MB_ICONQUESTION|MB_OKCANCEL)==1)
								{
								quMemberInfo->Close();
								quMemberInfo->SQL->Clear();
								quMemberInfo->SQL->Add(sql);
								quMemberInfo->ExecSQL();
								this->Close();
								}
							}
							catch(Exception &E)
							{
								MessageBox(0,"�����ݲ��ܸ��£�","����ȷ��" ,MB_ICONWARNING);
							}

					}
					else
					{
						MessageBox(0,"���µĻ�Ա�����ڣ�","����ȷ��" ,MB_ICONWARNING);
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
//�˳�
void __fastcall TfrmMemberCard::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

//��ʼ������ʾ
void __fastcall TfrmMemberCard::FormShow(TObject *Sender)
{
	PageControl1->ActivePageIndex = 0;

//------��ѯ��Ա��������ӵ���Ա���͵������б���
	AnsiString sql = "select IDType,Type as T from cust_membertype order by discount desc ";  //��ѯ��Ա�����
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	quMemberType->First();
	while(!quMemberType->Eof )
	{
	  cbtype->AddObject(quMemberType->FieldByName("T")->AsAnsiString ,(TObject*)quMemberType->FieldByName("IDType")->AsInteger );
	  quMemberType->Next();
	}
	cbtype->ItemIndex = 0;
//------����Ա������
	cbsex->Add("��");//��Ӧ������ֵΪ0
	cbsex->Add("Ů");//��Ӧ������ֵΪ1
	cbsex->Text = "��";
	memtype = int(cbtype->Items->Objects[cbtype->ItemIndex]);
//------�ۿ۵ĳ�ʼ��ʾ
	sql = "select IDType,discount from cust_membertype where IDType = ";
	sql = sql +  memtype;
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	edtdiscount->Text =  quMemberType->FieldByName("discount")->AsString + "%";
	cbtype->ItemIndex = 0;
//------�޸�ʱ����ĳ�ʼֵ�趨
	if (m_modle == 2) {
        edtcardID->Enabled = false;
		edtname->Text =  ASMemInfo[1]; // ��Ա��
		tdtbirthday->DateTime = StrToDateTime(ASMemInfo[2]); // ��Ա����
		cbsex->Text = ASMemInfo[3];    // ��Ա�Ա�
		edttelephone->Text =  ASMemInfo[4]; // ��Ա�绰
		edtmobile->Text =  ASMemInfo[5];  // ��Ա�ֻ�
		edtaddress->Text = ASMemInfo[6];  // ��Ա��ַ
		edtpostalcode->Text =  ASMemInfo[7];  // ��Ա��ַ�ʱ�
		edtcardID->Text =  ASMemInfo[8];  // ��Ա����
		cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)StrToInt(ASMemInfo[11]));  //��Ա����
		edCardCast->Text = ASMemInfo[12];
		rg->ItemIndex = StrToInt(ASMemInfo[13]);
		edbircard->Text = ASMemInfo[14];
		//-----�ۿ۵���ʾ
		memtype = int(cbtype->Items->Objects[cbtype->ItemIndex]);
		sql = "select IDType,discount from cust_membertype where IDType = ";
		sql = sql + memtype;
		quMemberType->Close();
		quMemberType->SQL->Clear();
		quMemberType->SQL->Add(sql);
		quMemberType->Open();
		edtdiscount->Text =  quMemberType->FieldByName("discount")->AsString + "%";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edtnameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        if (edtname->Text == "") {
			MessageBox(0,"��Ա���ֲ���Ϊ�գ�","����ȷ��" ,MB_ICONWARNING);
			return;
		}
		cbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edtcardIDKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	String cardID =  edtcardID->Text ;
	if (Key == VK_RETURN) {
		if (cardID == "") {
			MessageBox(0,"��Ա���Ų���Ϊ�գ�","����ȷ��" ,MB_ICONWARNING);
			return;
		}
		else
		{
			int cardsnlen =  cardID.Length();
			if (cardsnlen!= 13) {
				MessageBox(0,"������13λ��Ա���ţ�","����λ��ȷ��" ,MB_ICONWARNING);
				return;
			}
		}
		if (m_modle == 1) {
			edpassword->SetFocus();
		}
		else
			edtname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::cbsexKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_RETURN) {
		edCardCast->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::tdtbirthdayKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
	    PageControl1->ActivePageIndex = 1;
		edbircard->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::cbtypeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		cbsex->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edttelephoneKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
    	edtmobile->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edtmobileKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edtaddress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edtaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edtpostalcode->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edtpostalcodeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edCardCastKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		tdtbirthday->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edpasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edtname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
		if (Key == VK_F4) {
		 BtnSave->Click();
	   }
		if (Shift.Contains(ssCtrl)&& Key ==81  ) {
			BtnExit->Click();
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberCard::edbircardKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edttelephone->SetFocus();
	}
}
//---------------------------------------------------------------------------

