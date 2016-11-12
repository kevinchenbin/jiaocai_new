#ifndef storageadminH
#define storageadminH

#include <vcl.h>
#include <ADODB.hpp>

//extern "C" __declspec(dllexport) void __stdcall ManageStorage(TApplication* app, TADOConnection* con);
extern "C" __declspec(dllexport) void __stdcall CheckStock(TApplication* app, TADOConnection* con);
extern "C" __declspec(dllexport) void __stdcall AdjustStock(TApplication* app, TADOConnection* con);
extern "C" __declspec(dllexport) void __stdcall ManageBookstack(TApplication* app, TADOConnection* con);
extern "C" __declspec(dllexport) void __stdcall WarnStock(TApplication* app, TADOConnection* con);

#endif
