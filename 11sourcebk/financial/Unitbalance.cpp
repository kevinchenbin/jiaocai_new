//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitbalance.h"
#include "Unitautojie.h"
#include "Unitweijieselect.h"
#include "..\bsadmin\UnitSelectClient.h"
#include "Notedetail.h"
#include "PwdForm.h"
#include "Unittishi.h"
#include   <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RpBase"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpSystem"
#pragma link "RpRave"
#pragma resource "*.dfm"
Tfrmbalance *frmbalance;
//---------------------------------------------------------------------------
__fastcall Tfrmbalance::Tfrmbalance(TComponent* Owner,TADOConnection *cn,int userid,int type,int stgid,bool master)
	: TForm(Owner)
{
  fcon = cn;
  Type = type;
  fstgid = stgid;
  fmaster = master;
  fuserid = userid;
  aquery->Connection = fcon;
  aqhd->Connection = fcon;
  aqdg1->Connection = fcon;
  aquerytotal->Connection = fcon;
  hc = 0;
  AddNew = false;
  if (Type == 1) {
	  this->Caption = "��Ӧ����������";
	  lablename->Caption = "��Ӧ��";
	  spselectClient->Visible = false;
	  edtclient->Visible = false;
	  dg->Columns->Items[1]->Title->Caption = "��ⵥ��";
	  dg->Columns->Items[2]->Title->Caption = "��ⵥ��";
	  dg->Columns->Items[3]->Title->Caption = "�������";
	  dg->Columns->Items[9]->Title->Caption = "��ⵥ��ע";
	  Label21->Caption = "���";
	  cbjieshuantype->Add("�����˿�");
	  cbjieshuantype->Add("����");
	  cbjieshuantype->Add("Ԥ����");
	  cbjieshuantype->Add("�����Գ�");
	  cbjieshuantype->Add("����˿�");
	  Label10->Caption = "������";
	  Label2->Caption = "��Ӧ��";
	  spselect->Caption = "ѡ�������ⵥ";
  }else
  {
		this->Caption = "�ͻ���������";
		lablename->Caption = "�ͻ�";
		cbselect->Visible = false;
		dg->Columns->Items[1]->Title->Caption = "��������";
		dg->Columns->Items[2]->Title->Caption = "��������";
		dg->Columns->Items[3]->Title->Caption = "��������";
		dg->Columns->Items[9]->Title->Caption = "��������ע";
		Label21->Caption = "�տ";
		cbjieshuantype->Add("�տ��˿�");
		cbjieshuantype->Add("����տ�");
		cbjieshuantype->Add("Ԥ�տ�");
		cbjieshuantype->Add("�����Գ�");
	    cbjieshuantype->Add("����˿�");
		Label12->Caption = "Ԥ�տ�";
		Label10->Caption = "�տ���";
		Label2->Caption = "��Ӧ��";
		spselect->Caption = "ѡ����㷢����";
		Label7->Caption = "�տ�����";
		Label24->Caption = "ת��Ԥ�տ�";
  }
  aqdg->Connection = fcon;
  ReadyData();
  selectID = new TStringList();
  save = false;

   AnsiString sql;
   sql = "select value from sys_bsset where name = 'changeDanHaoDisplay'";
   TADOQuery *aq1 = new TADOQuery(NULL);
   aq1->Connection = cn;
   aq1->Close();
   aq1->SQL->Clear();
   aq1->SQL->Add(sql);
   aq1->Open();
   ChangeDisplay = aq1->FieldByName("value")->AsBoolean;

   sql = "select Name from sys_user where id = " + IntToStr(userid);
   aq1->Close();
   aq1->SQL->Clear();
   aq1->SQL->Add(sql);
   aq1->Open();
   edemploy->Text = aq1->FieldByName("Name")->AsAnsiString ;

   sql = "select ID,Name,supshenheipwd,supfanshenpwd,clishenheipwd,clifanshenpwd from SYS_StorageInfo where id = " + IntToStr(fstgid);
   aq1->Close();
   aq1->SQL->Clear();
   aq1->SQL->Add(sql);
   aq1->Open();
   Edit1->Text = aq1->FieldByName("ID")->AsString ;
   Edit2->Text = aq1->FieldByName("Name")->AsString ;
   supshenheipwd  =  aq1->FieldByName("supshenheipwd")->AsString ;
   supfanshenpwd  =  aq1->FieldByName("supfanshenpwd")->AsString ;
   clishenheipwd  =  aq1->FieldByName("clishenheipwd")->AsString ;
   clifanshenpwd  =  aq1->FieldByName("clifanshenpwd")->AsString ;

   if (type == 1) {
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add("select * from sys_bsset where name ='xiaoshudian'");
		aq1->Open();
		Disc =  "###,###,##" + aq1->FieldByName("bk")->AsAnsiString ;
	}
	else
	{
    	aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
		aq1->Open();
		Disc =  "###,###,##" + aq1->FieldByName("bk")->AsAnsiString ;
	}
	if (Disc == "###,###,##0") {
		xiaoshubit = 0;
		cc = "%0.0f";
	}
	else if (Disc == "###,###,##0.0") {
		xiaoshubit = 1;
		cc = "%0.1f";
	}
	else if (Disc == "###,###,##0.00") {
		xiaoshubit = 2;
		cc = "%0.2f";
	}

   delete aq1;
   if (ChangeDisplay) {
		 dg->Columns->Items[1]->Visible = false;
		 dg->Columns->Items[2]->Visible = true;
   }
   else
   {
		dg->Columns->Items[1]->Visible = true;
		dg->Columns->Items[2]->Visible = false;
   }
   ClientID = 1;
}
void Tfrmbalance::ReadyData()
{
   TADOQuery *aq = new TADOQuery(this);
   aq->Connection = fcon;
   String sqlstr;
   if (Type == 1) {
		sqlstr = "select ID,Name from CUST_CustomerInfo where type = 1 and name <> '' order by name ";
   }
   else
   {
		sqlstr = "select ID,Name from CUST_CustomerInfo where type in(2,3)  order by name  ";
   }
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sqlstr);
   aq->Open();

   while(!aq->Eof)
   {
	  cbselect->AddObject(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
	  aq->Next();
   }
   delete aq;
   dtp->Date = Date();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbalance::BtnNewClick(TObject *Sender)
{
	 if (MessageBoxA(0,"ȷ��Ҫ����µ���","��������",MB_ICONQUESTION|MB_OKCANCEL)==1 ) {
		Enable(true);
		save = false;
		BtnOK->Enabled = true;
		BtnCancel->Enabled = false;
		BtnDelete->Enabled = true;
		cbselect->ItemIndex = -1;
		cbjieshuantype->ItemIndex = -1;
		cbmethod->ItemIndex = -1;
		editnum->Text = "";
		editstate->Text = "";
		edithukuan->Text = "0.00";
		membk->Text = "";
		editmoney->Text = "0.00";
		editmayang->Text = "0.00";
		editshiyang->Text = "0.00";
		editaddcost->Text = "0.00";
		edityijie->Text = "0.00";
		editweijie->Text = "0.00";
		editthistime->Text = "0.00";
		edzryuhu->Text = "0.00";
		edduicong->Text = "0.00";
		editmoney->Enabled = true;
		spselect->Enabled = true;
		sbautojieshuan->Enabled = true;
		autobt->Enabled = true;
		btduicong->Enabled = true;
		edtQryVendor->Enabled = true;
		spselectClient->Enabled = true;
		edtclient->Enabled = true;
		aqdg->Close();
		dtp->Date = Date();
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		String sql;
		if (Type == 1) {
			sql = "select * from CUST_CustomerInfo where Type = 1 order by Name";
		}
		else
		{
			sql = " select * from CUST_CustomerInfo where Type in (2,3) order by Name ";
		}
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();

		while(!aq->Eof)
		{
			cbselect->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
			aq->Next();
		}
		delete aq;
		aqdg1->Active = false;
		aqdg->Active = false;
		cbselect->Clear();
		edtQryVendor->Text = "";
		cbselect->Text = "";
		edtclient->Text = "";
		edityu->Text = "0.00";
		editweijiedan->Text = "0.00";
		edityuhu->Text = "0.00";
		edityinghu->Text = "0.00";
		ts = 0 ;
		hc = 0;
		edtQryVendor->SetFocus();
		dbnv->Enabled = false;
	 }
}
void Tfrmbalance::Excute(String sql)
 {
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
 }
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnSaveClick(TObject *Sender)
{
  if (!save) {

      if (Type == 1 && cbselect->Text == "") {
			MessageBox(0,"��ѡ����㹩Ӧ�̣�","��������",MB_ICONASTERISK|MB_OK);
			return;
	  }
	  if (Type == 2 && edtclient->Text == "") {
			MessageBox(0,"��ѡ�����ͻ���","��������",MB_ICONASTERISK|MB_OK);
			return;
	  }
	  if (cbjieshuantype->Text  == "") {
		  MessageBox(0,"�������Ͳ���Ϊ�գ�","��������",MB_ICONASTERISK|MB_OK);
		  return;
	  }
	  if (cbmethod->Text == "") {
		  MessageBox(0,"���㷽ʽ����Ϊ�գ�","��������",MB_ICONASTERISK|MB_OK);
		  return;
	  }

		String sqlstr;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		Code = NoteCode::BuildCode(aq, GetDBTime(aq), 0, "FN_CUSEndMoneyDocuments", "MoneyCode");
		delete aq;
		editnum->Text = Code;  //���ɵ���

		editnum->Text = editnum->Text.SubString(2,editnum->Text.Length() );                                            //0Ϊû����� 1 �����
		editstate->Text = "δ���";																	//�����µ�

		sqlstr = "insert into FN_CUSEndMoneyDocuments (MoneyCode,date,state,type,userid,stgid) values ("+Code+",getdate(),0," + IntToStr(Type) + "," + IntToStr(fuserid)  + "," + IntToStr(fstgid) + ")";

		Excute(sqlstr);

	  String sql;
	  sql ="update FN_CUSEndMoneyDocuments set custmerName='" ;
	  if (editstate->Text == "δ���") {
			if (Type == 1) {
				sql = sql + cbselect->Text + "', clearingtype='"+cbjieshuantype->Text + "', clearingstyle='" +cbmethod->Text +"', state=0,remarks = '"  + membk->Text + "'";
			}
			else
			{
				sql = sql + edtclient->Text + "', cusid = " + IntToStr(ClientID) + ",clearingtype='"+cbjieshuantype->Text + "', clearingstyle='" +cbmethod->Text +"', state=0,remarks = '"  + membk->Text + "'";
			}
	  } else if (editstate->Text == "�����") {
			if (Type == 1) {
				sql = sql + cbselect->Text + "', clearingtype='"+cbjieshuantype->Text + "', clearingstyle='" +cbmethod->Text +"', state=1,remarks = '"  + membk->Text + "'";
			}
			else
			{
				sql = sql + edtclient->Text + "', cusid = " + IntToStr(ClientID) + ",clearingtype='"+cbjieshuantype->Text + "', clearingstyle='" +cbmethod->Text +"', state=1,remarks = '"  + membk->Text + "'";
			}
	  }

  //	  sql = sql + " ,payment = '" + edithukuan->Text;
	  sql = sql + " ,type = " + IntToStr(Type);
	  sql = sql + ", paymentdate = '" + dtp->Date  + "'";
	  sql = sql + ",jiespz = '" + edjspz->Text + "'";
	  sql = sql + " where moneycode = '" + Code+"'";
	  Excute(sql);
	  Enable(false);
	  save = true;

					 //�����ݼ�
	  DisplayDetail(editnum->Text);
	  MessageBox(0,"���㵥�����ɳɹ�!","��λ��������",MB_ICONASTERISK);

       selectID->Clear();
	   editmoney->Enabled = true;

       editmoney->SetFocus();
   }else
   {
		String sql;
		sql ="update FN_CUSEndMoneyDocuments set jiespz = '" + edjspz->Text + "',Remarks = '" + membk->Text + "',clearingstyle = '" + cbmethod->Text + "'," + "clearingtype = '" + cbjieshuantype->Text + "' " ;
		sql = sql + " where moneycode = " + editnum->Text ;
		Excute(sql);
		//editmoney->SetFocus();
   }
}
//---------------------------------------------------------------------------
void Tfrmbalance::Enable(BOOL var)
{
	cbselect->Enabled  = var;
	edtQryVendor->Enabled = var;
	spselectClient->Enabled = var;
	edtclient->Enabled = var;
	cbjieshuantype->Enabled = var;
	//cbmethod->Enabled = var;
	//edityu->Enabled = var;
	//edityinghu->Enabled = var;
	//editnum->Enabled = var;
	//editstate->Enabled = var;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbalance::editmoneyKeyPress(TObject *Sender, wchar_t &Key)
{
	FLOAT hukuan;
	AnsiString sql;
	String sqlupdate;
	float overage = 0.00;


	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == VK_RETURN) {
		if (aqdg->IsEmpty() && (cbjieshuantype->ItemIndex != 2 && cbjieshuantype->ItemIndex != 4)) {
			MessageBox(0,"��ѡ����㵥��!","��λ��������",MB_ICONASTERISK);
			editmoney->Text = "0.00";
		return;
	}


	  FLOAT num;
	  if (editnum->Text =="") {
		  return;
	  }
	  if (editstate->Text =="�����") {
		  MessageBox(0,"���ŵ�������ˣ������ٽ���!","��λ��������",MB_ICONASTERISK);
		  return;
	  }
	  try {
		num = StrToFloat(editmoney->Text);
		editmoney->Text = FormatFloat("0.00",num);
	  } catch (...) {
			MessageBox(0,"��������ȷ�Ľ��!","��λ��������",MB_ICONASTERISK);
			return;
	  }

		hukuan = aqdg1->FieldByName("nochecked")->AsFloat ;
		if (cbjieshuantype->ItemIndex == 0)   //�����˿�
		{
        	if (num > 0 && hukuan < 0) {
				num = 0-num;
				editmoney->Text = "-" + editmoney->Text ;
			}
			if ((num > 0 && hukuan < 0) || (num < 0 && hukuan > 0)) {
				editmoney->Text = "0.00";
				return;
			}
		}


		if (Disc == "0.0") {
			if ((num - hukuan )>0.1 && (cbjieshuantype->ItemIndex != 2 && cbjieshuantype->ItemIndex != 4)) {
				MessageBox(0,"���������,�����¸���!","��λ��������",MB_ICONASTERISK);
				editmoney->Text = "0.00";
				editmoney->SetFocus();
				return;
			}
		}
		else if (Disc == "0") {
			if ((num - hukuan )>1 && (cbjieshuantype->ItemIndex != 2 && cbjieshuantype->ItemIndex != 4)) {
				MessageBox(0,"��������࣬�����¸���!","��λ��������",MB_ICONASTERISK);
				editmoney->Text = "0.00";
				editmoney->SetFocus();
				return;
			}
		}
		else if ((num - hukuan )>0 && (cbjieshuantype->ItemIndex != 2 && cbjieshuantype->ItemIndex != 4)) {
				MessageBox(0,"���������,�����¸���!","��λ��������",MB_ICONASTERISK);
				editmoney->Text = "0.00";
				editmoney->SetFocus();
				return;
			}


		   switch (cbjieshuantype->ItemIndex) {
				case 0:                //�����˿�
					aqdg1->Edit();

					if (Disc == "0.0") {
						if (abs(num - hukuan)<0.1) {
							aqdg1->FieldByName("thistime")->AsFloat = hukuan + aqdg1->FieldByName("hongcong")->AsFloat;
						}
						else
						{
							aqdg1->FieldByName("thistime")->AsFloat = num + aqdg1->FieldByName("hongcong")->AsFloat;

						}
					}
					else if (Disc == "0") {
						if (abs(num - hukuan)<1) {
							aqdg1->FieldByName("thistime")->AsFloat = hukuan + aqdg1->FieldByName("hongcong")->AsFloat ;

						}
						else
						{
							aqdg1->FieldByName("thistime")->AsFloat = num + aqdg1->FieldByName("hongcong")->AsFloat;

						}
					}
					else {
						aqdg1->FieldByName("thistime")->AsFloat = num + aqdg1->FieldByName("hongcong")->AsFloat;

					}
					aqdg1->UpdateBatch(arCurrent);
                    aqdg->Refresh();
                    sql = "update FN_CUSEndMoneyDocuments set yuhu = 0 where MoneyCode = " + editnum->Text ;
					Excute(sql);

					break;
				case 1:     //�����
					edityu->Text = StringReplace(edityu->Text , ",","",TReplaceFlags()<<rfReplaceAll);
						edithukuan->Text = StringReplace(edithukuan->Text , ",","",TReplaceFlags()<<rfReplaceAll);
						overage = StrToFloat(editmoney->Text) + StrToFloat(edithukuan->Text) - aqdg1->FieldByName("thistime")->AsFloat - StrToFloat(edityu->Text);
						if ( overage > 0.01) {
							if (!MessageBoxA(0,"���㣬�Ƿ�¼����������㣿","��ʾ",MB_ICONQUESTION||MB_YESNO) == 1)
							{
								editmoney->Text = "0.00";
								editmoney->SetFocus();
								return;
							}
							sql = "update FN_CUSEndMoneyDocuments set overage = " + FloatToStr(overage)  + " where MoneyCode = " + editnum->Text ;
							Excute(sql);
						}
						else
						{
							sql = "update FN_CUSEndMoneyDocuments set overage = 0 where MoneyCode = " + editnum->Text ;
							Excute(sql);
						}
						aqdg1->Edit();
						aqdg1->FieldByName("thistime")->AsFloat = StrToFloat(editmoney->Text) + aqdg1->FieldByName("hongcong")->AsFloat;
						aqdg1->UpdateBatch(arCurrent);
						aqdg->Refresh();
					break;
				 case 2:                 ////Ԥ����

					   sql = "update FN_CUSEndMoneyDocuments set yuhu = " + StringReplace(editmoney->Text , ",","",TReplaceFlags()<<rfReplaceAll) + " where MoneyCode = " + editnum->Text ;
					   Excute(sql);
					   //edityuhu->Text =  editmoney->Text;
					   break;
				 case 4:                 ////����˿�
					if (num >= 0) {
                    	edityu->Text = StringReplace(edityu->Text , ",","",TReplaceFlags()<<rfReplaceAll);

						if (StrToFloat(editmoney->Text) > StrToFloat(edityu->Text)) {
							MessageBox(0,"����!","��λ��������",MB_ICONASTERISK);
							editmoney->Text = "0.00";
							editmoney->SetFocus();
							return;
						} else
						{
							sql = "update FN_CUSEndMoneyDocuments set yuhu = " + StringReplace(editmoney->Text , ",","",TReplaceFlags()<<rfReplaceAll) + " where MoneyCode = " + editnum->Text ;
							Excute(sql);
						}
					}
					else
					{
                    	editmoney->Text = "0.00";
					}

			break;
		}
		Displaytotal(editnum->Text);
	}
}
//---------------------------------------------------------------------------
void Tfrmbalance::shenhe()  //��ǰѡ�еĵ���ID������������
{
  String sql;
   AnsiString zryuhu;
   float yy = 0.00;
   switch (cbjieshuantype->ItemIndex) {
		   case 0:       //�����˿�
		   case 3:       //�Գ�

			 aqdg->First();
			  while(!aqdg->Eof)
			  {
				  sql = "exec JieShuan '"+aqdg->FieldByName("stgntcode")->AsAnsiString+"','"+aqdg->FieldByName("thistime")->AsAnsiString+"',"+IntToStr(Type);
				  Excute(sql);
				  aqdg->Edit();
				  aqdg->FieldByName("checked")->AsAnsiString =  FormatFloat("0.00",aqdg->FieldByName("thistime")->AsFloat) ;
				  aqdg->FieldByName("nochecked")->AsAnsiString = FormatFloat("0.00",aqdg->FieldByName("nochecked")->AsFloat - aqdg->FieldByName("thistime")->AsFloat) ;
				  aqdg->UpdateBatch(arCurrent);

				  aqdg->Next();

			   }
			   //aqdg->Active = false;
			   //aqdg->Active = true;

			   //����û�н�Ŀ�
			   editweijiedan->Text = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edityinghu->Text = StringReplace(edityinghu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edithukuan->Text = StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);

			   editweijiedan->Text = FormatFloat("0.00",StrToFloat(editweijiedan->Text) - StrToFloat(edithukuan->Text));
			   edityinghu->Text =  FormatFloat("0.00",StrToFloat(edityinghu->Text) - StrToFloat(edithukuan->Text));

			   zryuhu = StringReplace(edzryuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   if (StrToFloat(zryuhu) > 0.00 ) {
					sql = "update CUST_CustomerStartMoney set totalyue = totalyue + "+ zryuhu +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
					Excute(sql);
					edityuhu->Text = StringReplace(edityuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
					edityuhu->Text = FormatFloat("0.00",StrToFloat(edityuhu->Text)+ StrToFloat(zryuhu));
					edityu->Text = StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
					edityu->Text = FormatFloat("0.00",StrToFloat(edityu->Text)+ StrToFloat(zryuhu));
			   }
			  break;
		   case 1:              //�����

			  aqdg->First();
			  while(!aqdg->Eof)
			  {
				  sql = "exec JieShuan '"+aqdg->FieldByName("stgntcode")->AsAnsiString+"','"+aqdg->FieldByName("thistime")->AsAnsiString+"',"+IntToStr(Type);
				  Excute(sql);
				  aqdg->Edit();
				  aqdg->FieldByName("checked")->AsAnsiString =  FormatFloat("0.00",aqdg->FieldByName("thistime")->AsFloat);
				  aqdg->FieldByName("nochecked")->AsAnsiString =  FormatFloat("0.00",aqdg->FieldByName("nochecked")->AsFloat - aqdg->FieldByName("thistime")->AsFloat);
				  aqdg->UpdateBatch(arCurrent);
				  aqdg->Next();
			   }

				edithukuan->Text = StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);
				edzryuhu->Text = StringReplace(edzryuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
				edityu->Text = StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
				yy = StrToFloat(edityu->Text) - StrToFloat(edithukuan->Text);

				if (yy > 0) {
					//yy =  yy - StrToFloat(edzryuhu->Text);
					sql = "update CUST_CustomerStartMoney set totalyue = totalyue - " + edithukuan->Text + " where customerid ="+IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
					Excute(sql);
				}
				else
				{
					yy =  StrToFloat(edityu->Text) - StrToFloat(edzryuhu->Text) ;
					sql = "update CUST_CustomerStartMoney set totalyue = totalyue - " + FloatToStr(yy) + " where customerid ="+IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
					Excute(sql);
				}

				edityu->Text = FormatFloat("0.00",StrToFloat(yy));

			   //����û�н�Ŀ�
				editweijiedan->Text = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
				edityinghu->Text = StringReplace(edityinghu->Text,",","",TReplaceFlags()<<rfReplaceAll);

			   editweijiedan->Text = FormatFloat("0.00",StrToFloat(editweijiedan->Text) - StrToFloat(edithukuan->Text));
			   edityinghu->Text =  FormatFloat("0.00",StrToFloat(edityinghu->Text) - StrToFloat(edithukuan->Text));

			  break;
		   case 2:                       //Ԥ����

			   edithukuan->Text = StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edityuhu->Text = StringReplace(edityuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   editmoney->Text = StringReplace(editmoney->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edityuhu->Text = FormatFloat("0.00",StrToFloat(edityuhu->Text)+ StrToFloat(edithukuan->Text));
			   edityu->Text = StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edityu->Text = FormatFloat("0.00",StrToFloat(edityu->Text)+ StrToFloat(edithukuan->Text));
			   sql = "update CUST_CustomerStartMoney set totalyue = totalyue + "+ StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll) +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
			   Excute(sql);

			  break;
		   case 4:                       //����˿�
			   edithukuan->Text = StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edityuhu->Text = StringReplace(edityuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   editmoney->Text = StringReplace(editmoney->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edityuhu->Text = FormatFloat("0.00",StrToFloat(edityuhu->Text)- StrToFloat(edithukuan->Text));
               edityu->Text = StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edityu->Text = FormatFloat("0.00",StrToFloat(edityu->Text) - StrToFloat(edithukuan->Text));
			   sql = "update CUST_CustomerStartMoney set totalyue = totalyue - "+ StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll) +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
			   Excute(sql);

			  break;
   default:
	   ;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnOKClick(TObject *Sender)
{
  String sql;
  if(editnum->Text == "")
  {
		return;
  }
  if (editstate->Text == "�����") {
      return;
  }
	TfrmPwd* frm = new TfrmPwd(this);
	if (mrOk == frm->ShowModal())
	{
		if (Type == 1) {                               //��Ӧ��
			if (frm->GetPassword() != supshenheipwd)
			{
				MessageBoxA(0,"�������","����",MB_ICONASTERISK);
				return;
			}
		}
		else
		{
			if (frm->GetPassword() != clishenheipwd)
			{
				MessageBoxA(0,"�������","����",MB_ICONASTERISK);
				return;
			}
		}
	}

  if(MessageBoxA(0,"ȷ��Ҫ��˸��ŵ�����","��������",MB_ICONQUESTION |MB_OKCANCEL )==1 )
  {
	shenhe();
	sql = "update FN_CUSEndMoneyDocuments set state=1  " ;
	sql = sql + " where moneycode = '" + editnum->Text+"'";
	Excute(sql);

	QryNthead(editnum->Text );

	/*editstate->Text = "�����";
	Enable(0);
	dtp->Enabled = false;
	editmoney->Enabled = false;
	sbautojieshuan->Enabled = false;
	autobt->Enabled = false;
	spselect->Enabled  = false;                
	if (cbjieshuantype->Text == "�����Գ�") {
		btduicong->Enabled = false;    
	}
	BtnOK->Enabled = false;
	BtnCancel->Enabled = true;
	BtnDelete->Enabled = false;

	Displaytotal(editnum->Text);
	DisplayDetail(editnum->Text);  */


  //	MessageBoxA(0,"�ɹ���ˣ�","��������",MB_ICONEXCLAMATION);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnDeleteClick(TObject *Sender)
{
	int i;
	i = dg->SelectedRows->Count;

	if (dg->DataSource->DataSet->IsEmpty() ) {
		return;
	}
	if (editstate->Text == "�����") {
		return;
	}
	AnsiString sql;
	if (cbjieshuantype->ItemIndex == 3) {
		if( MessageBoxA(0,"��������Ϊ�����Գ�ʱ���޷����һ��ɾ�������ȷ������ɾ�����м�¼��","��������",MB_ICONQUESTION |MB_OKCANCEL )==1 )
		{
			sql = "delete from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + editnum->Text ;
			Excute(sql);

			editmoney->Text = FormatFloat(Disc,aqdg1->FieldByName("thistime")->AsFloat);
			if (cbjieshuantype->ItemIndex == 0) {      //����Ԥ���
				sql = "update FN_CUSEndMoneyDocuments set yuhu = 0 where MoneyCode = " + editnum->Text ;
				Excute(sql);
			}
			DisplayDetail(editnum->Text);
			Displaytotal(editnum->Text);
		}
	}
	else
	{
		if( MessageBoxA(0,"ȷ��ɾ������¼��","��������",MB_ICONQUESTION |MB_OKCANCEL )==1 )
		{
			if (dg->SelectedRows->Count == 0)
			{
				i = selectID->IndexOf(dg->DataSource->DataSet->FieldByName("stgntcode")->AsAnsiString);
				if (i != -1) {
					selectID->Delete(i);
				}
				sql = "delete from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + editnum->Text + " and stgntcode = " + aqdg1->FieldByName("stgntcode")->AsAnsiString;
				Excute(sql);
			}
			else if (dg->SelectedRows->Count > 0)
			{
				aqdg1->Bookmark = dg->SelectedRows->Items[0];
				i = selectID->IndexOf(dg->DataSource->DataSet->FieldByName("stgntcode")->AsAnsiString);
				if (i != -1) {
					selectID->Delete(i);
				}
				sql = "delete from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + editnum->Text + " and stgntcode = " + aqdg1->FieldByName("stgntcode")->AsAnsiString;
				Excute(sql);

				for (int j=1; j < dg->SelectedRows->Count; j++)
				{
					aqdg1->Bookmark = dg->SelectedRows->Items[j];
					i = selectID->IndexOf(dg->DataSource->DataSet->FieldByName("stgntcode")->AsAnsiString);
					if (i != -1) {
						selectID->Delete(i);
					}
					sql = "delete from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + editnum->Text + " and stgntcode = " + aqdg1->FieldByName("stgntcode")->AsAnsiString;
					Excute(sql);
				}
			}
			else
				return;

			editmoney->Text = FormatFloat(Disc,aqdg1->FieldByName("thistime")->AsFloat);
			if (cbjieshuantype->ItemIndex == 0) {      //����Ԥ���
				sql = "update FN_CUSEndMoneyDocuments set yuhu = 0 where MoneyCode = " + editnum->Text ;
				Excute(sql);
			}
			DisplayDetail(editnum->Text);
			Displaytotal(editnum->Text);
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnClick(TObject *Sender)
{
  /*String Danhao;
  Tfrmweishenhe *frm = new  Tfrmweishenhe(this,fcon,Type);
  frm->ShowModal();
  Danhao = frm->Danhao ;
  if (Danhao!="") {
	  QryNthead(Danhao);
  }
  delete frm;    */


	String Codestr,sqlstr;
	TfrmQryNoteCode1 *frm = new TfrmQryNoteCode1(this,Type,fcon);
	frm->Caption = "δ���";
	frm->weishenhei = true;
	frm->SetstgID(fstgid);
	frm->master = fmaster;
	if (mrOk == frm->ShowModal() ) {
		Codestr =  frm->GetNoteCode();
		sqlstr = frm->GetSqlWhere();
		QryNthead(Codestr);
		dbnv->Enabled = true;
		aqhd->Close();
		aqhd->SQL->Clear();
		aqhd->SQL->Add(sqlstr);
		aqhd->Open();
	}
	delete frm;
}

//---------------------------------------------------------------------------
void Tfrmbalance::DisplayDetail(String Danhao)
{
	String sql;

	if (Type == 1) {
		if (editstate->Text == "�����") {
        	sql = "select rank() over(order by FN_CUSEndMoneyDtails.id) as xuhao,FN_CUSEndMoneyDtails.id,FN_CUSEndMoneyDtails.EndMoneyDocumentID,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.hdtime,FN_CUSEndMoneyDtails.thistime,FN_CUSEndMoneyDtails.type,FN_CUSEndMoneyDtails.bk,FN_CUSEndMoneyDtails.CodeStr,BS_StorageNoteHeader.fapiaotext ,BS_StorageNoteHeader.Remarks,"
				"BS_StorageNoteHeader.totalfixedprice,BS_StorageNoteHeader.totaldiscountedprice,BS_StorageNoteHeader.addcosts,BS_StorageNoteHeader.checked,BS_StorageNoteHeader.nochecked,BS_StorageNoteHeader.totalamount,FN_CUSEndMoneyDtails.hongcong "
				" from FN_CUSEndMoneyDtails left join BS_StorageNoteHeader on FN_CUSEndMoneyDtails.stgntcode = BS_StorageNoteHeader.StgNtCode where EndMoneyDocumentID = " + Danhao + " order by FN_CUSEndMoneyDtails.id asc";
		}
		else
		{
        	sql = "select rank() over(order by FN_CUSEndMoneyDtails.id) as xuhao,FN_CUSEndMoneyDtails.id,FN_CUSEndMoneyDtails.EndMoneyDocumentID,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.hdtime,FN_CUSEndMoneyDtails.thistime,FN_CUSEndMoneyDtails.type,FN_CUSEndMoneyDtails.bk,FN_CUSEndMoneyDtails.CodeStr,BS_StorageNoteHeader.fapiaotext ,BS_StorageNoteHeader.Remarks,"
				"BS_StorageNoteHeader.totalfixedprice,BS_StorageNoteHeader.totaldiscountedprice,BS_StorageNoteHeader.addcosts,BS_StorageNoteHeader.checked,BS_StorageNoteHeader.nochecked - FN_CUSEndMoneyDtails.hongcong as nochecked,BS_StorageNoteHeader.totalamount,FN_CUSEndMoneyDtails.hongcong "
				" from FN_CUSEndMoneyDtails left join BS_StorageNoteHeader on FN_CUSEndMoneyDtails.stgntcode = BS_StorageNoteHeader.StgNtCode where EndMoneyDocumentID = " + Danhao + " order by FN_CUSEndMoneyDtails.id asc";
		}
	}
	else
	{
		if (editstate->Text == "�����") {
        	sql = "select rank() over(order by FN_CUSEndMoneyDtails.id) as xuhao,FN_CUSEndMoneyDtails.id,FN_CUSEndMoneyDtails.EndMoneyDocumentID,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.hdtime,FN_CUSEndMoneyDtails.thistime,FN_CUSEndMoneyDtails.type,FN_CUSEndMoneyDtails.bk,FN_CUSEndMoneyDtails.CodeStr,BS_WsaleNoteHeader.fapiaotext ,BS_WsaleNoteHeader.Remarks,"
				"BS_WsaleNoteHeader.fixedprice as totalfixedprice,BS_WsaleNoteHeader.discountedprice as totaldiscountedprice,BS_WsaleNoteHeader.addcosts,BS_WsaleNoteHeader.checked,BS_WsaleNoteHeader.nochecked,BS_WsaleNoteHeader.totalamount,FN_CUSEndMoneyDtails.hongcong "
				" from FN_CUSEndMoneyDtails left join BS_WsaleNoteHeader on FN_CUSEndMoneyDtails.stgntcode = BS_WsaleNoteHeader.WsaleNtCode where EndMoneyDocumentID =  " + Danhao + " order by FN_CUSEndMoneyDtails.id asc";
		}
		else
		{
        	sql = "select rank() over(order by FN_CUSEndMoneyDtails.id) as xuhao,FN_CUSEndMoneyDtails.id,FN_CUSEndMoneyDtails.EndMoneyDocumentID,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.hdtime,FN_CUSEndMoneyDtails.thistime,FN_CUSEndMoneyDtails.type,FN_CUSEndMoneyDtails.bk,FN_CUSEndMoneyDtails.CodeStr,BS_WsaleNoteHeader.fapiaotext ,BS_WsaleNoteHeader.Remarks,"
				"BS_WsaleNoteHeader.fixedprice as totalfixedprice,BS_WsaleNoteHeader.discountedprice as totaldiscountedprice,BS_WsaleNoteHeader.addcosts,BS_WsaleNoteHeader.checked,BS_WsaleNoteHeader.nochecked - FN_CUSEndMoneyDtails.hongcong as nochecked ,BS_WsaleNoteHeader.totalamount,FN_CUSEndMoneyDtails.hongcong "
				" from FN_CUSEndMoneyDtails left join BS_WsaleNoteHeader on FN_CUSEndMoneyDtails.stgntcode = BS_WsaleNoteHeader.WsaleNtCode where EndMoneyDocumentID =  " + Danhao + " order by FN_CUSEndMoneyDtails.id asc";
		}
	}
	aqdg1->Close();
	aqdg1->SQL->Clear();
	aqdg1->SQL->Add(sql);
	aqdg1->Open();

	sql = "select * from FN_CUSEndMoneyDtails where EndMoneyDocumentID =  " + Danhao + " order by id asc";
	aqdg->Close();
	aqdg->SQL->Clear();
	aqdg->SQL->Add(sql);
	aqdg->Open();
	selectID->Clear();
	while (!aqdg->Eof )
	{
		selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
		aqdg->Next();
	}

	Enable(0);
	if (aqdg1->IsEmpty() ) {
		cbjieshuantype->Enabled = true;
	}
	else
	{
    	cbjieshuantype->Enabled = false;
	}

	((TFloatField *)aqdg1->FieldByName("totalfixedprice"))->DisplayFormat = "###,###,##0.00";
	((TFloatField *)aqdg1->FieldByName("totaldiscountedprice"))->DisplayFormat = Disc;
	((TFloatField *)aqdg1->FieldByName("addcosts"))->DisplayFormat = Disc;
	((TFloatField *)aqdg1->FieldByName("checked"))->DisplayFormat = Disc;
	((TFloatField *)aqdg1->FieldByName("nochecked"))->DisplayFormat = Disc;
	((TFloatField *)aqdg1->FieldByName("totalamount"))->DisplayFormat = "###,###,##0";
	((TFloatField *)aqdg1->FieldByName("thistime"))->DisplayFormat = Disc;
	editmoney->Text = FormatFloat(Disc,aqdg1->FieldByName("thistime")->AsFloat);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::searchClick(TObject *Sender)
{
	String Codestr,sqlstr;
	TfrmQryNoteCode1 *frm = new TfrmQryNoteCode1(this,Type,fcon);
	frm->SetstgID(fstgid);
	frm->master = fmaster;
	if (mrOk == frm->ShowModal() ) {
		Codestr =  frm->GetNoteCode();
		sqlstr = frm->GetSqlWhere();
		QryNthead(Codestr);
		dbnv->Enabled = true;
		aqhd->Close();
		aqhd->SQL->Clear();
		aqhd->SQL->Add(sqlstr);
		aqhd->Open();
	}
	delete frm;

}
//---------------------------------------------------------------------------
void Tfrmbalance::QryNthead(String code)
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	String sql;

	cbselect->Clear();
	ReadyData();
	edtQryVendor->Text = "";

	sql = "select custmername,sys_user.name as opname,cusid,yuhu,date,jiespz,Remarks,payment,clearingtype,clearingstyle,Convert(varchar(20),date,111) as date,case state when 0 then 'δ���' when 1 then '�����' end as state,remarks from FN_CUSEndMoneyDocuments left join sys_user on FN_CUSEndMoneyDocuments.userid = sys_user.id ";
	sql = sql + " where moneycode = " + code+ " and type = " + IntToStr(Type) ;
	aq->SQL->Add(sql);
	aq->Open();

	if (aq->IsEmpty() ) {
		MessageBox(0,"���޴˵�!","��λ��������",MB_ICONASTERISK);
		delete aq;
		return;
	}
	if (Type == 1 ) {
    	cbselect->ItemIndex =  cbselect->Items->IndexOf(aq->FieldByName("custmername")->AsAnsiString);
	}
	else
	{
		ClientID = aq->FieldByName("cusid")->AsInteger ;
		cbselect->ItemIndex = cbselect->Items->IndexOfObject((TObject*)ClientID);
		ClientView();
	}

	//cbselect->OnChange(this) ;
	cbselect->OnSelect(this);
	cbjieshuantype->Text =  aq->FieldByName("clearingtype")->AsAnsiString ;
	cbmethod->Text = aq->FieldByName("clearingstyle")->AsAnsiString ;
	editnum->Text = code ;
	dtp->Date = aq->FieldByName("date")->AsDateTime ;
	membk->Text =  aq->FieldByName("remarks")->AsAnsiString ;
	if (aq->FieldByName("clearingtype")->AsAnsiString == "Ԥ����" ||aq->FieldByName("clearingtype")->AsAnsiString == "Ԥ�տ�" ) {
		editmoney->Text =  aq->FieldByName("yuhu")->AsAnsiString ;
	}

	edemploy->Text = aq->FieldByName("opname")->AsAnsiString ;
	editstate->Text = aq->FieldByName("state")->AsAnsiString ;
	membk->Text = aq->FieldByName("Remarks")->AsAnsiString ;
	edjspz->Text = aq->FieldByName("jiespz")->AsAnsiString ;

	if (editstate->Text == "�����") {
	   editmoney->Enabled = false;
	   spselect->Enabled  = false;
	   sbautojieshuan->Enabled  = false;
	   autobt->Enabled = false;
	   BtnOK->Enabled = false;
	   BtnDelete->Enabled = false;
	   BtnCancel->Enabled = true;
	}else if (editstate->Text == "δ���") {
		editmoney->Enabled = true;
		spselect->Enabled  = true;
		sbautojieshuan->Enabled  = true;
		autobt->Enabled = true;
		BtnOK->Enabled = true;
		BtnDelete->Enabled = true;
		BtnCancel->Enabled = false;
	}
	btduicong->Enabled = false;
	if (cbjieshuantype->Text=="Ԥ����" || cbjieshuantype->Text=="Ԥ�տ�" || cbjieshuantype->Text=="����˿�" || cbjieshuantype->Text=="�����Գ�") {
		spselect->Enabled  = false;
		sbautojieshuan->Enabled  = false;
		autobt->Enabled = false;
	}
	if (cbjieshuantype->ItemIndex == 3 && editstate->Text == "δ���") {
		btduicong->Enabled = true;
        editmoney->Enabled = false;
	}

	//cbselect->OnSelect(this) ;
	//cbselect->OnChange(this) ;
	DisplayDetail(code);
	Displaytotal(code);
	save = true;
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnCancelClick(TObject *Sender)
{
  String sql;
  if(editnum->Text == "")
  {
    return;
  }
  if (editstate->Text == "δ���") {
      return;
  }

	TfrmPwd* frm = new TfrmPwd(this);
	if (mrOk == frm->ShowModal())
	{
		if (Type == 1) {                               //��Ӧ��
			if (frm->GetPassword() != supfanshenpwd)
			{
				MessageBoxA(0,"�������","����",MB_ICONASTERISK);
				return;
			}
		}
		else
		{
			if (frm->GetPassword() != clifanshenpwd)
			{
				MessageBoxA(0,"�������","����",MB_ICONASTERISK);
				return;
			}
		}
	}

  if(MessageBoxA(0,"ȷ��Ҫ����˸��ŵ�����","��������",MB_ICONQUESTION |MB_OKCANCEL )==1 )
  {
	 String sql;
	 AnsiString zryuhu;
	 float yy = 0.00;
	 switch (cbjieshuantype->ItemIndex) {
		   case 0:      //�����˿�
           case 3:     //�Գ�
		   	aqdg->First();
			  while(!aqdg->Eof)
			  {
				  sql = "exec fajieshan '"+aqdg->FieldByName("stgntcode")->AsAnsiString+"','"+aqdg->FieldByName("thistime")->AsAnsiString+"',"+IntToStr(Type);
				  Excute(sql);
				  aqdg->Edit();
				  aqdg->FieldByName("checked")->AsAnsiString = FloatToStr(aqdg->FieldByName("checked")->AsFloat -  aqdg->FieldByName("thistime")->AsFloat) ;
				  aqdg->FieldByName("nochecked")->AsAnsiString =  FloatToStr(aqdg->FieldByName("nochecked")->AsFloat + aqdg->FieldByName("thistime")->AsFloat);
				  aqdg->UpdateBatch(arCurrent);
				  aqdg->Next();
			   }

			   //����û�н�Ŀ�
			   editweijiedan->Text = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edityinghu->Text =StringReplace(edityinghu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edithukuan->Text =StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   editweijiedan->Text = FloatToStr(StrToFloat(editweijiedan->Text) + StrToFloat(edithukuan->Text));
			   edityinghu->Text =  FloatToStr(StrToFloat(edityinghu->Text) + StrToFloat(edithukuan->Text));

			   zryuhu = StringReplace(edzryuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   if (StrToFloat(zryuhu) > 0.00 ) {
					sql = "update CUST_CustomerStartMoney set totalyue = totalyue - "+ zryuhu +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
					Excute(sql);
					edityuhu->Text = StringReplace(edityuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
					edityuhu->Text = FormatFloat("0.00",StrToFloat(edityuhu->Text)- StrToFloat(zryuhu));
					edityu->Text = StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
					edityu->Text = FormatFloat("0.00",StrToFloat(edityu->Text)- StrToFloat(zryuhu));
			   }
			  break;
		   case 1:              //�����
			  aqdg->First();
			  while(!aqdg->Eof)
			  {
				  editweijiedan->Text = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
				  edithukuan->Text =StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);
				  edityinghu->Text =StringReplace(edityinghu->Text,",","",TReplaceFlags()<<rfReplaceAll);
				  sql = "exec fajieshan '"+aqdg->FieldByName("stgntcode")->AsAnsiString+"','"+aqdg->FieldByName("thistime")->AsAnsiString+"',"+IntToStr(Type);
				  Excute(sql);
				  aqdg->Edit();

				  editweijiedan->Text = FloatToStr(StrToFloat(editweijiedan->Text) + StrToFloat(edithukuan->Text));
				  edityinghu->Text =  FloatToStr(StrToFloat(edityinghu->Text) + StrToFloat(edithukuan->Text));
				  aqdg->UpdateBatch(arCurrent);
				  aqdg->Next();
			  }
			  edityu->Text =StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			  edithukuan->Text =StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);
			  edzryuhu->Text =StringReplace(edzryuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			  yy = StrToFloat(edithukuan->Text) + StrToFloat(edzryuhu->Text);
			  sql = "select overage from FN_CUSEndMoneyDocuments where moneycode = " + editnum->Text ;
			  aquery->Close();
			  aquery->SQL->Clear();
			  aquery->SQL->Add(sql);
			  aquery->Open();
			  yy = StrToFloat(edithukuan->Text) - aquery->FieldByName("overage")->AsFloat ;

				sql = "update CUST_CustomerStartMoney set totalyue = totalyue + " + FloatToStr(yy)  + " where customerid ="+IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
				Excute(sql);

				edityu->Text = FloatToStr(yy);

				editweijiedan->Text =StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   //����û�н�Ŀ�

			   edityinghu->Text = StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);

			   editweijiedan->Text = FloatToStr(StrToFloat(editweijiedan->Text) + StrToFloat(edithukuan->Text));
			   edityinghu->Text =  FloatToStr(StrToFloat(edityinghu->Text) + StrToFloat(edithukuan->Text));

			  break;
		   case 2:                       //Ԥ����

			   edityuhu->Text = StringReplace(edityuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   //editmoney->Text = StringReplace(editmoney->Text,",","",TReplaceFlags()<<rfReplaceAll);

			   edityu->Text =StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edithukuan->Text =StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edityuhu->Text = FormatFloat("0.00",StrToFloat(edityuhu->Text) - StrToFloat(edithukuan->Text));

			   edityu->Text = FloatToStr(StrToFloat(edityu->Text)- StrToFloat(edithukuan->Text));
			   sql = "update CUST_CustomerStartMoney set totalyue = totalyue - "+ StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll) +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
			   Excute(sql);

			  break;
		   case 4:                       //����˿�

			   edityuhu->Text = StringReplace(edityuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   //editmoney->Text = StringReplace(editmoney->Text,",","",TReplaceFlags()<<rfReplaceAll);

			   edityu->Text =StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edithukuan->Text =StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   edityuhu->Text = FormatFloat("0.00",StrToFloat(edityuhu->Text) + StrToFloat(edithukuan->Text));

			   edityu->Text = FloatToStr(StrToFloat(edityu->Text) + StrToFloat(edithukuan->Text));
			   sql = "update CUST_CustomerStartMoney set totalyue = totalyue + "+ StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll) +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
			   Excute(sql);

			  break;
   default:
	   ;
   }

	sql = "update FN_CUSEndMoneyDocuments set state = 0 , paymentdate ='" + DateToStr(dtp->DateTime) + "'  where moneycode = "+editnum->Text ;
	Excute(sql);


    /*editstate->Text = "δ���";
	aqdg->Refresh();
	cbselect->Enabled = false;
	cbjieshuantype->Enabled = false;
	//cbmethod->Enabled = false;
	editnum->Enabled = false;
	editstate->Enabled = false;
	editmoney->Enabled = true;
	spselect->Enabled = true;
	sbautojieshuan->Enabled = true;
	autobt->Enabled = true;
	edtQryVendor->Enabled = false;
	edtclient->Enabled = false;
	spselectClient->Enabled = false;
	BtnCancel->Enabled = false;
	BtnOK->Enabled = true;
	BtnDelete->Enabled = true;
	if (cbjieshuantype->Text == "�����Գ�") {
		btduicong->Enabled = true;    
	}  */

	MessageBoxA(0,"�ɹ�����ˣ�","��������",MB_ICONEXCLAMATION);
	QryNthead(editnum->Text);
  }
}
//---------------------------------------------------------------------------


void __fastcall Tfrmbalance::BtnExitClick(TObject *Sender)
{
	 Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::cbjieshuantypeChange(TObject *Sender)
{
	if ((Type == 1 && cbselect->Text == "") || (Type == 2 && edtclient->Text == "")) {
		return;
	}
	if (cbjieshuantype->Text == "Ԥ����" || cbjieshuantype->Text == "Ԥ�տ�" || cbjieshuantype->Text == "����˿�") {
		spselect->Enabled = false;
		sbautojieshuan->Enabled = false;
		autobt->Enabled = false;
		btduicong->Enabled = false;
		editmoney->Enabled = true;
	} 
	else if (cbjieshuantype->ItemIndex == 3) {
		btduicong->Enabled = true;
		spselect->Enabled = false;
		sbautojieshuan->Enabled = false;
		autobt->Enabled = false;
		editmoney->Enabled = false;
	}
	else
	{
		btduicong->Enabled = false;
		spselect->Enabled = true;
		sbautojieshuan->Enabled = true;
		autobt->Enabled = true;
		editmoney->Enabled = true;
	}
}

//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::dgCellClick(TColumn *Column)
{
	if (editnum->Text == "") {
	   return;
   }
   if (dg->DataSource->DataSet->IsEmpty() ) {
	   return;
   }
   editmoney->Text = FormatFloat(Disc,aqdg1->FieldByName("thistime")->AsFloat);
}
//---------------------------------------------------------------------------


void __fastcall Tfrmbalance::cbselectSelect(TObject *Sender)
{
	String sql;
	int custID;
	float tmpweijie,tmpyinhu;
	try {
		if (Type == 1) {
			custID = (int)(cbselect->Items->Objects[cbselect->ItemIndex]);
		}
		else
		{
			custID = ClientID ;
		}

	} catch (...) {
        MessageBox(0,"��ѡ����ȷ�Ŀͻ�!","����",MB_ICONASTERISK);
	}

	if (Type == 1) {
		 sql = "select sum(NoChecked) as totalnochecked from BS_StorageNoteHeader where supplierid= " + IntToStr(custID);
	}else
	{
		sql = " select sum(NoChecked) as totalnochecked  from BS_WsaleNoteHeader where VendorID in  (select ID from GetChild("+IntToStr(custID)+"))";
	}

	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	editweijiedan->Text = FormatFloat(Disc,aquery->FieldByName("totalnochecked")->AsFloat);
    if (aquery->FieldByName("totalnochecked")->AsFloat == 0.00) {
		cbjieshuantype->ItemIndex = 2;
		spselect->Enabled = false;
		sbautojieshuan->Enabled = false;
		autobt->Enabled = false;
		btduicong->Enabled = false;
	}
	else
	{
		cbjieshuantype->ItemIndex = -1;
		spselect->Enabled = true;
		sbautojieshuan->Enabled = true;
		autobt->Enabled = true;
		btduicong->Enabled = true;
	}
	sql = "select totalyue + balance as totalyue from CUST_CustomerStartMoney   where customerid =" + IntToStr(custID) ;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	edityu->Text =  FormatFloat(Disc,aquery->FieldByName("totalyue")->AsFloat);
	edityuhu->Text =FormatFloat(Disc,aquery->FieldByName("totalyue")->AsFloat);

	editweijiedan->Text = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
	edityu->Text =StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);

	tmpweijie =  StrToFloat(editweijiedan->Text);
    tmpyinhu =  StrToFloat(edityu->Text);
	if (StrToFloat(edityu->Text) > StrToFloat(editweijiedan->Text)) {

	 edityinghu->Text = FormatFloat(Disc,StrToFloat(editweijiedan->Text));
	} else if (StrToFloat(edityu->Text)< StrToFloat(editweijiedan->Text)) {
	   edityinghu->Text = FormatFloat(Disc,(tmpweijie-tmpyinhu ));
	}else if (StrToFloat(edityu->Text)== StrToFloat(editweijiedan->Text)) {
	  edityinghu->Text = "0.00";
	}

}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::cbselectKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		cbselect->OnSelect(this);
		cbjieshuantype->SetFocus();

	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmbalance::edtQryVendorKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		String sql;
		if (Type == 1) {
			sql = " select * from CUST_CustomerInfo where Type = 1 and Name like '%"+ edtQryVendor->Text.Trim() + "%' and name <> '' ";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			cbselect->Clear();
			while(!aq->Eof)
			{
				cbselect->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
				aq->Next();
			}
			aq->First();
			cbselect->ItemIndex = cbselect->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
			cbselect->SetFocus();
			cbselect->OnSelect(this);
		}
		else
		{
			TfrmselectClient * frm = new TfrmselectClient(Application,fcon,edtQryVendor->Text,fstgid);
			if (mrOk == frm->ShowModal())
			{
				ClientID = frm->GetSelectID();
				cbselect->ItemIndex = cbselect->Items->IndexOfObject((TObject*)ClientID);
				cbselect->OnSelect(this);
				ClientView();
			}
	   		delete frm;
		}
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {    //�鵥
		if (!search->Enabled ) {
			return;
		}
		search->Click();
	}
	if (Key == VK_F2) {    //��
		if (!BtnNew->Enabled ) {
			return;
		}
		BtnNew->Click();
	}
	if (Key == VK_F3) {    //����
		if (!BtnSave->Enabled ) {
			return;
		}
		BtnSave->Click();
	}
	if (Key == VK_F5) {    //ɾ��
		if (!BtnDelete->Enabled ) {
			return;
		}
		BtnDelete->Click();
	}
	if (Key == VK_F7) {    //���
		if (!BtnOK->Enabled ) {
			return;
		}
		BtnOK->Click();
	}
	if (Key == VK_F8) {    //�����
		if (!BtnCancel->Enabled ) {
			return;
		}
		BtnCancel->Click();
	}
	if (Key == VK_F9) {    //δ���
		if (!Btn->Enabled ) {
			return;
		}
		Btn->Click();
	}
	if (Key == VK_F10) {    //��ӡ
		if (!BtnPrint->Enabled ) {
			return;
		}
		BtnPrint->Click();
	}
	if (Key == VK_F11) {    //Ԥ��
		if (!BtnView->Enabled ) {
			return;
		}
		BtnView->Click();
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

void __fastcall Tfrmbalance::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::spselectClientClick(TObject *Sender)
{
	TfrmselectClient * frm = new TfrmselectClient(Application,fcon,"",fstgid);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		cbselect->ItemIndex = cbselect->Items->IndexOfObject((TObject*)ClientID);
		cbselect->OnSelect(this);
		ClientView();
	}
	delete frm;
}
//---------------------------------------------------------------------------

void Tfrmbalance::ClientView()
{
	if (ClientID == -1) {
		return;
	}
	AnsiString sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	sql = "exec USP_BS_Client_View 0," + IntToStr(ClientID)  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edtclient->Text = aq->FieldByName("Name")->AsAnsiString ;
	delete aq;
}
//---------------------------------------------------------------------------



void __fastcall Tfrmbalance::spselectClick(TObject *Sender)
{
	if (editnum->Text == "") {
	   return;
   }
   Tfrmselectjiedan *frm = new Tfrmselectjiedan(Application,fcon,aqdg);
   if (Type == 1) {
		frm->ID = IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
   }
   else
   {
		frm->ID = ClientID;
   }
   frm->balance = this;
   frm->selectedID = selectID ;
   frm->DanCode = editnum->Text ;
   frm->Type = Type ;
   frm->stgid = fstgid;
   frm->master = fmaster;
   frm->ShowModal();
   delete frm;
   aqdg->UpdateBatch(arAll);
   DisplayDetail(editnum->Text);
   editmoney->SetFocus();
   Displaytotal(editnum->Text);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::sbautojieshuanClick(TObject *Sender)
{
	String sqlupdate;
	AnsiString sql;
	Double Totalyinhu=0.00,shijie=0.00,danjie=0.00;
	if (aqdg1->IsEmpty() ) {
		return;
	}
	aqdg1->First();
	//aqdg->DisableControls();
	while(!aqdg1->Eof)
	{
		//AnsiString bb;
		//bb.sprintf(cc.c_str(),aqdg1->FieldByName("nochecked")->AsFloat );
		Totalyinhu = Totalyinhu + aqdg1->FieldByName("nochecked")->AsFloat ;
		aqdg1->Next();
		//Totalyinhu = Totalyinhu + aqdg->FieldByName("nochecked")->AsFloat  ;
	}

	Tfrmautojieshuan * frm = new Tfrmautojieshuan(Application);
	frm->Caption = "ͳһ����";
	if (Type == 1) {
		frm->Label1->Caption  = "Ӧ��";
	}
	else
	{
		frm->Label1->Caption = "Ӧ��";
	}
	float yy = StrToFloat(StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll));
	frm->edityinhu->Text =FormatFloat(Disc,Totalyinhu);
	if (cbjieshuantype->ItemIndex == 1) {
		frm->yue = yy;
	}
	if ( mrOk == frm->ShowModal())
	{
		aqdg->First();
		while(!aqdg->Eof)
		{
			aqdg->Edit();
			aqdg->FieldByName("thistime")->AsFloat = 0;
			aqdg->UpdateBatch(arCurrent);
			aqdg->Next();
		}
		shijie = StrToFloat(frm->editshijie->Text);
		if (cbjieshuantype->ItemIndex == 1) {
			if (shijie > yy ) {
				sql = "update FN_CUSEndMoneyDocuments set overage = " + FloatToStr(shijie-yy) + " where MoneyCode = " + editnum->Text ;
				Excute(sql);
			}
			else
			{
				sql = "update FN_CUSEndMoneyDocuments set overage = 0 where MoneyCode = " + editnum->Text ;
				Excute(sql);
			}
		}
		//AnsiString bb;
		aqdg1->First();
		aqdg->First();
		float chakuan = 0.00;
		if (!frm->yuhukuan && Totalyinhu < 0) {
			chakuan = Totalyinhu - shijie;
		}
		while(!aqdg->Eof)
		{
			if (aqdg1->FieldByName("nochecked")->AsFloat < 0 ) {
				//bb.sprintf(cc.c_str(),aqdg1->FieldByName("nochecked")->AsFloat) ;
				if (aqdg1->FieldByName("nochecked")->AsFloat < chakuan && chakuan < 0) {
					aqdg->Edit();
					aqdg->FieldByName("thistime")->AsFloat = aqdg1->FieldByName("nochecked")->AsFloat - chakuan ;
					shijie =  shijie - aqdg1->FieldByName("nochecked")->AsFloat + chakuan;
					aqdg->UpdateBatch(arCurrent);
					chakuan = 0;
				}
				else if (chakuan < 0 && aqdg1->FieldByName("nochecked")->AsFloat >= chakuan)
				{
					chakuan = chakuan - aqdg1->FieldByName("nochecked")->AsFloat;
				}
				else
				{
					aqdg->Edit();
					aqdg->FieldByName("thistime")->AsFloat = aqdg1->FieldByName("nochecked")->AsFloat + aqdg->FieldByName("hongcong")->AsFloat;
					shijie =  shijie - aqdg1->FieldByName("nochecked")->AsFloat;
					aqdg->UpdateBatch(arCurrent);
				}
			}
			aqdg->Next();
			aqdg1->Next();
		}
		aqdg->First();
		aqdg1->First();
		while(!aqdg->Eof)
		{
			if (aqdg1->FieldByName("nochecked")->AsFloat > 0) {
				//bb.sprintf(cc.c_str(),aqdg1->FieldByName("nochecked")->AsFloat );
				if (shijie - aqdg1->FieldByName("nochecked")->AsFloat >= 0 )
				{  	aqdg->Edit();
					aqdg->FieldByName("thistime")->AsFloat = aqdg1->FieldByName("nochecked")->AsFloat + aqdg->FieldByName("hongcong")->AsFloat;
					shijie =  shijie - aqdg1->FieldByName("nochecked")->AsFloat;
					aqdg->UpdateBatch(arCurrent);
				}else if (shijie - aqdg1->FieldByName("nochecked")->AsFloat < 0) {
					aqdg->Edit();
					aqdg->FieldByName("thistime")->AsFloat = shijie + aqdg->FieldByName("hongcong")->AsFloat;
					aqdg->UpdateBatch(arCurrent);
					shijie =  0;
					break;
				}
			}
			aqdg->Next();
			aqdg1->Next();
		}

		if (frm->yuhukuan && shijie > 0 && (cbjieshuantype->ItemIndex == 0 || cbjieshuantype->ItemIndex == 1)) {      //����Ԥ���
			sql = "update FN_CUSEndMoneyDocuments set yuhu = " + FloatToStr(shijie) + " where MoneyCode = " + editnum->Text ;
			Excute(sql);
		}
		else
		{
			sql = "update FN_CUSEndMoneyDocuments set yuhu = 0 where MoneyCode = " + editnum->Text ;
			Excute(sql);
		}
		DisplayDetail(editnum->Text);
		Displaytotal(editnum->Text);
		// aqdg->EnableControls();
	}
}
//---------------------------------------------------------------------------
void Tfrmbalance::Displaytotal(String documentid)
 {
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	if (cbjieshuantype->Text == "Ԥ����" || cbjieshuantype->Text == "Ԥ�տ�" || cbjieshuantype->Text == "����˿�" ) {
		sql = "select sum(round(yuhu," + IntToStr(xiaoshubit) + ")) as yuhu from FN_CUSEndMoneyDocuments where MoneyCode = " + documentid;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();

		editthistime->Text = FormatFloat(Disc,aq->FieldByName("yuhu")->AsFloat );
		edithukuan->Text = FormatFloat(Disc,aq->FieldByName("yuhu")->AsFloat );
		editmoney->Text =  FormatFloat("0.00",aq->FieldByName("yuhu")->AsFloat );
		edzryuhu->Text = "0.00";
		edduicong->Text = "0.00";
		editmayang->Text = "0.00" ;
		editshiyang->Text = FormatFloat(Disc,0.00 );
		editaddcost->Text = FormatFloat(Disc,0.00 );
	}
	else
	{
		if (Type == 1)  {
			sql = "select sum(B.TotalFixedPrice) as totalfixedprice,sum(round(B.TotalDiscountedPrice," + IntToStr(xiaoshubit) + ")) as totaldiscountedprice,sum(B.TotalAmount) as totalamount, "
			" sum(round(B.AddCosts," + IntToStr(xiaoshubit) + ")) as addcosts,sum(round(B.Checked," + IntToStr(xiaoshubit) + ")) as checked,sum(round(B.NoChecked," + IntToStr(xiaoshubit) + ")) as nochecked,sum(round(thistime-FN_CUSEndMoneyDtails.hongcong," + IntToStr(xiaoshubit) + ")) as thistime "
			" from FN_CUSEndMoneyDtails left join BS_StorageNoteHeader B ON FN_CUSEndMoneyDtails.stgntcode = B.StgNtCode where EndMoneyDocumentID = " + documentid;
		}
		else
		{
			sql = "select sum(B.FixedPrice) as totalfixedprice,sum(round(B.DiscountedPrice," + IntToStr(xiaoshubit) + ")) as totaldiscountedprice,sum(B.TotalAmount) as totalamount, "
			" sum(round(B.AddCosts," + IntToStr(xiaoshubit) + ")) as addcosts,sum(round(B.Checked," + IntToStr(xiaoshubit) + ")) as checked,sum(round(B.Nochecked," + IntToStr(xiaoshubit) + ")) as nochecked,sum(round(thistime-FN_CUSEndMoneyDtails.hongcong," + IntToStr(xiaoshubit) + ")) as thistime "
			" from FN_CUSEndMoneyDtails left join BS_WsaleNoteHeader B ON FN_CUSEndMoneyDtails.stgntcode = B.WsaleNtCode where EndMoneyDocumentID = " + documentid;
		}
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();

		editmayang->Text = aq->FieldByName("totalfixedprice")->AsAnsiString ;
		editshiyang->Text = FormatFloat(Disc,aq->FieldByName("totaldiscountedprice")->AsFloat );
		editaddcost->Text = FormatFloat(Disc,aq->FieldByName("addcosts")->AsFloat );
		edityijie->Text = FormatFloat(Disc,aq->FieldByName("checked")->AsFloat );
		editweijie->Text = FormatFloat(Disc,aq->FieldByName("nochecked")->AsFloat );
		editthistime->Text = FormatFloat(Disc,aq->FieldByName("thistime")->AsFloat );
		edithukuan->Text = FormatFloat(Disc,aq->FieldByName("thistime")->AsFloat );
		edduicong->Text = "0.00";
		edzryuhu->Text = "0.00";
		if (cbjieshuantype->ItemIndex == 0 || cbjieshuantype->ItemIndex == 1) { //�����˿��жึ��ʱ
			sql = "select sum(round(yuhu," + IntToStr(xiaoshubit) + ")) as yuhu from FN_CUSEndMoneyDocuments where MoneyCode = " + documentid;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			edzryuhu->Text = FormatFloat(Disc,aq->FieldByName("yuhu")->AsFloat );
		}
		if (cbjieshuantype->ItemIndex == 3) {   //�Գ���
			sql = "select sum(thistime) as thistime from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + documentid + " and thistime > 0.00";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			edduicong->Text = FormatFloat(Disc,aq->FieldByName("thistime")->AsFloat );
		}
	}
	delete aq;
 }

//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::cbjieshuantypeKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        cbmethod->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::cbmethodKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edjspz->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::edjspzKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::edtclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		cbjieshuantype->SetFocus();
		edtQryVendor->Text = "";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::dbnvClick(TObject *Sender, TNavigateBtn Button)
{
	QryNthead(aqhd->FieldByName("MoneyCode")->AsAnsiString );
}
//---------------------------------------------------------------------------




void __fastcall Tfrmbalance::dgDblClick(TObject *Sender)
{
	if (aqdg->IsEmpty() ) {
		return;
	}
	TfrmNotedetail *frm = new TfrmNotedetail(Application,aqdg1->FieldByName("stgntcode")->AsAnsiString ,Type,fcon,0,fuserid);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::autobtClick(TObject *Sender)
{
	if (editnum->Text == "") {
		return;
	}
	AnsiString weijie,sql;
	weijie = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
	if (StrToFloat(weijie) == 0.00 ) {
		MessageBox(0,"����Ҫ����ĵ���!","��ʾ",MB_ICONASTERISK);
		return;
	}
	Tfrmautojieshuan * frm = new Tfrmautojieshuan(Application);
	if (Type == 1) {
		frm->Label1->Caption  = "Ӧ��";
	}
	else
	{
		frm->Label1->Caption = "Ӧ��";
	}
	frm->edityinhu->Text =FormatFloat(Disc,StrToFloat(weijie));
	if (cbjieshuantype->ItemIndex == 1) {
		frm->yue = StrToFloat(StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll));
	}
	Double shijie = 0.00,tmp = 0.0;
	ts = 0;
	if (mrOk == frm->ShowModal()) {
		shijie = StrToFloat(frm->editshijie->Text);

		float chakuan = 0.00;
		if (!frm->yuhukuan && StrToFloat(weijie) < 0) {
			chakuan = StrToFloat(weijie) - shijie;
		}
		sql = "delete from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + editnum->Text ;
		Excute(sql);
		selectID->Clear();
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked < 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID in (select ID from GetChild("+ IntToStr(ClientID) +")) and  nochecked < 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
		if (!fmaster) {
			sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
		}
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		//AnsiString bb;
		while(!aquery->Eof)
		{
			if (AddEnable(Type,aquery->FieldByName("stgntcode")->AsAnsiString)) {
				if (ts == 0 && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
					Tfrmtishi *frm = new Tfrmtishi(Application);
					frm->edcode->Text = aquery->FieldByName("CodeStr")->AsAnsiString ;
					frm->edsy->Text = aquery->FieldByName("totalfixedprice")->AsAnsiString ;
					frm->edmy->Text = aquery->FieldByName("totaldiscountedprice")->AsAnsiString ;
					frm->edyj->Text = aquery->FieldByName("checked")->AsAnsiString ;
					frm->edwj->Text = aquery->FieldByName("nochecked")->AsAnsiString ;
					frm->edhc->Text = aquery->FieldByName("hongcong")->AsAnsiString ;
					frm->membk->Lines->Append(aquery->FieldByName("Remarks")->AsAnsiString);
					if (frm->ShowModal() == mrOk  ) {
						hc = frm->hc ;
						ts = frm->ts ;
					}
				}
				if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
					tmp = aquery->FieldByName("nochecked")->AsFloat - aquery->FieldByName("hongcong")->AsFloat;
				}
				else
				{
					tmp = aquery->FieldByName("nochecked")->AsFloat;
				}

				if (chakuan < 0 && tmp < chakuan ) {
					aqdg->Append();
					aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
					aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
					aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
					aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
					aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
					aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
					if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
						aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
					}
					aqdg->FieldByName("thistime")->AsFloat = aquery->FieldByName("nochecked")->AsFloat-chakuan;
					aqdg->FieldByName("type")->AsInteger  = Type ;
					aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
					selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
					chakuan = 0;
					shijie = shijie - tmp + chakuan;
				}
				else if (chakuan < 0 && tmp >= chakuan) {
					chakuan = chakuan - tmp;
				}
				else
				{
					aqdg->Append();
					aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
					aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
					aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
					aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
					aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
					aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
					if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
						aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
					}
					aqdg->FieldByName("thistime")->AsFloat = aquery->FieldByName("nochecked")->AsFloat;
					aqdg->FieldByName("type")->AsInteger  = Type ;
					aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
					selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
					tmp = aqdg->FieldByName("nochecked")->AsFloat;
					shijie = shijie - tmp;
				}
			}
			aquery->Next();
		}
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked > 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID in (select ID from GetChild("+ IntToStr(ClientID) +")) and  nochecked > 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
		if (!fmaster) {
			sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
		}
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		while(!aquery->Eof)
		{
			if (AddEnable(Type,aquery->FieldByName("stgntcode")->AsAnsiString)) {
				if (ts == 0 && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
					Tfrmtishi *frm = new Tfrmtishi(Application);
					frm->edcode->Text = aquery->FieldByName("CodeStr")->AsAnsiString ;
					frm->edsy->Text = aquery->FieldByName("totalfixedprice")->AsAnsiString ;
					frm->edmy->Text = aquery->FieldByName("totaldiscountedprice")->AsAnsiString ;
					frm->edyj->Text = aquery->FieldByName("checked")->AsAnsiString ;
					frm->edwj->Text = aquery->FieldByName("nochecked")->AsAnsiString ;
					frm->edhc->Text = aquery->FieldByName("hongcong")->AsAnsiString ;
					frm->membk->Lines->Append(aquery->FieldByName("Remarks")->AsAnsiString);
					if (frm->ShowModal() == mrOk  ) {
						hc = frm->hc ;
						ts = frm->ts ;
					}
				}
				if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
					tmp = aquery->FieldByName("nochecked")->AsFloat - aquery->FieldByName("hongcong")->AsFloat;
				}
				else
				{
					tmp = aquery->FieldByName("nochecked")->AsFloat;
				}
				if (shijie - tmp > 0 ) {
					aqdg->Append();
					aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
					aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
					aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
					aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
					aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
					aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
					if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
						aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
					}
					aqdg->FieldByName("thistime")->AsFloat = aquery->FieldByName("nochecked")->AsFloat;
					aqdg->FieldByName("type")->AsInteger  = Type ;
					aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
					selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
				}
				else
				{
					aqdg->Append();
					aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
					aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
					aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
					aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
					aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
					aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
					if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
						aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
						aqdg->FieldByName("thistime")->AsFloat = shijie + aquery->FieldByName("hongcong")->AsFloat ;
					}
					else
					{
						aqdg->FieldByName("thistime")->AsFloat = shijie;
					}

					aqdg->FieldByName("type")->AsInteger  = Type ;
					aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
					selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
					break;
				}

				shijie = shijie - tmp;
			}
			aquery->Next();
		}

		if (frm->yuhukuan && shijie > 0 && cbjieshuantype->ItemIndex == 0) {      //����Ԥ���
			sql = "update FN_CUSEndMoneyDocuments set yuhu = " + FloatToStr(shijie) + " where MoneyCode = " + editnum->Text ;
			Excute(sql);
		}
		else
		{
			sql = "update FN_CUSEndMoneyDocuments set yuhu = 0 where MoneyCode = " + editnum->Text ;
			Excute(sql);
		}
		aqdg->UpdateBatch(arAll);
		DisplayDetail(editnum->Text);
		Displaytotal(editnum->Text);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnViewClick(TObject *Sender)
{
	Print(1);
}
//---------------------------------------------------------------------------

void Tfrmbalance::Print(int modle)
{
	if (aqdg->IsEmpty() ) {
		return;
	}
	RvSystem1->SystemSetups >>ssAllowSetup;
	RvSystem1->SystemSetups >>ssAllowDestPreview;
	RvSystem1->SystemSetups >>ssAllowDestPrinter;
	RvSystem1->SystemSetups >>ssAllowPrinterSetup;
	RvSystem1->SystemSetups >>ssAllowDestFile;
	if (modle == 1) {
		RvSystem1->DefaultDest   = rdPreview ;
	}
	else
	{
		RvSystem1->DefaultDest   = rdPrinter ;
	}
	RvSystem1->SystemSetups<<ssAllowDestPrinter;


	if (Type == 1) {
		if (ChangeDisplay) {
			RvProject1->ProjectFile  =ExtractFilePath(Application->ExeName) + "supplierfance1.rav";
		}
		else
		{
			RvProject1->ProjectFile  =ExtractFilePath(Application->ExeName) + "supplierfance.rav";
		}
		RvProject1->Open();
		RvProject1->SetParam("title",Edit2->Text + "���");
		RvProject1->SetParam("Name",cbselect->Text);
	}
	else
	{
		if (ChangeDisplay) {
			RvProject1->ProjectFile  =ExtractFilePath(Application->ExeName) + "clientfance1.rav";
		}
		else
		{
			RvProject1->ProjectFile  =ExtractFilePath(Application->ExeName) + "clientfance.rav";
		}
		RvProject1->Open();
		RvProject1->SetParam("title",Edit2->Text + "�տ");
		RvProject1->SetParam("Name",edtclient->Text);
	}
	RvProject1->SetParam("yue",edityu->Text);
	RvProject1->SetParam("yuhu",edityuhu->Text);
	RvProject1->SetParam("weijie",editweijiedan->Text);
	RvProject1->SetParam("yingfu",edityinghu->Text);
	RvProject1->SetParam("Danhao",editnum->Text);
	RvProject1->SetParam("riqi",DateToStr(dtp->Date));
	RvProject1->SetParam("state",editstate->Text);
	RvProject1->SetParam("style",cbjieshuantype->Text);
	RvProject1->SetParam("method",cbmethod->Text);
	RvProject1->SetParam("pingz",edjspz->Text);
	RvProject1->SetParam("bk",membk->Text);
	RvProject1->SetParam("maker",edemploy->Text);
	TRavePage *RavePage;
	TRaveRegion *RaveRegion;
	TRaveCalcText *calctext3,*calctext4,*calctext5,*calctext6,*calctext7;
	TRaveBand *raveband;
	RavePage = (TRavePage *)RvProject1->ProjMan->FindRaveComponent("Report1.Page1",NULL);
	//RaveRegion = (TRaveRegion *)RvProject1->ProjMan->FindRaveComponent("Region1",RavePage);
	//raveband = (TRaveBand *)RvProject1->ProjMan->FindRaveComponent("Band5",RavePage);
	calctext3 =  (TRaveCalcText *)RvProject1->ProjMan->FindRaveComponent("CalcText3",RavePage);
	calctext4 =  (TRaveCalcText *)RvProject1->ProjMan->FindRaveComponent("CalcText4",RavePage);
	calctext5 =  (TRaveCalcText *)RvProject1->ProjMan->FindRaveComponent("CalcText5",RavePage);
	calctext6 =  (TRaveCalcText *)RvProject1->ProjMan->FindRaveComponent("CalcText6",RavePage);
	calctext7 =  (TRaveCalcText *)RvProject1->ProjMan->FindRaveComponent("CalcText7",RavePage);

	calctext3->DisplayFormat = Disc;
	calctext4->DisplayFormat = Disc;
	calctext5->DisplayFormat = Disc;
	calctext6->DisplayFormat = Disc;
	calctext7->DisplayFormat = Disc;

	RvProject1->Execute();
	RvProject1->Close();

}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnPrintClick(TObject *Sender)
{
	Print(2);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::cbjieshuantypeExit(TObject *Sender)
{
	if ((Type == 1 && cbselect->Text == "") || (Type == 2 && edtclient->Text == "")) {
		return;
	}
	AnsiString weijie,yue,sql;
	yue = StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
	if (StrToFloat(yue) == 0.00 && (cbjieshuantype->ItemIndex == 1 || cbjieshuantype->ItemIndex == 4)) {
		MessageBox(0,"û���������������н��","��ʾ",MB_ICONASTERISK);
		cbjieshuantype->ItemIndex = -1;
		btduicong->Enabled = true;
		spselect->Enabled = true;
		sbautojieshuan->Enabled = true;
		autobt->Enabled = true;
		editmoney->Enabled = true;
		cbjieshuantype->SetFocus();
		return;
	}
	weijie = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
	if (StrToFloat(weijie) == 0.00 && StrToFloat(yue) == 0 && cbjieshuantype->ItemIndex != 2) {
		if (Type == 1) {
			MessageBox(0,"����Ҫ����ĵ��ݣ�ֻ��ѡ��Ԥ����!","��ʾ",MB_ICONASTERISK);
		}
		else
		{
			MessageBox(0,"����Ҫ����ĵ��ݣ�ֻ��ѡ��Ԥ�տ�!","��ʾ",MB_ICONASTERISK);
		}
		cbjieshuantype->ItemIndex = 2;
		btduicong->Enabled = false;
		spselect->Enabled = false;
		sbautojieshuan->Enabled = false;
		autobt->Enabled = false;
		editmoney->Enabled = true;
		cbjieshuantype->SetFocus();
		return;
	}
	else if ((cbjieshuantype->ItemIndex != 2 && cbjieshuantype->ItemIndex != 4) && StrToFloat(weijie) == 0.00 ) {
		if (Type == 1) {
			MessageBox(0,"����Ҫ����ĵ��ݣ�ֻ��ѡ��Ԥ���������˿�!","��ʾ",MB_ICONASTERISK);
		}
		else
		{
			MessageBox(0,"����Ҫ����ĵ��ݣ�ֻ��ѡ��Ԥ�տ������˿�!","��ʾ",MB_ICONASTERISK);
		}

		cbjieshuantype->ItemIndex = 2;
		btduicong->Enabled = false;
		spselect->Enabled = false;
		sbautojieshuan->Enabled = false;
		autobt->Enabled = false;
		editmoney->Enabled = true;
		cbjieshuantype->SetFocus();
		return;
	}
	else if (cbjieshuantype->ItemIndex == 3) {
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked < 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID in (select ID from GetChild("+ IntToStr(ClientID) +")) and  nochecked < 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
		if (!fmaster) {
			sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
		}
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->IsEmpty() ) {
			MessageBox(0,"�޶Գ嵥�ݣ�����ʹ�������Գ�!","��ʾ",MB_ICONASTERISK);
			cbjieshuantype->ItemIndex = -1;
			btduicong->Enabled = true;
			spselect->Enabled = true;
			sbautojieshuan->Enabled = true;
			autobt->Enabled = true;
			editmoney->Enabled = true;
			cbjieshuantype->SetFocus();
			return;
		}
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked > 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID in (select ID from GetChild("+ IntToStr(ClientID) +")) and  nochecked > 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
		if (!fmaster) {
			sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
		}
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->IsEmpty() ) {
			MessageBox(0,"�޶Գ嵥�ݣ�����ʹ�������Գ�!","��ʾ",MB_ICONASTERISK);
			cbjieshuantype->ItemIndex = -1;
			btduicong->Enabled = true;
			spselect->Enabled = true;
			sbautojieshuan->Enabled = true;
			autobt->Enabled = true;
			editmoney->Enabled = true;
			cbjieshuantype->SetFocus();
			return;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::btduicongClick(TObject *Sender)
{
	if (editnum->Text == "") {
		return;
	}
	ts = 0;
	AnsiString weijie,sql;
	weijie = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
	sql = "delete from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + editnum->Text ;
	Excute(sql);
	selectID->Clear();
	DOUBLE shijie = 0.00,tmp = 0.0;
	//AnsiString bb;
	if (StrToFloat(weijie) > 0.00 ) {
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked < 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID in (select ID from GetChild("+ IntToStr(ClientID) +")) and  nochecked < 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
	}
	else
	{
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked > 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID in (select ID from GetChild("+ IntToStr(ClientID) +")) and  nochecked > 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
	}
	if (!fmaster) {
		sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
	}
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while(!aquery->Eof)
	{
		if (AddEnable(Type,aquery->FieldByName("stgntcode")->AsAnsiString)) {
			if (ts == 0 && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
				Tfrmtishi *frm = new Tfrmtishi(Application);
				frm->edcode->Text = aquery->FieldByName("CodeStr")->AsAnsiString ;
				frm->edsy->Text = aquery->FieldByName("totalfixedprice")->AsAnsiString ;
				frm->edmy->Text = aquery->FieldByName("totaldiscountedprice")->AsAnsiString ;
				frm->edyj->Text = aquery->FieldByName("checked")->AsAnsiString ;
				frm->edwj->Text = aquery->FieldByName("nochecked")->AsAnsiString ;
				frm->edhc->Text = aquery->FieldByName("hongcong")->AsAnsiString ;
				frm->membk->Lines->Append(aquery->FieldByName("Remarks")->AsAnsiString);
				if (frm->ShowModal() == mrOk) {
					hc = frm->hc ;
					ts = frm->ts ;
				}
			}
			aqdg->Append();
			aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
			aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
			aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
			aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
			aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
			aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
			aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
			aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
			aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
			aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
			if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
				aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
			}
			aqdg->FieldByName("thistime")->AsFloat = aquery->FieldByName("nochecked")->AsFloat;
			aqdg->FieldByName("type")->AsInteger  = Type ;
			aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
			selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);

			if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
				tmp = aquery->FieldByName("nochecked")->AsFloat - aquery->FieldByName("hongcong")->AsFloat;
			}
			else
			{
				tmp = aquery->FieldByName("nochecked")->AsFloat;
			}
			shijie = shijie + tmp;
		}
		aquery->Next();

	}
	if (shijie > 0.00) {
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked < 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID in (select ID from GetChild("+ IntToStr(ClientID) +")) and  nochecked < 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
		if (!fmaster) {
			sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
		}
	}
	else if (shijie < 0.00) {
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked > 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID in (select ID from GetChild("+ IntToStr(ClientID) +")) and  nochecked > 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
		if (!fmaster) {
			sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
		}
	}
	shijie = 0.00-shijie;

	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while(!aquery->Eof)
	{
		if (AddEnable(Type,aquery->FieldByName("stgntcode")->AsAnsiString)) {
			if (ts == 0 && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
				Tfrmtishi *frm = new Tfrmtishi(Application);
				frm->edcode->Text = aquery->FieldByName("CodeStr")->AsAnsiString ;
				frm->edsy->Text = aquery->FieldByName("totalfixedprice")->AsAnsiString ;
				frm->edmy->Text = aquery->FieldByName("totaldiscountedprice")->AsAnsiString ;
				frm->edyj->Text = aquery->FieldByName("checked")->AsAnsiString ;
				frm->edwj->Text = aquery->FieldByName("nochecked")->AsAnsiString ;
				frm->edhc->Text = aquery->FieldByName("hongcong")->AsAnsiString ;
				frm->membk->Lines->Append(aquery->FieldByName("Remarks")->AsAnsiString);
				if (frm->ShowModal() == mrOk) {
					hc = frm->hc ;
					ts = frm->ts ;
				}
			}
			if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
				tmp = aquery->FieldByName("nochecked")->AsFloat - aquery->FieldByName("hongcong")->AsFloat ;
			}
			else
			{
				tmp = aquery->FieldByName("nochecked")->AsFloat;
			}
			if ((shijie - tmp > 0 && shijie > 0) || (shijie - tmp < 0 && shijie < 0) ) {
				aqdg->Append();
				aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
				aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
				aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
				aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
				aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
				aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
				aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
				aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
				aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
				aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
				if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00){
					aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
				}
				aqdg->FieldByName("thistime")->AsFloat = aquery->FieldByName("nochecked")->AsFloat;
				aqdg->FieldByName("type")->AsInteger  = Type ;
				aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
				selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
			}
			else
			{
				aqdg->Append();
				aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
				aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
				aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
				aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
				aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
				aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
				aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
				aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
				aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
				aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
				if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00){
					aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
					aqdg->FieldByName("thistime")->AsFloat = shijie + aquery->FieldByName("hongcong")->AsFloat;
				}
				else
				{
					aqdg->FieldByName("thistime")->AsFloat = shijie;
				}
				aqdg->FieldByName("type")->AsInteger  = Type ;
				aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
				selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
				break;
			}
			shijie = shijie - tmp;
		}

		aquery->Next();
	}
	aqdg->UpdateBatch(arAll);
	DisplayDetail(editnum->Text);
	Displaytotal(editnum->Text);
}
//---------------------------------------------------------------------------


void __fastcall Tfrmbalance::N2Click(TObject *Sender)
{
	if (aqdg->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= aqdg->RecordCount ; i++) {
		dg->DataSource->DataSet->RecNo = i;
		dg->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::edtQryVendorExit(TObject *Sender)
{
	edtQryVendor->Text = "";
}
//---------------------------------------------------------------------------
bool Tfrmbalance::AddEnable(int type,AnsiString code)
{
	AnsiString sql;
	TADOQuery *aq1 = new TADOQuery(NULL);
	aq1->Connection = fcon;

	if (type == 1) {
		sql = "select * from FN_CUSEndMoneyDocuments left join FN_CUSEndMoneyDtails on FN_CUSEndMoneyDocuments.MoneyCode = FN_CUSEndMoneyDtails.EndMoneyDocumentID "
			" where FN_CUSEndMoneyDocuments.type = 1 and FN_CUSEndMoneyDtails.type = 1 and FN_CUSEndMoneyDocuments.state = 0 and FN_CUSEndMoneyDtails.stgntcode = " + code;
	}
	else
	{
		sql = "select * from FN_CUSEndMoneyDocuments left join FN_CUSEndMoneyDtails on FN_CUSEndMoneyDocuments.MoneyCode = FN_CUSEndMoneyDtails.EndMoneyDocumentID "
			" where FN_CUSEndMoneyDocuments.type = 2 and FN_CUSEndMoneyDtails.type = 2 and FN_CUSEndMoneyDocuments.state = 0 and FN_CUSEndMoneyDtails.stgntcode = " + code;
	}
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();

	if (aq1->RecordCount > 0) {
		delete aq1;
		return false;
	}
	else
	{
		delete aq1;
		return true;
	}
}
//---------------------------------------------------------------------------



