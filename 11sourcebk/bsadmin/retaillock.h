//---------------------------------------------------------------------------

#ifndef retaillockH
#define retaillockH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmretaillock : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *edpassword;
	TButton *btok;
	TADOQuery *aq;
	void __fastcall edpasswordKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btokClick(TObject *Sender);
private:	// User declarations
	int Userid;
public:		// User declarations
	__fastcall Tfrmretaillock(TComponent* Owner,TADOConnection *con,int userid);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmretaillock *frmretaillock;
//---------------------------------------------------------------------------
#endif
