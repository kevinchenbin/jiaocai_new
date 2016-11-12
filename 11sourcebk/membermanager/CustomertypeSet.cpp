//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CustomertypeSet.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmcustomertype *frmcustomertype;
//---------------------------------------------------------------------------
__fastcall Tfrmcustomertype::Tfrmcustomertype(TComponent* Owner,TADOConnection *cnn,int Type)
	: TForm(Owner)
{
	Root = tvMemberType->Items->Item[0];
	quMemberType->Connection = cnn;
	type = Type;
	if (type == 1) {
		tvMemberType->Items->Item[0]->Text = "��Ӧ�̷���";
		this->Caption = "��Ӧ�̷���";
	}
	else
	{
		tvMemberType->Items->Item[0]->Text = "�ͻ�����";
		this->Caption = "�ͻ�����";
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcustomertype::FormShow(TObject *Sender)
{
	AnsiString sql;
	sg = new TStringList;
	sql = "select ID,Name from CUST_Customertype where type = " + IntToStr(type);
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	while(!quMemberType->Eof )
	{
	  AnsiString idtypename =  quMemberType->FieldByName("Name")->AsAnsiString.Trim();
	  tvMemberType->Items->AddChild(Root,idtypename);
	  //sg->Add(idtypename + "=" + quMemberType->FieldByName("ID")->AsString);
	  quMemberType->Next();
	}
	tvMemberType->AutoExpand = true;
	edTypeName->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::BtnAddClick(TObject *Sender)
{
	savemodle = 1; //1Ϊ���
	edTypeName->Text = "";
	edTypeName->Enabled = true;
	edTypeName->SetFocus();
	BtnChangeOptions->Enabled = false;
	BtnSave->Enabled = true;
	AnsiString sql;
	sql = "select MAX(ID) as ID from CUST_Customertype";
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	int memberid = quMemberType->FieldByName("ID")->AsInteger + 1;
	edMemberID->Text = IntToStr(memberid);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::BtnDeleteClick(TObject *Sender)
{
	if (tvMemberType->Selected->Level != 1){
		if (type == 1) {
			MessageBox(0,"��ѡ��Ӧ�����ͣ�","û��ѡ��" ,MB_OK);
		}
		else
		{
			MessageBox(0,"��ѡ��ͻ����ͣ�","û��ѡ��" ,MB_OK);
		}
	}
	else
	{
		AnsiString idtypename =  tvMemberType->Selected->Text;
		AnsiString sql,sdf ;
		//AnsiString idtype = sg->Values[tvMemberType->Selected->Text];
		//sql = "select * from CUST_CustomerInfo where customertype = " + idtype;
		sql = "select * from CUST_CustomerInfo where customertype = (select ID from CUST_Customertype where Name = '" + idtypename + "' and type = " + IntToStr(type) + ")";
		quMemberType->Close();
		quMemberType->SQL->Clear();
		quMemberType->SQL->Add(sql);
		quMemberType->Open();
		if (!quMemberType->IsEmpty()) {
			if (type == 1) {
				MessageBox(0,"�ù�Ӧ�����͵Ĺ�Ӧ����Ϣ���ڣ�����ɾ���ù�Ӧ�����ͣ�","ɾ������" ,MB_OK);
			}
			else
			{
				MessageBox(0,"�ÿͻ����͵Ŀͻ���Ϣ���ڣ�����ɾ���ÿͻ����ͣ�","ɾ������" ,MB_OK);
			}

		}
		else
		{
			sql = "delete from CUST_Customertype where Name = '" + idtypename + "' and type = " + IntToStr(type) ;
			if (type == 1) {
				sdf = "ȷ��ɾ����Ӧ�����ͣ�"+Trim(tvMemberType->Selected->Text)+"��";
			}
			else
			{
				sdf = "ȷ��ɾ���ͻ����ͣ�"+Trim(tvMemberType->Selected->Text)+"��";
			}
			if (MessageBox(0,sdf.c_str() ,"ɾ��ȷ��" ,MB_OKCANCEL)==1) {
				try {
					quMemberType->Close();
					quMemberType->SQL->Clear();
					quMemberType->SQL->Add(sql);
					quMemberType->ExecSQL();
					tvMemberType->Selected->Delete();
					edTypeName->Text = "";
				} catch (Exception &E) {
					MessageBox(0,"�����ݸ�ϵͳ���������й���������ɾ����","ɾ������" ,MB_OK);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::tvMemberTypeClick(TObject *Sender)
{
	AnsiString sql;
	BtnAdd->Enabled = true;
	BtnChangeOptions->Enabled = true;
	BtnSave->Enabled = false;
	edTypeName->Enabled = false;
	//ShowMessage(sg->Values[tvMemberType->Selected->Text]);
	//AnsiString idtype = IntToStr(sg->IndexOfName(tvMemberType->Selected->Text)) ;
	AnsiString idtypename =  tvMemberType->Selected->Text;
	sql = "select * from CUST_Customertype where Name = '" + idtypename + "' and type = " + IntToStr(type) ;
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	if (tvMemberType->Selected->Level == 1) {
		edMemberID->Text = quMemberType->FieldByName("ID")->AsString ;
		edTypeName->Text = idtypename;
	}
	//edMemberID->Text = idtype ;
	//edTypeName->Text = idtypename;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::BtnChangeOptionsClick(TObject *Sender)
{
	BtnAdd->Enabled = false;
	BtnSave->Enabled = true;
	if (savemodle == 1 && edTypeName->Enabled) {
		MessageBox(0,"����Ϊ���״̬�������޸ģ�","�޸Ĵ���" ,MB_OK);
	}
	else
	{
		edTypeName->Enabled = true;
	}
	savemodle = 2; //2Ϊ�޸�
	edTypeName->SetFocus();
	if (tvMemberType->Selected->Level != 1){
		if (type == 1) {
			MessageBox(0,"��ѡ��һ����Ӧ�����ͣ�","û��ѡ��" ,MB_OK);
		}
		else
		{
			MessageBox(0,"��ѡ��һ���ͻ����ͣ�","û��ѡ��" ,MB_OK);
		}
	}
	else
	{
		AnsiString idtypename =  tvMemberType->Selected->Text;
	}
}
//---------------------------------------------------------------------------


//��ӱ��溯��
void __fastcall Tfrmcustomertype::Addsave()
{
	AnsiString sql,sdf;
	sql = "select * from CUST_Customertype where Name = '" + edTypeName->Text + "' and type = " + IntToStr(type);
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	if (edTypeName->Text == "") {
		if (type == 1) {
			MessageBox(0,"��Ӧ���������Ʋ���Ϊ�գ�","����ȷ��" ,MB_OK);
		}
		else
		{
			MessageBox(0,"�ͻ��������Ʋ���Ϊ�գ�","����ȷ��" ,MB_OK);
		}

	}
	else
	{
			if (!quMemberType->IsEmpty() ) {
				if (type == 1) {
					MessageBox(0,"�ù�Ӧ����������ӣ�","����ȷ��" ,MB_OK);
				}
				else
				{
					MessageBox(0,"�ÿͻ���������ӣ�","����ȷ��" ,MB_OK);
				}
			}
			else
			{

				if (type == 1) {
					sdf =  "ȷ����ӹ�Ӧ�����ͣ�"+edTypeName->Text+"��";
				}
				else
				{
					sdf =  "ȷ����ӿͻ����ͣ�"+edTypeName->Text+"��";
				}
				if (MessageBox(0,sdf.c_str() ,"���ȷ��" ,MB_OKCANCEL)==1) {
					if (quMemberType->State != dsInsert) {
						quMemberType->Append();
					}
					if (quMemberType->State == dsInsert) {
						quMemberType->FieldByName("Name")->AsString = edTypeName->Text;
						quMemberType->FieldByName("type")->AsInteger = type;
						quMemberType->Post();
                        sql = "select max(ID) as ID from CUST_Customertype";
						quMemberType->Close();
						quMemberType->SQL->Clear();
						quMemberType->SQL->Add(sql);
						quMemberType->Open();
						AnsiString addname = edTypeName->Text.Trim() ;
						tvMemberType->Items->AddChild(Root,addname);
						//tvMemberType->Items->AddChildObject(Root,addname,(TObject *)quMemberType->FieldByName("ID")->AsInteger);
						sg->AddObject(addname,(TObject *)quMemberType->FieldByName("ID")->AsInteger);
						edTypeName->Enabled = false;
						BtnAdd->Enabled = true;
						BtnChangeOptions->Enabled = true;
						BtnSave->Enabled = false;
					}
				}
			}
	}
}
//---------------------------------------------------------------------------

//�޸ı��溯��
void __fastcall Tfrmcustomertype::Changesave()
{
	savemodle = 2; //2Ϊ�޸�
	edTypeName->Enabled = true;
	if (tvMemberType->Selected->Level != 1){
		if (type == 1) {
			MessageBox(0,"��ѡ��һ����Ӧ�����ͣ�","û��ѡ��" ,MB_OK);
		}
		else
		{
			MessageBox(0,"��ѡ��һ���ͻ����ͣ�","û��ѡ��" ,MB_OK);
		}
	}
	else
	{
		AnsiString sql,sdf;
		AnsiString idtypename =  tvMemberType->Selected->Text.Trim() ;
		//AnsiString idtype = sg->Values[tvMemberType->Selected->Text];
		//sql = "select * from CUST_CustomerInfo where customertype = " + idtype;
		sql = "select * from CUST_CustomerInfo where customertype = (select ID from CUST_Customertype where Name = '" + idtypename + "' and type = " + IntToStr(type) + ")";
		quMemberType->Close();
		quMemberType->SQL->Clear();
		quMemberType->SQL->Add(sql);
		quMemberType->Open();
		if (!quMemberType->IsEmpty()) {
			if (type == 1) {
				MessageBox(0,"�ù�Ӧ�̵Ĺ�Ӧ����Ϣ���ڣ������޸ĸù�Ӧ�����ͣ�","�޸Ĵ���" ,MB_OK);
			}
			else
			{
				MessageBox(0,"�ÿͻ����͵Ŀͻ���Ϣ���ڣ������޸ĸÿͻ����ͣ�","�޸Ĵ���" ,MB_OK);
			}
		}
		else
		{
			sql = "update CUST_Customertype set Name = '" + Trim(edTypeName->Text)+ "' where Name = '" + idtypename + "' and type = " + IntToStr(type) ;
			if (type == 1) {
				sdf = "ȷ���޸Ĺ�Ӧ�����ͣ�"+idtypename+"��";
			}
			else
			{
				sdf = "ȷ���޸Ŀͻ����ͣ�"+idtypename+"��";
			}
			if (MessageBox(0,sdf.c_str() ,"�޸�ȷ��" ,MB_OKCANCEL)==1) {
				try {
					quMemberType->Close();
					quMemberType->SQL->Clear();
					quMemberType->SQL->Add(sql);
					quMemberType->ExecSQL();
					AnsiString addname = edTypeName->Text.Trim() ;
					tvMemberType->Selected->Text = addname;
					edTypeName->Enabled = false;
					BtnAdd->Enabled = true;
					BtnChangeOptions->Enabled = true;
					BtnSave->Enabled = false;
				} catch (Exception &E) {
					MessageBox(0,"�����ݸ�ϵͳ���������й����������޸ģ�","�޸Ĵ���" ,MB_OK);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcustomertype::BtnSaveClick(TObject *Sender)
{
	if (edTypeName->Text == "") {
		if (type == 1) {
			MessageBox(0,"��Ӧ���������Ʋ���Ϊ�գ�","������ʾ" ,MB_OK);
		}
		else
		{
			MessageBox(0,"�ͻ��������Ʋ���Ϊ�գ�","������ʾ" ,MB_OK);
		}
		return;
	}
	if (savemodle == 1) {
		Addsave();
	}
	else if (savemodle == 2) {
		Changesave();
	}
	else
	{}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::edTypeNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnSave->Click();
		//edTypeDiscount->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcustomertype::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {
		BtnAdd->Click();
	}
	if (Key == VK_F3) {
		BtnChangeOptions->Click();
	}
	if (Key == VK_F4) {
		BtnSave->Click();
	}
	if (Key == VK_F5) {
		BtnDelete->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==81) {
		BtnExit->Click();
	}
}
//---------------------------------------------------------------------------

