//---------------------------------------------------------------------------

#ifndef UnitclasscodeH
#define UnitclasscodeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class Tfrmclasscode : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TCheckBox *ch5;
	TCheckBox *ch8;
	TCheckBox *ch7;
	TCheckBox *ch6;
	TCheckBox *ch4;
	TCheckBox *ch3;
	TCheckBox *ch2;
	TCheckBox *ch1;
	TEdit *ed1;
	TEdit *ed2;
	TEdit *ed3;
	TEdit *ed4;
	TEdit *ed5;
	TEdit *ed6;
	TEdit *ed7;
	TEdit *ed8;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall ed1Change(TObject *Sender);
	void __fastcall ed6Change(TObject *Sender);
	void __fastcall ed2Change(TObject *Sender);
	void __fastcall ed3Change(TObject *Sender);
	void __fastcall ed4Change(TObject *Sender);
	void __fastcall ed5Change(TObject *Sender);
	void __fastcall ed7Change(TObject *Sender);
	void __fastcall ed8Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmclasscode(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmclasscode *frmclasscode;
//---------------------------------------------------------------------------
#endif
