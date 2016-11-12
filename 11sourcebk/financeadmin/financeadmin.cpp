//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "financeadmin.h"
#include "SupplyInitForm.h"
#include "CUSInitForm.h"
#include "PayGatherForm.h"
#include "CUSPayGatherForm.h"
#include "PayMentClearForm.h"
#include "CUSPayMentClearForm.h"
#include "PaydetailForm.h"
#include "CUSPayDetailForm.h"
#include "PayDocQueryForm.h"
#include "CUSDocQueryForm.h"

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

void __stdcall CheckCustomerFinance(TApplication* app, TADOConnection* con, int bsmode)
{
	Application = app;
	if(bsmode==1)
	  {	TfrmCUSInit* CUSInit= new TfrmCUSInit(Application);
		CUSInit->Init(app, con);
	 }
	 else if (bsmode==2)
		 {
			   TfrmCUSPayMentClear* CUSPayMentClear= new TfrmCUSPayMentClear(Application);
			CUSPayMentClear->Init(app, con);
		  }
		 else if (bsmode==3)
		 {
			   TfrmCUSPayGather* CUSPayGather= new TfrmCUSPayGather(Application);
			CUSPayGather->Init(app, con);
		  }
			 else if (bsmode==4)
		 {
				TfrmCUSPayDetail* CUSPayDetail= new TfrmCUSPayDetail(Application);
				CUSPayDetail->Init(app, con);
		  }
			 else if (bsmode==5)
		 {
				TfrmCUSDocQuery* CUSDocQuery= new TfrmCUSDocQuery(Application);
				CUSDocQuery->Init(app, con);
		  }


}

void __stdcall CheckSupplierFinance(TApplication* app, TADOConnection* con, int bsmode)
{
    	Application = app;
	if(bsmode==1)
	  {	TfrmSupplyInit* SupplyInit= new TfrmSupplyInit(Application);
		SupplyInit->Init(app, con);
	 }
	 else if (bsmode==2)
		 {
			   TfrmPayMentCle* PaymentClear= new TfrmPayMentCle(Application);
			PaymentClear->Init(app, con);
		  }
		 else if (bsmode==3)
		 {
			   TfrmPayGather* PayGather= new TfrmPayGather(Application);
			PayGather->Init(app, con);
		  }
			 else if (bsmode==4)
		 {
		 		TfrmPaydetail* Paydetail= new TfrmPaydetail(Application);
				Paydetail->Init(app, con);
		  }
			 else if (bsmode==5)
		 {
				TfrmPayDocQuery* PayDocQuery= new TfrmPayDocQuery(Application);
				PayDocQuery->Init(app, con);
		  }

}
