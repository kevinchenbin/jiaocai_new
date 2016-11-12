//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "stockcheckprint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RpBase"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpSystem"
#pragma resource "*.dfm"
Tfrmstoragecheck *frmstoragecheck;
//---------------------------------------------------------------------------
__fastcall Tfrmstoragecheck::Tfrmstoragecheck(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{    Rpdefine::DataID = IntToStr((int)HInstance);
  aqcheckreport->Connection = cn;
//  ado = cn;
  //if (!ado->Connected ) {
 //  ado->Connected = true;
 // }else if (ado->Connected ) {
 //	ado->Connected = false;
  //	ado->Connected = true;
  //		}


}
void Tfrmstoragecheck::aqactive(String Code)
{
     aqcheckreport->Parameters->ParamByName("code")->Value = Code;
	 aqcheckreport->Active = true;
}
void Tfrmstoragecheck::printpantian(int type)
{
 // aqcheckreport->Parameters->ParamByName("code")->Value = Code;
 // aqcheckreport->Close();
  //aqcheckreport->SQL->Clear();
  //aqcheckreport->SQL->Add(Code);
 // aqcheckreport->Open();

 //  aqcheckreport->Active = true;
 // ShowMessage(aqcheckreport->FieldByName("suppliername")->AsAnsiString) ;


	 //	stockprint->SetParam("danhao","");
	  //	stockprint->SetParam("storage","");
		//stockprint->SetParam("local","");
	  //	stockprint->SetParam("bk","");
	  //	stockprint->SetParam("user","");

   //	aqcheckreport->First();
	 //	ShowMessage(aqcheckreport->FieldByName("suppliername")->AsAnsiString);
	t->ProjectFile ="Project1.rav";// "storagecheck.rav";
	t->Open();
	t->Execute(); //  ShowMessage(RvDataSetConnection1->DataSet->FieldByName("suppliername")->AsAnsiString) ;
	t->Close();

}
//---------------------------------------------------------------------------
void __fastcall Tfrmstoragecheck::RvDataSetConnection1Open(TRvCustomConnection *Connection)

{
aqcheckreport->Active = true;
}
//---------------------------------------------------------------------------

