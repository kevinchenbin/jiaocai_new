//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PayGatherForm.h"
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
{            m_module = MTFinance;
	dtp1->Date=dtp1->Date .CurrentDate();
	dtp2->Date=dtp2->Date .CurrentDate();
}
//---------------------------------------------------------------------------
void TfrmPayGather::Init(TApplication* app, TADOConnection* con)
{        TfrmMDIChild::Init(app, con);
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
	 String sql=" select avg(Balance)as Balance, SUM(dbo.BS_StorageNote.Amount) AS Amount,Name,sum(BS_StorageNoteHeader.Nochecked) as NoChecked,sum(BS_StorageNoteHeader.TotalFixedPrice) as TotalFixedPrice,sum(BS_StorageNoteHeader.TotalDiscountedPrice)as TotalDiscountedPrice,sum(BS_StorageNoteHeader.Checked)as Checked,sum(BS_StorageNoteHeader.AddCosts) as AddCosts from CUST_CustomerInfo left join BS_StorageNoteHeader on SupplierID=CUST_CustomerInfo.id  left join BS_StorageNote on StgID=BS_StorageNote.ID where Type=1 ";


		 if (cbbType->Text!="全部供应商") {
		  sql=sql+" and Name='"+cbbType->Text+"'";
	 }
	 if (cbb2->Text=="进货") {
		 sql=sql+" and Amount>=0";
	 }
	 else
		  if (cbb2->Text=="退货") {
		 sql=sql+" and Amount<0";
	 }
	sql=sql+" and datediff(d,HdTime,'"+dtp1->Date+"')<=0 and datediff(d,HdTime,'"+dtp2->Date+"')>=0 group by CUST_CustomerInfo.Name";

	 if (chk1->Checked==true) {
		  sql=sql+" having sum(BS_StorageNoteHeader.Checked)=0";
	 }
   if (dsQuery->Active) {
	   dsQuery->Active=false;
   }
   dsQuery->CommandText=sql;
   dsQuery->Active=true;

}
//---------------------------------------------------------------------------

void __fastcall TfrmPayGather::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	        	   			if (Shift.Contains(ssCtrl)&&Key==81) {  //Q键
				  this->RzToolButton3->Click();
			}
			if (Key==0x1B) {       //esc 键
				  this->RzToolButton1->Click();
			}
}
//---------------------------------------------------------------------------

