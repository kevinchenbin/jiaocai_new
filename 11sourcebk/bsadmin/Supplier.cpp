//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Supplier.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmSupplierinfo *frmSupplierinfo;
//---------------------------------------------------------------------------
__fastcall TfrmSupplierinfo::TfrmSupplierinfo(TComponent* Owner,int type)
	: TForm(Owner)
{
   Ftype =  type;
}
void  TfrmSupplierinfo::Init(LandInfo* li)
{
	if (Ftype == 2) {
		this->Caption = "客户管理";
		rzgb->Caption = "客户基本信息";
		Title = "客户管理";
		cbsale->Visible = true;
        sale->Visible = true;
	}
    cn = li->con ;
    Title = this->Caption ;
	aqsupplier->Connection = li->con ;

}

void TfrmSupplierinfo::GetCDS(String SQLstr, TADOQuery *aqury)
{
	aqury->Connection = cn;
	aqury->Close();
	aqury->SQL->Clear();
	aqury->SQL->Add(SQLstr);
	aqury->Prepared = true;
	aqury->Open();

}

void TfrmSupplierinfo::ReadyData()
{
	  TADOQuery * aq = new TADOQuery(this);
	  String sql;
	  sql = "select * from sys_local";
	  GetCDS(sql,aq);
	  while(!aq->Eof)
	  {
		cblocal->Items->AddObject(aq->FieldByName("local")->AsAnsiString ,(TObject*) aq->FieldByName("ID")->AsInteger);
		aq->Next();
	  }

	  sql = "select * from sys_salesman";
	  GetCDS(sql,aq);
	  while(!aq->Eof)
	  {
		cbsale->Items->AddObject(aq->FieldByName("salesman")->AsAnsiString ,(TObject*) aq->FieldByName("ID")->AsInteger);
		aq->Next();
	  }



	 delete aq;
}
int TfrmSupplierinfo::ExecSQL(String sqlstr)
{
   TADOQuery * aq = new TADOQuery(NULL);
   aq->Connection = cn;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sqlstr);
   aq->Prepared = true;
   if (aq->ExecSQL() != -1)
   {
	 return 1;
   }else
   {
	 return 0;
   }
   delete aq;


}
//---------------------------------------------------------------------------
void __fastcall TfrmSupplierinfo::FormShow(TObject *Sender)
{
   AnsiString sql;
   sql = "select ID,name,Contact,address,type,local,code,telephone,fax,date," ;
   sql = sql + "salesman,local from cust_customerinfo  where type  = "+IntToStr(Ftype);
   aqsupplier->Close();
   aqsupplier->SQL->Clear();
   aqsupplier->SQL->Add(sql);
   aqsupplier->Open();
   ReadyData();
   //EnableEdit(false);

}
//---------------------------------------------------------------------------



void __fastcall TfrmSupplierinfo::FormClose(TObject *Sender, TCloseAction &Action)

{
  Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSupplierinfo::rtbdelClick(TObject *Sender)
{
	   String sql;
	   TADOQuery * aq;

       aq = new TADOQuery(this);


	   if (MessageBox(0,"确认要删除吗？",Title.c_str() ,MB_ICONQUESTION|MB_OKCANCEL)==1) {
		   sql = "select count(*) as count from STK_bookinfo where SupplierID='"+ aqsupplier->FieldByName("ID")->AsAnsiString   +"'";
		   GetCDS(sql,aq);
		   if (aq->FieldByName("count")->AsInteger !=0  ) {


			 MessageBox(0,"该供应商具有业务数据关联，不能删除！",Title.c_str(),MB_ICONEXCLAMATION);

		   }  else
		   {
			  aqsupplier->Edit();
			  aqsupplier->Delete();
			  aqsupplier->UpdateBatch(arAll);
		   }
	   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmSupplierinfo::rtbaddClick(TObject *Sender)
{

	edtcompany->Text = "";
	edtaddress->Text  = "";
	edtcode->Text = "";
	edtcontact->Text = "";
	edtfax->Text = "";
	edtphone->Text = "";


	EnableEdit(false);

	rtbadd->Enabled = false;
	rtbsave->Enabled = true;

}
//---------------------------------------------------------------------------
void TfrmSupplierinfo::EnableEdit(BOOL value)
{

	edtcompany->ReadOnly  = value;
	edtaddress->ReadOnly  = value;
	edtcode->ReadOnly  = value;
	edtcontact->ReadOnly  = value;
	edtfax->ReadOnly  = value;
	edtphone->ReadOnly  = value;


}

void __fastcall TfrmSupplierinfo::rtbmodifyClick(TObject *Sender)
{
  EnableEdit(false);
  rtbmodify->Enabled = false;
  rtbsave->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSupplierinfo::rtbsaveClick(TObject *Sender)
{
   if (!rtbmodify->Enabled ) {
	   rtbmodify->Enabled = true;
	   aqsupplier->Edit();
   }
   if (!rtbadd->Enabled) {
		rtbadd->Enabled  = true;
		aqsupplier->Insert();
		aqsupplier->Append();

   }


	aqsupplier->FieldByName("name")->AsAnsiString =  edtcompany->Text.Trim();
	aqsupplier->FieldByName("Contact")->AsAnsiString  = edtcontact->Text.Trim();
	aqsupplier->FieldByName("address")->AsAnsiString  = edtaddress->Text.Trim();
	aqsupplier->FieldByName("local")->AsAnsiString   = cblocal->Text ;
	aqsupplier->FieldByName("code")->AsAnsiString    = edtcode->Text.Trim();
	aqsupplier->FieldByName("telephone")->AsAnsiString = edtphone->Text.Trim();
	aqsupplier->FieldByName("fax")->AsAnsiString  = edtfax->Text.Trim();
	aqsupplier->FieldByName("type")->AsAnsiString = 1;
	if (Ftype==2) {
	aqsupplier->FieldByName("type")->AsAnsiString = 2;
	}


   aqsupplier->UpdateBatch(arAll) ;
   EnableEdit(true);


}
//---------------------------------------------------------------------------

void __fastcall TfrmSupplierinfo::dbGridCustCellClick(TColumn *Column)
{
		edtcompany->Text = aqsupplier->FieldByName("name")->AsAnsiString ;
		edtcontact->Text  =	aqsupplier->FieldByName("Contact")->AsAnsiString;
		edtaddress->Text=	aqsupplier->FieldByName("address")->AsAnsiString;
		cblocal->Text	= aqsupplier->FieldByName("local")->AsAnsiString;
		edtcode->Text =	aqsupplier->FieldByName("code")->AsAnsiString ;
		edtphone->Text=	aqsupplier->FieldByName("telephone")->AsAnsiString ;
		edtfax->Text =	aqsupplier->FieldByName("fax")->AsAnsiString;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSupplierinfo::rtbexitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

