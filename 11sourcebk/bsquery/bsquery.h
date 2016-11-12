#ifndef bsqueryH
#define bsqueryH

#include <ADODB.hpp>
#include "pdtypes.h"

extern "C" __declspec(dllexport) void __stdcall BusinessQuery(TApplication* app, LandInfo* li, int mode);
extern "C" __declspec(dllexport) void __stdcall QueryStorageNote(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall QueryRetailNote(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall QueryWsaleNote(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall Saleduibi(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall QryCheckNote(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall QryOderNote(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall QryProcureNote(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall QryPeisongNote(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall QryJiechun(LandInfo* li);
extern "C" __declspec(dllexport) void __stdcall QryCOderNote(LandInfo* li);
#endif
