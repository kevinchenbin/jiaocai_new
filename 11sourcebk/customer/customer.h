
#ifndef customerH
#define customerH

#include <ADODB.hpp>

/* ��������Ѿ���������伤����û�д��򴴽����� */
extern "C" __declspec(dllexport) void __stdcall SetUpSupplier(TApplication* app, TADOConnection* con, int mode);
/* ��Ա��ֵ */
extern "C" __declspec(dllexport) void __stdcall MemberPayment(TApplication* app, TADOConnection* con);

/* ����ѡ�пͻ���ID */
extern "C" __declspec(dllexport) int __stdcall SelectCustomer(TApplication* app, TADOConnection* con, int mode);

extern "C" __declspec(dllexport) int __stdcall SelectMember(TApplication* app, TADOConnection* con, TComponent* Owner);
extern "C" __declspec(dllexport) int __stdcall NewMember(TApplication* app, TADOConnection* con);
extern "C" __declspec(dllexport) int __stdcall NewCustomer(TApplication* app, TADOConnection* con);

#endif
