//---------------------------------------------------------------------------

#ifndef MemberCardUnuseH
#define MemberCardUnuseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmMemberCardUnuse : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *btok;
	TButton *btconcel;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edcard;
	TEdit *edpassword;
	TADOQuery *aq;
	TLabel *Label3;
	TEdit *edname;
	TADOConnection *fcon;
	void __fastcall btokClick(TObject *Sender);
	void __fastcall btconcelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	int id;
public:		// User declarations
	__fastcall TfrmMemberCardUnuse(TComponent* Owner,TADOConnection *cn,int memberid);
	int userid,fstgid;
	AnsiString logmessage;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMemberCardUnuse *frmMemberCardUnuse;
//---------------------------------------------------------------------------
#endif
