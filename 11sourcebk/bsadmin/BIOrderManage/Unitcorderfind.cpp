//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitcorderfind.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmcorderfind *frmcorderfind;
//---------------------------------------------------------------------------
__fastcall Tfrmcorderfind::Tfrmcorderfind(TComponent* Owner,TADOConnection *con,int stgid,int UserID)
	: TForm(Owner)
{
	 fUserID= UserID;
	 fStgID=stgid;
	 fcon=con;
	 aqfind->Connection=fcon;
	 dtpstart->Date=Now();
	 dtpend->Date=Now();
}

//---------------------------------------------------------------------------
void __fastcall Tfrmcorderfind::Button1Click(TObject *Sender)
{
  //find
  AnsiString sql;
  sql ="select * from C_OrderHeader  ";
  wheres=" where 1=1 ";
  if (chstart->Checked) {
	wheres=wheres + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
  }
  if (chend->Checked) {
	wheres=wheres + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
  }
  if (shouhuo->Checked) {
	wheres=wheres + " and OrderAddress like '%"+editaddress->Text+"%'";
  }
  if (chclient->Checked) {
	wheres=wheres + " and OrderUser like '%"+edtclient->Text+"%'";
  }
  if (chcode->Checked) {

	wheres=wheres + " and OrderNtCode like '%"+edcode->Text+"%'";
  }
  if (tel->Checked) {
	wheres=wheres + " and OrderTel like '%"+edittel->Text+"%'";
  }
  if (chinorder->Checked) {

   int index;
   index=cbzt->ItemIndex;
   index++;
   wheres=wheres + " and statea  = "+IntToStr(index);
  }
  if (danhao->Checked) {
   wheres=wheres + " and expressNumber like '%"+Edit3->Text+"%'";
  }

  aqfind->Close();
  aqfind->SQL->Clear();
  aqfind->SQL->Add(sql+wheres);
  aqfind->Open();

}
//---------------------------------------------------------------------------
void __fastcall Tfrmcorderfind::DBGrid1DblClick(TObject *Sender)
{
ModalResult = mrOk ;
}
AnsiString Tfrmcorderfind::GetWhere()
{
   return wheres;

}
AnsiString Tfrmcorderfind::GetSelectDH()
{
 return  aqfind->FieldByName("OrderNtCode")->AsAnsiString;

}
//---------------------------------------------------------------------------
void __fastcall Tfrmcorderfind::Button2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcorderfind::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcorderfind::edtclientChange(TObject *Sender)
{
   if (edtclient->Text!="") {
		 chclient->Checked=true;
   } else chclient->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcorderfind::edcodeChange(TObject *Sender)
{
  if (edcode->Text!="") {
	   chcode->Checked=true;
  }else chcode->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcorderfind::edittelChange(TObject *Sender)
{
  if (edittel->Text!="") {
	tel->Checked=true;
  }else   tel->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcorderfind::editaddressChange(TObject *Sender)
{
  if (editaddress->Text!="") {
	 shouhuo->Checked=true;
  }else  shouhuo->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcorderfind::Edit3Change(TObject *Sender)
{
 if (Edit3->Text!="") {
	danhao->Checked=true;
 }else danhao->Checked=false;
}
//---------------------------------------------------------------------------
