

#include "Addsyslog.h"

//---------------------------------------------------------------------------


void AddEvent(int type,AnsiString SourceFrom,int user,int Stg,AnsiString Mg,TADOConnection *con)
{
  AnsiString MsType;
  AnsiString sql;

  switch (type) {
	  case 1:
		   MsType = "ÐÅÏ¢";
			break;
	  case 2:
		   MsType = "¾¯¸æ";
		   break;
	  case 3:
		   MsType = "´íÎó";
		   break;
  default:
	  ;
  }
  sql = "insert into sys_log (EventType,SourceFrom,EventDate,EventUser,EventMessage,stgName) values('";
  sql = sql + MsType + "','"+SourceFrom+ "',getDate()," +IntToStr(user) +",'" +  Mg + "'," +IntToStr(Stg) +")";
  TADOQuery *aq = new TADOQuery(NULL);
  aq->Connection = con ;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->ExecSQL();
  delete aq;

}
