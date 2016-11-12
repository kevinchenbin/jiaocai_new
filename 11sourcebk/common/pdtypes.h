#ifndef pdtypesH
#define pdtypesH

#include <ADODB.hpp>

typedef enum
{
	MTUnknown,
	MTStorageMng, // 入库
	MTWsaleMng, // 批销
	MTRetailMng, // 零售
	MTFinance, //财务
	MTBsqry, //查询
	MTBkcatalog, //书目
	MTDiscount, //打折
	MTSysadmin, //系统管理
	MTStore,//库存管理
	MTCustom,//客户管理
	MTData,// 数据分析
	MTUser,//用户权限
	MTOrder,//订单
	MTPur //采购
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
