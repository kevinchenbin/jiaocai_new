//---------------------------------------------------------------------------

#ifndef UnitfahuoclassH
#define UnitfahuoclassH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class Tfrmfahuoclass : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TCheckBox *ch5;
	TCheckBox *ch6;
	TCheckBox *ch3;
	TCheckBox *ch2;
	TEdit *ed2;
	TEdit *ed3;
	TEdit *ed5;
	TEdit *ed6;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TCheckBox *chclass;
	TEdit *edclass;
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall ed6Change(TObject *Sender);
	void __fastcall ed2Change(TObject *Sender);
	void __fastcall ed3Change(TObject *Sender);
	void __fastcall ed5Change(TObject *Sender);
	void __fastcall edclassChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmfahuoclass(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmfahuoclass *frmfahuoclass;
//---------------------------------------------------------------------------
#endif
