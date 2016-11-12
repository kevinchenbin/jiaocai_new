//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "sysadmin.h"
#include "StorageInfoForm.h"
#include "RetailNoteForm.h"
 #include "Print.h"
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


void __stdcall SetUpStorageInfo(TApplication* app, TADOConnection* con,int userid,int storageid,bool master)
{
	Application = app;
	TfrmStorageInfo* frm = new TfrmStorageInfo(app);
	frm->userid = userid;
	frm->storageid = storageid;
	frm->master = master;
	frm->Init(con);
}

void __stdcall ManagePrint(TApplication* app, TADOConnection* con, int mode,int stgid)
{
	Application = app;
	if (mode == 1)//入库单格式
	{
		
	}
	else if (mode == 2)//批销单格式
	{

	}
	else if (mode == 3)//零售小票格式
	{
		TfrmRetailNote* frm = new TfrmRetailNote(app);
		frm->stgid = stgid;
		frm->Init(app, con);
	}
	else
	{
    }
}

void __stdcall SetBusiness(TApplication* app, TADOConnection* con)
{


}

