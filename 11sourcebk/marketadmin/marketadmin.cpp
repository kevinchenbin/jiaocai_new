//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>

#include "marketadmin.h"

#include "DiscountPlan.h"
#include "WsaleDiscount.h"
#include "MemberTypeDiscount.h"
#include "WsaleDiscountPlan.h"
#include "Membertypeadddot.h"

#pragma hdrstop
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

#pragma argsused

TApplication* DllApplication = NULL;

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	switch(reason)                                                 //手工增加
	{
		case DLL_PROCESS_ATTACH:
			CoInitialize(NULL);
			DllApplication = Application;
			break;
		case DLL_PROCESS_DETACH:
			CoUninitialize();
			Application = DllApplication;
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}

	return 1;
}
//---------------------------------------------------------------------------


void __stdcall ControlDiscount(TApplication* app, TADOConnection* con)
{
	/*Application = app;
	TfrmDiscountCtrl* frm = new TfrmDiscountCtrl(Application);
	frm->Init(Application, con); */
}

void __stdcall ManageRetailSales(TApplication* app, TADOConnection* con)
{
	
}
void __stdcall DiscountSales(TApplication* app, TADOConnection* con,int stgid)
{
	Application = app;
	TFormDiscount* frm = new TFormDiscount(Application);
	frm->Init(Application, con,stgid);
}

void __stdcall WsaleDiscount(TApplication* app, TADOConnection* con,int stgid)
{
	Application = app;
	TFormWsaleDiscount* frm = new TFormWsaleDiscount(Application,stgid);
	frm->Init(Application, con);
}


void __stdcall MemberDiscount(TApplication* app, TADOConnection* con,int stgid)
{
	Application = app;
	TfrmMemberDiscount* frm = new TfrmMemberDiscount(Application,con,stgid);

}

void __stdcall WsaleDiscountSales(TApplication* app, TADOConnection* con,int stgid)
{
	Application = app;
	TfrmWsaleDiscount* frm = new TfrmWsaleDiscount(Application);
	frm->Init(Application, con,stgid);
}

void __stdcall Memtypeadd(TApplication* app, TADOConnection* con,int stgid)
{
	Application = app;
	Tfrmmemberadddot* frm = new Tfrmmemberadddot(Application,con,stgid);
}
