//---------------------------------------------------------------------------

#ifndef unitfapiaoH
#define unitfapiaoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrmunitfapiao : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *ed;
	void __fastcall edKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmunitfapiao(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmunitfapiao *frmunitfapiao;
//---------------------------------------------------------------------------
#endif
