#ifndef pdtypesH
#define pdtypesH

#include <ADODB.hpp>

typedef enum
{
	MTUnknown,
	MTStorageMng, // ���
	MTWsaleMng, // ����
	MTRetailMng, // ����
	MTFinance, //����
	MTBsqry, //��ѯ
	MTBkcatalog, //��Ŀ
	MTDiscount, //����
	MTSysadmin, //ϵͳ����
	MTStore,//������
	MTCustom,//�ͻ�����
	MTData,// ���ݷ���
	MTUser,//�û�Ȩ��
	MTOrder,//����
	MTPur //�ɹ�
}
ModuleType;

typedef struct
{
	TApplication* app;
	TADOConnection* con;
	int userID;
	int storageID;
	AnsiString UserName;
	String FormatStr;
}LandInfo;
class Storage
{
   public:
	 Storage(AnsiString IName,AnsiString IID);
     AnsiString Name;
     AnsiString ID;

};
class Booklocal
{  
   public:
	 Booklocal(AnsiString IName,AnsiString IStgID,AnsiString IID,AnsiString IState);
     AnsiString Name;
     AnsiString StgID;
	 AnsiString ID;
     AnsiString State;
};
Storage::Storage(AnsiString IName,AnsiString IID)
{
   Name = IName;
   ID = IID;
}
Booklocal::Booklocal(AnsiString IName,AnsiString IStgID,AnsiString IID,AnsiString IState)
{
   Name = IName;
   StgID = IStgID;
   ID = IID;
   State= IState;

}

#endif
