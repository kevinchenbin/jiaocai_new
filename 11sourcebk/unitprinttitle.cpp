//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unitprinttitle.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmprinttitle *frmprinttitle;
//---------------------------------------------------------------------------
__fastcall Tfrmprinttitle::Tfrmprinttitle(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
	fcon = con;
	fstgid = stgid;
	AnsiString sql;
	sql = "select * from sys_printtitle where stgid = " + IntToStr(stgid);
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edorprinttitle->Text = aq->FieldByName("orprinttitle")->AsAnsiString ;
	edorcontact->Text = aq->FieldByName("orcontact")->AsAnsiString ;
	edortel->Text = aq->FieldByName("ortel")->AsAnsiString ;
	edoraddress->Text = aq->FieldByName("oraddress")->AsAnsiString ;
	edorprintbk->Text = aq->FieldByName("orprintbk")->AsAnsiString ;

	edcgprinttitle->Text = aq->FieldByName("cgprinttitle")->AsAnsiString ;
	edcgcontact->Text = aq->FieldByName("cgcontact")->AsAnsiString ;
	edcgtel->Text = aq->FieldByName("cgtel")->AsAnsiString ;
	edcgaddress->Text = aq->FieldByName("cgaddress")->AsAnsiString ;
	edcgprintbk->Text = aq->FieldByName("cgprintbk")->AsAnsiString ;

	edrkprinttitle->Text = aq->FieldByName("rkprinttitle")->AsAnsiString ;
	edrkcontact->Text = aq->FieldByName("rkcontact")->AsAnsiString ;
	edrktel->Text = aq->FieldByName("rktel")->AsAnsiString ;
	edrkaddress->Text = aq->FieldByName("rkaddress")->AsAnsiString ;
	edrkprintbk->Text = aq->FieldByName("rkprintbk")->AsAnsiString ;

	edwsprinttitle->Text = aq->FieldByName("wsprinttitle")->AsAnsiString ;
	edwscontact->Text = aq->FieldByName("wscontact")->AsAnsiString ;
	edwstel->Text = aq->FieldByName("wstel")->AsAnsiString ;
	edwsaddress->Text = aq->FieldByName("wsaddress")->AsAnsiString ;
	edpxprintbk->Text = aq->FieldByName("wsprintbk")->AsAnsiString ;

	edshcontact->Text = aq->FieldByName("shcontact")->AsAnsiString ;
	edshtel->Text = aq->FieldByName("shtel")->AsAnsiString ;
	edshaddress->Text = aq->FieldByName("shaddress")->AsAnsiString ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprinttitle::RzButton2Click(TObject *Sender)
{
	if (aq->IsEmpty() ) {
		return;
	}
	aq->Edit();

	aq->FieldByName("cgprinttitle")->AsAnsiString = edcgprinttitle->Text;
	aq->FieldByName("cgcontact")->AsAnsiString = edcgcontact->Text;
	aq->FieldByName("cgtel")->AsAnsiString = edcgtel->Text;
	aq->FieldByName("cgaddress")->AsAnsiString = edcgaddress->Text;

	aq->FieldByName("shcontact")->AsAnsiString = edshcontact->Text;
	aq->FieldByName("shtel")->AsAnsiString = edshtel->Text;
	aq->FieldByName("shaddress")->AsAnsiString = edshaddress->Text;

	aq->FieldByName("cgprintbk")->AsAnsiString = edcgprintbk->Text;

	aq->UpdateBatch(arAll);
	MessageBox(0,"保存成功！","提示",MB_ICONWARNING);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprinttitle::RzButton1Click(TObject *Sender)
{
	if (aq->IsEmpty() ) {
		return;
	}
	aq->Edit();

	aq->FieldByName("orprinttitle")->AsAnsiString = edorprinttitle->Text;
	aq->FieldByName("orcontact")->AsAnsiString = edorcontact->Text;
	aq->FieldByName("ortel")->AsAnsiString = edortel->Text;
	aq->FieldByName("oraddress")->AsAnsiString = edoraddress->Text;
	aq->FieldByName("orprintbk")->AsAnsiString = edorprintbk->Text;

	aq->UpdateBatch(arAll);
	MessageBox(0,"保存成功！","提示",MB_ICONWARNING);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprinttitle::RzButton3Click(TObject *Sender)
{
	if (aq->IsEmpty() ) {
		return;
	}
	aq->Edit();

	aq->FieldByName("rkprinttitle")->AsAnsiString = edrkprinttitle->Text;
	aq->FieldByName("rkcontact")->AsAnsiString = edrkcontact->Text;
	aq->FieldByName("rktel")->AsAnsiString = edrktel->Text;
	aq->FieldByName("rkaddress")->AsAnsiString = edrkaddress->Text;
	aq->FieldByName("rkprintbk")->AsAnsiString = edrkprintbk->Text;

	aq->UpdateBatch(arAll);
	MessageBox(0,"保存成功！","提示",MB_ICONWARNING);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprinttitle::RzButton4Click(TObject *Sender)
{
	if (aq->IsEmpty() ) {
		return;
	}
	aq->Edit();

	aq->FieldByName("wsprinttitle")->AsAnsiString = edwsprinttitle->Text;
	aq->FieldByName("wscontact")->AsAnsiString = edwscontact->Text;
	aq->FieldByName("wstel")->AsAnsiString = edwstel->Text;
	aq->FieldByName("wsaddress")->AsAnsiString = edwsaddress->Text;
	aq->FieldByName("wsprintbk")->AsAnsiString = edpxprintbk->Text;

	aq->UpdateBatch(arAll);
	MessageBox(0,"保存成功！","提示",MB_ICONWARNING);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmprinttitle::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

