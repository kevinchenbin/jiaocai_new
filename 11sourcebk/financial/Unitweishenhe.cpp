//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitweishenhe.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmweishenhe *frmweishenhe;
//---------------------------------------------------------------------------
__fastcall Tfrmweishenhe::Tfrmweishenhe(TComponent* Owner,TADOConnection *cn,int type)
	: TForm(Owner)
{
  Type = type;
  aqdg->Connection = cn;
  AnsiString sql;
   sql = "select value from sys_bsset where name = 'changeDanHaoDisplay'";
   TADOQuery *aq1 = new TADOQuery(NULL);
   aq1->Connection = cn;
   aq1->SQL->Clear();
   aq1->SQL->Add(sql);
   aq1->Open();
   ChangeDisplay = aq1->FieldByName("value")->AsBoolean;
   delete aq1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmweishenhe::BtnExitClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmweishenhe::FormCreate(TObject *Sender)
{
  String sql;
  if (Type == 1) {
   sql = "select ID,Moneycode as '单号',custmername as '供应商',payment as '付款',clearingtype as '结算类型',"
		" clearingstyle as '结算方式',Convert(varchar(20),date,111) as '日期' from FN_CUSEndMoneyDocuments"
		" where state =0 and type =" + IntToStr(Type);
  } else
  {

	   sql = "select ID,Moneycode as '单号',custmername as '供应商',payment as '付款',clearingtype as '结算类型',"
		" clearingstyle as '结算方式',Convert(varchar(20),date,111) as '日期' from FN_CUSEndMoneyDocuments"
		" where state =0 and type =" + IntToStr(Type);
  }
  aqdg->Close();
  aqdg->SQL->Clear();
  aqdg->SQL->Add(sql);
  aqdg->Open();
  Createdg(aqdg,dg);
}
void Tfrmweishenhe::Createdg(TADOQuery *aq,TRzDBGrid *dg)
{
  TColumn *column;
   for (int i = 0; i < aq->Fields->Count ; i++) {
	column = dg->Columns ->Add();
	column->FieldName  = aq->Fields->Fields[i]->FieldName  ;
	column->Width = 90;
	aq->Next();
   }
   dg->Columns->Items[0]->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmweishenhe::dgDblClick(TObject *Sender)
{
	  Danhao = aqdg->FieldByName("单号")->AsAnsiString ;
      Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmweishenhe::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmweishenhe::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

