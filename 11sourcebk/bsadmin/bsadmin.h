#ifndef bsadminH
#define bsadminH

#include <ADODB.hpp>
#include "pdtypes.h"
#include "RpDefine.hpp"
extern "C" __declspec(dllexport) void __stdcall ManageMarketing(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall ManageRetail(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall ManageOrder(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall ManageProcurement(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall ManageStorage(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall CheckQuery(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall SupplierManage(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall OrderManage(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall ProcureManage(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall ManageReturnStorage(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall ManageReturnMarketing(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall ManageReturnRetail(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall StockAdjust(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall BIOrderManage(LandInfo *li,int type);
extern "C" __declspec(dllexport) void __stdcall SupplierModify(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall Stockxuyi(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall fastcheck(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall ZNProcureManage(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall BIOrderManageDanHao(LandInfo *li,AnsiString Danhao);
extern "C" __declspec(dllexport) void __stdcall ZNStorage(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall ZNWsale(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall Ysbooksale(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall OrdereShenhei(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall CaigoufromOrder(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall daohuofenfa(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall orderask(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall siglefenfa(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall DiaoBo(LandInfo *li,int modle,AnsiString Danhao);
extern "C" __declspec(dllexport) void __stdcall ImpBIOrderManage(LandInfo *li,int type);
extern "C" __declspec(dllexport) void __stdcall OrderLock(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall COrder(LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall COrderLock(LandInfo *li);
#endif
