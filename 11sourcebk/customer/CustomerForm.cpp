//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CustomerForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzLine"
#pragma link "RzPanel"
#pragma link "MDIChild"
#pragma resource "*.dfm"
TfrmCustomer *frmCustomer;
//---------------------------------------------------------------------------
__fastcall TfrmCustomer::TfrmCustomer(TComponent* Owner)
	: TfrmMDIChild(Owner)
{        m_module = MTCustom;

}

//---------------------------------------------------------------------------
void __fastcall TfrmCustomer::SetCustomerType(int type)
{
   /*	m_type=type;
      	if (dsetCustomer->Active)
	{
		dsetCustomer->Active = false;
	}
	String sql;

	if (m_type == 1)
		{
			sql = "select * from CUST_CustomerInfo where (Type = '1' and ID > 0) or ID=0";
		}
		else if (m_type ==2)
		{
			sql = "select * from CUST_CustomerInfo where (Type = '2' and ID > 0) or ID=0 ";
		}

		dsetCustomer->CommandText=sql;
		dsetCustomer->Active=true;
   //	Query("", m_type);   */
}
//---------------------------------------------------------------------------

void __fastcall TfrmCustomer::rtbaddClick(TObject *Sender)
{
//添加记录
  /*   dbedtName->ReadOnly=false;
	  dbeditContact->ReadOnly=false;
	  RzDBEdit1->ReadOnly=false;
	  RzDBEdit5->ReadOnly=false;
	  dbedit->ReadOnly=false;
	  RzDBEdit4->ReadOnly=false;
	  RzDBEdit10->ReadOnly=false;
     dbedtName->SetFocus();
   if (dsetCustomer->State == dsInsert&&dbedtName->Text!= "")
	{
		dbcbbType->ReadOnly = false;
		if (m_type == CT_Supplier)
		{
			dbcbbType->Value = "1";
		}
		else
		{
			dbcbbType->Value = "2";
		}
		//dsetCustomer->Post();
		dbcbbType->ReadOnly = true;

		if (dbcbbType->Text=="销售商") {
		   dsetCustomer->FieldByName("Type")->AsString=IntToStr(2);
		}
		dsetCustomer->Post();
	  	dsetCustomer->Refresh();
	}
	else
	{
			dsetCustomer->Append();

 }     */
}

//---------------------------------------------------------------------------

void __fastcall TfrmCustomer::RzToolButton5Click(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------


void __fastcall TfrmCustomer::RzToolButton1Click(TObject *Sender)
{
	//

	//Query(edtQuery->Text, m_type);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCustomer::rtbdelClick(TObject *Sender)
{
	//删除记录
 /*	try{
						 
			 
				  

					 if(MessageDlg("您确认删除吗？", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true)
						{
							if(!dsetCustomer->IsEmpty())
							{     if (dsetCustomer->FieldByName("id")->AsInteger!=0&&dsetCustomer->FieldByName("id")->AsInteger!=104)
								 {
	
								  cmddel->CommandText="delete from CUST_CustomerInfo  where id="+dsetCustomer->FieldByName("id")->AsString;
								  cmddel->Execute();
								  
								  }
								  else
								  {ShowMessage("系统默认客户不能删除");}
							}
								Query(edtQuery->Text, m_type);
					}
					
					  
	 }
	 catch(Exception &E)
	 {
			ShowMessage("此数据更系统其他地方有关联，不能删除！");
	 }   */

}
 //---------------------------------------------------------------------------

void TfrmCustomer::Query(String condition, CustomerType type)
{
  /*	if (dsetCustomer->Active)
	{
		dsetCustomer->Active = false;
	}
	String sql;
	if (condition == "")
	{
		if (m_type == CT_Supplier)
		{
			sql = "select * from CUST_CustomerInfo where (Type = '1' and ID>0) or ID=0";
		}
		else if (m_type == CT_Vendor)
		{
			sql = "select * from CUST_CustomerInfo where (Type = '2' and ID>0) or ID=0";
		}
		else
		{
			sql = "select * from CUST_CustomerInfo ";
        }
	}
	else
	{
		if (m_type == CT_Supplier)
		{
			sql = "select * from CUST_CustomerInfo where (Type = '1'  and Name like '%" + condition + "%' and ID>0) or ID=0";
		}
		else if (m_type == CT_Vendor)
		{
			sql = "select * from CUST_CustomerInfo where (Type = '2' and Name like '%" + condition + "%' and ID>0) or ID=0";
		}
		else
		{
			sql = "select * from CUST_CustomerInfo where (Name like '%" + condition + "%' and ID>0) or ID=0";
        }
	}
	dsetCustomer->CommandText = sql;
	dsetCustomer->Active = true;	 */
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TfrmCustomer::RzToolButton3Click(TObject *Sender)
{
	/*	dbedtName->SetFocus();
	  dbedtName->ReadOnly=false;
	  dbeditContact->ReadOnly=false;
	  RzDBEdit1->ReadOnly=false;
	  RzDBEdit5->ReadOnly=false;
	  dbedit->ReadOnly=false;
	  RzDBEdit4->ReadOnly=false;
	  RzDBEdit10->ReadOnly=false; */

}
//---------------------------------------------------------------------------

void TfrmCustomer::ShowData()
{
   AnsiString sql;
   sql = "select A.ID,A.name,A.contact,A.telephone,A.fax,C.salesman,A.code,A.date,A.address,B.local  from cust_customerinfo A left join Sys_local B on " ;
   sql = sql + " A.Local = b.ID left join Sys_salesman c on A.salesman = C.ID ";
   sql = sql + " where type  = 1";
   aqsupplier->Close();
   aqsupplier->SQL->Clear();
   aqsupplier->SQL->Add(sql);
   aqsupplier->Open();
}
void TfrmCustomer::UpdateSupplier()
{
  AnsiString sql;
  AnsiString salesmanID,LocalID;



	 if (cbsaler->Text.Trim() == "") {
		 salesmanID = 0;
	 }
	 else
	 {
	   salesmanID = salesman->Values[cbsaler->Text.Trim()];
	 }
	 if (cblocal->Text.Trim()=="") {

	   LocalID = 0;
	 }else
	 {
	  LocalID = local->Values[cblocal->Text.Trim()];
	 }
   //

  //


  sql = "Insert into cust_customerinfo(name,contact,telephone,fax,salesman,code,date,address,local) ";
  sql = sql + " values('" + dbedtName->Text + "','" + dbeditContact->Text.Trim()+"','" + edtphone->Text + "','";
  sql = sql + edtfax->Text.Trim() + "','" + salesmanID + "','" + edtcode->Text.Trim();
  sql = sql + "',GetDate(),'" +  dbedit->Text.Trim()+ "','" + LocalID + "')";

  aqinit->Close();
  aqinit->SQL->Clear();
  aqinit->SQL->Add(sql);
  aqinit->ExecSQL();


}
void TfrmCustomer::Initsalesman()
{                               //初始化销售人员
   AnsiString sql ,value;
   sql = "select ID , salesman from SYS_salesman";
   salesman = new TStringList();
   cbsaler->Items->Clear();
   aqinit->Close();
   aqinit->SQL->Clear();
   aqinit->SQL->Add(sql);
   aqinit->Open();
   while(!aqinit->Eof )
   {
	 value = "'"+ aqinit->FieldByName("salesman")->AsAnsiString + "'='" + aqinit->FieldByName("ID")->AsAnsiString +"'" ;
	 cbsaler->Items->Text = aqinit->FieldByName("salesman")->AsAnsiString;
	 salesman->Add(value);
	 aqinit->Next();
   }

}
void TfrmCustomer::InitLocalinfo()
{
							   //初始化地区
   AnsiString sql ,value;
   sql = "select ID,local from SYS_local";
   cbsaler->Items->Clear();
   local = new TStringList();
   aqinit->Close();
   aqinit->SQL->Clear();
   aqinit->SQL->Add(sql);
   aqinit->Open();
   while(!aqinit->Eof)
   {

	 value = "'"+ aqinit->FieldByName("Local")->AsAnsiString + "'='" + aqinit->FieldByName("ID")->AsAnsiString +"'" ;
	 cbsaler->Items->Text = aqinit->FieldByName("Local")->AsAnsiString;
	 salesman->Add(value);
	 aqinit->Next();
   }
}




void __fastcall TfrmCustomer::BtnSaveClick(TObject *Sender)
{
	  UpdateSupplier();
	  ShowData();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCustomer::BtnExitClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------



void __fastcall TfrmCustomer::FormShow(TObject *Sender)
{
   BtnSave->Enabled = false;
   BtnDelete->Enabled  = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCustomer::BtnNewClick(TObject *Sender)
{
  BtnSave->Enabled  = true;
}
//---------------------------------------------------------------------------



