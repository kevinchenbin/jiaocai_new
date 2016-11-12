//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "detailemessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
TDetaileForm *DetaileForm;
//---------------------------------------------------------------------------
__fastcall TDetaileForm::TDetaileForm(TComponent* Owner,int type,int savamod,String id,TADOConnection *cnn)
	: TForm(Owner)
{
	modsave = savamod;
	Type = type;
	ID = id;
	aqinit->Connection = cnn;
	aqdetail->Connection = cnn;
}
//---------------------------------------------------------------------------
void TDetaileForm::Initsalesman()
{  	//��ʼ��������Ա
   AnsiString sql ,value;
   sql = "select ID , salesman from SYS_salesman";
   aqinit->Close();
   aqinit->SQL->Clear();
   aqinit->SQL->Add(sql);
   aqinit->Open();
   while(!aqinit->Eof )
   {
	 CBsale->Add(aqinit->FieldByName("salesman")->AsString);
	 aqinit->Next();
   }
}
void TDetaileForm::InitLocalinfo()
{
	//��ʼ������
   AnsiString sql ,value;
   sql = "select ID,local from SYS_local";
   aqinit->Close();
   aqinit->SQL->Clear();
   aqinit->SQL->Add(sql);
   aqinit->Open();
   while(!aqinit->Eof)
   {
	 CBlocal->Add(aqinit->FieldByName("local")->AsString);
	 aqinit->Next();
   }
}
void __fastcall TDetaileForm::FormShow(TObject *Sender)
{
	AnsiString sql;

	Initsalesman();
	InitLocalinfo();

	if (modsave == 2) {
		sql = "select * from CUST_CustomerInfo where ID = " + ID;
        aqinit->Close();
		aqinit->SQL->Clear();
		aqinit->SQL->Add(sql);
		aqinit->Open();
		dbedtName->Text = aqinit->FieldByName("Name")->AsString;
		dbeditContact->Text = aqinit->FieldByName("Contact")->AsString;
		edtphone->Text = aqinit->FieldByName("Telephone")->AsString;
		edtfax->Text = aqinit->FieldByName("Fax")->AsString;
		dbedit->Text = aqinit->FieldByName("Address")->AsString;
		edtcode->Text = aqinit->FieldByName("Code")->AsString;
		CBlocal->Text = aqinit->FieldByName("Local")->AsString;
		CBsale->Text = aqinit->FieldByName("Salesman")->AsString;
		dbedtName->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TDetaileForm::BtnSaveClick(TObject *Sender)
{
	if (modsave == 1) {
		if (dbedtName->Text == "") {
        	MessageBox(0,"�����뵥λ���ƣ�","��Ϣ����" ,MB_OK);
		}
		else
		{
			AnsiString sql,sdf;
			AnsiString salesmanID,LocalID;

			salesmanID = CBsale->Text.Trim();
			LocalID = CBlocal->Text.Trim();

			sql = "Insert into cust_customerinfo(Type,name,contact,telephone,fax,salesman,code,date,address,local) ";
			sql = sql + " values(" + Type + ",'" + dbedtName->Text + "','" + dbeditContact->Text.Trim()+"','" + edtphone->Text + "','";
			sql = sql + edtfax->Text.Trim() + "','" + salesmanID + "','" + edtcode->Text.Trim();
			sql = sql + "',GetDate(),'" +  dbedit->Text.Trim()+ "','" + LocalID + "')";

			if (Type == 1) {
				sdf = "ȷ����ӹ�Ӧ��" + dbedtName->Text +"��" ;
			}
			if (Type == 2) {
				sdf = "ȷ����ӿͻ�" + dbedtName->Text +"��" ;
			}

			if (MessageBox(0,sdf.c_str() ,"���ȷ��" ,MB_OKCANCEL)==1) {
            	aqinit->Close();
				aqinit->SQL->Clear();
				aqinit->SQL->Add(sql);
				aqinit->ExecSQL();
				sql =  "select max(ID) as id from cust_customerinfo";
				aqinit->Close();
				aqinit->SQL->Clear();
				aqinit->SQL->Add(sql);
				aqinit->Open();
				int customerid = aqinit->FieldByName("id")->AsInteger ;
				sql = "insert into CUST_CustomerStartMoney(CustomerID) values (" + IntToStr(customerid)  + ")" ;
				aqinit->Close();
				aqinit->SQL->Clear();
				aqinit->SQL->Add(sql);
				aqinit->ExecSQL();
				this->Close();
			}
		}
	}
	if (modsave == 2) {
		AnsiString sql,sdf;
		sql = "update cust_customerinfo set Contact = '" + dbeditContact->Text.Trim()+ "',Telephone = '";
		sql = sql + edtphone->Text + "',Fax = '" + edtfax->Text.Trim() + "',Address = '" + dbedit->Text.Trim();
		sql = sql + "',Code = '" + edtcode->Text.Trim() +"',local = '" + CBlocal->Text.Trim() + "',salesman = '" + CBsale->Text.Trim() + "'";
		sql = sql + " where ID = " + ID;

		if (Type == 1) {
			sdf = "ȷ���޸Ĺ�Ӧ��" + dbedtName->Text +"��" ;
		}
		if (Type == 2) {
			sdf = "ȷ���޸Ŀͻ�" + dbedtName->Text +"��" ;
		}

		if (MessageBox(0,sdf.c_str() ,"�޸�ȷ��" ,MB_OKCANCEL)==1) {
			try {
				aqinit->Close();
				aqinit->SQL->Clear();
				aqinit->SQL->Add(sql);
				aqinit->ExecSQL();
				this->Close();
			} catch (Exception &E) {
				MessageBox(0,"�����ݸ�ϵͳ���������й����������޸ģ�","�޸Ĵ���" ,MB_OK);
			}
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TDetaileForm::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

