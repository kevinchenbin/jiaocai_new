//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include "customer.h"
#include "CustomerForm.h"
#include "MemberForm.h"
#include "MemberVoucherForm.h"
#include "SelectMemberForm.h"
#include "SelectCustomerForm.h"

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
	switch(reason)            //手工增加
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
   /*	Application->Handle = app->Handle;
	TForm** p = (TForm**)(&(Application->MainForm));
	*p = app->MainForm;
	if (mode == 1)
	{
			TfrmCustomer* cust = new TfrmCustomer(Application);
			cust->Name = "frmSupplier";
			cust->Caption="供应商设置" ;
			cust->dsetCustomer->Connection = con;
			cust->dsetCustomer->Active=false;
			cust->cmddel->Connection=con;
			cust->SetCustomerType(1);

	}
	else if (mode == 2)
	{
			TfrmCustomer* cust = new TfrmCustomer(app);
			cust->Name = "frmVendor";
			cust->Caption="销售商设置" ;
			cust->dsetCustomer->Active=false;
			cust->dsetCustomer->Connection = con;
			cust->cmddel->Connection=con;
			cust->SetCustomerType(2);
	}

	 else if (mode == 3)
	{
		TfrmMember* mmb = new TfrmMember(app);
		mmb->Init(Application, con);
	}
	else
	{

	}   */
}

void __stdcall MemberPayment(TApplication* app, TADOConnection* con)
{
   /*	Application->Handle = app->Handle;
	TForm** p = (TForm**)(&(Application->MainForm));
	*p = app->MainForm;
	TfrmMemberVoucher* frm = new TfrmMemberVoucher(Application);
	frm->Init(Application, con); */
}

int __stdcall SelectCustomer(TApplication* app, TADOConnection* con, int mode)
{
	return 0;
}

  int __stdcall SelectMember(TApplication* app, TADOConnection* con, TComponent* Owner)
{

return 0;
}

int __stdcall NewMember(TApplication* app, TADOConnection* con)
{


//TfrmSelectMember* frm = new TfrmSelectMember(Application);
	//frm->Init(app, con);
	//frm->ShowModal();
	//return 0;
}

int __stdcall NewCustomer(TApplication* app, TADOConnection* con)
{
	/*	Application->Handle = app->Handle;
	TForm** p = (TForm**)(&(Application->MainForm));
	*p = app->MainForm;
	if (mode == 1)
	{
		TfrmSelectCustomer* cust = new TfrmSelectCustomer(Application);
		cust->Name = "frmSupplier";
		cust->Caption="供应商设置" ;
		cust->dsetCustomer->Connection = con;
		cust->dsetCustomer->Active=false;
		cust->cmddel->Connection=con;
		cust->SetCustomerType(1);
		cust->ShowModal();
		delete cust;
	}
	else if (mode == 2)
	{
    	TfrmSelectCustomer* cust = new TfrmSelectCustomer(Application);
		cust->Name = "frmVendor";
		cust->Caption="销售商设置" ;
		cust->dsetCustomer->Connection = con;
		cust->dsetCustomer->Active=false;
		cust->cmddel->Connection=con;
		cust->SetCustomerType(2);
		cust->ShowModal();
		delete cust;
	}
	return 0;    */


		Application->Handle = app->Handle;
	TForm** p = (TForm**)(&(Application->MainForm));
	*p = app->MainForm;
   TfrmCustomer	*frm = new TfrmCustomer(Application);
   frm->aqsupplier->Connection = con;
   frm->aqinit->Connection = con;
  frm->ShowData();
   frm->Init(app,con);

   //	frm->ShowModal();
   //	delete frmCustomer;
}


