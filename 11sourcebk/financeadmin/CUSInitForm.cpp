//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CUSInitForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmCUSInit *frmCUSInit;
//---------------------------------------------------------------------------
__fastcall TfrmCUSInit::TfrmCUSInit(TComponent* Owner)
	: TfrmMDIChild(Owner)
{   m_module = MTFinance;
}
void TfrmCUSInit::OnHotKeyPress(DWORD vkCode)
{

		if (vkCode==0x1B) {       //esc 键
				  this->RzToolButton3->Click();
			}

}
//---------------------------------------------------------------------------
 void TfrmCUSInit::Init(TApplication* app, TADOConnection* con)
{         TfrmMDIChild::Init(app, con);
	this->Caption="客户往来期初";
		dsSupplyInit->Connection=con;
		cmdaddMoney->Connection=con;
		qrySupply->Connection=con;
	   //	edtnum1->NumbersOnly=true;
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

void __fastcall TfrmCUSInit::cbbTypeSelect(TObject *Sender)
{
			if(dsSupplyInit->Active)
		{
			  dsSupplyInit->Active=false;
		}
		String sql;
		sql="select id,Name,Telephone,Contact,Address,BookstoreLessBusiness ,BusinessLessBookstore,Balance as Balance from  CUST_CustomerInfo where Type=2 and Name='"+cbbType->Text+"'";
		dsSupplyInit->CommandText = sql;
	   dsSupplyInit->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSInit::FormClose(TObject *Sender, TCloseAction &Action)
{
	   Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSInit::edtnum1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN&&edtnum1->Text!="")
	{
	  if(MessageDlg("是否确认修改，输入的金额为："+edtnum1->Text+"?", mtConfirmation, TMsgDlgButtons(mbOKCancel), 0)==true )
	   {
	   String m=edtnum1->Text;
	   float  money=StrToFloat(m);

		  if (money<0) {



				m=FloatToStr(money);
			  String sql="update CUST_CustomerInfo set Balance=Balance+Abs("+m+") where id=(select id from CUST_CustomerInfo where Name='"+cbbType->Text+"')";
			   cmdaddMoney->CommandText=sql;
			 cmdaddMoney->Execute();

		  }
		   else if(money>0) {



	 String sql="update CUST_CustomerInfo set BusinessLessBookstore=BusinessLessBookstore+Abs("+m+") where id="+dsSupplyInit->FieldByName("id")->AsString;
	   cmdaddMoney->CommandText=sql;
			 cmdaddMoney->Execute();
				}
				edtnum1->Text="";
		  dsSupplyInit->Refresh();
	   }

	   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSInit::RzToolButton3Click(TObject *Sender)
{
	  Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSInit::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN){
	  this->Close();
	 }
}
//---------------------------------------------------------------------------


