//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AreaSet.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TMemberAreaSet *MemberAreaSet;
//---------------------------------------------------------------------------
__fastcall TMemberAreaSet::TMemberAreaSet(TComponent* Owner,TADOConnection *cnn)
	: TForm(Owner)
{
	Root = tvArea->Items->Item[0];
	quArea->Connection = cnn;
}
//---------------------------------------------------------------------------
void __fastcall TMemberAreaSet::FormShow(TObject *Sender)
{
	AnsiString sql;
	sql = "select * from Sys_Local ";
	quArea->Close();
	quArea->SQL->Clear();
	quArea->SQL->Add(sql);
	quArea->Open();
	while(!quArea->Eof )
	{
	  tvArea->Items->AddChild(Root,quArea->FieldByName("Local")->AsAnsiString);
	  quArea->Next();
	}
	tvArea->AutoExpand = true;
}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::BtnNewClick(TObject *Sender)
{
	savamodle = 1;//1Ϊ���
	BtnChangeOptions->Enabled = false;
	BtnSave->Enabled = true;
	edAreaId->Enabled = false;
	AnsiString sql;
	sql = "select max(ID) as id from Sys_Local";
    quArea->Close();
	quArea->SQL->Clear();
	quArea->SQL->Add(sql);
	quArea->Open();
	int AreaId = quArea->FieldByName("id")->AsInteger + 1;
	edAreaId->Text = IntToStr(AreaId);
	edName->Text = "";
	edName->Enabled = true;
	edName->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::BtnChangeOptionsClick(TObject *Sender)
{

	BtnNew->Enabled = false;
	BtnSave->Enabled = true;
	if (savamodle == 1 && edName->Enabled == true) {
		MessageBox(0,"����Ϊ���״̬�������޸ģ�","�޸Ĵ���" ,MB_OK);
	}
	else
	{
    	edName->Enabled = true;
	}
	savamodle = 2;//2Ϊ�޸�

}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::BtnDeleteClick(TObject *Sender)
{
	if (tvArea->Selected->Level != 1) {
		MessageBox(0,"��ѡ��һ������","û��ѡ��" ,MB_OK);
	}
	else
	{
		AnsiString sql,sdf;
		sql = "select * from CUST_CustomerInfo where Local = '" + Trim(tvArea->Selected->Text) + "'";
		quArea->Close();
		quArea->SQL->Clear();
		quArea->SQL->Add(sql);
		quArea->Open();
		if (!quArea->IsEmpty() ) {
			MessageBox(0,"������Ĺ˿���Ϣ���ڣ�����ɾ����","����ȷ��" ,MB_OK);
		}
		else
		{
			sql = "delete from Sys_Local where Local = '" + Trim(tvArea->Selected->Text) + "'";
			sdf = "ȷ��ɾ������" + Trim(tvArea->Selected->Text) + "��";
			if (MessageBox(0,sdf.c_str() ,"ɾ��ȷ��" ,MB_OKCANCEL)==1){
				try {
                	quArea->Close();
					quArea->SQL->Clear();
					quArea->SQL->Add(sql);
					quArea->ExecSQL();
					tvArea->Selected->Delete();
					edName->Text = "";
					edAreaId->Text = "";
				} catch (Exception &E) {
					MessageBox(0,"�����ݸ�ϵͳ���������й���������ɾ����","����ȷ��" ,MB_OK);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::tvAreaClick(TObject *Sender)
{
	AnsiString sql;
	BtnNew->Enabled = true;
	BtnChangeOptions->Enabled  = true;
	BtnSave->Enabled  = false;
	edAreaId->Enabled = false;
	edName->Enabled = false;
	sql = "select * from Sys_Local where Local = '" + Trim(tvArea->Selected->Text) + "'";
	quArea->Close();
	quArea->SQL->Clear();
	quArea->SQL->Add(sql);
	quArea->Open();
	if (tvArea->Selected->Level == 1) {
		edAreaId->Text =  quArea->FieldByName("ID")->AsString;
		edName->Text = Trim(tvArea->Selected->Text);
	}
}
//---------------------------------------------------------------------------

// ��ӱ��溯��
void __fastcall TMemberAreaSet::Newsava()
{
	AnsiString sql,sdf;
	if (edName->Text == "") {
		MessageBox(0,"�������������ƣ�","����Ϊ��" ,MB_OK);
	}
	else
	{
		sql = "select * from Sys_Local where Local = '" + Trim(edName->Text) + "'";
		quArea->Close();
		quArea->SQL->Clear();
		quArea->SQL->Add(sql);
		quArea->Open();
		sdf = "����" + Trim(edName->Text) + "�Ѿ����ڣ�";
		if (!quArea->IsEmpty() ) {
			MessageBox(0,sdf.c_str(),"�����ظ�" ,MB_OK);
		}
		else
		{
			sdf = "ȷ���������" + Trim(edName->Text) + "��";
			if (quArea->State !=dsInsert) {
            	quArea->Append();
			}
			if (MessageBox(0,sdf.c_str() ,"���ȷ��" ,MB_OKCANCEL)==1){
				if (quArea->State ==dsInsert) {
					quArea->FieldByName("Local")->AsString = Trim(edName->Text);
					quArea->Post();
					tvArea->Items->AddChild(Root,Trim(edName->Text));
					edAreaId->Enabled = false;
					edName->Enabled = false;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

//�޸ı��溯��
void __fastcall TMemberAreaSet::Changesava()
{
	AnsiString sql;
	if (tvArea->Selected->Level != 1) {
		MessageBox(0,"��ѡ��һ������","û��ѡ��" ,MB_OK);
	}
	else
	{
    	sql = "select * from CUST_CustomerInfo where Local = '" + Trim(tvArea->Selected->Text) + "'";
		quArea->Close();
		quArea->SQL->Clear();
		quArea->SQL->Add(sql);
		quArea->Open();
		if (!quArea->IsEmpty() ) {
			MessageBox(0,"������Ĺ˿���Ϣ���ڣ������޸ģ�","����ȷ��" ,MB_OK);
		}
		else
		{
           	if (edName->Text == "") {
				MessageBox(0,"�������������ƣ�","����Ϊ��" ,MB_OK);
			}
			else
			{
				AnsiString sql,sdf;
				int id;
				sql = "select * from Sys_Local where Local = '" + Trim(tvArea->Selected->Text) + "'";
				quArea->Close();
				quArea->SQL->Clear();
				quArea->SQL->Add(sql);
				quArea->Open();
				id = quArea->FieldByName("ID")->AsInteger;
				if (quArea->IsEmpty() ) {
					sdf = "����" + Trim(tvArea->Selected->Text) + "�����ڣ�";
					MessageBox(0,sdf.c_str(),"�޸ĳ���" ,MB_OK);
				}
				else
				{
					sql = "update Sys_Local set Local = '" + Trim(edName->Text) + "' where ID = " + id;
					sdf = "ȷ���޸�����" + Trim(tvArea->Selected->Text) + "��";
					if (MessageBox(0,sdf.c_str() ,"�޸�ȷ��" ,MB_OKCANCEL)==1) {
						try {
							quArea->Close();
							quArea->SQL->Clear();
							quArea->SQL->Add(sql);
							quArea->ExecSQL();
							tvArea->Selected->Text =  Trim(edName->Text);
							edAreaId->Enabled = false;
							edName->Enabled = false;
							BtnNew->Enabled = true;
							BtnChangeOptions->Enabled = true;
						} catch (Exception &E) {
							MessageBox(0,"�����ݸ�ϵͳ���������й����������޸ģ�","����ȷ��" ,MB_OK);
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TMemberAreaSet::BtnSaveClick(TObject *Sender)
{
	if (savamodle == 1) {
		Newsava();
	}
	else if (savamodle == 2) {
		Changesava();
	}
	else
    {}
}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TMemberAreaSet::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {     //��
		BtnNew->Click();
	}
	if (Key == VK_F3) {     //�޸�
		BtnChangeOptions->Click();
	}
	if (Key == VK_F4) {     //����
		BtnSave->Click();
	}
	if (Key == VK_F5) {     //ɾ��
		BtnDelete->Click();
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

void __fastcall TMemberAreaSet::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

