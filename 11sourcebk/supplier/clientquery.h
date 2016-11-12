//---------------------------------------------------------------------------

#ifndef clientqueryH
#define clientqueryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tfrmclientquery : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edclientname;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall edclientnameKeyPress(TObject *Sender, wchar_t &Key);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmclientquery(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmclientquery *frmclientquery;
//---------------------------------------------------------------------------
#endif
