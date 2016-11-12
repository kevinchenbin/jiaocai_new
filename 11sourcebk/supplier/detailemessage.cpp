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
	if (Type == 1) {
		if (modsave == 1) {
			this->Caption = "�¹�Ӧ������¼��" ;
		}
		else
		{
			this->Caption = "��Ӧ�������޸�" ;
		}
		Label12->Visible = false;
		Label13->Visible = false;
		edlogname->Visible = false;
		edpassword->Visible = false;
	}
	if (Type == 2) {
		if (modsave == 1) {
			this->Caption = "�¿ͻ�����¼��" ;
		}
		else
		{
			this->Caption = "�ͻ������޸�" ;
		}
	}
}
//---------------------------------------------------------------------------
void TDetaileForm::Initsalesman()
{  	//��ʼ��������Ա
   AnsiString sql ,value;
   sql = "select * from SYS_StaffInfo where Career = 1";
   if (Type==2) {
		sql = "select * from SYS_StaffInfo where Career = 2";
        RzLabel9->Caption = "ҵ��Ա��";
   }
   aqinit->Close();
   aqinit->SQL->Clear();
   aqinit->SQL->Add(sql);
   aqinit->Open();
   while(!aqinit->Eof )
   {
	 CBsale->AddItem(aqinit->FieldByName("Name")->AsString ,(TObject*)aqinit->FieldByName("ID")->AsInteger );
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
void TDetaileForm::InitType()
{
	//��ʼ������
   AnsiString sql ,value;
   sql = "select ID,Name from CUST_Customertype where type = " + IntToStr(Type) ;
   aqinit->Close();
   aqinit->SQL->Clear();
   aqinit->SQL->Add(sql);
   aqinit->Open();
   while(!aqinit->Eof)
   {
	 cbtype->AddItem(aqinit->FieldByName("Name")->AsString,(TObject*)aqinit->FieldByName("ID")->AsInteger);
	 aqinit->Next();
   }
}
void __fastcall TDetaileForm::FormShow(TObject *Sender)
{
	dbedtName->SetFocus();
	if (modsave == 2) {
    	edtphone->SetFocus();
	}
	AnsiString sql;

	Initsalesman();
	InitLocalinfo();
	InitType();

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
		edemail->Text = aqinit->FieldByName("Email")->AsString ;
		edsecondcontact->Text = aqinit->FieldByName("secondlyContact")->AsString ;
		edpostaddress->Text = aqinit->FieldByName("postAddress")->AsString ;
		edmsnaddress->Text = aqinit->FieldByName("MSNAddress")->AsString ;
		edwebaddress->Text = aqinit->FieldByName("WEBAddress")->AsString ;
		edbank->Text = aqinit->FieldByName("bank")->AsString ;
		edbankaccount->Text = aqinit->FieldByName("bankAccount")->AsString ;
		edqq->Text = aqinit->FieldByName("QQCode")->AsString ;
		edlogname->Text = aqinit->FieldByName("logname")->AsString ;
		edpassword->Text = aqinit->FieldByName("logpassword")->AsString ;
		cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)aqinit->FieldByName("customertype")->AsInteger );

               if (Type==1) { //��Ӧ��
                  sql="exec getclientyefuguanlian "+ID+",0";
               }else if (Type==2) {  //�ͻ�
                   sql="exec getclientyefuguanlian "+ID+",1";
                     }

                aqinit->SQL->Clear();
	      	aqinit->SQL->Add(sql);
	      	aqinit->Open();
                if (aqinit->FieldByName("result")->AsInteger==1)
                {
                 // dbedtName->Enabled = false;
                }




	  //	dbedtName->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TDetaileForm::BtnSaveClick(TObject *Sender)
{
	AnsiString sql,sdf;

    if (dbedtName->Text == "") {
		MessageBox(0,"�����뵥λ���ƣ�","��Ϣ����" ,MB_ICONWARNING);
		return;
	}
	if (modsave == 1) {
        if (Type == 1) {
			sql = "select * from CUST_CustomerInfo where type = 1 and Name = '" + dbedtName->Text.Trim() + "'";
			aqdetail->Close();
			aqdetail->SQL->Clear();
			aqdetail->SQL->Add(sql);
			aqdetail->Open();
			if (aqdetail->RecordCount > 0) {
				MessageBox(0,"�ù�Ӧ���Ѿ�¼�룬��ȷ�ϣ�","¼���ظ�" ,MB_ICONWARNING);
				return;
			}else {    //����������ʾ
                         sql = "select * from CUST_CustomerInfo where type = 1 and Name like '%" + dbedtName->Text.Trim() + "%'";
			aqdetail->Close();
			aqdetail->SQL->Clear();
			aqdetail->SQL->Add(sql);
			aqdetail->Open();
                        if (aqdetail->RecordCount > 0) {
                             AnsiString msg="ϵͳ�������ƹ�Ӧ�̣�";
                           while(!aqdetail->Eof)
                           {

                              msg = msg + aqdetail->FieldByName("name")->AsAnsiString;


                              aqdetail->Next();
                           }
                           msg=msg+"��ע��";
                            MessageBox(0,msg.c_str(),"��ʾ" ,MB_ICONWARNING);
                        }
                        }
		}else if (Type==2) {    //�ͻ�

                      sql = "select * from CUST_CustomerInfo where type = 2 and Name = '" + dbedtName->Text.Trim() + "'";
			aqdetail->Close();
			aqdetail->SQL->Clear();
			aqdetail->SQL->Add(sql);
			aqdetail->Open();
			if (aqdetail->RecordCount > 0) {
				MessageBox(0,"�ÿͻ��Ѿ�¼�룬��ȷ�ϣ�","¼���ظ�" ,MB_ICONWARNING);
				return;
			}else {    //����������ʾ
                         sql = "select * from CUST_CustomerInfo where type = 2 and Name like '%" + dbedtName->Text.Trim() + "%'";
			aqdetail->Close();
			aqdetail->SQL->Clear();
			aqdetail->SQL->Add(sql);
			aqdetail->Open();
                        if (aqdetail->RecordCount > 0) {
                             AnsiString msg="ϵͳ�������ƿͻ����ƣ�";
                           while(!aqdetail->Eof)
                           {

                              msg = msg + aqdetail->FieldByName("name")->AsAnsiString;


                              aqdetail->Next();
                           }
                           msg=msg+"��ע��";
                            MessageBox(0,msg.c_str(),"��ʾ" ,MB_ICONWARNING);
                        }

                        }
                }


			int memtype;
			if (cbtype->Text != "") {
            	try {
					memtype =  int(cbtype->Items->Objects[cbtype->ItemIndex]);
				} catch (...) {
					MessageBox(0,"��ѡ����ȷ�����","����" ,MB_ICONWARNING);
					return;
				}
			}

			AnsiString salesmanID,LocalID;

			salesmanID = CBsale->Text.Trim();
			LocalID = CBlocal->Text.Trim();

			if (ParentID != -1 && Type != 1) {
				Type = 3;
			}
			if (cbtype->Text != "") {
				sql = "Insert into cust_customerinfo(Type,name,contact,telephone,fax,salesman,code,date,address,local,PrentID,Email,postAddress,bank,bankAccount,MSNAddress,WEBAddress,secondlyContact,QQCode,logname,logpassword,customertype) ";
				sql = sql + " values("+StrToInt(Type) + ",'" + dbedtName->Text + "','" + dbeditContact->Text.Trim()+"','" + edtphone->Text + "','";
				sql = sql + edtfax->Text.Trim() + "','" + salesmanID + "','" + edtcode->Text.Trim();
				sql = sql + "',GetDate(),'" +  dbedit->Text.Trim()+ "','" + LocalID + "'," + IntToStr(ParentID)  + ",'" + edemail->Text + "','";
				sql = sql + edpostaddress->Text + "','" + edbank->Text + "','" + edbankaccount->Text + "','" + edmsnaddress->Text + "','";
				sql = sql + edwebaddress->Text + "','" + edsecondcontact->Text + "','" + edqq->Text + "','" + edlogname->Text + "','" + edpassword->Text + "',";
				sql = sql + IntToStr(int(cbtype->Items->Objects[cbtype->ItemIndex])) + ")";
			}
			else
			{
				sql = "Insert into cust_customerinfo(Type,name,contact,telephone,fax,salesman,code,date,address,local,PrentID,Email,postAddress,bank,bankAccount,MSNAddress,WEBAddress,secondlyContact,QQCode,logname,logpassword) ";
				sql = sql + " values("+StrToInt(Type) + ",'" + dbedtName->Text + "','" + dbeditContact->Text.Trim()+"','" + edtphone->Text + "','";
				sql = sql + edtfax->Text.Trim() + "','" + salesmanID + "','" + edtcode->Text.Trim();
				sql = sql + "',GetDate(),'" +  dbedit->Text.Trim()+ "','" + LocalID + "'," + IntToStr(ParentID)  + ",'" + edemail->Text + "','";
				sql = sql + edpostaddress->Text + "','" + edbank->Text + "','" + edbankaccount->Text + "','" + edmsnaddress->Text + "','";
				sql = sql + edwebaddress->Text + "','" + edsecondcontact->Text + "','" + edqq->Text + "','" + edlogname->Text + "','" + edpassword->Text + "')";
			}

			if (Type == 1) {
				sdf = "ȷ�����ӹ�Ӧ��" + dbedtName->Text +"��" ;
			}
			if ((Type == 2) || (Type == 3)) {
				sdf = "ȷ�����ӿͻ�" + dbedtName->Text +"��" ;
			}

			if (MessageBox(0,sdf.c_str() ,"����ȷ��?     " ,MB_ICONQUESTION|MB_OKCANCEL)==1) {
				//qudetail->Active = true;
				/*if (qudetail->State != dsInsert) {
					qudetail->Append();
				}
				qudetail->FieldByName("Type")->AsInteger = Type;
				qudetail->FieldByName("name")->AsString =  dbedtName->Text.Trim();
				qudetail->FieldByName("contact")->AsString =  dbeditContact->Text.Trim();
				qudetail->FieldByName("telephone")->AsString =  edtphone->Text.Trim();
				qudetail->FieldByName("fax")->AsString = edtfax->Text.Trim();
				qudetail->FieldByName("salesman")->AsString   = salesmanID;
				qudetail->FieldByName("code")->AsString = edtcode->Text.Trim();
				qudetail->FieldByName("date")->AsDateTime = Date();
				qudetail->FieldByName("address")->AsString =  dbedit->Text.Trim();
				qudetail->FieldByName("local")->AsString   =  LocalID;
				qudetail->Edit() ;*/
				aqdetail->Close();
				aqdetail->SQL->Clear();
				aqdetail->SQL->Add(sql);
				aqdetail->ExecSQL();
				sql =  "select max(ID) as id from cust_customerinfo";
				aqdetail->Close();
				aqdetail->SQL->Clear();
				aqdetail->SQL->Add(sql);
				aqdetail->Open();
				int customerid = aqdetail->FieldByName("id")->AsInteger ;
				sql = "insert into CUST_CustomerStartMoney(CustomerID) values (" + IntToStr(customerid)  + ")" ;
				aqdetail->Close();
				aqdetail->SQL->Clear();
				aqdetail->SQL->Add(sql);
				aqdetail->ExecSQL();
				this->Close();
			}

	}
	if (modsave == 2) {
		AnsiString sql,sdf;
		sql = "update cust_customerinfo set name = '" +dbedtName->Text +"',Contact = '" + dbeditContact->Text.Trim()+ "',Telephone = '";
		sql = sql + edtphone->Text + "',Fax = '" + edtfax->Text.Trim() + "',Address = '" + dbedit->Text.Trim();
		sql = sql + "',Code = '" + edtcode->Text.Trim() +"',local = '" + CBlocal->Text.Trim() + "',salesman = '" + CBsale->Text.Trim() + "',Email = '";
		sql = sql + edemail->Text + "',postAddress = '" + edpostaddress->Text + "',bank = '" + edbank->Text + "',bankAccount = '" + edbankaccount->Text;
		sql = sql + "',MSNAddress = '" + edmsnaddress->Text + "',WEBAddress = '" + edwebaddress->Text + "',secondlyContact = '";
		sql = sql + edsecondcontact->Text + "',QQCode = '" + edqq->Text + "',logname = '" + edlogname->Text + "',logpassword = '" + edpassword->Text + "'";
		if (cbtype->Text != "") {
			sql = sql + ",customertype = " + IntToStr(int(cbtype->Items->Objects[cbtype->ItemIndex]));
		}
		sql = sql + " where ID = " + ID;

		if (Type == 1) {
			sdf = "ȷ���޸Ĺ�Ӧ��" + dbedtName->Text +"��" ;
		}
		if (Type == 2) {
			sdf = "ȷ���޸Ŀͻ�" + dbedtName->Text +"��" ;
		}

		if (MessageBox(0,sdf.c_str() ,"�޸�ȷ��" ,MB_ICONQUESTION|MB_OKCANCEL)==1) {
			try {
				aqinit->Close();
				aqinit->SQL->Clear();
				aqinit->SQL->Add(sql);
				aqinit->ExecSQL();
				this->Close();
			} catch (Exception &E) {
				MessageBox(0,"�����ݸ�ϵͳ���������й����������޸ģ�","�޸Ĵ���" ,MB_ICONWARNING);
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

void __fastcall TDetaileForm::dbedtNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
    	edtphone->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edtphoneKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		CBlocal->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::dbeditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
    	edpostaddress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::CBlocalKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		dbeditContact->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::dbeditContactKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edsecondcontact->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edtfaxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edemail->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edtcodeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edtfax->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::CBsaleKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edmsnaddress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edsecondcontactKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edtcode->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edemailKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        CBsale->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edmsnaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edqq->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edqqKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edbank->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edbankKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edbankaccount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edbankaccountKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		if (Type == 1) {
			edwebaddress->SetFocus();
		}
		else
		{
        	edlogname->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edlognameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edpassword->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edpasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_RETURN) {
        edwebaddress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edwebaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
    	dbedit->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edpostaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F4) {     //����
		BtnSave->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------
