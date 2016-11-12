#ifndef financeadminH
#define financeadminH

#include <vcl.h>
#include <ADODB.hpp>

extern "C" __declspec(dllexport) void __stdcall CheckSupplierFinance(TApplication* app, TADOConnection* con, int bsmode);
extern "C" __declspec(dllexport) void __stdcall CheckCustomerFinance(TApplication* app, TADOConnection* con, int bsmode);

#endif
