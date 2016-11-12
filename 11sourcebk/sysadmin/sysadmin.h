#ifndef sysadminH
#define sysadminH

#include <ADODB.hpp>

extern "C" __declspec(dllexport) void __stdcall SetUpStorageInfo(TApplication* app, TADOConnection* con,int userid,int storageid,bool master);
extern "C" __declspec(dllexport) void __stdcall ManagePrint(TApplication* app, TADOConnection* con, int mode,int stgid);
extern "C" __declspec(dllexport) void __stdcall SetBusiness(TApplication* app, TADOConnection* con);

#endif
