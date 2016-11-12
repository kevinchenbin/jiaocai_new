//---------------------------------------------------------------------------

#ifndef UnitautojieH
#define UnitautojieH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class Tfrmautojieshuan : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edityinhu;
	TLabel *Label2;
	TEdit *editshijie;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TLabel *Label3;
	void __fastcall editshijieKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmautojieshuan(TComponent* Owner);
	float yue;
	bool yuhukuan;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmautojieshuan *frmautojieshuan;
//---------------------------------------------------------------------------
#endif
