//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fastcheckprint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RpCon"
#pragma link "RpConBDE"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpBase"
#pragma link "RpSystem"
#pragma resource "*.dfm"
Tfrmfastcheckprint *frmfastcheckprint;
//---------------------------------------------------------------------------
__fastcall Tfrmfastcheckprint::Tfrmfastcheckprint(TComponent* Owner,TADOConnection *cn,TADOQuery *aq)
	: TForm(Owner)
{
	aqdetail = aq;
}
//---------------------------------------------------------------------------
void Tfrmfastcheckprint::PrintExe()
{
   fastcheck->ProjectFile = "fastcheck.rav";
	Rvfastcheck->DataSet = aqdetail;
   aqdetail->First();
   fastcheck->Open();
   fastcheck->SetParam("title",title) ;
   fastcheck->SetParam("user",username);

   fastcheck->Execute();
   fastcheck->Close();
}
//---------------------------------------------------------------------------





