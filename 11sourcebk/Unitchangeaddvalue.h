//---------------------------------------------------------------------------

#ifndef UnitchangeaddvalueH
#define UnitchangeaddvalueH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class Tfrmchangeaddvalue : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edname;
	TLabel *Label2;
	TEdit *edcard;
	TLabel *Label3;
	TEdit *edyuan;
	TLabel *Label4;
	TEdit *ednow;
	TLabel *Label5;
	TEdit *edyue;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmchangeaddvalue(TComponent* Owner);
	float getValue();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmchangeaddvalue *frmchangeaddvalue;
//---------------------------------------------------------------------------
#endif
