//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CUSDocQueryForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmCUSDocQuery *frmCUSDocQuery;
//---------------------------------------------------------------------------
__fastcall TfrmCUSDocQuery::TfrmCUSDocQuery(TComponent* Owner)
	: TfrmMDIChild(Owner)
{     m_module = MTFinance;
	dtp1->Date=dtp1->Date .CurrentDate();
	dtp2->Date=dtp2->Date .CurrentDate();
}

//---------------------------------------------------------------------------
void TfrmCUSDocQuery::Init(TApplication* app, TADOConnection* con)
{                TfrmMDIChild::Init(app, con);
		   this->Caption="收款单查询" ;
	   dsDoc->Connection=con;
	   qrySupply->Connection=con;
	   dsSNoteHD->Connection=con;
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
void TfrmCUSDocQuery::query()
{
  if (cbbType->Text!="全部客户")
	 {
					if (dsDoc->Active) {
			  dsDoc->Active=false;
		   }


		   String sql="select MoneyCode,CustmerName,Payment,ClearingType,date,Remarks,Salesman,Clearingstyle,CASE State WHEN 1 THEN '审核' WHEN 0 THEN '未审核' END  as State from FN_CUSEndMoneyDocuments where CustmerName='"+cbbType->Text+"' and datediff(d,date,'"+dtp1->Date+"')<=0 and datediff(d,date,'"+dtp2->Date+"')>=0";
			 if (cbb2->Text=="未审核") {
			   sql=sql+" and State=0";
			 }
			 else 	 if (cbb2->Text=="审核") {
			   sql=sql+" and State=1";
			 }
			 if (cbb1->Text!="全部") {
				sql=sql+" and ClearingType='"+cbb1->Text+"'";
			 }
			  if (cbb3->Text!="全部") {
				sql=sql+" and Clearingstyle='"+cbb3->Text+"'";
			 }
		  dsDoc->CommandText=sql;

		  dsDoc->Active=true;
	  }
}
void __fastcall TfrmCUSDocQuery::RzToolButton3Click(TObject *Sender)
{
	   this->query();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSDocQuery::rzdbgrd1DblClick(TObject *Sender)
{
     		if (dsSNoteHD->Active) {
		  dsSNoteHD->Active=false;
		  }
		  String sql="select * from BS_WsaleNoteHeader left join FN_CUSEndMoneyDtails on WsaleNtCode=WsaleNTHDcode where WsaleEndMoneycode="+dsDoc->FieldByName("MoneyCode")->AsString;
		  if (!dsDoc->IsEmpty()) {


		dsSNoteHD->CommandText=sql;
		  dsSNoteHD->Active=true;
		   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSDocQuery::FormClose(TObject *Sender, TCloseAction &Action)

{
	    Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSDocQuery::RzToolButton1Click(TObject *Sender)
{
	     Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSDocQuery::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	  		if (Key==0x1B) {   //esc
			this->RzToolButton1->Click();

		}

		if (Shift.Contains(ssCtrl)&&Key==81) {   //Q
			this->RzToolButton3->Click();

		}
}
//---------------------------------------------------------------------------

