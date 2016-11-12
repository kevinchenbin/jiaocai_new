//---------------------------------------------------------------------------

#ifndef UnitSelectConditionH
#define UnitSelectConditionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <Buttons.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrmselectcondition : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TCheckBox *cbclient;
	TCheckBox *cbnet;
	TCheckBox *cbsale;
	TComboBox *cbtime;
	TCheckBox *cbinside;
	TSpeedButton *sbok;
	TSpeedButton *sbcancel;
	void __fastcall sbokClick(TObject *Sender);
	void __fastcall cbsaleClick(TObject *Sender);
	void __fastcall sbcancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmselectcondition(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmselectcondition *frmselectcondition;
//---------------------------------------------------------------------------
#endif
