//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitCbprice.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
TfrmCbprice *frmCbprice;
//---------------------------------------------------------------------------
__fastcall TfrmCbprice::TfrmCbprice(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
	aq->Connection = con;
	fstgid = stgid;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCbprice::RzButton1Click(TObject *Sender)
{
	AnsiString sql;
	if (rg->ItemIndex == 0) {
		sql =  "exec CBprice_Calculation " + IntToStr(fstgid) + ",0";
	}
	else if (rg->ItemIndex == 1) {
		sql =  "exec CBprice_Calculation " + IntToStr(fstgid) + ",1";
	}
	else
	{
    	return;
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	MessageBox(0,"成本已重新计算！","提示" ,MB_OK|MB_ICONASTERISK);
	Close();
}
//---------------------------------------------------------------------------
