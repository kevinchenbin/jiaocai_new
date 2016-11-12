
#ifndef customerH
#define customerH

#include <ADODB.hpp>

/* 如果窗体已经打开了则对其激活，如果没有打开则创建窗体 */
extern "C" __declspec(dllexport) void __stdcall SetUpSupplier(TApplication* app, TADOConnection* con, int mode);
/* 会员充值 */
extern "C" __declspec(dllexport) void __stdcall MemberPayment(TApplication* app, TADOConnection* con);

/* 返回选中客户的ID */
extern "C" __declspec(dllexport) int __stdcall SelectCustomer(TApplication* app, TADOConnection* con, int mode);

extern "C" __declspec(dllexport) int __stdcall SelectMember(TApplication* app, TADOConnection* con, TComponent* Owner);
extern "C" __declspec(dllexport) int __stdcall NewMember(TApplication* app, TADOConnection* con);
extern "C" __declspec(dllexport) int __stdcall NewCustomer(TApplication* app, TADOConnection* con);

#endif
