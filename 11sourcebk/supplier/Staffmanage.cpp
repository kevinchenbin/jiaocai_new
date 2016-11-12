//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Staffmanage.h"
#include "Staffdetail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TfrmStaff *frmStaff;
//---------------------------------------------------------------------------
__fastcall TfrmStaff::TfrmStaff(TComponent* Owner,TADOConnection *cnn,int stgid)
	: TForm(Owner)
{
	cn = cnn;
	fstgid = stgid;
	aqinit->Connection = cnn;
	aqrecord->Connection = cnn;
	query->Connection = cnn;
	AnsiString sql;
	sql = "select SYS_StaffInfo.*,case Career when 1 then '�ɹ�Ա' when 2 then 'ҵ��Ա'  end as careername from SYS_StaffInfo where StgID = " + IntToStr(fstgid) ;
	aqrecord->Close();
	aqrecord->SQL->Clear();
	aqrecord->SQL->Add(sql);
	aqrecord->Open();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStaff::BtnViewClick(TObject *Sender)
{
	AnsiString sql;
	sql = "select SYS_StaffInfo.*,case Career when 1 then '�ɹ�Ա' when 2 then 'ҵ��Ա'  end as careername from SYS_StaffInfo where name like '%" + etname->Text.Trim() + "%' and StgID = " + IntToStr(fstgid) ;
	aqrecord->Close();
	aqrecord->SQL->Clear();
	aqrecord->SQL->Add(sql);
	aqrecord->Open();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStaff::BtnNewClick(TObject *Sender)
{
	TfrmStaffdetail * frm = new TfrmStaffdetail(Application,1,"",cn,fstgid);
	frm->ShowModal() ;
	delete frm;
	aqrecord->Active = false;
	aqrecord->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStaff::BtnFinishClick(TObject *Sender)
{
	if (aqrecord->IsEmpty() ) {
		return;
	}
	TfrmStaffdetail * frm = new TfrmStaffdetail(Application,2,aqrecord->FieldByName("ID")->AsString,cn,fstgid);
	frm->ShowModal() ;
	delete frm;
	aqrecord->Active = false;
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStaff::BtnDeleteClick(TObject *Sender)
{
	AnsiString sql,sdf;
	if (aqrecord->IsEmpty() ) {
    	return;
	}
	sql = "delete from SYS_StaffInfo where id = " + aqrecord->FieldByName("ID")->AsString ;
	if (aqrecord->FieldByName("ID")->AsInteger == 1) {
		sdf = "ȷ��ɾ���ɹ�Ա"+aqrecord->FieldByName("name")->AsString +"��" ;
	}
	else {
		sdf = "ȷ��ɾ��ҵ��Ա"+aqrecord->FieldByName("name")->AsString +"��" ;
	}

	if (MessageBox(0,sdf.c_str() ,"ɾ��ȷ��" ,MB_OKCANCEL)==1) {
		try {
			aqinit->Close();
			aqinit->SQL->Clear();
			aqinit->SQL->Add(sql);
			aqinit->ExecSQL();
		} catch (Exception &E) {
			MessageBox(0,"�����ݸ�ϵͳ���������й���������ɾ����","ɾ������" ,MB_ICONWARNING);
		}
	}
	aqrecord->Active = false;
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStaff::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStaff::BtnExportClick(TObject *Sender)
{
	if (aqrecord->RecordCount > 0) {
    	DbgridToExcel(DBGridrecord);
	}
}
//---------------------------------------------------------------------------

//Excel��������
bool __fastcall TfrmStaff::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		MessageBox(0,"û�����ݣ�","����ȷ��" ,MB_ICONWARNING);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  ��Excel�г��ַ�����ʾ
	v.OlePropertyGet("Cells",1,5).OlePropertySet("Value","�ɹ�Ա/ҵ��Ա" );

/*v.OlePropertyGet("Cells",2,1).OlePropertySet("Value","��λ����" );
	temptext = "'"+ etname->Text;
	v.OlePropertyGet("Cells",2,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",2,4).OlePropertySet("Value","��ϵ��" );
	temptext = "'"+ etcontax->Text;
	v.OlePropertyGet("Cells",2,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","��������" );
	temptext = "'"+ CBlocal->Text;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","�ɹ�Ա" );
	temptext = "'"+ CBsale->Text;
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());  */

	n=1;

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
		}
	}
	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}

	return false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStaff::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStaff::etnameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStaff::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStaff::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {     //�µ�
		BtnNew->Click();
	}
	if (Key == VK_F3) {     //�޸�
		BtnFinish->Click();
	}
	if (Key == VK_F5) {     //ɾ��
		BtnDelete->Click();
	}
	if (Key == VK_F6) {     //����
		BtnExport->Click();
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

