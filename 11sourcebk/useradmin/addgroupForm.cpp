//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "addgroupForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma resource "*.dfm"
Tfrmaddgroup *frmaddgroup;
//---------------------------------------------------------------------------
__fastcall Tfrmaddgroup::Tfrmaddgroup(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmaddgroup::FormClose(TObject *Sender, TCloseAction &Action)
{
	   Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmaddgroup::btn2Click(TObject *Sender)
{
	      Close();
}
//---------------------------------------------------------------------------
void Tfrmaddgroup::Init(LandInfo* li)
{
   TfrmMDIChild::Init(li);
}
