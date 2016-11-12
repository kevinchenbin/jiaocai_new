//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "suppmanage.h"
#include "detailemessage.h"
#include "CoustomerImport.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TSuppMana *SuppMana;
//---------------------------------------------------------------------------
__fastcall TSuppMana::TSuppMana(TComponent* Owner,int Type,TADOConnection *cnn)
	: TForm(Owner)
{
	type = Type;
    cn = cnn;
	aqinit->Connection = cnn;
	aqrecord->Connection = cnn;
	query->Connection = cnn;
	if (type == 1) {
		this->Caption = "��Ӧ������";
	   //	DBGridrecord->Columns ->Items[5]->Title->Caption = "�ɹ�Ա";
		RzLabel1->Caption = "��Ӧ������" ;
	}
	if (type == 2) {
		this->Caption = "�ͻ�����";
		RzLabel1->Caption = "�ͻ�����"  ;
	}
	AnsiString sql;
	int maxid;
	sql = "select max(ID) as id from cust_customerinfo";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	maxid = query->FieldByName("id")->AsInteger ;

		sql = "select A.Type,A.ID,A.name,A.contact,A.telephone,A.fax,A.Salesman,A.code,A.date,Convert(varchar(20),A.date,111) as date1,A.address,A.local,A.Balance,A.BusinessLessBookstore,A.BookstoreLessBusiness  from cust_customerinfo A left join Sys_local B on "
			  "A.Local = b.Local left join SYS_User C on A.salesman = C.Name "
			  " where A.ID > " + IntToStr(maxid) ;

	aqrecord->Close();
	aqrecord->SQL->Clear();
	aqrecord->SQL->Add(sql);

       AnsiString sql1;









}
//---------------------------------------------------------------------------
void TSuppMana::Initsalesman()
{  	//��ʼ��������Ա
   AnsiString sql ,value;
   sql = "select A.ID,A.Name as salesman from SYS_User A left join SYS_UserGroup B on A.id =B.UserID left join SYS_group C ON B.GroupID = C.id "
		   " where C.groupname = '�ɹ�Ա'";

   if (type==2) {
   sql =  "select A.ID,A.Name as salesman from SYS_User A left join SYS_UserGroup B on A.id =B.UserID left join SYS_group C ON B.GroupID = C.id "
		   " where C.groupname = 'ҵ��Ա'";
		   Label3->Caption = "ҵ��Ա��";
   }

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
//---------------------------------------------------------------------------
void TSuppMana::Initname()
{  	//��ʼ����λ
   AnsiString sql ,value;
   sql = "select Name from CUST_CustomerInfo where Type = " + IntToStr(type);

   aqinit->Close();
   aqinit->SQL->Clear();
   aqinit->SQL->Add(sql);
   aqinit->Open();
   while(!aqinit->Eof )
   {
	 etname->Add(aqinit->FieldByName("Name")->AsString);
	 aqinit->Next();
   }
}
//---------------------------------------------------------------------------
void TSuppMana::InitLocalinfo()
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
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnViewClick(TObject *Sender)
{
	AnsiString sql,sqlwhere;
	sql = "select rank() over(order by A.id) as xuhao,A.Type,A.ID,A.name,A.contact,A.telephone,A.fax,A.Salesman,A.code,A.date,Convert(varchar(20),A.date,111) as date1,A.address,A.local,A.Balance,A.BusinessLessBookstore,A.BookstoreLessBusiness from cust_customerinfo A left join Sys_local B on " ;
	sql = sql + "A.Local = b.Local left join SYS_User C on A.salesman = C.Name ";


	sqlwhere = " where type  = " + IntToStr(type);
	if (etname->Text != "") {
		sqlwhere = sqlwhere + " and A.name like '%" + etname->Text.Trim() + "%'";
	}
	if (etcontax->Text != "") {
		sqlwhere = sqlwhere +  " and A.Contact like '%" + etcontax->Text + "%'";
	}
	if (CBlocal->Text != "") {
		sqlwhere = sqlwhere + " and B.Local = '" + CBlocal->Text.Trim() +"'";
	}
	if (CBsale->Text !="") {
		sqlwhere = sqlwhere + " and c.name = '" + CBsale->Text.Trim() +"'";
	}
	sql = sql+sqlwhere;
	aqrecord->Close();
	aqrecord->SQL->Clear();
	aqrecord->SQL->Add(sql);
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Open();
	/*DBGridrecord->Columns->Items[0]->Width = 64;
	DBGridrecord->Columns->Items[1]->Width = 120;
	DBGridrecord->Columns->Items[2]->Width = 64;
	DBGridrecord->Columns->Items[3]->Width = 72;
	DBGridrecord->Columns->Items[4]->Width = 72;
	DBGridrecord->Columns->Items[5]->Width = 64;
	DBGridrecord->Columns->Items[6]->Width = 64;
	DBGridrecord->Columns->Items[7]->Width = 64;
	DBGridrecord->Columns->Items[8]->Width = 80;
	DBGridrecord->Columns->Items[9]->Width = 64;  */
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnNewClick(TObject *Sender)
{
	TDetaileForm * frm = new TDetaileForm(Application,type,1,"",cn);
	frm->ShowModal() ;
	delete frm;
	//aqrecord->Close();
	//aqrecord->Open();
	aqrecord->Active = false;
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Active = true;
	/*DBGridrecord->Columns->Items[0]->Width = 64;
	DBGridrecord->Columns->Items[1]->Width = 120;
	DBGridrecord->Columns->Items[2]->Width = 64;
	DBGridrecord->Columns->Items[3]->Width = 72;
	DBGridrecord->Columns->Items[4]->Width = 72;
	DBGridrecord->Columns->Items[5]->Width = 64;
	DBGridrecord->Columns->Items[6]->Width = 64;
	DBGridrecord->Columns->Items[7]->Width = 64;
	DBGridrecord->Columns->Items[8]->Width = 80;
	DBGridrecord->Columns->Items[9]->Width = 64;  */
	//BtnView->Click();
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnFinishClick(TObject *Sender)
{
	if (aqrecord->IsEmpty() ) {
    	return;
	}
	if (aqrecord->FieldByName("name")->AsString == "��ͨ��Ӧ��" ) {
		MessageBox(0,"��ͨ��Ӧ�̲����޸ģ�","��ʾ" ,MB_ICONWARNING);
		return;
	}
	TDetaileForm * frm = new TDetaileForm(Application,type,2,aqrecord->FieldByName("ID")->AsString,cn);
	frm->ShowModal() ;
	delete frm;
	aqrecord->Active = false;
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnDeleteClick(TObject *Sender)
{
	AnsiString sqlSM,sqlCUS,sdf;
	if (aqrecord->IsEmpty() ) {
    	return;
	}
	if (aqrecord->FieldByName("name")->AsString == "��ͨ��Ӧ��" ) {
		MessageBox(0,"��ͨ��Ӧ�̲���ɾ����","��ʾ" ,MB_ICONWARNING);
		return;
	}
	sqlSM = "delete from CUST_CustomerStartMoney where CustomerID = " + aqrecord->FieldByName("ID")->AsString ;
	sqlCUS = "delete from CUST_CustomerInfo where ID = " + aqrecord->FieldByName("ID")->AsString ;
	if (type == 1) {
		sdf = "ȷ��ɾ����Ӧ��"+aqrecord->FieldByName("name")->AsString +"��" ;
	}
	if (type == 2) {
		sdf = "ȷ��ɾ���ͻ�"+aqrecord->FieldByName("name")->AsString +"��" ;
	}

	if (MessageBox(0,sdf.c_str() ,"ɾ��ȷ��" ,MB_ICONQUESTION|MB_OKCANCEL)==1) {
		try {
			aqinit->Close();
			aqinit->SQL->Clear();
			aqinit->SQL->Add(sqlSM);
			aqinit->ExecSQL();
			aqinit->Close();
			aqinit->SQL->Clear();
			aqinit->SQL->Add(sqlCUS);
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
void __fastcall TSuppMana::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::FormShow(TObject *Sender)
{
	Initsalesman();
	InitLocalinfo();
	Initname();
	if (type == 1) {
		DBGridrecord->Columns->Items[1]->Title->Caption = "��Ӧ������";
	}
	if (type == 2) {
    	DBGridrecord->Columns->Items[1]->Title->Caption = "�ͻ�����";
	}

}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::BtnExportClick(TObject *Sender)
{
	if (!aqrecord->IsEmpty() ) {
    	DbgridToExcel(DBGridrecord);
	}
}
//---------------------------------------------------------------------------

//Excel��������
bool __fastcall TSuppMana::DbgridToExcel(TRzDBGrid* dbg)
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
	v.OlePropertySet("Visible",false);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  ��Excel�г��ַ�����ʾ
	if (type == 1) {
		v.OlePropertyGet("Cells",1,5).OlePropertySet("Value","��Ӧ�̲�ѯ��¼" );
	}
	else
	{
		v.OlePropertyGet("Cells",1,5).OlePropertySet("Value","�ͻ���ѯ��¼" );
	}

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



void __fastcall TSuppMana::etcontaxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::CBlocalKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::CBsaleKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------


void __fastcall TSuppMana::BtnImportClick(TObject *Sender)
{
	aqrecord->Active = true;
	TFormCousImport *frm = new TFormCousImport(Application,aqrecord,1);
	frm->Show();
	/*DBGridrecord->Columns->Items[0]->Width = 64;
	DBGridrecord->Columns->Items[1]->Width = 120;
	DBGridrecord->Columns->Items[2]->Width = 64;
	DBGridrecord->Columns->Items[3]->Width = 72;
	DBGridrecord->Columns->Items[4]->Width = 72;
	DBGridrecord->Columns->Items[5]->Width = 64;
	DBGridrecord->Columns->Items[6]->Width = 64;
	DBGridrecord->Columns->Items[7]->Width = 64;
	DBGridrecord->Columns->Items[8]->Width = 80;
	DBGridrecord->Columns->Items[9]->Width = 64; */
}
//---------------------------------------------------------------------------



void __fastcall TSuppMana::etnameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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
	if (Key == VK_F7) {     //����
		BtnImport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //��ѯ
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

void __fastcall TSuppMana::edqueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == '\r') {
		if (edquery->Text == "") {
			return;
		}
		AnsiString sql;
		sql = "select id,Name from cust_customerinfo where name like '%" + edquery->Text.Trim() + "%' and type = 1";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		etname->Clear();
		while (!query->Eof )
		{
			etname->AddItem(query->FieldByName("name")->AsAnsiString,(TObject*)query->FieldByName("id")->AsInteger );
			query->Next();
		}
		query->First();
		etname->ItemIndex = (int)etname->Items->IndexOfObject((TObject*)query->FieldByName("id")->AsInteger );
	}
}
   void TSuppMana::lock()
   {

            if (add) {
               BtnNew->Enabled= true;
            }else  BtnNew->Enabled= false;

            if (modify) {
              BtnFinish->Enabled= true;
            }else BtnFinish->Enabled= false;
            if (del) {
                BtnDelete->Enabled= true;
            } else  BtnDelete->Enabled= false;


           





   }
//---------------------------------------------------------------------------

