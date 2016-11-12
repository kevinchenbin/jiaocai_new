//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PayGatherForm1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmPayGather *frmPayGather;
//---------------------------------------------------------------------------
__fastcall TfrmPayGather::TfrmPayGather(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
}
//---------------------------------------------------------------------------
void TfrmPayGather::Init(TApplication* app, TADOConnection* con)
{
  this->Caption="应付汇总";
  dsQuery->Connection=con;
  qrySupply->Connection=con;
      qrySupply->SQL->Clear();
	qrySupply->SQL->Add("select id,Name from CUST_CustomerInfo where type=1");
		qrySupply->Open();
		qrySupply->First();
		 while (!qrySupply->Eof)
		 {
			cbbType->Items->Add(qrySupply->FieldByName("Name")->AsString);
			qrySupply->Next();
		 }
		qrySupply->Close();


}
//---------------------------------------------------------------------------
void __fastcall TfrmPayGather::FormClose(TObject *Sender, TCloseAction &Action)
{
	    Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPayGather::RzToolButton1Click(TObject *Sender)
{
	 Close();

}
//---------------------------------------------------------------------------

void __fastcall TfrmPayGather::RzToolButton3Click(TObject *Sender)
{
	 String sql="select CUST_CustomerInfo.Name as Name,sum(TotalFixedPrice) as TotalFixedPrice, sum(TotalDiscountedPrice) as TotalDiscountedPrice,sum(AddCosts) as AddCosts,sum(Amount) as Amount,sum(Checked) as Checked,sum(NoChecked) as NoChecked,Balance";
	sql=sql+"from CUST_CustomerInfo left join BS_StorageNoteHeader on SupplierID=CUST_CustomerInfo.id  left join BS_StorageNote on StgID=BS_StorageNote.ID";
	sql=sql+"where Type=1 and datediff(d,HdTime,'"+dtp1->Date+"')<=0 and datediff(d,HdTime,'"+dtp2->Date+"')>=0 group by CUST_CustomerInfo.Name";
	 if (cbbType->Text!="全部供应商") {
		  sql=sql+" and Name='"+cbbType->Text+"'";
	 }
	 if (cbb1->Text=="进货") {
		 sql=sql+" and Amount>=0";
	 }
	 else
		  if (cbb1->Text=="退货") {
		 sql=sql+" and Amount<0";
	 }
	 if (chk1->Checked==true) {
          sql=sql+" and Checked=0";
	 }
   if (dsQuery->Active) {
	   dsQuery->Active=false;
   }
   dsQuery->CommandText=sql;
   dsQuery->Active=true;

}
//---------------------------------------------------------------------------

