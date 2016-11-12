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
		this->Caption = "供应商资料";
	   //	DBGridrecord->Columns ->Items[5]->Title->Caption = "采购员";
		RzLabel1->Caption = "供应商名称" ;
	}
	if (type == 2) {
		this->Caption = "客户资料";
		RzLabel1->Caption = "客户名称"  ;
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
{  	//初始化销售人员
   AnsiString sql ,value;
   sql = "select A.ID,A.Name as salesman from SYS_User A left join SYS_UserGroup B on A.id =B.UserID left join SYS_group C ON B.GroupID = C.id "
		   " where C.groupname = '采购员'";

   if (type==2) {
   sql =  "select A.ID,A.Name as salesman from SYS_User A left join SYS_UserGroup B on A.id =B.UserID left join SYS_group C ON B.GroupID = C.id "
		   " where C.groupname = '业务员'";
		   Label3->Caption = "业务员：";
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
{  	//初始化单位
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
	//初始化地区
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
	if (aqrecord->FieldByName("name")->AsString == "普通供应商" ) {
		MessageBox(0,"普通供应商不能修改！","提示" ,MB_ICONWARNING);
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
	if (aqrecord->FieldByName("name")->AsString == "普通供应商" ) {
		MessageBox(0,"普通供应商不能删除！","提示" ,MB_ICONWARNING);
		return;
	}
	sqlSM = "delete from CUST_CustomerStartMoney where CustomerID = " + aqrecord->FieldByName("ID")->AsString ;
	sqlCUS = "delete from CUST_CustomerInfo where ID = " + aqrecord->FieldByName("ID")->AsString ;
	if (type == 1) {
		sdf = "确认删除供应商"+aqrecord->FieldByName("name")->AsString +"吗？" ;
	}
	if (type == 2) {
		sdf = "确认删除客户"+aqrecord->FieldByName("name")->AsString +"吗？" ;
	}

	if (MessageBox(0,sdf.c_str() ,"删除确认" ,MB_ICONQUESTION|MB_OKCANCEL)==1) {
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
			MessageBox(0,"该数据跟系统其他数据有关联，不能删除！","删除错误" ,MB_ICONWARNING);
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
		DBGridrecord->Columns->Items[1]->Title->Caption = "供应商名称";
	}
	if (type == 2) {
    	DBGridrecord->Columns->Items[1]->Title->Caption = "客户名称";
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

//Excel导出函数
bool __fastcall TSuppMana::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		MessageBox(0,"没有数据！","错误确认" ,MB_ICONWARNING);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",false);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	if (type == 1) {
		v.OlePropertyGet("Cells",1,5).OlePropertySet("Value","供应商查询记录" );
	}
	else
	{
		v.OlePropertyGet("Cells",1,5).OlePropertySet("Value","客户查询记录" );
	}

/*v.OlePropertyGet("Cells",2,1).OlePropertySet("Value","单位名称" );
	temptext = "'"+ etname->Text;
	v.OlePropertyGet("Cells",2,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",2,4).OlePropertySet("Value","联系人" );
	temptext = "'"+ etcontax->Text;
	v.OlePropertyGet("Cells",2,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","所属区域" );
	temptext = "'"+ CBlocal->Text;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","采购员" );
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
	if (Key == VK_F2) {     //新单
		BtnNew->Click();
	}
	if (Key == VK_F3) {     //修改
		BtnFinish->Click();
	}
	if (Key == VK_F5) {     //删除
		BtnDelete->Click();
	}
	if (Key == VK_F6) {     //导出
		BtnExport->Click();
	}
	if (Key == VK_F7) {     //导入
		BtnImport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		BtnView->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
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

