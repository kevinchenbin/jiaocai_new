//---------------------------------------------------------------------------

#ifndef MemberCardaddvalueH
#define MemberCardaddvalueH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrmaddvalue : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *Edit1;
	TLabel *Label2;
	TEdit *edtcardnum;
	TLabel *Label3;
	TEdit *edtvalue;
	TLabel *Label4;
	TEdit *edtaddvalue;
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmaddvalue(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmaddvalue *frmaddvalue;
//---------------------------------------------------------------------------
#endif
