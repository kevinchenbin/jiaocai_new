//---------------------------------------------------------------------------

#ifndef MemberCardchangeH
#define MemberCardchangeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmMemberCardChange : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *ednew;
	TEdit *edconfirm;
	TADOQuery *aq;
	TADOConnection *fcon;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	int id;
public:		// User declarations
	__fastcall TfrmMemberCardChange(TComponent* Owner,TADOConnection *cn,int memberid);
	AnsiString logmessage;
	int userid,fstgid;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMemberCardChange *frmMemberCardChange;
//---------------------------------------------------------------------------
#endif
