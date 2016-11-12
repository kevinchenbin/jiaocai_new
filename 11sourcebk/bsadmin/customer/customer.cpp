//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include "customer.h"
#include "CustomerForm.h"
#include "MemberForm.h"

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

void __stdcall SetUpSupplier(TApplication* app, TADOConnection* con, int mode)
{
	Application = app;
	if (mode == 1)
	{
		TComponent* com = Application->FindComponent("frmProvider");
		if (com == NULL)
		{
			TfrmCustomer* cust = new TfrmCustomer(Application);
			cust->Name = "frmProvider";
			cust->Caption="供应商设置";
			cust->dsetCustomer->Connection = con;
			cust->SetCustomerType(1);
		}
		else
		{
			TfrmCustomer* cust = dynamic_cast<TfrmCustomer*>(com);
			cust->Show();
		}
	}
	else if (mode == 2)
	{
		TComponent* com1 = Application->FindComponent("frmCustomer");

		if (com1 == NULL)
		{
			TfrmCustomer* cust = new TfrmCustomer(app);
			cust->Name = "frmCustomer";
			cust->Caption="销售商设置";
			cust->dsetCustomer->Connection = con;
			cust->SetCustomerType(2);
		}
		else
		{
			TfrmCustomer* cust = dynamic_cast<TfrmCustomer*>(com1);
			cust->Show();
		}
	}
	else if (mode == 3)
	{
		TfrmMember* mmb = new TfrmMember(app);
		mmb->Caption="会员管理";
		mmb->AQMemberList->Connection = con;
	}
	else
	{

	}
}

int __stdcall SelectCustomer(TApplication* app, TADOConnection* con, int mode)
{
	return 0;
}

