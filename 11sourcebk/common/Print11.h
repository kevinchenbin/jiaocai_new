//---------------------------------------------------------------------------

#ifndef Print11H
#define Print11H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RpRave.hpp"
#include "RpBase.hpp"
#include "RpSystem.hpp"
#include "MDIChild.h"
//---------------------------------------------------------------------------
class TfrmPrint11 : public TForm
{
__published:	// IDE-managed Components
	TADOQuery *aquerybs;
	TRvSystem *RvSystem1;
	TRvDataSetConnection *conRVretail;
	TRvProject *prjretail;

private:	// User declarations
public:		// User declarations
	__fastcall TfrmPrint11(TComponent* Owner);

   void RetailPrint(String ID,TADOConnection* con,int stgid);
	 void RetailjiaojiePrint(String userid,TADOConnection* con,int stgid);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrint11 *frmPrint11;
//---------------------------------------------------------------------------
#endif
