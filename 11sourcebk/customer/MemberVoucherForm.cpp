//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberVoucherForm.h"
//#include "SelectMemberForm.h"
#include "customer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "MDIChild"
#pragma resource "*.dfm"
TfrmMemberVoucher *frmMemberVoucher;
//---------------------------------------------------------------------------
__fastcall TfrmMemberVoucher::TfrmMemberVoucher(TComponent* Owner)
	: TfrmMDIChild(Owner)
	, m_app(NULL)
	, m_con(NULL)
{   m_module = MTFinance;
	dtp1->Date=dtp1->Date .CurrentDate();
		dtp2->Date=dtp2->Date .CurrentDate();
}
//---------------------------------------------------------------------------



void TfrmMemberVoucher::Init(TApplication* app, TADOConnection* con)
{       TfrmMDIChild::Init(app, con);
	m_app = app;
	m_con = con;
		dsetMemberVoucher->Connection = con;

}

void __fastcall TfrmMemberVoucher::btnTopClick(TObject *Sender)
{


				int id  = SelectMember(m_app, m_con, this);
				  //	ShowMessage(IntToStr(id));

}
//---------------------------------------------------------------------------


void __fastcall TfrmMemberVoucher::RzButton1Click(TObject *Sender)
{
	//
	int id  = SelectMember(m_app, m_con, this);
    ShowMessage(IntToStr(id));
}
//-----------------------------查询----------------------------------------------
 void TfrmMemberVoucher::Query()
{

	if (dsetMemberVoucher->Active)
	{
		dsetMemberVoucher->Active = false;
	}
	String sql;
	if (cbbType->Text=="会员号") {
		   sql="select Tid,Name,MIType,CardSN,date,VoucherAmount,BeforeVoucherAmount,ID,AfterVoucherAmount,CardNumber,Discount,TotalConsumption from CUST_MemberToprecord  LEFT join CUST_MemberInfo on MIid=ID LEFT join CUST_MemberType on MTid=IDType where (datediff(d,date,'"+dtp1->Date+"')<=0 and datediff(d,date,'"+dtp2->Date+"')>=0 ) and id like '%"+RzEditInfor->Text+"%'";
	}
		else if (cbbType->Text=="会员姓名")
		{
			 sql="select Tid,Name,MIType,CardSN,date,VoucherAmount,BeforeVoucherAmount,ID,AfterVoucherAmount,CardNumber,Discount,TotalConsumption from CUST_MemberToprecord  LEFT join CUST_MemberInfo on MIid=ID LEFT join CUST_MemberType on MTid=IDType where  (datediff(d,date,'"+dtp1->Date+"')<=0 and datediff(d,date,'"+dtp2->Date+"')>=0 ) and Name like '%"+RzEditInfor->Text+"%'";
		 }
			else if (cbbType->Text=="会员卡号")
				{
				 sql="select Tid,Name,MIType,CardSN,date,VoucherAmount,BeforeVoucherAmount,ID,AfterVoucherAmount,CardNumber,Discount,TotalConsumption from CUST_MemberToprecord  LEFT join CUST_MemberInfo on MIid=ID LEFT join CUST_MemberType on MTid=IDType where (datediff(d,date,'"+dtp1->Date+"')<=0 and datediff(d,date,'"+dtp2->Date+"')>=0 ) and CardSN like '%"+RzEditInfor->Text+"%'";
				}
				 else
					 {
						sql="select Tid,Name,CardSN,MIType,date,VoucherAmount,BeforeVoucherAmount,ID,AfterVoucherAmount,CardNumber,Discount,TotalConsumption from CUST_MemberToprecord  LEFT join CUST_MemberInfo on MIid=ID LEFT join CUST_MemberType on MTid=IDType where (datediff(d,date,'"+dtp1->Date+"')<=0 and datediff(d,date,'"+dtp2->Date+"')>=0 )" ;
					}
	dsetMemberVoucher->CommandText = sql;
	dsetMemberVoucher->Active = true;
	RzEditInfor->Text="";
}
void __fastcall TfrmMemberVoucher::RzToolButton1Click(TObject *Sender)
{
		cbbType->SetFocus();
	   Query();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberVoucher::RzEditInforKeyPress(TObject *Sender, wchar_t &Key)

{
	        if (Key==VK_RETURN) {
				Query();
		   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberVoucher::RzToolButton5Click(TObject *Sender)
{

    Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberVoucher::FormClose(TObject *Sender, TCloseAction &Action)

{      dsetMemberVoucher->Active=false;
	  Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberVoucher::cbbTypeSelect(TObject *Sender)
{
         RzEditInfor->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemberVoucher::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
      		if (Shift.Contains(ssCtrl)&&Key==81) {  //Q键
				  this->RzToolButton1->Click();
			}
		if (Key==0x1B) {       //esc 键
				  this->RzToolButton5->Click();
			}
}
//---------------------------------------------------------------------------

