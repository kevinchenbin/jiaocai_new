#include "global.h"
#include "Dog.h"

bool Login(String name,String pwd,int& user, int& storage)
{
	//return true;
	user = -1;
	if (!frmLand->conLand->Connected) {
	  frmLand->conLand->Connected =true;
	}
	String sql = "select ID,StgID from sys_user "
		" where Name = '" + name + "' and Password = '" + pwd + "' and stgID = " + IntToStr(storage) ;
	frmLand->ADODataSet->CommandText = sql;
	frmLand->ADODataSet->Active = true;
	if (frmLand->ADODataSet->RecordCount != 1)
	{
		frmLand->ADODataSet->Active = false;
		frmLand->conLand->Connected = false;
		return false;
	}
	user = frmLand->ADODataSet->FieldByName("ID")->AsInteger;
	storage = frmLand->ADODataSet->FieldByName("StgID")->AsInteger;
	return true;
}
void AddEvent(int type,AnsiString SourceFrom,int user,int Stg,AnsiString Mg)
{
  AnsiString MsType;
  AnsiString sql;

  switch (type) {
	  case 1:
		   MsType = "��Ϣ";
			break;
	  case 2:
		   MsType = "����";
		   break;
	  case 3:
		   MsType = "����";
		   break;
  default:
	  ;
  }
  sql = "insert into sys_log (EventType,SourceFrom,EventDate,EventUser,EventMessage,stgName) values('";
  sql = sql + MsType + "','"+SourceFrom+ "',getDate()," +IntToStr(user) +",'" +  Mg + "'," +IntToStr(Stg) +")";
  TADOQuery *aq = new TADOQuery(NULL);
  aq->Connection = frmLand->conLand ;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->ExecSQL();
  delete aq;

}

bool FindDog()
{
    return true;
	int DevNumber = 1128550468;
	ReadDog *Dog1 = new ReadDog();
	if (1== Dog1->OpenDog())
	   {
		 MessageBoxA(0,"�밲װ���ܹ���","����",MB_ICONERROR);
		 return false;

	   }
	   if (2== Dog1->OpenDog())
	   {
		 MessageBoxA(0,"���ܹ�û�򿪻��������","����",MB_ICONERROR);
		 return false;
	   }
	   if (DevNumber != Dog1->ReadDevNumber())
	   {
		 MessageBoxA(0,"��Ч�ļ��ܹ����������Ա��ϵ","����",MB_ICONERROR);
		 Dog1->CloseDog();
		 return false;
	   }
	Dog1->CloseDog();
	return true;
}
