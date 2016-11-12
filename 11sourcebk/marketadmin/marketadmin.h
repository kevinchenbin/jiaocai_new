#ifndef marketadminH
#define marketadminH

#include <vcl.h>
#include <ADODB.hpp>

extern "C" __declspec(dllexport) void __stdcall ControlDiscount(TApplication* app, TADOConnection* con);
extern "C" __declspec(dllexport) void __stdcall ManageRetailSales(TApplication* app, TADOConnection* con);
extern "C" __declspec(dllexport) void __stdcall DiscountSales(TApplication* app, TADOConnection* con,int stgid);
extern "C" __declspec(dllexport) void __stdcall WsaleDiscount(TApplication* app, TADOConnection* con,int stgid);
extern "C" __declspec(dllexport) void __stdcall MemberDiscount(TApplication* app, TADOConnection* con,int stgid);
extern "C" __declspec(dllexport) void __stdcall WsaleDiscountSales(TApplication* app, TADOConnection* con,int stgid);
extern "C" __declspec(dllexport) void __stdcall Memtypeadd(TApplication* app, TADOConnection* con,int stgid);



#endif
