//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CUSPayDetailForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmCUSPayDetail *frmCUSPayDetail;
//---------------------------------------------------------------------------
__fastcall TfrmCUSPayDetail::TfrmCUSPayDetail(TComponent* Owner)
	: TfrmMDIChild(Owner)
{       m_module = MTFinance;
	dtp1->Date=dtp1->Date .CurrentDate();
	dtp2->Date=dtp2->Date .CurrentDate();
}

//---------------------------------------------------------------------------
void TfrmCUSPayDetail::Init(TApplication* app, TADOConnection* con)
{             TfrmMDIChild::Init(app, con);
		   this->Caption="应收明细";
			 qrySupply->Connection=con;
			 dsDoc->Connection=con;
			 dsbalance->Connection=con;
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



//---------------------------------------------------------------------------


void __fastcall TfrmCUSPayDetail::FormClose(TObject *Sender, TCloseAction &Action)

{
   Action = caFree;

}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayDetail::RzToolButton1Click(TObject *Sender)
{            Close();

}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayDetail::RzToolButton3Click(TObject *Sender)
{
			 if (cbbType->Text!="全部客户")
	 {
		   if (dsDoc->Active) {
			   dsDoc->Active=false;
		   }

		 String sql="select * from BS_WsaleNoteHeader where VendorID=(select id from CUST_CustomerInfo where Name='"+cbbType->Text+"')  and datediff(d,HdTime,'"+dtp1->Date+"')<=0 and datediff(d,HdTime,'"+dtp2->Date+"')>=0";

		   if (cbb2->Text=="已结") {
					   sql=sql+" and State=1" ;
		   }
		   else if (cbb2->Text=="未结") {
			   sql=sql+" and State=0";
		   }
		   else if (cbb2->Text=="审核中") {
				  sql=sql+" and State=2" ;
		   }


		   dsDoc->CommandText=sql;
		   dsDoc->Active=true;

		  dsDoc->First();
		  int  DiscountedPrice=0;
		   int  checked=0;
		   int AddCosts=0;

		  while (!dsDoc->Eof)
		  {     DiscountedPrice+=dsDoc->FieldByName("DiscountedPrice")->AsInteger;
				 AddCosts+=dsDoc->FieldByName("AddCosts")->AsInteger;
				 checked+=dsDoc->FieldByName("Checked")->AsInteger;
				dsDoc->Next();
		  }
		 if (dsbalance->Active) {
			 dsbalance->Active=false;
		 }
		  dsbalance->CommandText="select Balance from CUST_CustomerInfo where Name='"+cbbType->Text+"'";
		   dsbalance->Active=true;
		 String  balance=dsbalance->FieldByName("Balance")->AsString;
		edt1->Text=IntToStr(DiscountedPrice);
		edt2->Text=IntToStr(checked);
		edt4->Text=IntToStr(AddCosts);
		edt5->Text=balance;
		int s=DiscountedPrice+AddCosts-checked;
		edt3->Text=IntToStr(s);

	 }
	 else {
	   ShowMessage("请先选择客户");
	 }

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayDetail::rzdbgrd2DblClick(TObject *Sender)
{
			 if (cbbType->Text!="全部客户")
	{

				if (dsdetail->Active)
			 {
				dsdetail->Active=false;
			 }
			 if (!dsDoc->IsEmpty()) {


			 String sql="select HdTime,ISBN,Name,Price,PressCount,BS_WsaleNote.Amount as Amount,Discount ,FixedPrice,DiscountedPrice  from BS_WsaleNote  left join STK_BookInfo on STK_BookInfo.id=BkInfoID left join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_WsaleNoteHeader on BS_WsaleNoteHeader.id=WsaleNtHeaderID where WsaleNtCode="+dsDoc->FieldByName("WsaleNtCode")->AsString;
			 dsdetail->CommandText=sql;
			 dsdetail->Active;

			}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCUSPayDetail::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
			if (Shift.Contains(ssCtrl)&&Key==81) {  //Q键
				  this->RzToolButton3->Click();
			}
			if (Key==0x1B) {       //esc 键
				  this->RzToolButton1->Click();
			}
}
//---------------------------------------------------------------------------

