//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "orderimportselect.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmorderimportselect *frmorderimportselect;
//---------------------------------------------------------------------------
__fastcall Tfrmorderimportselect::Tfrmorderimportselect(TComponent* Owner,TADOQuery *aq)
	: TForm(Owner)
{
	newbook = false;
	query = aq;
	fcon = aq->Connection ;
	ds->DataSet = aq;
	comHebingshumu->Connection = aq->Connection ;
	ybookid = -1;
    mbookid = -1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderimportselect::SpeedButton2Click(TObject *Sender)
{
	newbook = true;
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderimportselect::SpeedButton1Click(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void Tfrmorderimportselect::showorderbook()
{
	edbook->Text = orderbook;
	edpress->Text = orderpress;
    edisbn->Text = orderisbn;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderimportselect::N1Click(TObject *Sender)
{
	ybookid = query->FieldByName("id")->AsInteger;
	ybookname = query->FieldByName("Name")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderimportselect::N2Click(TObject *Sender)
{
	mbookid = query->FieldByName("id")->AsInteger;
	mbookname = query->FieldByName("Name")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderimportselect::buhebingClick(TObject *Sender)
{
	if (ybookid == -1) {
		MessageBoxA(0,"û�����úϲ�Դ��Ŀ��","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	if (mbookid == -1) {
		MessageBoxA(0,"û�����úϲ�Ŀ����Ŀ��","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	if (ybookid == mbookid) {
		MessageBoxA(0,"�ϲ�Դ��Ŀ��ϲ�Ŀ����Ŀ��ͬ��","��ʾ",MB_ICONEXCLAMATION);
		return;
	}
	comHebingshumu->Parameters->ParamByName("@ybookid")->Value = ybookid;
	comHebingshumu->Parameters->ParamByName("@mbookid")->Value = mbookid;
	try {
		comHebingshumu->Execute();
		MessageBoxA(0,"�ϲ���Ŀ�ɹ���","�ϲ��ɹ�",MB_ICONEXCLAMATION);
		query->Active = false;
		query->Active = true;
		logmessage =  "�ϲ���Ŀ��" + ybookname + "��Ϊ��" + mbookname + "��";
		AddEvent(1,"����������Ŀѡ��",userid,stgid,logmessage,fcon);
	} catch (...) {
		MessageBoxA(0,"�ϲ���Ŀ����,����Ŀ������ҵ����ϵ��","�ϲ�����",MB_ICONEXCLAMATION);
	}

}
//---------------------------------------------------------------------------

