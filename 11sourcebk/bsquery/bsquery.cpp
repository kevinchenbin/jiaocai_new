//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "bsquery.h"
//#include "CheckQuery.h"
#include "StockInQuery.h"
#include "QryCOderNoteForm.h"
#include "Qryjichun.h"
#include "QryStorageNoteForm.h"
#include "QryRetailNoteForm.h"
#include "QryWsaleNoteForm.h"
#include "QryStockNoteForm.h"
#include "QryOderNoteForm.h"
#include "QryProcureNoteForm.h"
#include "QryPeisongNoteForm.h"
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
	switch(reason)                                                 //�ֹ�����
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

void __stdcall BusinessQuery(TApplication* app, LandInfo* li, int mode)
{
	//
	Application = app;
	//ShowMessage(IntToStr(mode));
	if(mode==1)
	{
//		TfrmCheckQuery* frm = new TfrmCheckQuery(Application);
//		frm->Init(Application,con);
	//TfrmCustomerOrder* frm = new TfrmCustomerOrder(Application);
	//frm->Init(Application, con);
	}
	else if(mode == 2)
	{
	//	TfrmCheckQuery* frm = new TfrmCheckQuery(Application);
	//	frm->Init(Application,li->con);
//		TfrmPurchaseQuery* frm = new TfrmPurchaseQuery(Application);
//		frm->Init(Application, con);
	}
	else if(mode == 3)
	{
		TfrmStockInQuery* frm = new TfrmStockInQuery(Application);
		frm->Init(li);
	}
	else if(mode == 4)
	{
		//TfrmBookQueryBySupplier* frm = new TfrmBookQueryBySupplier(Application);
		//frm->Init(Application,li->con);
		//TfrmWholeSalesQuery* frm = new TfrmWholeSalesQuery(Application);
		//frm->Init(Application,con);
	}
	else if(mode == 5)
	{
	   //	TfrmQuery* frm = new TfrmQuery(Application);
	   //	frm->Init(Application,li->con);
	}
}

void __stdcall QueryStorageNote(LandInfo* li)
{
	Application = li->app;
	TfrmQryStorageNote* frm = new TfrmQryStorageNote(Application);
	frm->Init(li);

}

void __stdcall QueryRetailNote(LandInfo* li)
{
	Application = li->app;
	TfrmQryRetailNote* frm = new TfrmQryRetailNote(Application);
	frm->Init(li);
}

void __stdcall QueryWsaleNote(LandInfo* li)
{
	Application = li->app;
	TfrmQryWsaleNote* frm = new TfrmQryWsaleNote(Application);
	frm->Init(li);
}
void __stdcall Saleduibi(LandInfo* li)
{
	 /*Application = li->app ;
	 Tfrmsaleduibi * frm = new Tfrmsaleduibi(Application);
	 frm->init(li);
	 frm->Show();   */
}

void __stdcall QryCheckNote(LandInfo* li)
{
	Application = li->app;
	TfrmQryCheckNote* frm = new TfrmQryCheckNote(Application);
	frm->Init(li);

}

void __stdcall QryOderNote(LandInfo* li)
{
	Application = li->app;
	TfrmQryOderNote* frm = new TfrmQryOderNote(Application);
	frm->Init(li);

}
void __stdcall QryCOderNote(LandInfo* li)
{
	Application = li->app;
	TfrmCQryOderNote* frm = new TfrmCQryOderNote(Application);
	frm->Init(li);

}

void __stdcall QryProcureNote(LandInfo* li)
{
	Application = li->app;
	TfrmQryProcureNote* frm = new TfrmQryProcureNote(Application);
	frm->Init(li);
}

void __stdcall QryPeisongNote(LandInfo* li)
{
	Application = li->app;
	TfrmQryPeisongNote* frm = new TfrmQryPeisongNote(Application);
	frm->Init(li);
}
void __stdcall QryJiechun(LandInfo* li)
{

   	Application = li->app;
	Tfrmjichun* frm = new Tfrmjichun(Application);
        frm->Init(li);

}
