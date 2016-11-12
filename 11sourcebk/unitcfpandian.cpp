//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unitcfpandian.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmcfpandian *frmcfpandian;
//---------------------------------------------------------------------------
__fastcall Tfrmcfpandian::Tfrmcfpandian(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
	con = cn;
	bendan = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcfpandian::RzButton1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcfpandian::edamountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r' && edamount->Text != "") {
		RzButton2->Click();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcfpandian::RzButton2Click(TObject *Sender)
{
	if (edamount->Text == "") {
		return;
	}
	if (bendan == 0) {
    	TADOQuery *aq = new TADOQuery(this);
		aq->Connection = con;
    	AnsiString sql;
		sql = "update STK_StockInventories set shouldamount = shouldamount + " + edamount->Text + ",balance = balance + " + edamount->Text + ",states = 0,Fixedprice = shouldamount*Price,Discountprice = price*shouldamount*discount/100 where stk_bookinfoid = " + IntToStr(stkbkid) + " and notecode in(select codestr from BS_PandianCount where state = 0)";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
	}
	addamount = StrToInt(edamount->Text);
    ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
