//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include   <stdlib.h>


#include "SupplyInitForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzDBEdit"
#pragma resource "*.dfm"
TfrmSupplyInit *frmSupplyInit;
//---------------------------------------------------------------------------
__fastcall TfrmSupplyInit::TfrmSupplyInit(TComponent* Owner)
	: TfrmMDIChild(Owner)
{           	m_module = MTFinance;
}
//---------------------------------------------------------------------------
void TfrmSupplyInit::Init(TApplication* app, TADOConnection* con)
{              TfrmMDIChild::Init(app, con);
		this->Caption="供应商往来期初";
		dsSupplyInit->Connection=con;
		cmdaddMoney->Connection=con;
		qrySupply->Connection=con;
	   //	edtnum1->NumbersOnly=true;
			qrySupply->SQL->Add("select Name from CUST_CustomerInfo where type=1");
		qrySupply->Open();
		qrySupply->First();

	 while (!qrySupply->Eof)
	 {
	// ShowMessage(qrySupply->FieldByName("Name")->AsString);
		   cbbType->Items->Add(qrySupply->FieldByName("Name")->AsString);
		//cbbType->AddItem();
		qrySupply->Next();
	 }
	 qrySupply->Close();

}
void __fastcall TfrmSupplyInit::cbbTypeSelect(TObject *Sender)
{
		if(dsSupplyInit->Active)
		{
			  dsSupplyInit->Active=false;
		}
		String sql;
		sql="select id,Name,Telephone,Contact,Address,BookstoreLessBusiness,BusinessLessBookstore,Balance from  CUST_CustomerInfo where Type=1 and Name='"+cbbType->Text+"'";
		dsSupplyInit->CommandText = sql;
	   dsSupplyInit->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSupplyInit::FormClose(TObject *Sender, TCloseAction &Action)
{
		Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSupplyInit::RzToolButton3Click(TObject *Sender)
{
      Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSupplyInit::edtnum1KeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==VK_RETURN&&edtnum1->Text!="")
	{
	  if(MessageDlg("是否确认修改，输入的金额为："+edtnum1->Text+"?", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
	   {
	   String m=edtnum1->Text;
	   float  money=StrToFloat(m);

		  if (money>0) {



			  String sql="update CUST_CustomerInfo set BookstoreLessBusiness=BookstoreLessBusiness+"+m+" where id="+dsSupplyInit->FieldByName("id")->AsString;
			   cmdaddMoney->CommandText=sql;
			 cmdaddMoney->Execute();

		  }
		   else if(money<0) {


				m=FloatToStr(money);
				ShowMessage(m);

		 String sql="update CUST_CustomerInfo set Balance=Balance+Abs("+m+") where id="+dsSupplyInit->FieldByName("id")->AsString;
	    cmdaddMoney->CommandText=sql;
			 cmdaddMoney->Execute();
				}
			 edtnum1->Text="";
		  dsSupplyInit->Refresh();
	   }

	   }

}
//---------------------------------------------------------------------------


void __fastcall TfrmSupplyInit::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	   		if (Key==0x1B) {   //esc
			this->RzToolButton3->Click();
		}

}
//---------------------------------------------------------------------------

