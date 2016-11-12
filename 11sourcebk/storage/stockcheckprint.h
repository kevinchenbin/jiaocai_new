//---------------------------------------------------------------------------

#ifndef stockcheckprintH
#define stockcheckprintH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RpBase.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpSystem.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmstoragecheck : public TForm
{
__published:	// IDE-managed Components
	TRvSystem *RvSystem1;
	TADOQuery *aqcheckreport;
	TRvDataSetConnection *RvDataSetConnection2;
	TRvProject *t;
	void __fastcall RvDataSetConnection1Open(TRvCustomConnection *Connection);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmstoragecheck(TComponent* Owner,TADOConnection *cn);
	void printpantian(int type);
	void aqactive(String Code);

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmstoragecheck *frmstoragecheck;
//---------------------------------------------------------------------------
#endif
