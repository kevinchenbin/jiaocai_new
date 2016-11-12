#ifndef useradminH
#define useradminH

#include "pdtypes.h"

extern "C" __declspec(dllexport) void __stdcall SetAuthority(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall ManageUserInfo(LandInfo* li);

#endif
