
#ifndef customerH
#define customerH

#include <ADODB.hpp>

/* 如果窗体已经打开了则对其激活，如果没有打开则创建窗体 */
extern "C" __declspec(dllexport) void __stdcall SetUpSupplier(TApplication* app, TADOConnection* con, int mode);
/* 返回选中客户的ID */
extern "C" __declspec(dllexport) int __stdcall SelectCustomer(TApplication* app, TADOConnection* con, int mode);


#endif
