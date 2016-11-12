//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitclientbijiao.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "DBChart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmbijiao *frmbijiao;
//---------------------------------------------------------------------------
__fastcall Tfrmbijiao::Tfrmbijiao(TComponent* Owner)
	: TForm(Owner)
{
	DateTimePicker1->Date = Date();
	 DateTimePicker2->Date = Date();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbijiao::BtnClick(TObject *Sender)
{   		AnsiString title;
	 AnsiString sql;

	 if (type == 1) {  //客户

	  sql = "select C.name as text ,sum(discountedprice) as bar from BS_WsaleNoteHeader B "
			" join  Cust_customerinfo C on B.vendorid = C.ID "
			" where C.type in (2,3) and Hdtime between '" + DateToStr(DateTimePicker1->Date)+"' and '" + DateToStr(DateTimePicker2->Date) + "' group by C.name";
			Chart1->Series[0]->Clear();
		title = DateToStr(DateTimePicker1->Date) + "---" + DateToStr(DateTimePicker2->Date) + " 客户销售实洋比较";

	 } else  //供应商
	 {
	   sql = "select top 15 C.name as text ,sum(totalDiscountedprice) as bar from BS_StorageNoteHeader B "
			 " join  Cust_customerinfo C on B.supplierid = C.ID where C.type =1  and Hdtime between '" + DateToStr(DateTimePicker1->Date)+"' and '" + DateToStr(DateTimePicker2->Date) + "'  group by C.name ";
		Chart1->Series[0]->Clear();

		title = DateToStr(DateTimePicker1->Date) + "---" + DateToStr(DateTimePicker2->Date) + " 供应商进货实洋比较";

	 }
	  Chart1->Title->Text->Clear();
	 Chart1->Title->Text->Add(title);
	aq->Connection = fcn;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	for (int i = 1; i < aq->RecordCount ; i++) {

	   Chart1->Series[0]->AddXY(i,aq->FieldByName("bar")->AsFloat,aq->FieldByName("text")->AsAnsiString ,clRed);

	   aq->Next();
	}


}
void Tfrmbijiao::init(TADOConnection *cn)
{

 fcn = cn;
 if (type == 1) {
	 this->Caption = "销售同期比较";
 }
 else
 {
	this->Caption = "供货同期比较";
 }

}
//---------------------------------------------------------------------------
void __fastcall Tfrmbijiao::BtnAlignBottomClick(TObject *Sender)
{
 WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbijiao::BtnExitClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbijiao::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

