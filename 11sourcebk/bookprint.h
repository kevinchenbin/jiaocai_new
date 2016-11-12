//---------------------------------------------------------------------------

#ifndef bookprintH
#define bookprintH
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
class Tfrmbookprint : public TForm
{
__published:	// IDE-managed Components
	TRvDataSetConnection *rvdatacondiaobo11;
	TRvProject *RvProject11;
	TRvSystem *RvSystem11;
	TADOConnection *con;
	TADOQuery *aqprint1;
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmbookprint(TComponent* Owner,TADOConnection *cn);
	void SetPrint(AnsiString Code);
	void Print();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmbookprint *frmbookprint;
//---------------------------------------------------------------------------
#endif
