#ifndef GlobalH
#define GlobalH

#include <vcl.h>
#include "LandForm.h"

typedef enum
{
    MTBusiness = 1,
	MTStock,
	MTFinance1,
	MTCatalog,
	MTSell,
	MTCustomer,
    MTSystem
}ModuleType1;
bool Login(String name,String pwd,int& user, int& storage);
void AddEvent(int type,AnsiString SourceFrom,int user,int Stg,AnsiString Mg);
bool FindDog();
class storage
{
   AnsiString Name;
   int ID;

};
class booklocal
{
   AnsiString Name;
   AnsiString StgID;
   AnsiString ID;
   AnsiString State;
};



#endif
