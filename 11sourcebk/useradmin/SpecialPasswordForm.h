//---------------------------------------------------------------------------

#ifndef SpecialPasswordFormH
#define SpecialPasswordFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MDIChild.h"
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmSpecialPassword : public TfrmMDIChild
{
__published:	// IDE-managed Components
	TLabel *lbl1;
	TEdit *edt1;
	TLabel *lbl2;
	TEdit *edt2;
	TLabel *lbl3;
	TEdit *edt3;
	TLabel *lbl4;
	TEdit *edt4;
	TLabel *lbl5;
	TEdit *edt5;
	TLabel *lbl6;
	TEdit *edt6;
	TLabel *lbl7;
	TEdit *edt7;
	TRzButton *btn1;
	TRzButton *btn2;
	TADOCommand *cmd;
	TLabel *lbl8;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btn2Click(TObject *Sender);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmSpecialPassword(TComponent* Owner);
		void Init(LandInfo* li);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSpecialPassword *frmSpecialPassword;
//---------------------------------------------------------------------------
#endif
