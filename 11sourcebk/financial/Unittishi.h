//---------------------------------------------------------------------------

#ifndef UnittishiH
#define UnittishiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class Tfrmtishi : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRzButton *btok;
	TRadioGroup *rg;
	TCheckBox *cbts;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *edcode;
	TLabel *Label2;
	TEdit *edmy;
	TLabel *Label3;
	TEdit *edsy;
	TLabel *Label4;
	TEdit *edwj;
	TLabel *Label5;
	TEdit *edhc;
	TLabel *Label6;
	TEdit *edyj;
	TLabel *Label7;
	TMemo *membk;
	void __fastcall btokClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmtishi(TComponent* Owner);
	int hc,ts;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmtishi *frmtishi;
//---------------------------------------------------------------------------
#endif
