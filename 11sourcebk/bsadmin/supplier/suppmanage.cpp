//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "suppmanage.h"
#include "detailemessage.h"
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
	if (type == 1) {
		this->Caption = "供应商管理";
	}
	if (type == 2) {
        this->Caption = "客户管理";
	}
}
//---------------------------------------------------------------------------
void TSuppMana::Initsalesman()
{  	//初始化销售人员
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
void __fastcall TSuppMana::BtnViewClick(TObject *Sender)
{
	AnsiString sql,sqlwhere;
	sql = "select A.ID,A.name,A.contact,A.telephone,A.fax,C.salesman,A.code,Convert(varchar(20),A.date,111) as date,A.address,A.local  from cust_customerinfo A left join Sys_local B on " ;
	sql = sql + " A.Local = b.Local left join Sys_salesman c on A.salesman = C.salesman ";
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
		sqlwhere = sqlwhere + " and C.Salesman = '" + CBsale->Text.Trim() +"'";
	}
	sql = sql+sqlwhere;
	aqrecord->Close();
	aqrecord->SQL->Clear();
	aqrecord->SQL->Add(sql);
	aqrecord->Open();
	DBGridrecord->Columns->Items[0]->Width = 64;
	DBGridrecord->Columns->Items[1]->Width = 80;
	DBGridrecord->Columns->Items[2]->Width = 64;
	DBGridrecord->Columns->Items[3]->Width = 72;
	DBGridrecord->Columns->Items[4]->Width = 72;
	DBGridrecord->Columns->Items[5]->Width = 64;
	DBGridrecord->Columns->Items[6]->Width = 64;
	DBGridrecord->Columns->Items[7]->Width = 64;
	DBGridrecord->Columns->Items[8]->Width = 80;
	DBGridrecord->Columns->Items[9]->Width = 64;
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnNewClick(TObject *Sender)
{
	TDetaileForm * frm = new TDetaileForm(Application,type,1,"",cn);
	frm->ShowModal() ;
	delete frm;
	BtnView->Click();
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnFinishClick(TObject *Sender)
{
	TDetaileForm * frm = new TDetaileForm(Application,type,2,aqrecord->FieldByName("ID")->AsString,cn);
	frm->ShowModal() ;
	delete frm;
	BtnView->Click();
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnDeleteClick(TObject *Sender)
{
	AnsiString sqlSM,sqlCUS,sdf;
	sqlSM = "delete from CUST_CustomerStartMoney where CustomerID = " + aqrecord->FieldByName("ID")->AsString ;
	sqlCUS = "delete from CUST_CustomerInfo where ID = " + aqrecord->FieldByName("ID")->AsString ;
	if (type == 1) {
		sdf = "确认删除供应商"+aqrecord->FieldByName("name")->AsString +"吗？" ;
	}
	if (type == 2) {
		sdf = "确认删除客户"+aqrecord->FieldByName("name")->AsString +"吗？" ;
	}

	if (MessageBox(0,sdf.c_str() ,"删除确认" ,MB_OKCANCEL)==1) {
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
			MessageBox(0,"该数据跟系统其他数据有关联，不能删除！","删除错误" ,MB_OK);
		}
	}
	BtnView->Click();
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
	if (type == 1) {
		DBGridrecord->Columns->Items[1]->Title->Caption = "供应商名称";
	}
	if (type == 2) {
    	DBGridrecord->Columns->Items[1]->Title->Caption = "客户名称";
	}
}
//---------------------------------------------------------------------------

