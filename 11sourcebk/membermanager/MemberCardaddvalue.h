//---------------------------------------------------------------------------

#ifndef MemberCardaddvalueH
#define MemberCardaddvalueH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <ADODB.hpp>
//---------------------------------------------------------------------------
class Tfrmaddvalue : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edtcardname;
	TLabel *Label2;
	TEdit *edtcardnum;
	TLabel *Label3;
	TEdit *edtvalue;
	TLabel *Label4;
	TEdit *edtaddvalue;
	TButton *btComfirm;
	TButton *btConsel;
	TADOQuery *MemberCardQuery;
	TADOQuery *quMemberRecord;
	TADOConnection *fcon;
	void __fastcall edtcardnameChange(TObject *Sender);
	void __fastcall edtcardnumChange(TObject *Sender);
	void __fastcall edtvalueChange(TObject *Sender);
	void __fastcall edtaddvalueChange(TObject *Sender);
	void __fastcall btComfirmClick(TObject *Sender);
	void __fastcall btConselClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall edtaddvalueKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
	AnsiString cardID, cardnum, value, addvalue, name;   //IDºÅ£¬¿¨ºÅ£¬¿¨ÄÚÓà¶î£¬³äÖµ½ð¶î	£¬³Ö¿¨ÈË
public:		// User declarations
	__fastcall Tfrmaddvalue(TComponent* Owner,AnsiString MemcardID,TADOConnection *cn);
	int userid,fstgid;
	AnsiString logmessage;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmaddvalue *frmaddvalue;
//---------------------------------------------------------------------------
#endif
