//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>

#include "catalogadmin.h"
#include "CatalogAdminForm.h"
#include "PressAdminForm.h"
#include "BookTypeAdminForm.h"
#include "ExcelImport.h"
#include "Catalogkanli.h"
#include "catalogbuilt.h"
#include "catalognewandrec.h"
#include "Qikanguanli.h"
#include "mutibooktongyi.h"
#include "BigBookType.h"
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



void __stdcall ManagePress(TApplication* app, TADOConnection* con)
{
	Application = app;
	TfrmPressAdmin* frm = new TfrmPressAdmin(Application);
	frm->Init(Application, con);
}

void __stdcall ManageBookType(TApplication* app, TADOConnection* con)
{
	Application = app;
	TfrmBookTypeAdmin* frm = new TfrmBookTypeAdmin(Application);
	frm->Init(Application,con);
	frm->ShowModal();
}

void __stdcall BigBookType(TApplication* app, TADOConnection* con)
{
	Application = app;
	TfrmBigBookType* frm = new TfrmBigBookType(Application);
	frm->Init(Application,con);
	frm->ShowModal();
}

void __stdcall CatalogKan(TApplication* app, TADOConnection* con,int stgid,int userid,bool add,bool del,bool mod)
{
	Application = app;
	TfrmCatalogkanli* frm = new TfrmCatalogkanli(Application,con,stgid,userid);
        frm->mod=mod;
        frm->add=add;
        frm->del=del;

    frm->Show();
}

void __stdcall Catalogbuilt(TApplication* app, TADOConnection* con)
{
	Application = app;
	Tfrmcatalogbuit* frm = new Tfrmcatalogbuit(Application,con);
    frm->Show();
}
void __stdcall Catalogneworrec(TApplication* app, TADOConnection* con)
{
	Application = app;
	Tfrmcatalogneworrec* frm = new Tfrmcatalogneworrec(Application,con);
    frm->Show();
}

void __stdcall QiKanguanli(TApplication* app, TADOConnection* con)
{
	Application = app;
	TfrmQikanguanli* frm = new TfrmQikanguanli(Application,con);
	frm->Show();
}

void __stdcall Multibook(TApplication* app, TADOConnection* con,int stgid,int userid)
{
	Tfrmmutibook *frm = new Tfrmmutibook(Application,con);
	frm->stgid = stgid;
	frm->userid = userid;
	frm->ShowModal();
}





