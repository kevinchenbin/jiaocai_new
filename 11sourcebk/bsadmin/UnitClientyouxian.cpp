//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitClientyouxian.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
Tfrmclientyouxian *frmclientyouxian;
//---------------------------------------------------------------------------
__fastcall Tfrmclientyouxian::Tfrmclientyouxian(TComponent* Owner)
	: TForm(Owner)
{
}
void Tfrmclientyouxian::init(TADOConnection *cn)
{
  fcn = cn;
  AnsiString sql;
  sql = "select name,'Èý¼¶' as jibie from Cust_customerinfo where type in (2,3)";
  aq->Connection = fcn;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->Open();

}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientyouxian::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

