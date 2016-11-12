#ifndef catalogadminH
#define catalogadminH

#include <ADODB.hpp>

extern "C" __declspec(dllexport) void __stdcall ManagePress(TApplication* app, TADOConnection* con);
extern "C" __declspec(dllexport) void __stdcall ManageBookType(TApplication* app, TADOConnection* con);
extern "C" __declspec(dllexport) void __stdcall CatalogKan(TApplication* app, TADOConnection* con,int stgid,int userid,bool add,bool del,bool mod);
extern "C" __declspec(dllexport) void __stdcall Catalogbuilt(TApplication* app, TADOConnection* con);
extern "C" __declspec(dllexport) void __stdcall Catalogneworrec(TApplication* app, TADOConnection* con);
extern "C" __declspec(dllexport) void __stdcall QiKanguanli(TApplication* app, TADOConnection* con);
extern "C" __declspec(dllexport) void __stdcall Multibook(TApplication* app, TADOConnection* con,int stgid,int userid);
extern "C" __declspec(dllexport) void __stdcall BigBookType(TApplication* app, TADOConnection* con);
#endif
