#ifndef dataanalysisH
#define dataanalysisH

#include <ADODB.hpp>

extern "C" __declspec(dllexport) void __stdcall SalesAnalysis(TApplication* app, TADOConnection* con,int stgid);
extern "C" __declspec(dllexport) void __stdcall PurchaseSalesInventoryAnalysis(TApplication* app, TADOConnection* con,int stgid);
extern "C" __declspec(dllexport) void __stdcall SupplierStageClearing(TApplication* app, TADOConnection* con,int stgid);
extern "C" __declspec(dllexport) void __stdcall RetailSummary(TApplication* app, TADOConnection* con,int stgid);
extern "C" __declspec(dllexport) void __stdcall ClientStageClearing(TApplication* app, TADOConnection* con,int stgid);
extern "C" __declspec(dllexport) void __stdcall Yewupaihang(TApplication* app, TADOConnection* con,int stgid);
extern "C" __declspec(dllexport) void __stdcall YuTongji(TApplication* app, TADOConnection* con,int stgid);

#endif
