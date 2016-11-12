//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CUSPayGatherForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmCUSPayGather *frmCUSPayGather;
//---------------------------------------------------------------------------
__fastcall TfrmCUSPayGather::TfrmCUSPayGather(TComponent* Owner)
	: TfrmMDIChild(Owner)
{      m_module = MTFinance;
	dtp1->Date=dtp1->Date .CurrentDate();
	dtp2->Date=dtp2->Date .CurrentDate();
}

//---------------------------------------------------------------------------
void TfrmCUSPayGather::Init(TApplication* app, TADOConnection* con)
{       TfrmMDIChild::Init(app, con);
     this->Caption="应收汇总";
  dsQuery->Connection=con;
  qrySupply->Connection=con;
      qrySupply->SQL->Clear();
	qrySupply->SQL->Add("select id,Name from CUST_CustomerInfo where type=2");
		qrySupply->Open();
		qrySupply->First();
		 while (!qrySupply->Eof)
		 {
			cbbType->Items->Add(qrySupply->FieldByName("Name")->AsString);
			qrySupply->Next();
		 }
		qrySupply->Close();

}

void __fastcall TfrmCUSPayGather::RzToolButton3Click(TObject *Sender)
{   if (cbbType->Text!="全部客户") {


		 String sql="select avg(Balance)as Balance, SUM(dbo.BS_WsaleNote.Amount) AS Amount,Name as Name1,sum(BS_WsaleNoteHeader.Nochecked) as NoChecked,sum(BS_WsaleNoteHeader.FixedPrice) as TotalFixedPrice,sum(BS_WsaleNoteHeader.DiscountedPrice)as TotalDiscountedPrice,sum(BS_WsaleNoteHeader.Checked)as Checked,sum(BS_WsaleNoteHeader.AddCosts) as AddCosts";
sql=sql+" from CUST_CustomerInfo left join BS_WsaleNoteHeader on VendorID=CUST_CustomerInfo.id left join BS_WsaleNote on WsaleNtHeaderID=BS_WsaleNoteHeader.id where Type=2 " ;
	 if (cbb2->Text=="进货") {
		 sql=sql+" and Amount>=0";
	 }
	 else
		  if (cbb2->Text=="退货") {
		 sql=sql+" and Amount<0";
	 }
	 if (cbbType->Text!="全部客户") {
		  sql=sql+" and Name='"+cbbType->Text+"'";
	 }
	 sql=sql+" and datediff(d,HdTime,'"+dtp1->Date+"')<=0 and datediff(d,HdTime,'"+dtp2->Date+"')>=0 group by CUST_CustomerInfo.Name";


	 if (chk1->Checked==true) {
		  sql=sql+" having sum(BS_WsaleNoteHeader.Checked)=0";
	 }
   if (dsQuery->Active) {
	   dsQuery->Active=false;
   }
   dsQuery->CommandText=sql;
   dsQuery->Active=true;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayGather::FormClose(TObject *Sender, TCloseAction &Action)

{
       Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayGather::RzToolButton1Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayGather::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	   			if (Shift.Contains(ssCtrl)&&Key==81) {  //Q键
				  this->RzToolButton3->Click();
			}
			if (Key==0x1B) {       //esc 键
				  this->RzToolButton1->Click();
			}
}
//---------------------------------------------------------------------------

