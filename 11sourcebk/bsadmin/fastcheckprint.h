//---------------------------------------------------------------------------

#ifndef fastcheckprintH
#define fastcheckprintH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RpCon.hpp"
#include "RpConBDE.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RpBase.hpp"
#include "RpSystem.hpp"
//---------------------------------------------------------------------------
class Tfrmfastcheckprint : public TForm
{
__published:	// IDE-managed Components
	TRvProject *fastcheck;
	TADOQuery *aqdetail;
	TRvDataSetConnection *Rvfastcheck;
	TRvSystem *RvSystem1;



private:	// User declarations
public:		// User declarations
	__fastcall Tfrmfastcheckprint(TComponent* Owner,TADOConnection *cn,TADOQuery *aq);
	void Tfrmfastcheckprint::PrintExe();
	String title,username;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmfastcheckprint *frmfastcheckprint;
#endif
