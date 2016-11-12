//---------------------------------------------------------------------------

#ifndef UnitfindbookH
#define UnitfindbookH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
#define   WM_FINDNEXTMESSAGE   WM_USER+100
class Tfrmfindorderbook : public TForm
{
__published:	// IDE-managed Components
	TComboBox *cbfindname;
	TEdit *editname;
	TSpeedButton *sbfind;
	TADOQuery *ADOQuery1;
	void __fastcall sbfindClick(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall editnameKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmfindorderbook(TComponent* Owner);
	AnsiString type;
	AnsiString value;
	HANDLE hand;
	TADOQuery *aq;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmfindorderbook *frmfindorderbook;
//---------------------------------------------------------------------------
#endif
