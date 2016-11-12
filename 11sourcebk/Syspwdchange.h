//---------------------------------------------------------------------------

#ifndef SyspwdchangeH
#define SyspwdchangeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmsyspwdchange : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *edoldpwd;
	TEdit *ednewpwd;
	TEdit *edpwdagain;
	TButton *btOK;
	TButton *btConcel;
	TADOConnection *fcon;
	TADOQuery *aq;
	void __fastcall btOKClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btConcelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmsyspwdchange(TComponent* Owner,TADOConnection *con);
	int userid,storageid;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmsyspwdchange *frmsyspwdchange;
//---------------------------------------------------------------------------
#endif
