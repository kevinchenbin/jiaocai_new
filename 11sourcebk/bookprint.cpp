//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bookprint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RpBase"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpSystem"
#pragma resource "*.dfm"
Tfrmbookprint *frmbookprint;
//---------------------------------------------------------------------------
__fastcall Tfrmbookprint::Tfrmbookprint(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{    Rpdefine::DataID = IntToStr((int)HInstance);
	con = cn;
	//aqprint->Connection = cn;
}
//---------------------------------------------------------------------------

void Tfrmbookprint::SetPrint(AnsiString Code)
{
  //	aqprint->Active = false;
  //	aqprint->Parameters->ParamByName("Code")->Value = Code;
  //	aqprint->Active = true;

	/*RvProject1->ProjectFile = ExtractFilePath(Application->ExeName) + "diaobo.rav";
	RvProject1->Open();
	RvProject1->Execute();  */
}
//---------------------------------------------------------------------------
void Tfrmbookprint::Print()
{
	/*RvProject1->Execute();
	RvProject1->Close(); */
}
//---------------------------------------------------------------------------

