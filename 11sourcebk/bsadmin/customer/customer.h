
#ifndef customerH
#define customerH

#include <ADODB.hpp>

/* ��������Ѿ���������伤����û�д��򴴽����� */
extern "C" __declspec(dllexport) void __stdcall SetUpSupplier(TApplication* app, TADOConnection* con, int mode);
/* ����ѡ�пͻ���ID */
extern "C" __declspec(dllexport) int __stdcall SelectCustomer(TApplication* app, TADOConnection* con, int mode);


#endif
