//---------------------------------------------------------------------------

#ifndef UnitCbpriceH
#define UnitCbpriceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <SqlExpr.hpp>
#include <WideStrings.hpp>
//---------------------------------------------------------------------------
class TfrmCbprice : public TForm
{
__published:	// IDE-managed Components
	TRadioGroup *rg;
	TRzButton *RzButton1;
	TADOQuery *aq;
	TADOConnection *fcon;
	void __fastcall RzButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmCbprice(TComponent* Owner,TADOConnection *con,int stgid);
	int fstgid;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCbprice *frmCbprice;
//---------------------------------------------------------------------------
#endif
