//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>

#include "bsadmin.h"
#include "StorageMngForm.h"
#include "WholesaleMngForm.h"
#include "RetailMngForm.h"
#include "ProcureMng.h"
#include "StorageReturnMngForm.h"
#include "WholesaleMngReturnForm.h"
#include "RetailReturnMngForm.h"
#include <tchar.h>
#include "CheckQuery.h"
#include "Supplier.h"
#include "\BIOrderManage\UnitBIOrder.h"
#include "suppliermodify.h"
#include "Stockcheckxuyi.h"
#include "fastcheck.h"
#include "ZNProcureMng.h"
//#include "procurequery.h"
#include "ZNStorageMngForm.h"
#include "ZNruku.h"
#include "ZNfahuo.h"
#include "Ysbooksale.h"
#include "Ordermodify.h"
#include "Unitchaigoufromorder.h"
#include "Unitdistribute.h"
#include "Unitask.h"
#include "Unitsiglefenfa.h"
#include "StockAdjust.h"
#include "UnitDiaobo.h"
#include "ImportBIOrder.h"
#include "OrderLock.h"

#include "COrderLock.h"
#include "\BIOrderManage\UnitCOrder.h"
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
   Rpdefine::DataID = IntToStr((int)HInstance);
	switch(reason)                                                 //�ֹ�����
	{
		case DLL_PROCESS_ATTACH:
			CoInitialize(NULL);
			SetLocaleInfo(GetThreadLocale(), LOCALE_IDATE, _TEXT("2"));
            SetLocaleInfo(GetThreadLocale(), LOCALE_ITIME, _TEXT("1"));
			SetLocaleInfo(GetThreadLocale(), LOCALE_SDATE, _TEXT("yyyy-mm-dd"));
            SetLocaleInfo(GetThreadLocale(), LOCALE_STIME, _TEXT("HH-mm-ss"));
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
void __stdcall ManageMarketing(LandInfo* li)
{
	Application = li->app;
	TfrmWholesaleMng* frm = new TfrmWholesaleMng(Application,1);
	frm->Init(li);
}

void __stdcall ManageRetail(LandInfo* li)
{
	Application = li->app;
	TfrmRetailMng* frm = new TfrmRetailMng(Application);
	frm->Init(li);
}

void __stdcall ManageOrder(LandInfo* li)
{
//	Application = li->app;
//	TfrmOrderMng* frm = new TfrmOrderMng(Application);
//	frm->Init(li);
}

void __stdcall ManageProcurement(LandInfo* li)
{
//	Application = li->app;
//	TfrmProcureMng* frm = new TfrmProcureMng(Application);
//	frm->Init(li);
}

void __stdcall ManageStorage(LandInfo* li)
{
	Application = li->app;
	TfrmStorageMng* frm = new TfrmStorageMng(Application);
	frm->Init(li);
}

void __stdcall CheckQuery(LandInfo* li)
{
	Application = li->app;
	TfrmCheckQuery* frm = new TfrmCheckQuery(Application);
	frm->stgid = li->storageID ;
	frm->Init(li->app, li->con);
}
void __stdcall SupplierManage(LandInfo* li)
{
	
}
void __stdcall OrderManage(LandInfo *li)
{
  /*Application = li->app ;
  TfrmOrderMng *frm = new TfrmOrderMng(Application);
  frm->Init(li); */
}
void __stdcall ProcureManage(LandInfo *li)
{
	Application = li->app ;
	TfrmProcureMng *frm = new TfrmProcureMng(Application);
	frm->Init(li);
}

void __stdcall ManageReturnStorage(LandInfo* li)
{
	Application = li->app;
	TfrmStorageReturnMng* frm = new TfrmStorageReturnMng(Application);
	frm->Init(li);
}

void __stdcall ManageReturnMarketing(LandInfo* li)
{
	Application = li->app;
	TfrmWholesaleReturnMng* frm = new TfrmWholesaleReturnMng(Application);
	frm->Init(li);
}

void __stdcall ManageReturnRetail(LandInfo* li)
{
	Application = li->app;
	TfrmRetailReturnMng* frm = new TfrmRetailReturnMng(Application);
	frm->Init(li);
}
void __stdcall StockAdjust(LandInfo *li)
{

  Application = li->app ;
  TfrmStockAdjust * frm = new TfrmStockAdjust(Application);
  frm->init(li);
  frm->Show();

}
 void __stdcall BIOrderManage(LandInfo *li,int type)
 {
   Application  = li->app ;
   TfrmBIorder * frm = new TfrmBIorder(Application);
   frm->type = type;
   frm->init(li);
   frm->Show();
 }
  void __stdcall ImpBIOrderManage(LandInfo *li,int type)
 {
   Application  = li->app ;
   TfrmimptBIorder * frm = new TfrmimptBIorder(Application);
   frm->type = type;
   frm->init(li);
   frm->Show();
 }
void __stdcall COrder(LandInfo *li)
{
 Application  = li->app ;
  TfrmCNetOrder *frm = new TfrmCNetOrder(Application);
  frm->init(li);
  frm->Show();

}
  void __stdcall SupplierModify(LandInfo *li)
 {
   Application  = li->app ;
   Tfrmsuppliermodify * frm = new Tfrmsuppliermodify(Application,li->con);
   frm->Show();
 }

 void __stdcall Stockxuyi(LandInfo *li)
{
	 Application = li->app ;
	 TfrmStockcheckxuyi *frm = new TfrmStockcheckxuyi(Application);
	 frm->init(li);
	 frm->Show();
}

 void __stdcall fastcheck(LandInfo *li)
{
	 Application = li->app ;
	 Tfrmfastcheck *frm = new Tfrmfastcheck(Application,li->con,li->storageID);
	 frm->username = li->UserName ;
	 frm->Show();
}

void __stdcall ZNProcureManage(LandInfo *li)
{
	Application = li->app ;
	TfrmZNProcureMng *frm = new TfrmZNProcureMng(Application);
	frm->Init(li);
}

void __stdcall BIOrderManageDanHao(LandInfo *li,AnsiString Danhao)
  {
  	Application  = li->app ;
   TfrmBIorder * frm = new TfrmBIorder(Application);
   frm->init(li,Danhao);
   frm->Show();
  }

void __stdcall ZNStorage(LandInfo *li)
{
	Application = li->app ;
	TfrmZNruku *frm = new TfrmZNruku(Application);
	frm->Init(li);
}

void __stdcall ZNWsale(LandInfo *li)
{
	Application = li->app ;
	TfrmZNfahuo *frm = new TfrmZNfahuo(Application);
	frm->Init(li);
}

 void __stdcall Ysbooksale(LandInfo *li)
 {
   Application  = li->app ;
   TfrmYsbooksale * frm = new TfrmYsbooksale(Application);
   frm->init(li);
   frm->Show();
 }
void __stdcall OrdereShenhei(LandInfo *li)
 {
   Application  = li->app ;
   Tfrmordermodify * frm = new Tfrmordermodify(Application,li->con,li->storageID);
   frm->Show();
 }
 void __stdcall CaigoufromOrder(LandInfo *li)
 {
   Application  = li->app ;
   Tfrmchaigoufromorder * frm = new Tfrmchaigoufromorder(Application);
   frm->Init(li);
   frm->Show();
 }

  void __stdcall daohuofenfa(LandInfo *li)
 {
   Application  = li->app ;
   Tfrmdaohuofenfa * frm = new Tfrmdaohuofenfa(Application);
   frm->Init(li);
   frm->Show();
 }

   void __stdcall orderask(LandInfo *li)
 {
   Application  = li->app ;
   Tfrmorderask * frm = new Tfrmorderask(Application,li->con,li->storageID,li->userID);
   frm->Show();
 }

   void __stdcall siglefenfa(LandInfo *li)
 {
   Application  = li->app ;
   Tfrmsiglefenfa * frm = new Tfrmsiglefenfa(Application,li->con,li->storageID);
   frm->Show();
 }

 void __stdcall DiaoBo(LandInfo *li,int modle,AnsiString Danhao)
 {
	Application  = li->app ;
	Tfrmdiaobo *frm = new Tfrmdiaobo(Application,li->con,li->storageID,li->userID,modle);
	frm->username = li->UserName  ;
	frm->Show();
	if (modle == 2) {
		frm->QryNtHeader(Danhao);
	}
 }
 	void __stdcall OrderLock(LandInfo *li)
	{
		Application  = li->app ;
		Tfrmorderlock * frm = new Tfrmorderlock(Application);
		frm->init(li);
		frm->Show();
	}
void __stdcall COrderLock(LandInfo *li)
{
		Application  = li->app ;
		TfrmCnetorderlock * frm = new TfrmCnetorderlock(Application);
		frm->init(li);
		frm->Show();
}


